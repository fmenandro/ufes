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
#include "elcal2d4nnl.h"

elcal2d4nnl::elcal2d4nnl()
 : elcal2d4n()
{
}


elcal2d4nnl::~elcal2d4nnl()
{
}

void elcal2d4nnl::monta_c()
{
#ifdef ALEATORIO
   class aleatorio
#else
   double
#endif
      T=0.0;
   for (int i=0;i<qnlb()*qnlb();i++)
      c[i]=0.0;
   monta_n();
   for (int i=0;i<nno;i++)
      T+=x[i]*N[i];
   c[0]=pmaterial->qK(T);
   c[3]=pmaterial->qK(T);
};

