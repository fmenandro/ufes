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
#ifndef ISCAL1D_H
#define ISCAL1D_H

#include "elemento.h"

/**
@author Fernando Cesar Meira Menandro
*/
class iscal1d : public elemento
{
private:
   const static int dim=1;  //Dimensao do problema
   const static int ipn=1;  //Numero de incognitas por no
   const static int prp=1;  //Numero de propriedades do elemento (area,espessura)
                            //Propriedade 0: espessura
   const static int nlb=1;  //Numero de linhas da matriz B (componentes do fluxo)
protected:
public:
#ifdef ALEATORIO
   class aleatorio *N,*dn,*dN,detJ,*xg,*wg,peso,*m;
#else
   double *N,*dn,*dN,detJ,*xg,*wg,peso,*m;
#endif
    iscal1d(int,int);
    ~iscal1d();
   int qdim(){return(dim);};
   int qipn(){return(ipn);};
virtual int qnno()=0;
   int qprp(){return(prp);};
virtual int qptg()=0;
   int qnlb(){return(nlb);};
   double qvol(){return(peso*prop[0]);};
#ifdef ALEATORIO
  class aleatorio qm(int,int);
#else
  double qm(int,int);
#endif
   void monta_rigidez();
   void monta_b();
   void monta_c();
virtual void monta_n();
   void monta_massa();
friend ostream& operator<<(ostream&,iscal1d&);
};

#endif
