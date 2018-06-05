/***************************************************************************
 *   Copyright (C) 2005 by Fernando Cesar Meira Menandro                   *
 *   fcmm@npd.ufes.br                                                      *
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
#include "barra2d.h"


Barra2D::Barra2D():elemento(dim,ipn,nno,prp,ptg,nlb)
{
}

Barra2D::~Barra2D()
{
}
void Barra2D::monta_rigidez()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
       E,A,L,xx[2],yy[2],dx,dy,dx2,dy2,s,c,h;
   E=this->pmaterial->qE();
   A=this->prop[0];
   xx[0]=this->pno[0]->qx(0);
   xx[1]=this->pno[1]->qx(0);
   yy[0]=this->pno[0]->qx(1);
   yy[1]=this->pno[1]->qx(1);
   dx=xx[1]-xx[0];
   dy=yy[1]-yy[0];
   dx2=dx*dx;
   dy2=dy*dy;
   h=dy2+dx2;
#ifdef ALEATORIO
   L=h.asqrt();
#else
   L=sqrt(h);
#endif
   s=dy/L;
   c=dx/L;
   k[0]=          k[10]=       E*A*c*c/L;
   k[1]=k[4]=     k[11]=k[14]= E*A*c*s/L;
        k[5]=           k[15]= E*A*s*s/L;
   k[2]=     k[8]=             -k[0];
   k[3]=k[6]=k[9]=k[12]=       -k[1];
        k[7]=     k[13]=       -k[5];
}
void Barra2D::monta_b()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
       L,xx[2],yy[2],dx,dy,h,s,c,B[2],T[2][4],um=1.0;
   for (int j=0;j<4;j++)
      b[j]=0.0;
   xx[0]=this->pno[0]->qx(0);
   xx[1]=this->pno[1]->qx(0);
   yy[0]=this->pno[0]->qx(1);
   yy[1]=this->pno[1]->qx(1);
   dx=xx[1]-xx[0];
   dy=yy[1]-yy[0];
   h=dx*dx+dy*dy;
#ifdef ALEATORIO
   L=h.asqrt();
#else
   L=sqrt(h);
#endif
   c=dx/L;
   s=dy/L;
   for (int i=0;i<2;i++)
      for (int j=0;j<4;j++)
         T[i][j]=0.0;
   B[1]=um/L;
   B[0]=-B[1];
   T[0][0]=T[1][2]=c;
   T[0][1]=T[1][3]=s;
   for (int i=0;i<2;i++)
      for (int j=0;j<4;j++)
         b[j]+=B[i]*T[i][j];
}
void Barra2D::monta_c()
{
   c[0]=pmaterial->qE()*prop[0];
}

