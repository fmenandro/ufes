#ifndef POLIGONAL2D5N_H
#define POLIGONAL2D5N_H

#include "poligonal2d.h"

/**
@author Fernando Cesar Meira Menandro
*/
class pol2D5N : public pol2d
{
private:
	const static int nno = 5;  //Numero de nos
	const static int ptg = 11;
	const static int ptg_tot = ptg;
public:
#ifdef ALEATORIO
	class aleatorio *yg;
#else
	double *yg;
#endif
	pol2D5N();
	~pol2D5N();

	int qptg();
	int qnno();
	int qptg_tot();
	void funcao_Forma(double, double, double*, double*);
	void pontos_de_gauss(int, double*, double*, double*);
};

#endif
