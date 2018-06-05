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
#ifndef ELEMENTO2D8N_H
#define ELEMENTO2D8N_H

#include "isop2d.h"

/**
@author Fernando Cesar Meira Menandro
*/
class elemento2D8N : public isop2d
{
private:
   const static int nno=8;  //Numero de nos
   const static int ptg=3;  //Numero de Pontos de Gauss nas diferentes direcoes
public:
    elemento2D8N();

    ~elemento2D8N();
   int qnno(){return(nno);};
   int qptg(){return(ptg);};
   void monta_n();
};

#endif
