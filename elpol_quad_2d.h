#ifndef ELPOL_QUAD_2D_H
#define ELPOL_QUAD_2D_H

#include "isop2d.h"

class elpol_quad_2d : public isop2d
{
private:
	const static int ptg = 4; // Numero de pontos de Gauss TOTAL em cada sub-quadrado!
public:
#ifdef ALEATORIO
	class aleatorio *yg;
	void p_processa(aleatorio*);
#else
	double *yg;
	void p_processa(double*);
#endif
	double *xpg, *wpg;

	elpol_quad_2d();
	elpol_quad_2d(int);
	~elpol_quad_2d();

	int qptg();
	void monta_rigidez();
	void monta_n();
	virtual void funcao_Forma(double r, double s, double *N, double *dn) = 0;
	int tri;
};

#endif
