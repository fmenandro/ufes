/***************************************************************************
 *   Copyright (C) 2005 by Fernando César Meira Menandro   *
 *   fernando.menandro@ufes.br   *
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
#include "elementodd.h"

 /* O elemento com derivada descontínua bidimensional é uma classe base para
 criação de outros elementos de duas dimensões. As variáveis estáticas
    const static int dim=2;  //Dimensao do problema
    const static int ipn=2;  //Numero de incognitas por no
    const static int prp=1;  //Numero de propriedades do elemento (area,espessura)
                             //Propriedade 0: espessura
    const static int nlb=3;  //Numero de linhas da matriz B (componentes de deformacao)
 já ficam definidas, restando a definição do número de nós (nno) e do número de pontos
 de Gauss por direção (ptg). */
elementodd::elementodd(int nno, int ptg)
    : elemento(dim, ipn, nno, prp, ptg, nlb)
{
    /* Alocação de memória
    N - função de interpolação de deslocamento (função de forma para elemento isoparamétrico)
    dN- derivadas das funções N nas coordenadas x e y.
    */
#ifdef ALEATORIO
    N = new class aleatorio[nno];
    dN = new class aleatorio[nno * 2];
#else
    N = new double[nno];
    dN = new double[nno * 2];
#endif
    // Inicialização da variável DetJ (Determinante da matriz Jacobiano)
};


elementodd::~elementodd()
{
};

