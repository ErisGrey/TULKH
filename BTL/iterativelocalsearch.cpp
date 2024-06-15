#include "iterativelocalsearch.h"
#include <algorithm>
#include <random>

IterativeLocalSearch::IterativeLocalSearch(Solution& solution) : solution(solution) {}

pair<vector<int>, int> IterativeLocalSearch::performIterativeLocalSearch(int maxIterations) {
    vector<int> bestSolution = solution.gen_init_sol();
    int bestCost = solution.evaluateSolution(bestSolution);

    for (int iter = 0; iter < maxIterations; ++iter) {
        
        vector<int> perturbedSolution = perturbSolution(bestSolution);
        auto localSolution = performLocalSearch(perturbedSolution).first;
        auto localCost = performLocalSearch(perturbedSolution).second;

        if (localCost > bestCost) {
            bestSolution = localSolution;
            bestCost = localCost;
        }
    }

    return { bestSolution, bestCost };
}

vector<int> IterativeLocalSearch::perturbSolution(const std::vector<int>& currentSolution) {
    vector<int> newSolution = currentSolution;
    int num_order = solution.num_order;
    int num_veh = solution.num_veh;

    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, num_order - 1);
    std::uniform_int_distribution<> vehicleDis(0, num_veh - 1);

    int perturbationSize = max(1, num_order / 10); 

    for (int i = 0; i < perturbationSize; ++i) {
        int orderIndex = dis(gen);
        int newVehicle = vehicleDis(gen);
        newSolution[orderIndex] = newVehicle;
    }

    return newSolution;
}

pair<vector<int>, int> IterativeLocalSearch::performLocalSearch(const vector<int>& initialSolution) {
    vector<int> currentSolution = initialSolution;
    int currentCost = solution.evaluateSolution(currentSolution);

    bool improved = true;

    while (improved) {
        improved = false;
        vector<vector<int>> neighbors = solution.getNeighbors(currentSolution);
        for (const auto& neighbor : neighbors) {
            int neighborCost = solution.evaluateSolution(neighbor);
            if (neighborCost > currentCost) {
                currentSolution = neighbor;
                currentCost = neighborCost;
                improved = true;
                break;
            }
        }
    }

    return { currentSolution, currentCost };
}
