/***************************************************************************
 *   Copyright (C) 2005 by Fernando Cesar Meira Menandro                   *
 *   fcmm@npd.ufes.br                                                      *
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
#ifndef ELEMENTO3D_H
#define ELEMENTO3D_H

#include "elemento.h"

/**
@author Fernando Cesar Meira Menandro
*/
// Definicao da Classe elemento tridimensional

class elemento3D : public elemento
{
private:
    const static int dim = 3;  //Dimensao do problema
    const static int ipn = 3;  //Numero de incognitas por no
 //   const static int nno=3;  //Numero de nos
    const static int prp = 0;  //Numero de propriedades do elemento (area,espessura)
                             //Propriedade 0: espessura
 //  const static int ptg=1;  //Numero de Pontos de Gauss nas diferentes direcoes
    const static int nlb = 6;  //Numero de linhas da matriz B (componentes de deformacao)
public:
   elemento3D():elemento(){};
   ~elemento3D();
};
#endif
