#pragma once
#include "elementodd.h"
class edd5N :
    public elementodd
{
private:
    const static int nno = 5;  //Numero de nos
    const static int ptg = 5;  //Numero de Pontos de Gauss
public:
    edd5N();

    ~edd5N();
    int qnno() { return(nno); };
    int qptg() { return(ptg); };
    int qptt() { return(ptg); };
//    void monta_n();
};

