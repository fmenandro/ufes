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
#include "elemento.h"

// Funcoes membro da Classe elemento


elemento::elemento()
{
};

elemento::elemento(int dim, int ipn, int nno, int prp, int ptg, int nlb)
{
   no=new int[nno];
   pno=new class no*[nno];
   material=0;
   ro=0.5;
   p=3.0;
   dc=0.0;
   dcn=0.0;
   pmaterial=NULL;
#ifdef ALEATORIO
   prop=new class aleatorio[prp];
   k = new class aleatorio[nno*ipn*nno*ipn];
   b = new class aleatorio[nlb*nno*ipn];
   c = new class aleatorio[nlb*nlb];
   x = new class aleatorio[nno*ipn];
   f = new class aleatorio[nno*ipn];
   ten = new class aleatorio[dim*nlb*ptg];
   def = new class aleatorio[dim*nlb*ptg];
#else
   prop=new double[prp];
   k = new double[nno*ipn*nno*ipn];
   b = new double[nlb*nno*ipn];
   c = new double[nlb*nlb];
   x = new double[nno*ipn];
   f = new double[nno*ipn];
   if (dim==1)
   {
      ten = new double[nlb*ptg];
      def = new double[nlb*ptg];
   }
   else if (dim==2)
   {
      ten = new double[nlb*ptg*ptg];
      def = new double[nlb*ptg*ptg];
   }
   else
   {
      ten = new double[nlb*ptg*ptg*ptg];
      def = new double[nlb*ptg*ptg*ptg];
   }
#endif
};

// Adicionado por Renan
elemento::elemento(int dim, int ipn, int nno, int prp, int ptg, int nlb, int poli)
{
	// poli: quando existente (= 1) indica que o elemento é poligonal 2d
	no = new int[nno];
	pno = new class no*[nno];
	material = 0;
	ro = 0.5;
	p = 3.0;
	dc = 0.0;
	dcn = 0.0;
	pmaterial = NULL;
#ifdef ALEATORIO
	prop = new class aleatorio[prp];
	k = new class aleatorio[nno*ipn*nno*ipn];
	b = new class aleatorio[nlb*nno*ipn];
	c = new class aleatorio[nlb*nlb];
	x = new class aleatorio[nno*ipn];
	f = new class aleatorio[nno*ipn];
	ten = new class aleatorio[dim*nlb*ptg];
	def = new class aleatorio[dim*nlb*ptg];
#else
	prop = new double[prp];
	k = new double[nno*ipn*nno*ipn];
	b = new double[nlb*nno*ipn];
	c = new double[nlb*nlb];
	x = new double[nno*ipn];
	f = new double[nno*ipn];
	if (dim == 1)
	{
		ten = new double[nlb*ptg];
		def = new double[nlb*ptg];
	}
	else if (dim == 2)
	{
		ten = new double[nlb*ptg*nno];	// A diferenca está aqui
		def = new double[nlb*ptg*nno];
	}
	else
	{
		ten = new double[nlb*ptg*ptg*ptg];
		def = new double[nlb*ptg*ptg*ptg];
	}
#endif
};

elemento::~elemento(){delete no;delete pno;delete prop;delete k;delete b;};

void elemento::aponta_no(int i,class no *gno)
{
      this->pno[i]=gno;
};


void elemento::aponta_mat(class material *gmaterial)
{
     switch(gmaterial->qnum())
     {
        case 0:
           this->pmaterial=new class mat_termico;
	   break;
        case 1:
           this->pmaterial=new class mat_linear_elastico;
	   break;
        case 2:
           this->pmaterial=new class mat_termico_nao_linear;
	   break;
     }
   this->pmaterial=gmaterial;
};

