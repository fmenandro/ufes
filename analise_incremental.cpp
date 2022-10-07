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
#include "analise_incremental.h"

analise_incremental::analise_incremental()
 : analise()
{
}

analise_incremental::analise_incremental(ifstream& ci, ofstream& co)
 : analise()
{
//   ci>>this;
   ndof=this->nn*this->elementos[0]->qipn();
   ci>>ncci;
   nci= new int[this->ncci];
   for (int k=0;k<ncci;k++)
   {
      ci>>nci[k];
      cci[k]=new class c_contorno*[nci[k]];
      for (int i=0;i<nci[k];i++)
      {
         int tipo;
         ci>>tipo;
         switch(tipo)
         {
            case 0: cci[k][i]=new class apoio; break;
            case 1: cci[k][i]=new class deslocamento; break;
            case 2: cci[k][i]=new class forca; break;
            case 3: cci[k][i]=new class multipla; break;
            case 4: ci>>tipo; cci[k][i]=new class multipla(tipo); break;
            case 5: cci[k][i]=new class mista; break;
            case 6: ci>>tipo; cci[k][i]=new class mista(tipo); break;
         }
         ci>>*cci[k][i];
      }
   }
   ci>>dt;
   ci>>npa;
#ifdef ALEATORIO
      fc = new aleatorio[this->ncci*this->npa];
#else
      fc = new double[this->ncci*this->npa];
#endif
   for (int k=0;k<ncci;k++)
   {
      int tipo;
      ci>>tipo;
      int j,nt=0;
      switch(tipo)
      {
         case 0:
            for (int i=0;i<npa;i++)
               ci>>fc[k*npa+i];
            break;
         case 1:
            ci>>fc[k*npa];
            for (int i=1;i<npa;i++)
            {
               ci>>fc[k*npa+i];
               for (int j=0;j<i;j++)
                  fc[k*npa+i]-=fc[k*npa+j];
            }
            break;
         case 2:
            ci>>j;
            for (int jj=0;jj<j;jj++)
            {
#ifdef ALEATORIO
               class aleatorio
#else
               double
#endif
                  a,b;
               int n;
               ci>>n;
               ci>>a>>b;
               if (nt+n>npa)
                  n=npa-nt;
               for (int i=0;i<n;i++)
               {
                  fc[k*npa+i+nt]=a+b*i;
               }
               nt+=n;
            }
            for (int i=1;i<npa;i++)
            {
               for (int j=0;j<i;j++)
                  fc[k*npa+i]-=fc[k*npa+j];
            }
            break;
         case 3:
            ci>>j;
            for (int jj=0;jj<j;jj++)
            {
#ifdef ALEATORIO
               class aleatorio
#else
               double
#endif
                  a,b;
               int n;
               ci>>n;
               ci>>a>>b;
               if (nt+n>npa)
                  n=npa-nt;
               for (int i=0;i<n;i++)
               {
                  fc[k*npa+i+nt]=a+b*i;
               }
               nt+=n;
            }
            break;
      }
   }
#ifdef ALEATORIO
   x = new aleatorio[this->ndof];
   f = new aleatorio[this->ndof];
   xt = new aleatorio[this->ndof];
   ft = new aleatorio[this->ndof];
   xp = new aleatorio[this->ndof];
   fp = new aleatorio[this->ndof];
   K = new aleatorio[this->ndof*this->ndof];
#else
   x = new double[this->ndof];
   f = new double[this->ndof];
   xt = new double[this->ndof];
   ft = new double[this->ndof];
   xp = new double[this->ndof];
   fp = new double[this->ndof];
   K = new double[this->ndof*this->ndof];
#endif
   t=0;
   for (int i=0;i<ndof;i++)
   {
      xt[i]=x[i]=0.0;
      ft[i]=f[i]=0.0;
   }
   for (int i=0;i<npa;i++)
   {
      t+=dt;
      for (int k=0;k<ndof;k++)
      {
         xp[k]=x[k]=0.0;
         fp[k]=f[k]=0.0;
      }
      montaK();
      impoeCC(i);
      do
      {
         for (int k=0;k<ndof;k++)
         {
            f[k]-=fp[k];
         }
         resolve();
         posprocessa();
         for (int k=0;k<ndof;k++)
         {
            xp[k]+=x[k];
            fp[k]+=f[k];
         }
         montaK();
         impoeCC();
      } while(testa_iteracao());
      for (int k=0;k<ndof;k++)
      {
         xt[k]+=xp[k];
         ft[k]+=fp[k];
         x[k]=xt[k];
         f[k]=ft[k];
      }
      co<<"\n\nPasso "<<i<<"\n t = "<<t;
      cout<<"\n\nPasso "<<i<<"\n t = "<<t;
      co<<*this;
      co<<"\nNumero de conjuntos de CC incrementais:  "<<ncci;
      for (int k=0;k<ncci;k++)
      {
         co<<"\n\nConjunto  "<<k<<"\n Numero de CC:  "<<nci[k]<<"\n";
         for (int i=0;i<nci[k];i++)
            co<<*cci[k][i]<<"\n";
      }
      co<<"\n\nIntervalo de Passo = "<<dt<<"\nNumero de passos = "<<npa;
      co<<"\n\nFator de carga:\n Passo ";
      for (int k=0;k<ncci;k++)
         co<<" Conjunto "<<k;
      for (int i=0;i<npa;i++)
      {
         co<<"\n   "<<i<<"   ";
         for (int k=0;k<ncci;k++)
            co<<"      "<<fc[k*npa+i];
      }
      cout<<*this;
   }
}
analise_incremental::analise_incremental(wxTextInputStream& ci, wxTextOutputStream& co)
 : analise()
{
   ci>>*this;
   ndof=this->nn*this->elementos[0]->qipn();
   ci>>ncci;
   nci= new int[this->ncci];
   for (int k=0;k<ncci;k++)
   {
      ci>>nci[k];
      cci[k]=new class c_contorno*[nci[k]];
      for (int i=0;i<nci[k];i++)
      {
         int tipo;
         ci>>tipo;
         switch(tipo)
         {
            case 0: cci[k][i]=new class apoio; break;
            case 1: cci[k][i]=new class deslocamento; break;
            case 2: cci[k][i]=new class forca; break;
            case 3: cci[k][i]=new class multipla; break;
            case 4: ci>>tipo; cci[k][i]=new class multipla(tipo); break;
            case 5: cci[k][i]=new class mista; break;
            case 6: ci>>tipo; cci[k][i]=new class mista(tipo); break;
         }
         ci>>*cci[k][i];
      }
   }
   ci>>dt;
   ci>>npa;
#ifdef ALEATORIO
      fc = new aleatorio[this->ncci*this->npa];
#else
      fc = new double[this->ncci*this->npa];
#endif
   for (int k=0;k<ncci;k++)
   {
      int tipo;
      ci>>tipo;
      int j,nt=0;
      switch(tipo)
      {
         case 0:
            for (int i=0;i<npa;i++)
               ci>>fc[k*npa+i];
            break;
         case 1:
            ci>>fc[k*npa];
            for (int i=1;i<npa;i++)
            {
               ci>>fc[k*npa+i];
               for (int j=0;j<i;j++)
                  fc[k*npa+i]-=fc[k*npa+j];
            }
            break;
         case 2:
            ci>>j;
            for (int jj=0;jj<j;jj++)
            {
#ifdef ALEATORIO
               class aleatorio
#else
               double
#endif
                  a,b;
               int n;
               ci>>n;
               ci>>a>>b;
               if (nt+n>npa)
                  n=npa-nt;
               for (int i=0;i<n;i++)
               {
                  fc[k*npa+i+nt]=a+b*i;
               }
               nt+=n;
            }
            for (int i=1;i<npa;i++)
            {
               for (int j=0;j<i;j++)
                  fc[k*npa+i]-=fc[k*npa+j];
            }
            break;
         case 3:
            ci>>j;
            for (int jj=0;jj<j;jj++)
            {
#ifdef ALEATORIO
               class aleatorio
#else
               double
#endif
                  a,b;
               int n;
               ci>>n;
               ci>>a>>b;
               if (nt+n>npa)
                  n=npa-nt;
               for (int i=0;i<n;i++)
               {
                  fc[k*npa+i+nt]=a+b*i;
               }
               nt+=n;
            }
            break;
      }
   }
#ifdef ALEATORIO
   x = new aleatorio[this->ndof];
   f = new aleatorio[this->ndof];
   xt = new aleatorio[this->ndof];
   ft = new aleatorio[this->ndof];
   xp = new aleatorio[this->ndof];
   fp = new aleatorio[this->ndof];
   K = new aleatorio[this->ndof*this->ndof];
#else
   x = new double[this->ndof];
   f = new double[this->ndof];
   xt = new double[this->ndof];
   ft = new double[this->ndof];
   xp = new double[this->ndof];
   fp = new double[this->ndof];
   K = new double[this->ndof*this->ndof];
#endif
   t=0;
   for (int i=0;i<ndof;i++)
   {
      xt[i]=x[i]=0.0;
      ft[i]=f[i]=0.0;
   }
   for (int i=0;i<npa;i++)
   {
      t+=dt;
      for (int k=0;k<ndof;k++)
      {
         xp[k]=x[k]=0.0;
         fp[k]=f[k]=0.0;
      }
      montaK();
      impoeCC(i);
      do
      {
         for (int k=0;k<ndof;k++)
         {
            f[k]-=fp[k];
         }
         resolve();
         posprocessa();
         for (int k=0;k<ndof;k++)
         {
            xp[k]+=x[k];
            fp[k]+=f[k];
         }
         montaK();
         impoeCC();
      } while(testa_iteracao());
      for (int k=0;k<ndof;k++)
      {
         xt[k]+=xp[k];
         ft[k]+=fp[k];
         x[k]=xt[k];
         f[k]=ft[k];
      }
      co<<"\n\nPasso "<<i<<"\n t = "<<t;
      cout<<"\n\nPasso "<<i<<"\n t = "<<t;
      co<<*this;
      co<<"\nNumero de conjuntos de CC incrementais:  "<<ncci;
      for (int k=0;k<ncci;k++)
      {
         co<<"\n\nConjunto  "<<k<<"\n Numero de CC:  "<<nci[k]<<"\n";
         for (int i=0;i<nci[k];i++)
            co<<*cci[k][i]<<"\n";
      }
      co<<"\n\nIntervalo de Passo = "<<dt<<"\nNumero de passos = "<<npa;
      co<<"\n\nFator de carga:\n Passo ";
      for (int k=0;k<ncci;k++)
         co<<" Conjunto "<<k;
      for (int i=0;i<npa;i++)
      {
         co<<"\n   "<<i<<"   ";
         for (int k=0;k<ncci;k++)
            co<<"      "<<fc[k*npa+i];
      }
      cout<<*this;
   }
}

