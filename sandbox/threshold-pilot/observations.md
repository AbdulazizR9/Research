# Threshold Distribution Pilot Observations

## Single-seed checkpoint

Parameters:

- N = 100
- p = 0.1
- k = 5
- T = 100
- seed = 42

## Results

| Threshold condition | Final active count | Final active proportion | Stabilization step |
|---|---:|---:|---:|
| Uniform(0,1) | 29 | 0.29 | 7 |
| Fixed 0.5 | 5 | 0.05 | 1 |
| Fixed 0.9 | 5 | 0.05 | 1 |

## Initial interpretation

Under the same graph and initial active set, heterogeneous Uniform(0,1)
thresholds allowed the cascade to begin and reach 29 agents.

The fixed 0.5 and fixed 0.9 conditions both stopped immediately because no
inactive agent met the activation condition during the first update.

This is evidence about one random realization only. It does not establish
the typical behavior of any condition.

## Methodological note

The comparison isolates threshold assumptions because graph generation,
initial-state generation, and threshold generation use separate random-number
streams.