void elemento::monta_rigidez()
{
   double peso;
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
int elemento::qmat()
{
   return(this->material);
};
int elemento::qno(int i)
{
   return(this->no[i]);
};
#ifdef ALEATORIO
class aleatorio elemento::qk(int i, int j)
#else
double elemento::qk(int i, int j)
#endif
{
   return(this->k[qpos(i,j)]);
};
#ifdef ALEATORIO
class aleatorio elemento::qro()
#else
double elemento::qro()
#endif
{
   return(this->ro);
};
#ifdef ALEATORIO
class aleatorio elemento::qrov()
#else
double elemento::qrov()
#endif
{
   return(this->rov);
};
#ifdef ALEATORIO
class aleatorio elemento::qrov()
#else
double elemento::qx(int i)
#endif
{
   return(this->x[i]);
};
#ifdef ALEATORIO
class aleatorio elemento::qdc()
#else
double elemento::qdc()
#endif
{
   return(this->dc);
};
#ifdef ALEATORIO
class aleatorio elemento::qdcn()
#else
double elemento::qdcn()
#endif
{
   return(this->dcn);
};
double elemento::qp()
{
   return(this->p);
};
#ifdef ALEATORIO
void elemento::upro(class aleatorio r)
#else
void elemento::upro(double r)
#endif
{
   this->ro=r;
};
#ifdef ALEATORIO
void elemento::uprov(class aleatorio r)
#else
void elemento::uprov(double r)
#endif
{
   this->rov=r;
};
#ifdef ALEATORIO
void elemento::updc(class aleatorio d)
#else
void elemento::updc(double d)
#endif
{
   this->dc=d;
};
#ifdef ALEATORIO
void elemento::updcn(class aleatorio d)
#else
void elemento::updcn(double d)
#endif
{
   this->dcn=d;
};
#ifdef ALEATORIO
class aleatorio elemento::qm(int i, int j){};
#else
double elemento::qm(int i, int j){return 0.0;};
#endif
int elemento::qpos(int i, int j)
{
   return(i*qnno()*qipn()+j);
};
void elemento::pontos_de_gauss(const int p,double *x, double *w)
{
switch (p)
{
case 1:
   x[0]=0.0;
   w[0]=2.0;
   break;
case 2:
   x[0]=-0.577350269189626;
   x[1]=0.577350269189626;
   w[0]=w[1]=1.0;
   break;
case 3:
   x[0]=-0.774596669241483;
   x[1]=0.0;
   x[2]=0.774596669241483;
   w[0]=w[2]=0.555555555555556;
   w[1]=0.888888888888889;
   break;
case 4:
   x[0]=-0.861136311594053;
   x[1]=-0.339981043584856;
   x[2]=0.339981043584856;
   x[3]=0.861136311594053;
   w[0]=w[3]=0.347854845137454;
   w[1]=w[2]=0.652145154862546;
   break;
case 5:
   x[0]=-0.906179845938664;
   x[1]=-0.538469310105683;
   x[2]=0.0;
   x[3]=0.538469310105683;
   x[4]=0.906179845938664;
   w[0]=w[4]=0.236926885056189;
   w[1]=w[3]=0.478628670499366;
   w[2]=0.568888888888889;
   break;
case 6:
   x[0]=-0.932469514203152;
   x[1]=-0.661209386466265;
   x[2]=-0.238619186083197;
   x[3]=0.238619186083197;
   x[4]=0.661209386466265;
   x[5]=0.932469514203152;
   w[0]=w[5]=0.171324492379170;
   w[1]=w[4]=0.360761573048139;
   w[2]=w[3]=0.467913934572691;
   break;
case 7:
   x[0]=-0.949107912342759;
   x[1]=-0.741531185599394;
   x[2]=-0.405845151377397;
   x[3]=0.0;
   x[4]=0.405845151377397;
   x[5]=0.741531185599394;
   x[6]=0.949107912342759;
   w[0]=w[6]=0.129484966168870;
   w[1]=w[5]=0.279705391489277;
   w[2]=w[4]=0.381830050505119;
   w[3]=0.417959183673469;
   break;
case 8:
   x[0]=-0.960289856497536;
   x[1]=-0.796666477413627;
   x[2]=-0.525532409916329;
   x[3]=-0.183434642495650;
   x[4]=0.183434642495650;
   x[5]=0.525532409916329;
   x[6]=0.796666477413627;
   x[7]=0.960289856497536;
   w[0]=w[7]=0.101228536290376;
   w[1]=w[6]=0.222381034453374;
   w[2]=w[5]=0.313706645877887;
   w[3]=w[4]=0.362683783378362;
   break;
case 9:
   x[0]=-0.968160239507626;
   x[1]=-0.836031107326636;
   x[2]=-0.613371432700590;
   x[3]=-0.324253432403809;
   x[4]=0.0;
   x[5]=0.324253432403809;
   x[6]=0.613371432700590;
   x[7]=0.836031107326636;
   x[8]=0.968160239507626;
   w[0]=w[8]=0.081274388361574;
   w[1]=w[7]=0.180648160694857;
   w[2]=w[6]=0.260610696402935;
   w[3]=w[5]=0.312347077040003;
   w[4]=0.330239355001260;
   break;
case 10:
   x[0]=-0.973906528517172;
   x[1]=-0.865063366688985;
   x[2]=-0.679409568299024;
   x[3]=-0.433395394129247;
   x[4]=-0.148874338981631;
   x[5]=0.148874338981631;
   x[6]=0.433395394129247;
   x[7]=0.679409568299024;
   x[8]=0.865063366688985;
   x[9]=0.973906528517172;
   w[0]=w[9]=0.066671344308688;
   w[1]=w[8]=0.149451349150581;
   w[2]=w[7]=0.219086362515982;
   w[3]=w[6]=0.269266719309996;
   w[4]=w[5]=0.295524224714753;
}
};
void elemento::monta_n(){};
void elemento::monta_b(){};
void elemento::monta_massa(){};
void elemento::monta_c(){};
#ifdef ALEATORIO
void elemento::p_processa(aleatorio *xx)
{
#else
void elemento::p_processa(double *xx)
{
#endif
   double *xpg,*wpg;
   xpg=new double[qptg()];
   wpg=new double[qptg()];
   pg=qptg();
   for (int i=0;i<qnno()*qipn();i++)
   {
      f[i]=0.0;
      for (int n=0;n<qnno();n++)
         for (int j=0;j<qipn();j++)
            f[j]+=qk(i,n*qipn()+j)*xx[qno(n)*qipn()+j];
   }
   for (int n=0;n<qnno();n++)
      for (int i=0;i<qipn();i++)
         x[n*qipn()+i]=xx[qno(n)*qipn()+i];
   pontos_de_gauss(pg,xpg,wpg);
   int lpg=qptg();
   if (qdim()==2) lpg*=lpg;
   if (qdim()==3) lpg*=lpg*lpg;
   for(pg=0;pg<lpg;pg++)
   {
      monta_b();
      for (int i=0;i<qnlb(); i++)
      {
         def[pg*qnlb()+i]=ten[pg*qnlb()+i]=0;
         for (int j=0;j<qnno()*qipn();j++)
            def[pg*qnlb()+i]+=b[i*qnno()*qipn()+j]*x[j];
      }
      monta_c();
      for (int i=0;i<qnlb(); i++)
      {
         for (int j=0;j<qnlb();j++)
            ten[pg*qnlb()+i]+=c[i*qnlb()+j]*def[j];
      }
   }
};

ostream& operator<<(ostream& co,elemento& e)
{
   co<<"  Numero de nos = "<<e.qnno()<<"\n  Material => "<<e.material<<"\n  Nos =>";
   for(int i=0;i<e.qnno();i++)
      co<<"\n    No "<<i<<" = "<<e.no[i];
   for(int i=0;i<e.qprp();i++)
      co<<"\n  Propriedade "<<i<<" = "<<e.prop[i];
   co<<"\n  Deformacao calculada";
   int lpg=e.qptg();
   if (e.qdim()==2) lpg*=lpg;
   if (e.qdim()==3) lpg*=lpg*lpg;
   for(int pg=0;pg<lpg;pg++)
   {
      co<<"\n    Ponto de Gauss "<<pg<<":";
      for(int i=0;i<e.qnlb();i++)
         co<<"\n      Componente "<<i<<" = "<<e.def[pg*e.qnlb()+i];
   }
   co<<"\n  Tensao calculada";
   for(int pg=0;pg<lpg;pg++)
   {
      co<<"\n    Ponto de Gauss "<<pg<<":";
      for(int i=0;i<e.qnlb();i++)
         co<<"\n      Componente "<<i<<" = "<<e.ten[pg*e.qnlb()+i];
   }
   co<<"\n  Deslocamentos Nodais";
   for(int i=0;i<e.qnno()*e.qipn();i++)
      co<<"\n x["<<i<<"] = "<<e.x[i];
   co<<"\n  Forcas Nodais";
   for(int i=0;i<e.qnno()*e.qipn();i++)
      co<<"\n f["<<i<<"] = "<<e.f[i];
   return co;
};

istream& operator>>(istream& ci, elemento& e)
{
   ci>>e.material;
   for(int i=0;i<e.qnno();i++)
      ci>>e.no[i];
   for(int i=0;i<e.qprp();i++)
      ci>>e.prop[i];
   return ci;
};

// RENAN COMENTOU PARA O ELEMENTO POLIGONAL, DEPOIS VOLTAR AO ORIGINAL
wxTextOutputStream& operator<<(wxTextOutputStream& co,elemento& e)
{
   co<<"  Numero de nos = "<<e.qnno()<<"\n  Material => "<<e.material<<"\n  Nos =>";
   for(int i=0;i<e.qnno();i++)
      co<<"\n    No "<<i<<" = "<<e.no[i];
   /*for(int i=0;i<e.qprp();i++)
      co<<"\n  Propriedade "<<i<<" = "<<e.prop[i];
   co<<"\n  Deformacao calculada";
   int lpg=e.qptg();
   if (e.qdim()==2) lpg*=lpg;
   if (e.qdim()==3) lpg*=lpg*lpg;
   for(int pg=0;pg<lpg;pg++)
   {
      co<<"\n    Ponto de Gauss "<<pg<<":";
      for(int i=0;i<e.qnlb();i++)
         co<<"\n      Componente "<<i<<" = "<<e.def[pg*e.qnlb()+i];
   }
   co<<"\n  Tensao calculada";
   for(int pg=0;pg<lpg;pg++)
   {
      co<<"\n    Ponto de Gauss "<<pg<<":";
      for(int i=0;i<e.qnlb();i++)
         co<<"\n      Componente "<<i<<" = "<<e.ten[pg*e.qnlb()+i];
   }
   co<<"\n  Deslocamentos Nodais";
   for(int i=0;i<e.qnno()*e.qipn();i++)
      co<<"\n x["<<i<<"] = "<<e.x[i];
   co<<"\n  Forcas Nodais";
   for(int i=0;i<e.qnno()*e.qipn();i++)
      co<<"\n f["<<i<<"] = "<<e.f[i];*/
   return co;
};

wxTextInputStream& operator>>(wxTextInputStream& ci, elemento& e)
{
   ci>>e.material;
   for(int i=0;i<e.qnno();i++)
      ci>>e.no[i];
   for(int i=0;i<e.qprp();i++)
      ci>>e.prop[i];
   return ci;
};
void elemento::draw(wxDC& dc, double xmed, double xdif, double ymed, double ydif)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    int dim=qdim(), nn=qnno();
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    switch(dim)
    {
    case 1:
       for(int i=0;i<nn-1;i++)
          dc.DrawLine( w/2.+(pno[i]->qx(0)-xmed)*(0.9*w)/xdif, 0.5*(h), w/2.+(pno[i+1]->qx(0)-xmed)*(0.9*w)/xdif, 0.5*(h) ); // draw line across the rectangle
       break;
    case 2:
        if(xdif/w>ydif/h)
        {
            for(int i=0;i<nn-1;i++)
                dc.DrawLine( w/2.+(pno[i]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[i]->qx(1)-ymed)*(0.9*w)/xdif, w/2.+(pno[i+1]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[i+1]->qx(1)-ymed)*(0.9*w)/xdif ); // draw line across the rectangle
//                dc.DrawLine( w/2.+(pno[qno(i)]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[qno(i)]->qx(1)-ymed)*(0.9*w)/xdif, w/2.+(pno[qno(i+1)]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[qno(i+1)]->qx(1)-ymed)*(0.9*w)/xdif ); // draw line across the rectangle
//            dc.DrawLine( w/2.+(pno[qno(nn-1)]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[qno(nn-1)]->qx(1)-ymed)*(0.9*w)/xdif, w/2.+(pno[qno(0)]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[qno(0)]->qx(1)-ymed)*(0.9*w)/xdif ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[nn-1]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[nn-1]->qx(1)-ymed)*(0.9*w)/xdif, w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*w)/xdif ); // draw line across the rectangle
        }
        else
        {
            for(int i=0;i<nn-1;i++)
                dc.DrawLine( w/2.+(pno[i]->qx(0)-xmed)*(0.9*h)/ydif,  h/2.-(pno[i]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+(pno[i+1]->qx(0)-xmed)*(0.9*h)/ydif,  h/2.-(pno[i+1]->qx(1)-ymed)*(0.9*h)/ydif ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[nn-1]->qx(0)-xmed)*(0.9*h)/ydif,  h/2.-(pno[nn-1]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+(pno[0]->qx(0)-xmed)*(0.9*h)/ydif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*h)/ydif ); // draw line across the rectangle
        }
      break;
    }
}
void elemento::draw(wxDC& dc, double xmed, double xdif, double ymed, double ydif, int e)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    int dim=qdim(), nn=qnno();
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    wxString E;
    E<<e;
    this->draw(dc,xmed,xdif,ymed,ydif);
    double xc=0.0;
    switch(dim)
    {
    case 1:
        for(int i=0;i<nn;i++)
            xc+=pno[i]->qx(0);
        xc/=nn;
        dc.DrawText( E,w/2.+(xc-xmed)*(0.9*w)/xdif, 0.5*(h) ); 
       break;
    case 2:
        double yc=0.0;
        for(int i=0;i<nn;i++)
        {
            xc+=pno[i]->qx(0);            
            yc+=pno[i]->qx(1);            
        }
        xc/=nn;yc/=nn;
        if(xdif/w>ydif/h)
        {
            dc.DrawText( E,w/2.+(xc-xmed)*(0.9*w)/xdif,  h/2.-(yc-ymed)*(0.9*w)/xdif); // draw line across the rectangle
        }
        else
        {
            dc.DrawText( E,w/2.+(xc-xmed)*(0.9*h)/ydif,  h/2.-(yc-ymed)*(0.9*h)/ydif); // draw line across the rectangle
        }
      break;
    }
}
void elemento::draw(wxDC& dc, double xmed, double xdif, double ymed, double ydif, double e)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    int dim=qdim(), nn=qnno();
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    wxString E;
    E<<e;
    this->draw(dc,xmed,xdif,ymed,ydif);
    double xc=0.0;
    switch(dim)
    {
    case 1:
        for(int i=0;i<nn;i++)
            xc+=pno[i]->qx(0);
        xc/=nn;
        dc.DrawText( E,w/2.+(xc-xmed)*(0.9*w)/xdif, 0.5*(h) ); 
       break;
    case 2:
        double yc=0.0;
        for(int i=0;i<nn;i++)
        {
            xc+=pno[i]->qx(0);            
            yc+=pno[i]->qx(1);            
        }
        xc/=nn;yc/=nn;
        if(xdif/w>ydif/h)
        {
            dc.DrawText( E,w/2.+(xc-xmed)*(0.9*w)/xdif,  h/2.-(yc-ymed)*(0.9*w)/xdif); // draw line across the rectangle
        }
        else
        {
            dc.DrawText( E,w/2.+(xc-xmed)*(0.9*h)/ydif,  h/2.-(yc-ymed)*(0.9*h)/ydif); // draw line across the rectangle
        }
      break;
    }
}
void elemento::draw(wxDC& dc, double xmed, double ymed, int d, double ddif, double zoom, double* view)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    int dim=qdim(), nn=qnno();
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    wxColour *tmpcolour;
    unsigned char c=255;
    unsigned char *r,*g,*b;