void analise_incremental::impoeCC(int i)
{
   for (int c=0;c<nc;c++)
   {
      if(!strcmp(cc[c]->qtipo(),"Forca"))
         cc[c]->impor(K,f,ndof/nn,ndof);
   }
   for (int k=0;k<ncci;k++)
   {
      for (int c=0;c<nci[k];c++)
      {
         if(!strcmp(cci[k][c]->qtipo(),"Forca"))
            cci[k][c]->impor(K,f,ndof/nn,ndof,fc[k*npa+i]);
      }
   }
   for (int k=0;k<ncci;k++)
   {
      for (int c=0;c<nci[k];c++)
      {
         if(strcmp(cci[k][c]->qtipo(),"Forca"))
            cci[k][c]->impor(K,f,ndof/nn,ndof,fc[k*npa+i]);
      }
   }
   for (int c=0;c<nc;c++)
   {
      if(strcmp(cc[c]->qtipo(),"Forca"))
         cc[c]->impor(K,f,ndof/nn,ndof);
   }
}
void analise_incremental::impoeCC()
{
   for (int c=0;c<nc;c++)
   {
      if(!strcmp(cc[c]->qtipo(),"Forca"))
         cc[c]->impor(K,f,ndof/nn,ndof,0.0);
   }
   for (int k=0;k<ncci;k++)
   {
      for (int c=0;c<nci[k];c++)
      {
         if(!strcmp(cci[k][c]->qtipo(),"Forca"))
            cci[k][c]->impor(K,f,ndof/nn,ndof,0.0);
      }
   }
}

