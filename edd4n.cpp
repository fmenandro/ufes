/***************************************************************************
 *   Copyright (C) 2005 by Fernando César Meira Menandro   *
 *   menandro@localhost.localdomain   *
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
#include "edd4n.h"

edd4N::edd4N()
    : elementodd(nno, ptg)
{
}


edd4N::~edd4N()
{
}

/*void edd4N::monta_n()
{
    int num = qnno();
#ifdef ALEATORIO
    aleatorio
#else
    double
#endif
        r, s, * xx, * yy, xxc = 0, yyc = 0, A, Bx, By, um = 1.0, quatro = 4.0, tres = 3.0;
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
        {
            b[i * ncb + j] = 0.0;
        }
    xxc = yyc = 0;
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
    Bx = 0.2 * (xx[pg + 1] - xx[pg]) / (A * num);
    By = 0.2 * (yy[pg] - yy[pg + 1]) / (A * num);
    for (int i = 0; i < num; i++)
    {
        N[i] = um / (tres * num);
        b[2 * i] = b[2 * (ncb + i) + 1] = By;
        b[2 * (num + i) + 1] = b[2 * (ncb + i)] = Bx;
    }
    N[pg] = N[pg + 1] = (num + um) / (tres * num);
    b[2 * (ncb + pg) + 1] = b[2 * pg] += (yy[pg + 1] - yyc) / A;
    b[2 * (ncb + pg) + 3] = b[2 * pg + 2] += (yyc - yy[pg]) / A;
    b[2 * (ncb + pg)] = b[2 * (num + pg) + 1] += (xxc - xx[pg + 1]) / A;
    b[2 * (ncb + pg) + 2] = b[2 * (num + pg) + 3] += (xx[pg] - xxc) / A;
    peso = A / 2.0;
};*/
/*void edd4N::monta_n()
{
#ifdef ALEATORIO
    aleatorio
#else
    double
#endif
        r, s, xx[4], yy[4], xxc=0, yyc=0, A[4], Ag, At, um = 1.0, quatro = 4.0, tres = 3.0;
    for (int i = 0; i < qnlb(); i++)
        for (int j = 0; j < 8; j++)
        {
            b[i * 8 + j] = 0.0;
        }
    for (int i = 0; i < 4; i++)
    {
        xx[i] = this->pno[i]->qx(0);
        yy[i] = this->pno[i]->qx(1);
    }
    intersecta(this->pno[0], this->pno[1], this->pno[2], this->pno[3], xxc, yyc);
    A[0] = nn(xx[0], yy[0], xx[1], yy[1], xx[2], yy[2]);
    A[1] = nn(xx[1], yy[1], xx[2], yy[2], xx[3], yy[3]);
    A[2] = nn(xx[2], yy[2], xx[3], yy[3], xx[0], yy[0]);
    A[3] = nn(xx[3], yy[3], xx[0], yy[0], xx[1], yy[1]);
    switch(pg)
    {
    case 0:
        r = (xx[0] + xx[1] + xxc) / tres;
        s = (yy[0] + yy[1] + yyc) / tres;
        At = nn(xxc, yyc, xx[0], yy[0], xx[1], yy[1]);
        Ag = nn(r, s, xx[0], yy[0], xx[1], yy[1]);
        N[0] = nn(r, s, xx[1], yy[1], xx[2], yy[2]) / A[0] - 0.25 * Ag / At;
        N[1] = nn(r, s, xx[3], yy[3], xx[0], yy[0]) / A[3] - 0.25 * Ag / At;
        N[2] = Ag / A[0] - 0.25 * Ag / At;
        N[3] = nn(r, s, xx[0], yy[0], xx[1], yy[1]) / A[3] - 0.25 * Ag / At;
        b[0] = b[17] = (yy[1] - yy[2]) / A[0] - 0.25 * (yy[0] - yy[1]) / At;
        b[2] = b[19] = (yy[3] - yy[0]) / A[3] - 0.25 * (yy[0] - yy[1]) / At;
        b[4] = b[21] = (yy[0] - yy[1]) / A[0] - 0.25 * (yy[0] - yy[1]) / At;
        b[6] = b[23] = (yy[0] - yy[1]) / A[3] - 0.25 * (yy[0] - yy[1]) / At;
        b[9] = b[16] = (xx[2] - xx[1]) / A[0] - 0.25 * (xx[1] - xx[0]) / At;
        b[11] = b[18] = (xx[0] - xx[3]) / A[3] - 0.25 * (xx[1] - xx[0]) / At;
        b[13] = b[20] = (xx[1] - xx[0]) / A[0] - 0.25 * (xx[1] - xx[0]) / At;
        b[15] = b[22] = (xx[1] - xx[0]) / A[3] - 0.25 * (xx[1] - xx[0]) / At;
        peso = At / A[0];
        break;
    case 1:
        r = (xx[1] + xx[2] + xxc) / tres;
        s = (yy[1] + yy[2] + yyc) / tres;
        At = nn(xxc, yyc, xx[1], yy[1], xx[2], yy[2]);
        Ag = nn(r, s, xx[1], yy[1], xx[2], yy[2]);
        N[0] = nn(r, s, xx[1], yy[1], xx[2], yy[2]) / A[0] - 0.25 * Ag / At;
        N[1] = nn(r, s, xx[2], yy[2], xx[3], yy[3]) / A[1] - 0.25 * Ag / At;
        N[2] = nn(r, s, xx[0], yy[0], xx[1], yy[1]) / A[0] - 0.25 * Ag / At;
        N[3] = Ag / A[1] - 0.25 * Ag / At;
        b[0] = b[17] = (yy[1] - yy[2]) / A[0] - 0.25 * (yy[1] - yy[2]) / At;
        b[2] = b[19] = (yy[2] - yy[3]) / A[1] - 0.25 * (yy[1] - yy[2]) / At;
        b[4] = b[21] = (yy[0] - yy[1]) / A[0] - 0.25 * (yy[1] - yy[2]) / At;
        b[6] = b[23] = (yy[1] - yy[2]) / A[1] - 0.25 * (yy[1] - yy[2]) / At;
        b[9] = b[16] = (xx[2] - xx[1]) / A[0] - 0.25 * (xx[2] - xx[1]) / At;
        b[11] = b[18] = (xx[3] - xx[2]) / A[1] - 0.25 * (xx[2] - xx[1]) / At;
        b[13] = b[20] = (xx[1] - xx[0]) / A[0] - 0.25 * (xx[2] - xx[1]) / At;
        b[15] = b[22] = (xx[2] - xx[1]) / A[1] - 0.25 * (xx[2] - xx[1]) / At;
        peso = At / A[1];
        break;
    case 2:
        r = (xx[2] + xx[3] + xxc) / tres;
        s = (yy[2] + yy[3] + yyc) / tres;
        At = nn(xxc, yyc, xx[2], yy[2], xx[3], yy[3]);
        Ag = nn(r, s, xx[2], yy[2], xx[3], yy[3]);
        N[0] = Ag / A[2] - 0.25 * Ag / At;
        N[1] = nn(r, s, xx[2], yy[2], xx[3], yy[3]) / A[1] - 0.25 * Ag / At;
        N[2] = nn(r, s, xx[3], yy[3], xx[0], yy[0]) / A[2] - 0.25 * Ag / At;
        N[3] = nn(r, s, xx[1], yy[1], xx[2], yy[2]) / A[1] - 0.25 * Ag / At;
        b[0] = b[17] = (yy[2] - yy[3]) / A[2] - 0.25 * (yy[2] - yy[3]) / At;
        b[2] = b[19] = (yy[2] - yy[3]) / A[1] - 0.25 * (yy[2] - yy[3]) / At;
        b[4] = b[21] = (yy[3] - yy[0]) / A[2] - 0.25 * (yy[2] - yy[3]) / At;
        b[6] = b[23] = (yy[1] - yy[2]) / A[1] - 0.25 * (yy[2] - yy[3]) / At;
        b[9] = b[16] = (xx[3] - xx[2]) / A[2] - 0.25 * (xx[3] - xx[2]) / At;
        b[11] = b[18] = (xx[3] - xx[2]) / A[1] - 0.25 * (xx[3] - xx[2]) / At;
        b[13] = b[20] = (xx[0] - xx[3]) / A[2] - 0.25 * (xx[3] - xx[2]) / At;
        b[15] = b[22] = (xx[2] - xx[1]) / A[1] - 0.25 * (xx[3] - xx[2]) / At;
        peso = At / A[2];
        break;
    case 3:
        r = (xx[3] + xx[0] + xxc) / tres;
        s = (yy[3] + yy[0] + yyc) / tres;
        At = nn(xxc, yyc, xx[3], yy[3], xx[0], yy[0]);
        Ag = nn(r, s, xx[3], yy[3], xx[0], yy[0]);
        N[0] = nn(r, s, xx[2], yy[2], xx[3], yy[3]) / A[2] - 0.25 * Ag / At;
        N[1] = Ag / A[3] - 0.25 * Ag / At;
        N[2] = nn(r, s, xx[3], yy[3], xx[0], yy[0]) / A[2] - 0.25 * Ag / At;
        N[3] = nn(r, s, xx[0], yy[0], xx[1], yy[1]) / A[3] - 0.25 * Ag / At;
        b[0] = b[17] = (yy[2] - yy[3]) / A[2] - 0.25 * (yy[3] - yy[0]) / At;
        b[2] = b[19] = (yy[3] - yy[0]) / A[3] - 0.25 * (yy[3] - yy[0]) / At;
        b[4] = b[21] = (yy[3] - yy[0]) / A[2] - 0.25 * (yy[3] - yy[0]) / At;
        b[6] = b[23] = (yy[0] - yy[1]) / A[3] - 0.25 * (yy[3] - yy[0]) / At;
        b[9] = b[16] = (xx[3] - xx[2]) / A[2] - 0.25 * (xx[0] - xx[3]) / At;
        b[11] = b[18] = (xx[0] - xx[3]) / A[3] - 0.25 * (xx[0] - xx[3]) / At;
        b[13] = b[20] = (xx[0] - xx[3]) / A[2] - 0.25 * (xx[0] - xx[3]) / At;
        b[15] = b[22] = (xx[1] - xx[0]) / A[3] - 0.25 * (xx[0] - xx[3]) / At;
        peso = At / A[3];
    }
}*/
