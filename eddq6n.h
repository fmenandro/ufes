#ifndef EDDQ6N_H
#define EDDQ6N_H

#include "elementoddq.h"
class eddq6N :
    public elementoddq
{
private:
    const static int nno = 6;  //Numero de nos
    const static int ptg = 6;  //Numero de Pontos de Gauss
public:
    eddq6N();

    ~eddq6N();
    int qnno() { return(nno); };
    int qptg() { return(ptg); };
    int qptt() { return(ptg); };
};
#endif

