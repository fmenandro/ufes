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
#include "aleatorio.h"

aleatorio::aleatorio(double media, double desvio)
{
   x[0]=-inf;  y[0]=0;
   x[np-1]=inf;  y[np-1]=0;
   m=media-1.287*desvio;
   d=2.574*desvio/(np-3);
   if(d>0)
   {
      for (int i=0;i<np-2;i++)
      {
         x[i+1]=m+i*d;  y[i+1]=exp((x[i+1]-media)*(x[i+1]-media)/(-2*desvio*desvio))/(2*PI);
      }
      A[0]=B[0]=C[0]=D[0]=A[np-2]=B[np-2]=C[np-2]=D[np-2]=0;
      for (int i=1;i<np-2;i++)
      {
         double K[np-2][np-2],f[np-2];
	 for(int j=0;j<np-2;j++)
	 {
	    f[j]=0.0;
	    for(int k=0;k<np-2;k++)
	       K[j][k]=0.0;
	 }
	 for(int j=0;j<np-3;j++)
	 {
	    K[j][j]=4*d;
	    K[j][j+1]=K[j+1][j]=d;
	 }
	 K[np-3][np-3]=4*d;
         A[i]=y[i];
      }
   }
   else
   {
      double x0=media-1.0/inf; 
      double x1=media+1.0/inf;
      m=(x1+x0)/2.0;
      d=(x1-x0)/(np-1);
      for (int i=0;i<(np+1)/2;i++)
      {
         x[i]=x0+i*d;  y[i]=0.0+4*i/((np-1)*(x1-x0));
         A[i]=y[i]; B[i]=4/((x1-x0)*(x1-x0)); C[i]=D[i]=0;
      }
      for (int i=0;i<np/2;i++)
      {
         int j=np-i-1;
         x[j]=x1-i*d;  y[j]=0.0+4*i/((np-1)*(x1-x0));
      }
      for (int i=(np-1)/2;i<np-1;i++)
      {
         A[i]=y[i]; B[i]=-4/((x1-x0)*(x1-x0)); C[i]=D[i]=0;
      }
      x[np/2]=media;
   }
   m=media;
   d=desvio;
};
aleatorio::aleatorio()
{
   const aleatorio objeto(0.,0.,0);
   this->copy(objeto);
};
aleatorio::aleatorio(aleatorio const &objeto)
{
   m=objeto.m;
   d=objeto.d;
   for(int i=0;i<np;i++)
   {
      x[i]=objeto.x[i];
      y[i]=objeto.y[i];
   }
   for(int i=0;i<np-1;i++)
   {
      A[i]=objeto.A[i];
      B[i]=objeto.B[i];
      C[i]=objeto.C[i];
      D[i]=objeto.D[i];
   }
};
aleatorio::aleatorio(double xx)
{
   const aleatorio objeto(xx,xx,0);
   this->copy(objeto);
};
aleatorio::aleatorio(double x0, double x1, int i)
{
   double p,xm=0;
   if(x0==x1)
   {
      m=x0;
      for (int i=0;i<np-1;i++)
      {
         x[i]=x0;
	 y[i]=qinf;
	 A[i]=qinf;
         B[i]=C[i]=D[i]=0.0;
      }
      x[np-1]=x0;
      y[np-1]=qinf;
      d=0.0;
/*      m=x0;
      x0-=0.5/qinf;
      x1+=0.5/qinf;
      p=(x1-x0)/(np-1);
      x[np-1]=x1;
      y[np-1]=qinf;
      for (int i=0;i<np-1;i++)
      {
         x[i]=x0+i*p;
	 y[i]=qinf;
	 A[i]=qinf;
         B[i]=C[i]=D[i]=0.0;
      }
      d=0.0;
*/   }
   else
   {
   switch(i)
   {
   case 0:
      m=(x1+x0)/2.0;
      d=0;
      p=(x1-x0)/(np-1);
      for (int i=0;i<np;i++)
      {
         x[i]=x0+i*p;  y[i]=1.0/(x1-x0);   d=d+(x[i]-m)*(x[i]-m);
      }
/*      for (int i=0;i<np-1;i++)
      {
         A[i]=y[i]; B[i]=C[i]=D[i]=0;
      }*/
      this->getFDPspline();
      break;
   case 1:
      m=(x1+x0)/2.0;
      d=0;
      p=(x1-x0)/(np-1);
      for (int i=0;i<(np+1)/2;i++)
      {
         x[i]=x0+i*p;  y[i]=0.0+4*i/((np-1)*(x1-x0));
//         A[i]=y[i]; B[i]=4/((x1-x0)*(x1-x0)); C[i]=D[i]=0;
      }
      for (int i=0;i<np/2;i++)
      {
         int j=np-i-1;
         x[j]=x1-i*p;  y[j]=0.0+4*i/((np-1)*(x1-x0));
      }
      x[np/2]=m;
/*      for (int i=(np-1)/2;i<np-1;i++)
      {
         A[i]=y[i]; B[i]=-4/((x1-x0)*(x1-x0)); C[i]=D[i]=0;
      }*/
      this->getFDPspline();
      break;
   case 2:
      m=(x1+x0)/2.0;
      d=0;
      double AA,BB,CC;
      CC=2.0/(-x1*x1*x1/3.0+x1*x1*x0-x1*x0*x0+x0*x0*x0/3.0);
      BB=-CC*(x1+x0);
      AA=-BB*x0-CC*x0*x0;
      p=(x1-x0)/(np-1);
      for (int i=0;i<np-1;i++)
      {
         x[i]=x0+i*p;  y[i]=AA+BB*x[i]+CC*x[i]*x[i];
         A[i]=y[i]; B[i]=BB+2*CC*x[i]; C[i]=CC; D[i]=0;
      }
      x[np-1]=x1;
      y[np-1]=0.0;
      x[np/2]=m;
//      this->getFDPspline();
      break;
   case 3:
      m=(x1+x0)/2.0;
      d=0;
      double aa[np-1],kk[np-1][np-1];
      kk[0][0]=m-x0; kk[0][1]=(m*m-x0*x0)/2.0; kk[0][2]=(m*m*m-x0*x0*x0)/3.0; kk[0][3]=(m*m*m*m-x0*x0*x0*x0)/4.0;
      kk[1][0]=1.0;  kk[1][1]=x0;              kk[1][2]=x0*x0;                kk[1][3]=x0*x0*x0;
      kk[2][0]=0.0;  kk[2][1]=1.0;             kk[2][2]=2.0*m;                kk[2][3]=3.0*m*m;
      kk[3][0]=0.0;  kk[3][1]=1.0;             kk[3][2]=2.0*x0;               kk[3][3]=3.0*x0*x0;
      aa[0]=0.5; aa[1]=aa[2]=aa[3]=0.0;
      gauss(kk,aa,4);
      p=(x1-x0)/(np-1);
      for (int i=0;i<(np+1)/2;i++)
      {
         x[i]=x0+i*p;  y[i]=aa[0]+aa[1]*x[i]+aa[2]*x[i]*x[i]+aa[3]*x[i]*x[i]*x[i];
         A[i]=y[i]; B[i]=aa[1]+2*aa[2]*x[i]+3*aa[3]*x[i]*x[i]; C[i]=aa[2]+3.0*aa[3]*x[i]; D[i]=aa[3];
      }
      kk[0][0]=x1-m; kk[0][1]=(x1*x1-m*m)/2.0; kk[0][2]=(x1*x1*x1-m*m*m)/3.0; kk[0][3]=(x1*x1*x1*x1-m*m*m*m)/4.0;
      kk[1][0]=1.0;  kk[1][1]=x1;              kk[1][2]=x1*x1;                kk[1][3]=x1*x1*x1;
      kk[2][0]=0.0;  kk[2][1]=1.0;             kk[2][2]=2.0*m;                kk[2][3]=3.0*m*m;
      kk[3][0]=0.0;  kk[3][1]=1.0;             kk[3][2]=2.0*x1;               kk[3][3]=3.0*x1*x1;
      aa[0]=0.5; aa[1]=aa[2]=aa[3]=0.0;
      gauss(kk,aa,4);
      for (int i=0;i<np/2;i++)
      {
         int j=np-i-1;
         x[j]=x1-i*p;  y[j]=aa[0]+aa[1]*x[j]+aa[2]*x[j]*x[j]+aa[3]*x[j]*x[j]*x[j];
      }
      for (int i=(np-1)/2;i<np-1;i++)
      {
         A[i]=y[i]; B[i]=aa[1]+2*aa[2]*x[i]+3*aa[3]*x[i]*x[i]; C[i]=aa[2]+3.0*aa[3]*x[i]; D[i]=aa[3];
      }
      x[np/2]=m;
      break;
   case 4:
      m=(x1+x0)/2.0;
      d=0;
      kk[0][0]=m-x0; kk[0][1]=(m*m-x0*x0)/2.0; kk[0][2]=(m*m*m-x0*x0*x0)/3.0; kk[0][3]=0.0;
      kk[1][0]=1.0;  kk[1][1]=x0;              kk[1][2]=x0*x0;                kk[1][3]=0.0;
      kk[2][0]=0.0;  kk[2][1]=1.0;             kk[2][2]=2.0*x0;               kk[2][3]=0.0;
      kk[3][0]=0.0;  kk[3][1]=0.0;             kk[3][2]=0.0;                  kk[3][3]=1.0;
      aa[0]=0.5; aa[1]=aa[2]=aa[3]=0.0;
      gauss(kk,aa,4);
      p=(x1-x0)/(np-1);
      for (int i=0;i<(np+1)/2;i++)
      {
         x[i]=x0+i*p;  y[i]=aa[0]+aa[1]*x[i]+aa[2]*x[i]*x[i]+aa[3]*x[i]*x[i]*x[i];
         A[i]=y[i]; B[i]=aa[1]+2*aa[2]*x[i]+3*aa[3]*x[i]*x[i]; C[i]=aa[2]+3.0*aa[3]*x[i]; D[i]=aa[3];
      }
      kk[0][0]=x1-m; kk[0][1]=(x1*x1-m*m)/2.0; kk[0][2]=(x1*x1*x1-m*m*m)/3.0; kk[0][3]=0.0;
      kk[1][0]=1.0;  kk[1][1]=x1;              kk[1][2]=x1*x1;                kk[1][3]=0.0;
      kk[2][0]=0.0;  kk[2][1]=1.0;             kk[2][2]=2.0*x1;               kk[2][3]=0.0;
      kk[3][0]=0.0;  kk[3][1]=0.0;             kk[3][2]=0.0;                  kk[3][3]=1.0;
      aa[0]=0.5; aa[1]=aa[2]=aa[3]=0.0;
      gauss(kk,aa,4);
      for (int i=0;i<np/2;i++)
      {
         int j=np-i-1;
         x[j]=x1-i*p;  y[j]=aa[0]+aa[1]*x[j]+aa[2]*x[j]*x[j]+aa[3]*x[j]*x[j]*x[j];
      }
      for (int i=(np-1)/2;i<np-1;i++)
      {
         A[i]=y[i]; B[i]=aa[1]+2*aa[2]*x[i]+3*aa[3]*x[i]*x[i]; C[i]=aa[2]+3.0*aa[3]*x[i]; D[i]=aa[3];
      }
      x[np/2]=m;
   }
   d=desvio(this);
   }
};
void aleatorio::testefdp(void)
{
  cout<<"\n\n media  = "<<this->m<<"\n desvio = "<<this->d<<"\n\n";
   cout<<"\n\n media calculada  = "<<media(this)<<"\n\n";
   cout<<"\n\n desvio calculado = "<<desvio(this)<<"\n\n";
};
aleatorio aleatorio::operator+(aleatorio b)
{
   aleatorio a,s;
   double w,gw,zw,hzw;
   double xg[4]={-0.861136311594063,
                 -0.339981043584856,
                  0.339981043584856,
		  0.861136311594063},
          wg[4]={ 0.347854845137454,
	          0.652145154862546,
	          0.652145154862546,
                  0.347854845137454};
   double ta,tb;
   ta=this->x[np-1]-this->x[0];
   tb=b.x[np-1]-b.x[0];
   if (ta<=tb)
      a.copy(*this);
   else
   {
      a.copy(b);
      b.copy(*this);
   }
   if (b.d==0.0)
   {
      for (int i=0;i<np;i++)
         a.x[i]+=b.m;
      a.m+=b.m;
     return(a);   
   }
   else if (a.d==0.0)
   {
      for (int i=0;i<np-1;i++)
      {
         s.x[i]=b.x[i]+a.m;
         s.y[i]=b.y[i];
	 s.A[i]=b.A[i];
	 s.B[i]=b.B[i];
	 s.C[i]=b.C[i];
	 s.D[i]=b.D[i];
      }
      s.x[np-1]=b.x[np-1]+a.m;
      s.y[np-1]=b.y[np-1];
      s.m=b.m+a.m;
      s.d=b.d;
      return(s);
   }
   else
   {
      s.x[0]=a.x[0]+b.x[0];
      s.x[np-1]=a.x[np-1]+b.x[np-1];
      double d=(s.x[np-1]-s.x[0])/(np-1);
      s.y[np-1]=0.0;
      for (int i=0;i<np-1;i++)
      {
         s.x[i]=s.x[0]+d*i;
         s.y[i]=0.0;
         for (int l=0;l<4;l++)
         {
            for (int j=0;j<np-1;j++)
            {
               w=(a.x[j+1]-a.x[j])*xg[l]/2.0+(a.x[j+1]+a.x[j])/2.0;
	          gw=a.A[j]+a.B[j]*(w-a.x[j])+a.C[j]*(w-a.x[j])*(w-a.x[j])+a.D[j]*(w-a.x[j])*(w-a.x[j])*(w-a.x[j]);
               for (int k=0;k<np-1;k++)
               {
	          zw=s.x[i]-w;
	          if ((b.x[k]<zw)&&(b.x[k+1]>=zw))
	             hzw=b.A[k]+b.B[k]*(zw-b.x[k])+b.C[k]*(zw-b.x[k])*(zw-b.x[k])+b.D[k]*(zw-b.x[k])*(zw-b.x[k])*(zw-b.x[k]);
	          else
	             hzw=0.0;
	          s.y[i]+=fabs(gw*hzw*wg[l]*(a.x[j+1]-a.x[j]))/2.0;
                  if (s.y[i]<0.0)
                     throw("Erro na soma y<0");
	       }
	    }
         }
      }
      s.getFDPspline();
      s.m=media(&s);
      s.d=desvio(&s);
      return(s);   
   }
};
aleatorio aleatorio::operator-()
{
   aleatorio a,n;
//   double w,gw,zw,hzw;
   double xg[4]={-0.861136311594063,
                 -0.339981043584856,
                  0.339981043584856,
		  0.861136311594063},
          wg[4]={ 0.347854845137454,
	          0.652145154862546,
	          0.652145154862546,
                  0.347854845137454};
   a.copy(*this);
   for (int i=0;i<np;i++)
   {
      int j=np-1-i;
      n.x[i]=-a.x[j];
      n.y[i]=a.y[j];
   }
/*   for (int i=0;i<np-1;i++)
   {
      int j=np-2-i;
      n.A[i]=a.A[j];
      n.B[i]=-a.B[j];
      n.C[i]=a.C[j];
      n.D[i]=-a.D[j];
   }*/
   if (a.d!=0.0)
   {
      n.getFDPspline();
/*      n.m=media(&n);
      n.d=desvio(&n);*/
      n.d=a.d;
      n.m=-a.m;
   }
   else
   {
      n.d=0.0;
      n.m=-a.m;
   }
   return(n);   
};
aleatorio aleatorio::operator-(aleatorio b)
{
   aleatorio a=-b,s=*this+a;
   return(s);   
};
aleatorio aleatorio::operator*(aleatorio b)
{
   aleatorio a,s;
   double w,gw,zw,hzw,pmax,pmin,p;
   double xg[4]={-0.861136311594063,
                 -0.339981043584856,
                  0.339981043584856,
		  0.861136311594063},
          wg[4]={ 0.347854845137454,
	          0.652145154862546,
	          0.652145154862546,
                  0.347854845137454};
   double ta,tb;
   ta=this->x[np-1]-this->x[0];
   tb=b.x[np-1]-b.x[0];
/*   if (ta<tb)
      a.copy(*this);
   else
   {
      a.copy(b);
      b.copy(*this);
   }*/
   a.copy(*this);
   if (b.d==0.0)
   {
      if (b.m==0.0)
      {
         s=0.0;
         return(s);
      }
      else if (b.m>0.0)
      {
         for (int i=0;i<np;i++)
         {
            a.x[i]*=b.m;
            a.y[i]/=b.m;
         }
         for (int i=0;i<np-1;i++)
         {
	    a.A[i]/=b.m;
	    a.B[i]/=b.m;
	    a.C[i]/=b.m;
	    a.D[i]/=b.m;
         }
         a.m*=b.m;
         a.d*=b.m;
         return(a);
      }
      else // b.m < 0.0
      {
         for (int i=0;i<np;i++)
         {
            int j=np-i-1;
            s.x[j]=a.x[i]*b.m;
            s.y[j]=-a.y[i]/b.m;
         }
/*         for (int i=0;i<np-1;i++)
         {
            int j=np-i-2;
	    s.A[j]=-a.A[i]/b.m;
	    s.B[j]=a.B[i]/b.m;
	    s.C[j]=-a.C[i]/b.m;
	    s.D[j]=a.D[i]/b.m;
         }*/
         s.getFDPspline();
         s.m=a.m*b.m;
         s.d=-a.d*b.m;
         return(s);
      }
   }
   else if (a.d==0.0)
   {
      if (a.m==0.0)
      {
         s=0.0;
         return(s);
      }
      else if (a.m>0.0)
      {
         for (int i=0;i<np-1;i++)
         {
            s.x[i]=b.x[i]*a.m;
            s.y[i]=b.y[i]/a.m;
	    s.A[i]=b.A[i]/a.m;
	    s.B[i]=b.B[i]/a.m;
	    s.C[i]=b.C[i]/a.m;
	    s.D[i]=b.D[i]/a.m;
         }
         s.x[np-1]=b.x[np-1]*a.m;
         s.y[np-1]=b.y[np-1]/a.m;
         s.m=b.m*a.m;
         s.d=b.d*a.m;
         return(s);
      }
      else // (a.m < 0.0)
      {
         for (int i=0;i<np;i++)
         {
            s.x[np-i-1]=b.x[i]*a.m;
            s.y[np-i-1]=-b.y[i]/a.m;
         }
         s.getFDPspline();
         s.m=b.m*a.m;
         s.d=-b.d*a.m;
         return(s);
      }
   }
   else
   {
      pmax=pmin=a.x[0]*b.x[0];
      p=a.x[0]*b.x[np-1];
      if (pmax<p) pmax=p;
      if (pmin>p) pmin=p;
      p=a.x[np-1]*b.x[0];
      if (pmax<p) pmax=p;
      if (pmin>p) pmin=p;
      p=a.x[np-1]*b.x[np-1];
      if (pmax<p) pmax=p;
      if (pmin>p) pmin=p;
      s.x[0]=pmin;
      s.x[np-1]=pmax;
      s.y[np-1]=0.0;
      double d=(s.x[np-1]-s.x[0])/(np-1);
      for (int i=0;i<np-1;i++)
      {
         s.x[i]=s.x[0]+d*i;
         s.y[i]=0.0;
         for (int l=0;l<4;l++)
         {
            for (int j=0;j<np-1;j++)
	    {
               w=(a.x[j+1]-a.x[j])*xg[l]/2.0+(a.x[j+1]+a.x[j])/2.0;
	       gw=a.A[j]+a.B[j]*(w-a.x[j])+a.C[j]*(w-a.x[j])*(w-a.x[j])+a.D[j]*(w-a.x[j])*(w-a.x[j])*(w-a.x[j]);
               for (int k=0;k<np-1;k++)
	       {
	          zw=s.x[i]/w;
	          if ((b.x[k]<zw)&&(b.x[k+1]>=zw))
	             hzw=b.A[k]+b.B[k]*(zw-b.x[k])+b.C[k]*(zw-b.x[k])*(zw-b.x[k])+b.D[k]*(zw-b.x[k])*(zw-b.x[k])*(zw-b.x[k]);
	          else
	             hzw=0.0;
	          s.y[i]+=fabs(gw*hzw*fabs(1./w)*wg[l]*(a.x[j+1]-a.x[j]))/2.0;
	       }
	    }
         } 
         if (s.y[i]<0.0)
            throw("Erro no produto y<0");

      }
      double somay=0.0,prodsoma=1.0;
      for (int j=0;j<np/2;j++)
      {
         for (int i=j;i<np-1-j;i++)
            somay+=s.y[i];
         prodsoma*=somay;
         somay=0.0;
      }
      if (prodsoma==0)
         for (int i=0;i<np-1;i++)
         {
            if (ta>tb)
               s.y[i]=a.y[i];
            else
               s.y[i]=b.y[i];
         }
      s.getFDPspline();
      s.m=media(&s);
      s.d=desvio(&s);
      return(s);
   }
};
aleatorio aleatorio::operator*(double b)
{
   aleatorio a;
   if (b==0.0)
      a=0.0;
   else if (b>0.0)
   {
      a.copy(*this);
      for (int i=0;i<np;i++)
      {
         a.x[i]*=b;
         a.y[i]/=b;
      }
      for (int i=0;i<np-1;i++)
      {
         a.A[i]/=b;
	 a.B[i]/=b;
	 a.C[i]/=b;
	 a.D[i]/=b;
      }
      a.m*=b;
      a.d*=b;
   }
   else // (b<0.0)
   {
      a.copy(*this);
      for (int i=0;i<=np/2;i++)
      {
         int j=np-i-1;
         double temp;
         temp=a.x[i];
         a.x[i]=a.x[j]*b;
         a.x[j]=temp*b;
         temp=a.y[i];
         a.y[i]=-a.y[j]/b;
         a.y[j]=-temp/b;
      }
/*      for (int i=0;i<np/2;i++)
      {
         int j=np-i-2;
         double temp;
         temp=a.A[i];
         a.A[i]=-a.A[j]/b;
         a.A[j]=-temp/b;
         temp=a.B[i];
         a.B[i]=a.B[j]/b;
         a.B[j]=temp/b;
         temp=a.C[i];
         a.C[i]=-a.C[j]/b;
         a.C[j]=-temp/b;
         temp=a.D[i];
         a.D[i]=a.D[j]/b;
         a.D[j]=temp/b;
      }*/
      a.getFDPspline();
      a.m*=b;
      a.d*=-b;
   }
   return(a);
};
aleatorio aleatorio::operator/(double b)
{
   aleatorio c;
   c.copy(*this);
   if (b==0.0)
      throw("Erro! Divisao de aleatorio por zero");
   else if (b>0.0)
   {
      for (int i=0;i<np;i++)
      {
         c.x[i]/=b;
         c.y[i]*=b;
      }
      for (int i=0;i<np-1;i++)
      {
         c.A[i]*=b;
	 c.B[i]*=b;
	 c.C[i]*=b;
	 c.D[i]*=b;
      }
      c.getFDPspline();
      c.m/=b;
      c.d/=b;
   }
   else // (b<0.0)
   {
      for (int i=0;i<=np/2;i++)
      {
         int j=np-i-1;
         double temp;
         temp=c.x[i];
         c.x[i]=c.x[j]/b;
         c.x[j]=temp/b;
         temp=c.y[i];
         c.y[i]=-c.y[j]*b;
         c.y[j]=-temp*b;
      }
/*      for (int i=0;i<np/2;i++)
      {
         int j=np-i-2;
         double temp;
         temp=c.A[i];
         c.A[i]=-c.A[j]*b;
         c.A[j]=-temp*b;
         temp=c.B[i];
         c.B[i]=c.B[j]*b;
         c.B[j]=temp*b;
         temp=c.C[i];
         c.C[i]=-c.C[j]*b;
         c.C[j]=-temp*b;
         temp=c.D[i];
         c.D[i]=c.D[j]*b;
         c.D[j]=temp*b;
      }*/
      c.getFDPspline();
      c.m/=b;
      c.d/=-b;
   }
   return(c);
};
aleatorio aleatorio::operator/(aleatorio b)
{
   aleatorio a,s;
   double w,hw,wz,gwz,pmax,pmin,p;
   double xg[4]={-0.861136311594063,
                 -0.339981043584856,
                  0.339981043584856,
		  0.861136311594063},
          wg[4]={ 0.347854845137454,
	          0.652145154862546,
	          0.652145154862546,
                  0.347854845137454};
   double ta,tb;
   ta=this->x[np-1]-this->x[0];
   tb=b.x[np-1]-b.x[0];
   a.copy(*this);
   if (b.d==0.0)
   {
      if (b.m==0.0)
         throw("Erro! Divisão por aleatorio nulo.");
      else if (b.m>0.0)
      {
         for (int i=0;i<np;i++)
         {
            a.x[i]/=b.m;
            a.y[i]*=b.m;
         }
         for (int i=0;i<np-1;i++)
         {
            a.A[i]*=b.m;
	    a.B[i]*=b.m;
            a.C[i]*=b.m;
	    a.D[i]*=b.m;
         }
         a.m/=b.m;
         a.d/=b.m;
         return(a);   
      }   
      else // (b.m<0.0)
      {
         for (int i=0;i<=np/2;i++)
         {
            int j=np-i-1;
            double temp;
            temp=a.x[i];
            a.x[i]=a.x[j]/b.m;
            a.x[j]=temp/b.m;
            temp=a.y[i];
            a.y[i]=-a.y[j]*b.m;
            a.y[j]=-temp*b.m;
         }
         a.getFDPspline();
/*         for (int i=0;i<np/2;i++)
         {
            int j=np-i-2;
            double temp;
            temp=a.A[i];
            a.A[i]=-a.A[j]*b.m;
            a.A[j]=-temp*b.m;
            temp=a.B[i];
            a.B[i]=a.B[j]*b.m;
            a.B[j]=temp*b.m;
            temp=a.C[i];
            a.C[i]=-a.C[j]*b.m;
            a.C[j]=-temp*b.m;
            temp=a.D[i];
            a.D[i]=a.D[j]*b.m;
            a.D[j]=temp*b.m;
         }*/
         a.m/=b.m;
         a.d/=-b.m;
         return(a);   
      }
   }
   else if (a.d==0.0)
   {
      if (a.m==0.0)
         return(a);
      else
      {
      if (a.m*b.x[0]*b.x[np-1]>0.0)
      {
         s.x[0]=a.m/b.x[np-1];
         s.x[np-1]=a.m/b.x[0];
      } else if (a.m*b.x[0]*b.x[np-1]<0.0)
      {
         s.x[0]=a.m/b.x[0];
         s.x[np-1]=a.m/b.x[np-1];
      }
      double dd=(s.x[np-1]-s.x[0])/(np-1);
      for (int i=0;i<np-1;i++)
      {
         s.x[i]=s.x[0]+dd*i;
	 w=a.m/s.x[i];
         s.y[i]=0.0;
         for (int j=0;j<np-1;j++)
            if ((b.x[j]<=w)&&(b.x[j+1]>w))
	       hw=b.A[j]+b.B[j]*(w-b.x[j])+b.C[j]*(w-b.x[j])*(w-b.x[j])+b.D[j]*(w-b.x[j])*(w-b.x[j])*(w-b.x[j]);
	 s.y[i]=fabs(hw*w);
                  if ((i!=0)&&(s.y[i]<0.0))
                     throw("Erro na divisao y<0");
      }
      s.y[np-1]=0.0;
      double somay=0.0,prodsoma=1.0;
      for (int j=0;j<np/2;j++)
      {
         for (int i=j;i<np-1-j;i++)
            somay+=s.y[i];
         prodsoma*=somay;
         somay=0.0;
      }
      if (prodsoma==0)
         for (int i=0;i<np-1;i++)
         {
            if (ta>1.0/tb)
               s.y[i]=a.y[i];
            else
               s.y[i]=1.0/b.y[i];
         }
      s.getFDPspline();
      s.m=media(&s);
      s.d=desvio(&s);
      return(s);
      }
   }
   else
   {
      if (b.x[0]!=0.0)
         pmax=pmin=a.x[0]/b.x[0];
      else if (b.x[np-1]!=0.0)
         pmax=pmin=a.x[0]/b.x[np-1];
      else
         throw("Erro na divisao aleatorio: divisao por zero");
      if (b.x[0]!=0.0)
      {
         p=a.x[np-1]/b.x[0];
         if (pmax<p) pmax=p;
         if (pmin>p) pmin=p;
      }
      if (b.x[np-1]!=0.0)
      {
         p=a.x[0]/b.x[np-1];
         if (pmax<p) pmax=p;
         if (pmin>p) pmin=p;
         p=a.x[np-1]/b.x[np-1];
         if (pmax<p) pmax=p;
         if (pmin>p) pmin=p;
      }
      s.x[0]=pmin;
      s.x[np-1]=pmax;
      s.y[np-1]=0.0;
      double dd=(s.x[np-1]-s.x[0])/(np-1);
      for (int i=0;i<np-1;i++)
      {
         s.x[i]=s.x[0]+dd*i;
         s.y[i]=0.0;
         for (int l=0;l<4;l++)
         {
            for (int j=0;j<np-1;j++)
            {
               w=(b.x[j+1]-b.x[j])*xg[l]/2.0+(b.x[j+1]+b.x[j])/2.0;
               hw=b.A[j]+b.B[j]*(w-b.x[j])+b.C[j]*(w-b.x[j])*(w-b.x[j])+b.D[j]*(w-b.x[j])*(w-b.x[j])*(w-b.x[j]);
               for (int k=0;k<np-1;k++)
	       {
	          wz=w*s.x[i];
	          if ((a.x[k]<wz)&&(a.x[k+1]>=wz))
	             gwz=a.A[k]+a.B[k]*(wz-a.x[k])+a.C[k]*(wz-a.x[k])*(wz-a.x[k])+a.D[k]*(wz-a.x[k])*(wz-a.x[k])*(wz-a.x[k]);
	          else
	             gwz=0.0;
//	          s.y[i]+=gwz*hw*fabs(w)*wg[l]*(b.x[j+1]-b.x[j])/2.0;
	          s.y[i]+=fabs(gwz*hw*(w)*wg[l]*(b.x[j+1]-b.x[j]))/2.0;
	       }
	    }
         }
                  if ((i!=0)&&(s.y[i]<0.0))
                     throw("Erro na divisao y<0");

      }
      s.getFDPspline();
      s.m=media(&s);
      s.d=desvio(&s);
      return(s);   
   }
};
aleatorio aleatorio::operator+=(aleatorio b)
{
   aleatorio a,s;
   a=*this;
   s=a+b;
   *this=s;
   return(s);   
};
aleatorio aleatorio::operator-=(aleatorio b)
{
   aleatorio a,s;
   a=*this;
   s=a-b;
   *this=s;
   return(s);   
};
aleatorio aleatorio::operator/=(aleatorio b)
{
   aleatorio a,s;
   a=*this;
   s=a/b;
   *this=s;
   return(s);   
};
aleatorio aleatorio::operator*=(aleatorio b)
{
   aleatorio a,s;
   a=*this;
   s=a*b;
   *this=s;
   return(s);   
};
aleatorio aleatorio::aabs(aleatorio a)
{
   if (a.qm()<0)
      return(-a);
   else
      return(a);
};
bool aleatorio::operator<(double d)
{
   return(this->qm()<d);
};
bool aleatorio::operator>(double d)
{
   return(this->qm()>d);
};
bool aleatorio::operator<(aleatorio& b)
{
   return(this->qm()<b.qm());
};
bool aleatorio::operator>(aleatorio& b)
{
   return(this->qm()>b.qm());
};
/*bool operator<(aleatorio& a, double d)
{
   return(a.qm()<d);
};
bool operator>(aleatorio& a, double d)
{
   return(a.qm()>d);
};
bool operator<(aleatorio& a, aleatorio& b)
{
   return(a.qm()<b.qm());
};
bool operator>(aleatorio& a, aleatorio& b)
{
   return(a.qm()>b.qm());
};*/
istream& operator>>(istream& ci, aleatorio& a)
{
double min,max;
int tipo;
ci>>min>>max>>tipo;
aleatorio b=aleatorio(min,max,tipo);
a=b;
return ci;
};
ostream& operator<<(ostream& co, const aleatorio& a)
{
//co<<(a.x[0]+a.x[np-1])/2.;
co<<a.m<<" ± "<<a.d<<"["<<a.x[0]<<","<<a.x[np-1]<<"]";
/*
co<<"Media  = "<<a.m
  <<"\nDesvio = "<<a.d
  <<"\nMinimo = "<<a.x[0]
  <<"\nMaximo = "<<a.x[np-1];*//*
for (int i=0;i<np;i++)
{
   co<<"\n x["<<i<<"] = "<<a.x[i];
   co<<"   y["<<i<<"] = "<<a.y[i];
}*//*
for (int i=0;i<np-1;i++)
{
   co<<"\n A["<<i<<"] = "<<a.A[i];
   co<<"   B["<<i<<"] = "<<a.B[i];
   co<<"   C["<<i<<"] = "<<a.C[i];
   co<<"   D["<<i<<"] = "<<a.D[i];
}*/
return co;
};
aleatorio aleatorio::getFDPspline()
{
   double c[np-1],k[np-1][np-1],A[np],B[np-1],C[np],D[np-1],hi,errov=1.0,errof;
   if (this->x[np-1]-this->x[0]<Tolerancia)
   {
      double tam=this->x[np-1]-this->x[0];
      if (tam!=0.0)
      {
      for (int i=0;i<np-1;i++)
      {
         this->A[i]=this->y[i]=1.0/tam;
         this->B[i]=this->C[i]=this->D[i]=0.0;
      }
      }
   }
   else
   {
   while (errov*errov>Tolerancia*Tolerancia)
   {
   for (int i=0;i<np-1;i++)
   {
      A[i]=this->y[i];
      B[i]=(this->y[i+1]-this->y[i])/(this->x[i+1]-this->x[i]);
      C[i]=D[i]=0.0;
   }
   A[np-1]=0.0;
   for (int i=0;i<np-2;i++)
      for (int j=0;j<np-2;j++)
         k[i][j]=0.0;
   k[0][0]=2.0*((this->x[2]-this->x[1])+(this->x[1]-this->x[0]));
   k[0][1]=this->x[2]-this->x[1];
   for (int i=1;i<np-2;i++)
   {
      k[i][i-1]=this->x[i+1]-this->x[i];  
      k[i][i]=2.0*((this->x[i+2]-this->x[i+1])+(this->x[i+1]-this->x[i]));  
      k[i][i+1]=this->x[i+2]-this->x[i+1];
      c[i-1]=3*(this->y[i+1]-this->y[i])/(this->x[i+1]-this->x[i])-3*(this->y[i]-this->y[i-1])/(this->x[i]-this->x[i-1]);
   }
   k[np-2][np-3]=this->x[np-1]-this->x[np-2];
   k[np-2][np-2]=2.0*((this->x[np]-this->x[np-1])+(this->x[np-1]-this->x[np-2]));
   gauss(k,c,np-3);
   C[0]=C[np-1]=0.0;
   for (int i=1;i<np-2;i++)
   {
      C[i]=c[i-1];
   }
   for (int i=0;i<np-2;i++)
   {
      B[i]-=(2*C[i]+C[i+1])*(this->x[i+1]-this->x[i])/3.0;
      D[i]=(C[i+1]-C[i])/(3.0*(this->x[i+1]-this->x[i]));
   }
   A[np-1]=this->y[np-1];
/*   errov=0.0;
   for (int i=0;i<np-1;i++)
   {
      hi=this->x[i+1]-this->x[i];
      errov+=(A[i]+(B[i]/2.0+(C[i]/3.0+D[i]*hi/4.0)*hi)*hi)*hi-(A[i]+A[i+1])*hi/2.0;
   }*/
   errov=-1.0;
   for (int i=0;i<np-1;i++)
   {
      hi=this->x[i+1]-this->x[i];
      errov+=(A[i]+(B[i]/2.0+(C[i]/3.0+D[i]*hi/4.0)*hi)*hi)*hi;
   }
   for (int i=0;i<np-1;i++)
   {
      this->A[i]=A[i];
      this->B[i]=B[i];
      this->C[i]=C[i];
      this->D[i]=D[i];
   }
   
   for (int i=0;i<np-1;i++)
   {
      B[i]=(this->y[i+1]-this->y[i])/(this->x[i+1]-this->x[i]);
   }
   C[0]=D[0]=0.0;
   for (int i=1;i<=(np-2)/2;i++)
   {
      D[i]=0;
      C[i]=((this->y[i+1]-this->y[i])/(this->x[i+1]-this->x[i])-(this->y[i]-this->y[i-1])/(this->x[i]-this->x[i-1])+C[i-1]*(this->x[i]-this->x[i-1]))/(this->x[i+1]-this->x[i]);
      B[i]-=C[i]*(this->x[i+1]-this->x[i]);
   }
   C[np-2]=D[np-2]=0.0;
   for (int i=np-2;i>(np-2)/2+1;i--)
   {
      D[i-1]=0;
      C[i-1]=(-(this->y[i+1]-this->y[i])/(this->x[i+1]-this->x[i])+(this->y[i]-this->y[i-1])/(this->x[i]-this->x[i-1])+C[i]*(this->x[i+1]-this->x[i]))/(this->x[i]-this->x[i-1]);
      B[i-1]-=this->C[i-1]*(this->x[i]-this->x[i-1]);
   }
/*   errof=0.0;
   for (int i=0;i<np-1;i++)
   {
      hi=this->x[i+1]-this->x[i];
      errof+=(A[i]+(B[i]/2.0+(C[i]/3.0+D[i]*hi/4.0)*hi)*hi)*hi-(A[i]+A[i+1])*hi/2.0;
   }*/
   errof=-1.0;
   for (int i=0;i<np-1;i++)
   {
      hi=this->x[i+1]-this->x[i];
      errof+=(A[i]+(B[i]/2.0+(C[i]/3.0+D[i]*hi/4.0)*hi)*hi)*hi;
   }
   if (errof*errof<errov*errov)
   {
      errov=errof;
      for (int i=0;i<np-1;i++)
      {
         this->B[i]=B[i];
         this->C[i]=C[i];
         this->D[i]=D[i];
      }
   }
   
   for (int i=0;i<np-1;i++)
   {
      B[i]=(this->y[i+1]-this->y[i])/(this->x[i+1]-this->x[i]);
   }
   for (int i=0;i<np-2;i++)
      for (int j=0;j<np-2;j++)
         k[i][j]=0.0;
   k[0][0]=2.0*((this->x[2]-this->x[1])+(this->x[1]-this->x[0]));
   k[0][1]=this->x[2]-this->x[1];
   for (int i=1;i<np-2;i++)
   {
      k[i][i-1]=this->x[i+1]-this->x[i];  
      k[i][i]=2.0*((this->x[i+2]-this->x[i+1])+(this->x[i+1]-this->x[i]));  
      k[i][i+1]=this->x[i+2]-this->x[i+1];
      c[i-1]=3*(this->y[i+1]-this->y[i])/(this->x[i+1]-this->x[i])-3*(this->y[i]-this->y[i-1])/(this->x[i]-this->x[i-1]);
   }
   k[np-2][np-3]=this->x[np-1]-this->x[np-2];
   k[np-2][np-2]=2.0*((this->x[np]-this->x[np-1])+(this->x[np-1]-this->x[np-2]));
   gauss(k,c,np-3);
   C[0]=C[np-1]=0.0;
   for (int i=1;i<np-2;i++)
   {
      C[i]=c[i-1];
   }
   for (int i=0;i<np-2;i++)
   {
      B[i]-=(2*C[i]+C[i+1])*(this->x[i+1]-this->x[i])/3.0;
      D[i]=(C[i+1]-C[i])/(3.0*(this->x[i+1]-this->x[i]));
   }
/*   errof=0.0;
   for (int i=0;i<np-1;i++)
   {
      hi=this->x[i+1]-this->x[i];
      errof+=(A[i]+(B[i]/2.0+(C[i]/3.0+D[i]*hi/4.0)*hi)*hi)*hi-(A[i]+A[i+1])*hi/2.0;
   }*/
   errof=-1.0;
   for (int i=0;i<np-1;i++)
   {
      hi=this->x[i+1]-this->x[i];
      errof+=(A[i]+(B[i]/2.0+(C[i]/3.0+D[i]*hi/4.0)*hi)*hi)*hi;
   }
   if (errof*errof<errov*errov)
   {
      errov=errof;
      for (int i=0;i<np-1;i++)
      {
         this->B[i]=B[i];
         this->C[i]=C[i];
         this->D[i]=D[i];
      }
   }

   for (int i=0;i<np-1;i++)
   {
      A[i]=this->y[i];
      B[i]=(this->y[i+1]-this->y[i])/(this->x[i+1]-this->x[i]);
      C[i]=D[i]=0.0;
   }
/*   errof=0.0;
   for (int i=0;i<np-1;i++)
   {
      hi=this->x[i+1]-this->x[i];
      errof+=(A[i]+(B[i]/2.0+(C[i]/3.0+D[i]*hi/4.0)*hi)*hi)*hi-(A[i]+A[i+1])*hi/2.0;
   }*/
   errof=-1.0;
   for (int i=0;i<np-1;i++)
   {
      hi=this->x[i+1]-this->x[i];
      errof+=(A[i]+(B[i]/2.0+(C[i]/3.0+D[i]*hi/4.0)*hi)*hi)*hi;
   }
   if (errof*errof<errov*errov)
   {
      errov=errof;
      for (int i=0;i<np-1;i++)
      {
         this->B[i]=B[i];
         this->C[i]=C[i];
         this->D[i]=D[i];
      }
   }
   if (errov*errov>Tolerancia*Tolerancia)
   {
      for (int i=0;i<np;i++)
         this->y[i]/=(errov+1.0);
   }
   }
   }
   return(*this);
}//Fim de getFDPspline
aleatorio aleatorio::copy(aleatorio objeto)
{
   m=objeto.m;
   d=objeto.d;
   for(int i=0;i<np;i++)
   {
      x[i]=objeto.x[i];
      y[i]=objeto.y[i];
   }
   for(int i=0;i<np-1;i++)
   {
      A[i]=objeto.A[i];
      B[i]=objeto.B[i];
      C[i]=objeto.C[i];
      D[i]=objeto.D[i];
   }
   return(*this);
};
double aleatorio::media(aleatorio *a)
{
   double e=0.0;
   if (a->x[np-1]-a->x[0]<2.0/qinf)
      e=(a->x[np-1]+a->x[0])/2.0;
   else if((a->x[0]>-qinf)&&(a->x[np-1]<qinf))
   {
   for(int i=0;i<np-1;i++)
   {
      double xi,xi1,Ai,Bi,Ci,Di;
      xi=a->x[i];
      xi1=a->x[i+1];
      Ai=a->A[i];
      Bi=a->B[i];
      Ci=a->C[i];
      Di=a->D[i];
      e+=(xi1*xi1-xi*xi)*(Ai-xi*(Bi-xi*(Ci-xi*Di)))/2.0+(xi1*xi1*xi1-xi*xi*xi)*(Bi-xi*(2*Ci-xi*3*Di))/3.0+(xi1*xi1*xi1*xi1-xi*xi*xi*xi)*(Ci-3*Di*xi)/4.0+(xi1*xi1*xi1*xi1*xi1-xi*xi*xi*xi*xi)*Di/5.0;
/*      e+=xi1*xi1*((Ai-xi*(Bi-xi*(Ci-xi*Di)))/2.0+xi1*((Bi-xi*(2*Ci-xi*3*Di))/3.0+xi1*((Ci-3*Di*xi)/4.0+xi1*Di/5.0)));
      e-=xi*xi*((Ai-xi*(Bi-xi*(Ci-xi*Di)))/2.0+xi*((Bi-xi*(2*Ci-xi*3*Di))/3.0+xi*((Ci-3*Di*xi)/4.0+xi*Di/5.0)));*/
   }
   }
   else if((a->x[0]<=-qinf)&&(a->x[np-1]>=qinf))
   {
      double alfa,h;
      alfa=a->d/(a->x[1]-a->m);
      h=alfa/10;
      for(double i=h/2;i>alfa;i+=h)
         e+=exp(-1.0/i*i)/(i*i);
      e=e*h/sqrt(2*PI);
      for(int i=1;i<np-2;i++)
      {
         double xi,xi1,Ai,Bi,Ci,Di;
         xi=a->x[i];
         xi1=a->x[i+1];
         Ai=a->A[i];
         Bi=a->B[i];
         Ci=a->C[i];
         Di=a->D[i];
         e+=xi1*xi1*((Ai-xi*(Bi-xi*(Ci-xi*Di)))/2.0+xi1*((Bi-xi*(2*Ci-xi*3*Di))/3.0+xi1*((Ci-3*Di*xi)/4.0+xi1*Di/5.0)));
         e-=xi*xi*((Ai-xi*(Bi-xi*(Ci-xi*Di)))/2.0+xi*((Bi-xi*(2*Ci-xi*3*Di))/3.0+xi*((Ci-3*Di*xi)/4.0+xi*Di/5.0)));
      }
      alfa=a->d/(a->x[np-2]-a->m);
      h=alfa/10;
      for(double i=h/2;i>alfa;i+=h)
         e+=exp(-1.0/i*i)/(i*i);
      e=e*h/sqrt(2*PI);
   }
   return e;
};
double aleatorio::desvio(aleatorio *a)
{
   double e=0.0,d=0.0;
   if (a->x[np-1]-a->x[0]<2.0/qinf)
      d=0.0;
   else
   {
   for(int i=0;i<np-1;i++)
   {
      double xi,xi1,Ai,Bi,Ci,Di;
      xi=a->x[i];
      xi1=a->x[i+1];
      Ai=a->A[i];
      Bi=a->B[i];
      Ci=a->C[i];
      Di=a->D[i];
      e+=xi1*xi1*((Ai-xi*(Bi-xi*(Ci-xi*Di)))/2.0+xi1*((Bi-xi*(2*Ci-xi*3*Di))/3.0+xi1*((Ci-3*Di*xi)/4.0+xi1*Di/5.0)));
      e-=xi*xi*((Ai-xi*(Bi-xi*(Ci-xi*Di)))/2.0+xi*((Bi-xi*(2*Ci-xi*3*Di))/3.0+xi*((Ci-3*Di*xi)/4.0+xi*Di/5.0)));
      d+=xi1*xi1*xi1*((Ai-xi*(Bi-xi*(Ci-xi*Di)))/3.0+xi1*((Bi-xi*(2*Ci-xi*3*Di))/4.0+xi1*((Ci-3*Di*xi)/5.0+xi1*Di/6.0)));
      d-=xi*xi*xi*((Ai-xi*(Bi-xi*(Ci-xi*Di)))/3.0+xi*((Bi-xi*(2*Ci-xi*3*Di))/4.0+xi*((Ci-3*Di*xi)/5.0+xi*Di/6.0)));
   }
   d-=e*e;
   d=sqrt(sqrt(d*d));
   }
   return d;
};
/*************************************************************** gauss */
void aleatorio::gauss(double K[np-1][np-1], double f[np-1], int n)
/* Resolve um sistema de equacoes [K]{u} = {f},
   pelo metodo da eliminacao de Gauss */
{
   int i,j,k,kk,pivo;
   double Kpivo, fator;
   for(k=0;k<n-1;k++)
   {
      Kpivo=fabs(K[k][k]);
      kk=k+1;
      pivo=k;
      for (i=kk;i<n;i++)
      {
         if (fabs(K[i][k])>Kpivo)
         {
            Kpivo=fabs(K[i][k]);
            pivo=i;
         }
      }
      if (k!=pivo)
      {
         for (j=k;j<n;j++)
         {
            fator=K[k][j];
            K[k][j]=K[pivo][j];
            K[pivo][j]=fator;
         }
         fator=f[k];
         f[k]=f[pivo];
         f[pivo]=fator;
      }
      if (Kpivo*Kpivo<tolerGauss*tolerGauss)
      {
         cout<<"O sistema e' singular! (aleatorio 1)";
      }
      for (i=kk;i<n;i++)
      {
         fator = K[i][k]/K[k][k];
      	for (j=kk;j<n;j++)
         {
            K[i][j] -= fator*K[k][j];
         }
         f[i] -= fator*f[k];
      }
   }
   if (K[n-1][n-1]*K[n-1][n-1]<tolerGauss*tolerGauss)
   {
      cout<<"O sistema e' singular (aleatorio 2)!";
   }
   f[n-1] /= K[n-1][n-1];
   for (i=n-2;i>=0;i--)
   {
      for (j=i+1;j<n;j++)
         f[i] -= f[j]*K[i][j];
      f[i] /= K[i][i];
   }
}; /* Fim de gauss */
double aleatorio::qm()
{
   return(m);
}; /* Fim de qm */
aleatorio aleatorio::asqrt()
{
   aleatorio b,c,dd;
   this->getFDPspline();
   this->m=media(this);
   this->d=desvio(this);
   dd=*this;
   while ((dd*dd-*this)>Tolerancia)
   {
      b=dd;
      c=*this/dd;
      dd=(b+c)/double(2.0);
   }
   return(dd);
};

aleatorio::~aleatorio()
{
};
