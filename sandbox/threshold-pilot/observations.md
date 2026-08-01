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

## Paired-seed experiment: seeds 1-10

### Parameters

- N = 100
- p = 0.1
- k = 5
- T = 100
- paired seeds = 1 through 10

For every seed, the three threshold conditions used the same generated
network and the same initially active agents.

### Descriptive results

| Condition | Mean final active | Median final active | Minimum | Maximum | Runs above 50 active |
|---|---:|---:|---:|---:|---:|
| Uniform(0,1) | 40.8 | 36.5 | 11 | 75 | 4/10 |
| Fixed 0.5 | 5.0 | 5.0 | 5 | 5 | 0/10 |
| Fixed 0.9 | 5.0 | 5.0 | 5 | 5 | 0/10 |

The Uniform(0,1) condition stabilized after an average of 9 recorded
steps, including the final zero-change step.

The fixed-threshold conditions stabilized at step 1 in every run.

### Interpretation

Uniform threshold heterogeneity created low-threshold agents that could
activate under weak initial exposure. Their activation increased exposure
for other agents and allowed cascades of different sizes to develop.

With only five initially active agents, fixed thresholds of 0.5 and 0.9
were too demanding for any inactive agent to activate during the first
update in these ten realizations.

### Floor effect

The fixed 0.5 and fixed 0.9 conditions both remained at the initial active
count of five. Therefore, this experiment does not show that the two
threshold values are behaviorally equivalent.

Instead, both conditions reached the same lower-bound outcome under the
selected initial conditions.

### Scope of the conclusion

These ten simulations are sufficient for a learning pilot and demonstrate
that threshold-distribution assumptions can strongly change cascade
behavior.

They are not sufficient for a general scientific claim about typical
cascade probabilities or all parameter settings.
