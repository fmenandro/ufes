#ifndef ELEMENTO_POLIGONAL2D_H
#define ELEMENTO_POLIGONAL2D_H

#include "isop2d.h"

class elpol2d : public isop2d
{
private:
	const static int ptg = 25;
public:
#ifdef ALEATORIO
	class aleatorio *yg;
	void p_processa(aleatorio*);
#else
	double *yg;
	void p_processa(double*);
#endif
	elpol2d();
	elpol2d(int);
	~elpol2d();

	int qptg();
	void pontos_de_gauss(int, double*, double*, double*);
	void monta_rigidez();
	void monta_n();
	virtual void funcao_Forma(double r, double s, double *N, double *dn);
	int tri;
};

#endif
