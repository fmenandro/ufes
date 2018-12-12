#ifndef ELPOL_QUAD_2D5N_H
#define ELPOL_QUAD_2D5N_H

#include "elpol_quad_2d.h"

/**
@author Fernando Cesar Meira Menandro
*/
class elpol_quad_2D5N : public elpol_quad_2d
{
private:
	const static int nno = 5;  //Numero de nos
	//const static int ptg = 3;  //Numero de Pontos de Gauss nas diferentes direcoes
public:
    #ifdef ALEATORIO
   class aleatorio *yg;
#else
   double *yg;
#endif
	elpol_quad_2D5N();
	~elpol_quad_2D5N();

	int qnno();
	void funcao_Forma(double, double, double*, double*);
};

#endif
