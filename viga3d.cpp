/***************************************************************************
 *   Copyright (C) 2005 by Leonardo Tutanko Souza Ferraz &                 *
 *   Fernando Cesar Meira Menandro                                         *
 *   menandro@localhost.localdomain                                        *
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
#include "viga3d.h"

Viga3D::Viga3D():elemento(dim,ipn,nno,prp,ptg,nlb)
{
}

Viga3D::~Viga3D()
{
}
void Viga3D::monta_b()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      E,A,Iy,Iz,J,ni,L,L1,L2,xx[2],yy[2],zz[2],v1[3],v2[3],dx,dy,dz,h,h1,h2,vx,vy,vz,prodesc,csa1,csa2,csa3,csb1,csb2,csb3,csg1,csg2,csg3,B[6][12],T[12][12],X,um=1.0;
   for (int i=0;i<qnlb();i++)
      for (int j=0;j<12;j++)
      {
         b[i*12+j]=0.0;
         B[i][j]=0.0;
      }
   E=this->pmaterial->qE();
   ni=this->pmaterial->qni();
   A=this->prop[0];
   Iy=this->prop[1];
   Iz=this->prop[2];
   J=this->prop[3];
   xx[0]=this->pno[0]->qx(0);
   xx[1]=this->pno[1]->qx(0);
   yy[0]=this->pno[0]->qx(1);
   yy[1]=this->pno[1]->qx(1);
   zz[0]=this->pno[0]->qx(2);
   zz[1]=this->pno[1]->qx(2);
   vx=this->prop[4];   //coordenada x do nó localizado no plano xy local
   vy=this->prop[5];   //coordenada y do nó localizado no plano xy local
   vz=this->prop[6];   //coordenada z do nó localizado no plano xy local
   dx=xx[1]-xx[0];
   dy=yy[1]-yy[0];
   dz=zz[1]-zz[0];
   h=dx*dx+dy*dy+dz*dz;
#ifdef ALEATORIO
   L=h.asqrt();     // comprimento da viga
#else
   L=sqrt(h);       // comprimento da viga
#endif
   prodesc=dx*vx+dy*vy+dz*vz; /* produto escalar entre o vetor de direção determinada pela
                                 linha de centro do elemento e o vetor contido no plano xy */
   v1[0]=vx-dx*(prodesc/h);  /* determinação da componente x do vetor ortogonal ao vetor que passa
                                pelos centróides das seções transversais ao longo do elemento*/
   v1[1]=vy-dy*(prodesc/h);  /* determinação da componente y do vetor ortogonal ao vetor que passa
                                pelos centróides das seções transversais ao longo do elemento*/
   v1[2]=vz-dz*(prodesc/h);  /* determinação da componente z do vetor ortogonal ao vetor que passa
                                pelos centróides das seções transversais ao longo do elemento*/ 
   v2[0]=v1[2]*dy-v1[1]*dz;  // coordenada x do vetor na direção e sentido do eixo z local 
   v2[1]=v1[0]*dz-v1[2]*dx;  // coordenada y do vetor na direção e sentido do eixo z local 
   v2[2]=v1[1]*dx-v1[0]*dy;  // coordenada z do vetor na direção e sentido do eixo z local 
   csa1=(dx*1+dy*0+dz*0)/(L*(sqrt(double(1*1+0*0+0*0))));  //coseno do angulo formado entre os eixos x local e X global
   csa2=(dx*0+dy*1+dz*0)/(L*(sqrt(double(0*0+1*1+0*0))));  //coseno do angulo formado entre os eixos x local e Y global
   csa3=(dx*0+dy*0+dz*1)/(L*(sqrt(double(0*0+0*0+1*1))));  //coseno do angulo formado entre os eixos x local e Z global
   h1=v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2];
#ifdef ALEATORIO
   L1=h1.asqrt();     // comprimento da viga
#else
   L1=sqrt(h1);       // comprimento da viga
#endif
   csb1=(v1[0]*1+v1[1]*0+v1[2]*0)/(L1*(sqrt(double(1*1+0*0+0*0)))); //coseno do angulo formado entre os eixos y local e X global
   csb2=(v1[0]*0+v1[1]*1+v1[2]*0)/(L1*(sqrt(double(0*0+1*1+0*0)))); //coseno do angulo formado entre os eixos y local e Y global
   csb3=(v1[0]*0+v1[1]*0+v1[2]*1)/(L1*(sqrt(double(0*0+0*0+1*1)))); //coseno do angulo formado entre os eixos y local e Z global
   h2=v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2];
