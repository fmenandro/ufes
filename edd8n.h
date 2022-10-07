#pragma once
#include "elementodd.h"
class edd8N :
    public elementodd
{
private:
    const static int nno = 8;  //Numero de nos
    const static int ptg = 8;  //Numero de Pontos de Gauss
public:
    edd8N();

    ~edd8N();
    int qnno() { return(nno); };
    int qptg() { return(ptg); };
    int qptt() { return(ptg); };
};

