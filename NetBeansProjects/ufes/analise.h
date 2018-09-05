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
#ifndef ANALISE_H
#define ANALISE_H

#define tolerancia 1e-40
//#include "elemento.h"
#include "no1d.h"
#include "no2d.h"
#include "no3d.h"
#include "mat_termico.h"
#include "mat_linear_elastico.h"
#include "mat_termico_nao_linear.h"
#include "barra1d.h"
#include "barra2d.h"
#include "viga2d.h"
#include "viga3d.h"
#include "barra3d.h"
#include "elemento2d3n.h"
#include "elemento2d4n.h"
#include "elemento2d8n.h"
#include "elemento2d9n.h"
#include "tubo.h"
#include "elcal2d4n.h"
#include "elcal2d8n.h"
#include "nlcal2d4n.h"
#include "elcal1d2n.h"
#include "elemento_poligonal2d5n.h"
#include "elemento_poligonal2d6n.h"
#include "elemento_poligonal2d7n.h"
#include "elemento_poligonal2d8n.h"
#include "c_contorno.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#ifdef ALEATORIO
#include <aleatorio.h>
#else
#include <math.h>
#endif
#include <wx/textfile.h>
#include <wx/txtstrm.h>
#include <wx/wx.h>

#include <wx/wfstream.h>
using namespace std;

/**
@author Fernando Cesar Meira Menandro
*/
// Definicao da Classe analise

class analise
{
public:
   int nn,ne,nm,nc,ndof,nccc;
   int fn,fe,fcc,fnn,fne,fnc,fnm,fro;
   class no **nos;
   class elemento **elementos;
   class c_contorno **cc;
   class material **materiais;
   int *ccc;
   double view[6];
   double ro,rm,ch_lim;
#ifdef ALEATORIO
   class aleatorio *K,*x,*f;
#else
   double *K,*x,*f;
#endif
//public:
   analise();
   analise(istream&);
   analise(ifstream&);
   analise(wxTextInputStream&);

   ~analise();

   friend ostream& operator<<(ostream&, analise&);
   friend istream& operator>>(istream&, analise&);
   friend ifstream& operator>>(ifstream&, analise&);
   friend wxTextOutputStream& operator<<(wxTextOutputStream&, analise&);
   friend wxTextInputStream& operator>>(wxTextInputStream&, analise&);

   void montaK();
   void zerar();
   void montaroK();
   double ofsa();
   void fs(double);
   double oc();
   void impoeCC();
   void resolve();
   void posprocessa();
   int qpos(int, int);
   void visao(class wxString);
#ifdef ALEATORIO
   friend bool operator>(aleatorio&, aleatorio&);
   friend bool operator<(aleatorio&, aleatorio&);
   friend bool operator>(aleatorio&, double);
   friend bool operator<(aleatorio&, double);
#endif
   void draw(wxDC&);
   int qndof();
   void upK(int,double);
   void upx(int,double);
   void upf(int,double);
};

#endif
