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
#include "iscal2d.h"

iscal2d::iscal2d(int nno,int ptg)
 : elemento(dim,ipn,nno,prp,ptg,nlb)
{
#ifdef ALEATORIO
   N = new class aleatorio[nno];
   dn = new class aleatorio[nno*2];
   dN = new class aleatorio[nno*2];
   xg = new class aleatorio[dim];
   wg = new class aleatorio[dim];
   m = new class aleatorio[nno*nno];
#else
   N = new double[nno];
   dn = new double[nno*2];
   dN = new double[nno*2];
   xg = new double[dim];
   wg = new double[dim];
   m = new double[nno*nno];
#endif
   detJ=0.0;
};


iscal2d::~iscal2d()
{
};

#ifdef ALEATORIO
class aleatorio iscal2d::qm(int i, int j)
#else
double iscal2d::qm(int i, int j)
#endif
{
   return(this->m[qpos(i,j)]);
};
void iscal2d::monta_b()
{
   monta_n();
   for (int i=0;i<qnno();i++)
   {
      b[(i)]=dN[i*2];
      b[qnno()+i]=dN[i*2+1];
   }
};
void iscal2d::monta_c()
{
   for (int i=0;i<qnlb()*qnlb();i++)
      c[i]=0.0;
   c[0]=pmaterial->qK();
   c[3]=pmaterial->qK();
};
void iscal2d::monta_rigidez()
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
   for (int pg=0;pg<qdim()*qptg();pg++)
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
void iscal2d::monta_n(){};
void iscal2d::monta_massa()
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
         this->m[qnno()*qipn()*i+j]=0.0;
   pontos_de_gauss(qptg(),xpg,wpg);
   for (int pg=0;pg<qdim()*qptg();pg++)
   {
      monta_n();
      for (int i=0;i<qnno()*qipn();i++)
      {
         for (int j=0;j<qnno()*qipn();j++)
         {
            int I=i/qipn();
            int J=j/qipn();
            m[qnno()*qipn()*i+j]+=N[I]*N[J]*peso;
         }
      }
   }
};
