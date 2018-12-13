/***************************************************************************
*   Copyright (C) 2005 by Fernando Cesar Meira Menandro                   *
*   fcmm@npd.ufes.br                                                      *
*																		  *
*	Created: 12-Dec-18	Renan Lima Thomes, renanlthomes@hotmail.com       *
*	Supervised by:		Fernando Cesar Meira Menandro                     *
*																		  *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

/**************************************************************************
* Elemento Poligonal 2D dividindo o poligono em triangulos				  *
*																		  *
* REF:	THOMES, R.L. Elemento Finito Poligonal: Comparacao dos metodos de *
*		integracao da matriz de rigidez.                                  *
*		TABARRAEI, A.; SUKUMAR, N. Application of Polygonal Finite		  *
*		Elements in Linear Elasticity.									  *
***************************************************************************/

#ifndef ELPOL_TRI_2D_H
#define ELPOL_TRI_2D_H

#include "isop2d.h"

class elpol_tri_2d : public isop2d
{
private:
	const static int ptg = 6; // Numero de pontos de Gauss por sub-divisao
public:
#ifdef ALEATORIO
	class aleatorio *yg;
	void p_processa(aleatorio*);
#else
	double *yg;
	void p_processa(double*);
#endif
	double *rpg, *spg, *wpg;

	elpol_tri_2d();
	elpol_tri_2d(int);
	~elpol_tri_2d();

	int qptg();
	void pontos_de_gauss(int, double*, double*, double*);
	void monta_rigidez();
	void monta_n();
	void map2(double *r, double *s, double *detJ1);
	virtual void funcao_Forma(double r, double s, double *N, double *dn) = 0;
	int tri; // Contador da sub-divisao
};

#endif
