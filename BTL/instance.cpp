#include "instance.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <iostream>
#include <math.h>
Instance::Instance(string instanceFile)
{
	vector<string> numbers;
	split(instanceFile, numbers, '/');
	instanceName = numbers[numbers.size() - 1];
	read_input(instanceFile);
	initialize();
}


void Instance::read_input(const string& inputFile)
{
	ifstream myFile(inputFile);
	if (!myFile.is_open())
	{
		// End program immediately
		cout << "Unable to open instance file \n";
		exit(0);
	}

	string line;
	vector<string> numbers;

	getline(myFile, line);
	//cout << line << endl;
	split(line, numbers, ' ');
	
	num_order = stod(numbers[0]);
	num_veh = stod(numbers[1]);

	/*cout << num_order << endl;
	cout << num_veh << endl;*/
	quantity.resize(num_order);
	cost.resize(num_order);
	low_bou.resize(num_veh);
	up_bou.resize(num_veh);

	int sum = 0;

	for (int i = 0; i < num_order; i++)
	{
		getline(myFile, line);
		split(line, numbers, ' ');
		quantity[i] = stod(numbers[0]);
		cost[i] = stod(numbers[1]);
		sum += cost[i];
	}

	cout << " possible cost = " << sum << endl;
	/*for (int i = 0; i < num_order; i++)
	{
		cout << quantity[i] << " ";
	}
	cout << endl;*/

	for (int i = 0; i < num_veh; i++)
	{
		getline(myFile, line);
		split(line, numbers, ' ');
		low_bou[i] = stod(numbers[0]);
		up_bou[i] = stod(numbers[1]);
	}

	/*for (int i = 0; i < num_veh; i++)
	{
		cout << up_bou[i] << " ";
	}
	cout << endl;*/

	//num_scenario = stod(numbers[0]); // fixed tam thoi
	//cout << num_scenario << endl;

	//getline(myFile, line);
	////cout << line << endl;
	//split(line, numbers, ',');
	//sto_sel.resize(numbers.size());
	//cout << numbers.size() << endl;
	//for (int i = 0; i < numbers.size(); i++)
	//{
	//	sto_sel[i] = stod(numbers[i]);
	//}
	//
	//for (int i = 0; i < sto_sel.size(); i++)
	//{
	//	cout << sto_sel[i] << " ";
	//}
	//cout << endl;



	//realization.resize(num_stock);
	//for (int i = 0; i < num_stock; i++)
	//{
	//	realization[i].resize(num_scenario, 0);
	//}

	//for (int i = 0; i < num_scenario; i++)
	//{
	//	getline(myFile, line);
	//	//cout << line << endl;
	//	split(line, numbers, ',');
	//	//cout << numbers.size() << endl;
	//	for (int j = 0; j < numbers.size(); j++)
	//	{
	//		//cout << stod(numbers[j]) << endl;
	//		//realization[j][i] = ceil(stod(numbers[j]) * 100.0)/100.0;
	//		realization[j][i] = stod(numbers[j]);
	//	}
	//}

	////cout << "done1" << endl;
	//out_sample.resize(num_stock, 0);
	//getline(myFile, line);
	//split(line, numbers, ',');
	//for (int i = 0; i < num_stock; i++)
	//{

	//	out_sample[i] = stod(numbers[i]);

	//	//cout << "out_sample[" << i << "] = " << out_sample[i] << endl;
	//	//cout << out_sample[i] << " ";
	//}
	//cout << endl;

	//cout << "done read instance" << endl;
	//
	/////*for (int i = 0; i < num_stock; i++)
	////{*/
	////	for (int j = 0; j < num_scenario; j++)
	////	{
	////		//cout << realization[0][j] << " ";
	////	}
	////	cout << endl;

	//////}

	myFile.close();
}

void Instance::initialize()
{
	
}

template<class Container>
void Instance::split(const std::string& str, Container& cont, char delim)
{
	cont.clear();
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delim)) {
		if (token != "")
			cont.push_back(token);
	}
}