#pragma once
#include "Graph.h"
#include "TabuTSP.h"


class menu
{
private:
	std::string mainMenuStr = " 1. Wczytaj dane z pliku. \n 2. Wyswietl graf \n 3. Tabu \n 4. none \n 6. Testy!!!";

	Graph * _graph = nullptr;

	double PCFreq = 0.0;
	__int64 CounterStart = 0;

	void StartCounter();
	double GetCounter();

	void mainMenu();

	TabuTSP * Tabu;

public:
	menu();
	~menu();
};
