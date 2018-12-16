#pragma once
#include "Graph.h"

class TabuTSP
{
private:
	Graph * G;

	int maxIteration;
	int maxIterationFromBetterSolution;

	std::vector<int> tabuList;

	std::vector<int> solution;

	void initTabu();

	void resolveTabu();

	void findInitialSolution();

	void showSolution();

public:

	void Resolve();

	TabuTSP(Graph * _G);
	~TabuTSP();
};

