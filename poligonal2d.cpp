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
#include "poligonal2d.h"

pol2d::pol2d(int nno, int ptg)
: isop2d(nno, ptg, 1)
{
	rpg = new double[ptg];
	spg = new double[ptg];
	wpg = new double[ptg];
}

pol2d::~pol2d()
{
}

void pol2d::monta_n()
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

void pol2d::monta_rigidez()
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
void pol2d::p_processa(double *xx)
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
};