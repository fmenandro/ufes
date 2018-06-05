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
#include "analise_termica.h"

analise_termica::analise_termica()
 : analise()
{
}


analise_termica::analise_termica(ifstream& ci,ofstream& co)
 : analise()
{
   teta=0.5;
 //  ci>>this;
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
   M = new aleatorio[this->ndof*this->ndof];
   KK = new aleatorio[this->ndof*this->ndof];
   MM = new aleatorio[this->ndof*this->ndof];
#else
   x = new double[this->ndof];
   f = new double[this->ndof];
   xt = new double[this->ndof];
   ft = new double[this->ndof];
   xp = new double[this->ndof];
   fp = new double[this->ndof];
   K = new double[this->ndof*this->ndof];
   M = new double[this->ndof*this->ndof];
   KK = new double[this->ndof*this->ndof];
   MM = new double[this->ndof*this->ndof];
#endif
   if (dt==0.0)
   {
      for (int i=0;i<ndof;i++)
	     ci>>ft[i];
	  for (int i=0;i<ndof*ndof;i++)
         K[i]=M[i]=0.0;
      for (int i=0;i<ndof;i++)
      {
         x[i]=0.0;
         f[i]=0.0;
      }
      montaK();
      impoeCC(0);
      resolve();
      montaK();
      posprocessa();
      cout<<*this;
   }
   else
   {
      t=0;
      for (int i=0;i<ndof*ndof;i++)
         K[i]=M[i]=KK[i]=MM[i]=0.0;
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
         for (int m=0;m<ndof;m++)
            for (int n=0;n<ndof;n++)
            {
               int mn=qpos(m,n);
               KK[mn]=K[mn];
               MM[mn]=M[mn];
               K[mn]=MM[mn]+teta*dt*KK[mn];
               M[mn]=MM[mn]-(1.0-teta)*dt*KK[mn];
            }
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
            for (int m=0;m<ndof;m++)
               for (int n=0;n<ndof;n++)
               {
                  int mn=qpos(m,n);
                  KK[mn]=K[mn];
                  MM[mn]=M[mn];
                  K[mn]=MM[mn]+teta*dt*KK[mn];
                  M[mn]=MM[mn]-(1.0-teta)*dt*KK[mn];
               }
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
}
analise_termica::analise_termica(wxTextInputStream& ci)
	:analise()
{}
wxTextInputStream& operator>>(wxTextInputStream& ci, analise_termica& n)
{
  ci>>n.nn>>n.ne>>n.nm>>n.nc;
   n.fn=n.fe=n.fcc=1;
   n.fnn=n.fne=n.fnc=n.fnm=0;
  n.materiais=new class material*[n.nm];
  for (int i=0;i<n.nm;i++)
  {
     int tipo;
     ci>>tipo;
     switch(tipo)
     {
        case 0:
           n.materiais[i]=new class mat_termico;
	   break;
        case 1:
           n.materiais[i]=new class mat_linear_elastico;
	   break;
        case 2:
           n.materiais[i]=new class mat_termico_nao_linear;
	   break;
     }
     ci>>*n.materiais[i];
  }
  n.nos=new class no*[n.nn];
  for (int i=0;i<n.nn;i++)
  {
     int tipo;
     ci>>tipo;
     switch(tipo)
     {
        case 1:
           n.nos[i]=new class no1D;
	   break;
        case 2:
           n.nos[i]=new class no2D;
	   break;
        case 3:
           n.nos[i]=new class no3D;
     }
     ci>>*n.nos[i];
  }
  n.elementos=new class elemento*[n.ne];
  for (int i=0;i<n.ne;i++)
  {
     int tipo;
     ci>>tipo;
     switch(tipo)
     {
        case 1:
           n.elementos[i]=new class Barra1D;
           break;
        case 2:
           n.elementos[i]=new class Barra2D;
           break;
	case 3:
	   n.elementos[i]=new class Viga2D;
           break;
	case 4:
	   n.elementos[i]=new class Barra3D;
	   break;
        case 5:
           n.elementos[i]=new class elemento2D3N;
	   break;
        case 6:
           n.elementos[i]=new class elemento2D4N;
           break;
        case 7:
           n.elementos[i]=new class Viga3D;
           break;
        case 8:
           n.elementos[i]=new class elemento2D8N;
           break;
        case 9:
           n.elementos[i]=new class elemento2D9N;
           break;
        case 10:
           n.elementos[i]=new class Tubo;
           break;
        case 11:
           n.elementos[i]=new class elcal2d4n;
           break;
        case 12:
           n.elementos[i]=new class nlcal2d4n;
           break;
        case 13:
           n.elementos[i]=new class elcal1d2n;
     }
     ci>>*n.elementos[i];
     n.elementos[i]->aponta_mat(n.materiais[n.elementos[i]->qmat()]);
     for(int j=0;j<n.elementos[i]->qnno();j++)
        n.elementos[i]->aponta_no(j,n.nos[n.elementos[i]->qno(j)]);
  }
  n.cc=new class c_contorno*[n.nc];
  for (int i=0;i<n.nc;i++)
  {
     int tipo;
     ci>>tipo;
     switch(tipo)
     {
 	case 0: n.cc[i]=new class apoio; break;
 	case 1: n.cc[i]=new class deslocamento; break;
	case 2: n.cc[i]=new class forca; break;
        case 3: n.cc[i]=new class multipla; break;
        case 4: ci>>tipo; n.cc[i]=new class multipla(tipo); break;
        case 5: n.cc[i]=new class mista; break;
        case 6: ci>>tipo; n.cc[i]=new class mista(tipo); break;
     }
     ci>>*n.cc[i];
       for(int j=0;j<n.cc[i]->qnno();j++)
        n.cc[i]->aponta_no(j,n.nos[n.cc[i]->qno(j)]);
}
  n.ndof=n.nn*n.elementos[0]->qipn();
  #ifdef ALEATORIO
   n.x = new aleatorio[n.ndof];
   n.f = new aleatorio[n.ndof];
   n.K = new aleatorio[n.ndof*n.ndof];
#else
   n.x = new double[n.ndof];
   n.f = new double[n.ndof];
   n.K = new double[n.ndof*n.ndof];
#endif
for (int i=0;i<n.ndof;i++)
  {
      n.x[i]=n.f[i]=0.0;
  }
  for (int i=0;i<n.ndof*n.ndof;i++)
  {
      n.K[i]=0.0;
  }
   n.teta=0.5;
   n.ndof=n.nn*n.elementos[0]->qipn();
   ci>>n.ncci;
   n.nci= new int[n.ncci];
   for (int k=0;k<n.ncci;k++)
   {
      ci>>n.nci[k];
      n.cci[k]=new class c_contorno*[n.nci[k]];
      for (int i=0;i<n.nci[k];i++)
      {
         int tipo;
         ci>>tipo;
         switch(tipo)
         {
		    case 0: n.cci[k][i]=new class apoio; break;
            case 1: n.cci[k][i]=new class deslocamento; break;
            case 2: n.cci[k][i]=new class forca; break;
            case 3: n.cci[k][i]=new class multipla; break;
            case 4: ci>>tipo; n.cci[k][i]=new class multipla(tipo); break;
            case 5: n.cci[k][i]=new class mista; break;
            case 6: ci>>tipo; n.cci[k][i]=new class mista(tipo); break;
         }
         ci>>*n.cci[k][i];
      }
   }
   ci>>n.dt;
   ci>>n.npa;
#ifdef ALEATORIO
      n.fc = new aleatorio[n.ncci*n.npa];
#else
      n.fc = new double[n.ncci*n.npa];
#endif
   for (int k=0;k<n.ncci;k++)
   {
      int tipo;
      ci>>tipo;
      int j,nt=0;
      switch(tipo)
      {
         case 0:
            for (int i=0;i<n.npa;i++)
               ci>>n.fc[k*n.npa+i];
            break;
         case 1:
            ci>>n.fc[k*n.npa];
            for (int i=1;i<n.npa;i++)
            {
               ci>>n.fc[k*n.npa+i];
               for (int j=0;j<i;j++)
                  n.fc[k*n.npa+i]-=n.fc[k*n.npa+j];
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
               int nnn;
               ci>>nnn;
               ci>>a>>b;
               if (nt+nnn>n.npa)
                  nnn=n.npa-nt;
               for (int i=0;i<nnn;i++)
               {
                  n.fc[k*n.npa+i+nt]=a+b*i;
               }
               nt+=nnn;
            }
            for (int i=1;i<n.npa;i++)
            {
               for (int j=0;j<i;j++)
                  n.fc[k*n.npa+i]-=n.fc[k*n.npa+j];
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
               int nnn;
               ci>>nnn;
               ci>>a>>b;
               if (nt+nnn>n.npa)
                  nnn=n.npa-nt;
               for (int i=0;i<nnn;i++)
               {
                  n.fc[k*n.npa+i+nt]=a+b*i;
               }
               nt+=nnn;
            }
            break;/*
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
   M = new aleatorio[this->ndof*this->ndof];
   KK = new aleatorio[this->ndof*this->ndof];
   MM = new aleatorio[this->ndof*this->ndof];
#else
   x = new double[this->ndof];
   f = new double[this->ndof];
   xt = new double[this->ndof];
   ft = new double[this->ndof];
   xp = new double[this->ndof];
   fp = new double[this->ndof];
   K = new double[this->ndof*this->ndof];
   M = new double[this->ndof*this->ndof];
   KK = new double[this->ndof*this->ndof];
   MM = new double[this->ndof*this->ndof];
#endif
   if (dt==0.0)
   {
      for (int i=0;i<ndof;i++)
	     ci>>ft[i];
	  for (int i=0;i<ndof*ndof;i++)
         K[i]=M[i]=0.0;
      for (int i=0;i<ndof;i++)
      {
         x[i]=0.0;
         f[i]=0.0;
      }
      montaK();
      impoeCC(0);
      resolve();
      montaK();
      posprocessa();
      cout<<*this;
   }
   else
   {
      t=0;
      for (int i=0;i<ndof*ndof;i++)
         K[i]=M[i]=KK[i]=MM[i]=0.0;
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
         for (int m=0;m<ndof;m++)
            for (int n=0;n<ndof;n++)
            {
               int mn=qpos(m,n);
               KK[mn]=K[mn];
               MM[mn]=M[mn];
               K[mn]=MM[mn]+teta*dt*KK[mn];
               M[mn]=MM[mn]-(1.0-teta)*dt*KK[mn];
            }
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
            for (int m=0;m<ndof;m++)
               for (int n=0;n<ndof;n++)
               {
                  int mn=qpos(m,n);
                  KK[mn]=K[mn];
                  MM[mn]=M[mn];
                  K[mn]=MM[mn]+teta*dt*KK[mn];
                  M[mn]=MM[mn]-(1.0-teta)*dt*KK[mn];
               }
            impoeCC();
         } while(testa_iteracao());
         for (int k=0;k<ndof;k++)
         {
            xt[k]+=xp[k];
            ft[k]+=fp[k];
            x[k]=xt[k];
            f[k]=ft[k];
         }
/*         co<<"\n\nPasso "<<i<<"\n t = "<<t;
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
         cout<<*this;*/
      }
   }
   if (n.dt==0.0)
   {
         for (int i=0;i<n.ndof;i++)
	     ci>>n.ft[i];
   }
   return ci;
}
void analise_termica::impoeCC(int i)
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
   if (dt==0.0)
   {
      for (int k=0;k<ndof;k++)
         for (int c=0;c<ndof;c++)
            f[k]+=M[qpos(k,c)]*ft[c];
   }
   for (int k=0;k<ncci;k++)
   {
      for (int c=0;c<nci[k];c++)
      {
         if(strcmp(cci[k][c]->qtipo(),"Forca"))
            cci[k][c]->impor(K,f,ndof/nn,ndof,fc[k*npa+i]*dt);
      }
   }
   if (dt==0.0)
   {
      for (int c=0;c<nc;c++)
      {
         if(strcmp(cc[c]->qtipo(),"Forca"))
            cc[c]->impor(K,f,ndof/nn,ndof);
      }
   }
   else
   {
      for (int c=0;c<nc;c++)
      {
         if(strcmp(cc[c]->qtipo(),"Forca"))
            cc[c]->impor(K,f,ndof/nn,ndof,dt);
      }
      for (int k=0;k<ndof;k++)
         for (int c=0;c<ndof;c++)
            f[k]+=M[qpos(k,c)]*x[c];
   }
}
void analise_termica::impoeCC()
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

