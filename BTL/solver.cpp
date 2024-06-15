#include "solver.h"
#include <algorithm>
#include "instance.h"
#include <tuple>

ILOSTLBEGIN
#define pos(u,v) min(u,v)][max(u,v)


Solver::Solver(Instance* instance, string input, string output, double time_limit, double mem_limit)
	:instance(instance), inputFile(input), outputFile(output), time_limit(time_limit), mem_limit(mem_limit) {
	cerr << "-- Solving \n";
	startTime = chrono::high_resolution_clock::now();
	outputFile = instance->instanceName;
	gap = 1e5;
	status = "-";

	/*  SET -------------------------------- */
	n = instance->num_order;
	k = instance->num_veh;
	 
	for (int i = 0; i < n; i++)
	{
		N.push_back(i);
	}

	for (int i = 0; i < k; i++)
	{
		K.push_back(i);
	}
}

Solver::~Solver() {
	//    cerr << "Runtime = " << (double)(clock() - startTime) / CLOCKS_PER_SEC << "s\n";
}

void Solver::Solve() {
	try {
		createModel();

		masterCplex.exportModel("lpex.lp");
		masterCplex.setParam(IloCplex::Param::Parallel, 1);
		masterCplex.setParam(IloCplex::Param::MIP::Tolerances::Integrality, 0);
		masterCplex.setParam(IloCplex::Param::Threads, 16);
		masterCplex.setParam(IloCplex::TiLim, time_limit);
		masterCplex.setParam(IloCplex::TreLim, mem_limit);
		masterCplex.setParam(IloCplex::Param::MIP::Strategy::RINSHeur, 10);

		masterCplex.solve();
		if (masterCplex.getStatus() == IloAlgorithm::Infeasible) {
			cout << UB << endl;
			cout << "Infeasible" << endl;
		}
		else if (masterCplex.getStatus() == IloAlgorithm::Unbounded) {
			cout << "Unbounded" << endl;
		}
		else if (masterCplex.getStatus() == IloAlgorithm::Unknown) {
			cout << "Unknown" << endl;
		}
		else {
			cout << "DONE ..." << endl;
			cout << masterCplex.getObjValue() << endl;
			dispay_solution();
		}


	}
	catch (IloException& e) {
		cerr << "Conver exception caught: " << e << endl;
	}
	catch (...) {
		cerr << "Unknown exception caught" << endl;
	}


	auto endTime = chrono::high_resolution_clock::now();
	runtime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
	runtime = runtime / 1000;


	
	cout << "Environment cleared \n";
	//        workerCplex.end();
	masterCplex.end();

	//        workerEnv.end();
	masterEnv.end();
}

void Solver::createModel() {

	masterModel = IloModel(masterEnv);
	masterCplex = IloCplex(masterEnv);
	

	
	x = NumVar2D(masterEnv, n);
	y = IloNumVarArray(masterEnv, k);
	stringstream name;


	//x_ij
	for (int i : N)
	{
		x[i] = IloNumVarArray(masterEnv, k);
		for (int j : K)
		{
			name << "x." << i << "." << j;
			x[i][j] = IloNumVar(masterEnv, 0, 1, ILOINT, name.str().c_str());
			name.str("");
		}
		
	}

	//y_j
	for (int j : K)
	{
		name << "y." << j;
		y[j] = IloNumVar(masterEnv, 0, 1, ILOINT, name.str().c_str());
		name.str("");
	}

	// OBJ FUNCTION
	
	IloExpr exprSolution(masterEnv);
	for (int i : N)
	{
		for (int j : K)
		{
			exprSolution += x[i][j] * instance->cost[i];
		}
	}
	masterModel.add(IloMaximize(masterEnv, exprSolution));
	//CONSTRAINT

	int BIGM = 10000;
	for (int i : N)
	{
		IloExpr exp(masterEnv);
		for (int j : K)
		{
			exp += x[i][j];
		}
		masterModel.add(exp <= 1);
	}

	for (int j : K)
	{
		IloExpr exp1(masterEnv);
		IloExpr exp2(masterEnv);
		for (int i : N)
		{
			exp1 += x[i][j] * instance->quantity[i];
			exp2 += x[i][j];
		}
		masterModel.add(exp2 >= y[j]);
		masterModel.add(exp2 <= BIGM * y[j]);
		masterModel.add(exp1 >= instance->low_bou[j] * y[j]);
		masterModel.add(exp1 <= instance->up_bou[j] + (1 - y[j]) * BIGM);
	}

	
	masterCplex.extract(masterModel); // <<<< IMPORTANT
	cout << "Done create init MasterProblem\n";
}

void Solver::dispay_solution()
{
	/*int num_com = 0;
	for (int i : N)
	{
		for (int j : K)
		{
			if (masterCplex.getValue(x[i][j]) >= 0.0001)
				num_com++;
		}
	}
	cout << num_com << endl;
	for (int i : N)
	{
		int sum = 0;
		for (int j : K)
		{
			if (masterCplex.getValue(x[i][j]) >= 0.0001)
			{
				cout << i+1 << " " << j+1 << endl;
				sum++;
			}
		}
		if (sum == 0)
			cout << "Order " << i << " is not served" << endl;
	}*/

	vector<int> vehicleLoad(k, 0);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j)
		{
			if (masterCplex.getValue(x[i][j]) >= 0.0001) {
				vehicleLoad[j] += instance->quantity[i];
			}
		}
		
	}

	for (int i = 0; i < k; i++)
	{
		cout << vehicleLoad[i] << " ";
	}
	cout << endl;
}
