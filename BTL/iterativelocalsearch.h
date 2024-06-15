#ifndef ITERATIVELOCALSEARCH_H
#define ITERATIVELOCALSEARCH_H

#include "solution.h"
#include <vector>
#include <utility>
#include <iostream>
using namespace std;
class IterativeLocalSearch {
public:
    IterativeLocalSearch(Solution& solution);
    pair<vector<int>, int> performIterativeLocalSearch(int maxIterations);

    Solution& solution;
    vector<int> perturbSolution(const vector<int>& currentSolution);
    pair<vector<int>, int> performLocalSearch(const vector<int>& initialSolution);
};

#endif // ITERATIVELOCALSEARCH_H

