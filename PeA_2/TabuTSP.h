#pragma once
#include "Graph.h"

class TabuTSP
{
private:
	Graph * G;

	int maxIteration;

	int changePermutation;
	int endThroughRefuse;

	std::vector<std::vector<int>> tabuList;
	int tabuCadency;

	void tabuSetCityMove(int c1, int c2);
	void tabuDecrement();

	std::vector<int> bestSolution;

	std::vector<int> currSolution;
	std::vector<int> firstPermutation;
	std::vector<int> secondPermutation;



	void initTabu();

	void generatePermutation(std::vector<int> & perm);

	void showSolution();

	int calcSolutionCost(std::vector<int> solutionToCalc);

	void swap(std::vector<int> & toSwap, int i, int k);

public:

	void Resolve();

	TabuTSP(Graph * _G);
	~TabuTSP();
};

