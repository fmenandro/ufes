#ifndef POLIGONAL2D_H
#define POLIGONAL2D_H

#include "isop2d.h"

class pol2d : public isop2d
{
private:
	//const static int ptg = 25;
public:
#ifdef ALEATORIO
	class aleatorio *yg;
	void p_processa(aleatorio*);
#else
	double *yg;
	void p_processa(double*);
#endif
	double *rpg, *spg, *wpg;

	pol2d();
	pol2d(int, int, int);
	~pol2d();

	virtual int qptg() = 0;
	virtual int qptg_tot() = 0; // Adicionado por Renan
	virtual void pontos_de_gauss(int, double*, double*, double*);
	void monta_rigidez();
	void monta_n();
	virtual void funcao_Forma(double r, double s, double *N, double *dn) = 0;
};

#endif
