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
#include "mat_linear_elastico.h"

mat_linear_elastico::mat_linear_elastico()
 : material(nprp)
{
   prn[0]="Modulo de Elasticidade";
   prn[1]="Coeficiente de Poisson";
}


mat_linear_elastico::~mat_linear_elastico()
{
}
string mat_linear_elastico::qtipo()
{
   return("Linear Elastico");
}
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
 mat_linear_elastico::qE()
{
   return prp[0];
}
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
 mat_linear_elastico::qni()
{
   return prp[1];
}


