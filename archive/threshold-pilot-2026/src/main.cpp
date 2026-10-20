#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

using Graph = std::vector<std::vector<int>>;

// Generate an undirected Erdős–Rényi G(N, p) graph.
Graph generate_graph(int n, double edge_probability, std::mt19937& rng) {
    Graph adjacency(n);
    std::uniform_real_distribution<double> uniform(0.0, 1.0);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (uniform(rng) < edge_probability) {
                adjacency[i].push_back(j);
                adjacency[j].push_back(i);
            }
        }
    }

    return adjacency;
}

// Select k different initially active agents.
std::vector<int> initialize_active_state(
    int n,
    int initial_active_count,
    std::mt19937& rng
) {
    std::vector<int> active(n, 0);
    std::vector<int> agent_ids(n);

    std::iota(agent_ids.begin(), agent_ids.end(), 0);
    std::shuffle(agent_ids.begin(), agent_ids.end(), rng);

    for (int i = 0; i < initial_active_count; ++i) {
        active[agent_ids[i]] = 1;
    }

    return active;
}

// Create either Uniform(0,1) thresholds or one fixed threshold.
std::vector<double> initialize_thresholds(
    int n,
    const std::string& threshold_mode,
    double fixed_threshold,
    std::mt19937& rng
) {
    std::vector<double> thresholds(n);

    if (threshold_mode == "uniform") {
        std::uniform_real_distribution<double> uniform(0.0, 1.0);

        for (double& threshold : thresholds) {
            threshold = uniform(rng);
        }
    } else if (threshold_mode == "fixed") {
        std::fill(
            thresholds.begin(),
            thresholds.end(),
            fixed_threshold
        );
    } else {
        throw std::invalid_argument(
            "threshold_mode must be 'uniform' or 'fixed'"
        );
    }

    return thresholds;
}

void run_simulation(
    int maximum_steps,
    const Graph& adjacency,
    const std::vector<double>& thresholds,
    std::vector<int> active
) {
    int active_count = static_cast<int>(
        std::count(active.begin(), active.end(), 1)
    );

    // CSV header and initial state.
    std::cout << "t,active_count,newly_active\n";
    std::cout << "0," << active_count << ",0\n";

    for (int t = 1; t <= maximum_steps; ++t) {
        // Synchronous update:
        // all decisions use the old active state.
        std::vector<int> next_active = active;
        int newly_active = 0;

        for (std::size_t i = 0; i < active.size(); ++i) {
            if (active[i] == 1) {
                continue;
            }

            // An isolated node has no social exposure.
            if (adjacency[i].empty()) {
                continue;
            }

            int active_neighbors = 0;

            for (int neighbor : adjacency[i]) {
                active_neighbors += active[neighbor];
            }

            const double active_fraction =
                static_cast<double>(active_neighbors) /
                static_cast<double>(adjacency[i].size());

            if (active_fraction >= thresholds[i]) {
                next_active[i] = 1;
                ++newly_active;
            }
        }

        active = std::move(next_active);
        active_count += newly_active;

        // Record every step, including the stabilization step.
        std::cout
            << t << ","
            << active_count << ","
            << newly_active << "\n";

        if (newly_active == 0) {
            break;
        }
    }
}

int main() {
    int maximum_steps = 0;
    int number_of_agents = 0;
    double edge_probability = 0.0;
    int initial_active_count = 0;
    std::uint32_t seed = 0;
    std::string threshold_mode;
    double fixed_threshold = 0.0;

    // Input format:
    // T N p k seed threshold_mode threshold_value
    if (!(std::cin
          >> maximum_steps
          >> number_of_agents
          >> edge_probability
          >> initial_active_count
          >> seed
          >> threshold_mode
          >> fixed_threshold)) {
        std::cerr
            << "Usage: T N p k seed threshold_mode threshold_value\n"
            << "Example: 100 100 0.1 5 42 uniform 0\n"
            << "Example: 100 100 0.1 5 42 fixed 0.5\n";
        return 1;
    }

    if (maximum_steps < 1) {
        std::cerr << "T must be at least 1.\n";
        return 1;
    }

    if (number_of_agents < 1) {
        std::cerr << "N must be at least 1.\n";
        return 1;
    }

    if (edge_probability < 0.0 || edge_probability > 1.0) {
        std::cerr << "p must be between 0 and 1.\n";
        return 1;
    }

    if (initial_active_count < 0 ||
        initial_active_count > number_of_agents) {
        std::cerr << "k must be between 0 and N.\n";
        return 1;
    }

    if (threshold_mode != "uniform" &&
        threshold_mode != "fixed") {
        std::cerr
            << "threshold_mode must be 'uniform' or 'fixed'.\n";
        return 1;
    }

    if (threshold_mode == "fixed" &&
        (fixed_threshold < 0.0 || fixed_threshold > 1.0)) {
        std::cerr
            << "A fixed threshold must be between 0 and 1.\n";
        return 1;
    }

    /*
     * Separate RNG streams are required for a fair comparison.
     *
     * Changing threshold mode must not change:
     * - the graph;
     * - the initially active agents.
     */
    std::mt19937 graph_rng(seed);
    std::mt19937 initial_state_rng(seed + 1U);
    std::mt19937 threshold_rng(seed + 2U);

    const Graph adjacency = generate_graph(
        number_of_agents,
        edge_probability,
        graph_rng
    );

    std::vector<int> active = initialize_active_state(
        number_of_agents,
        initial_active_count,
        initial_state_rng
    );

    const std::vector<double> thresholds = initialize_thresholds(
        number_of_agents,
        threshold_mode,
        fixed_threshold,
        threshold_rng
    );

    run_simulation(
        maximum_steps,
        adjacency,
        thresholds,
        std::move(active)
    );

    return 0;
}
