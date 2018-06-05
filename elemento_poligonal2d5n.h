/***************************************************************************
*   Copyright (C) 2005 by Fernando C�sar Meira Menandro   *
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
#ifndef ELEMENTO_POLIGONAL2D5N_H
#define ELEMENTO_POLIGONAL2D5N_H

#include "isop2d.h"

/**
@author Fernando Cesar Meira Menandro
*/
class elpol2D5N : public isop2d
{
private:
	const static int nno = 5;  //Numero de nos
	const static int ptg = 1;  //Numero de Pontos de Gauss nas diferentes direcoes
public:
    #ifdef ALEATORIO
   class aleatorio *yg;
#else
   double *yg;
#endif
	elpol2D5N();

	~elpol2D5N();
	int qnno();
	int qptg();
        void pontos_de_gauss(int, int, double*, double*, double*);
	void monta_n();
   void monta_rigidez();
};

#endif
