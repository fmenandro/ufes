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
#include "elemento_poligonal2d.h"

elpol2d::elpol2d(int nno, int ptg, int ptg_tot)
: isop2d(nno, ptg, ptg_tot, 1)
{
	rpg = new double[ptg];
	spg = new double[ptg];
	wpg = new double[ptg];
}

elpol2d::~elpol2d()
{
}

void elpol2d::pontos_de_gauss(const int p, double *r, double *s, double *w) {
	switch (p){
	case 1:
		r[0] = 1.0 / 3;
		s[0] = 1.0 / 3;
		w[0] = 0.5;
		break;
	case 3:
		r[0] = 1.0 / 6;
		s[0] = 1.0 / 6;
		r[1] = 2.0 / 3;
		s[1] = 1.0 / 6;
		r[2] = 1.0 / 6;
		s[2] = 2.0 / 3;
		w[0] = 1.0 / 6;
		w[1] = 1.0 / 6;
		w[2] = 1.0 / 6;
		break;
	/*case 3:
		r[0] = 0;
		s[0] = 1.0 / 2;
		r[1] = 1.0 / 2;
		s[1] = 0;
		r[2] = 1.0 / 2;
		s[2] = 1.0 / 2;
		w[0] = 1.0 / 6;
		w[1] = 1.0 / 6;
		w[2] = 1.0 / 6;
		break;*/
	case 4:
		r[0] = 1.0 / 3;
		s[0] = 1.0 / 3;
		r[1] = 1.0 / 5;
		s[1] = 1.0 / 5;
		r[2] = 1.0 / 5;
		s[2] = 3.0 / 5;
		r[3] = 3.0 / 5;
		s[3] = 1.0 / 5;
		w[0] = -27.0 / 96;
		w[1] = 25.0 / 96;
		w[2] = 25.0 / 96;
		w[3] = 25.0 / 96;
		break;
	/*case 4:
		r[0] = 1.0 / 3;
		s[0] = 1.0 / 3;
		r[1] = 2.0 / 15;
		s[1] = 11. / 15;
		r[2] = 2.0 / 15;
		s[2] = 2.0 / 15;
		r[3] = 11. / 15;
		s[3] = 2.0 / 15;
		w[0] = -27.0 / 96;
		w[1] = 25.0 / 96;
		w[2] = 25.0 / 96;
		w[3] = 25.0 / 96;
		break;*/
	case 5:
		r[0] = 0.0000000000014824;
		r[1] = 0.2351484020246200;
		r[2] = 0.1924603527038700;
		r[3] = 0.7978532790397950;
		r[4] = 0.6473475534216230;
		s[0] = 0.7978532790397950;
		s[1] = 0.6473475534216230;
		s[2] = 0.1924603526784430;
		s[3] = 0.0000000000014824;
		s[4] = 0.2351484020246200;
		w[0] = 0.0342602422445202;
		w[1] = 0.1122768273544550;
		w[2] = 0.2073746278616690;
		w[3] = 0.0342602422445202;
		w[4] = 0.1122768273544550;
		break;
	case 6:
		r[0] = 0.4459484909159650;
		r[1] = 0.4459484909159650;
		r[2] = 0.1081030181680700;
		r[3] = 0.0915762135097710;
		r[4] = 0.0915762135097710;
		r[5] = 0.8168475729804590;
		s[0] = 0.4459484909159650;
		s[1] = 0.1081030181680700;
		s[2] = 0.4459484909159650;
		s[3] = 0.0915762135097710;
		s[4] = 0.8168475729804590;
		s[5] = 0.0915762135097710;
		w[0] = 0.1116907948390055;
		w[1] = 0.1116907948390055;
		w[2] = 0.1116907948390055;
		w[3] = 0.0549758718276610;
		w[4] = 0.0549758718276610;
		w[5] = 0.0549758718276610;
		break;
	case 7:
		r[0] = 0.3333333333333330;
		r[1] = 0.4701420641051150;
		r[2] = 0.4701420641051150;
		r[3] = 0.0597158717897700;
		r[4] = 0.1012865073234560;
		r[5] = 0.1012865073234560;
		r[6] = 0.7974269853530870;
		s[0] = 0.3333333333333330;
		s[1] = 0.4701420641051150;
		s[2] = 0.0597158717897700;
		s[3] = 0.4701420641051150;
		s[4] = 0.1012865073234560;
		s[5] = 0.7974269853530870;
		s[6] = 0.1012865073234560;
		w[0] = 0.1125000000000000;
		w[1] = 0.0661970763942530;
		w[2] = 0.0661970763942530;
		w[3] = 0.0661970763942530;
		w[4] = 0.0629695902724135;
		w[5] = 0.0629695902724135;
		w[6] = 0.0629695902724135;
		break;
	case 12:
		r[0] = 0.2492867451709100;
		r[1] = 0.2492867451709100;
		r[2] = 0.5014265096581790;
		r[3] = 0.0630890144915020;
		r[4] = 0.0630890144915020;
		r[5] = 0.8738219710169960;
		r[6] = 0.6365024991213990;
		r[7] = 0.6365024991213990;
		r[8] = 0.3103524510337840;
		r[9] = 0.3103524510337840;
		r[10] = 0.0531450498448170;
		r[11] = 0.0531450498448170;
		s[0] = 0.2492867451709100;
		s[1] = 0.5014265096581790;
		s[2] = 0.2492867451709100;
		s[3] = 0.0630890144915020;
		s[4] = 0.8738219710169960;
		s[5] = 0.0630890144915020;
		s[6] = 0.3103524510337840;
		s[7] = 0.0531450498448170;
		s[8] = 0.6365024991213990;
		s[9] = 0.0531450498448170;
		s[10] = 0.6365024991213990;
		s[11] = 0.3103524510337840;
		w[0] = 0.0583931378631895;
		w[1] = 0.0583931378631895;
		w[2] = 0.0583931378631895;
		w[3] = 0.0254224531851035;
		w[4] = 0.0254224531851035;
		w[5] = 0.0254224531851035;
		w[6] = 0.0414255378091870;
		w[7] = 0.0414255378091870;
		w[8] = 0.0414255378091870;
		w[9] = 0.0414255378091870;
		w[10] = 0.0414255378091870;
		w[11] = 0.0414255378091870;
		break;
	case 16:
		r[0] = 0.333333333;
		r[1] = 0.459292588;
		r[2] = 0.459292588;
		r[3] = 0.081414823;
		r[4] = 0.170569308;
		r[5] = 0.170569308;
		r[6] = 0.658861384;
		r[7] = 0.050547228;
		r[8] = 0.050547228;
		r[9] = 0.898905543;
		r[10] = 0.26311283;
		r[11] = 0.728492393;
		r[12] = 0.008394777;
		r[13] = 0.728492393;
		r[14] = 0.26311283;
		r[15] = 0.008394777;
		s[0] = 0.333333333;
		s[1] = 0.459292588;
		s[2] = 0.081414823;
		s[3] = 0.459292588;
		s[4] = 0.170569308;
		s[5] = 0.658861384;
		s[6] = 0.170569308;
		s[7] = 0.050547228;
		s[8] = 0.898905543;
		s[9] = 0.050547228;
		s[10] = 0.728492393;
		s[11] = 0.008394777;
		s[12] = 0.26311283;
		s[13] = 0.26311283;
		s[14] = 0.008394777;
		s[15] = 0.728492393;
		w[0] = 0.144315608 / 2;
		w[1] = 0.095091634 / 2;
		w[2] = 0.095091634 / 2;
		w[3] = 0.095091634 / 2;
		w[4] = 0.103217371 / 2;
		w[5] = 0.103217371 / 2;
		w[6] = 0.103217371 / 2;
		w[7] = 0.032458498 / 2;
		w[8] = 0.032458498 / 2;
		w[9] = 0.032458498 / 2;
		w[10] = 0.027230314 / 2;
		w[11] = 0.027230314 / 2;
		w[12] = 0.027230314 / 2;
		w[13] = 0.027230314 / 2;
		w[14] = 0.027230314 / 2;
		w[15] = 0.027230314 / 2;
		break;
	case 25:
		r[0] = 0.333333333;
		r[1] = 0.485577633;
		r[2] = 0.485577633;
		r[3] = 0.028844733;
		r[4] = 0.109481575;
		r[5] = 0.109481575;
		r[6] = 0.781036849;
		r[7] = 0.550352942;
		r[8] = 0.550352942;
		r[9] = 0.307939839;
		r[10] = 0.307939839;
		r[11] = 0.141707219;
		r[12] = 0.141707219;
		r[13] = 0.728323905;
		r[14] = 0.728323905;
		r[15] = 0.246672561;
		r[16] = 0.246672561;
		r[17] = 0.025003535;
		r[18] = 0.025003535;
		r[19] = 0.923655934;
		r[20] = 0.923655934;
		r[21] = 0.066803251;
		r[22] = 0.066803251;
		r[23] = 0.009540815;
		r[24] = 0.009540815;
		s[0] = 0.333333333;
		s[1] = 0.485577633;
		s[2] = 0.028844733;
		s[3] = 0.485577633;
		s[4] = 0.109481575;
		s[5] = 0.781036849;
		s[6] = 0.109481575;
		s[7] = 0.307939839;
		s[8] = 0.141707219;
		s[9] = 0.550352942;
		s[10] = 0.141707219;
		s[11] = 0.550352942;
		s[12] = 0.307939839;
		s[13] = 0.246672561;
		s[14] = 0.025003535;
		s[15] = 0.728323905;
		s[16] = 0.025003535;
		s[17] = 0.728323905;
		s[18] = 0.246672561;
		s[19] = 0.066803251;
		s[20] = 0.009540815;
		s[21] = 0.923655934;
		s[22] = 0.009540815;
		s[23] = 0.923655934;
		s[24] = 0.066803251;
		w[0] = 0.045408995;
		w[1] = 0.0183629788782335;
		w[2] = 0.0183629788782335;
		w[3] = 0.0183629788782335;
		w[4] = 0.0226605295;
		w[5] = 0.0226605295;
		w[6] = 0.0226605295;
		w[7] = 0.0363789585;
		w[8] = 0.0363789585;
		w[9] = 0.0363789585;
		w[10] = 0.0363789585;
		w[11] = 0.0363789585;
		w[12] = 0.0363789585;
		w[13] = 0.0141636215;
		w[14] = 0.0141636215;
		w[15] = 0.0141636215;
		w[16] = 0.0141636215;
		w[17] = 0.0141636215;
		w[18] = 0.0141636215;
		w[19] = 0.0047108335;
		w[20] = 0.0047108335;
		w[21] = 0.0047108335;
		w[22] = 0.0047108335;
		w[23] = 0.0047108335;
		w[24] = 0.0047108335;
		break;
	}
}

