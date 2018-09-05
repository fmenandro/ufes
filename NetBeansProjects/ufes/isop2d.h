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
#ifndef ISOP2D_H
#define ISOP2D_H

#include "elemento.h"

/**
@author Fernando Cesar Meira Menandro
*/
class isop2d : public elemento
{
private:
   const static int dim=2;  //Dimensao do problema
   const static int ipn=2;  //Numero de incognitas por no
//   const static int nno=3;  //Numero de nos
   const static int prp=1;  //Numero de propriedades do elemento (area,espessura)
                            //Propriedade 0: espessura
//  const static int ptg=1;  //Numero de Pontos de Gauss nas diferentes direcoes
   const static int nlb=3;  //Numero de linhas da matriz B (componentes de deformacao)
protected:
public:
#ifdef ALEATORIO
   class aleatorio *N,*dn,*dN,detJ,*xg,*wg,peso;
#else
   double *N,*dn,*dN,detJ,*xg,*wg,peso;
#endif
    isop2d(int,int);
	isop2d(int, int, int);	// Adicionado por Renan, temporario
    ~isop2d();
   int qdim(){return(dim);};
   int qipn(){return(ipn);};
virtual int qnno()=0;
   int qprp(){return(prp);};
virtual int qptg()=0;
   int qnlb(){return(nlb);};
   double qvol(){return(peso*prop[0]);};
#ifdef ALEATORIO
  class aleatorio qm(int,int){};
#else
  double qm(int,int){return 0.0;};
#endif
   void monta_rigidez();
   void monta_b();
   void monta_c();
   void monta_massa(){};
virtual void monta_n();
};

#endif