//    r = g = b = &c;
//    dc.SetBrush(wxColor(ro,0,1-ro));
    dc.SetBrush(wxColor(255,255*(1.-ro),255));
    switch(dim)
    {
    case 1:
       for(int i=0;i<nn-1;i++)
          dc.DrawLine( w/2.+(view[0]*pno[i]->qx(0)-xmed)*(zoom*d)/ddif, 0.5*(h)+(view[3]*pno[i]->qx(0)-ymed)*zoom*d/ddif, w/2.+(view[0]*pno[i+1]->qx(0)-xmed)*(zoom*d)/ddif, 0.5*(h)+(view[3]*pno[i+1]->qx(0)-ymed)*zoom*d/ddif ); // draw line across the rectangle
       break;
    case 2:
        double xm,ym;
        xm=pno[0]->qx(0);
        ym=pno[0]->qx(1);
        for(int i=0;i<nn-1;i++)
        {
            dc.DrawLine( w/2.+(view[0]*pno[i]->qx(0)+view[1]*pno[i]->qx(1)-xmed)*(zoom*d)/ddif,  h/2.-(view[3]*pno[i]->qx(0)+view[4]*pno[i]->qx(1)-ymed)*(zoom*d)/ddif, w/2.+(view[0]*pno[i+1]->qx(0)+view[1]*pno[i+1]->qx(1)-xmed)*(zoom*d)/ddif,  h/2.-(view[3]*pno[i+1]->qx(0)+view[4]*pno[i+1]->qx(1)-ymed)*(zoom*d)/ddif ); // draw line across the rectangle
            xm+=pno[i+1]->qx(0);
            ym+=pno[i+1]->qx(1);
        }
        xm/=nn;
        ym/=nn;
        dc.DrawLine( w/2.+(view[0]*pno[nn-1]->qx(0)+view[1]*pno[nn-1]->qx(1)-xmed)*(zoom*d)/ddif,  h/2.-(view[3]*pno[nn-1]->qx(0)+view[4]*pno[nn-1]->qx(1)-ymed)*(zoom*d)/ddif, w/2.+(view[0]*pno[0]->qx(0)+view[1]*pno[0]->qx(1)-xmed)*(zoom*d)/ddif,  h/2.-(view[3]*pno[0]->qx(0)+view[4]*pno[0]->qx(1)-ymed)*(zoom*d)/ddif ); // draw line across the rectangle
            dc.FloodFill(w/2.+(view[0]*xm+view[1]*ym-xmed)*(zoom*d)/ddif,
                         h/2.-(view[3]*xm+view[4]*ym-ymed)*(zoom*d)/ddif,
                         wxT("BLACK"),wxFLOOD_BORDER);
//                         tmpcolour->MakeGrey(r,g,b,this->ro,0,1.0-this->ro),wxFLOOD_SURFACE);
        break;
    }
}
void elemento::draw(wxDC& dc, double xmed, double ymed, int d, double ddif, double zoom, double* view, int e)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    int dim=qdim(), nn=qnno();
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    wxString E;
    E<<e;
    this->draw(dc,xmed,ymed,d,ddif,zoom,view);
    double xc=0.0;
    switch(dim)
    {
    case 1:
        for(int i=0;i<nn;i++)
            xc+=pno[i]->qx(0);
        xc/=nn;
        dc.DrawText( E,w/2.+(xc-xmed)*(zoom*d)/ddif, 0.5*(h) ); 
       break;
    case 2:
        double yc=0.0;
        for(int i=0;i<nn;i++)
        {
            xc+=pno[i]->qx(0);            
            yc+=pno[i]->qx(1);            
        }
        xc/=nn;yc/=nn;
            dc.DrawText( E,w/2.+(xc-xmed)*(zoom*d)/ddif,  h/2.-(yc-ymed)*(zoom*d)/ddif); // draw line across the rectangle
      break;
    }
}
void elemento::draw(wxDC& dc, double xmed, double ymed, int d, double ddif, double zoom, double* view, double e)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    int dim=qdim(), nn=qnno();
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    wxString E;
    E<<e;
    this->draw(dc,xmed,ymed,d,ddif,zoom,view);
    double xc=0.0;
    switch(dim)
    {
    case 1:
        for(int i=0;i<nn;i++)
            xc+=pno[i]->qx(0);
        xc/=nn;
        dc.DrawText( E,w/2.+(xc-xmed)*(zoom*d)/ddif, 0.5*(h) ); 
       break;
    case 2:
        double yc=0.0;
        for(int i=0;i<nn;i++)
        {
            xc+=pno[i]->qx(0);            
            yc+=pno[i]->qx(1);            
        }
        xc/=nn;yc/=nn;
            dc.DrawText( E,w/2.+(xc-xmed)*(zoom*d)/ddif,  h/2.-(yc-ymed)*(zoom*d)/ddif); // draw line across the rectangle
      break;
    }
}
