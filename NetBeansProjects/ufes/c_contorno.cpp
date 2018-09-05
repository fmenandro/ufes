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
#include <wx/dc.h>

#include "c_contorno.h"

c_contorno::c_contorno()
{
//   no=new int[nno];
//   gl=new int[ngl];
//   valor=new double[nvl];
}
c_contorno::c_contorno(int nno, int ngl, int nvl)
{
   no=new int[nno];
   pno=new class no*[nno];
   gl=new int[ngl];
#ifdef ALEATORIO
   valor=new class aleatorio[nvl];
#else
   valor=new double[nvl];
#endif
}

/*void c_contorno::draw(wxDC& dc, double xmed, double xdif, double ymed, double ydif)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
}*/

c_contorno::~c_contorno()
{
   delete no;delete gl;delete valor;delete pno;
}

int c_contorno::qno(int i)
{
   return(this->no[i]);
};

void c_contorno::aponta_no(int i,class no *gno)
{
      this->pno[i]=gno;
};
void c_contorno::draw(wxDC& dc, double xmed, double ymed, int d, double ddif, double zoom, double* view, int cc)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    int dim=pno[0]->qdim(), nn=qnno();
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    int x,y;
    wxString CC;
    CC<<cc;
    this->draw(dc,xmed,ymed,d,ddif,zoom,view);
    switch(dim)
    {
    case 1:
        x=w/2.+(view[0]*pno[0]->qx(0)-xmed)*zoom*d/ddif;
        y=h/2.-(view[3]*pno[0]->qx(0)-ymed)*zoom*d/ddif;
       break;
    case 2:
        x=w/2.+(view[0]*pno[0]->qx(0)+view[1]*pno[0]->qx(1)-xmed)*zoom*d/ddif;
        y=h/2.-(view[3]*pno[0]->qx(0)+view[4]*pno[0]->qx(1)-ymed)*zoom*d/ddif;
      break;
    }
    dc.DrawText( CC,x,y );
};
int apoio::nno=1;
int apoio::ngl=1;
int apoio::nvl=0;
apoio::apoio():c_contorno(nno,ngl,nvl){}
apoio::~apoio()
{
   this->c_contorno::~c_contorno();
}

#ifdef ALEATORIO
void apoio::impor(aleatorio *K, aleatorio *f, int ipn, int ndof)
#else
void apoio::impor(double *K, double *f, int ipn, int ndof)
#endif
{
   int i=no[0]*ipn+gl[0];
#ifdef ALEATORIO
   aleatorio
#else
   double
#endif
      KK,KJ;
   KK=K[qpos(i,i,ndof)];
   if (KK<tolerancia_contorno)
   {
      for (int j=0;j<ndof;j++)
      {
         KJ=K[qpos(j,j,ndof)];
         KK = ( KK < KJ )? KJ : KK;
      }
      K[qpos(i,i,ndof)]=KK;
   }
   for(int j=0;j<i;j++)
   {
      K[qpos(i,j,ndof)]=0.0;
   }
   f[i]=0.0;
   for(int j=i+1;j<ndof;j++)
   {
      K[qpos(i,j,ndof)]=0.0;
   }
}
#ifdef ALEATORIO
void apoio::impor(aleatorio *K, aleatorio *f, int ipn, int ndof, class aleatorio fc)
#else
void apoio::impor(double *K, double *f, int ipn, int ndof, double fc)
#endif
{
   int i=no[0]*ipn+gl[0];
#ifdef ALEATORIO
   aleatorio
#else
   double
#endif
      KK,KJ;
   KK=K[qpos(i,i,ndof)];
   if (KK<tolerancia_contorno)
   {
      for (int j=0;j<ndof;j++)
      {
         KJ=K[qpos(j,j,ndof)];
         KK = ( KK < KJ )? KJ : KK;
      }
      K[qpos(i,i,ndof)]=KK;
   }
   for(int j=0;j<i;j++)
   {
      K[qpos(i,j,ndof)]=0.0;
   }
   f[i]=0.0;
   for(int j=i+1;j<ndof;j++)
   {
      K[qpos(i,j,ndof)]=0.0;
   }
}

