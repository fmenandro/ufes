/***************************************************************************
 *   Copyright(C) 2005 by Leonardo Tutanko Souza Ferraz &                  *
 *   Fernando Cesar Meira Menandro                                        *
 *   menandro@localhost.localdomain                                        *
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
#ifndef VIGA3D_H
#define VIGA3D_H
#include "defaleat.h"
#include "elemento.h"

/**
@author Fernando Cesar Meira Menandro
*/
class Viga3D : public elemento
{
private:
   const static int dim=3;  //Dimensao do problema
   const static int ipn=6;  //Numero de incognitas por no
   const static int nno=2;  //Numero de nos
   const static int prp=7;  //Numero de propriedades do elemento (area,espessura)
                            //Propriedade 0: Area da secao transversal
                            //Propriedade 1: Momento de Inércia da seção transversal em relação a y
                            //Propriedade 2: Momento de Inércia da seção transversal em relação a z
                            //Propriedade 3: Momento polar de inércia
                            //Propriedade 4: Coordenada x do vetor perpendicular a largura
                            //Propriedade 5: Coordenada y do vetor perpendicular a largura
                            //Propriedade 6: Coordenada z do vetor perpendicular a largura
                            //Propriedade 7: Coordenada x do vetor aleatório
                            //Propriedade 8: Coordenada y do vetor aleatório
                            //Propriedade 9: Coordenada z do vetor aleatório
/*O Momento Iy e calculado em relacao a um eixo y na secao transversal na direcao da largura,
o momento Iz e calculado em relacao a um eixo perpendicular a este eixo y na direcao da largura e ao eixo x da peca.
O vetor de coordenadas estara preferencialmente na direcao deste eixo z, mas sera normalizado em relacao ao eixo x da peca*/
   const static int ptg=2;  //Numero de Pontos de Gauss nas diferentes direcoes
   const static int nlb=6; //Numero de linhas da matriz B (componentes de deformacao)
public:
   Viga3D();

   ~Viga3D();
   int qdim(){return(dim);};
   int qipn(){return(ipn);};
   int qnno(){return(nno);};
   int qprp(){return(prp);};
   int qptg(){return(ptg);};
   int qnlb(){return(nlb);};
   double qvol(){return(prop[0]*sqrt((pno[0]->qx(0)-pno[1]->qx(0))
                                    *(pno[0]->qx(0)-pno[1]->qx(0))
                                    +(pno[0]->qx(1)-pno[1]->qx(1))
                                    *(pno[0]->qx(1)-pno[1]->qx(1))
                                    +(pno[0]->qx(2)-pno[1]->qx(2))
                                    *(pno[0]->qx(2)-pno[1]->qx(2))));};
   void monta_rigidez();
   void monta_b();
   void monta_c();
//   friend aleatorio::aleatorio asqrt(aleatorio);
};

#endif
