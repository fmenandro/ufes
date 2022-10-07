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
#include "tubo.h"

Tubo::Tubo():elemento(dim,ipn,nno,prp,ptg,nlb)
{
}

Tubo::~Tubo()
{
}
void Tubo::monta_b()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      E,A,I,J,ni,L,Di,De,alfa,R,e,Lxz,d,xx[2],yy[2],zz[2],v1[3],v2[3],dx,dy,dz,h,hxz,prodesc,csa1,csa2,csa3,csb1,csb2,csb3,csg1,csg2,csg3,cl[6][6],B[6][12],T[12][12],Ti[6][6],X,um=1.0;
   for (int i=0;i<qnlb();i++)
      for (int j=0;j<12;j++)
      {
         b[i*+j]=0.0;
         B[i][j]=0.0;
      }
   E=this->pmaterial->qE();
   ni=this->pmaterial->qni();
   Di=this->prop[0];
   De=this->prop[1];
   alfa=this->prop[2];
   R=(De+Di)/4;
   e=(De-Di)/2; //espessura da parede do tubo.
   A=(3.141592653/4)*(De*De-Di*Di); 
//   As=A/2;
   I=(3.141592653/64)*(De*De*De*De-Di*Di*Di*Di); 
   J=(3.141592653/32)*(De*De*De*De-Di*Di*Di*Di); 
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
   hxz=dx*dx+dz*dz;
#ifdef ALEATORIO
   L=h.asqrt();     // comprimento da viga
   Lxz=hxz.asqrt();
#else
   L=sqrt(h);       // comprimento da viga
   Lxz=sqrt(hxz);
#endif
   d=0.0001*L; 
   cout<<"h = "<<h<<"\n";
   cout<<"L = "<<L<<"\n";
   cout<<"Lxz = "<<Lxz<<"\n";  
    
   if(Lxz>d)
   {  
      prodesc=dx*0+dy*1+dz*0;  /* produto escalar entre o vetor de direção determinada pela
                                  linha de centro do elemento e o vetor y */
      v1[0]=0-dx*(prodesc/h);  /* determinação da componente x do vetor ortogonal ao vetor que passa
                                  pelos centróides das seções transversais ao longo do elemento */
      v1[1]=1-dy*(prodesc/h);  /* determinação da componente y do vetor ortogonal ao vetor que passa
                                  pelos centróides das seções transversais ao longo do elemento */
      v1[2]=0-dz*(prodesc/h);  /* determinação da componente z do vetor ortogonal ao vetor que passa
                                  pelos centróides das seções transversais ao longo do elemento */                         
   }
   else
   {
      prodesc=dx*(-1)+dy*0+dz*0; 
      v1[0]=-1-dx*(prodesc/h);
      v1[1]=0-dy*(prodesc/h);
      v1[2]=0-dz*(prodesc/h);  
   }  
  
   cout<<"prodesc = "<<prodesc<<"\n";
   
   for (int l=0;l<3;l++)
   { 
      cout<<"v1["<<l<<"] = "<<v1[l]<<"\n";
   } 
   
   v2[0]=v1[2]*dy-v1[1]*dz;  // coordenada x do vetor na direção e sentido do eixo z local 
   v2[1]=v1[0]*dz-v1[2]*dx;  // coordenada y do vetor na direção e sentido do eixo z local 
   v2[2]=v1[1]*dx-v1[0]*dy;  // coordenada z do vetor na direção e sentido do eixo z local 
   
   for (int l=0;l<3;l++)
   { 
     cout<<"v2["<<l<<"] = "<<v2[l]<<"\n";
   }   
   
   csa1=(dx*1+dy*0+dz*0)/((sqrt(dx*dx+dy*dy+dz*dz))*(sqrt(double(1*1+0*0+0*0))));  //coseno do angulo formado entre os eixos x local e X global
   csa2=(dx*0+dy*1+dz*0)/((sqrt(dx*dx+dy*dy+dz*dz))*(sqrt(double(0*0+1*1+0*0))));  //coseno do angulo formado entre os eixos x local e Y global
   csa3=(dx*0+dy*0+dz*1)/((sqrt(dx*dx+dy*dy+dz*dz))*(sqrt(double(0*0+0*0+1*1))));  //coseno do angulo formado entre os eixos x local e Z global
   csb1=(v1[0]*1+v1[1]*0+v1[2]*0)/((sqrt(v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2]))*(sqrt(double(1*1+0*0+0*0)))); //coseno do angulo formado entre os eixos y local e X global
   csb2=(v1[0]*0+v1[1]*1+v1[2]*0)/((sqrt(v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2]))*(sqrt(double(0*0+1*1+0*0)))); //coseno do angulo formado entre os eixos y local e Y global
   csb3=(v1[0]*0+v1[1]*0+v1[2]*1)/((sqrt(v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2]))*(sqrt(double(0*0+0*0+1*1)))); //coseno do angulo formado entre os eixos y local e Z global
   csg1=(v2[0]*1+v2[1]*0+v2[2]*0)/((sqrt(v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2]))*(sqrt(double(1*1+0*0+0*0)))); //coseno do angulo formado entre os eixos z local e X global
   csg2=(v2[0]*0+v2[1]*1+v2[2]*0)/((sqrt(v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2]))*(sqrt(double(0*0+1*1+0*0)))); //coseno do angulo formado entre os eixos z local e Y global
   csg3=(v2[0]*0+v2[1]*0+v2[2]*1)/((sqrt(v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2]))*(sqrt(double(0*0+0*0+1*1)))); //coseno do angulo formado entre os eixos z local e Z global
   
   cout<<"csa1= "<<csa1<<"\n";
   cout<<"csa2= "<<csa2<<"\n";
   cout<<"csa3= "<<csa3<<"\n";
   cout<<"csb1= "<<csb1<<"\n";
   cout<<"csb2= "<<csb2<<"\n";
   cout<<"csb3= "<<csb3<<"\n";
   cout<<"csg1= "<<csg1<<"\n";
   cout<<"csg2= "<<csg2<<"\n";
   cout<<"csg3= "<<csg3<<"\n";   
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
   
