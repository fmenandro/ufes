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
#include "elementoddq.h"

 /* O elemento com derivada descontínua bidimensional quadrático é uma classe base para
 criação de outros elementos quadráticos de duas dimensões. As variáveis estáticas
    const static int dim=2;  //Dimensao do problema
    const static int ipn=2;  //Numero de incognitas por no
    const static int prp=1;  //Numero de propriedades do elemento (area,espessura)
                             //Propriedade 0: espessura
    const static int nlb=3;  //Numero de linhas da matriz B (componentes de deformacao)
 já ficam definidas, restando a definição do número de nós (nno) e do número de pontos
 de Gauss (ptg). */
elementoddq::elementoddq(int nno, int ptg)
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


elementoddq::~elementoddq()
{
};


void elementoddq::monta_b()
{
    monta_n();
    /*    for (int i = 0; i < qnno(); i++)
        {
            b[(2 * i)] = b[4 * qnno() + 2 * i + 1] = dN[i * 2];
            b[2 * (qnno() + i) + 1] = b[4 * qnno() + 2 * i] = dN[i * 2 + 1];
            b[(2 * i) + 1] = b[2 * (qnno() + i)] = 0.0;
        }*/
};
void elementoddq::monta_c()
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
void elementoddq::monta_rigidez()
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
void elementoddq::p_processa(double* xx)
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

