/***************************************************************************
*   Copyright (C) 2005 by Fernando C�sar Meira Menandro   *
*   menandro@localhost.localdomain   *
*                                                                         *
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
#include "elemento_poligonal2d6n.h"

elpol2D6N::elpol2D6N()
: elpol2d(nno)
{
}

elpol2D6N::~elpol2D6N()
{
}

int elpol2D6N::qnno(){
	return nno;
}

void elpol2D6N::funcao_Forma(double r, double s, double *N, double *dn){
	// RENAN
	// CALCULO DAS FUNCOES DE FORMA (N) E SUAS DERIVADAS (dn)
	// A. TABARRAEI and N. SUKUMAR, Application of polygonal finite elements in linear elasticity
	double raiz3 = sqrt(3);
	double A, B, C, D, E, F, G, H, I, c, e, den;
	// Expres~soes que se repetem
	A = (raiz3*r - s - raiz3);
	B = (2 * s + raiz3);
	C = (3 * pow(r, 2) + 6 * r - pow(s, 2) + 3);
	D = (raiz3*r + s + raiz3);
	E = (3 * pow(r, 2) - 6 * r - pow(s, 2) + 3);
	F = (4 * pow(s, 2) - 3);
	G = (raiz3*r - s + raiz3);
	H = (raiz3 - 2 * s);
	I = (raiz3*r + s - raiz3);
	c = (6 + 6 * r);
	e = (-6 + 6 * r);
	// Denominador e numerador de N, respectivamente
	den = 18 * (pow(r, 2) + pow(s, 2) - 3);
	double num[] = {A * B * C, -D * B * E, E * F, -G * H * E, I * H * C, C * F };
	// Derivadas do denominador e numerador de N, respectivamente
	double dden[] = { 36 * r, 36 * s };
	double dnum_dr[] = { c*A*B + raiz3*B*C, -(e*D*B) - raiz3*B*E, e*F,
		-(e*H*G) - raiz3*H*E, c*H*I + raiz3*H*C, c*F };
	double dnum_ds[] = { -2 * A*s*B + 2 * A*C - B*C, 2 * s*D*B - 2 * D*E - B*E, 8 * s*E - 2 * s*F,
		2 * H*G*s + H*E + 2 * G*E, -2 * H*s*I + H*C - 2 * I*C, 8 * s*C - 2 * s*F };

	// Calculo N e dn
	int j = 0;
	for (int i = 0; i < nno; i++){
		N[i] = num[i] / den;
		dn[j] = (den * dnum_dr[i] - num[i] * dden[0]) / pow(den, 2);	// Derivada de N em relacao a r
		dn[j + 1] = (den * dnum_ds[i] - num[i] * dden[1]) / pow(den, 2);	// Derivada de N em relacao a s

		j = j + 2;
	}
}
