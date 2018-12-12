#ifndef ELPOL_QUAD_2D8N_H
#define ELPOL_QUAD_2D8N_H

#include "elpol_quad_2d.h"

/**
@author Fernando Cesar Meira Menandro
*/
class elpol_quad_2D8N : public elpol_quad_2d
{
private:
	const static int nno = 8;  //Numero de nos
public:
#ifdef ALEATORIO
	class aleatorio *yg;
#else
	double *yg;
#endif
	elpol_quad_2D8N();
	~elpol_quad_2D8N();

	int qnno();
	void funcao_Forma(double, double, double*, double*);
};

#endif