void apoio::draw(wxDC& dc, double xmed, double xdif, double ymed, double ydif)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    dc.SetPen( wxPen( wxColor(0,0,255), 1 ) ); // blue line, 1 pixel thick
    int tri=5;
    if(gl[0]==1)
    {
        if(xdif/w>ydif/h)
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*w)/xdif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)+tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)+2*tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*w)/xdif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)-tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)+2*tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)-tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)+2*tri, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)+tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)+2*tri ); // draw line across the rectangle
        }
        else
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*h)/ydif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)+tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)+2*tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*h)/ydif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)-tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)+2*tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)-tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)+2*tri, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)+tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)+2*tri ); // draw line across the rectangle
        }
    }
    else
    {
        if(xdif/w>ydif/h)
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*w)/xdif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)-2*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)+tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*w)/xdif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)-2*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)-tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)-2*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)+tri, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)-2*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)-tri ); // draw line across the rectangle
        }
        else
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*h)/ydif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)-2*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)+tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*h)/ydif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)-2*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)-tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)-2*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)+tri, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)-2*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)-tri ); // draw line across the rectangle
        }        
    }
}
void apoio::draw(wxDC& dc, double xmed, double ymed, int d, double ddif, double zoom, double* view)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    dc.SetPen( wxPen( wxColor(0,0,255), 1 ) ); // blue line, 1 pixel thick
    int tri=5;
    wxCoord wx[5], wy[5];
    wx[0]=w/2.+(view[0]*pno[0]->qx(0)
               +view[1]*pno[0]->qx(1)
               +view[2]*pno[0]->qx(2)-xmed)*(zoom*d)/ddif;
    wy[0]=h/2.-(view[3]*pno[0]->qx(0)
               +view[4]*pno[0]->qx(1)
               +view[5]*pno[0]->qx(2)-ymed)*(zoom*d)/ddif;
    switch(gl[0])
    {
        case 0:
            wx[1]=wx[0]-view[0]*2*tri-view[1]*tri;
            wy[1]=wy[0]+view[3]*2*tri+view[4]*tri;
            wx[2]=wx[0]-view[0]*2*tri+view[1]*tri;
            wy[2]=wy[0]+view[3]*2*tri-view[4]*tri;
            wx[3]=wx[0]-view[0]*2*tri-view[2]*tri;
            wy[3]=wy[0]+view[3]*2*tri-view[5]*tri;
            wx[4]=wx[0]-view[0]*2*tri+view[2]*tri;
            wy[4]=wy[0]+view[3]*2*tri+view[5]*tri;
            break;
        case 1:
            wx[1]=wx[0]-view[0]*tri-view[1]*2*tri;
            wy[1]=wy[0]+view[3]*tri+view[4]*2*tri;
            wx[2]=wx[0]+view[0]*tri-view[1]*2*tri;
            wy[2]=wy[0]-view[3]*tri+view[4]*2*tri;
            wx[3]=wx[0]-view[1]*2*tri+view[2]*tri;
            wy[3]=wy[0]+view[4]*2*tri-view[5]*tri;
            wx[4]=wx[0]-view[1]*2*tri-view[2]*tri;
            wy[4]=wy[0]+view[4]*2*tri+view[5]*tri;
            break;
        case 2:
            wx[1]=wx[0]-view[2]*2*tri+view[1]*tri;
            wy[1]=wy[0]+view[5]*2*tri-view[4]*tri;
            wx[2]=wx[0]-view[2]*2*tri-view[1]*tri;
            wy[2]=wy[0]+view[5]*2*tri+view[4]*tri;
            wx[3]=wx[0]-view[0]*tri-view[2]*2*tri;
            wy[3]=wy[0]+view[3]*tri+view[5]*2*tri;
            wx[4]=wx[0]+view[0]*tri-view[2]*2*tri;
            wy[4]=wy[0]-view[3]*tri+view[5]*2*tri;
            break;
    }
    dc.DrawLine(wx[0],wy[0],wx[1],wy[1]);  
    dc.DrawLine(wx[0],wy[0],wx[2],wy[2]);  
    dc.DrawLine(wx[1],wy[1],wx[2],wy[2]);  
    dc.DrawLine(wx[0],wy[0],wx[3],wy[3]);  
    dc.DrawLine(wx[0],wy[0],wx[4],wy[4]);  
    dc.DrawLine(wx[3],wy[3],wx[4],wy[4]);  
}

int deslocamento::nno=1;
int deslocamento::ngl=1;
int deslocamento::nvl=1;
deslocamento::deslocamento():c_contorno(nno,ngl,nvl){}

