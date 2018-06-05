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
#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "aleatorio.h"
#include <wx/txtstrm.h>

using namespace std;

/**
@author Fernando Cesar Meira Menandro
*/
// Definicao da Classe material

class material
{
protected:
   int nprn;
#ifdef ALEATORIO
   aleatorio
#else
   double
#endif
      *prp;
   string *prn;

public:
   material();
   material(int);
   ~material();
#ifdef ALEATORIO
   virtual class aleatorio qE(){};
   virtual class aleatorio qni(){};
   virtual class aleatorio qK(){};
   virtual class aleatorio qK(class aleatorio){};
   class aleatorio qprp(int);
#else
   virtual double qE(){return 0.0;};
   virtual double qni(){return 0.0;};
   virtual double qK(){return 0.0;};
   virtual double qK(double){return 0.0;};
   double qprp(int);
#endif
   string qprn(int);
   virtual int qnum()=0;
   virtual int qnprp();
   virtual string qtipo();
   friend ostream& operator<<(ostream&, material&);
   friend istream& operator>>(istream&, material&);
   friend wxTextOutputStream& operator<<(wxTextOutputStream&,material&);
   friend wxTextInputStream& operator>>(wxTextInputStream&, material&);
};

#endif
