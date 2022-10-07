#pragma once
#include "elementodd.h"
class edd7N :
    public elementodd
{
private:
    const static int nno = 7;  //Numero de nos
    const static int ptg = 7;  //Numero de Pontos de Gauss
public:
    edd7N();

    ~edd7N();
    int qnno() { return(nno); };
    int qptg() { return(ptg); };
    int qptt() { return(ptg); };
};