/*   T[0][0]=T[7][7]=T[3][3]=T[10][10]=csa1;
   T[1][1]=T[8][8]=T[4][4]=T[12][12]=csb2;
   T[2][2]=T[9][9]=T[5][5]=T[12][12]=csg3;
   T[0][1]=T[7][8]=T[3][4]=T[10][11]=csb1;
   T[0][2]=T[7][9]=T[3][5]=T[10][12]=csg1;
   T[1][0]=T[8][7]=T[4][3]=T[11][10]=csa2;
   T[1][2]=T[8][9]=T[4][5]=T[11][12]=csg2;
   T[2][0]=T[9][7]=T[5][3]=T[12][10]=csa3;
   T[2][1]=T[9][8]=T[5][4]=T[12][11]=csb3;   
   T[6][6]=T[13][13]=1.0;   */
   
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
   
/*   B[0][0]=-um/L;
   B[0][7]=-B[0][0];
   B[3][3]=-um/L;
   B[3][10]=-B[3][3];
   B[4][2]=-(((X*12.0)/L)-(um*6.0))/(L*L);
   B[4][4]=(((X*6.0)/L)-(um*4.0))/L;
   B[4][9]=-B[4][2];
   B[4][11]=(((X*6.0)/L)-(um*2.0))/L;
   B[5][1]=(((X*12.0)/L)-(um*6.0))/(L*L);
   B[5][5]=(((X*6.0)/L)-(um*4.0))/L;
   B[5][8]=-B[5][1];
   B[5][12]=(((X*6.0)/L)-(um*2.0))/L;
   B[1][1]=(um*12.0)/(L*L*L);
   B[1][5]=B[1][12]=(um*6.0)/(L*L);
   B[1][8]=-B[1][1];
   B[2][2]=(um*12.0)/(L*L*L);
   B[2][4]=B[2][11]=-(um*6.0)/(L*L);
   B[2][9]=-B[2][2];     
   B[6][6]=um/R;
   B[6][13]=um/R;  */
      
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