#ifdef ALEATORIO
   L2=h2.asqrt();     // comprimento da viga
#else
   L2=sqrt(h2);       // comprimento da viga
#endif
   csg1=(v2[0]*1+v2[1]*0+v2[2]*0)/(L2*(sqrt(double(1*1+0*0+0*0)))); //coseno do angulo formado entre os eixos z local e X global
   csg2=(v2[0]*0+v2[1]*1+v2[2]*0)/(L2*(sqrt(double(0*0+1*1+0*0)))); //coseno do angulo formado entre os eixos z local e Y global
   csg3=(v2[0]*0+v2[1]*0+v2[2]*1)/(L2*(sqrt(double(0*0+0*0+1*1)))); //coseno do angulo formado entre os eixos z local e Z global
   
   X=(pg==0)?0:L;
   for (int i=0;i<12;i++)
      for (int j=0;j<12;j++)
         T[i][j]=0.0;
   T[0][0]=T[6][6]=T[3][3]=T[9][9]=csa1;
   T[1][1]=T[7][7]=T[4][4]=T[10][10]=csb2;
   T[2][2]=T[8][8]=T[5][5]=T[11][11]=csg3;
   T[0][1]=T[6][7]=T[3][4]=T[9][10]=csb1;
   T[0][2]=T[6][8]=T[3][5]=T[9][11]=csg1;
   T[1][0]=T[7][6]=T[4][3]=T[10][9]=csa2;
   T[1][2]=T[7][8]=T[4][5]=T[10][11]=csg2;
   T[2][0]=T[8][6]=T[5][3]=T[11][9]=csa3;
   T[2][1]=T[8][7]=T[5][4]=T[11][10]=csb3; 
   
   cout<<"\nMatriz T";
   for (int h=0;h<12;h++)
   {
      cout<<"\n";
      for (int l=0;l<12;l++)
      { 
         cout<<T[h][l]<<"  ";
      }
   }
   cout<<"\n";
        
   B[0][0]=-um/L;
   B[0][6]=-B[0][0];
   B[3][3]=-um/L;
   B[3][9]=-B[3][3];
   B[4][2]=-(((X*12.0)/L)-(um*6.0))/(L*L);
   B[4][4]=(((X*6.0)/L)-(um*4.0))/L;
   B[4][8]=-B[4][2];
   B[4][10]=(((X*6.0)/L)-(um*2.0))/L;
   B[5][1]=(((X*12.0)/L)-(um*6.0))/(L*L);
   B[5][5]=(((X*6.0)/L)-(um*4.0))/L;
   B[5][7]=-B[5][1];
   B[5][11]=(((X*6.0)/L)-(um*2.0))/L;
   B[1][1]=(um*12.0)/(L*L*L);
   B[1][5]=B[1][11]=(um*6.0)/(L*L);
   B[1][7]=-B[1][1];
   B[2][2]=(um*12.0)/(L*L*L);
   B[2][4]=B[2][10]=-(um*6.0)/(L*L);
   B[2][8]=-B[2][2];
      
   cout<<"\nMatriz B";
   for (int h=0;h<qnlb();h++)
   {
      cout<<"\n";
      for (int l=0;l<12;l++)
      { 
         cout<<B[h][l]<<"  ";
      }
   }
   cout<<"\n";

   for (int i=0;i<qnlb()*qnlb();i++)  //matriz c utilizada para determinação das deformações
      c[i]=0.0;      
   c[0]=E*prop[0];
   c[7]=E*prop[1];
   c[14]=E*prop[2];
   c[21]=E*prop[3]/((um+ni)*2.0); 
   c[28]=E*prop[1];
   c[35]=E*prop[2];  
   
   for (int h=0;h<qnlb();h++)
      for (int i=0;i<qnlb();i++)
         for (int j=0;j<12;j++)
            for (int k=0;k<12;k++)         
                 b[h*12+k]+=c[h*6+i]*B[i][j]*T[k][j];
 
   cout<<"\nMatriz b";
   for (int h=0;h<qnlb();h++)
   {
      cout<<"\n";
      for (int l=0;l<12;l++)
      { 
         cout<<b[h*12+l]<<"  ";
      }
   }
   cout<<"\n";
}

