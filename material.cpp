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
#include "material.h"


// Funcoes membro da Classe material
material::material(){};
material::material(int nprp)
{
#ifdef ALEATORIO
   prp=new class aleatorio[nprp] ;
#else
   prp=new double[nprp];
#endif
   prn=new string[nprp];
};
material::~material()
{
   delete prp;
   delete prn;
};
#ifdef ALEATORIO
class aleatorio
#else
double
#endif
material::qprp(int i)
{
   return(prp[i]);
};
string material::qprn(int i)
{
   return(prn[i]);
};
int material::qnprp(){return 0;};
string material::qtipo()
{
   return("Material");
};
/*
#ifdef ALEATORIO
class aleatorio
#else
double
#endif
material::qE()
{
   return(0.0);
};
#ifdef ALEATORIO
class aleatorio
#else
double
#endif
material::qni()
{
   return(0.0);
};
#ifdef ALEATORIO
class aleatorio
#else
double
#endif
material::qK()
{
   return(0.0);
};
#ifdef ALEATORIO
class aleatorio material::qK(class aleatorio T)
#else
double material::qK(double T)
#endif
{
   return(0.0);
};
*/
ostream& operator<<(ostream& co, material& m)
{
   co<<m.qtipo();
   for (int i=0;i<m.qnprp();i++)
      co<<"\n"<<m.qprn(i)<<" = "<<m.qprp(i);
   return co;
};
istream& operator>>(istream& ci, material& m)
{
   for (int i=0;i<m.qnprp();i++)
      ci>>m.prp[i];
   return ci;
};
wxTextOutputStream& operator<<(wxTextOutputStream& co, material& m)
{
   co<<m.qtipo();
   for (int i=0;i<m.qnprp();i++)
      co<<"\n"<<m.qprn(i)<<" = "<<m.qprp(i);
   return co;
};
wxTextInputStream& operator>>(wxTextInputStream& ci, material& m)
{
   for (int i=0;i<m.qnprp();i++)
      ci>>m.prp[i];
   return ci;
};


