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
#include "analise.h"


// Funcoes membro da Classe analise

analise::analise()
{
   nn=ne=nm=nc=0;
   ro=rm=0.5;
   ch_lim=0.01;
   fn=fe=fcc=1;
   view[0]=1.;
   view[1]=0.;
   view[2]=0.;
   view[3]=0.;
   view[4]=1.;
   view[5]=0.;

/*  cin>>nn>>ne>>nm>>nd>>nf;

  nos=new no[nn];
  for (int i=0;i<nn;i++)
     cin>>nos[i];
  elementos=new elemento[ne];
  for (int i=0;i<ne;i++)
     cin>>elementos[i];
  materiais=new material[nm];
  for (int i=0;i<nm;i++)
     cin>>materiais[i];*/
};

analise::analise(ifstream& ci)
{
//   ci>>this;
   ndof=this->nn*this->elementos[0]->qipn();
#ifdef ALEATORIO
   x = new aleatorio[this->ndof];
   f = new aleatorio[this->ndof];
   K = new aleatorio[this->ndof*this->ndof];
#else
   x = new double[this->ndof];
   f = new double[this->ndof];
   K = new double[this->ndof*this->ndof];
#endif
   montaK();
/*   for(int ii=0;ii<ndof;ii++)
   {
      for(int jj=0;jj<ndof;jj++)
      {
         cout<<"      K["<<ii<<","<<jj<<"]="<<K[jj*ndof+ii];
      }
      cout<<"\n";
   }*/
   impoeCC();
/*   for(int ii=0;ii<ndof;ii++)
   {
      for(int jj=0;jj<ndof;jj++)
      {
         cout<<"      K["<<ii<<","<<jj<<"]="<<K[jj*ndof+ii];
      }
      cout<<"\n";
   }*/
   resolve();
/*   for(int ii=0;ii<ndof;ii++)
   {
      for(int jj=0;jj<ndof;jj++)
      {
         cout<<"      K["<<ii<<","<<jj<<"]="<<K[jj*ndof+ii];
      }
      cout<<"\n";
   }*/
   posprocessa();
}
analise::analise(wxTextInputStream& ci)
{
   ci>>*this;
   ndof=this->nn*this->elementos[0]->qipn();
#ifdef ALEATORIO
   x = new aleatorio[this->ndof];
   f = new aleatorio[this->ndof];
   K = new aleatorio[this->ndof*this->ndof];
#else
   x = new double[this->ndof];
   f = new double[this->ndof];
   K = new double[this->ndof*this->ndof];
#endif
//   montaK();
//   impoeCC();
//   resolve();
};

analise::~analise()
{
   delete nos;
   delete elementos;
//   delete materiais;
   delete cc;
   delete x;
   delete f;
   delete K;
}

