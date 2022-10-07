#pragma once
#include "elementodd.h"
class edd6N :
    public elementodd
{
private:
    const static int nno = 6;  //Numero de nos
    const static int ptg = 6;  //Numero de Pontos de Gauss
public:
    edd6N();

    ~edd6N();
    int qnno() { return(nno); };
    int qptg() { return(ptg); };
    int qptt() { return(ptg); };
};

