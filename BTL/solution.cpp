#include "Solution.h"
#include <algorithm>
#include <limits>

using namespace std;
Solution::Solution(const Instance& instance)
    : num_order(instance.num_order), num_veh(instance.num_veh), quantities(instance.quantity), costs(instance.cost), low_bou(instance.low_bou), up_bou(instance.up_bou) {}

vector<int> Solution::gen_init_sol() {
    vector<int> solution(num_order, -1);
    vector<int> vehicleLoad(num_veh, 0);
    
    vector<pair<int, int>> vehicles;
    for (int k = 0; k < num_veh; ++k) {
        vehicles.push_back({up_bou[k] - low_bou[k], k });
    }
    sort(vehicles.rbegin(), vehicles.rend(), [](const auto& a, const auto& b) { return a.first > b.first; });

    // Sort orders by cost in descending order
    vector<pair<int, int>> orders;
    for (int i = 0; i < num_order; ++i) {
        orders.push_back({ costs[i], i });
    }
    sort(orders.rbegin(), orders.rend());

    // Assign orders to vehicles while ensuring feasibility
    for (auto vehicle : vehicles) {
        int vehicleIndex = vehicle.second;
        for (auto order : orders) {
            /*if (vehicleLoad[vehicleIndex] >= low_bou[vehicleIndex])
                continue;*/
            int orderIndex = order.second;
            if (solution[orderIndex] == -1 && vehicleLoad[vehicleIndex] + quantities[orderIndex] <= up_bou[vehicleIndex])
            {
                solution[orderIndex] = vehicleIndex;
                vehicleLoad[vehicleIndex] += quantities[orderIndex];
            }
        }
        // Ensure the vehicle meets its lower bound
        if (vehicleLoad[vehicleIndex] < low_bou[vehicleIndex])
        {
            for (auto order : orders)
            {
                int orderIndex = order.second;
                if (solution[orderIndex] != vehicleIndex && solution[orderIndex] != -1 && vehicleLoad[solution[orderIndex]] - quantities[orderIndex] >= low_bou[solution[orderIndex]] && vehicleLoad[vehicleIndex] + quantities[orderIndex] <= up_bou[vehicleIndex]) {
                    vehicleLoad[solution[orderIndex]] -= quantities[orderIndex];
                    vehicleLoad[vehicleIndex] += quantities[orderIndex];
                    solution[orderIndex] = vehicleIndex;
                }
                if (vehicleLoad[vehicleIndex] >= low_bou[vehicleIndex]) break;
            }
        }

        if (vehicleLoad[vehicleIndex] < low_bou[vehicleIndex])
        {
            for (auto order : orders)
            {
                int orderIndex = order.second;
                if (solution[orderIndex] == vehicleIndex)
                {
                    solution[orderIndex] = -1;
                    vehicleLoad[vehicleIndex] -= quantities[orderIndex];
                }

            }
        
            
        }
        
    }
    return solution;
}

int Solution::evaluateSolution(const vector<int>& solution) {
    int totalCost = 0;
    vector<int> vehicleLoad(num_veh, 0);
    int error = 0;


    for (int i = 0; i < num_order; ++i) {
        if (solution[i] != -1) {
            vehicleLoad[solution[i]] += quantities[i];
            totalCost += costs[i];
        }
    }
    
    for (int k = 0; k < num_veh; ++k) {
        if (vehicleLoad[k] < low_bou[k] && vehicleLoad[k] > 0)
        {
           // cout << "low at " << k << endl;
            error += 1;
            //pen += low_bou[k] - vehicleLoad[k];
            
        }
        else if (vehicleLoad[k] > up_bou[k])
        {
           // cout << "up at " << k << endl;
            error += 1;
            //pen += vehicleLoad[k] - up_bou[k];
        }
    }
    if (error == 0)
        return totalCost;
    else
    {
       // cout << "Error = " << error << endl;
        return -error ;
    }
        
}

vector<vector<int>> Solution::getNeighbors(const vector<int>& solution) {
    vector<vector<int>> neighbors;
    for (int i = 0; i < num_order; ++i) {
        for (int k = -1; k < num_veh; ++k) {
            if (solution[i] != k) {
                vector<int> newSolution = solution;
                newSolution[i] = k;
                neighbors.push_back(newSolution);
            }
        }
    }

    for (int i = 0; i < num_order - 1; i++)
    {
        for (int j = i + 1; j < num_order; j++)
        {
            vector<int> newSolution = solution;
            swap(newSolution[i], newSolution[j]);
            neighbors.push_back(newSolution);
        }
    }
    return neighbors;
}

void Solution::print(const vector<int>& solution)
{
    /*int sum = 0;
    for (int i = 0; i < numOrders; i++)
    {
        if(solution[i] != -1)
            sum += costs[i];
        cout << solution[i] << " ";
    }
    cout << endl;*/
    int totalCost = 0;
    vector<int> vehicleLoad(num_veh, 0);

    for (int i = 0; i < num_order; ++i) {
        if (solution[i] != -1) {
            vehicleLoad[solution[i]] += quantities[i];
            totalCost += costs[i];
        }
    }

    for (int i = 0; i < num_veh; i++)
    {
        cout << vehicleLoad[i] << " ";
    }
    cout << endl;

    cout << "Cost = " << evaluateSolution(solution) << endl;
}
