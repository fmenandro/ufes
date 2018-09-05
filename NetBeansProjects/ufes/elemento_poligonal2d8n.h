#ifndef ELEMENTO_POLIGONAL2D8N_H
#define ELEMENTO_POLIGONAL2D8N_H

#include "elemento_poligonal2d.h"

/**
@author Fernando Cesar Meira Menandro
*/
class elpol2D8N : public elpol2d
{
private:
	const static int nno = 8;  //Numero de nos
public:
#ifdef ALEATORIO
	class aleatorio *yg;
#else
	double *yg;
#endif
	elpol2D8N();
	~elpol2D8N();

	int qnno();
	void funcao_Forma(double, double, double*, double*);
};

#endif
