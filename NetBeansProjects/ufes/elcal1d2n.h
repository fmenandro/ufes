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
#ifndef ELCAL1D2N_H
#define ELCAL1D2N_H

#include "iscal1d.h"

/**
@author Fernando Cesar Meira Menandro
*/
class elcal1d2n : public iscal1d
{
protected:
   const static int nno=2;  //Numero de nos
   const static int ptg=2;  //Numero de Pontos de Gauss nas diferentes direcoes
public:
    elcal1d2n();

    ~elcal1d2n();
   int qnno(){return(nno);};
   int qptg(){return(ptg);};
   void monta_n();
   void monta_c();
};

#endif
