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
#ifndef MAT_TERMICO_H
#define MAT_TERMICO_H

#include "material.h"

/**
@author Fernando Cesar Meira Menandro
*/
class mat_termico : public material
{
protected:
   const static int nprp=1;  //Numero de propriedades
public:
   mat_termico();

   ~mat_termico();
   int qnprp(){return(nprp);};
   string qtipo();
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
 qK();
#ifdef ALEATORIO
  virtual aleatorio qK(aleatorio); 
#else
  virtual double qK(double);
#endif
 int qnum(){return(0);};
};

#endif
