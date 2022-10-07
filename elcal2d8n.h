#ifndef ELCAL2D8N_H
#define ELCAL2D8N_H

#include "iscal2d.h"

/**
@author Fernando Cesar Meira Menandro
*/
class elcal2d8n : public iscal2d
{
protected:
   const static int nno=8;  //Numero de nos
   const static int ptg=3;  //Numero de Pontos de Gauss nas diferentes direcoes
public:
    elcal2d8n();

    ~elcal2d8n();
   int qnno(){return(nno);};
   int qptg(){return(ptg);};
   int qptt() { return(ptg * ptg); };
   void monta_n();
};

#endif


