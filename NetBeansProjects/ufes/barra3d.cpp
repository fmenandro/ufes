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
#include "barra3d.h"

Barra3D::Barra3D():elemento(dim,ipn,nno,prp,ptg,nlb)
{
}

Barra3D::~Barra3D()
{
}
void Barra3D::monta_rigidez()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      E,A,L,xx[2],yy[2],zz[2],dx,dy,dz,h,cx,cy,cz,K[2][2],T[2][6];
   E=this->pmaterial->qE();
   A=this->prop[0];
   xx[0]=this->pno[0]->qx(0);
   xx[1]=this->pno[1]->qx(0);
   yy[0]=this->pno[0]->qx(1);
   yy[1]=this->pno[1]->qx(1);
   zz[0]=this->pno[0]->qx(2);
   zz[1]=this->pno[1]->qx(2);
   dx=xx[1]-xx[0];
   dy=yy[1]-yy[0];
   dz=zz[1]-zz[0];
   h=dx*dx+dy*dy+dz*dz;
#ifdef ALEATORIO
   L=h.asqrt();
#else
   L=sqrt(h);
#endif
   cx=dx/L;
   cy=dy/L;
   cz=dz/L;
   for (int i=0;i<2;i++)
      for (int j=0;j<6;j++)
         T[i][j]=0.0;
   K[0][0]=K[1][1]=E*A/L;
   K[0][1]=K[1][0]=-K[0][0];
   T[0][0]=T[1][3]=cx;
   T[0][1]=T[1][4]=cy;
   T[0][2]=T[1][5]=cz;
   for (int i=0;i<6;i++)
      for (int j=0;j<2;j++)
         for (int l=0;l<2;l++)
            for (int m=0;m<6;m++)
               k[6*i+m]+=T[j][i]*K[j][l]*T[l][m];
}
void Barra3D::monta_b()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      L,xx[2],yy[2],zz[2],dx,dy,dz,h,cx,cy,cz,B[2],T[2][6],um=1.0;
   for (int j=0;j<6;j++)
      b[j]=0.0;
   xx[0]=this->pno[0]->qx(0);
   xx[1]=this->pno[1]->qx(0);
   yy[0]=this->pno[0]->qx(1);
   yy[1]=this->pno[1]->qx(1);
   zz[0]=this->pno[0]->qx(2);
   zz[1]=this->pno[1]->qx(2);
   dx=xx[1]-xx[0];
   dy=yy[1]-yy[0];
   dz=zz[1]-zz[0];
   h=dx*dx+dy*dy+dz*dz;
#ifdef ALEATORIO
   L=h.asqrt();
#else
   L=sqrt(h);
#endif
   cx=dx/L;
   cy=dy/L;
   cz=dz/L;
   for (int i=0;i<2;i++)
      for (int j=0;j<6;j++)
         T[i][j]=0.0;
   B[1]=um/L;
   B[0]=-B[1];
   T[0][0]=T[1][3]=cx;
   T[0][1]=T[1][4]=cy;
   T[0][2]=T[1][5]=cz;
   for (int i=0;i<2;i++)
      for (int j=0;j<6;j++)
         b[j]+=B[i]*T[i][j];
}
void Barra3D::monta_c()
{
   c[0]=pmaterial->qE()*prop[0];
}




