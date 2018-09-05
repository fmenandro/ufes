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
#ifndef ELEMENTO_H
#define ELEMENTO_H

/**
@author Fernando Cesar Meira Menandro
*/
#include <iostream>
#include "no.h"
#include "material.h"
#include "mat_termico.h"
#include "mat_linear_elastico.h"
#include "mat_termico_nao_linear.h"
#include <math.h>
#include <wx/txtstrm.h>
#include <wx/wx.h>


using namespace std;

// Definicao da Classe elemento

class elemento
{
protected:
   int *no,material,pg;
   class no **pno;
   class material *pmaterial;
#ifdef ALEATORIO
   class aleatorio *k,*prop,*b,*c,*x,*f,*ten,*def,ro;
#else
   double *k,*prop,*b,*c,*x,*f,*ten,*def,ro,rov,p,dc,dcn;
#endif
public:
   elemento();
   elemento(int,int,int,int,int,int);
   elemento(int, int, int, int, int, int, int); // Adicionado por Renan
   ~elemento();
   void aponta_no(int, class no*);
   void aponta_mat(class material*);
   virtual int qmat();
   virtual int qno(int);
   virtual int qdim()=0;
   virtual int qipn()=0;
   virtual int qnno()=0;
   virtual int qprp()=0;
   virtual int qptg()=0;
   virtual int qnlb()=0;
   virtual double qvol()=0;
#ifdef ALEATORIO
   class aleatorio qk(int,int);
#else
   double qk(int,int);
#endif
#ifdef ALEATORIO
   class aleatorio qrov();
   class aleatorio qro();
   class aleatorio qx(int);
   class aleatorio qdc();
   class aleatorio qdcn();
   void upro(class aleatorio);
   void updc(class aleatorio);
   void updcn(class aleatorio);
#else
   double qrov();
   double qro();
   double qx(int);
   double qdc();
   double qdcn();
   void upro(double);
   void uprov(double);
   void updc(double);
   void updcn(double);
#endif
   double qp();
#ifdef ALEATORIO
  virtual class aleatorio qm(int,int);
#else
  virtual double qm(int,int);
#endif
   int qpos(int, int);
   virtual void monta_rigidez();
   void pontos_de_gauss(int, double*, double*);
   void monta_n();
   virtual void monta_b();
   virtual void monta_c();
   virtual void monta_massa();
#ifdef ALEATORIO
   virtual void p_processa(aleatorio*);
#else
   virtual void p_processa(double*);
#endif
   friend ostream& operator<<(ostream&,elemento&);
   friend istream& operator>>(istream&,elemento&);
   friend wxTextOutputStream& operator<<(wxTextOutputStream&,elemento&);
   friend wxTextInputStream& operator>>(wxTextInputStream&,elemento&);
   void draw(wxDC&,double,double,double,double);
   void draw(wxDC&,double,double,double,double,int);
   void draw(wxDC&,double,double,double,double,double);
   void draw(wxDC&,double,double,int,double,double,double*);
   void draw(wxDC&,double,double,int,double,double,double*,int);
   void draw(wxDC&,double,double,int,double,double,double*,double);
};


#endif
