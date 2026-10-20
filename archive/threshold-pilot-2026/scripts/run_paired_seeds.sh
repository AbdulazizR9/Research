#!/usr/bin/env bash

set -euo pipefail

PILOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

SOURCE="$PILOT_DIR/src/main.cpp"
BINARY="$PILOT_DIR/build/lt_model"
RAW_DIR="$PILOT_DIR/results/raw"
PROCESSED_DIR="$PILOT_DIR/results/processed"
SUMMARY="$PROCESSED_DIR/summary_seeds_1_10.csv"

mkdir -p \
  "$PILOT_DIR/build" \
  "$RAW_DIR" \
  "$PROCESSED_DIR"

echo "Compiling model..."

clang++ -std=c++17 -O2 \
  "$SOURCE" \
  -o "$BINARY"

printf '%s\n' \
  "seed,condition,final_active,final_proportion,stabilization_step" \
  > "$SUMMARY"

run_condition() {
    local seed="$1"
    local condition="$2"
    local threshold_mode="$3"
    local threshold_value="$4"

    local output_file="$RAW_DIR/${condition}_seed_${seed}.csv"

    printf "100 100 0.1 5 %s %s %s\n" \
      "$seed" \
      "$threshold_mode" \
      "$threshold_value" \
      | "$BINARY" \
      > "$output_file"

    local initial_line
    local final_line

    initial_line="$(sed -n '2p' "$output_file")"
    final_line="$(tail -n 1 "$output_file")"

    local initial_t
    local initial_active
    local initial_new

    IFS=',' read -r \
      initial_t \
      initial_active \
      initial_new \
      <<< "$initial_line"

    local final_t
    local final_active
    local final_new

    IFS=',' read -r \
      final_t \
      final_active \
      final_new \
      <<< "$final_line"

    if [[ "$initial_t" != "0" ]]; then
        echo "ERROR: initial time is not zero in $output_file" >&2
        exit 1
    fi

    if [[ "$initial_active" != "5" ]]; then
        echo "ERROR: initial active count is not five in $output_file" >&2
        exit 1
    fi

    if [[ "$final_new" != "0" ]]; then
        echo "ERROR: simulation did not record stabilization in $output_file" >&2
        exit 1
    fi

    local final_proportion

    final_proportion="$(
      awk -v active="$final_active" \
        'BEGIN { printf "%.4f", active / 100.0 }'
    )"

    printf "%s,%s,%s,%s,%s\n" \
      "$seed" \
      "$condition" \
      "$final_active" \
      "$final_proportion" \
      "$final_t" \
      >> "$SUMMARY"
}

for seed in $(seq 1 10); do
    echo "Running paired seed $seed..."

    run_condition \
      "$seed" \
      "uniform" \
      "uniform" \
      "0"

    run_condition \
      "$seed" \
      "fixed_05" \
      "fixed" \
      "0.5"

    run_condition \
      "$seed" \
      "fixed_09" \
      "fixed" \
      "0.9"
done

echo
echo "Completed 30 simulations."
echo "Summary written to:"
echo "$SUMMARY"
