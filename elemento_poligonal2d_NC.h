#ifndef ELEMENTO_POLIGONAL2D_NC_H
#define ELEMENTO_POLIGONAL2D_NC_H

#include "isop2d.h"

class elpol2d_NC : public isop2d
{
private:
	//int nno;  //Numero de nos
	const static int ptg = 66;
public:
#ifdef ALEATORIO
	class aleatorio *yg;
#else
	double *yg;
#endif
	elpol2d_NC();
	elpol2d_NC(int);
	~elpol2d_NC();

	int qptg();
	void pontos_de_gauss(int, double*, double*, double*);
	void monta_rigidez();
	void monta_n();
	virtual void funcao_Forma(double r, double s, double *N, double *dn);
	int tri;
	// Se funcionar, jogar no if de cima
#ifdef ALEATORIO
	void p_processa(aleatorio*);
#else
	void p_processa(double*);
#endif
};

#endif
