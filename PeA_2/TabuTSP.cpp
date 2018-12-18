#include "TabuTSP.h"
#include <algorithm>
#include <iostream>


void TabuTSP::tabuSetCityMove(int c1, int c2)
{
	tabuList[c1][c2] += tabuCadency;
	tabuList[c2][c1] += tabuCadency;
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
	generatePermutation(firstPermutation); // wygenerowanie 1 rozwiązania
	bestSolution = firstPermutation;

	for (int i = 0; i < G->MatrixSize; ++i)
	{
		for (int j = 0; j < G->MatrixSize; ++j)
		{
			tabuList[i][j] = 0;
		}
	}
}



void TabuTSP::generatePermutation(std::vector<int> & perm)
{

	for (int i = 0; i < G->MatrixSize; ++i)
	{
		perm[i] = i;
	}

	std::random_shuffle(perm.begin(), perm.end());
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
			cost += G->CityMatrix[solutionToCalc[i]][solutionToCalc[0]];
		}
		else
		{
			cost += G->CityMatrix[solutionToCalc[i]][solutionToCalc[i+1]];
		}
	}

	return cost;
}

void TabuTSP::Resolve()
{
	int firstCity, secondCity, firstTabu, secondTabu;
	int isEnd = 0; // zmienna sprawdzajaca czy zakonczyc 

	while (isEnd < maxIteration) // iteruje sie dopoki nie jest spelniony warunek zakonczenia(endCondition 60, 120...)
	{
		bool needToChange = false; // czy trzeba zmieniac permutacje
		int mval = 0; // minimalna wartosc odleglosci
		
		secondPermutation = firstPermutation; // przypisanie do 2 permutacji

		for (int i = 0; i < G->MatrixSize - 1; i++) //przeszukiwanie sasiedztwa
		{
			for (int j = i + 1; j < G->MatrixSize; j++) // sprawdzanie wszystkich mozliwosci zamiany
			{
				firstCity = i;
				secondCity = j;
				secondPermutation[firstCity] = firstPermutation[secondCity]; // zamienia miasta 
				secondPermutation[secondCity] = firstPermutation[firstCity];
				int sub = calcSolutionCost(firstPermutation) - calcSolutionCost(secondPermutation); // liczy sie roznice odleglosci
				if (sub > mval) //jezeli znaleziono lepsze mval
				{
					if (tabuList[i][j] == 0 || calcSolutionCost(secondPermutation) < calcSolutionCost(bestSolution) * 0.95)
						//sprawdzenie tabuList oraz kryterium aspiracji,
					{
						mval = sub;
						for (int k = 0; k < G->MatrixSize; k++)
							currSolution[k] = secondPermutation[k]; // przypisujemy 
						firstTabu = firstCity; // wpisanie indeksow miast ktore zamieniamy, zeby dodac do tabu list
						secondTabu = secondCity;
						needToChange = true; // zmiana obecnego rozwiazania, bo znalezlismy lepsze 
					}
				}
				secondPermutation[firstCity] = firstPermutation[firstCity]; // wracamy do poprzedniego stanu
				secondPermutation[secondCity] = firstPermutation[secondCity];
			}
		}

		if (needToChange == true)
			// skoro znalezlismy najlepsze to teraz robimy dla niego, czyli przepisujemy do 1 permutacji curroSolutions(najlepsze rozwiazanie dla petli zamiany miast(sasiedztwa))
		{

			firstPermutation = currSolution; // przepisujemy
			tabuSetCityMove(firstTabu, secondTabu);
			isEnd++; // ziwksza sie bo wykonany ruch
			this->changePermutation = 0;
			// zerujemy bo ona oznacza czy musimy zmienic obecna permutacje, nie trzeba bo znalezlismy juz najlepsze 
		}
		else // jesli nie znalezlismy najlepszej permutacji to generujemy nowa bo tam wyzej nic nie polepszy�o		
		{
			this->generatePermutation(firstPermutation); //ewentualna zmiana permutacji
			this->changePermutation++; // zwiekszamy licznik 
			if (changePermutation > endThroughRefuse)
				//zakonczenie w przypadku nie znalezienia lepszego, tyle razy zmienialismy permutacje a nie znajdujemy rozwiazania, to nie bedzie lepiej
				// i tu badamy czy 10 razy byla zmiana i nie bylo porawy i od razu warunek koncowy i wychodzi
				isEnd = maxIteration;
		}

		if (calcSolutionCost(firstPermutation) < calcSolutionCost(bestSolution))
			//	bada czy obecna badana permutacja jest lepsza od obecnie najlepszej
		{
			bestSolution = firstPermutation; // no i jesli jest to nadpisujemy 
		}

		tabuDecrement(); // zmniejsza kadencje
		std::cout << calcSolutionCost(bestSolution)<<std::endl;
		
	}

	
	showSolution();
}

TabuTSP::TabuTSP(Graph * _G)
{
	G = _G;
	maxIteration = 10000;

	tabuCadency = 2*G->MatrixSize;

	changePermutation = 0;
	endThroughRefuse = 0;

	tabuList.resize(G->MatrixSize);
	bestSolution.resize(G->MatrixSize);
	currSolution.resize(G->MatrixSize);
	firstPermutation.resize(G->MatrixSize);
	secondPermutation.resize(G->MatrixSize);

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
