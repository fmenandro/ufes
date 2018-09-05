/***************************************************************************
 *   Copyright (C) 2005 by Fernando César Meira Menandro   *
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
#include "isop2d.h"

/* O elemento isoparamétrico bidimensional é uma classe base para
criação de outros elementos de duas dimensões. As variáveis estáticas
   const static int dim=2;  //Dimensao do problema
   const static int ipn=2;  //Numero de incognitas por no
   const static int prp=1;  //Numero de propriedades do elemento (area,espessura)
                            //Propriedade 0: espessura
   const static int nlb=3;  //Numero de linhas da matriz B (componentes de deformacao)
já ficam definidas, restando a definição do número de nós (nno) e do número de pontos
de Gauss por direção (ptg). */
isop2d::isop2d(int nno,int ptg)
 : elemento(dim,ipn,nno,prp,ptg,nlb)
{
/* Alocação de memória
N - função de interpolação de deslocamento (função de forma para elemento isoparamétrico)
dn- derivadas das funções N nas coordenadas r e s.
dN- derivadas das funções N nas coordenadas x e y.
xg- coordenadas dos pontos de Gauss (para uma dimensão)
wg- pesos de Gauss associados aos pontos
*/
#ifdef ALEATORIO
   N = new class aleatorio[nno];
   dn = new class aleatorio[nno*2];
   dN = new class aleatorio[nno*2];
   xg = new class aleatorio[dim];
   wg = new class aleatorio[dim];
#else
   N = new double[nno];
   dn = new double[nno*2];
   dN = new double[nno*2];
   xg = new double[dim];
   wg = new double[dim];
#endif
// Inicialização da variável DetJ (Determinante da matriz Jacobiano)
   detJ=0.0;
};

// ADICIONADO POR RENAN, temporario. Para avisar que e poligonal
isop2d::isop2d(int nno, int ptg, int poli)
: elemento(dim, ipn, nno, prp, ptg, nlb, poli)
{
	// poli: quando existente (= 1) indica que o elemento é poligonal

	/* Alocação de memória
	N - função de interpolação de deslocamento (função de forma para elemento isoparamétrico)
	dn- derivadas das funções N nas coordenadas r e s.
	dN- derivadas das funções N nas coordenadas x e y.
	xg- coordenadas dos pontos de Gauss (para uma dimensão)
	wg- pesos de Gauss associados aos pontos
	*/
#ifdef ALEATORIO
	N = new class aleatorio[nno];
	dn = new class aleatorio[nno * 2];
	dN = new class aleatorio[nno * 2];
	xg = new class aleatorio[dim];
	wg = new class aleatorio[dim];
#else
	N = new double[nno];
	dn = new double[nno * 2];
	dN = new double[nno * 2];
	xg = new double[dim];
	wg = new double[dim];
#endif
	// Inicialização da variável DetJ (Determinante da matriz Jacobiano)
	detJ = 0.0;
};

isop2d::~isop2d()
{
};

void isop2d::monta_b()
{
   monta_n();
   for (int i=0;i<qnno();i++)
   {
      b[(2*i)]=b[4*qnno()+2*i+1]=dN[i*2];
      b[2*(qnno()+i)+1]=b[4*qnno()+2*i]=dN[i*2+1];
      b[(2*i)+1]=b[2*(qnno()+i)]=0.0;
   }
};
void isop2d::monta_c()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      um=1.0;
   for (int i=0;i<qnlb()*qnlb();i++)
      c[i]=0.0;
   c[0]=pmaterial->qE()/(um-pmaterial->qni()*pmaterial->qni());
   c[1]=pmaterial->qni()*c[0];
   c[3]=c[1];
   c[4]=c[0];
   c[8]=pmaterial->qE()/((um+pmaterial->qni())*2.0);
};
/* Para elementos isoparamétricos apenas montamos as matrizes deslocamento-deformação
e de propriedades dos materiais, para em seguida realizar o produto
   T
 [B] [C] [B].
*/
void isop2d::monta_rigidez()
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
   double *xpg,*wpg;
   xpg=new double[qptg()];
   wpg=new double[qptg()];
   for (int i=0;i<qnno()*qipn();i++)
      for (int j=0;j<qnno()*qipn();j++)
         this->k[qnno()*qipn()*i+j]=0.0;
   pontos_de_gauss(qptg(),xpg,wpg);
   for (pg=0;pg<qdim()*qptg();pg++)
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
/* Em diferentes */
void isop2d::monta_n(){};