ostream& operator<<(ostream& co, analise& a)
{
  co<<"\nNumero de nos = "<<a.nn<<"\n\n";
  for (int i=0;i<a.nn;i++)
    co<<"\nNo "<<i<<":     "<<*a.nos[i]<<"\n";
  co<<"\nNumero de elementos = "<<a.ne<<"\n\n";
  for (int i=0;i<a.ne;i++)
    co<<"\nElemento "<<i<<":\n"<<*a.elementos[i]<<"\n";
  co<<"\nNumero de materiais = "<<a.nm<<"\n\n";
  for (int i=0;i<a.nm;i++)
    co<<"\nMaterial "<<i<<":\n"<<*a.materiais[i]<<"\n";
  co<<"\nNumero de Condicoes de Contorno = "<<a.nc<<"\n\n";
  for (int i=0;i<a.nc;i++)
    co<<"\nCondicao de contorno "<<i<<":\n"<<*a.cc[i]<<"\n";
  co<<"\nMatriz de Rigidez = \n\n";
  for (int i=0;i<a.ndof;i++)
  {
     for (int j=0;j<a.ndof;j++)
        co<<"\t"<<a.K[a.qpos(i,j)]<<"     ";
     co<<"\n";
  }
  co<<"\nVetor de forcas = \n\n";
  for (int i=0;i<a.ndof;i++)
     co<<"f["<<i<<"]="<<a.f[i]<<"\n";
  co<<"\nVetor de deslocamentos resultantes = \n\n";
  for (int i=0;i<a.ndof;i++)
     co<<"u["<<i<<"]="<<a.x[i]<<"\n";
  return co;
}
wxTextOutputStream& operator<<(wxTextOutputStream& co, analise& a)
{
  co<<"\nNumero de nos = "<<a.nn<<"\n\n";
  for (int i=0;i<a.nn;i++)
    co<<"\nNo "<<i<<":     "<<*a.nos[i]<<"\n";
  co<<"\nNumero de elementos = "<<a.ne<<"\n\n";
  for (int i=0;i<a.ne;i++)
    co<<"\nElemento "<<i<<":\n"<<*a.elementos[i]<<"\n";
  co<<"\nNumero de materiais = "<<a.nm<<"\n\n";
  for (int i=0;i<a.nm;i++)
    co<<"\nMaterial "<<i<<":\n"<<*a.materiais[i]<<"\n";
  co<<"\nNumero de Condicoes de Contorno = "<<a.nc<<"\n\n";
  for (int i=0;i<a.nc;i++)
    co<<"\nCondicao de contorno "<<i<<":\n"<<*a.cc[i]<<"\n";
  co<<"\nMatriz de Rigidez = \n\n";
  for (int i=0;i<a.ndof;i++)
  {
     for (int j=0;j<a.ndof;j++)
        co<<"\t"<<a.K[a.qpos(i,j)]<<"     ";
     co<<"\n";
  }
  co<<"\nVetor de forcas = \n\n";
  for (int i=0;i<a.ndof;i++)
     co<<"f["<<i<<"]="<<a.f[i]<<"\n";
  co<<"\nVetor de deslocamentos resultantes = \n\n";
  for (int i=0;i<a.ndof;i++)
     co<<"u["<<i<<"]="<<a.x[i]<<"\n";
  return co;
}

istream& operator>>(istream& ci, analise& n)
{
  ci>>n.nn>>n.ne>>n.nm>>n.nc;
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
           ci>>*n.nos[i];
	   break;
        case 2:
           n.nos[i]=new class no2D;
           ci>>*n.nos[i];
	   break;
        case 3:
           n.nos[i]=new class no3D;
           ci>>*n.nos[i];
	   break;
        case 4:
            int nx,ny;
            ci>>nx>>ny;
            for(int j=0;j<=nx+1;j++)
                for(int k=0;k<=ny+1;k++)
                {
                   n.nos[j*(ny+1)+k]=new class no2D;
                   double xx,yy;
                   ci>>xx>>yy;
                   char str[40];
                   ostringstream ost(str);
                   istringstream ist(str);
                   ost<<xx<<"  "<<yy;
                   ist>>*n.nos[i+j*(ny+1)+k];
                }
            i+=nx*ny;
     }
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
           break;
	case 14:
           n.elementos[i]=new class elcal2d8n;
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
   return ci;
}
wxTextInputStream& operator>>(wxTextInputStream& ci, analise& n)
{
  ci>>n.nn>>n.ne>>n.nm>>n.nc>>n.nccc;
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
           ci>>*n.nos[i];
	   break;
        case 2:
           n.nos[i]=new class no2D;
           ci>>*n.nos[i];
	   break;
        case 3:
           n.nos[i]=new class no3D;
           ci>>*n.nos[i];
	   break;
        case 4:
            int nx,ny;
            ci>>nx>>ny;
            double xx,yy,ix,iy;
            ci>>xx>>yy>>ix>>iy;
            for(int j=0;j<=nx;j++)
                for(int k=0;k<=ny;k++)
                {
                   int ii=i+j*(ny+1)+k;
                   n.nos[ii]=new class no2D;
                   char str[40];
                   sprintf(str,"%lf %lf",xx+j*ix,yy+k*iy);
                   istringstream ist(str,ios::in);
                   ist>>*n.nos[ii];
                }
            i+=(nx+1)*(ny+1);
     }
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
           break;
	case 14:
           n.elementos[i]=new class elcal2d8n;
           break;
	case 15:
           n.elementos[i]=new class elpol2D5N;
           break;
	case 16:
		n.elementos[i] = new class elpol2D6N;
		break;
	case 17:
		n.elementos[i] = new class elpol2D7N;
		break;
	case 18:
		n.elementos[i] = new class elpol2D8N;
		break;

        case 106:
            int nx,ny;
            ci>>nx>>ny;
            int mat,n1,n2,n3,n4;
            double prop;
            ci>>mat;
            ci>>n1>>n2>>n3>>n4;
            ci>>prop;
            for(int j=0;j<nx;j++)
                for(int k=0;k<ny;k++)
                {
                   int ii=i+j*ny+k;
                   n.elementos[ii]=new class elemento2D4N;
                   char str[100];
                   sprintf(str,"%d\n%d %d %d %d\n%lf",mat,n1+j*(ny+1)+k,n2+j*(ny+1)+k,
                                             n3+j*(ny+1)+k,n4+j*(ny+1)+k,prop);
                   istringstream ist(str,ios::in);
                   ist>>*n.elementos[ii];
                   n.elementos[ii]->aponta_mat(n.materiais[n.elementos[ii]->qmat()]);
                   for(int l=0;l<n.elementos[ii]->qnno();l++)
                      n.elementos[ii]->aponta_no(l,n.nos[n.elementos[ii]->qno(l)]);
                }
            i+=nx*ny;
     }
     if (tipo<100)
     {
     ci>>*n.elementos[i];
     n.elementos[i]->aponta_mat(n.materiais[n.elementos[i]->qmat()]);
     for(int j=0;j<n.elementos[i]->qnno();j++)
        n.elementos[i]->aponta_no(j,n.nos[n.elementos[i]->qno(j)]);
     }
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
  n.ccc=new int[n.nccc+1];
  n.ccc[n.nccc]=n.nc;
  for (int i=0;i<n.nccc;i++)
      ci>>n.ccc[i];
  n.ndof=n.nn*n.elementos[0]->qipn();
  #ifdef ALEATORIO
   n.x = new aleatorio[n.ndof*n.nccc];
   n.f = new aleatorio[n.ndof*n.nccc];
   n.K = new aleatorio[n.ndof*n.ndof];