bool analise_termica::testa_iteracao()
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
void analise_termica::montaK()
{
   for (int e=0;e<ne;e++)
   {
      class elemento *el=elementos[e];
      int I=el->qipn();
//	  if ((materiais[el->qmat()])->qtipo()=="Termico Nao Linear") el->p_processa(x);
	  el->p_processa(x);
	  el->monta_rigidez();
      el->monta_massa();
      for (int in=0;in<el->qnno();in++)
         for (int jn=0;jn<el->qnno();jn++)
            for (int ii=0;ii<I;ii++)
               for (int ji=0;ji<I;ji++)
               {
	          this->K[qpos(el->qno(in)*I+ii,el->qno(jn)*I+ji)]+=el->qk(in*I+ii,jn*I+ji);
	          this->M[qpos(el->qno(in)*I+ii,el->qno(jn)*I+ji)]+=el->qm(in*I+ii,jn*I+ji);
               }
   }
}

analise_termica::~analise_termica()
{
   delete fc;
   delete nci;
   delete cci;
}
double analise_termica::qdt()
{
	return dt;
}
void analise_termica::upft(int i, double v)
{
	ft[i]=v;
}
void analise_termica::upM(int i, double v)
{
	M[i]=v;
}
void analise_termica::roda()
{
	   if (dt==0.0)
   {
	  for (int i=0;i<ndof*ndof;i++)
      {
		  K[i]=M[i]=0.0;
	  }
      for (int i=0;i<ndof;i++)
      {
         x[i]=0.0;
         f[i]=0.0;
      }
      montaK();
      impoeCC(0);
      resolve();
      montaK();
      posprocessa();
      cout<<*this;
   }
   else
   {
      t=0;
      for (int i=0;i<ndof*ndof;i++)
         K[i]=M[i]=KK[i]=MM[i]=0.0;
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
         for (int m=0;m<ndof;m++)
            for (int n=0;n<ndof;n++)
            {
               int mn=qpos(m,n);
               KK[mn]=K[mn];
               MM[mn]=M[mn];
               K[mn]=MM[mn]+teta*dt*KK[mn];
               M[mn]=MM[mn]-(1.0-teta)*dt*KK[mn];
            }
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
            for (int m=0;m<ndof;m++)
               for (int n=0;n<ndof;n++)
               {
                  int mn=qpos(m,n);
                  KK[mn]=K[mn];
                  MM[mn]=M[mn];
                  K[mn]=MM[mn]+teta*dt*KK[mn];
                  M[mn]=MM[mn]-(1.0-teta)*dt*KK[mn];
               }
            impoeCC();
         } while(testa_iteracao());
         for (int k=0;k<ndof;k++)
         {
            xt[k]+=xp[k];
            ft[k]+=fp[k];
            x[k]=xt[k];
            f[k]=ft[k];
         }
//         co<<"\n\nPasso "<<i<<"\n t = "<<t;
         cout<<"\n\nPasso "<<i<<"\n t = "<<t;
//         co<<*this;
//         co<<"\nNumero de conjuntos de CC incrementais:  "<<ncci;
/*         for (int k=0;k<ncci;k++)
         {
//            co<<"\n\nConjunto  "<<k<<"\n Numero de CC:  "<<nci[k]<<"\n";
            for (int i=0;i<nci[k];i++)
//               co<<*cci[k][i]<<"\n";
         }*/
//         co<<"\n\nIntervalo de Passo = "<<dt<<"\nNumero de passos = "<<npa;
//         co<<"\n\nFator de carga:\n Passo ";
/*         for (int k=0;k<ncci;k++)
//            co<<" Conjunto "<<k;
         for (int i=0;i<npa;i++)
         {
//            co<<"\n   "<<i<<"   ";
            for (int k=0;k<ncci;k++)
//               co<<"      "<<fc[k*npa+i];
         }
         cout<<*this;*/
      }
}
}