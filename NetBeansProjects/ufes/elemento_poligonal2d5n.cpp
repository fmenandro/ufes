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
: isop2d(nno, ptg)
{
}


elpol2D5N::~elpol2D5N()
{
}

int elpol2D5N::qnno(){
	return nno;
}

int elpol2D5N::qptg(){
	return ptg;
}
void elpol2D5N::pontos_de_gauss(const int p, const int n, double *r,double *s, double *w)
{
switch (p)
{
case 1:
   r[0]=0.0;
   s[0]=0.0;
   w[0]=n*sin(8*atan(1.0)/n);
   break;
}
}

void elpol2D5N::monta_n()
{
#ifdef ALEATORIO
	aleatorio
#else
	double
#endif
		r, s, J[2][2], invJ[2][2];
	double rpg[ptg], spg[ptg], wpg[ptg];
	int p = ptg;
	for (int i = 0; i < 2; i++)
	for (int n = 0; n < 5; n++)
		dn[2 * n + i] = dN[2 * n + i] = 0.0;
	pontos_de_gauss(p, nno, rpg, spg, wpg);
	r = rpg[pg];
	s = spg[pg];
	peso = wpg[pg];

	// RENAN
	// Coeficientes para as fun��es de forma(?)
	// A. TABARRAEI and N. SUKUMAR, Application of polygonal finite elements in linear elasticity
	// Usar double em vez de float?
	float k_a[5][10] = {
		{ -0.092937, 3.23607, 4, 0, -3.80423, 3.80423, -2.76393, 15.2169, 5.81234, 17.8885 },
		{ -0.0790569, 3.80423, -3.80423, -2.76393, -3.80423, 3.80423, -2.76393, 15.2169, 5.81234, 17.8885 },
		{ -0.0790569, 15.2169, 5.81234, -17.8885, 3.80423, -3.80423, -2.76393, -3.80423, 3.80423, -2.76393 },
		{ 0.092937, 3.23607, 4, 0, 15.2169, 5.81234, -17.8885, 3.80423, -3.80423, -2.76393 },
		{ 0.0232343, 3.23607, 4, 0, 15.2169, 5.81234, -17.8885, 15.2169, 5.81234, 17.8885 }
	};
	float k_b[3] = { 87.05, -12.7004, -12.7004 };

	float b = k_b[0] + k_b[1] * pow(r, 2)  + k_b[2] * pow(s, 2);
	float a[5];
	int j = 0;

	// C�lculo das Fun��es de Forma(?) e derivadas
	for (int i = 0; i < 5; i++){
		a[i] = k_a[i][0] * (k_a[i][1] + k_a[i][2] * r + k_a[i][3] * s) *
			(k_a[i][4] + k_a[i][5] * r + k_a[i][6] * s) *
			(k_a[i][7] + k_a[i][8] * r + k_a[i][9] * s);
		// Melhor calcular os pacotes de "k"s separadamente? Pois eles se repetem

		N[i] = a[i] / b;

		// Derivada em rela��o a r
		dn[j] = k_a[i][0] / b * (
			k_a[i][5] * (k_a[i][7] + k_a[i][8] * r + k_a[i][9] * s) * (k_a[i][1] + k_a[i][2] * r + k_a[i][3] * s) +
			k_a[i][2] * (k_a[i][7] + k_a[i][8] * r + k_a[i][9] * s) * (k_a[i][4] + k_a[i][5] * r + k_a[i][6] * s) +
			k_a[i][8] * (k_a[i][1] + k_a[i][2] * r + k_a[i][3] * s) * (k_a[i][4] + k_a[i][5] * r + k_a[i][6] * s)
			)
			- 2 * k_b[1] * r * a[i] / pow(b, 2);

		// Derivada em rela��o a s
		dn[j+1] = k_a[i][0] / b * (
			k_a[i][6] * (k_a[i][7] + k_a[i][8] * r + k_a[i][9] * s) * (k_a[i][1] + k_a[i][2] * r + k_a[i][3] * s) +
			k_a[i][3] * (k_a[i][7] + k_a[i][8] * r + k_a[i][9] * s) * (k_a[i][4] + k_a[i][5] * r + k_a[i][6] * s) +
			k_a[i][9] * (k_a[i][1] + k_a[i][2] * r + k_a[i][3] * s) * (k_a[i][4] + k_a[i][5] * r + k_a[i][6] * s)
			)
			- 2 * k_b[2] * s * a[i] / pow(b, 2);

		j = j + 2;
	}

	// Jacobiano
	J[0][0] = J[0][1] = J[1][0] = J[1][1] = 0.0;
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			for (int n = 0; n < 5; n++){
				J[i][j] += dn[2 * n + i] * this->pno[n]->qx(j); // N�o entendi esse this -> ...
			}
		}
	}
	detJ = J[0][0] * J[1][1] - J[1][0] * J[0][1];
	invJ[0][0] = J[1][1] / detJ;
	invJ[1][1] = J[0][0] / detJ;
	invJ[0][1] = -J[0][1] / detJ;
	invJ[1][0] = -J[1][0] / detJ;
	for (int i = 0; i<2; i++)
	for (int j = 0; j<2; j++)
	for (int n = 0; n<5; n++)
		dN[2 * n + i] += invJ[i][j] * dn[2 * n + j];
	peso *= detJ; // ?
}
void elpol2D5N::monta_rigidez()
{
#ifdef ALEATORIO
   aleatorio *xx,*yy;
   xx=new aleatorio[qnno()];
   yy=new aleatorio[qnno()];
#else
   double *xx,*yy;
   xx=new double[qnno()];
   yy=new double[qnno()];
#endif
   double *rpg,*spg,*wpg;
   rpg=new double[qptg()];
   spg=new double[qptg()];
   wpg=new double[qptg()];
   for (int i=0;i<qnno()*qipn();i++)
      for (int j=0;j<qnno()*qipn();j++)
         this->k[qnno()*qipn()*i+j]=0.0;
   pontos_de_gauss(qptg(),nno,rpg,spg,wpg);
   for (pg=0;pg<qptg();pg++)
   {
      monta_b();
      monta_c();
      for (int i=0;i<qnno()*qipn();i++)
         for (int j=0;j<qnlb();j++)
            for (int l=0;l<qnlb();l++)
               for (int m=0;m<qnno()*qipn();m++)
                  k[qnno()*qipn()*i+m]+=
                     b[qnno()*qipn()*j+i]*c[qnlb()*j+l]*b[qnno()*qipn()*l+m]*peso;

   }
};