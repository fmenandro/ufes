/***************************************************************************
 *   Copyright (C) 2005 by Fernando Cesar Meira Menandro                   *
 *   fcmm@npd.ufes.br                                                      *
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
#ifndef ALEATORIO_H
#define ALEATORIO_H

/**
@author Fernando Cesar Meira Menandro
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <cstdlib>
#include <math.h>
#define np 11
#define nf 8
#define Tolerancia 1e-8
#define tolerGauss 1e-40
#define inf 1e101
#define qinf 1e100
#define PI 3.141592654
//class analise;
//class elemento;
//class Barra3D;
using namespace std;

class aleatorio
{
double x[np],y[np];
double A[np-1],B[np-1],C[np],D[np-1];
double m,d;
//friend class Barra1D;
//friend class Barra2D;
//friend class Barra3D;
//friend class Viga2D;
public:
/* A variável aleatória é guardada através das "np" abcissas 
e ordenadas da função densidade de probabilidade*/
aleatorio(double, double);
aleatorio();
aleatorio(const aleatorio& );
aleatorio(double );
aleatorio(double , double , int );
~aleatorio();
friend istream& operator>>(istream& ,aleatorio& );
friend ostream& operator<<(ostream& , const aleatorio& );
void testefdp(void);
aleatorio operator+(aleatorio);
aleatorio operator-();
aleatorio operator-(aleatorio);
aleatorio operator*(double);
aleatorio operator*(aleatorio);
aleatorio operator/(double);
aleatorio operator/(aleatorio);
aleatorio operator+=(aleatorio);
aleatorio operator-=(aleatorio);
aleatorio operator/=(aleatorio);
aleatorio operator*=(aleatorio);
aleatorio aabs(aleatorio);
bool operator<(double);
bool operator>(double);
bool operator<(aleatorio&);
bool operator>(aleatorio&);
double qm();
aleatorio asqrt();
private:
aleatorio getFDPspline();
aleatorio copy(aleatorio);
double media(aleatorio*);
double desvio(aleatorio*);
void gauss(double[np-1][np-1], double[np-1], int);
};
#endif
