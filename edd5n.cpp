#include "edd5n.h"
edd5N::edd5N()
    : elementodd(nno, ptg)
{
}


edd5N::~edd5N()
{
}

/*void edd5N::monta_n()
{
    int num = qnno();
#ifdef ALEATORIO
    aleatorio
#else
    double
#endif
        r, s, xx[6], yy[6], xxc = 0, yyc = 0, A, Bx, By, um = 1.0, quatro = 4.0, tres = 3.0;
    int ncb = num * qipn();
//#ifdef ALEATORIO
//    xx = new aleatorio[num + 1];
//    yy = new aleatorio[num + 1];
//#else
//    xx = new double[num + 1];
//    yy = new double[num + 1];
//#endif
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
    A = nn(xx[pg], yy[pg], xx[pg + 1], yy[pg + 1], xxc, yyc);
    r = (xx[pg] + xx[pg + 1] + xxc) / tres;
    s = (yy[pg] + yy[pg + 1] + yyc) / tres;
    Bx = (xx[pg + 1] - xx[pg]) / (A * num);
    By = (yy[pg] - yy[pg + 1]) / (A * num);
    for (int i = 0; i < num; i++)
    {
        N[i] = um / (tres * num);
        b[2 * i] = b[2 * (ncb + i) + 1] = By;
        b[2 * (num + i) + 1] = b[2 * (ncb + i)] = Bx;
    }
    int pgm1=(pg==4)?0:pg+1;
    N[pg] = N[pgm1] = (num + um) / (tres * num);
    b[2 * (ncb + pg) + 1] = b[2 * pg] += (yy[pg + 1] - yyc) / A;
    b[2 * (ncb + pgm1) + 1] = b[2 * pgm1] += (yyc - yy[pg]) / A;
    b[2 * (ncb + pg)] = b[2 * (num + pg) + 1] += (xxc - xx[pg + 1]) / A;
    b[2 * (ncb + pgm1)] = b[2 * (num + pgm1) + 1] += (xx[pg] - xxc) / A;
    peso = A / 2.0;
};
/*void edd5N::monta_n()
{
#ifdef ALEATORIO
    aleatorio
#else
    double
#endif
        r, s, xx[5], yy[5], xxc = 0, yyc = 0, A[5], Bx, By, Ag, At, um = 1.0, quatro = 4.0, tres = 3.0;
    for (int i = 0; i < qnlb(); i++)
        for (int j = 0; j < 10; j++)
        {
            b[i * 10 + j] = 0.0;
        }
    xxc = yyc = 0;
    for (int i = 0; i < 5; i++)
    {
        xx[i] = this->pno[i]->qx(0);
        yy[i] = this->pno[i]->qx(1);
        xxc += xx[i];
        yyc += yy[i];
    }
    xxc /= 5.0;
    yyc /= 5.0;
//    intersecta(this->pno[0], this->pno[1], this->pno[2], this->pno[3], xxc, yyc);
    A[0] = nn(xx[0], yy[0], xx[1], yy[1], xxc, yyc);
    A[1] = nn(xx[1], yy[1], xx[2], yy[2], xxc, yyc);
    A[2] = nn(xx[2], yy[2], xx[3], yy[3], xxc, yyc);
    A[3] = nn(xx[3], yy[3], xx[4], yy[4], xxc, yyc);
    A[4] = nn(xx[4], yy[4], xx[0], yy[0], xxc, yyc);
    At = A[0] + A[1] + A[2] + A[3] + A[4] + A[5];
    switch (pg)
    {
    case 0:
        r = (xx[0] + xx[1] + xxc) / tres;
        s = (yy[0] + yy[1] + yyc) / tres;
 //       Ag = nn(xx[0], yy[0], xx[1], yy[1], r, s);
        Bx = 0.2 * (xx[1] - xx[0]) / A[0];
        By = 0.2 * (yy[0] - yy[1]) / A[0];
        N[0] = N[1] = 0.4;
        N[2] = N[3] = N[4] = 0.2 / 3.0;
        // dN0/dx
        b[0] = b[21] = By + (yy[1] - yyc) / A[0];
        // dN1/dx
        b[2] = b[23] = By + (yyc - yy[0]) / A[0];
        // dN2/dx
        b[4] = b[25] = By;
        // dN3/dx
        b[6] = b[27] = By;
        // dN4/dx
        b[8] = b[29] = By;
        // dN0/dy
        b[11] = b[20] = Bx + (xxc - xx[1]) / A[0];
        // dN1/dy
        b[13] = b[22] = Bx + (xx[0] - xxc) / A[0];
        // dN2/dy
        b[15] = b[24] = Bx;
        // dN3/dy
        b[17] = b[26] = Bx;
        // dN4/dy
        b[19] = b[28] = Bx;
//        peso = At / A[0];
        break;
    case 1:
        r = (xx[1] + xx[2] + xxc) / tres;
        s = (yy[1] + yy[2] + yyc) / tres;
        Bx = 0.2 * (xx[2] - xx[1]) / A[1];
        By = 0.2 * (yy[1] - yy[2]) / A[1];
        N[1] = N[2] = 0.4;
        N[0] = N[3] = N[4] = 0.2 / 3.0;
        // dN0/dx
        b[0] = b[21] = By;
        // dN1/dx
        b[2] = b[23] = By + (yy[2] - yyc) / A[1];
        // dN2/dx
        b[4] = b[25] = By + (yyc - yy[1]) / A[1];
        // dN3/dx
        b[6] = b[27] = By;
        // dN4/dx
        b[8] = b[29] = By;
        // dN0/dy
        b[11] = b[20] = Bx;
        // dN1/dy
        b[13] = b[22] = Bx + (xxc - xx[2]) / A[1];
        // dN2/dy
        b[15] = b[24] = Bx + (xx[1] - xxc) / A[1];
        // dN3/dy
        b[17] = b[26] = Bx;
        // dN4/dy
        b[19] = b[28] = Bx;
        break;
    case 2:
        r = (xx[2] + xx[3] + xxc) / tres;
        s = (yy[2] + yy[3] + yyc) / tres;
        Bx = 0.2 * (xx[3] - xx[2]) / A[2];
        By = 0.2 * (yy[2] - yy[3]) / A[2];
        N[2] = N[3] = 0.4;
        N[0] = N[1] = N[4] = 0.2 / 3.0;
        // dN0/dx
        b[0] = b[21] = By;
        // dN1/dx
        b[2] = b[23] = By;
        // dN2/dx
        b[4] = b[25] = By + (yy[3] - yyc) / A[2];
        // dN3/dx
        b[6] = b[27] = By + (yyc - yy[2]) / A[2];
        // dN4/dx
        b[8] = b[29] = By;
        // dN0/dy
        b[11] = b[20] = Bx;
        // dN1/dy
        b[13] = b[22] = Bx;
        // dN2/dy
        b[15] = b[24] = Bx + (xxc - xx[3]) / A[2];
        // dN3/dy
        b[17] = b[26] = Bx + (xx[2] - xxc) / A[2];
        // dN4/dy
        b[19] = b[28] = Bx;
        break;
    case 3:
        r = (xx[3] + xx[4] + xxc) / tres;
        s = (yy[3] + yy[4] + yyc) / tres;
        Bx = 0.2 * (xx[4] - xx[3]) / A[3];
        By = 0.2 * (yy[3] - yy[4]) / A[3];
        N[3] = N[4] = 0.4;
        N[0] = N[1] = N[2] = 0.2 / 3.0;
        // dN0/dx
        b[0] = b[21] = By;
        // dN1/dx
        b[2] = b[23] = By;
        // dN2/dx
        b[4] = b[25] = By;
        // dN3/dx
        b[6] = b[27] = By + (yy[4] - yyc) / A[3];
        // dN4/dx
        b[8] = b[29] = By + (yyc - yy[3]) / A[3];
        // dN0/dy
        b[11] = b[20] = Bx;
        // dN1/dy
        b[13] = b[22] = Bx;
        // dN2/dy
        b[15] = b[24] = Bx;
        // dN3/dy
        b[17] = b[26] = Bx + (xxc - xx[4]) / A[3];
        // dN4/dy
        b[19] = b[28] = Bx + (xx[3] - xxc) / A[3];
        break;
    case 4:
        r = (xx[4] + xx[0] + xxc) / tres;
        s = (yy[4] + yy[0] + yyc) / tres;
        Bx = 0.2 * (xx[0] - xx[4]) / A[4];
        By = 0.2 * (yy[4] - yy[0]) / A[4];
        N[4] = N[0] = 0.4;
        N[3] = N[1] = N[2] = 0.2 / 3.0;
        // dN0/dx
        b[0] = b[21] = By + (yyc - yy[4]) / A[4];
        // dN1/dx
        b[2] = b[23] = By;
        // dN2/dx
        b[4] = b[25] = By;
        // dN3/dx
        b[6] = b[27] = By;
        // dN4/dx
        b[8] = b[29] = By + (yy[0] - yyc) / A[4];
        // dN0/dy
        b[11] = b[20] = Bx + (xx[4] - xxc) / A[4];
        // dN1/dy
        b[13] = b[22] = Bx;
        // dN2/dy
        b[15] = b[24] = Bx;
        // dN3/dy
        b[17] = b[26] = Bx;
        // dN4/dy
        b[19] = b[28] = Bx + (xxc - xx[0]) / A[4];
    }
    peso = A[pg]/2;
}*/
