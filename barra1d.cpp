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
#include "barra1d.h"



Barra1D::Barra1D():elemento(dim,ipn,nno,prp,ptg,nlb)
{
}

Barra1D::~Barra1D()
{
   this->elemento::~elemento();
}

void Barra1D::monta_rigidez()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
       E,A,L,x0,x1,dx,h;
   E=this->pmaterial->qE();
   A=this->prop[0];
   x0=this->pno[0]->qx(0);
   x1=this->pno[1]->qx(0);
   dx=x1-x0;
   h=dx*dx;
#ifdef ALEATORIO
   L=h.asqrt();
#else
   L=sqrt(h);
#endif
   k[0]=k[3]=E*A/L;
   k[1]=k[2]=-E*A/L;
}
void Barra1D::monta_b()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
       L,x0,x1,dx,h,um=1.0;
   x0=this->pno[0]->qx(0);
   x1=this->pno[1]->qx(0);
   dx=x1-x0;
   h=dx*dx;
#ifdef ALEATORIO
   L=h.asqrt();
#else
   L=sqrt(h);
#endif
   b[1]=um/L;
   b[0]=-b[1];
}
void Barra1D::monta_c()
{
   c[0]=pmaterial->qE()*prop[0];
}
