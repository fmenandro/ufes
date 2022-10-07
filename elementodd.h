#pragma once
#include "elemento.h"
#include "no2d.h"
class elementodd :
    public elemento
{
private:
    const static int dim = 2;  //Dimensao do problema
    const static int ipn = 2;  //Numero de incognitas por no
//    const static int nno = 3;  //Numero de nos
    const static int prp = 1;  //Numero de propriedades do elemento (area,espessura)
                             //Propriedade 0: espessura
//    const static int ptg = 1;  //Numero de Pontos de Gauss nas diferentes direcoes
    const static int nlb = 3;  //Numero de linhas da matriz B (componentes de deformacao)
public:
#ifdef ALEATORIO
    class aleatorio* N, * dN, peso;
#else
    double* N, * dN, peso;
#endif
//    int pg;
    elementodd(int, int);

    ~elementodd();

    int qdim() { return(dim); };
    int qipn() { return(ipn); };
//    int qnno() { return(nno); };
    int qprp() { return(prp); };
//    int qptg() { return(ptg); };
    int qnlb() { return(nlb); };
    void intersecta(class no*,class no*,class no*,class no*, double&, double&);
    void monta_rigidez();
    void monta_b();
    void monta_c();
    void monta_massa() {};
#ifdef ALEATORIO
    void p_processa(aleatorio*);
#else
    void p_processa(double*);
#endif
/*    friend ostream& operator<<(ostream&, elementodd&);
    friend wxTextOutputStream& operator<<(wxTextOutputStream&, elementodd&);*/
    void monta_n();
#ifdef ALEATORIO
    aleatorio
#else
    double
#endif
        nn(double x0, double y0, double x1, double y1, double x2, double y2) { return(x1 * y2 - x2 * y1 + (y1 - y2) * x0 + (x2 - x1) * y0); };
    double qvol() { return(peso * prop[0]); };
};

