#ifndef EDDQ8N_H
#define EDDQ8N_H

#include "elementoddq.h"
class eddq8N :
    public elementoddq 
{
private:
    const static int nno = 8;  //Numero de nos
    const static int ptg = 8;  //Numero de Pontos de Gauss
public:
    eddq8N();

    ~eddq8N();
    int qnno() { return(nno); };
    int qptg() { return(ptg); };
    int qptt() { return(ptg); };
};
#endif