deslocamento::~deslocamento()
{
   this->c_contorno::~c_contorno();
}
#ifdef ALEATORIO
void deslocamento::impor(aleatorio *K, aleatorio *f, int ipn, int ndof)
#else
void deslocamento::impor(double *K, double *f, int ipn, int ndof)
#endif
{
   int i=no[0]*ipn+gl[0];
#ifdef ALEATORIO
   aleatorio
#else
   double
#endif
      KK,KJ;
   KK=K[qpos(i,i,ndof)];
   if (KK<tolerancia_contorno)
   {
      for (int j=0;j<ndof;j++)
      {
         KJ=K[qpos(j,j,ndof)];
         KK = ( KK < KJ )? KJ : KK;
      }
      K[qpos(i,i,ndof)]=KK;
   }
   for(int j=0;j<i;j++)
   {
      f[j]-=K[qpos(j,i,ndof)]*valor[0];
      K[qpos(i,j,ndof)]=K[qpos(j,i,ndof)]=0.0;
   }
   f[i]=KK*valor[0];
   for(int j=i+1;j<ndof;j++)
   {
      f[j]-=K[qpos(j,i,ndof)]*valor[0];
      K[qpos(i,j,ndof)]=K[qpos(j,i,ndof)]=0.0;
   }
}
#ifdef ALEATORIO
void deslocamento::impor(aleatorio *K, aleatorio *f, int ipn, int ndof, class aleatorio fc)
#else
void deslocamento::impor(double *K, double *f, int ipn, int ndof, double fc)
#endif
{
   int i=no[0]*ipn+gl[0];
#ifdef ALEATORIO
   aleatorio
#else
   double
#endif
      KK,KJ;
   KK=K[qpos(i,i,ndof)];
   if (KK<tolerancia_contorno)
   {
      for (int j=0;j<ndof;j++)
      {
         KJ=K[qpos(j,j,ndof)];
         KK = ( KK < KJ )? KJ : KK;
      }
      K[qpos(i,i,ndof)]=KK;
   }
   for(int j=0;j<i;j++)
   {
      f[j]-=K[qpos(j,i,ndof)]*valor[0]*fc;
      K[qpos(i,j,ndof)]=K[qpos(j,i,ndof)]=0.0;
   }
   f[i]=KK*valor[0]*fc;
   for(int j=i+1;j<ndof;j++)
   {
      f[j]-=K[qpos(j,i,ndof)]*valor[0];
      K[qpos(i,j,ndof)]=K[qpos(j,i,ndof)]=0.0;
   }
}
void deslocamento::draw(wxDC& dc, double xmed, double xdif, double ymed, double ydif)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    dc.SetPen( wxPen( wxColour(0,255,0), 1 ,wxPENSTYLE_SOLID) ); // green line, 1 pixel thick, solid
    int tri=5;
    if(gl[0]==1)
    {
        if(xdif/w>ydif/h)
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*w)/xdif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif),  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)-3*tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif-tri,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*w)/xdif-3*tri, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)+tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)-3*tri ); // draw line across the rectangle
        }
        else
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*h)/ydif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif),  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)-3*tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*h)/ydif-tri,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*h)/ydif-3*tri, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)+tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)-3*tri ); // draw line across the rectangle
       }
    }
    else
    {
        if(xdif/w>ydif/h)
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*w)/xdif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)+3*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif) ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif+3*tri,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*w)/xdif+tri, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)+3*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)-tri ); // draw line across the rectangle
        }
        else
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*h)/ydif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)+3*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif) ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*h)/ydif+3*tri,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*h)/ydif+tri, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)+3*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)-tri ); // draw line across the rectangle
        }        
    }
}
void deslocamento::draw(wxDC& dc, double xmed, double ymed, int d, double ddif, double zoom, double* view)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    dc.SetPen( wxPen( wxColour(0,255,0), 1 ,wxPENSTYLE_SOLID) ); // green line, 1 pixel thick, solid
    int tri=5;
    wxCoord wx[6], wy[6];
    wx[0]=w/2.+(view[0]*pno[0]->qx(0)
               +view[1]*pno[0]->qx(1)
               +view[2]*pno[0]->qx(2)-xmed)*(zoom*d)/ddif;
    wy[0]=h/2.-(view[3]*pno[0]->qx(0)
               +view[4]*pno[0]->qx(1)
               +view[5]*pno[0]->qx(2)-ymed)*(zoom*d)/ddif;
    switch(gl[0])
    {
        case 0:
            wx[1]=wx[0]+view[0]*3*tri;
            wy[1]=wy[0]-view[3]*3*tri;
            wx[2]=wx[0]+view[0]*3*tri-view[1]*tri;
            wy[2]=wy[0]-view[3]*3*tri+view[4]*tri;
            wx[3]=wx[0]+view[0]*3*tri+view[1]*tri;
            wy[3]=wy[0]-view[3]*3*tri-view[4]*tri;
            wx[4]=wx[0]+view[0]*3*tri+view[2]*tri;
            wy[4]=wy[0]-view[3]*3*tri-view[5]*tri;
            wx[5]=wx[0]+view[0]*3*tri-view[2]*tri;
            wy[5]=wy[0]-view[3]*3*tri+view[5]*tri;
            break;
        case 1:
            wx[1]=wx[0]+view[1]*3*tri;
            wy[1]=wy[0]-view[4]*3*tri;
            wx[2]=wx[0]+view[0]*tri+view[1]*3*tri;
            wy[2]=wy[0]-view[3]*tri-view[4]*3*tri;
            wx[3]=wx[0]-view[0]*tri+view[1]*3*tri;
            wy[3]=wy[0]+view[3]*tri-view[4]*3*tri;
            wx[4]=wx[0]+view[1]*3*tri+view[2]*tri;
            wy[4]=wy[0]-view[4]*3*tri-view[5]*tri;
            wx[5]=wx[0]+view[1]*3*tri-view[2]*tri;
            wy[5]=wy[0]-view[4]*3*tri+view[5]*tri;
            break;
        case 2:
            wx[1]=wx[0]+view[2]*3*tri+view[1]*tri;
            wy[1]=wy[0]-view[5]*3*tri-view[4]*tri;
            wx[2]=wx[0]+view[2]*3*tri-view[1]*tri;
            wy[2]=wy[0]-view[5]*3*tri+view[4]*tri;
            wx[3]=wx[0]+view[2]*3*tri+view[1]*tri;
            wy[3]=wy[0]-view[5]*3*tri-view[4]*tri;
            wx[4]=wx[0]-view[0]*tri+view[2]*3*tri;
            wy[4]=wy[0]+view[3]*tri-view[5]*3*tri;
            wx[5]=wx[0]+view[0]*tri+view[2]*3*tri;
            wy[5]=wy[0]-view[3]*tri-view[5]*3*tri;
            break;
    }
    dc.DrawLine(wx[0],wy[0],wx[1],wy[1]);  
    dc.DrawLine(wx[3],wy[3],wx[2],wy[2]);  
    dc.DrawLine(wx[4],wy[4],wx[5],wy[5]);  
}
int forca::nno=1;
int forca::ngl=1;
int forca::nvl=1;
forca::forca():c_contorno(nno,ngl,nvl){}
forca::~forca()
{
   this->c_contorno::~c_contorno();
}
#ifdef ALEATORIO
void forca::impor(aleatorio *K, aleatorio *f, int ipn, int ndof)
#else
void forca::impor(double *K, double *f, int ipn, int ndof)
#endif
{
   int i=no[0]*ipn+gl[0];
   f[i]+=valor[0];
}
#ifdef ALEATORIO
void forca::impor(aleatorio *K, aleatorio *f, int ipn, int ndof, class aleatorio fc)
#else
void forca::impor(double *K, double *f, int ipn, int ndof, double fc)
#endif
{
   int i=no[0]*ipn+gl[0];
   f[i]+=valor[0]*fc;
}
void forca::draw(wxDC& dc, double xmed, double xdif, double ymed, double ydif)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    dc.SetPen( wxPen( wxColour(255,0,0), 1 ,wxPENSTYLE_SOLID) ); // red line, 1 pixel thick, solid
    int tri=5;
    if(gl[0]==1)
    {
        if(xdif/w>ydif/h)
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*w)/xdif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif),  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)-3*tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*w)/xdif-3*tri, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)-tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)-2*tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif),  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)-3*tri, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)+tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)-2*tri ); // draw line across the rectangle
        }
        else
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*h)/ydif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif),  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)-3*tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*h)/ydif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*h)/ydif-3*tri, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)-tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)-2*tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif),  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)-3*tri, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)+tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)-2*tri ); // draw line across the rectangle
        }
    }
    else
    {
        if(xdif/w>ydif/h)
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*w)/xdif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)+3*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif) ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif+3*tri,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*w)/xdif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)+2*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)-tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)+3*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif), w/2.+((pno[0]->qx(0)-xmed)*(0.9*w)/xdif)+2*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*w)/xdif)+tri ); // draw line across the rectangle
        }
        else
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*h)/ydif,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)+3*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif) ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*h)/ydif+3*tri,  h/2.-(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)+2*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)-tri ); // draw line across the rectangle
            dc.DrawLine( w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)+3*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif), w/2.+((pno[0]->qx(0)-xmed)*(0.9*h)/ydif)+2*tri,  h/2.-((pno[0]->qx(1)-ymed)*(0.9*h)/ydif)+tri ); // draw line across the rectangle
        }        
    }
}
void forca::draw(wxDC& dc, double xmed, double ymed, int d, double ddif, double zoom, double* view)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    dc.SetPen( wxPen( wxColour(255,0,0), 1 ,wxPENSTYLE_SOLID) ); // red line, 1 pixel thick, solid
    int tri=5;
    wxCoord wx[6], wy[6];
    wx[0]=w/2.+(view[0]*pno[0]->qx(0)
               +view[1]*pno[0]->qx(1)
               +view[2]*pno[0]->qx(2)-xmed)*(zoom*d)/ddif;
    wy[0]=h/2.-(view[3]*pno[0]->qx(0)
               +view[4]*pno[0]->qx(1)
               +view[5]*pno[0]->qx(2)-ymed)*(zoom*d)/ddif;
    switch(gl[0])
    {
        case 0:
            wx[1]=wx[0]+view[0]*3*tri;
            wy[1]=wy[0]-view[3]*3*tri;
            wx[2]=wx[0]+view[0]*2*tri-view[1]*tri;
            wy[2]=wy[0]-view[3]*2*tri+view[4]*tri;
            wx[3]=wx[0]+view[0]*2*tri+view[1]*tri;
            wy[3]=wy[0]-view[3]*2*tri-view[4]*tri;
            wx[4]=wx[0]+view[0]*2*tri+view[2]*tri;
            wy[4]=wy[0]-view[3]*2*tri-view[5]*tri;
            wx[5]=wx[0]+view[0]*2*tri-view[2]*tri;
            wy[5]=wy[0]-view[3]*2*tri+view[5]*tri;
            break;
        case 1:
            wx[1]=wx[0]+view[1]*3*tri;
            wy[1]=wy[0]-view[4]*3*tri;
            wx[2]=wx[0]+view[0]*tri+view[1]*2*tri;
            wy[2]=wy[0]-view[3]*tri-view[4]*2*tri;
            wx[3]=wx[0]-view[0]*tri+view[1]*2*tri;
            wy[3]=wy[0]+view[3]*tri-view[4]*2*tri;
            wx[4]=wx[0]+view[1]*2*tri+view[2]*tri;
            wy[4]=wy[0]-view[4]*2*tri-view[5]*tri;
            wx[5]=wx[0]+view[1]*2*tri-view[2]*tri;
            wy[5]=wy[0]-view[4]*2*tri+view[5]*tri;
            break;
        case 2:
            wx[1]=wx[0]+view[2]*3*tri+view[1]*tri;
            wy[1]=wy[0]-view[5]*3*tri-view[4]*tri;
            wx[2]=wx[0]+view[2]*2*tri-view[1]*tri;
            wy[2]=wy[0]-view[5]*2*tri+view[4]*tri;
            wx[3]=wx[0]+view[2]*2*tri+view[1]*tri;
            wy[3]=wy[0]-view[5]*2*tri-view[4]*tri;
            wx[4]=wx[0]-view[0]*tri+view[2]*2*tri;
            wy[4]=wy[0]+view[3]*tri-view[5]*2*tri;
            wx[5]=wx[0]+view[0]*tri+view[2]*2*tri;
            wy[5]=wy[0]-view[3]*tri-view[5]*2*tri;
            break;
    }
    dc.DrawLine(wx[0],wy[0],wx[1],wy[1]);  
    dc.DrawLine(wx[1],wy[1],wx[2],wy[2]);  
    dc.DrawLine(wx[1],wy[1],wx[3],wy[3]);  
    dc.DrawLine(wx[1],wy[1],wx[4],wy[4]);  
    dc.DrawLine(wx[1],wy[1],wx[5],wy[5]);  
}

