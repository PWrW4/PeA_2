#pragma once
#include "Graph.h"

class TabuTSP
{
private:
	Graph * G;

	int maxIteration;
	int maxIterationFromBetterSolution;

	std::vector<std::vector<int>> tabuList;
	int tabuLifeTime;

	void tabuSetCityMove(int c1, int c2);
	void tabuDecrement();

	std::vector<int> bestSolution;
	int bestSolutionValue;

	std::vector<int> currSolution;



	void initTabu();

	void findInitialSolution();

	void showSolution();

	int calcSolutionCost(std::vector<int> solutionToCalc);

	void swap(int i, int k);

public:

	void Resolve();

	TabuTSP(Graph * _G);
	~TabuTSP();
};

