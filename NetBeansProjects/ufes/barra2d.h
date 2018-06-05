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
#ifndef STDBARRA2D_H
#define STDBARRA2D_H
#include "defaleat.h"

#include "elemento.h"

using namespace std;

/**
@author Fernando Cesar Meira Menandro
*/
class Barra2D : public elemento
{
private:
   const static int dim=2;  //Dimensao do problema
   const static int ipn=2;  //Numero de incognitas por no
   const static int nno=2;  //Numero de nos
   const static int prp=1;  //Numero de propriedades do elemento (area,espessura)
                            //Propriedade 0: Area da secao transversal
   const static int ptg=1;  //Numero de Pontos de Gauss nas diferentes direcoes
   const static int nlb=1;  //Numero de linhas da matriz B (componentes de deformacao)
public:
    Barra2D();

    ~Barra2D();
   int qdim(){return(dim);};
   int qipn(){return(ipn);};
   int qnno(){return(nno);};
   int qprp(){return(prp);};
   int qptg(){return(ptg);};
   int qnlb(){return(nlb);};
   double qvol(){return(prop[0]*sqrt((pno[0]->qx(0)-pno[1]->qx(0))
                                    *(pno[0]->qx(0)-pno[1]->qx(0))
                                    +(pno[0]->qx(1)-pno[1]->qx(1))
                                    *(pno[0]->qx(1)-pno[1]->qx(1))));};
   void monta_rigidez();
   void monta_b();
   void monta_c();

};


#endif