mista::mista():c_contorno(1,1,3){nno=ngl=1;nvl=3;}
mista::mista(int i):c_contorno(i,i,i){nno=ngl=nvl=i;}
mista::~mista()
{
   this->c_contorno::~c_contorno();
}
#ifdef ALEATORIO
void mista::impor(aleatorio *K, aleatorio *f, int ipn, int ndof)
#else
void mista::impor(double *K, double *f, int ipn, int ndof)
#endif
{
   int i;
      i=no[0]*ipn+gl[0];
   K[qpos(i,i,ndof)]-=valor[1]/valor[0];
   f[i]+=valor[2]/valor[0];
}
#ifdef ALEATORIO
void mista::impor(aleatorio *K, aleatorio *f, int ipn, int ndof, class aleatorio fc)
#else
void mista::impor(double *K, double *f, int ipn, int ndof, double fc)
#endif
{
   int* i;
   i=new int[nno];
   for (int j=0;j<nno;j++)
      i[j]=no[j]*ipn+gl[j];
#ifdef ALEATORIO
   aleatorio
#else
   double
#endif
      KK;
   KK=0.0;
   for (int j=0;j<nno;j++)
      KK+=valor[j]*K[qpos(i[0],i[j],ndof)];
   for(int j=0;j<ndof;j++)
   {
      for (int k=nno-1;k>=0;k--)
      {
         K[qpos(j,i[k],ndof)]-=K[qpos(j,i[0],ndof)]*valor[k]/valor[0];
         K[qpos(i[k],j,ndof)]=K[qpos(j,i[k],ndof)];
         f[i[k]]-=f[i[0]]*valor[k]/valor[0];
      }
   }
   for (int k=0;k<nno;k++)
   {
      K[qpos(i[k],i[0],ndof)]=K[qpos(i[0],i[k],ndof)]=KK*valor[k];
      f[i[0]]=0.0;
   }
}
void mista::draw(wxDC& dc, double xmed, double xdif, double ymed, double ydif)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    dc.SetPen( wxPen( wxColor(5,0,0), 3 ) ); // black line, 3 pixels thick
    if(gl[0]==0)
    {
        if(xdif/w<ydif/h)
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif, w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif+5,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif-10 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif, w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif-5,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif-10 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif-5,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif-10, w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif+5,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif-10 ); // draw line across the rectangle
        }
        else
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif+5,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*w)/ydif-10 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif-5,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*w)/ydif-10 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif-5,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*h)/ydif-10, w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif+5,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*w)/ydif-10 ); // draw line across the rectangle
        }
    }
    else
    {
        if(xdif/w<ydif/h)
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif, w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif-10,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif+5 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif, w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif-10,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif-5 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif-10,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif+5, w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif-10,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif-5 ); // draw line across the rectangle
        }
        else
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif-10,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*w)/ydif+5 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif-10,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*w)/ydif-5 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif-10,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*h)/ydif+5, w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif-10,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*w)/ydif-5 ); // draw line across the rectangle
        }        
    }
}
void mista::draw(wxDC& dc, double xmed, double ymed, int d, double ddif, double zoom, double* view)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    dc.SetPen( wxPen( wxColor(5,0,0), 3 ) ); // black line, 3 pixels thick
    wxCoord wx[6], wy[6];
    int tri=5;
    wx[0]=w/2.+(view[0]*pno[0]->qx(0)
               +view[1]*pno[0]->qx(1)
               +view[2]*pno[0]->qx(2)-xmed)*(zoom*d)/ddif;
    wy[0]=h/2.-(view[3]*pno[0]->qx(0)
               +view[4]*pno[0]->qx(1)
               +view[5]*pno[0]->qx(2)-ymed)*(zoom*d)/ddif;
    switch(gl[0])
    {
        case 0:
            wx[1]=wx[0]+view[0]*3*tri;
            wy[1]=wy[0]-view[3]*3*tri;
            wx[2]=wx[0]+view[0]*2*tri-view[1]*tri;
            wy[2]=wy[0]-view[3]*2*tri+view[4]*tri;
            wx[3]=wx[0]+view[0]*2*tri+view[1]*tri;
            wy[3]=wy[0]-view[3]*2*tri-view[4]*tri;
            wx[4]=wx[0]+view[0]*2*tri+view[2]*tri;
            wy[4]=wy[0]-view[3]*2*tri-view[5]*tri;
            wx[5]=wx[0]+view[0]*2*tri-view[2]*tri;
            wy[5]=wy[0]-view[3]*2*tri+view[5]*tri;
        case 1:
            wx[1]=wx[0]+view[1]*3*tri;
            wy[1]=wy[0]-view[4]*3*tri;
            wx[2]=wx[0]+view[0]*tri+view[1]*2*tri;
            wy[2]=wy[0]-view[3]*tri-view[4]*2*tri;
            wx[3]=wx[0]-view[0]*tri+view[1]*2*tri;
            wy[3]=wy[0]+view[3]*tri-view[4]*2*tri;
            wx[4]=wx[0]+view[1]*2*tri+view[2]*tri;
            wy[4]=wy[0]-view[4]*2*tri-view[5]*tri;
            wx[5]=wx[0]+view[1]*2*tri-view[2]*tri;
            wy[5]=wy[0]-view[4]*2*tri+view[5]*tri;
        case 2:
            wx[1]=wx[0]+view[2]*3*tri+view[1]*tri;
            wy[1]=wy[0]-view[5]*3*tri-view[4]*tri;
            wx[2]=wx[0]+view[2]*2*tri-view[1]*tri;
            wy[2]=wy[0]-view[5]*2*tri+view[4]*tri;
            wx[3]=wx[0]+view[2]*2*tri+view[1]*tri;
            wy[3]=wy[0]-view[5]*2*tri-view[4]*tri;
            wx[4]=wx[0]-view[0]*tri+view[2]*2*tri;
            wy[4]=wy[0]+view[3]*tri-view[5]*2*tri;
            wx[5]=wx[0]+view[0]*tri+view[2]*2*tri;
            wy[5]=wy[0]-view[3]*tri-view[5]*2*tri;
    }
    dc.DrawLine(wx[0],wy[0],wx[1],wy[1]);  
    dc.DrawLine(wx[1],wy[1],wx[2],wy[2]);  
    dc.DrawLine(wx[1],wy[1],wx[3],wy[3]);  
    dc.DrawLine(wx[1],wy[1],wx[4],wy[4]);  
    dc.DrawLine(wx[1],wy[1],wx[5],wy[5]);  
}
multipla::multipla():c_contorno(2,2,2){nno=ngl=nvl=2;}
multipla::multipla(int i):c_contorno(i,i,i){nno=ngl=nvl=i;}
multipla::~multipla()
{
   this->c_contorno::~c_contorno();
}
#ifdef ALEATORIO
void multipla::impor(aleatorio *K, aleatorio *f, int ipn, int ndof)
#else
void multipla::impor(double *K, double *f, int ipn, int ndof)
#endif
{
   int* i;
   i=new int[nno];
   for (int j=0;j<nno;j++)
      i[j]=no[j]*ipn+gl[j];
#ifdef ALEATORIO
   aleatorio
#else
   double
#endif
      KK;
   KK=0.0;
   for (int j=0;j<nno;j++)
      KK+=valor[j]*K[qpos(i[0],i[j],ndof)];
   for(int j=0;j<ndof;j++)
   {
      for (int k=nno-1;k>=0;k--)
      {
         K[qpos(j,i[k],ndof)]-=K[qpos(j,i[0],ndof)]*valor[k]/valor[0];
         K[qpos(i[k],j,ndof)]=K[qpos(j,i[k],ndof)];
         f[i[k]]-=f[i[0]]*valor[k]/valor[0];
      }
   }
   for (int k=0;k<nno;k++)
   {
      K[qpos(i[k],i[0],ndof)]=K[qpos(i[0],i[k],ndof)]=KK*valor[k];
      f[i[0]]=0.0;
   }
}
#ifdef ALEATORIO
void multipla::impor(aleatorio *K, aleatorio *f, int ipn, int ndof, class aleatorio fc)
#else
void multipla::impor(double *K, double *f, int ipn, int ndof, double fc)
#endif
{
   int* i;
   i=new int[nno];
   for (int j=0;j<nno;j++)
      i[j]=no[j]*ipn+gl[j];
#ifdef ALEATORIO
   aleatorio
#else
   double
#endif
      KK;
   KK=0.0;
   for (int j=0;j<nno;j++)
      KK+=valor[j]*K[qpos(i[0],i[j],ndof)];
   for(int j=0;j<ndof;j++)
   {
      for (int k=nno-1;k>=0;k--)
      {
         K[qpos(j,i[k],ndof)]-=K[qpos(j,i[0],ndof)]*valor[k]/valor[0];
         K[qpos(i[k],j,ndof)]=K[qpos(j,i[k],ndof)];
         f[i[k]]-=f[i[0]]*valor[k]/valor[0];
      }
   }
   for (int k=0;k<nno;k++)
   {
      K[qpos(i[k],i[0],ndof)]=K[qpos(i[0],i[k],ndof)]=KK*valor[k];
      f[i[0]]=0.0;
   }
}
void multipla::draw(wxDC& dc, double xmed, double xdif, double ymed, double ydif)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    dc.SetPen( wxPen( wxColor(5,0,0), 3 ) ); // black line, 3 pixels thick
    if(gl[0]==0)
    {
        if(xdif/w<ydif/h)
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif, w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif+5,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif-10 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif, w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif-5,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif-10 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif-5,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif-10, w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif+5,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif-10 ); // draw line across the rectangle
        }
        else
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif+5,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*w)/ydif-10 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif-5,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*w)/ydif-10 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif-5,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*h)/ydif-10, w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif+5,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*w)/ydif-10 ); // draw line across the rectangle
        }
    }
    else
    {
        if(xdif/w<ydif/h)
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif, w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif-10,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif+5 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif, w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif-10,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif-5 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif-10,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif+5, w/2.+(pno[0]->qx(0)-xmed)*(0.9*w)/xdif-10,  h/2.+(pno[0]->qx(1)-xmed)*(0.9*w)/xdif-5 ); // draw line across the rectangle
        }
        else
        {
            dc.DrawLine( w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif-10,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*w)/ydif+5 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*h)/ydif, w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif-10,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*w)/ydif-5 ); // draw line across the rectangle
            dc.DrawLine( w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif-10,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*h)/ydif+5, w/2.+(pno[0]->qx(0)-ymed)*(0.9*h)/ydif-10,  h/2.+(pno[0]->qx(1)-ymed)*(0.9*w)/ydif-5 ); // draw line across the rectangle
        }        
    }
}
void multipla::draw(wxDC& dc, double xmed, double ymed, int d, double ddif, double zoom, double* view)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    dc.SetPen( wxPen( wxColor(5,0,0), 3 ) ); // black line, 3 pixels thick
    wxCoord wx[6], wy[6];
    int tri=5;
    wx[0]=w/2.+(view[0]*pno[0]->qx(0)
               +view[1]*pno[0]->qx(1)
               +view[2]*pno[0]->qx(2)-xmed)*(zoom*d)/ddif;
    wy[0]=h/2.-(view[3]*pno[0]->qx(0)
               +view[4]*pno[0]->qx(1)
               +view[5]*pno[0]->qx(2)-ymed)*(zoom*d)/ddif;
    switch(gl[0])
    {
        case 0:
            wx[1]=wx[0]+view[0]*3*tri;
            wy[1]=wy[0]-view[3]*3*tri;
            wx[2]=wx[0]+view[0]*2*tri-view[1]*tri;
            wy[2]=wy[0]-view[3]*2*tri+view[4]*tri;
            wx[3]=wx[0]+view[0]*2*tri+view[1]*tri;
            wy[3]=wy[0]-view[3]*2*tri-view[4]*tri;
            wx[4]=wx[0]+view[0]*2*tri+view[2]*tri;
            wy[4]=wy[0]-view[3]*2*tri-view[5]*tri;
            wx[5]=wx[0]+view[0]*2*tri-view[2]*tri;
            wy[5]=wy[0]-view[3]*2*tri+view[5]*tri;
        case 1:
            wx[1]=wx[0]+view[1]*3*tri;
            wy[1]=wy[0]-view[4]*3*tri;
            wx[2]=wx[0]+view[0]*tri+view[1]*2*tri;
            wy[2]=wy[0]-view[3]*tri-view[4]*2*tri;
            wx[3]=wx[0]-view[0]*tri+view[1]*2*tri;
            wy[3]=wy[0]+view[3]*tri-view[4]*2*tri;
            wx[4]=wx[0]+view[1]*2*tri+view[2]*tri;
            wy[4]=wy[0]-view[4]*2*tri-view[5]*tri;
            wx[5]=wx[0]+view[1]*2*tri-view[2]*tri;
            wy[5]=wy[0]-view[4]*2*tri+view[5]*tri;
        case 2:
            wx[1]=wx[0]+view[2]*3*tri+view[1]*tri;
            wy[1]=wy[0]-view[5]*3*tri-view[4]*tri;
            wx[2]=wx[0]+view[2]*2*tri-view[1]*tri;
            wy[2]=wy[0]-view[5]*2*tri+view[4]*tri;
            wx[3]=wx[0]+view[2]*2*tri+view[1]*tri;
            wy[3]=wy[0]-view[5]*2*tri-view[4]*tri;
            wx[4]=wx[0]-view[0]*tri+view[2]*2*tri;
            wy[4]=wy[0]+view[3]*tri-view[5]*2*tri;
            wx[5]=wx[0]+view[0]*tri+view[2]*2*tri;
            wy[5]=wy[0]-view[3]*tri-view[5]*2*tri;
    }
    dc.DrawLine(wx[0],wy[0],wx[1],wy[1]);  
    dc.DrawLine(wx[1],wy[1],wx[2],wy[2]);  
    dc.DrawLine(wx[1],wy[1],wx[3],wy[3]);  
    dc.DrawLine(wx[1],wy[1],wx[4],wy[4]);  
    dc.DrawLine(wx[1],wy[1],wx[5],wy[5]);  
}

