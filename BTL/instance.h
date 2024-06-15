
#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>


using namespace std;


class Instance {
public:
    string instanceName;

    int num_order;
    int num_veh;
    vector<int> quantity;
    vector<int> cost;
    vector<int> low_bou;
    vector<int> up_bou;
    Instance(string inputFile);
    
    void read_input(const string& inputFile);
    void initialize();
    template <class Container>
    void split(const std::string& str, Container& cont, char delim);
};

#endif