#else
   n.x = new double[n.ndof*n.nccc];
   n.f = new double[n.ndof*n.nccc];
   n.K = new double[n.ndof*n.ndof];
#endif
for (int i=0;i<n.ndof*n.nccc;i++)
  {
      n.x[i]=n.f[i]=0.0;
  }
  for (int i=0;i<n.ndof*n.ndof;i++)
  {
      n.K[i]=0.0;
  }
   return ci;
}

void analise::montaK()
{
   for (int e=0;e<ne;e++)
   {
      class elemento *el=elementos[e];
      int I=el->qipn();
      el->monta_rigidez();
      for (int in=0;in<el->qnno();in++)
         for (int jn=0;jn<el->qnno();jn++)
            for (int ii=0;ii<I;ii++)
               for (int ji=0;ji<I;ji++)
	          this->K[qpos(el->qno(in)*I+ii,el->qno(jn)*I+ji)]+=el->qk(in*I+ii,jn*I+ji);
   }
}
void analise::zerar()
{
	for (int i=0;i<ndof;i++)
	{
		f[i]=x[i]=0.0;
		for (int j=0;j<ndof;j++)
			K[qpos(i,j)]=0.0;
	}
}
void analise::montaroK()
{
   for (int e=0;e<ne;e++)
   {
      class elemento *el=elementos[e];
      int I=el->qipn();
      el->monta_rigidez();
      for (int in=0;in<el->qnno();in++)
         for (int jn=0;jn<el->qnno();jn++)
            for (int ii=0;ii<I;ii++)
               for (int ji=0;ji<I;ji++)
	          this->K[qpos(el->qno(in)*I+ii,el->qno(jn)*I+ji)]+=el->qk(in*I+ii,jn*I+ji)*pow(el->qro(),el->qp());
   }
}
void analise::impoeCC()
{
   for (int lc=0;lc<nccc;lc++)
   {
      for (int c=0;c<ccc[0];c++)
      {
         if(!strcmp(cc[c]->qtipo(),"Forca"))
            cc[c]->impor(K,&f[lc*ndof],ndof/nn,ndof);
      }
      for (int c=0;c<ccc[0];c++)
      {
         if(strcmp(cc[c]->qtipo(),"Forca"))
            cc[c]->impor(K,&f[lc*ndof],ndof/nn,ndof);
      }
      for (int c=ccc[lc];c<ccc[lc+1];c++)
      {
         if(!strcmp(cc[c]->qtipo(),"Forca"))
            cc[c]->impor(K,&f[lc*ndof],ndof/nn,ndof);
      }
      for (int c=ccc[lc];c<ccc[lc+1];c++)
      {
      if(strcmp(cc[c]->qtipo(),"Forca"))
         cc[c]->impor(K,&f[lc*ndof],ndof/nn,ndof);
      }
   }

}
void analise::resolve()
/* Resolve um sistema de equacoes [K]{x} = {f},
   pelo metodo da eliminacao de Gauss */
{
   int i,j,k,kk,pivo;
#ifdef ALEATORIO
   aleatorio Kpivo, fator, a;
#else
   double Kpivo, fator;
#endif
   for(k=0;k<ndof*nccc;k++)
      x[k]=f[k];
   for(k=0;k<ndof-1;k++)
   {
#ifdef ALEATORIO
      Kpivo = Kpivo.aabs( K[qpos(k,k)] ) ;
      kk=k+1;
      pivo=k;
      for (i=kk;i<ndof;i++)
      {
         if (Kpivo.aabs(K[qpos(i,k)])>Kpivo)
         {
            Kpivo=Kpivo.aabs(K[qpos(i,k)]);
            pivo=i;
         }
      }
#else
      Kpivo = fabs( K[qpos(k,k)] ) ;
      kk=k+1;
      pivo=k;
      for (i=kk;i<ndof;i++)
      {
         if (fabs(K[qpos(i,k)])>Kpivo)
         {
            Kpivo=fabs(K[qpos(i,k)]);
            pivo=i;
         }
      }
#endif
      if (k!=pivo)
      {
         for (j=k;j<ndof;j++)
         {
            fator=K[qpos(k,j)];
            K[qpos(k,j)]=K[qpos(pivo,j)];
            K[qpos(pivo,j)]=fator;
         }
         for (int c=0;c<nccc;c++)
         {
            fator=x[k+c*ndof];
            x[k+c*ndof]=x[pivo+c*ndof];
            x[pivo+c*ndof]=fator;
         }
      }
#ifdef ALEATORIO
      if (Kpivo.aabs(Kpivo)<tolerancia)
#else
      if ((Kpivo*Kpivo)<double(tolerancia*tolerancia))
#endif
      {
         cout<<"O sistema e' singular! (analise 1)";
      }
      for (i=kk;i<ndof;i++)
      {
         fator = K[qpos(i,k)]/K[qpos(k,k)];
      	for (j=kk;j<ndof;j++)
         {
            K[qpos(i,j)] -= fator*K[qpos(k,j)];
         }
         for (int c=0;c<nccc;c++)
         {
            x[i+c*ndof] -= fator*x[k+c*ndof];
         }
      }
/*   if (k>=96)
{
   for(int ii=101;ii<117;ii++)
   {
      for(int jj=111;jj<117;jj++)
      {
         cout<<"      K["<<ii<<","<<jj<<"]="<<K[ii*ndof+jj];
      }
      cout<<"\n";
   }
   int pare=1;
}*/

   }
#ifdef ALEATORIO
      if (K[qpos(ndof-1,ndof-1)].aabs(K[qpos(ndof-1,ndof-1)])<tolerancia)
#else
   if ((K[qpos(ndof-1,ndof-1)]*K[qpos(ndof-1,ndof-1)])<double(tolerancia*tolerancia))
#endif
   {
      cout<<"O sistema e' singular! (analise 2)";
   }
   for (int c=0;c<nccc;c++)
   {   
   x[ndof-1+c*ndof] /= K[qpos(ndof-1,ndof-1)];
   for (i=ndof-2;i>=0;i--)
   {
      for (j=i+1;j<ndof;j++)
         x[i+c*ndof] -= x[j+c*ndof]*K[qpos(i,j)];
      x[i+c*ndof] /= K[qpos(i,i)];
   }
   }
}/* Fim de gauss */
double analise::ofsa()
{
   double c=0.0;
   for (int e=0;e<ne;e++)
   {
      class elemento *el=elementos[e];
      el->monta_rigidez();
      double ce=0.0;
      double dce=0.0;
      for(int c=0;c<nccc;c++)
      {
         el->p_processa(&x[c*ndof]);
         for(int i=0;i<el->qnno()*el->qipn();i++)
            for(int j=0;j<el->qnno()*el->qipn();j++)
               ce+=el->qx(i)*el->qk(i,j)*el->qx(j);
      }
      c+=pow(el->qro(),el->qp())*ce;
      el->updc(-el->qp()*pow(el->qro(),el->qp()-1.0)*ce);
   }
   return(c);
}
void analise::fs(double rmin)
{
   for (int e=0;e<ne;e++)
   {
      class elemento *el=elementos[e];
      double soma=0.0;
	  el->updcn(0.0);
      double x=0.0;
      double y=0.0;      
      for(int i=0;i<el->qnno();i++)
      {
          x+=nos[el->qno(i)]->qx(0);
          y+=nos[el->qno(i)]->qx(1);
      }
      x/=el->qnno();
      y/=el->qnno();
      for (int ee=0;ee<ne;ee++)
      {
         class elemento *ele=elementos[ee];
         double xe=0.0;
         double ye=0.0;      
         for(int i=0;i<ele->qnno();i++)
         {
            xe+=nos[ele->qno(i)]->qx(0);
            ye+=nos[ele->qno(i)]->qx(1);
         }
         xe/=ele->qnno();
         ye/=ele->qnno();
         double dist=sqrt((x-xe)*(x-xe)+(y-ye)*(y-ye));
         if (dist<rmin)
         {
            soma+=rmin-dist;
            el->updcn(el->qdcn()+(rmin-dist)*ele->qro()*ele->qdc());
         }
      }
/*      for (int ee=e+1;ee<ne;ee++)
      {
         class elemento *ele=elementos[ee];
         double xe=0.0;
         double ye=0.0;      
         for(int i=0;i<ele->qnno();i++)
         {
            xe+=nos[ele->qno(i)]->qx(0);
            ye+=nos[ele->qno(i)]->qx(1);
         }
         xe/=ele->qnno();
         ye/=ele->qnno();
         double dist=sqrt((x-xe)*(x-xe)+(y-ye)*(y-ye));
         if (dist<rmin)
         {
            soma+=rmin-dist;
            el->updcn(el->qdcn()+(rmin-dist)*ele->qro()*ele->qdc());
         }
      }*/
      el->updcn(el->qdcn()/(el->qro()*soma));
   }
}
double analise::oc()
{
    double li,lf,lm,passo,ch;
    li=0.0;
    lf=100000.0;
    double zeta=0.2;
    double volume=0.0;
    for(int e=0;e<ne;e++)
	{
		class elemento *el=elementos[e];
		el->uprov(el->qro());
                volume+=el->qvol();           
	}
    while (lf-li>1e-4)
    {
        double soma=0.0;
        lm=(li+lf)/2;
        for(int e=0;e<ne;e++)
        {
           class elemento *el=elementos[e];
           double Bk=-el->qdcn()/lm;
           double mi=((1-zeta)*el->qrov()>0.001)?(1-zeta)*el->qrov():0.001;
           double ma=((1+zeta)*el->qrov()<1.0)?(1+zeta)*el->qrov():1.0;
           double roBn=el->qrov()*sqrt(Bk);
           if(roBn>ma)el->upro(ma);
           else if(mi>roBn)el->upro(mi);
           else el->upro(roBn);
           soma+=el->qvol()*el->qro();
        }
        if (soma>this->ro*volume)
            li=lm;
        else
            lf=lm;
        soma=0.0;
    }
	ch=0.0;
    for(int e=0;e<ne;e++)
	{
		class elemento *el=elementos[e];
		ch+=el->qvol()*fabs(el->qro()-el->qrov());
	}
        ch/=volume;
	return(ch);
}
void analise::posprocessa()
{
   for (int e=0;e<ne;e++)
   {
      class elemento *el=elementos[e];
      el->p_processa(x);
   }
}

