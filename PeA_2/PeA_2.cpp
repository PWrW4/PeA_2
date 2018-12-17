#include "menu.h"
#include <iostream>
#include <ctime>

int main()
{
	//new menu;

	srand(time(NULL));

	Graph* g = new Graph;
	g->LoadGraph("tsp_17.txt");
	g->DrawMatrixSize();
	g->DrawMatrix();

	TabuTSP* Tabu = new TabuTSP(g);
	Tabu->Resolve();
	//Tabu->showSolution();

	//
	int a;
	std::cin >> a;
	//
	//	system("pause");
	return 0;
}
