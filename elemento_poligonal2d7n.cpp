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
#include "elemento_poligonal2d7n.h"

elpol2D7N::elpol2D7N()
: elpol2d(nno)
{
}

elpol2D7N::~elpol2D7N()
{
}

int elpol2D7N::qnno(){
	return nno;
}

void elpol2D7N::funcao_Forma(double r, double s, double *N, double *dn){
	// RENAN
	// CALCULO DAS FUNCOES DE FORMA (N) E SUAS DERIVADAS (dn)
	double b, b2, dbdr, dbds, A, B, C, D, E, F, G;
	// Expressoes que se repetem	
	A = (0.9009688679024191 + 1.*r);
	B = (-4.048917339522304 + 1.*r - 4.381286267534823*s);
	C = (1.445041867912629 + 1.*r - 1.253960337662704*s);
	D = (-1. + 1.*r - 0.4815746188075287*s);
	E = (1.445041867912629 + 1.*r + 1.253960337662704*s);
	F = (-1. + 1.*r + 0.4815746188075287*s);
	G = (-4.048917339522304 + 1.*r + 4.381286267534823*s);
	b = (1412.7983817039994 + 41.27066882957638*pow(r, 4) + pow(s, 2)*(-762.7594506989002 + 41.27066882957639*pow(s, 2)) + 
		pow(r, 2)*(-762.7594506988999 + 82.54133765915262*pow(s, 2)));
	b2 = pow(b, 2);
	dbdr = (165.08267531830552*pow(r, 3) + 2 * r*(-762.7594506988999 + 82.54133765915262*pow(s, 2)));
	dbds = (165.08267531830523*pow(r, 2)*s + 82.54133765915277*pow(s, 3) + 2 * s*(-762.7594506989002 + 41.27066882957639*pow(s, 2)));
	// Funcoes de Forma
	N[0] = (26.495528883381816*A*B*C*D*E) / b;
	N[1] = (-38.28714854897507*A*B*D*F*E) / b;
	N[2] = (8.519692053642082*B*D*F*E*G) / b;
	N[3] = (8.519692053642082*B*C*D*F*G) / b;
	N[4] = (-38.28714854897507*A*C*D*F*G) / b;
	N[5] = (26.495528883381816*A*C*F*E*G) / b;
	N[6] = (6.543855223902344*A*B*C*E*G) / b;
	// Derivadas em relacao a r 
	dn[0] = (-26.495528883381816*A*B*C*D*E*dbdr) / b2 + (26.495528883381816*A*B*C*D) / b + (26.495528883381816*A*B*C*E) / b + (26.495528883381816*A*B*D*E) / b + (26.495528883381816*A*C*D*E) / b + (26.495528883381816*B*C*D*E) / b;
	dn[2] = (38.28714854897507*A*B*D*F*E*dbdr) / b2 - (38.28714854897507*A*B*D*F) / b - (38.28714854897507*A*B*D*E) / b - (38.28714854897507*A*B*F*E) / b - (38.28714854897507*A*D*F*E) / b - (38.28714854897507*B*D*F*E) / b;
	dn[4] = (-8.519692053642082*B*D*F*E*G*dbdr) / b2 + (8.519692053642082*B*D*F*E) / b + (8.519692053642082*B*D*F*G) / b + (8.519692053642082*B*D*E*G) / b + (8.519692053642082*B*F*E*G) / b + (8.519692053642082*D*F*E*G) / b;
	dn[6] = (-8.519692053642082*B*C*D*F*G*dbdr) / b2 + (8.519692053642082*B*C*D*F) / b + (8.519692053642082*B*C*D*G) / b + (8.519692053642082*B*C*F*G) / b + (8.519692053642082*B*D*F*G) / b + (8.519692053642082*C*D*F*G) / b;
	dn[8] = (38.28714854897507*A*C*D*F*G*dbdr) / b2 - (38.28714854897507*A*C*D*F) / b - (38.28714854897507*A*C*D*G) / b - (38.28714854897507*A*C*F*G) / b - (38.28714854897507*A*D*F*G) / b - (38.28714854897507*C*D*F*G) / b;
	dn[10] = (-26.495528883381816*A*C*F*E*G*dbdr) / b2 + (26.495528883381816*A*C*F*E) / b + (26.495528883381816*A*C*F*G) / b + (26.495528883381816*A*C*E*G) / b + (26.495528883381816*A*F*E*G) / b + (26.495528883381816*C*F*E*G) / b;
	dn[12] = (-6.543855223902344*A*B*C*E*G*dbdr) / b2 + (6.543855223902344*A*B*C*E) / b + (6.543855223902344*A*B*C*G) / b + (6.543855223902344*A*B*E*G) / b + (6.543855223902344*A*C*E*G) / b + (6.543855223902344*B*C*E*G) / b;
	// Derivadas em relacao a s
	dn[1] = (-26.495528883381816*A*B* C*D*E* dbds) / b2 + (33.22434234515739*A*B* C*D) / b - (12.759574222118465*A*B* C*E) / b - (33.22434234515739*A*B*D* E) / b - (116.08449684783301*A*C*D* E) / b;
	dn[3] = (38.28714854897507*A*B*D* F*E* dbds) / b2 - (48.010565722614885*A*B*D* F) / b - (18.438118967699896*A*B*D* E) / b + (18.438118967699896*A*B*F* E) / b + (167.7469581606903*A*D*F* E) / b;
	dn[5] = (-8.519692053642082*B*D*F* E*G* dbds) / b2 + (37.32720979824761*B*D*F* E) / b + (10.68335592436728*B*D*F* G) / b + (4.102867453090217*B*D* E*G) / b - (4.102867453090217*B*F* E*G) / b - (37.32720979824761*D*F*E* G) / b;
	dn[7] = (-8.519692053642082*B*C* D*F*G* dbds) / b2 + (37.32720979824761*B*C* D*F) / b + (4.102867453090217*B*C* D*G) / b - (4.102867453090217*B*C* F*G) / b - (10.68335592436728*B*D*F* G) / b - (37.32720979824761*C*D*F* G) / b;
	dn[9] = (38.28714854897507*A*C*D* F*G* dbds) / b2 - (167.7469581606903*A*C*D* F) / b - (18.438118967699896*A*C*D* G) / b + (18.438118967699896*A*C*F* G) / b + (48.010565722614885*A*D*F* G) / b;
	dn[11] = (-26.495528883381816*A*C*F* E*G* dbds) / b2 + (116.08449684783301*A*C*F* E) / b + (33.22434234515739*A*C*F* G) / b + (12.759574222118465*A*C* E*G) / b - (33.22434234515739*A*F*E* G) / b;
	dn[13] = (-6.543855223902344*A*B* C*E* G*dbds) / b2 + (28.670503029219354*A*B* C*E) / b + (8.205734906180433*A*B* C*G) / b - (8.205734906180433*A*B* E*G) / b - (28.670503029219354*A*C* E*G) / b;
}