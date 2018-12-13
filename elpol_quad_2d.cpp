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

#include "elpol_quad_2d.h"

elpol_quad_2d::elpol_quad_2d(int nno)
: isop2d(nno, ptg, 2) // 2 indica mapeamento em 2 niveis
{
	xpg = new double[qptg()];
	wpg = new double[qptg()];
}

elpol_quad_2d::~elpol_quad_2d()
{
}

int elpol_quad_2d::qptg(){
	return ptg;
}

void elpol_quad_2d::monta_n()
{
#ifdef ALEATORIO
	aleatorio
#else
	double
#endif
	// Inicializacao de variaveis ---
		r, s, J[2][2], invJ[2][2];
	double r1[4], r2[4], phi[4], dphi[8], J1[2][2];
	double detJ1;
	const double pi = 3.14159265358979323846;
	int i, j, n;
	int p;
	i = j = n = 0;
	for (i = 0; i < 2; i++)
	for (n = 0; n < qnno(); n++)
		dn[2 * n + i] = dN[2 * n + i] = 0.0;
	// -------------------------------

	// Mudança de coordenadas dos pontos de Gauss. Coordenadas do quadrado
	// padrao para o elemento padrao ----------------------------------------
	// Pontos das extremidades do quadrado (coordenadas do elemento padrao)
	r1[1] = cos(2 * pi*(tri + 1) / qnno()); // Ponto do meio
	r2[1] = sin(2 * pi*(tri + 1) / qnno());
	r1[0] = (r1[1] + cos(2 * pi*tri / qnno())) / 2; // Ponto da direita
	r2[0] = (r2[1] + sin(2 * pi*tri / qnno())) / 2;
	r1[2] = (r1[1] + cos(2 * pi*(tri + 2) / qnno())) / 2; // Ponto da esquerda
	r2[2] = (r2[1] + sin(2 * pi*(tri + 2) / qnno())) / 2;
	r1[3] = r2[3] = 0; // Ponto central
	// Truque para obter os pontos de Gauss no quadrado padrão
	p = sqrt(qptg());
	r = xpg[pg%p];
	s = xpg[pg / p];
	peso = wpg[pg%p];
	peso *= wpg[pg / p];
	// Funcoes de forma 2 e derivadas
	phi[0] = (1 + r)*(1 + s) *0.25;
	phi[1] = (1 - r)*(1 + s) *0.25;
	phi[2] = (1 - r)*(1 - s) *0.25;
	phi[3] = (1 + r)*(1 - s) *0.25;
	dphi[0] = (1 + s) *0.25;
	dphi[1] = (1 + r) *0.25;
	dphi[2] = -(1 + s) *0.25;
	dphi[3] = (1 - r) *0.25;
	dphi[4] = -(1 - s) *0.25;
	dphi[5] = -(1 - r) *0.25;
	dphi[6] = (1 - s) *0.25;
	dphi[7] = -(1 + r) *0.25;
	// Determinante 2
	J1[0][0] = J1[0][1] = J1[1][0] = J1[1][1] = 0.0;
	for (int i = 0; i < 2; i++) {
		for (int n = 0; n < 4; n++) {
			J1[i][0] += dphi[2 * n + i] * r1[n];
			J1[i][1] += dphi[2 * n + i] * r2[n];
		}
	}
	detJ1 = J1[0][0] * J1[1][1] - J1[1][0] * J1[0][1];

	// Pontos de Gauss estão no sistema de coordenadas do quadrado,
	// entao, eles sao transformados para o sistema de coordenadas do elemento.
	// r e s: pontos de Gauss nas coordenadas do elemento.
	r = 0; s = 0;
	for (int n = 0; n < 4; n++) {
		r += r1[n] * phi[n];
		s += r2[n] * phi[n];
	}
	// -----------------------------------------------------------------------

	// Calcula N e dn para os pontos r e s (geralmente, os pontos de Gauss nas coordenadas do elemento)
	funcao_Forma(r, s, N, dn);

	// Matriz Jacobiana e Jacobiano
	J[0][0] = J[0][1] = J[1][0] = J[1][1] = 0.0;
	for (i = 0; i < 2; i++){
		for (j = 0; j < 2; j++){
			for (n = 0; n < qnno(); n++){
				J[i][j] += dn[2 * n + i] * this->pno[n]->qx(j);
			}
		}
	}
	detJ = J[0][0] * J[1][1] - J[1][0] * J[0][1];

	//if (detJ > 100 || detJ < 0.001){
	//	ofstream myfile;
	//	string str;
	//	str = "Entradas e Saídas/Debug_" + to_string(qnno()) + "n.txt";
	//	myfile.open(str);			
	//	myfile << "detJ = " << detJ << "\npg = " << pg << "\ntri = " << tri;
	//	myfile.close();
	//}

	invJ[0][0] = J[1][1] / detJ;
	invJ[1][1] = J[0][0] / detJ;
	invJ[0][1] = -J[0][1] / detJ;
	invJ[1][0] = -J[1][0] / detJ;
	for (i = 0; i < 2; i++)
	for (j = 0; j < 2; j++)
	for (n = 0; n < qnno(); n++)
		dN[2 * n + i] += invJ[i][j] * dn[2 * n + j];
	peso *= abs(detJ) * abs(detJ1);	// peso = peso * (detJ * detJ1)
}

