#ifndef EDDQ10N_H
#define EDDQ10N_H
#include "elementoddq.h"
class eddq10N :
    public elementoddq
{
private:
    const static int nno = 10;  //Numero de nos
    const static int ptg = 10;  //Numero de Pontos de Gauss
public:
    eddq10N();

    ~eddq10N();
    int qnno() { return(nno); };
    int qptg() { return(ptg); };
    int qptt() { return(ptg); };
};

#endif
