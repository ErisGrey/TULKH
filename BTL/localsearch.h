#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "Solution.h"
#include <vector>

using namespace std;
class LocalSearch {
public:
    LocalSearch(const Solution& solution);
    pair<vector<int>, long> performLocalSearch();


    Solution solution;
};

#endif // LOCALSEARCH_H
