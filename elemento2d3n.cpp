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
#include "elemento2d3n.h"

elemento2D3N::elemento2D3N()
 : elemento(dim,ipn,nno,prp,ptg,nlb)
{
}


elemento2D3N::~elemento2D3N()
{
}

void elemento2D3N::monta_b()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      xx[3],yy[3],duasxA;
   for (int i=0;i<qnlb();i++)
      for (int j=0;j<6;j++)
      {
         b[i*6+j]=0.0;
      }
   xx[0]=this->pno[0]->qx(0);
   xx[1]=this->pno[1]->qx(0);
   xx[2]=this->pno[2]->qx(0);
   yy[0]=this->pno[0]->qx(1);
   yy[1]=this->pno[1]->qx(1);
   yy[2]=this->pno[2]->qx(1);
   duasxA=-((xx[1]*yy[2]-xx[2]*yy[1])+(xx[2]*yy[0]-xx[0]*yy[2])+(xx[0]*yy[1]-xx[1]*yy[0]));
   b[0]=(yy[2]-yy[1])/duasxA;
   b[2]=(yy[0]-yy[2])/duasxA;
   b[4]=(yy[1]-yy[0])/duasxA;
   b[7]=(xx[1]-xx[2])/duasxA;
   b[9]=(xx[2]-xx[0])/duasxA;
   b[11]=(xx[0]-xx[1])/duasxA;
   b[12]=(xx[1]-xx[2])/duasxA;
   b[13]=(yy[2]-yy[1])/duasxA;
   b[14]=(xx[2]-xx[0])/duasxA;
   b[15]=(yy[0]-yy[2])/duasxA;
   b[16]=(xx[0]-xx[1])/duasxA;
   b[17]=(yy[1]-yy[0])/duasxA;
}
void elemento2D3N::monta_c()
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
}
void elemento2D3N::monta_rigidez()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      xx[3],yy[3],Volume;
   xx[0]=this->pno[0]->qx(0);
   xx[1]=this->pno[1]->qx(0);
   xx[2]=this->pno[2]->qx(0);
   yy[0]=this->pno[0]->qx(1);
   yy[1]=this->pno[1]->qx(1);
   yy[2]=this->pno[2]->qx(1);
   Volume=prop[0]*((xx[1]*yy[2]-xx[2]*yy[1])+(xx[2]*yy[0]-xx[0]*yy[2])+(xx[0]*yy[1]-xx[1]*yy[0]))/2.0;
   for (int i=0;i<6;i++)
      for (int j=0;j<6;j++)
         k[6*i+j]=0.0;
   monta_b();
   monta_c();
   for (int i=0;i<6;i++)
      for (int j=0;j<3;j++)
         for (int l=0;l<3;l++)
            for (int m=0;m<6;m++)
               k[6*i+m]+=b[6*j+i]*c[3*j+l]*b[6*l+m]*Volume;
}

