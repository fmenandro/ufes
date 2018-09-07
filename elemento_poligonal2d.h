#ifndef ELEMENTO_POLIGONAL2D_H
#define ELEMENTO_POLIGONAL2D_H

#include "isop2d.h"

class elpol2d : public isop2d
{
private:
	const static int ptg = 4;
	double r_pol, s_pol; // pontos de Gauss nas coordenadas do elemento de referencia
public:
#ifdef ALEATORIO
	class aleatorio *yg;
	void p_processa(aleatorio*);
#else
	double *yg;
	void p_processa(double*);
#endif
	double *rpg, *spg, *wpg;

	elpol2d();
	elpol2d(int);
	~elpol2d();

	int qptg();
	void pontos_de_gauss(int, double*, double*, double*);
	void monta_rigidez();
	void monta_n();
	virtual void funcao_Forma(double r, double s, double *N, double *dn) = 0;
	int tri;
};

#endif
