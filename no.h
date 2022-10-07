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
#ifndef NO_H
#define NO_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "aleatorio.h"
#include <wx/txtstrm.h>
#include <wx/wx.h>


using namespace std;

/**
@author Fernando Cesar Meira Menandro
*/
// Definicao da Classe no

class no
{
protected:
#ifdef ALEATORIO
   class aleatorio *x;
#else
   double *x;
#endif
public:
   no();
   no(int);
   ~no();

   virtual int qdim()=0;
#ifdef ALEATORIO
   aleatorio qx(int);
#else
   double qx(int);
#endif
   friend ostream& operator<<(ostream&,no&);
   friend istream& operator>>(istream&,no&);
   friend wxTextOutputStream& operator<<(wxTextOutputStream&,no&);
   friend wxTextInputStream& operator>>(wxTextInputStream&,no&);
   void draw(wxDC&,double,double,double,double,double*);
   void draw(wxDC&,double,double,double,double,double*,int);
   void draw(wxDC&,double,double,int,double,double,double*);
   void draw(wxDC&,double,double,int,double,double,double*,int);
};

#endif