void elementoddq::monta_n()
{
    int num = qnno();
    int n2 = num/2;
#ifdef ALEATORIO
    aleatorio
#else
    double
#endif
        r, s, * xx, * yy, * xm, * ym, xxc = 0, yyc = 0, A, rpg, spg, um = 1.0, dois = 2.0, quatro = 4.0, tres = 3.0, 
        NN[6], dN[12], dn[12], J[2][2], invJ[2][2], xyn[6][2], detJ, detJ1;
    int ipg, ppg, ncb = num * qipn();
#ifdef ALEATORIO
    xx = new aleatorio[n2 + 1];
    yy = new aleatorio[n2 + 1];
    xm = new aleatorio[n2];
    ym = new aleatorio[n2];
#else
    xx = new double[n2 + 1];
    yy = new double[n2 + 1];
    xm = new double[n2];
    ym = new double[n2];
#endif
    for (int i = 0; i < qnlb(); i++)
        for (int j = 0; j < ncb; j++)
            b[i * ncb + j] = 0.0;
    for (int i = 0; i < n2; i++)
    {
        xx[i] = this->pno[2*i]->qx(0);
        yy[i] = this->pno[2*i]->qx(1);
        xm[i] = this->pno[2*i+1]->qx(0);
        ym[i] = this->pno[2*i+1]->qx(1);
        xxc += xx[i]+ xm[i];
        yyc += yy[i]+ ym[i];
    }
    xxc /= num;
    yyc /= num;
    xx[n2] = xx[0];
    yy[n2] = yy[0];
    //    intersecta(this->pno[0], this->pno[1], this->pno[2], this->pno[3], xxc, yyc);
//    A = nn(xx[pg], yy[pg], xx[pg + 1], yy[pg + 1], xxc, yyc);
 //       for{int i = 0; i < pgmn1; i++}
//        {
//        xpg = xm[pg - n2];
//        ypg = ym[pg - n2];
/* 
    Tomando o sub-elemento (onde está definida a função de interpolação) imediatamente após o ponto de Gauss
*/
     peso = 1 / tres;
     ppg = pg / 2;
     if (pg % 2)
     {
         rpg = spg = 0.5;
     }
     else
     {
         rpg = 0.5; 
         spg = 0.0;
     }
     xyn[0][0] = xxc;
     xyn[0][1] = yyc;
     xyn[1][0] = xx[ppg];
     xyn[1][1] = yy[ppg];
     xyn[2][0] = xx[ppg + 1];
     xyn[2][1] = yy[ppg + 1];
     xyn[3][0] = (xxc + xx[ppg]) / dois;
     xyn[3][1] = (yyc + yy[ppg]) / dois;
     xyn[4][0] = xm[ppg];
     xyn[4][1] = ym[ppg];
     xyn[5][0] = (xxc + xx[ppg + 1]) / dois;
     xyn[5][1] = (yyc + yy[ppg + 1]) / dois;
     NN[0] = (dois * (um - rpg - spg) - um) * (um - rpg - spg);
     NN[1] = (dois * rpg - um) * rpg;
     NN[2] = (dois * spg - um) * spg;
     NN[3] = quatro * (um - rpg - spg) * rpg;
     NN[4] = quatro * rpg * spg;
     NN[5] = quatro * (um - rpg - spg) * spg;
     dn[0] = dn[1] = -tres + quatro * (rpg + spg);
     dn[2] = quatro * rpg - um;
     dn[3] = dn[4] = 0.0;
     dn[5] = quatro * spg - um;
     dn[6] = quatro * (um - dois * rpg - spg);
     dn[7] = -quatro * rpg;
     dn[8] = quatro * spg;
     dn[9] = quatro * rpg;
     dn[10] = -quatro * spg;
     dn[11] = quatro * (um - dois * spg - rpg);
     J[0][0] = J[0][1] = J[1][0] = J[1][1] = 0.0;
     for (int i = 0; i < 2; i++)
         for (int j = 0; j < 2; j++)
             for (int n = 0; n < 6; n++)
                 J[i][j] += dn[2 * n + i] * xyn[n][j];
     detJ = J[0][0] * J[1][1] - J[1][0] * J[0][1];
     invJ[0][0] = J[1][1] / detJ;
     invJ[1][1] = J[0][0] / detJ;
     invJ[0][1] = -J[0][1] / detJ;
     invJ[1][0] = -J[1][0] / detJ;
     for (int i = 0; i < 12; i++) dN[i] = 0.0;
     for (int i = 0; i < 2; i++)
         for (int j = 0; j < 2; j++)
             for (int n = 0; n < 6; n++)
                 dN[2 * n + i] += invJ[i][j] * dn[2 * n + j];
     if (!(pg % 2))
     { 
         int zero = (pg == num - 2) ? 1 : 0;
         for (int nn = zero; nn < pg; nn++)
         {             
             b[(2 * nn)] = b[2 * ncb + 2 * nn + 1] += (dN[0] + (dN[6] + dN[10]) / dois) / (dois*num);
             b[2 * (num + nn) + 1] = b[2 * ncb + 2 * nn] += (dN[1] + (dN[7]+dN[11]) / dois) / (dois*num);
//            b[(2 * nn) + 1] = b[2 * (num + nn)] += 0.0;
        }
         for (int nn = pg+3; nn < num; nn++)
        {
            b[(2 * nn)] = b[2*ncb+ 2 * nn + 1] += (dN[0] + (dN[6] + dN[10]) / dois) / (dois * num);
            b[2 * (num + nn) + 1] = b[2*ncb+ 2 * nn] += (dN[1] + (dN[7] + dN[11]) / dois) / (dois * num);
//            b[(2 * nn) + 1] = b[2 * (num + nn)] += 0.0;
        }
        int pgm2 = (pg == num-2) ? 0 : pg + 2;
        b[(2 * pg)] = b[2*ncb+ 2 * pg + 1] += (dN[0] + dN[2]*num + (dN[6]*(um+num)+ dN[10]) / dois) / (dois*num);
        b[2 * (num + pg) + 1] = b[2*ncb+ 2 * pg] += (dN[1] + dN[3] * num + (dN[7] * (um + num) + dN[11]) / dois) / (dois * num);
        //        b[(2 * pgmn2) + 1] = b[2 * (num + pgmn2)] += 0.0;
        b[(2 * pgm2)] = b[2*ncb+ 2 * pgm2 + 1] += (dN[0] + dN[4] * num + (dN[6] + (um + num) * dN[10]) / dois) / (dois * num);
        b[2 * (num + pgm2) + 1] = b[2*ncb+ 2 * pgm2] += (dN[1] + dN[5] * num + (dN[7] + (um + num) * dN[11]) / dois) / (dois * num);
        //        b[(2 * pgm2) + 1] = b[2 * (num + pgm2)] += 0.0;
        b[(2 * (pg+1))] = b[2*ncb+ 2 * (pg+1) + 1] += (dN[0] + dN[8]*num+ (dN[6] + dN[10]) / dois) / (dois * num);
        b[2 * (num + (pg+1)) + 1] = b[2*ncb+ 2 * (pg+1)] += (dN[1] + dN[9] * num + (dN[7] + dN[11]) / dois) / (dois * num);
        //        b[(2 * pgmn2) + 1] = b[2 * (num + pgmn2)] += 0.0;
 //       peso *= detJ;
        /*
           Tomando agora o sub-elemento (onde está definida a função de interpolação) imediatamente anterior ao ponto de Gauss
       */
        int pgmn1 = (ppg == 0) ? n2 - 1 : ppg - 1;
        xyn[0][0] = xxc;
        xyn[0][1] = yyc;
        xyn[1][0] = xx[pgmn1];
        xyn[1][1] = yy[pgmn1];
        xyn[2][0] = xx[pgmn1 + 1];
        xyn[2][1] = yy[pgmn1 + 1];
        xyn[3][0] = (xxc + xx[pgmn1]) / dois;
        xyn[3][1] = (yyc + yy[pgmn1]) / dois;
        xyn[4][0] = xm[pgmn1];
        xyn[4][1] = ym[pgmn1];
        xyn[5][0] = (xxc + xx[pgmn1 + 1]) / dois;
        xyn[5][1] = (yyc + yy[pgmn1 + 1]) / dois;
        rpg = 0.0;
        spg = 0.5;
        NN[0] = (dois * (um - rpg - spg) - um) * (um - rpg - spg);
        NN[1] = (dois * rpg - um) * rpg;
        NN[2] = (dois * spg - um) * spg;
        NN[3] = quatro * (um - rpg - spg) * rpg;
        NN[4] = quatro * rpg * spg;
        NN[5] = quatro * (um - rpg - spg) * spg;
        dn[0] = dn[1] = -tres + quatro * (rpg + spg);
        dn[2] = quatro * rpg - um;
        dn[3] = dn[4] = 0.0;
        dn[5] = quatro * spg - um;
        dn[6] = quatro * (um - dois * rpg - spg);
        dn[7] = -quatro * rpg;
        dn[8] = quatro * spg;
        dn[9] = quatro * rpg;
        dn[10] = -quatro * spg;
        dn[11] = quatro * (um - dois * spg - rpg);
        J[0][0] = J[0][1] = J[1][0] = J[1][1] = 0.0;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int n = 0; n < 6; n++)
                    J[i][j] += dn[2 * n + i] * xyn[n][j];
        detJ1 = J[0][0] * J[1][1] - J[1][0] * J[0][1];
        invJ[0][0] = J[1][1] / detJ1;
        invJ[1][1] = J[0][0] / detJ1;
        invJ[0][1] = -J[0][1] / detJ1;
        invJ[1][0] = -J[1][0] / detJ1;
        for (int i = 0; i < 12; i++) dN[i] = 0.0;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int n = 0; n < 6; n++)
                    dN[2 * n + i] += invJ[i][j] * dn[2 * n + j];
        for (int nn = 0; nn < pg-2; nn++)
        {
            b[(2 * nn)] = b[2*ncb+ 2 * nn + 1] += (dN[0] + (dN[6] + dN[10]) / dois) / (dois * num);
            b[2 * (num + nn) + 1] = b[2*ncb+ 2 * nn] += (dN[1] + (dN[7] + dN[11]) / dois) / (dois * num);
            //            b[(2 * nn) + 1] = b[2 * (num + nn)] += 0.0;
        }
        int pgmn2 = (pg < 3) ? pg+num - 2 : num;
        for (int nn = pg + 1; nn < pgmn2; nn++)
        {
            b[(2 * nn)] = b[2*ncb+ 2 * nn + 1] += (dN[0] + (dN[6] + dN[10]) / dois) / (dois * num);
            b[2 * (num + nn) + 1] = b[2*ncb+ 2 * nn] += (dN[1] + (dN[7] + dN[11]) / dois) / (dois * num);
            //            b[(2 * nn) + 1] = b[2 * (num + nn)] += 0.0;
        }
        pgmn2 = (pg == 0) ? num - 2 : pg - 2;
        b[(2 * pg)] = b[2*ncb+ 2 * pg + 1] += (dN[0] + dN[4] * num + (dN[6] + (um + num) * dN[10]) / dois) / (dois * num);
        b[2 * (num + pg) + 1] = b[2*ncb+ 2 * pg] += (dN[1] + dN[5] * num + (dN[7] + (um + num) * dN[11]) / dois) / (dois * num);
        //        b[(2 * pgmn2) + 1] = b[2 * (num + pgmn2)] += 0.0;
        b[(2 * pgmn2)] = b[2*ncb+ 2 * pgmn2 + 1] += (dN[0] + dN[2] * num + (dN[6] * (um + num) + dN[10]) / dois) / (dois * num);
        b[2 * (num + pgmn2) + 1] = b[2*ncb+ 2 * pgmn2] += (dN[1] + dN[3] * num + (dN[7] * (um + num) + dN[11]) / dois) / (dois * num);
        //        b[(2 * pgm2) + 1] = b[2 * (num + pgm2)] += 0.0;
        b[(2 * (pgmn2 + 1))] = b[2*ncb+ 2 * (pgmn2 + 1) + 1] += (dN[0] + dN[8] * num + (dN[6] + dN[10]) / dois) / (dois * num);
        b[2 * (num + (pgmn2 + 1)) + 1] = b[2*ncb+ 2 * (pgmn2 + 1)] += (dN[1] + dN[9] * num + (dN[7] + dN[11]) / dois) / (dois * num);
        //        b[(2 * pgmn2) + 1] = b[2 * (num + pgmn2)] += 0.0;
        peso *= (detJ+detJ1);
     }
     else
     {
         for (int nn = 0; nn < pg-1; nn++)
         {
             b[(2 * nn)] = b[2*ncb+ 2 * nn + 1] += (dN[0] + (dN[6] + dN[10]) / dois) / ( num);
             b[2 * (num + nn) + 1] = b[2*ncb+ 2 * nn] += (dN[1] + (dN[7] + dN[11]) / dois) / ( num);
             //            b[(2 * nn) + 1] = b[2 * (num + nn)] += 0.0;
         }
         for (int nn = pg + 2; nn < num; nn++)
         {
             b[(2 * nn)] = b[2*ncb+ 2 * nn + 1] += (dN[0] + (dN[6] + dN[10]) / dois) / ( num);
             b[2 * (num + nn) + 1] = b[2*ncb+ 2 * nn] += (dN[1] + (dN[7] + dN[11]) / dois) / ( num);
             //            b[(2 * nn) + 1] = b[2 * (num + nn)] += 0.0;
         }
         int pgm1 = (pg == num-1) ? 0 : pg + 1;
         b[(2 * pg)] = b[2*ncb+ 2 * pg + 1] += (dN[0] + dN[8] * num + (dN[6] + dN[10]) / dois) / ( num); 
         b[2 * (num + pg) + 1] = b[2*ncb+ 2 * pg] += (dN[1] + dN[9] * num + (dN[7] + dN[11]) / dois) / ( num); 
         //        b[(2 * pgmn2) + 1] = b[2 * (num + pgmn2)] += 0.0;
         b[(2 * pgm1)] = b[2*ncb+ 2 * pgm1 + 1] += (dN[0] + dN[4] * num + (dN[6] + (um + num) * dN[10]) / dois) / ( num);
         b[2 * (num + pgm1) + 1] = b[2*ncb+ 2 * pgm1] += (dN[1] + dN[5] * num + (dN[7] + (um + num) * dN[11]) / dois) / ( num);
         //        b[(2 * pgm2) + 1] = b[2 * (num + pgm2)] += 0.0;
         b[(2 * (pg - 1))] = b[2*ncb+ 2 * (pg - 1) + 1] += (dN[0] + dN[2] * num + (dN[6] * (um + num) + dN[10]) / dois) / ( num);
         b[2 * (num + (pg - 1)) + 1] = b[2*ncb+ 2 * (pg - 1)] += (dN[1] + dN[3] * num + (dN[7] * (um + num) + dN[11]) / dois) / ( num);
         //        b[(2 * pgmn2) + 1] = b[2 * (num + pgmn2)] += 0.0;
         peso *= detJ;
     }
     if (pg % n2)
     {
         N[pg] = (um + num) / (2 * num);
         //       N[pg] = ((dois * L3_a) * L3_a + (dois * L1_a) * L1_a / num + L3_a * L1_a * tres * tres / dois + L2_a * L1_a * / quatro +
 //            (dois * L2_d) * L2_d + L1_d / num + L2_d * L1_d * tres * tres / dois + L3_d * L1_d * / quatro) / dois;
     }
     else
     {
         N[pg] = 1;
         //        N[pg] = ((dois * L3_a) * L3_a + (dois * L1_a) * L1_a / num + L3_a * L1_a * tres * tres / dois + L2_a * L1_a * / quatro +
         //            (dois * L2_d) * L2_d + L1_d / num + L2_d * L1_d * tres * tres / dois + L3_d * L1_d * / quatro) / dois;

     }
     peso /= dois;
};