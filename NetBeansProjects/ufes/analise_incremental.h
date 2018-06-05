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
#ifndef ANALISE_INCREMENTAL_H
#define ANALISE_INCREMENTAL_H

#include "analise.h"

/**
@author Fernando Cesar Meira Menandro
*/
class analise_incremental : public analise
{
   int npa,ncci,*nci;
#ifdef ALEATORIO
   class aleatorio *fc,t,dt,*xt,*ft,*xp,*fp;
#else
   double *fc,t,dt,*xt,*ft,*xp,*fp;
#endif
   class c_contorno ***cci;
public:
    analise_incremental();
    analise_incremental(ifstream&,ofstream&);
    analise_incremental(wxTextInputStream&,wxTextOutputStream&);
    ~analise_incremental();
    void impoeCC(int);
    void impoeCC();
    bool testa_iteracao();

};

#endif
