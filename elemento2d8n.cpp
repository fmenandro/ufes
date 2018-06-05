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
#include "elemento2d8n.h"

elemento2D8N::elemento2D8N()
 : isop2d(nno,ptg)
{
}


elemento2D8N::~elemento2D8N()
{
}


void elemento2D8N::monta_n()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
          r,s,J[2][2],invJ[2][2],um=1.0,dois=2.0,quatro=4.0;
   double xpg[ptg],wpg[ptg];
   int p=ptg;
   for (int i=0;i<2;i++)
      for (int n=0;n<8;n++)
         dn[2*n+i]=dN[2*n+i]=0.0;
   pontos_de_gauss(p,xpg,wpg);
   r=xpg[pg%p];
   s=xpg[pg/p];
   peso=wpg[pg%p];
   peso*=wpg[pg/p];
   N[4]=(um-r*r)*(um+s)/dois;
   N[5]=(um-s*s)*(um-r)/dois;
   N[6]=(um-r*r)*(um-s)/dois;
   N[7]=(um-s*s)*(um+r)/dois;
   N[0]=(um+r)*(um+s)/quatro-N[4]/dois-N[7]/dois;
   N[1]=(um-r)*(um+s)/quatro-N[4]/dois-N[5]/dois;
   N[2]=(um-r)*(um-s)/quatro-N[5]/dois-N[6]/dois;
   N[3]=(um+r)*(um-s)/quatro-N[6]/dois-N[7]/dois;
   dn[0]=(um+s)/quatro+r*(um+s)/dois-(um-s*s)/quatro;
   dn[1]=(um+r)/quatro-(um-r*r)/quatro+s*(um+r)/dois;
   dn[2]= -(um+s)/quatro+r*(um+s)/dois+(um-s*s)/quatro;
   dn[3]=(um-r)/quatro-(um-r*r)/quatro+s*(um-r)/dois;
   dn[4]= -(um-s)/quatro+(um-s*s)/quatro+r*(um-s)/dois;
   dn[5]= -(um-r)/quatro+s*(um-r)/dois+(um-r*r)/quatro;
   dn[6]=(um-s)/quatro+r*(um-s)/dois-(um-s*s)/quatro;
   dn[7]= -(um+r)/quatro+(um-r*r)/quatro+s*(um+r)/dois;
   dn[8]= r*(um+s);
   dn[9]= -(um-r*r)/dois;
   dn[10]= (um-s*s)/dois;
   dn[11]= s*(um-r);
   dn[12]= r*(um-s);
   dn[13]= (um-r*r)/dois;
   dn[14]= -(um-s*s)/dois;
   dn[15]= s*(um+r);
   J[0][0]=J[0][1]=J[1][0]=J[1][1]=0.0;
   for (int i=0;i<2;i++)
      for (int j=0;j<2;j++)
         for (int n=0;n<8;n++)
            J[i][j]+=dn[2*n+i]*this->pno[n]->qx(j);
   detJ=J[0][0]*J[1][1]-J[1][0]*J[0][1];
   invJ[0][0]=J[1][1]/detJ;
   invJ[1][1]=J[0][0]/detJ;
   invJ[0][1]=-J[0][1]/detJ;
   invJ[1][0]=-J[1][0]/detJ;
   for (int i=0;i<2;i++)
      for (int j=0;j<2;j++)
         for (int n=0;n<8;n++)
            dN[2*n+i]+=invJ[i][j]*dn[2*n+j];
   peso*=detJ;
}

