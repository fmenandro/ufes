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
#include "elcal1d2n.h"

elcal1d2n::elcal1d2n()
 : iscal1d(nno,ptg)
{
}


elcal1d2n::~elcal1d2n()
{
}

void elcal1d2n::monta_n()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
          r,J[1][1],invJ[1][1],um=1.0,dois=2.0;
   double xpg[ptg],wpg[ptg];
   int p=ptg;
   for (int i=0;i<qdim();i++)
      for (int n=0;n<qnno();n++)
         dn[qdim()*n+i]=dN[qdim()*n+i]=0.0;
   pontos_de_gauss(p,xpg,wpg);
//   for (int pg=0;pg<qdim()*qptg();pg++)
//   {
      r=xpg[pg%p];
      peso=wpg[pg%p];
      N[0]=(um+r)/dois;
      N[1]=(um-r)/dois;
      dn[0]=(um)/dois;
      dn[1]= -(um)/dois;
      J[0][0]=0.0;
      for (int i=0;i<qnlb();i++)
         for (int j=0;j<qnlb();j++)
            for (int n=0;n<qnno();n++)
               J[i][j]+=dn[qnno()*i+n]*this->pno[n]->qx(j);
      detJ=J[0][0];
      invJ[0][0]=um/detJ;
      for (int i=0;i<qnlb();i++)
         for (int j=0;j<qnlb();j++)
            for (int n=0;n<qnno();n++)
               dN[qnno()*i+n]+=invJ[i][j]*dn[qnno()*j+n];
      peso*=detJ;
 //  }
}
void elcal1d2n::monta_c()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      T=0.0;
   for (int i=0;i<qnlb()*qnlb();i++)
      c[i]=0.0;
   monta_n();
   for (int i=0;i<qnno();i++)
      T+=x[i]*N[i];
   c[0]=pmaterial->qK(T);
};