/*   for (int i=0;i<qnlb()*qnlb();i++)  //matriz c utilizada para determinação das deformações
      c[i]=0.0;      
   c[0]=pmaterial->E*A;
   c[7]=pmaterial->E*I;
   c[14]=pmaterial->E*I;
   c[21]=pmaterial->E*J/(2.0*(1.0+pmaterial->ni)); 
   c[28]=pmaterial->E*I;
   c[35]=pmaterial->E*I;  */
   
/*   c[0]=pmaterial->E*A;
   c[8]=pmaterial->E*I;
   c[16]=pmaterial->E*I;
   c[24]=pmaterial->E*J/(2.0*(1.0+pmaterial->ni)); 
   c[32]=pmaterial->E*I;
   c[40]=pmaterial->E*I;   
   c[48]=pmaterial->E*I;    */  
   
   for (int i=0;h<qnlb();h++)      //matriz c utilizada para determinação das deformações
      for (int j=0;i<qnlb();i++)
         cl[i][j]=0.0;
   cl[0][0]=E*e/(R*R);    
   cl[1][1]=E*I;    
   cl[2][2]=E*I; //0.0;
   cl[3][3]=E*I; //E*J/(2.0*(1.0+pmaterial->ni)); 
   cl[4][4]=E*J/(2.0*(1.0+ni)); //E*I;    
   cl[5][5]=E*I;
   
   Ti[0][0]=1.0;
   Ti[1][1]=Ti[2][2]=cos(alfa)*cos(alfa);
   Ti[2][1]=Ti[1][2]=sin(alfa)*sin(alfa); 
   Ti[1][5]=-2*sin(alfa)*cos(alfa);
   Ti[2][5]=-Ti[1][5];
   Ti[3][3]=Ti[4][4]=cos(alfa);
   Ti[3][4]=sin(alfa);  
   Ti[4][3]=-Ti[3][4];
   Ti[5][1]=sin(alfa)*cos(alfa);
   Ti[5][2]=-Ti[5][1];
   Ti[5][5]=cos(alfa)*cos(alfa)-sin(alfa)*sin(alfa);
   
   for (int i=0;i<6;i++)
      for (int j=0;j<6;j++)
         for (int l=0;l<6;l++)
            c[12*i+l]+=Ti[i][j]*cl[j][l];    
   
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

