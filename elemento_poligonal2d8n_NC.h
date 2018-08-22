#ifndef ELEMENTO_POLIGONAL2D8N_NC_H
#define ELEMENTO_POLIGONAL2D8N_NC_H

#include "elemento_poligonal2d_NC.h"

/**
@author Fernando Cesar Meira Menandro
*/
class elpol2D8N_NC : public elpol2d_NC
{
private:
	const static int nno = 8;  //Numero de nos
public:
#ifdef ALEATORIO
	class aleatorio *yg;
#else
	double *yg;
#endif
	elpol2D8N_NC();
	~elpol2D8N_NC();

	int qnno();
	void funcao_Forma(double, double, double*, double*);
};

#endif
