# Threshold Distribution Pilot Protocol

## Objective

Understand how threshold assumptions affect cascade behavior.

## Fixed parameters

- N = 100 agents
- p = 0.1 edge probability
- k = 5 initially active agents
- T = 100 maximum steps

## Planned conditions

1. Thresholds sampled from Uniform(0,1)
2. All thresholds fixed at 0.5
3. All thresholds fixed at 0.9

## First checkpoint

Before modifying the code, compile and run the original implementation
unchanged using a fixed random seed.

## Recorded outputs

- time step;
- total number of active agents;
- newly active agents;
- final cascade size;
- number of steps before termination;
- random seed.

## Status

Learning experiment only. It is not part of an approved final research
question.

## Predictions

### Uniform(0,1)

The population contains both easily activated and resistant agents.
Some low-threshold agents may begin a cascade, but the final outcome
may vary substantially across network structures and initial seed locations.

### Fixed threshold = 0.5

Every inactive agent requires at least half of its neighbors to be active.
Spread should depend strongly on local reinforcement and the placement
of the initial active agents.

### Fixed threshold = 0.9

Large cascades should be less common because almost all neighbors of an
inactive agent must already be active. Spread may continue through low-degree
nodes, but it may stop at the boundary of an active cluster when external
nodes do not receive sufficient support.

## Fair-comparison requirement

For the same random seed, all three conditions must use:

- the same generated network;
- the same initial active agents;
- different thresholds only.

Separate random-number generators will be used for graph generation,
initial-agent selection, and threshold generation.