void Viga3D::monta_c()  //matriz c utilizada para determinação das tensões
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
   c1=1.0,c2=1.5,c3=4.81,prp=this->prop[0],sq;
   for (int i=0;i<qnlb()*qnlb();i++)
      c[i]=0.0;
   c[0]=c1/prp;
   c[7]=c2/prp;  //para tensão cisalhante maxima em vigas de seção transversal retangular
   c[14]=c2/prp;
#ifdef ALEATORIO
   sq=prp.asqrt();
#else
   sq=sqrt(prp);
#endif
   c[21]=c3/(sq*sq*sq); //para tensão cisalhante maxima em vigas de seção transversal retangular devido ao torque????????????????????????????
   c[28]=c2/prp;
   c[35]=c2/prp;
}
void Viga3D::monta_rigidez()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      E,A,Iy,Iz,J,ni,G,t,L,L1,L2,xx[2],yy[2],zz[2],v1[3],v2[3],vx,vy,vz,prodesc,dx,dy,dz,h,h1,h2,csa1,csa2,csa3,csb1,csb2,csb3,csg1,csg2,csg3,bz,by,T[12][12],K[12][12],um=1.0;
   E=this->pmaterial->qE();
   ni=this->pmaterial->qni();
   A=this->prop[0];
   Iy=this->prop[1];  //Momento de Inércia da seção transversal em relação a y
   Iz=this->prop[2];  //Momento de Inércia da seção transversal em relação a z
   J=this->prop[3];   //Momento polar de IInércia da seção transversal
   xx[0]=this->pno[0]->qx(0);  //coordenada x do nó 1
   xx[1]=this->pno[1]->qx(0);  //coordenada x do nó 2
   yy[0]=this->pno[0]->qx(1);  //coordenada y do nó 1
   yy[1]=this->pno[1]->qx(1);  //coordenada y do nó 2
   zz[0]=this->pno[0]->qx(2);  //coordenada z do nó 1
   zz[1]=this->pno[1]->qx(2);  //coordenada z do nó 2
   vx=this->prop[4];   //coordenada x do nó localizado no plano xy
   vy=this->prop[5];   //coordenada y do nó localizado no plano xy
   vz=this->prop[6];   //coordenada z do nó localizado no plano xy
   dx=xx[1]-xx[0];
   dy=yy[1]-yy[0];
   dz=zz[1]-zz[0];
   h=dx*dx+dy*dy+dz*dz;
#ifdef ALEATORIO
   L=h.asqrt();     // comprimento da viga
#else
   L=sqrt(h);       // comprimento da viga
#endif 
   prodesc=dx*vx+dy*vy+dz*vz; /* produto escalar entre o vetor de direção determinada pela
                                 linha de centro do elemento e o vetor contido no plano xy */
   v1[0]=vx-dx*(prodesc/h);  /* determinação da componente x do vetor ortogonal ao vetor que passa
                                pelos centróides das seções transversais ao longo do elemento*/
   v1[1]=vy-dy*(prodesc/h);  /* determinação da componente y do vetor ortogonal ao vetor que passa
                                pelos centróides das seções transversais ao longo do elemento*/
   v1[2]=vz-dz*(prodesc/h);  /* determinação da componente z do vetor ortogonal ao vetor que passa
                                pelos centróides das seções transversais ao longo do elemento*/   
   v2[0]=v1[2]*dy-v1[1]*dz;  // coordenada X do vetor na direção e sentido do eixo z local   
   v2[1]=v1[0]*dz-v1[2]*dx;  // coordenada Y do vetor na direção e sentido do eixo z local 
   v2[2]=v1[1]*dx-v1[0]*dy;  // coordenada Z do vetor na direção e sentido do eixo z local 
   
   csa1=(dx*1+dy*0+dz*0)/(L*(sqrt(double(1*1+0*0+0*0))));  //coseno do angulo formado entre os eixos x local e X global
   csa2=(dx*0+dy*1+dz*0)/(L*(sqrt(double(0*0+1*1+0*0))));  //coseno do angulo formado entre os eixos x local e Y global
   csa3=(dx*0+dy*0+dz*1)/(L*(sqrt(double(0*0+0*0+1*1))));  //coseno do angulo formado entre os eixos x local e Z global
   h1=v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2];
