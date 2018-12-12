﻿/***************************************************************************
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
#ifndef POLIGONAL2D7N_H
#define POLIGONAL2D7N_H

#include "poligonal2d.h"

/**
@author Fernando Cesar Meira Menandro
*/
class pol2D7N : public pol2d
{
private:
	const static int nno = 7;  //Numero de nos
	const static int ptg = 12;
	const static int ptg_tot = ptg;
public:
#ifdef ALEATORIO
	class aleatorio *yg;
#else
	double *yg;
#endif
	pol2D7N();
	~pol2D7N();
	
	int qptg();
	int qnno();
	int qptg_tot();
	void funcao_Forma(double, double, double*, double*);
	void pontos_de_gauss(int, double*, double*, double*);
};

#endif