bool analise_incremental::testa_iteracao()
{
#ifdef ALEATORIO
   class aleatorio
#else
   double
#endif
   residuo,total;
   residuo=total=0.0;
   for (int k=0;k<ndof;k++)
   {
      residuo+=f[k]-fp[k];
   }
   for (int c=0;c<nc;c++)
   {
      if(strcmp(cc[c]->qtipo(),"Forca"))
         total+=cc[c]->valor[0];
      if(strcmp(cc[c]->qtipo(),"Deslocamento"))
      {
         int t=cc[c]->no[0]*ndof/nn+cc[c]->gl[0];
         total+=cc[c]->valor[0]/K[qpos(t,t)];
      }
   }
   for (int k=0;k<ncci;k++)
   {
      for (int c=0;c<nci[k];c++)
      {
         if(strcmp(cci[k][c]->qtipo(),"Forca"))
            total+=cci[k][c]->valor[0];
         if(strcmp(cci[k][c]->qtipo(),"Deslocamento"))
         {
            int t=cci[k][c]->no[0]*ndof/nn+cci[k][c]->gl[0];
            total+=cci[k][c]->valor[0]/K[qpos(t,t)];
         }
      }
   }
   return(residuo/total>tolerancia);
}

analise_incremental::~analise_incremental()
{
   delete fc;
   delete nci;
   delete cci;
}


