#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "Instance.h"
#include <iostream>

using namespace std;
class Solution {
public:
    Solution(const Instance& instance);
    vector<int> gen_init_sol();
    int evaluateSolution(const vector<int>& solution);
    
    vector<vector<int>> getNeighbors(const vector<int>& solution);

    int num_order;
    int num_veh;
    vector<int> quantities;
    vector<int> costs;
    vector<int> low_bou;
    vector<int> up_bou;

    void print(const vector<int>& solution);
};

#endif // SOLUTION_H
