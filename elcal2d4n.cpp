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
#include "elcal2d4n.h"

elcal2d4n::elcal2d4n()
 : iscal2d(nno,ptg)
{
}


elcal2d4n::~elcal2d4n()
{
}

void elcal2d4n::monta_n()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
          r,s,J[2][2],invJ[2][2],um=1.0,quatro=4.0;
   double xpg[ptg],wpg[ptg];
   int p=ptg;
   for (int i=0;i<2;i++)
      for (int n=0;n<4;n++)
         dn[2*n+i]=dN[2*n+i]=0.0;
   pontos_de_gauss(p,xpg,wpg);
   r=xpg[pg%p];
   s=xpg[pg/p];
   peso=wpg[pg%p];
   peso*=wpg[pg/p];
   N[0]=(um+r)*(um+s)/quatro;
   N[1]=(um-r)*(um+s)/quatro;
   N[2]=(um-r)*(um-s)/quatro;
   N[3]=(um+r)*(um-s)/quatro;
   dn[0]=(um+s)/quatro;
   dn[1]=(um+r)/quatro;
   dn[2]= -(um+s)/quatro;
   dn[3]=(um-r)/quatro;
   dn[4]= -(um-s)/quatro;
   dn[5]= -(um-r)/quatro;
   dn[6]=(um-s)/quatro;
   dn[7]= -(um+r)/quatro;
   J[0][0]=J[0][1]=J[1][0]=J[1][1]=0.0;
   for (int i=0;i<2;i++)
      for (int j=0;j<2;j++)
         for (int n=0;n<4;n++)
            J[i][j]+=dn[2*n+i]*this->pno[n]->qx(j);
   detJ=J[0][0]*J[1][1]-J[1][0]*J[0][1];
   invJ[0][0]=J[1][1]/detJ;
   invJ[1][1]=J[0][0]/detJ;
   invJ[0][1]=-J[0][1]/detJ;
   invJ[1][0]=-J[1][0]/detJ;
   for (int i=0;i<2;i++)
      for (int j=0;j<2;j++)
         for (int n=0;n<4;n++)
            dN[2*n+i]+=invJ[i][j]*dn[2*n+j];
   peso*=detJ;
}

