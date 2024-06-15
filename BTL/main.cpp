#include <iostream>
#include "config.h"
#include "instance.h"
#include "solver.h"
#include "solution.h"
#include "localsearch.h"
#include "iterativelocalsearch.h"

int main(int argc, char* argv[])
{
    
   // BTL -i "C:\Users\ErisGrey\Downloads\BTL_test.txt"
   // BTL -i "C:\Users\ErisGrey\Downloads\inputTULKH2\testcase_192_14.txt"
   // BTL -i "C:\Users\ErisGrey\Downloads\testcase_166_19.txt"
    Config config(argc, argv);

    Instance instance(config.input);
    Solver solver(&instance, instance.instanceName, instance.instanceName, config.time_limit, config.mem_limit);
    solver.Solve();



    Solution solution(instance);
    vector<int> init_sol = solution.gen_init_sol();
    solution.print(init_sol);
    LocalSearch localSearch(solution);

    auto result = localSearch.performLocalSearch();
    vector<int> bestSolution = result.first;
    long bestCost = result.second;

    cout << "Best solution found:" << bestCost << endl;


    for (int i = 0; i < instance.num_order; ++i) {
        cout << bestSolution[i] << " ";
    }
    cout << endl;



    //Solution init_sol(instance);
    IterativeLocalSearch iterativeLocalSearch(solution);

    int maxIterations = 1000; // Define the number of iterations for ILS
    auto result = iterativeLocalSearch.performIterativeLocalSearch(maxIterations);
    vector<int> bestSolution = result.first;
    int bestCost = result.second;
    vector<int> vehicleLoad(instance.num_veh, 0);

    for (int i = 0; i < instance.num_order; ++i) {
        if (bestSolution[i] != -1) {
            vehicleLoad[bestSolution[i]] += instance.quantity[i];
        }
    }

    for (int i = 0; i < instance.num_veh; i++)
    {
        cout << vehicleLoad[i] << " ";
    }
    cout << endl;
    std::cout << "Cost of best solution: " << bestCost << std::endl;


    return 0;
}