void elpol2d::monta_n()
{
#ifdef ALEATORIO
	aleatorio
#else
	double
#endif
		// Inicializacao de variaveis ----
		r, s, J[2][2], invJ[2][2];
	int i, j, n;
	i = j = n = 0;
	for (i = 0; i < 2; i++)
		for (n = 0; n < qnno(); n++)
			dn[2 * n + i] = dN[2 * n + i] = 0.0;
	// Pontos de Gauss ---------------
	r = rpg[pg];
	s = spg[pg];
	peso = wpg[pg];

	// Calcula N e dn para os pontos r e s (geralmente, os pontos de Gauss nas coordenadas do elemento)
	funcao_Forma(r, s, N, dn);

	// Matriz Jacobiana e Jacobiano
	J[0][0] = J[0][1] = J[1][0] = J[1][1] = 0.0;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			for (n = 0; n < qnno(); n++) {
				J[i][j] += dn[2 * n + i] * this->pno[n]->qx(j);
			}
		}
	}
	detJ = J[0][0] * J[1][1] - J[1][0] * J[0][1];

	invJ[0][0] = J[1][1] / detJ;
	invJ[1][1] = J[0][0] / detJ;
	invJ[0][1] = -J[0][1] / detJ;
	invJ[1][0] = -J[1][0] / detJ;
	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			for (n = 0; n < qnno(); n++)
				dN[2 * n + i] += invJ[i][j] * dn[2 * n + j];
	peso *= abs(detJ);	// peso = peso * (detJ)
}

