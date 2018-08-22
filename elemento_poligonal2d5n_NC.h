#ifndef ELEMENTO_POLIGONAL2D5N_NC_H
#define ELEMENTO_POLIGONAL2D5N_NC_H

#include "elemento_poligonal2d_NC.h"

/**
@author Fernando Cesar Meira Menandro
*/
class elpol2D5N_NC : public elpol2d_NC
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
	elpol2D5N_NC();
	~elpol2D5N_NC();

	int qnno();
	void funcao_Forma(double, double, double*, double*);
	//int qptg();
	
	//void p_processa(double*);
	//void posprocessa();
};

#endif
