/***************************************************************************
 *   Copyright (C) 2005 by Fernando César Meira Menandro   *
 *   menandro@localhost.localdomain   *
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
#include "mat_termico_nao_linear.h"

mat_termico_nao_linear::mat_termico_nao_linear()
 : material(nprp)
{
   prn[0]="Condutividade Termica Inicial";
   prn[1]="Condutividade Termica Residual";
}


mat_termico_nao_linear::~mat_termico_nao_linear()
{
}

string mat_termico_nao_linear::qtipo()
{
   return("Termico Nao Linear");
}
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
 mat_termico_nao_linear::qK()
{
   return prp[0];
}
#ifdef ALEATORIO
   aleatorio mat_termico_nao_linear::qK(class aleatorio T)
#else
   double mat_termico_nao_linear::qK(double T)
#endif
{
   return prp[0]+T*prp[1];
}


