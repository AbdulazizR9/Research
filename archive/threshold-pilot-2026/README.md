# Threshold Cascade Learning Pilot

**Period:** July–August 2026  
**Status:** Archived learning experiment

## Overview

This project explores threshold-based diffusion through a small agent-based simulation implemented in C++17.

It uses an irreversible, synchronous Linear Threshold model on a randomly generated undirected network.

The objective was to understand how different threshold assumptions affect cascade behavior and to practice designing reproducible computational experiments.

## Model and Experiments

Three threshold conditions were compared:

1. Individual thresholds sampled from Uniform(0,1).
2. A fixed threshold of 0.5 for every agent.
3. A fixed threshold of 0.9 for every agent.

The experiments used 100 agents, an edge probability of 0.1, five initially active agents, and a maximum of 100 simulation steps.

Ten paired random seeds were tested under all three conditions, producing 30 simulation runs. For each seed, the network and initial active agents were held constant across conditions.

## Implementation

- `src/main.cpp` — C++ simulation implementation.
- `scripts/run_paired_seeds.sh` — Compilation and batch experiment script.
- `protocol.md` — Experimental design and comparison conditions.
- `observations.md` — Recorded observations and interpretation.
- `results/processed/` — Summary results in CSV format.
- `learning/` — Notes documenting model assumptions and concepts.

## Running the Experiment

The batch script requires a C++17-capable Clang compiler and standard Bash command-line utilities.

From this project's directory, run:

`bash scripts/run_paired_seeds.sh`

The script compiles the simulation, executes the 30 runs, and writes the resulting CSV files.

## Recorded Results

In the ten-seed experiment, the mean final number of active agents was:

- Uniform(0,1): 40.8
- Fixed threshold 0.5: 5.0
- Fixed threshold 0.9: 5.0

Both fixed-threshold conditions stopped at the initial five active agents in these runs, creating a floor effect. This does not establish that the two fixed thresholds behave equivalently in general.

See `observations.md` for the detailed results and limitations.

## Scope and Limitations

This project was an educational simulation and experimental exercise. It does not claim scientific novelty, empirical validation, or general conclusions about real-world diffusion.

The recorded results are limited to the selected model, parameters, and ten random seeds.

The original development history is preserved in the repository, including the [August 2026 archival snapshot](https://github.com/AbdulazizR9/Research/tree/archive/threshold-pilot-2026-08).