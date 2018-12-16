#include "TabuTSP.h"
#include <algorithm>
#include <iostream>


void TabuTSP::initTabu()
{
	findInitialSolution();
	showSolution();
}

void TabuTSP::resolveTabu()
{
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
		solution[i] = currentVert;
		currentVert = tmpBestVert;
		if (tmpBestVert>-1)
		{
			cityVisited[currentVert] = true;			
		}		
	}
}

void TabuTSP::showSolution()
{
	for (int i = 0; i < G->MatrixSize; i++)
	{
		if (i==G->MatrixSize-1)
		{
			std::cout << solution[i];
		}
		else
		{
			std::cout << solution[i] << " -> ";
		}		
	}
}

void TabuTSP::Resolve()
{
	initTabu();
	resolveTabu();


}

TabuTSP::TabuTSP(Graph * _G)
{
	G = _G;
	maxIteration = 1000;
	maxIterationFromBetterSolution = 200;

	tabuList.resize(G->MatrixSize);
	solution.resize(G->MatrixSize);
}


TabuTSP::~TabuTSP()
{
}
