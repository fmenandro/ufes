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
#include "viga2d.h"

Viga2D::Viga2D():elemento(dim,ipn,nno,prp,ptg,nlb)
{
}

Viga2D::~Viga2D()
{
}
void Viga2D::monta_b()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      E,A,I,L,xx[2],yy[2],dx,dy,h,sn,cs,B[3][6],T[6][6],X,um=1.0;
   for (int i=0;i<qnlb();i++)
      for (int j=0;j<6;j++)
      {
         b[i*6+j]=0.0;
         B[i][j]=0.0;
      }
   E=this->pmaterial->qE();
   A=this->prop[0];
   I=this->prop[1];
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
   sn=dy/L;
   cs=dx/L;
   X=(pg==0)?0:L;
   for (int i=0;i<6;i++)
      for (int j=0;j<6;j++)
         T[i][j]=0.0;
   T[0][0]=T[1][1]=T[3][3]=T[4][4]=cs;
   T[0][1]=T[3][4]=sn;
   T[1][0]=T[4][3]=-T[0][1];
   T[2][2]=T[5][5]=um;
   B[0][0]=-um/L;
   B[0][3]=-B[0][0];
   B[2][1]=((X*12.0)/L-(um*6.0))/(L*L);
   B[2][2]=((X*6)/L-(um*4.0))/L;
   B[2][4]=-B[2][1];
   B[2][5]=((X*6.0)/L-(um*2.0))/L;
   B[1][1]=(um*12.0)/(L*L*L);
   B[1][2]=B[1][5]=(um*6.0)/(L*L);
   B[1][4]=-B[1][1];
   for (int i=0;i<qnlb()*qnlb();i++)
      c[i]=0.0;
   c[0]=E*prop[0];
   c[4]=E*prop[1];
   c[8]=E*prop[1];
   for (int h=0;h<qnlb();h++)
      for (int i=0;i<qnlb();i++)
         for (int j=0;j<6;j++)
            for (int k=0;k<6;k++)
               b[h*6+k]+=c[h*qnlb()+i]*B[i][j]*T[k][j];
}
void Viga2D::monta_c()
{
   for (int i=0;i<qnlb()*qnlb();i++)
      c[i]=0.0;
}
void Viga2D::monta_rigidez()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      E,A,I,L,xx[2],yy[2],dx,dy,h,s,c,K[6][6],T[6][6];
   E=this->pmaterial->qE();
   A=this->prop[0];
   I=this->prop[1];
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
   s=dy/L;
   c=dx/L;
   for (int i=0;i<6;i++)
      for (int j=0;j<6;j++)
         K[i][j]=T[i][j]=k[6*i+j]=0.0;
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      fator=E*I/(L*L*L);
   K[0][0]=K[3][3]=E*A/L;
   K[0][3]=K[3][0]=-K[0][0];
   K[1][1]=K[4][4]=fator*12.0;
   K[1][4]=K[4][1]=-K[1][1];
   K[2][2]=K[5][5]=fator*L*L*4.0;
   K[2][5]=K[5][2]=fator*L*L*2.0;
   K[2][1]=K[5][1]=K[1][2]=K[1][5]=fator*L*6.0;
   K[4][2]=K[5][4]=K[2][4]=K[4][5]=-K[2][1];
   T[0][0]=T[1][1]=T[3][3]=T[4][4]=c;
   T[0][1]=T[3][4]=s;
   T[1][0]=T[4][3]=-T[0][1];
   T[2][2]=T[5][5]=1.0;
   for (int i=0;i<6;i++)
      for (int j=0;j<6;j++)
         for (int l=0;l<6;l++)
            for (int m=0;m<6;m++)
               k[6*i+m]+=T[i][j]*K[j][l]*T[m][l];
}