void elpol2d::monta_rigidez()
{
#ifdef ALEATORIO
	aleatorio *xx, *yy;
	xx = new aleatorio[qnno()];
	yy = new aleatorio[qnno()];
#else
	double *xx, *yy;
	xx = new double[qnno()];
	yy = new double[qnno()];
#endif
	for (int i = 0; i<qnno()*qipn(); i++)
		for (int j = 0; j<qnno()*qipn(); j++)
			this->k[qnno()*qipn()*i + j] = 0.0;
	pontos_de_gauss(qptg(), rpg, spg, wpg);
	for (pg = 0; pg < qptg(); pg++) {
		monta_b();
		monta_c();
		for (int i = 0; i < qnno()*qipn(); i++)
			for (int j = 0; j < qnlb(); j++)
				for (int l = 0; l < qnlb(); l++)
					for (int m = 0; m < qnno()*qipn(); m++)
						k[qnno()*qipn()*i + m] +=
						b[qnno()*qipn()*j + i] * c[qnlb()*j + l] * b[qnno()*qipn()*l + m] * peso;
	}
};

#ifdef ALEATORIO
void elpol2d::p_processa(aleatorio *xx)
{
#else
void elpol2d::p_processa(double *xx)
{
#endif
	pg = qptg();
	for (int i = 0; i<qnno()*qipn(); i++)
	{
		f[i] = 0.0;
		for (int n = 0; n<qnno(); n++)
			for (int j = 0; j<qipn(); j++)
				f[j] += qk(i, n*qipn() + j)*xx[qno(n)*qipn() + j];
	}
	for (int n = 0; n<qnno(); n++)
		for (int i = 0; i<qipn(); i++)
			x[n*qipn() + i] = xx[qno(n)*qipn() + i];

	// Calculo da area (Ae) e do centro (ptm) do elemento
	area_centro();
	// Zera tensao media
	for (int i = 0; i < qnlb(); i++)
		tenM[i] = 0;
	//for (pg = 0; pg < lpg; pg++)
	for (pg = 0; pg < qptg(); pg++)
	{
		monta_b();
		// Calculo das coordenados dos pontos de Gauss no dominio "real"
		// e deslocamentos nos pontos de Gauss
		Peso[pg] = peso;
		ptx[pg] = pty[pg] = 0;
		for (int i = 0; i < qipn(); i++)
			des[pg*qipn() + i] = 0;
		for (int n = 0; n < qnno(); n++) {
			ptx[pg] += N[n] * pno[n]->qx(0);
			pty[pg] += N[n] * pno[n]->qx(1);
			des[pg*qipn()] += N[n] * x[n*qipn()];
			des[pg*qipn() + 1] += N[n] * x[n*qipn() + 1];
		}
		//
		for (int i = 0; i < qnlb(); i++)
		{
			// Adicionei o  + tri*qptg()*qnlb() para computar os pontos de Gauss em cada triângulo
			// para 3 pontos de Gauss por triangulo, um elemento de 5 nós terá 15 pontos de Gauss.
			// Mas ainda falta escrever no arquivo de saída todos os pontos de Gauss.
			def[pg*qnlb() + i] = ten[pg*qnlb() + i] = 0;
			for (int j = 0; j < qnno()*qipn(); j++)
				def[pg*qnlb() + i] += b[i*qnno()*qipn() + j] * x[j];
		}
		monta_c();
		for (int i = 0; i < qnlb(); i++)
		{
			for (int j = 0; j < qnlb(); j++)
				// Revisar se é def[...+j+...]
				ten[pg*qnlb() + i] += c[i*qnlb() + j] * def[pg*qnlb() + j];
			tenM[i] += ten[pg*qnlb() + i] * peso;
		}
	}
	for (int i = 0; i < qnlb(); i++)
		tenM[i] = tenM[i] / Ae;

	//// Tensao media
	//double lpg = ptg*qnno();
	//for (int i = 0; i < qnlb(); i++){
	//	tenM[i] = 0;
	//	for (pg = 0; pg < lpg; pg++)
	//		tenM[i] += ten[pg*qnlb() + i];
	//	tenM[i] = tenM[i] / lpg;
	//}
};