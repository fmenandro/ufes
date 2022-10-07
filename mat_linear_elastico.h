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
#ifndef MAT_LINEAR_ELASTICO_H
#define MAT_LINEAR_ELASTICO_H

#include "material.h"

/**
@author Fernando Cesar Meira Menandro
*/
class mat_linear_elastico : public material
{
protected:
   const static int nprp=2;  //Numero de propriedades
public:
    mat_linear_elastico();

    ~mat_linear_elastico();
   int qnprp(){return(nprp);};
   string qtipo();
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
 qE();
#ifdef ALEATORIO
   aleatorio 
#else
   double
#endif
 qni();
 int qnum(){return(1);};};

#endif
