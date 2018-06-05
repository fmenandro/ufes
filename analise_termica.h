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
#ifndef ANALISE_TERMICA_H
#define ANALISE_TERMICA_H

#include "analise.h"
#include <cstring>

/**
@author Fernando Cesar Meira Menandro
*/
class analise_termica : public analise
{
   int npa,ncci,*nci;
#ifdef ALEATORIO
   class aleatorio *fc,t,dt,*xt,*ft,*xp,*fp,*M,*KK,*MM,teta;
#else
   double *fc,t,dt,*xt,*ft,*xp,*fp,*M,*KK,*MM,teta;
#endif
   class c_contorno ***cci;
public:
    analise_termica();
    analise_termica(ifstream&,ofstream&);
    analise_termica(wxTextInputStream&);
    ~analise_termica();
    void impoeCC(int);
    void impoeCC();
    void montaK();
    bool testa_iteracao();
	void roda();
	double qdt();
	void upft(int, double);
	void upM(int, double);
friend wxTextInputStream& operator>>(wxTextInputStream&, analise_termica&);

};

#endif
