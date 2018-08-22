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
#include "elemento_poligonal2d_NC.h"

elpol2d_NC::elpol2d_NC(int nno)
: isop2d(nno, ptg, 1)
{
	//this->nno = nno;
	//this->ptg = ptg;
}

elpol2d_NC::~elpol2d_NC()
{
}

int elpol2d_NC::qptg(){
	return ptg;
}

void elpol2d_NC::funcao_Forma(double r, double s, double *N, double *dn){};

void elpol2d_NC::pontos_de_gauss(const int p, double *r, double *s, double *w) {
	int n, i, j;
	double h, k;
	int flag = 1;
	int a = 0, c = 0;	// Origem do triângulo padrao
	int b = 1, d = 1;	// Vertice da direita e de cima do triangulo padrao

	n = (sqrt(1 + 8 * p) - 3) / 2;	// Número de intervalos
	h = (b - a) / double(n);	// Delta r (dimensao do intervalo)
	k = (d - c) / double(n);	// Delta s

	r[0] = a; s[0] = c; w[0] = h*k / 6;// / qnno();	// Vetice da origem
	r[1] = b; s[1] = c; w[1] = h*k / 6;	// Vertice da direita
	r[2] = a; s[2] = d; w[2] = h*k / 6;	// Vertice de cima

	for (i = 1; i < n; i++){
		// Nós do contorno inferior
		r[i + 2] = a + i*h;
		s[i + 2] = c;
		w[i + 2] = h*k / 2;// / 2;
		// Nós do contorno superior
		r[i + 2 + (n - 1)] = a;
		s[i + 2 + (n - 1)] = c + i*k;
		w[i + 2 + (n - 1)] = h*k / 2;///2;
		// Nós da diagonal
		r[i + 2 + 2 * (n - 1)] = a + i*h;
		s[i + 2 + 2 * (n - 1)] = c + (n - i)*k;
		w[i + 2 + 2 * (n - 1)] = h*k / 2;
		// Nós internos
		for (j = 1; j < n - i; j++){
			r[2 + 3 * (n - 1) + flag] = a + j*h;
			s[2 + 3 * (n - 1) + flag] = c + i*k;
			w[2 + 3 * (n - 1) + flag] = h*k;
			flag++;
		}
	}
}

void elpol2d_NC::monta_n()
{
#ifdef ALEATORIO
	aleatorio
#else
	double
#endif
		// Inicializacao de variaveis ---
		r, s, J[2][2], invJ[2][2];
	double rpg[ptg], spg[ptg], wpg[ptg];
	int p = ptg;
	double r1[2], r2[2];
	double detJ1;
	const double pi = 3.14159265358979323846;
	int i, j, n;
	i = j = n = 0;
	for (i = 0; i < 2; i++)
	for (n = 0; n < qnno(); n++)
		dn[2 * n + i] = dN[2 * n + i] = 0.0;
	// -------------------------------

	// Mudança de coordenadas dos pontos de Gauss. Coordenadas do triângulo
	// padrao para o elemento padrao ----------------------------------------
	// Pontos das extremidades do triangulo (coordenadas do elemento padrao)
	for (i = 0; i < 2; i++){
		r1[i] = cos(2 * pi*(tri + i + 1) / qnno());
		r2[i] = sin(2 * pi*(tri + i + 1) / qnno());
	}
	detJ1 = r1[0] * r2[1] - r2[0] * r1[1];
	// Esse determinante nao muda conforme o ponto de Gauss, so depende do triangulo

	// Pontos de Gauss estão no sistema de coordenadas do triangulo,
	//entao, ele sao transformados para o sistema de coordenadas do elemento.
	// r e s: pontos de Gauss nas coordenadas do elemento.
	pontos_de_gauss(p, rpg, spg, wpg);	// Tem necessidade de chamar esse método de novo? (já é chamado em monta_rigidez)
	r = r1[0] * rpg[pg] + r1[1] * spg[pg];
	s = r2[0] * rpg[pg] + r2[1] * spg[pg];
	peso = wpg[pg];
	// -----------------------------------------------------------------------

	// Calcula N e dn para os pontos r e s (geralmente, os pontos de Gauss nas coordenadas do elemento)
	funcao_Forma(r, s, N, dn);

	// Matriz Jacobiana e Jacobiano
	// Esse Jacobiano está certo? J2 com essa mudança de coordenadas é mesmo J2?
	J[0][0] = J[0][1] = J[1][0] = J[1][1] = 0.0;
	for (i = 0; i < 2; i++){
		for (j = 0; j < 2; j++){
			for (n = 0; n < qnno(); n++){
				J[i][j] += dn[2 * n + i] * this->pno[n]->qx(j); // N�o entendi esse this -> ...
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

void elpol2d_NC::monta_rigidez()
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
	double *rpg, *spg, *wpg;
	rpg = new double[qptg()];
	spg = new double[qptg()];
	wpg = new double[qptg()];
	for (int i = 0; i<qnno()*qipn(); i++)
	for (int j = 0; j<qnno()*qipn(); j++)
		this->k[qnno()*qipn()*i + j] = 0.0;
	pontos_de_gauss(qptg(), rpg, spg, wpg);
	for (tri = 0; tri < qnno(); tri++){	// Para cada triangulo dentro do elemento
		// ATENCAO: quando estava somente tri < nno, o valor de tri = 5 entrava no loop nao sei o porquê.
		for (pg = 0; pg < qptg(); pg++){
			// Revisar se os pontos de Gauss são escolhidos no elemento ou no triangulo.
			// Se forem dentro do triangulo, acho que o loop tri deve estar acima dos pontos de Gauss
			// (ou nao faz diferenca)
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
	//// Nao da pra fazer assim, pois o monta_rigidez zeraria o k a cada entrada no loop do tri
	//for (tri = 0; tri < nno; tri++){
	//	isop2d::monta_rigidez();
	//}
};



#ifdef ALEATORIO
void elpol2d_NC::p_processa(aleatorio *xx)
{
#else
void elpol2d_NC::p_processa(double *xx)
{
#endif
	double *xpg, *ypg, *wpg;
	xpg = new double[qptg()];
	ypg = new double[qptg()];	// Nao havia esta linha
	wpg = new double[qptg()];
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
	pontos_de_gauss(pg, xpg, ypg, wpg);
	//int lpg = qptg();
	//if (qdim() == 2) lpg *= lpg;
	//if (qdim() == 3) lpg *= lpg*lpg;
	for (tri = 0; tri < qnno(); tri++){
		//for (pg = 0; pg < lpg; pg++)
		for (pg = 0; pg < qptg(); pg++)
		{
			monta_b();
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
					ten[pg*qnlb() + i + tri*qptg()*qnlb()] += c[i*qnlb() + j] * def[j];
			}
		}
	}
};