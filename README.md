🧠 PROJECT: Agent Binary Decision Simulation Framework
0️⃣ Цель
Система для воспроизводимых симуляций, позволяющая:
включать/выключать факторы через config
запускать разные сценарии
собирать метрики
сравнивать эксперименты
1️⃣ Технологии
C++17+
STL
<random> (std::mt19937)
CSV output
Python (visualization only)
2️⃣ Структура проекта
/main.cpp

/config
    SimulationConfig.h

/core
    Agent.h / Agent.cpp
    World.h / World.cpp
    Simulation.h / Simulation.cpp

/graph
    Graph.h / Graph.cpp        (Stage 3)

/io
    DataLogger.h / DataLogger.cpp

/scripts
    plot_results.py
3️⃣ CONFIG SYSTEM
SimulationConfig
int N_agents;
int T_steps;
int seed;

double p_random_switch;
double noise_level;

bool use_confidence;
bool use_conformism;
bool use_social_pressure;
bool use_network;
bool use_emergency;

TopologyType topology;

std::string output_file;
4️⃣ RNG
std::mt19937 rng(seed);
Передаётся:
в World
в Agent decision logic
5️⃣ КЛАСС Agent
Поля
int id;
int choice;
int next_choice;

double confidence;
double conformism;
Методы
void compute_next_state(const World& world, std::mt19937& rng);
void apply_next_state();
6️⃣ КЛАСС World
Поля
std::vector<Agent> agents;
Graph graph;                // если use_network = true
int current_step;
SimulationConfig config;
Методы
void initialize();
void step();
Metrics collect_metrics() const;
7️⃣ DECISION MODEL
7.1 BASELINE (Stage 1)
Активно:
use_confidence = false
use_conformism = false
use_social_pressure = false
use_network = false
use_emergency = false
Правило:
switch with probability p_random_switch
7.2 CONFIDENCE (Stage 2)
Используется:
confidence
Влияние:
снижает вероятность смены выбора
7.3 SOCIAL PRESSURE (Stage 3)
Используется:
conformism
majority_choice_of_neighbors
7.4 NOISE MODEL
Финальная формула решения:
decision_score =
    deterministic_part
    + random_noise(noise_level)
7.5 EMERGENCY MODE
При use_emergency = true:
noise_level ↑
confidence_weight ↓
8️⃣ GRAPH TOPOLOGY (Stage 3)
Поддержать:
FullyConnected (Stage 2 fallback)
Lattice / Grid
Random graph (optional)
9️⃣ DATA LOGGER
CSV формат:
Step,
ChoiceA_Count,
ChoiceB_Count,
Switch_Count,
Fraction_A,
Avg_Confidence
🔟 МЕТРИКИ
Рассчитывать:
fraction_A
switch_count_per_step
time_to_stability
polarization_index (Stage 3+)
1️⃣1️⃣ STAGE SYSTEM
🟩 STAGE 1 — BASELINE ENGINE
DONE
✔ симуляция работает
✔ RNG с seed
✔ CSV генерируется
✔ разные p_random_switch → разная динамика
🟩 STAGE 2 — INTERNAL FACTOR (CONFIDENCE)
DONE
✔ влияние confidence видно в switching rate
✔ homogeneous vs heterogeneous confidence
🟩 STAGE 3 — SOCIAL DYNAMICS
DONE
✔ majority influence работает
✔ graph topology подключена
✔ появляется consensus / polarization
🟩 STAGE 4 — EMERGENCY / NOISE
DONE
✔ normal vs emergency различаются
✔ confidence теряет силу при high noise
1️⃣2️⃣ PYTHON VISUALIZATION
plot_results.py
Читает CSV и строит:
fraction_A vs time
switch_count vs time
scenario comparison
Библиотеки:
pandas
matplotlib / seaborn
1️⃣3️⃣ EXPERIMENT WORKFLOW
Каждый запуск определяется через config:
stage
parameters
scenario
seed