#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

uniform_real_distribution<double> uni(0.0, 1.0);

void generate_graph(int N, double p, mt19937 &rng, vector<vector<int>> &adj){

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (uni(rng) < p) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
}

void initialize_state(int N, int k, mt19937 &rng, vector<int> &active){
    vector<int> nums(N);
    for (int i = 0; i < N; i++){
        nums[i] = i;
    }
    shuffle(nums.begin(), nums.end(), rng);
    for (int i = 0; i < min(k, N); i++){
        active[nums[i]] = 1;
    }
}

void initialize_thresholds(int N, mt19937 &rng, vector<double> &thresholds){
    for (int i = 0; i < N; i++){
        thresholds[i] = uni(rng);
    }
}

void run_simulation(int T, vector<vector<int>> &adj, vector<int> &active, vector<double> &thresholds){
    int active_count = 0;
    for (int i = 0; i < active.size(); i++){
        if (active[i]) active_count++;
    }
    cout << 0 << " " << active_count << "\n";

    for (int t = 1; t <= T; t++){
        vector<int> next_active = active;
        int next_ac = 0;
        for (int i = 0; i < active.size(); i++){
            if (!active[i]){
                int active_n = 0;
                for (int j = 0; j < adj[i].size(); j++){
                    if (active[adj[i][j]]) active_n++;
                }
                double fraction;
                if (adj[i].size() == 0) fraction = 0;
                else fraction = (1.0 * active_n) / (adj[i].size());
                if (fraction >= thresholds[i]){
                    next_active[i] = 1;
                    next_ac++;
                }
            }
        }
        if (next_ac == 0) break;
        active_count += next_ac;
        active = next_active;
        cout << t << " " << active_count << " " << next_ac << "\n";
    }
}

int main(){

    int T, N, k;
    double p;
    unsigned seed;
    cin >> T >> N >> p >> k >> seed;

    mt19937 rng(seed);
    vector<vector<int>> adj(N);
    vector<double> thresholds(N);
    vector<int> active(N, 0);
    generate_graph(N, p, rng, adj);
    initialize_thresholds(N, rng, thresholds);
    initialize_state(N, k, rng, active);
    run_simulation(T, adj, active, thresholds);

    return 0;
}