void Tubo::monta_c()  //matriz c utilizada para determinação das tensões
{  double
     E,A,I,J,ni,Di,De,e,Rm,alfa,T[6][6],Ti[6][6],cl[6][6];
   E=this->pmaterial->qE();
   ni=this->pmaterial->qni();
   Di=this->prop[0];
   De=this->prop[1];
   alfa=this->prop[2];
   Rm=(Di+De)/4.;
   e=(De-Di)/2.; //espessura da parede do tubo.
   A=(3.141592653/4.)*(De*De-Di*Di); 
//   As=A/2;
   I=(3.141592653/64.)*(De*De*De*De-Di*Di*Di*Di); 
   J=(3.141592653/32.)*(De*De*De*De-Di*Di*Di*Di);
   
   for (int i=0;i<6;i++)
      for (int j=0;j<6;j++)
         T[i][j]=0.0;
         
   T[0][0]=1.0;
   T[1][1]=T[2][2]=cos(alfa)*cos(alfa);
   T[2][1]=T[1][2]=sin(alfa)*sin(alfa); 
   T[1][5]=2*sin(alfa)*cos(alfa);
   T[2][5]=-T[1][5];
   T[3][3]=T[4][4]=cos(alfa);
   T[3][4]=sin(alfa);  
   T[4][3]=-T[3][4];
   T[5][1]=-sin(alfa)*cos(alfa);
   T[5][2]=-T[5][1];
   T[5][5]=cos(alfa)*cos(alfa)-sin(alfa)*sin(alfa);  
   
/*   T[0][0]=T[6][6]=1.0;
   T[1][1]=T[2][2]=T[7][7]=T[8][8]=cos(alfa)*cos(alfa);
   T[2][1]=T[1][2]=T[8][7]=T[7][8]=sin(alfa)*sin(alfa); 
   T[1][5]=T[7][11]=2*sin(alfa)*cos(alfa);
   T[2][5]=T[8][11]=-T[1][5];
   T[3][3]=T[4][4]=T[9][9]=T[10][10]=cos(alfa);
   T[3][4]=T[9][10]=sin(alfa);  
   T[4][3]=T[10][9]=-T[3][4];
   T[5][1]=T[11][7]=-sin(alfa)*cos(alfa);
   T[5][2]=T[11][8]=-T[5][1];
   T[5][5]=T[11][11]=cos(alfa)*cos(alfa)-sin(alfa)*sin(alfa);  */
   
   for (int i=0;i<6;i++)
      for (int j=0;j<6;j++)
         Ti[i][j]=T[i][j]; 
   Ti[1][5]=-T[1][5];
   Ti[2][5]=-Ti[1][5];
   Ti[5][1]=-T[5][1];
   Ti[5][2]=-Ti[5][1];  
   
/*   Ti[0][0]=1.0;
   Ti[1][1]=Ti[2][2]=cos(alfa)*cos(alfa);
   Ti[2][1]=Ti[1][2]=sin(alfa)*sin(alfa); 
   Ti[1][5]=-2*sin(alfa)*cos(alfa);
   Ti[2][5]=-Ti[1][5];
   Ti[3][3]=Ti[4][4]=cos(alfa);
   Ti[3][4]=sin(alfa);  
   Ti[4][3]=-Ti[3][4];
   Ti[5][1]=sin(alfa)*cos(alfa);
   Ti[5][2]=-Ti[5][1];
   Ti[5][5]=cos(alfa)*cos(alfa)-sin(alfa)*sin(alfa);   */
   
/*   for (int i=0;i<qnlb()*qnlb();i++)
      c[i]=0.0;
   c[0]=1.0/A;
   c[7]=1.5/A;  //para tensão cisalhante maxima em vigas de seção transversal retangular
   c[14]=1.5/A;
   c[21]=(De/2)/J; //para tensão cisalhante maxima 
   c[28]=1.5/A;
   c[35]=1.5/A; */
   
   for (int i=0;i<6;i++)
      for (int j=0;j<6;j++)
         cl[i][j]=0.0; 
   cl[0][0]=((E*(1-ni))/((1+ni)*(1-2*ni)))*1;
   cl[0][1]=((E*(1-ni))/((1+ni)*(1-2*ni)))*ni/(1-ni);
   cl[0][2]=((E*(1-ni))/((1+ni)*(1-2*ni)))*ni/(1-ni);
   cl[1][0]=((E*(1-ni))/((1+ni)*(1-2*ni)))*ni/(1-ni);
   cl[1][2]=((E*(1-ni))/((1+ni)*(1-2*ni)))*1;
   cl[1][3]=((E*(1-ni))/((1+ni)*(1-2*ni)))*ni/(1-ni); 
   cl[2][0]=((E*(1-ni))/((1+ni)*(1-2*ni)))*ni/(1-ni);
   cl[2][1]=((E*(1-ni))/((1+ni)*(1-2*ni)))*ni/(1-ni);
   cl[2][2]=((E*(1-ni))/((1+ni)*(1-2*ni)))*1;
   cl[3][3]=((E*(1-ni))/((1+ni)*(1-2*ni)))*(1-2*ni)/(2*(1-ni));
   cl[4][4]=((E*(1-ni))/((1+ni)*(1-2*ni)))*(1-2*ni)/(2*(1-ni));
   cl[5][5]=((E*(1-ni))/((1+ni)*(1-2*ni)))*(1-2*ni)/(2*(1-ni));  
   
   for (int i=0;i<6;i++)
      for (int j=0;j<6;j++)
         for (int l=0;l<6;l++)
            for (int m=0;m<6;m++)
               c[6*i+m]+=Ti[i][j]*cl[j][l]*Ti[m][l];
   
/*   c[0]=1.0/A;
   c[8]=1.5/A;  //para tensão cisalhante maxima em vigas de seção transversal retangular
   c[16]=1.5/A;
   c[24]=(De/2)/J; //para tensão cisalhante maxima 
   c[32]=1.5/A;
   c[40]=1.5/A;  
   c[48]=1.0/Rm;  */
}
void Tubo::monta_rigidez()
{
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      E,A,I,J,ni,G,t,re,ri,p,r,L,Lxz,d,D,Di,De,e,xx[2],yy[2],zz[2],v1[3],v2[3],prodesc,dx,dy,dz,h,hxz,csa1,csa2,csa3,csb1,csb2,csb3,csg1,csg2,csg3,b,K[12][12],T[12][12];
   E=this->pmaterial->qE();
   ni=this->pmaterial->qni();   
   Di=this->prop[0];
   De=this->prop[1];
   e=(De-Di)/2; //espessura da parede do tubo.
   A=(3.141592653/4)*(De*De-Di*Di); 
//   As=A/2;
   I=(3.141592653/64)*(De*De*De*De-Di*Di*Di*Di); //Momento de Inércia da seção transversal em relação a y e Z
   D=(De+Di)/2;
//   if(D>10*e)
//     J=2*3.141592653*r*r*r*e;
//   else
     J=(3.141592653/32)*(De*De*De*De-Di*Di*Di*Di);   //Momento polar de Inércia da seção transversal
   xx[0]=this->pno[0]->qx(0);  //coordenada x do nó 1
   xx[1]=this->pno[1]->qx(0);  //coordenada x do nó 2
   yy[0]=this->pno[0]->qx(1);  //coordenada y do nó 1
   yy[1]=this->pno[1]->qx(1);  //coordenada y do nó 2
   zz[0]=this->pno[0]->qx(2);  //coordenada z do nó 1
   zz[1]=this->pno[1]->qx(2);  //coordenada z do nó 2
   dx=xx[1]-xx[0];
   dy=yy[1]-yy[0];
   dz=zz[1]-zz[0];   
   h=dx*dx+dy*dy+dz*dz;
   hxz=dx*dx+dz*dz;
#ifdef ALEATORIO
   L=h.asqrt();     // comprimento da viga
   Lxz=hxz.asqrt();
#else
   L=sqrt(h);       // comprimento da viga
   Lxz=sqrt(hxz);
#endif
   d=0.0001*L; 
   cout<<"h = "<<h<<"\n";
   cout<<"L = "<<L<<"\n";
   cout<<"Lxz = "<<Lxz<<"\n";  
    
   if(Lxz>d)
   {  
      prodesc=dx*0+dy*1+dz*0;  /* produto escalar entre o vetor de direção determinada pela
                                  linha de centro do elemento e o vetor y */
      v1[0]=0-dx*(prodesc/h);  /* determinação da componente x do vetor ortogonal ao vetor que passa
                                  pelos centróides das seções transversais ao longo do elemento */
      v1[1]=1-dy*(prodesc/h);  /* determinação da componente y do vetor ortogonal ao vetor que passa
                                  pelos centróides das seções transversais ao longo do elemento */
      v1[2]=0-dz*(prodesc/h);  /* determinação da componente z do vetor ortogonal ao vetor que passa
                                  pelos centróides das seções transversais ao longo do elemento */                       
   }
   else
   {
      prodesc=dx*(-1)+dy*0+dz*0; 
      v1[0]=-1-dx*(prodesc/h);
      v1[1]=0-dy*(prodesc/h);
      v1[2]=0-dz*(prodesc/h);  
   }  
  
   cout<<"prodesc = "<<prodesc<<"\n";
   
   for (int l=0;l<3;l++)
   { 
      cout<<"v1["<<l<<"] = "<<v1[l]<<"\n";
   } 
   
   v2[0]=v1[2]*dy-v1[1]*dz;  // coordenada x do vetor na direção e sentido do eixo z local 
   v2[1]=v1[0]*dz-v1[2]*dx;  // coordenada y do vetor na direção e sentido do eixo z local 
   v2[2]=v1[1]*dx-v1[0]*dy;  // coordenada z do vetor na direção e sentido do eixo z local 
   
   for (int l=0;l<3;l++)
   { 
     cout<<"v2["<<l<<"] = "<<v2[l]<<"\n";
   }   
   
   csa1=(dx*1+dy*0+dz*0)/((sqrt(double(dx*dx+dy*dy+dz*dz)))*(sqrt(double(1*1+0*0+0*0))));  //coseno do angulo formado entre os eixos x local e X global
   csa2=(dx*0+dy*1+dz*0)/((sqrt(double(dx*dx+dy*dy+dz*dz)))*(sqrt(double(0*0+1*1+0*0))));  //coseno do angulo formado entre os eixos x local e Y global
   csa3=(dx*0+dy*0+dz*1)/((sqrt(double(dx*dx+dy*dy+dz*dz)))*(sqrt(double(0*0+0*0+1*1))));  //coseno do angulo formado entre os eixos x local e Z global
   csb1=(v1[0]*1+v1[1]*0+v1[2]*0)/((sqrt(double(v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2])))*(sqrt(double(1*1+0*0+0*0)))); //coseno do angulo formado entre os eixos y local e X global
   csb2=(v1[0]*0+v1[1]*1+v1[2]*0)/((sqrt(double(v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2])))*(sqrt(double(0*0+1*1+0*0)))); //coseno do angulo formado entre os eixos y local e Y global
   csb3=(v1[0]*0+v1[1]*0+v1[2]*1)/((sqrt(double(v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2])))*(sqrt(double(0*0+0*0+1*1)))); //coseno do angulo formado entre os eixos y local e Z global
   csg1=(v2[0]*1+v2[1]*0+v2[2]*0)/((sqrt(double(v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2])))*(sqrt(double(1*1+0*0+0*0)))); //coseno do angulo formado entre os eixos z local e X global
   csg2=(v2[0]*0+v2[1]*1+v2[2]*0)/((sqrt(double(v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2])))*(sqrt(double(0*0+1*1+0*0)))); //coseno do angulo formado entre os eixos z local e Y global
   csg3=(v2[0]*0+v2[1]*0+v2[2]*1)/((sqrt(double(v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2])))*(sqrt(double(0*0+0*0+1*1)))); //coseno do angulo formado entre os eixos z local e Z global
   
   cout<<"csa1= "<<csa1<<"\n";
   cout<<"csa2= "<<csa2<<"\n";
   cout<<"csa3= "<<csa3<<"\n";
   cout<<"csb1= "<<csb1<<"\n";
   cout<<"csb2= "<<csb2<<"\n";
   cout<<"csb3= "<<csb3<<"\n";
   cout<<"csg1= "<<csg1<<"\n";
   cout<<"csg2= "<<csg2<<"\n";
   cout<<"csg3= "<<csg3<<"\n";
   for (int i=0;i<12;i++)
      for (int j=0;j<12;j++)
         K[i][j]=T[i][j]=0.0;

