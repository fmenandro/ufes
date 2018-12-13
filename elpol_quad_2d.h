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

#ifndef ELPOL_QUAD_2D_H
#define ELPOL_QUAD_2D_H

#include "isop2d.h"

class elpol_quad_2d : public isop2d
{
private:
	// Numero de pontos de Gauss TOTAL em cada sub-quadrado!
	// Ou seja, se temos 3 pontos por direção e 2 direções, então ptg = 3^2
	const static int ptg = 4; 
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
	void elpol_quad_2d::map2(double *r, double *s, double *detJ1);
	virtual void funcao_Forma(double r, double s, double *N, double *dn) = 0;
	int tri; // Contador da sub-divisao
};

#endif
