#include "menu.h"
#include <iostream>

int main()
{
	//new menu;

		Graph * g = new Graph;
		g->LoadGraph("tsp_10.txt");
		g->DrawMatrixSize();
		g->DrawMatrix();
	
		TabuTSP * Tabu = new TabuTSP(g);
		Tabu->Resolve();
		//Tabu->showSolution();

	//
		int a;
		std::cin >> a;
	//
	//	system("pause");
	return 0;
}
