#ifndef ELEMENTO_POLIGONAL2D_H
#define ELEMENTO_POLIGONAL2D_H

#include "isop2d.h"

class elpol2d : public isop2d
{
private:
	//int nno;  //Numero de nos
	const static int ptg = 25;  //Numero de Pontos de Gauss nas diferentes direcoes
public:
#ifdef ALEATORIO
	class aleatorio *yg;
#else
	double *yg;
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
// Se funcionar, jogar no if de cima
#ifdef ALEATORIO
	void p_processa(aleatorio*);
#else
	void p_processa(double*);
#endif
};

#endif
