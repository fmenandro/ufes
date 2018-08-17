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
#include "elemento_poligonal2d5n.h"

elpol2D5N::elpol2D5N()
: elpol2d(nno)
{
}

elpol2D5N::~elpol2D5N()
{
}

int elpol2D5N::qnno(){
	return nno;
}

void elpol2D5N::funcao_Forma(double r, double s, double *N, double *dn){
	// RENAN
	// Calcula N e dn para os pontos r e s (geralmente, os pontos de Gauss nas coordenadas do elemento)
	// Coeficientes para as fun��es de forma(?)
	// Expressões que se repetem
	double A, B, C, D, E, den, den2;
	A = (0.8090169943749475 + 1.*r);
	B = (-1. + 1.*r - 0.7265425280053609*s);
	C = (2.6180339887498953 + 1.*r + 3.077683537175254*s);
	D = (-1. + 1.*r + 0.7265425280053609*s);
	E = (2.6180339887498953 + 1.*r - 3.077683537175254*s);
	den = (122.60990336999416 - 17.888543819998326*pow(r, 2) - 17.88854381999832*pow(s, 2));
	den2 = pow(122.60990336999416 - 17.888543819998326*pow(r, 2) - 17.88854381999832*pow(s, 2), 2);
	// Funcao de forma
	N[0] = (-11.577708763999665*A*B*C) / den;
	N[1] = (9.366563145999496*B*D*C) / den;
	N[2] = (9.366563145999496*E*B*D) / den;
	N[3] = (-11.577708763999665*A*E*D) / den;
	N[4] = (4.422291236000336*A*E*C) / den;
	// Derivada em relação a r
	dn[0] = (-414.2167011199733*r*A*B*C) / den2 - (11.577708763999665*A*B) / den - (11.577708763999665*A*C) / den - (11.577708763999665*B*C) / den;
	dn[2] = (335.1083505599867*r*B*D*C) / den2 + (9.366563145999496*B*D) / den + (9.366563145999496*B*C) / den + (9.366563145999496*D*C) / den;
	dn[4] = (335.1083505599867*r*E*B*D) / den2 + (9.366563145999496*E*B) / den + (9.366563145999496*E*D) / den + (9.366563145999496*B*D) / den;
	dn[6] = (-414.2167011199733*r*A*E*D) / den2 - (11.577708763999665*A*E) / den - (11.577708763999665*A*D) / den - (11.577708763999665*E*D) / den;
	dn[8] = (158.21670111997315*r*A*E*C) / den2 + (4.422291236000336*A*E) / den + (4.422291236000336*A*C) / den + (4.422291236000336*E*C) / den;
	// Derivada em relação a s
	dn[1] = (-414.21670111997315*A*B*s*C) / den2 - (35.632523661171426*A*B) / den + (8.41169779390614*A*C) / den;
	dn[3] = (335.1083505599866*B*D*s*C) / den2 + (28.827317194355103*B*D) / den + (6.80520646681632*B*C) / den - (6.80520646681632*D*C) / den;
	dn[5] = (335.1083505599866*E*B*D*s) / den2 + (6.80520646681632*E*B) / den - (6.80520646681632*E*D) / den - (28.827317194355103*B*D) / den;
	dn[7] = (-414.21670111997315*A*E*D*s) / den2 - (8.41169779390614*A*E) / den + (35.632523661171426*A*D) / den;
	dn[9] = (158.21670111997307*A*E*s*C) / den2 + (13.61041293363264*A*E) / den - (13.61041293363264*A*C) / den;
}