int analise::qpos(int i, int j)
{
   return(i*ndof+j);
};
void analise::visao(wxString vetor)
{
    double a,b,c;
	sscanf(vetor,"%lf %lf %lf",&a,&b,&c);
	double cx,sx,cy,sy,cz,sz;
    cx=cos(PI*a/180.0);
    sx=sin(PI*a/180.0);
    cy=cos(PI*b/180.0);
    sy=sin(PI*b/180.0);
	cz=cos(PI*c/180.0);
	sz=sin(PI*c/180.0);
	    view[0]=cz*cy;
    view[1]=sz*cx-cz*sy*sx;
    view[2]=sz*sx+cz*sy*cx;
    view[3]= -sz*cy;
    view[4]=cz*cx+sz*sy*sx;
    view[5]=cz*sx-sz*sy*cx;

//	for(int i=0;i<3;i++)
//		vetor>>v[i];

}
void analise::draw(wxDC& dc)
{
    double xmin,xmax,ymin,ymax,xmed,xdif,ymed,ydif;
    double ddif,zoom,tetaz,tetax,tetay;
/*    double view[6];
//    tetax=1.;
//		tetay=0.;
//            tetaz=;
    double cx,sx,cy,sy,cz,sz;
    cx=cos(tetax);
    sx=sin(tetax);
    cy=cos(tetay);
    sy=sin(tetay);
    cz=cos(tetaz);
    sz=sin(tetaz);
    view[0]=cz*cy;
    view[1]=sz*cx-cz*sy*sx;
    view[2]=sz*sx+cz*sy*cx;
    view[3]= -sz*cy;
    view[4]=cz*cx+sz*sy*sx;
    view[5]=cz*sx-sz*sy*cx;*/
    switch(nos[0]->qdim())
    {
        case 1:
            xmin=(this->nos[0])->qx(0);
            xmax=xmin;
            for (int i=1;i<nn;i++)
                if(xmin>nos[i]->qx(0))
                    xmin=nos[i]->qx(0);
                else if(xmax<nos[i]->qx(0))
                    xmax=nos[i]->qx(0);
            xmed=(xmax+xmin)/2.0;
            xdif=xmax-xmin;
            ymed=0.0;
            ydif=xdif/100.0;
            break;
        case 2:
            xmin=(this->nos[0])->qx(0);
            xmax=xmin;
            for (int i=1;i<nn;i++)
                if(xmin>nos[i]->qx(0))
                    xmin=nos[i]->qx(0);
                else if(xmax<nos[i]->qx(0))
                    xmax=nos[i]->qx(0);
            xmed=(xmax+xmin)/2.0;
            xdif=xmax-xmin;
            ymin=(this->nos[0])->qx(1);
            ymax=ymin;
            for (int i=1;i<nn;i++)
                if(ymin>nos[i]->qx(1))
                    ymin=nos[i]->qx(1);
                else if(ymax<nos[i]->qx(1))
                    ymax=nos[i]->qx(1);
            ymed=(ymax+ymin)/2.0;
            ydif=ymax-ymin;
            break;
        case 3:
            break;
    }
    double wxmin,wxmax,wxmed,wxdif,wymin,wymax,wymed,wydif;
    switch(nos[0]->qdim())
    {
        case 1:
            wxmin=view[0]*(this->nos[0])->qx(0);
            wxmax=wxmin;
            for (int i=1;i<nn;i++)
                if(wxmin>view[0]*nos[i]->qx(0))
                    wxmin=view[0]*nos[i]->qx(0);
                else if(wxmax<view[0]*nos[i]->qx(0))
                    wxmax=view[0]*nos[i]->qx(0);
            wxmed=(wxmax+wxmin)/2.0;
            wxdif=wxmax-wxmin;
            wymin=view[3]*(this->nos[0])->qx(0);
            wymax=wymin;
            for (int i=1;i<nn;i++)
                if(wymin>view[3]*nos[i]->qx(0))
                    wymin=view[3]*nos[i]->qx(0);
                else if(wymax<view[3]*nos[i]->qx(0))
                    wymax=view[3]*nos[i]->qx(0);
            wymed=(wymax+wymin)/2.0;
            wydif=wymax-wymin;
            if(wxdif<1e-5*xdif)wxdif=xdif/100;
            if(wydif<1e-5*xdif)wydif=xdif/100;
            break;
        case 2:
            wxmin=view[0]*(this->nos[0])->qx(0)+view[1]*(this->nos[0])->qx(1);
            wxmax=wxmin;
            for (int i=1;i<nn;i++)
                if(wxmin>view[0]*nos[i]->qx(0)+view[1]*(this->nos[i])->qx(1))
                    wxmin=view[0]*nos[i]->qx(0)+view[1]*(this->nos[i])->qx(1);
                else if(wxmax<view[0]*nos[i]->qx(0)+view[1]*(this->nos[i])->qx(1))
                    wxmax=view[0]*nos[i]->qx(0)+view[1]*(this->nos[i])->qx(1);
            wxmed=(wxmax+wxmin)/2.0;
            wxdif=wxmax-wxmin;
            wymin=view[3]*(this->nos[0])->qx(0)+view[4]*(this->nos[0])->qx(1);
            wymax=wymin;
            for (int i=1;i<nn;i++)
                if(wymin>view[3]*nos[i]->qx(0)+view[4]*(this->nos[i])->qx(1))
                    wymin=view[3]*nos[i]->qx(0)+view[4]*(this->nos[i])->qx(1);
                else if(wymax<view[3]*nos[i]->qx(0)+view[4]*(this->nos[i])->qx(1))
                    wymax=view[3]*nos[i]->qx(0)+view[4]*(this->nos[i])->qx(1);
            wymed=(wymax+wymin)/2.0;
            wydif=wymax-wymin;
            if(wxdif<1e-5*wydif)wxdif=wydif/100;
            if(wydif<1e-5*wxdif)wydif=wxdif/100;
            break;
        case 3:
            break;
    }
    wxCoord w,h;
    int d;
    dc.GetSize(&w,&h);
    if(wxdif/w>wydif/h)
    {
        d=w;
        ddif=wxdif;
    }
    else
    {
        d=h;
        ddif=wydif;
    }
//  dc.DrawText(wxT("Estou aqui em analise!"), 75, 85);
    wxFont font(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
    dc.SetFont(font);
    zoom=0.8;
       if(fn)
           for (int i=0;i<nn;i++)
               if(fnn)
                   nos[i]->draw(dc, wxmed, wymed, d, ddif, zoom, view,i);
               else
                   nos[i]->draw(dc, wxmed, wymed, d, ddif, zoom, view);
       if(fe)
           for (int i=0;i<ne;i++)
               if(fne)
			   {
				   if(fnm)
                      elementos[i]->draw(dc, wxmed, wymed, d, ddif, zoom, view, elementos[i]->qmat());
                   else if(fro)
                      elementos[i]->draw(dc, wxmed, wymed, d, ddif, zoom, view, elementos[i]->qro());
				   else
                      elementos[i]->draw(dc, wxmed, wymed, d, ddif, zoom, view, i);
			   }
               else
                   elementos[i]->draw(dc, wxmed, wymed, d, ddif, zoom, view);
/*       if(fn)
           for (int i=0;i<nn;i++)
               if(fnn)
                   nos[i]->draw(dc,xmed, xdif, ymed, ydif,view,i);
               else
                   nos[i]->draw(dc,xmed, xdif, ymed, ydif,view);
       if(fe)
           for (int i=0;i<ne;i++)
               if(fne)
                   elementos[i]->draw(dc,xmed, xdif, ymed, ydif,i);
               else
                   elementos[i]->draw(dc,xmed, xdif, ymed, ydif);*/
//  co<<"\nNumero de materiais = "<<a.nm<<"\n\n";
//  for (int i=0;i<a.nm;i++)
//    co<<"\nMaterial "<<i<<":\n"<<*a.materiais[i]<<"\n";
//  co<<"\nNumero de Condicoes de Contorno = "<<a.nc<<"\n\n";
//  for (int i=0;i<a.nc;i++)
//    co<<"\nCondicao de contorno "<<i<<":\n"<<*a.cc[i]<<"\n";
       if(fcc)
           for (int i=0;i<nc;i++)
           {
               if(fnc)
                  cc[i]->draw(dc, wxmed, wymed, d, ddif, zoom, view, i);
               else
                  cc[i]->draw(dc, wxmed, wymed, d, ddif, zoom, view);
           }
//               cc[i]->draw(dc,xmed, xdif, ymed, ydif);

//  co<<"\nVetor de forcas = \n\n";
//  for (int i=0;i<a.ndof;i++)
//     co<<"f["<<i<<"]="<<a.f[i]<<"\n";
//  co<<"\nVetor de deslocamentos resultantes = \n\n";
//  for (int i=0;i<a.ndof;i++)
//     co<<"u["<<i<<"]="<<a.x[i]<<"\n";
//  return co;
}
int analise::qndof()
{
	return ndof;
}
void analise::upK(int i, double v)
{
	K[i]=v;
}
void analise::upx(int i, double v)
{
	x[i]=v;
}
void analise::upf(int i, double v)
{
	f[i]=v;
}