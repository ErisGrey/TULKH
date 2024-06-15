#include "LocalSearch.h"
#include<iostream>
using namespace std;
LocalSearch::LocalSearch(const Solution& solution)
    : solution(solution) {}

pair<vector<int>, long> LocalSearch::performLocalSearch() {

    vector<int> currentSolution = solution.gen_init_sol();
    int currentCost = solution.evaluateSolution(currentSolution);

    cout << currentCost << endl;
    while (true) {
        vector<vector<int>> neighbors = solution.getNeighbors(currentSolution);
        bool improved = false;
        for (const auto& neighbor : neighbors) {
            int neighborCost = solution.evaluateSolution(neighbor);
           
            if (neighborCost > currentCost)
            {
                cout << "ic" << endl;
                currentSolution = neighbor;
                currentCost = neighborCost;
                improved = true;
                break;
            }
        }

        if (!improved) {
            break;
        }
    }

    return { currentSolution, currentCost };
}
