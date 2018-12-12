#ifndef POLIGONAL2D8N_H
#define POLIGONAL2D8N_H

#include "poligonal2d.h"

/**
@author Fernando Cesar Meira Menandro
*/
class pol2D8N : public pol2d
{
private:
	const static int nno = 8;  //Numero de nos
	const static int ptg = 12;
public:
#ifdef ALEATORIO
	class aleatorio *yg;
#else
	double *yg;
#endif
	pol2D8N();
	~pol2D8N();

	int qptg();
	int qnno();
	void funcao_Forma(double, double, double*, double*);
	void pontos_de_gauss(int, double*, double*, double*);
};

#endif