void elementodd::intersecta(class no *pn0, class no *pn1, class no *pn2, class no *pn3, double &xp, double &yp)
{
    double csi1, eta1, csi2, eta2, csi3, eta3, r1, s1, r3, s3, teta,s,c,sp,cp,ep;
    csi1 = pn1->qx(0) - pn0->qx(0);
    eta1 = pn1->qx(1) - pn0->qx(1);
    csi2 = pn2->qx(0) - pn0->qx(0);
    eta2 = pn2->qx(1) - pn0->qx(1);
    csi3 = pn3->qx(0) - pn0->qx(0);
    eta3 = pn3->qx(1) - pn0->qx(1);
    teta = atan2(csi2, eta2);
    s = sin(teta);
    c = cos(teta);
    r1 = csi1 * c - eta1 * s;
    s1 = csi1 * s + eta1 * c;
    r3 = csi3 * c - eta3 * s;
    s3 = csi3 * s + eta3 * c;
    sp = (r1 * s3 - r3 * s1) / (r1 - r3);
    cp = sp * s;
    ep = sp * c;
    xp = cp + pn0->qx(0); 
    yp = ep + pn0->qx(1);
    return;
};
void elementodd::monta_b()
{
    monta_n();
/*    for (int i = 0; i < qnno(); i++)
    {
        b[(2 * i)] = b[4 * qnno() + 2 * i + 1] = dN[i * 2];
        b[2 * (qnno() + i) + 1] = b[4 * qnno() + 2 * i] = dN[i * 2 + 1];
        b[(2 * i) + 1] = b[2 * (qnno() + i)] = 0.0;
    }*/
};
void elementodd::monta_c()
{
#ifdef ALEATORIO
    aleatorio
#else
    double
#endif
        um = 1.0;
    for (int i = 0; i < qnlb() * qnlb(); i++)
        c[i] = 0.0;
        c[0] = pmaterial->qE() / (um - pmaterial->qni() * pmaterial->qni());
        c[1] = pmaterial->qni() * c[0];
        c[3] = c[1];
        c[4] = c[0];
        c[8] = pmaterial->qE() / ((um + pmaterial->qni()) * 2.0);
/*        if (qprp())
        {
            c[0] /= prop[0];
            c[1] /= prop[0];
            c[3] /= prop[0];
            c[4] /= prop[0];
            c[8] /= prop[0];
        }*/
};
/* Para elementos isoparamétricos apenas montamos as matrizes deslocamento-deformação
e de propriedades dos materiais, para em seguida realizar o produto
   T
 [B] [C] [B].
*/
void elementodd::monta_rigidez()
{
/*#ifdef ALEATORIO
    aleatorio* xx, * yy;
    xx = new aleatorio[qnno()];
    yy = new aleatorio[qnno()];
#else
    double* xx, * yy;
    xx = new double[qnno()];
    yy = new double[qnno()];
#endif*/
    for (int i = 0; i < qnno() * qipn(); i++)
        for (int j = 0; j < qnno() * qipn(); j++)
            this->k[qnno() * qipn() * i + j] = 0.0;
    for (pg = 0; pg < qptg(); pg++)
    {
        peso = 1.0;
        monta_n();
        monta_c();
        if (qprp())peso *= prop[0];
        for (int i = 0; i < qnno() * qipn(); i++)
            for (int j = 0; j < qnlb(); j++)
                for (int l = 0; l < qnlb(); l++)
                    for (int m = 0; m < qnno() * qipn(); m++)
                        k[qnno() * qipn() * i + m] +=
                        b[qnno() * qipn() * j + i] * c[qnlb() * j + l] * b[qnno() * qipn() * l + m] * peso;

    }
};
#ifdef ALEATORIO
void elementodd::p_processa(aleatorio* xx)
{
#else    
void elementodd::p_processa(double* xx)
    {
#endif
        //        double* xpg, * wpg;
        //        xpg = new double[qptg()];
        //        wpg = new double[qptg()];
//        int pg = qptg();
        for (int i = 0; i < qnno() * qipn(); i++)
        {
            f[i] = 0.0;
            for (int n = 0; n < qnno(); n++)
                for (int j = 0; j < qipn(); j++)
                    f[i] += qk(i, n * qipn() + j) * xx[qno(n) * qipn() + j];
        }
        for (int n = 0; n < qnno(); n++)
            for (int i = 0; i < qipn(); i++)
                x[n * qipn() + i] = xx[qno(n) * qipn() + i];
        int lpg = qptt();
        for (int pg = 0; pg < lpg; pg++)
        {
            monta_n();
            for (int i = 0; i < qnlb(); i++)
            {
                def[pg * qnlb() + i] = ten[pg * qnlb() + i] = 0;
                for (int j = 0; j < qnno() * qipn(); j++)
                    def[pg * qnlb() + i] += b[i * qnno() * qipn() + j] * x[j];
            }
            monta_c();
            for (int i = 0; i < qnlb(); i++)
            {
                for (int j = 0; j < qnlb(); j++)
                    ten[pg * qnlb() + i] += c[i * qnlb() + j] * def[j];
            }
        }
    };

/* Em diferentes */
//void elementodd::monta_n() {};
void elementodd::monta_n()
{
    int num = qnno();
#ifdef ALEATORIO
    aleatorio
#else
    double
#endif
        r, s, *xx, *yy, xxc = 0, yyc = 0, A, Bx, By, um = 1.0, quatro = 4.0, tres = 3.0;
    int ncb = num * qipn();
#ifdef ALEATORIO
    xx = new aleatorio[num + 1];
    yy = new aleatorio[num + 1];
#else
    xx = new double[num + 1];
    yy = new double[num + 1];
#endif
    for (int i = 0; i < qnlb(); i++)
        for (int j = 0; j < ncb; j++)
            b[i * ncb + j] = 0.0;
    for (int i = 0; i < num; i++)
    {
        xx[i] = this->pno[i]->qx(0);
        yy[i] = this->pno[i]->qx(1);
        xxc += xx[i];
        yyc += yy[i];
    }
    xxc /= num;
    yyc /= num;
    xx[num] = xx[0];
    yy[num] = yy[0];
    //    intersecta(this->pno[0], this->pno[1], this->pno[2], this->pno[3], xxc, yyc);
    A = nn(xx[pg], yy[pg], xx[pg+1], yy[pg+1], xxc, yyc);
    r = (xx[pg] + xx[pg+1] + xxc) / tres;
    s = (yy[pg] + yy[pg+1] + yyc) / tres;
    Bx = (xx[pg + 1] - xx[pg]) / (A * num);
    By = (yy[pg] - yy[pg + 1]) / (A * num);
    for (int i = 0; i < num; i++)
    {
        N[i] = um / (tres * num);
        b[2 * i] = b[2 * (ncb + i) + 1] = By;
        b[2 * (num + i) + 1] = b[2 * (ncb + i)] = Bx;
    }
//    int pgm1 = (pg == num-1) ? 0 : pg + 1;
//    N[pg] = N[pgm1] = (num + um) / (tres * num);
//    b[2 * (ncb + pg) + 1] = b[2 * pg] += (yy[pg + 1] - yyc) / A;
//    b[2 * (ncb + pgm1) + 1] = b[2 * pgm1] += (yyc - yy[pg]) / A;
//    b[2 * (ncb + pg)] = b[2 * (num + pg) + 1] += (xxc - xx[pg + 1]) / A;
//    b[2 * (ncb + pgm1)] = b[2 * (num + pgm1) + 1] += (xx[pg] - xxc) / A;
//    peso = A / 2.0;
};
/*ostream& operator<<(ostream& co, elementodd& e)
{
    co << "  Numero de nos = " << e.qnno() << "\n  Material => " << e.material << "\n  Nos =>";
    for (int i = 0; i < e.qnno(); i++)
        co << "\n    No " << i << " = " << e.no[i];
    for (int i = 0; i < e.qprp(); i++)
        co << "\n  Propriedade " << i << " = " << e.prop[i];
    co << "\n  Deformacao calculada";
    int lpg = e.qptt();
    for (int pg = 0; pg < lpg; pg++)
    {
        co << "\n    Ponto de Gauss " << pg << ":";
        for (int i = 0; i < e.qnlb(); i++)
            co << "\n      Componente " << i << " = " << e.def[pg * e.qnlb() + i];
    }
    co << "\n  Tensao calculada";
    for (int pg = 0; pg < lpg; pg++)
    {
        co << "\n    Ponto de Gauss " << pg << ":";
        for (int i = 0; i < e.qnlb(); i++)
            co << "\n      Componente " << i << " = " << e.ten[pg * e.qnlb() + i];
    }
    co << "\n  Deslocamentos Nodais";
    for (int i = 0; i < e.qnno() * e.qipn(); i++)
        co << "\n x[" << i << "] = " << e.x[i];
    co << "\n  Forcas Nodais";
    for (int i = 0; i < e.qnno() * e.qipn(); i++)
        co << "\n f[" << i << "] = " << e.f[i];
    return co;
};
wxTextOutputStream& operator<<(wxTextOutputStream& co, elementodd& e)
{
    co << "  Numero de nos = " << e.qnno() << "\n  Material => " << e.material << "\n  Nos =>";
    for (int i = 0; i < e.qnno(); i++)
        co << "\n    No " << i << " = " << e.no[i];
    for (int i = 0; i < e.qprp(); i++)
        co << "\n  Propriedade " << i << " = " << e.prop[i];
    co << "\n  Deformacao calculada";
    int lpg = e.qptt();
    for (int pg = 0; pg < lpg; pg++)
    {
        co << "\n    Ponto de Gauss " << pg << ":";
        for (int i = 0; i < e.qnlb(); i++)
            co << "\n      Componente " << i << " = " << e.def[pg * e.qnlb() + i];
    }
    co << "\n  Tensao calculada";
    for (int pg = 0; pg < lpg; pg++)
    {
        co << "\n    Ponto de Gauss " << pg << ":";
        for (int i = 0; i < e.qnlb(); i++)
            co << "\n      Componente " << i << " = " << e.ten[pg * e.qnlb() + i];
    }
    co << "\n  Deslocamentos Nodais";
    for (int i = 0; i < e.qnno() * e.qipn(); i++)
        co << "\n x[" << i << "] = " << e.x[i];
    co << "\n  Forcas Nodais";
    for (int i = 0; i < e.qnno() * e.qipn(); i++)
        co << "\n f[" << i << "] = " << e.f[i];
    return co;
};
*/
/*void elementodd::pontos_de_gauss(const int p, double* x, double* w)
{
    double *xno, *yno, xxc, yyc;
    xno = new double[qnno()];
    yno = new double[qnno()];
    for (int i = 0; i < qnno; i++)
    {
        xxc += xno[i] = pno[i]->qx(0);
        yyc += yno[i] = pno[i]->qx(1);
    }
    switch (p)
    {
    case 4:
    case 5:
        xxc /= 5.;
        yyc /= 5.;
        x[0] = (xno[0] + xno[1] + xxc) / 3.0;
        y[0] = (yno[0] + yno[1] + yyc) / 3.0;
        x[1] = (xno[2] + xno[1] + xxc) / 3.0;
        y[1] = (yno[2] + yno[1] + yyc) / 3.0;
        x[2] = (xno[2] + xno[3] + xxc) / 3.0;
        y[2] = (yno[2] + yno[3] + yyc) / 3.0;
        x[3] = (xno[4] + xno[3] + xxc) / 3.0;
        y[3] = (yno[4] + yno[3] + yyc) / 3.0;
        x[4] = (xno[4] + xno[0] + xxc) / 3.0;
        y[4] = (yno[4] + yno[0] + yyc) / 3.0;
    }
};*/

