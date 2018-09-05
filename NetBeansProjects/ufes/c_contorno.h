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
#include "defaleat.h"
#ifndef C_CONTORNO_H
#define C_CONTORNO_H
#include <iostream>
#ifdef ALEATORIO
#include <aleatorio.h>
#endif
#include <wx/txtstrm.h>
#include <wx/wx.h>
#include "no.h"
#define tolerancia_contorno 1e-05
using namespace std;

/**
Classe Base para Condiçoes de Contorno

@author Fernando Cesar Meira Menandro
*/
class c_contorno
{
public:
   int *no,*gl;
   class no **pno;
#ifdef ALEATORIO
   class aleatorio *valor;
#else
   double *valor;
#endif

    c_contorno();
    c_contorno(int,int,int);
    ~c_contorno();
    void aponta_no(int, class no*);
    int qno(int);
    virtual int qnno()=0;
    virtual int qngl()=0;
    virtual int qnvl()=0;
    virtual char* qtipo()=0;
#ifdef ALEATORIO
    virtual void impor(class aleatorio *, class aleatorio *, int, int)=0;
    virtual void impor(class aleatorio *, class aleatorio *, int, int, aleatorio)=0;
#else
    virtual void impor(double*, double*, int, int)=0;
    virtual void impor(double*, double*, int, int, double)=0;
#endif
    int qpos(int i, int j, int ndof){return(i*ndof+j);};
    friend ostream& operator<<(ostream&,c_contorno&);
    friend istream& operator>>(istream&,c_contorno&);
    friend wxTextOutputStream& operator<<(wxTextOutputStream&,c_contorno&);
    friend wxTextInputStream& operator>>(wxTextInputStream&,c_contorno&);
    virtual void draw(wxDC&,double,double,double,double)=0;
    virtual void draw(wxDC&,double,double,int,double,double,double*)=0;
    void draw(wxDC&,double,double,int,double,double,double*,int);
};
class apoio : public c_contorno
{
   static int nno,ngl,nvl;
public:
    apoio();
    ~apoio();
    int qnno(){return(nno);}
    int qngl(){return(ngl);}
    int qnvl(){return(nvl);}
    char* qtipo(){return("Apoio");};
#ifdef ALEATORIO
    virtual void impor(class aleatorio *, class aleatorio *, int, int);
    virtual void impor(class aleatorio *, class aleatorio *, int, int, class aleatorio);
#else
    virtual void impor(double*, double*, int, int);
    virtual void impor(double*, double*, int, int, double);
#endif
    virtual void draw(wxDC&,double,double,double,double);
    virtual void draw(wxDC&,double,double,int,double,double,double*);
};
class deslocamento : public c_contorno
{
   static int nno,ngl,nvl;
public:
    deslocamento();
    ~deslocamento();
    int qnno(){return(nno);};
    int qngl(){return(ngl);};
    int qnvl(){return(nvl);};
    char* qtipo(){return("Deslocamento");};
#ifdef ALEATORIO
    virtual void impor(class aleatorio *, class aleatorio *, int, int);
    virtual void impor(class aleatorio *, class aleatorio *, int, int, class aleatorio);
#else
    virtual void impor(double*, double*, int, int);
    virtual void impor(double*, double*, int, int, double);
#endif
    virtual void draw(wxDC&,double,double,double,double);
    virtual void draw(wxDC&,double,double,int,double,double,double*);
};
class forca : public c_contorno
{
   static int nno,ngl,nvl;
public:
    forca();
    ~forca();
    int qnno(){return(nno);};
    int qngl(){return(ngl);};
    int qnvl(){return(nvl);};
    char* qtipo(){return("Forca");};
#ifdef ALEATORIO
    virtual void impor(class aleatorio *, class aleatorio *, int, int);
    virtual void impor(class aleatorio *, class aleatorio *, int, int, class aleatorio);
#else
    virtual void impor(double*, double*, int, int);
    virtual void impor(double*, double*, int, int, double);
#endif
    virtual void draw(wxDC&,double,double,double,double);
    virtual void draw(wxDC&,double,double,int,double,double,double*);
};
class mista : public c_contorno
{
   int nno,ngl,nvl;
public:
    mista();
    mista(int);
    ~mista();
    int qnno(){return(nno);};
    int qngl(){return(ngl);};
    int qnvl(){return(nvl);};
    char* qtipo(){return("Mista");};
#ifdef ALEATORIO
    virtual void impor(class aleatorio *, class aleatorio *, int, int);
    virtual void impor(class aleatorio *, class aleatorio *, int, int, class aleatorio);
#else
    virtual void impor(double*, double*, int, int);
    virtual void impor(double*, double*, int, int, double);
#endif
    virtual void draw(wxDC&,double,double,double,double);
    virtual void draw(wxDC&,double,double,int,double,double,double*);
};
class multipla : public c_contorno
{
   int nno,ngl,nvl;
public:
    multipla();
    multipla(int);
    ~multipla();
    int qnno(){return(nno);};
    int qngl(){return(ngl);};
    int qnvl(){return(nvl);};
    char* qtipo(){return("Multipla");};
#ifdef ALEATORIO
    virtual void impor(class aleatorio *, class aleatorio *, int, int);
    virtual void impor(class aleatorio *, class aleatorio *, int, int, class aleatorio);
#else
    virtual void impor(double*, double*, int, int);
    virtual void impor(double*, double*, int, int, double);
#endif
    virtual void draw(wxDC&,double,double,double,double);
    virtual void draw(wxDC&,double,double,int,double,double,double*);
};

#endif