#ifdef ALEATORIO
   L1=h1.asqrt();     // comprimento da viga
#else
   L1=sqrt(h1);       // comprimento da viga
#endif
   csb1=(v1[0]*1+v1[1]*0+v1[2]*0)/(L1*(sqrt(double(1*1+0*0+0*0)))); //coseno do angulo formado entre os eixos y local e X global
   csb2=(v1[0]*0+v1[1]*1+v1[2]*0)/(L1*(sqrt(double(0*0+1*1+0*0)))); //coseno do angulo formado entre os eixos y local e Y global
   csb3=(v1[0]*0+v1[1]*0+v1[2]*1)/(L1*(sqrt(double(0*0+0*0+1*1)))); //coseno do angulo formado entre os eixos y local e Z global
   h2=v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2];
#ifdef ALEATORIO
   L2=h2.asqrt();     // comprimento da viga
#else
   L2=sqrt(h2);       // comprimento da viga
#endif
   csg1=(v2[0]*1+v2[1]*0+v2[2]*0)/(L2*(sqrt(double(1*1+0*0+0*0)))); //coseno do angulo formado entre os eixos z local e X global
   csg2=(v2[0]*0+v2[1]*1+v2[2]*0)/(L2*(sqrt(double(0*0+1*1+0*0)))); //coseno do angulo formado entre os eixos z local e Y global
   csg3=(v2[0]*0+v2[1]*0+v2[2]*1)/(L2*(sqrt(double(0*0+0*0+1*1)))); //coseno do angulo formado entre os eixos z local e Z global

   for (int i=0;i<12;i++)
      for (int j=0;j<12;j++)
         K[i][j]=T[i][j]=0.0;

#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      a=E*A/L;
      G=E/(um*2.0*(um+ni));
      bz=E*Iz/(L*L*L);  
      by=E*Iy/(L*L*L);
      t=G*J/L;
   K[0][0]=K[6][6]=a;     //MATRIZ K DESCONSIDERANDO DEFORMAÇÕES POR CISALHAMENTO
   K[0][6]=K[6][0]=-K[0][0];
   K[1][1]=K[7][7]=bz*12.0;
   K[1][7]=K[7][1]=-K[1][1];
   K[5][5]=K[11][11]=bz*L*L*4.0;
   K[5][11]=K[11][5]=bz*L*L*2.0;
   K[1][5]=K[5][1]=K[11][1]=K[1][11]=bz*L*6.0;
   K[11][7]=K[7][11]=K[7][5]=K[5][7]=-K[1][5];
   K[10][4]=K[4][10]=by*L*L*2.0;
   K[2][2]=K[8][8]=by*12.0;
   K[2][8]=K[8][2]=-K[2][2];
   K[4][4]=K[10][10]=by*L*L*4.0;
   K[2][4]=K[4][2]=K[10][2]=K[2][10]=-by*L*6.0;
   K[10][8]=K[8][10]=K[8][4]=K[4][8]=-K[2][4];
   K[3][3]=K[9][9]=t;
   K[9][3]=K[3][9]=-K[3][3]; 
   
   T[0][0]=T[6][6]=T[3][3]=T[9][9]=csa1;
   T[1][1]=T[7][7]=T[4][4]=T[10][10]=csb2;
   T[2][2]=T[8][8]=T[5][5]=T[11][11]=csg3;
   T[0][1]=T[6][7]=T[3][4]=T[9][10]=csb1;
   T[0][2]=T[6][8]=T[3][5]=T[9][11]=csg1;
   T[1][0]=T[7][6]=T[4][3]=T[10][9]=csa2;
   T[1][2]=T[7][8]=T[4][5]=T[10][11]=csg2;
   T[2][0]=T[8][6]=T[5][3]=T[11][9]=csa3;
   T[2][1]=T[8][7]=T[5][4]=T[11][10]=csb3;  
   
   for (int i=0;i<12;i++)
      for (int j=0;j<12;j++)
         for (int l=0;l<12;l++)
            for (int m=0;m<12;m++)
               k[12*i+m]+=T[i][j]*K[j][l]*T[m][l];

}