#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
      a=E*A/L;
      G=E/(2*(1+ni));
      b=E*I/(L*L*L);  
      t=G*J/L;
      r=(De+Di)/4;
      re=De/2;
      ri=Di/2;
      
      p=e*E/(r*r); 
 
      
   K[0][0]=K[6][6]=a;     //MATRIZ K DESCONSIDERANDO DEFORMAÇÕES POR CISALHAMENTO
   K[0][6]=K[6][0]=-K[0][0];
   K[1][1]=K[7][7]=b*12.0;
   K[1][7]=K[7][1]=-K[1][1];
   K[5][5]=K[11][11]=4.0*b*L*L;
   K[5][11]=K[11][5]=2.0*b*L*L;
   K[1][5]=K[5][1]=K[11][1]=K[1][11]=6.0*b*L;
   K[11][7]=K[7][11]=K[7][5]=K[5][7]=-K[1][5];
   K[10][4]=K[4][10]=2.0*b*L*L;
   K[2][2]=K[8][8]=12.0*b;
   K[2][8]=K[8][2]=-K[2][2];
   K[4][4]=K[10][10]=4*b*L*L;
   K[2][4]=K[4][2]=K[10][2]=K[2][10]=-6.0*b*L;
   K[10][8]=K[8][10]=K[8][4]=K[4][8]=-K[2][4];
   K[3][3]=K[9][9]=t;
   K[9][3]=K[3][9]=-K[3][3]; 
   