void elpol_quad_2d::monta_rigidez()
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
	pontos_de_gauss(sqrt(qptg()), xpg, wpg);
	for (tri = 0; tri < qnno(); tri++){	// Para cada triangulo dentro do elemento
		for (pg = 0; pg < qptg(); pg++){
			monta_b();
			monta_c();
			for (int i = 0; i < qnno()*qipn(); i++)
			for (int j = 0; j < qnlb(); j++)
			for (int l = 0; l < qnlb(); l++)
			for (int m = 0; m < qnno()*qipn(); m++)
				k[qnno()*qipn()*i + m] +=
				b[qnno()*qipn()*j + i] * c[qnlb()*j + l] * b[qnno()*qipn()*l + m] * peso;
		}
	}
};


#ifdef ALEATORIO
void elpol_quad_2d::p_processa(aleatorio *xx)
{
#else
void elpol_quad_2d::p_processa(double *xx)
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
	for (tri = 0; tri < qnno(); tri++){
		//for (pg = 0; pg < lpg; pg++)
		for (pg = 0; pg < qptg(); pg++)
		{
			monta_b();
			// Calculo das coordenados dos pontos de Gauss no dominio "real"
			// e deslocamentos nos pontos de Gauss
			Peso[pg + tri*qptg()] = peso;
			ptx[pg + tri*qptg()] = pty[pg + tri*qptg()] = 0;
			for (int i = 0; i < qipn(); i++)
				des[(pg + tri*qptg())*qipn() + i] = 0;
			for (int n = 0; n < qnno(); n++){
				ptx[pg + tri*qptg()] += N[n] * pno[n]->qx(0);
				pty[pg + tri*qptg()] += N[n] * pno[n]->qx(1);
				des[(pg + tri*qptg())*qipn()] += N[n] * x[n*qipn()];
				des[(pg + tri*qptg())*qipn() + 1] += N[n] * x[n*qipn() + 1];
			}
			//
			for (int i = 0; i < qnlb(); i++)
			{
				// Adicionei o  + tri*qptg()*qnlb() para computar os pontos de Gauss em cada triângulo
				// para 3 pontos de Gauss por triangulo, um elemento de 5 nós terá 15 pontos de Gauss.
				// Mas ainda falta escrever no arquivo de saída todos os pontos de Gauss.
				def[pg*qnlb() + i + tri*qptg()*qnlb()] = ten[pg*qnlb() + i + tri*qptg()*qnlb()] = 0;
				for (int j = 0; j < qnno()*qipn(); j++)
					def[pg*qnlb() + i + tri*qptg()*qnlb()] += b[i*qnno()*qipn() + j] * x[j];
			}
			monta_c();
			for (int i = 0; i < qnlb(); i++)
			{
				for (int j = 0; j < qnlb(); j++)
					// Revisar se é def[...+j+...]
					ten[pg*qnlb() + i + tri*qptg()*qnlb()] += c[i*qnlb() + j] * def[pg*qnlb() + j + tri*qptg()*qnlb()];
				tenM[i] += ten[pg*qnlb() + i + tri*qptg()*qnlb()] * peso;
			}
		}
	}
	for (int i = 0; i < qnlb(); i++)
		tenM[i] = tenM[i] / Ae;
};