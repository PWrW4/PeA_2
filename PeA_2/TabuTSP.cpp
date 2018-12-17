#include "TabuTSP.h"
#include <algorithm>
#include <iostream>


void TabuTSP::tabuSetCityMove(int c1, int c2)
{
	tabuList[c1][c2] += tabuLifeTime;
	tabuList[c2][c1] += tabuLifeTime;
}

void TabuTSP::tabuDecrement()
{
	for (int i = 0; i < G->MatrixSize; ++i)
	{
		for (int j = 0; j < G->MatrixSize; ++j)
		{
			if (tabuList[i][j]>0)
			{
				tabuList[i][j] -= 1;
			}			
		}
	}
}

void TabuTSP::initTabu()
{
	findInitialSolution();
	bestSolutionValue = calcSolutionCost(bestSolution);
	currSolution = bestSolution;

	for (int i = 0; i < G->MatrixSize; ++i)
	{
		for (int j = 0; j < G->MatrixSize; ++j)
		{
			tabuList[i][j] = 0;
		}
	}
}



void TabuTSP::findInitialSolution()
{
	std::vector<bool> cityVisited;
	cityVisited.resize(G->MatrixSize);
	for (bool city_visited : cityVisited)
	{
		city_visited = false;
	}


	int currentVert = 0;
	cityVisited[currentVert] = true;
	for (int i = 0; i < G->MatrixSize; i++)
	{
		int bestVertCost = INT32_MAX;
		int tmpBestVert = -1;
		for (int j = 0; j < G->MatrixSize; j++)
		{
			if (!cityVisited[j])
			{
				if (bestVertCost > G->CityMatrix[currentVert][j])
				{
					tmpBestVert = j;
					bestVertCost = G->CityMatrix[currentVert][j];
				}
			}
		}
		bestSolution[i] = currentVert;
		currentVert = tmpBestVert;
		if (tmpBestVert>-1)
		{
			cityVisited[currentVert] = true;			
		}		
	}

	showSolution();
}

void TabuTSP::showSolution()
{
	std::cout << "Cost of route: "<<calcSolutionCost(bestSolution)<<std::endl;


	for (int i = 0; i < G->MatrixSize; i++)
	{
		if (i==G->MatrixSize-1)
		{
			std::cout << bestSolution[i]<<std::endl;
		}
		else
		{
			std::cout << bestSolution[i] << " -> ";
		}		
	}
}

int TabuTSP::calcSolutionCost(std::vector<int> solutionToCalc)
{
	int cost = 0;

	for (int i = 0; i < G->MatrixSize; ++i)
	{
		if (i == G->MatrixSize - 1)
		{
			cost += G->CityMatrix[solutionToCalc[i]][0];
		}
		else
		{
			cost += G->CityMatrix[solutionToCalc[i]][solutionToCalc[i+1]];
		}
	}

	return cost;
}

void TabuTSP::swap(int i, int k)
{
	int temp = currSolution[i];
	currSolution[i] = currSolution[k];
	currSolution[k] = temp;
}

void TabuTSP::Resolve()
{
	int tmpMaxiterationFromBetterSolution= maxIterationFromBetterSolution;
	while(maxIteration>0 && tmpMaxiterationFromBetterSolution >0) {
		int city1 = 0;
		int city2 = 0;

		for (int j = 0; j < currSolution.size(); j++) {
			for (int k = 0; k < currSolution.size(); k++) {
				if (j != k && tabuList[j][k] == 0) {
					swap(j, k);
					int currCost = calcSolutionCost(currSolution);
					//std::cout << currCost <<std::endl;
					if (currCost < bestSolutionValue /* && tabuList[j][k] == 0*/) {
						city1 = j;
						city2 = k;
						bestSolution = currSolution;
						bestSolutionValue = currCost;
						tmpMaxiterationFromBetterSolution = maxIterationFromBetterSolution;
						goto forbreak;
					}
				}
			}
		}

		forbreak:

		if (city1!= 0)
		{
			tabuDecrement();
			tabuSetCityMove(city1, city2);
		}
		maxIteration--;
		tmpMaxiterationFromBetterSolution--;
	}

	std::cout << maxIteration<<std::endl<< tmpMaxiterationFromBetterSolution <<std::endl;

	showSolution();
}

TabuTSP::TabuTSP(Graph * _G)
{
	G = _G;
	maxIteration = 2000;
	maxIterationFromBetterSolution = maxIteration/4;

	bestSolutionValue = 0;
	tabuLifeTime = 5;

	tabuList.resize(G->MatrixSize);
	bestSolution.resize(G->MatrixSize);
	currSolution.resize(G->MatrixSize);

	tabuList.resize(G->MatrixSize);

	for (int i = 0; i < G->MatrixSize; ++i)
	{
		tabuList[i].resize(G->MatrixSize);
	}

	initTabu();
}


TabuTSP::~TabuTSP()
{
}
