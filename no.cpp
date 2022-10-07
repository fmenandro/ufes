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
#include "no.h"

// Funcoes membro da Classe no

no::no()
{
};
no::no(int dim)
{
#ifdef ALEATORIO
   x=new aleatorio[dim];
#else
   x=new double[dim];
#endif
   for (int i=0;i<dim;i++)
      x[i]=0.0;
};

no::~no(){delete x;}

#ifdef ALEATORIO
aleatorio
#else
double
#endif
 no::qx(int i)
{
   if(i>=this->qdim()) return(0);//throw "Excedeu limite";
   return(x[i]);
}

ostream& operator<<(ostream& co,no& n)
{
   co<<"(";
   for (int i=0;i<n.qdim()-1;i++)
      co<<n.x[i]<<",";
   co<<n.x[n.qdim()-1]<<")";

   return co;
}

istream& operator>>(istream& ci, no& n)
{
   for (int i=0;i<n.qdim();i++)
   ci>>n.x[i];

   return ci;
}

wxTextOutputStream& operator<<(wxTextOutputStream& co,no& n)
{
   co<<"(";
   for (int i=0;i<n.qdim()-1;i++)
      co<<n.x[i]<<",";
   co<<n.x[n.qdim()-1]<<")";

   return co;
}

wxTextInputStream& operator>>(wxTextInputStream& ci, no& n)
{
   for (int i=0;i<n.qdim();i++)
   ci>>n.x[i];

   return ci;
}
void no::draw(wxDC& dc, double xmed, double xdif, double ymed, double ydif, double* view)
{
//    double view[3][2];
    wxCoord w,h;
    dc.GetSize(&w,&h);
    int dim=qdim();
    dc.SetPen( wxPen( wxColor(0,0,0), 1 ) ); // black line, 1 pixel thick
    int xis=5;
    switch(dim)
    {
    case 1:
         dc.DrawLine( w/2.+(qx(0)-xmed)*(0.9*w)/xdif-xis, 0.5*(h)-xis, w/2.+(qx(0)-xmed)*(0.9*w)/xdif+xis, 0.5*(h)+xis ); // draw line across the rectangle
         dc.DrawLine( w/2.+(qx(0)-xmed)*(0.9*w)/xdif-xis, 0.5*(h)+xis, w/2.+(qx(0)-xmed)*(0.9*w)/xdif+xis, 0.5*(h)-xis ); // draw line across the rectangle
       break;
    case 2:
        if(xdif/w>ydif/h)
        {
            dc.DrawLine( w/2.+(qx(0)-xmed)*(0.9*w)/xdif-xis,  h/2.-(qx(1)-ymed)*(0.9*w)/xdif-xis, w/2.+(qx(0)-xmed)*(0.9*w)/xdif+xis,  h/2.-(qx(1)-ymed)*(0.9*w)/xdif+xis ); // draw line across the rectangle
            dc.DrawLine( w/2.+(qx(0)-xmed)*(0.9*w)/xdif-xis,  h/2.-(qx(1)-ymed)*(0.9*w)/xdif+xis, w/2.+(qx(0)-xmed)*(0.9*w)/xdif-xis,  h/2.-(qx(1)-ymed)*(0.9*w)/xdif+xis ); // draw line across the rectangle
        }
        else
        {
            dc.DrawLine( w/2.+(qx(0)-xmed)*(0.9*h)/ydif-xis,  h/2.-(qx(1)-ymed)*(0.9*h)/ydif-xis, w/2.+(qx(0)-xmed)*(0.9*h)/ydif+xis,  h/2.-(qx(1)-ymed)*(0.9*h)/ydif+xis ); // draw line across the rectangle
            dc.DrawLine( w/2.+(qx(0)-xmed)*(0.9*h)/ydif-xis,  h/2.-(qx(1)-ymed)*(0.9*h)/ydif+xis, w/2.+(qx(0)-xmed)*(0.9*h)/ydif+xis,  h/2.-(qx(1)-ymed)*(0.9*h)/ydif-xis ); // draw line across the rectangle
        }
      break;
    }
}
void no::draw(wxDC& dc, double xmed, double xdif, double ymed, double ydif, double* view,int i)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    int dim=qdim();
    dc.SetPen( wxPen( wxColor(0,0,0), 1 ) ); // black line, 1 pixel thick
    int xis=5;
    wxString I;
    I<<i;
    this->draw(dc,xmed,xdif,ymed,ydif,view);
    switch(dim)
    {
    case 1:
         dc.DrawText( I,w/2.+(qx(0)-xmed)*(0.9*w)/xdif, 0.5*(h) ); // draw line across the rectangle
       break;
    case 2:
        if(xdif/w>ydif/h)
        {
            dc.DrawText( I,w/2.+(qx(0)-xmed)*(0.9*w)/xdif,  h/2.-(qx(1)-ymed)*(0.9*w)/xdif );
        }
        else
        {
            dc.DrawText( I,w/2.+(qx(0)-xmed)*(0.9*h)/ydif,  h/2.-(qx(1)-ymed)*(0.9*h)/ydif );
        }
      break;
    }
    /*switch(dim)
    {
    case 1:
         dc.DrawLine( w/2.+(qx(0)-xmed)*(0.9*w)/xdif-xis, 0.5*(h)-xis, w/2.+(qx(0)-xmed)*(0.9*w)/xdif+xis, 0.5*(h)+xis ); // draw line across the rectangle
         dc.DrawLine( w/2.+(qx(0)-xmed)*(0.9*w)/xdif-xis, 0.5*(h)+xis, w/2.+(qx(0)-xmed)*(0.9*w)/xdif+xis, 0.5*(h)-xis ); // draw line across the rectangle
         dc.DrawText( I,w/2.+(qx(0)-xmed)*(0.9*w)/xdif, 0.5*(h) ); // draw line across the rectangle
       break;
    case 2:
        if(xdif/w>ydif/h)
        {
            dc.DrawLine( w/2.+(qx(0)-xmed)*(0.9*w)/xdif-xis,  h/2.-(qx(1)-ymed)*(0.9*w)/xdif-xis, w/2.+(qx(0)-xmed)*(0.9*w)/xdif+xis,  h/2.-(qx(1)-ymed)*(0.9*w)/xdif+xis ); // draw line across the rectangle
            dc.DrawLine( w/2.+(qx(0)-xmed)*(0.9*w)/xdif-xis,  h/2.-(qx(1)-ymed)*(0.9*w)/xdif+xis, w/2.+(qx(0)-xmed)*(0.9*w)/xdif-xis,  h/2.-(qx(1)-ymed)*(0.9*w)/xdif+xis ); // draw line across the rectangle
        }
        else
        {
            dc.DrawLine( w/2.+(qx(0)-xmed)*(0.9*h)/ydif-xis,  h/2.-(qx(1)-ymed)*(0.9*h)/ydif-xis, w/2.+(qx(0)-xmed)*(0.9*h)/ydif+xis,  h/2.-(qx(1)-ymed)*(0.9*h)/ydif+xis ); // draw line across the rectangle
            dc.DrawLine( w/2.+(qx(0)-xmed)*(0.9*h)/ydif-xis,  h/2.-(qx(1)-ymed)*(0.9*h)/ydif+xis, w/2.+(qx(0)-xmed)*(0.9*h)/ydif+xis,  h/2.-(qx(1)-ymed)*(0.9*h)/ydif-xis ); // draw line across the rectangle
        }
      break;
    }*/
}
void no::draw(wxDC& dc, double xmed, double ymed, int d, double ddif, double zoom, double* view)
{
//    double view[3][2];
    wxCoord w,h;
    dc.GetSize(&w,&h);
    int dim=qdim();
    int x,y;
    dc.SetPen( wxPen( wxColor(0,0,0), 1 ) ); // black line, 1 pixel thick
    int xis=5;
    switch(dim)
    {
    case 1:
        x=w/2.+(view[0]*qx(0)-xmed)*zoom*d/ddif;
        y=h/2.-(view[3]*qx(0)-ymed)*zoom*d/ddif;
       break;
    case 2:
        x=w/2.+(view[0]*qx(0)+view[1]*qx(1)-xmed)*zoom*d/ddif;
        y=h/2.-(view[3]*qx(0)+view[4]*qx(1)-ymed)*zoom*d/ddif;
      break;
    }
    dc.DrawLine( x-xis,  y-xis, x+xis,  y+xis ); // draw line across the rectangle
    dc.DrawLine( x-xis,  y+xis, x+xis,  y-xis ); // draw line across the rectangle
}
void no::draw(wxDC& dc, double xmed, double ymed, int d, double ddif, double zoom, double* view,int i)
{
    wxCoord w,h;
    dc.GetSize(&w,&h);
    int dim=qdim();
    dc.SetPen( wxPen( wxColor(0,0,0), 1 ) ); // black line, 1 pixel thick
    int xis=5;
    int x,y;
    wxString I;
    I<<i;
    this->draw(dc,xmed,ymed,d,ddif,zoom,view);
    switch(dim)
    {
    case 1:
        x=w/2.+(view[0]*qx(0)-xmed)*zoom*d/ddif;
        y=h/2.-(view[3]*qx(0)-ymed)*zoom*d/ddif;
       break;
    case 2:
        x=w/2.+(view[0]*qx(0)+view[1]*qx(1)-xmed)*zoom*d/ddif;
        y=h/2.-(view[3]*qx(0)+view[4]*qx(1)-ymed)*zoom*d/ddif;
      break;
    }
    dc.DrawText( I,x,y );
}