ostream& operator<<(ostream& co,c_contorno& a)
{
   for (int i=0;i<a.qnno();i++)
      co<<a.qtipo()<<":\nNo["<<i<<"] => "<<a.no[i];
   for (int i=0;i<a.qngl();i++)
      co<<"\nGrau de Liberdade["<<i<<"] => "<<a.gl[i];
   for (int i=0;i<a.qnvl();i++)
      co<<"\nValor["<<i<<"] => "<<a.valor[i];

   return co;
};

istream& operator>>(istream& ci, c_contorno& a)
{
   for (int i=0;i<a.qnno();i++)
      ci>>a.no[i];
   for (int i=0;i<a.qngl();i++)
      ci>>a.gl[i];
   for (int i=0;i<a.qnvl();i++)
      ci>>a.valor[i];
   return ci;
};

wxTextOutputStream& operator<<(wxTextOutputStream& co,c_contorno& a)
{
   for (int i=0;i<a.qnno();i++)
      co<<a.qtipo()<<":\nNo["<<i<<"] => "<<a.no[i];
   for (int i=0;i<a.qngl();i++)
      co<<"\nGrau de Liberdade["<<i<<"] => "<<a.gl[i];
   for (int i=0;i<a.qnvl();i++)
      co<<"\nValor["<<i<<"] => "<<a.valor[i];

   return co;
};

wxTextInputStream& operator>>(wxTextInputStream& ci, c_contorno& a)
{
   for (int i=0;i<a.qnno();i++)
      ci>>a.no[i];
   for (int i=0;i<a.qngl();i++)
      ci>>a.gl[i];
   for (int i=0;i<a.qnvl();i++)
      ci>>a.valor[i];
   return ci;
};