/*   K[0][0]=K[7][7]=a;     //MATRIZ K DESCONSIDERANDO DEFORMAÇÕES POR CISALHAMENTO
   K[0][7]=K[7][0]=-K[0][0];
   K[1][1]=K[8][8]=b*12.0;
   K[1][8]=K[8][1]=-K[1][1];
   K[5][5]=K[12][12]=4.0*b*L*L;
   K[5][12]=K[12][5]=2.0*b*L*L;
   K[1][5]=K[5][1]=K[12][1]=K[1][12]=6.0*b*L;
   K[12][8]=K[8][12]=K[8][5]=K[5][8]=-K[1][5];
   K[11][4]=K[4][11]=2.0*b*L*L;
   K[2][2]=K[9][9]=12.0*b;
   K[2][9]=K[9][2]=-K[2][2];
   K[4][4]=K[11][11]=4*b*L*L;
   K[2][4]=K[4][2]=K[11][2]=K[2][11]=-6.0*b*L;
   K[11][9]=K[9][11]=K[9][4]=K[4][9]=-K[2][4];
   K[3][3]=K[10][10]=t;
   K[10][3]=K[3][10]=-K[3][3]; 
   K[6][6]=K[13][13]=p; */
   
   T[0][0]=T[6][6]=T[3][3]=T[9][9]=csa1;
   T[1][1]=T[7][7]=T[4][4]=T[10][10]=csb2;
   T[2][2]=T[8][8]=T[5][5]=T[11][11]=csg3;
   T[0][1]=T[6][7]=T[3][4]=T[9][10]=csb1;
   T[0][2]=T[6][8]=T[3][5]=T[9][11]=csg1;
   T[1][0]=T[7][6]=T[4][3]=T[10][9]=csa2;
   T[1][2]=T[7][8]=T[4][5]=T[10][11]=csg2;
   T[2][0]=T[8][6]=T[5][3]=T[11][9]=csa3;
   T[2][1]=T[8][7]=T[5][4]=T[11][10]=csb3;  
   
/*   T[0][0]=T[7][7]=T[3][3]=T[10][10]=csa1;
   T[1][1]=T[8][8]=T[4][4]=T[12][12]=csb2;
   T[2][2]=T[9][9]=T[5][5]=T[12][12]=csg3;
   T[0][1]=T[7][8]=T[3][4]=T[10][11]=csb1;
   T[0][2]=T[7][9]=T[3][5]=T[10][12]=csg1;
   T[1][0]=T[8][7]=T[4][3]=T[11][10]=csa2;
   T[1][2]=T[8][9]=T[4][5]=T[11][12]=csg2;
   T[2][0]=T[9][7]=T[5][3]=T[12][10]=csa3;
   T[2][1]=T[9][8]=T[5][4]=T[12][11]=csb3;   
   T[6][6]=T[13][13]=1.0;  */
   
   for (int i=0;i<12;i++)
      for (int j=0;j<12;j++)
         for (int l=0;l<12;l++)
            for (int m=0;m<12;m++)
               k[12*i+m]+=T[i][j]*K[j][l]*T[m][l];

}

