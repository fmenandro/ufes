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
#ifndef ELEMENTO_POLIGONAL2D6N_NC_H
#define ELEMENTO_POLIGONAL2D6N_NC_H

#include "elemento_poligonal2d_NC.h"

/**
@author Fernando Cesar Meira Menandro
*/
class elpol2D6N_NC : public elpol2d_NC
{
private:
	const static int nno = 6;  //Numero de nos
public:
#ifdef ALEATORIO
	class aleatorio *yg;
#else
	double *yg;
#endif
	elpol2D6N_NC();
	~elpol2D6N_NC();

	int qnno();
	void funcao_Forma(double, double, double*, double*);
};

#endif
