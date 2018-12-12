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
: elpol2d(nno, ptg, ptg_tot)
{
}

elpol2D6N::~elpol2D6N()
{
}

int elpol2D6N::qptg(){
	return ptg;
}

int elpol2D6N::qnno(){
	return nno;
}

int elpol2D6N::qptg_tot() {
	return ptg_tot;
}

void elpol2D6N::pontos_de_gauss(const int p, double *r, double *s, double *w) {
	// Pontos de Gauss-Legendre encontrados para o hexagono
	switch (p){
	case 4: // polinomio ordem 3
		r[0] = 0.6106677068269424;
		r[1] = -0.2091688755656304;
		r[2] = -0.6106677068269424;
		r[3] = 0.2091688755656305;
		s[0] = 0.2091688755656305;
		s[1] = 0.6106677068269424;
		s[2] = -0.2091688755656305;
		s[3] = -0.6106677068269424;
		w[0] = 0.6495190528383290;
		w[1] = 0.6495190528383290;
		w[2] = 0.6495190528383290;
		w[3] = 0.6495190528383290;
		break;
	case 7: // polinomio ordem 5
		r[0] = 0.7079532902957145;
		r[1] = 0.1439728259692422;
		r[2] = -0.5639804643264723;
		r[3] = -0.7079532902957146;
		r[4] = -0.1439728259692427;
		r[5] = 0.5639804643264719;
		r[6] = 0.0000000000000004;
		s[0] = 0.2424915230672458;
		s[1] = 0.7343512956224910;
		s[2] = 0.4918597725552452;
		s[3] = -0.2424915230672456;
		s[4] = -0.7343512956224910;
		s[5] = -0.4918597725552458;
		s[6] = 0.0000000000000001;
		w[0] = 0.3221820698602816;
		w[1] = 0.3221820698602816;
		w[2] = 0.3221820698602816;
		w[3] = 0.3221820698602816;
		w[4] = 0.3221820698602816;
		w[5] = 0.3221820698602816;
		w[6] = 0.6649837921916265;
		break;
	case 12: // ordem 6
		r[0] = -0.4094814038031204;
		r[1] = 0.4094814038031203;
		r[2] = -0.3801045140866995;
		r[3] = 0.3801045140866995;
		r[4] = 0.8196160033371955;
		r[5] = -0.8196160033371955;
		r[6] = 0.2594641967049848;
		r[7] = -0.2594641967049847;
		r[8] = 0.6735354443182219;
		r[9] = -0.6735354443182219;
		r[10] = 0.1159195765752143;
		r[11] = -0.1159195765752143;
		s[0] = 0.6887771339497573;
		s[1] = -0.6887771339497573;
		s[2] = 0.1010186727501912;
		s[3] = -0.1010186727501914;
		s[4] = -0.1505686044388519;
		s[5] = 0.1505686044388518;
		s[6] = 0.8176892799135412;
		s[7] = -0.8176892799135412;
		s[8] = 0.4130808270570917;
		s[9] = -0.4130808270570917;
		s[10] = 0.4466913045093554;
		s[11] = -0.4466913045093554;
		w[0] = 0.2012029710839800;
		w[1] = 0.2012029710839800;
		w[2] = 0.3518846833868571;
		w[3] = 0.3518846833868571;
		w[4] = 0.1439068169671399;
		w[5] = 0.1439068169671399;
		w[6] = 0.1132725695144904;
		w[7] = 0.1132725695144904;
		w[8] = 0.1708044964976501;
		w[9] = 0.1708044964976501;
		w[10] = 0.3179665682265404;
		w[11] = 0.3179665682265404;
		break;
	case 15:
		r[0] = 0.2433678800209670;
		r[1] = -0.3638627911369946;
		r[2] = 0.1204949111160271;
		r[3] = 0.6815511544379341;
		r[4] = -0.1919704096443466;
		r[5] = -0.4895807447935853;
		r[6] = 1.0439220088499217;
		r[7] = -0.3932121491786226;
		r[8] = -0.6507098596713032;
		r[9] = 0.7376908434658901;
		r[10] = -0.6420307742629977;
		r[11] = -0.0956600692028959;
		r[12] = 0.3729917195782382;
		r[13] = -0.8321590642932697;
		r[14] = 0.4591673447150312;
		s[0] = 0.2796440497798506;
		s[1] = 0.0709407416733938;
		s[2] = -0.3505847914532461;
		s[3] = -0.1718254071120293;
		s[4] = 0.6761533172778766;
		s[5] = -0.5043279101658500;
		s[6] = -0.1486663724686596;
		s[7] = 0.9783961654680452;
		s[8] = -0.8297297929993829;
		s[9] = 0.3154472736437755;
		s[10] = 0.4811353737587404;
		s[11] = -0.7965826474025182;
		s[12] = 0.7455476498526157;
		s[13] = -0.0497535203703157;
		s[14] = -0.6957941294823040;
		w[0] = 0.3444822273297101;
		w[1] = 0.3444822273297101;
		w[2] = 0.3444822273297101;
		w[3] = 0.2327014949571080;
		w[4] = 0.2327014949571080;
		w[5] = 0.2327014949571080;
		w[6] = 0.0113025480286300;
		w[7] = 0.0113025480286300;
		w[8] = 0.0113025480286300;
		w[9] = 0.1347295079783832;
		w[10] = 0.1347295079783832;
		w[11] = 0.1347295079783832;
		w[12] = 0.1428096254906091;
		w[13] = 0.1428096254906091;
		w[14] = 0.1428096254906091;
		break;
	}
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