/***************************************************************************
*   Copyright (C) 2005 by Fernando C�sar Meira Menandro   *
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
#include "elemento_poligonal2d.h"

elpol2d::elpol2d(int nno)
: isop2d(nno, ptg, 1)
{
	//this->nno = nno;
	//this->ptg = ptg;
}

elpol2d::~elpol2d()
{
}

int elpol2d::qptg(){
	return ptg;
}

void elpol2d::funcao_Forma(double r, double s, double *N, double *dn){};

void elpol2d::pontos_de_gauss(const int p, double *r, double *s, double *w) {
	switch (p){
	case 1:
		r[0] = 1.0 / 3;
		s[0] = 1.0 / 3;
		w[0] = 0.5;
		break;
	case 3:
		r[0] = 1.0 / 6;
		s[0] = 1.0 / 6;
		r[1] = 2.0 / 3;
		s[1] = 1.0 / 6;
		r[2] = 1.0 / 6;
		s[2] = 2.0 / 3;
		w[0] = 1.0 / 6;
		w[1] = 1.0 / 6;
		w[2] = 1.0 / 6;
		break;
	/*case 3:
		r[0] = 0;
		s[0] = 1.0 / 2;
		r[1] = 1.0 / 2;
		s[1] = 0;
		r[2] = 1.0 / 2;
		s[2] = 1.0 / 2;
		w[0] = 1.0 / 6;
		w[1] = 1.0 / 6;
		w[2] = 1.0 / 6;
		break;*/
	case 4:
		r[0] = 1.0 / 3;
		s[0] = 1.0 / 3;
		r[1] = 1.0 / 5;
		s[1] = 1.0 / 5;
		r[2] = 1.0 / 5;
		s[2] = 3.0 / 5;
		r[3] = 3.0 / 5;
		s[3] = 1.0 / 5;
		w[0] = -27.0 / 96;
		w[1] = 25.0 / 96;
		w[2] = 25.0 / 96;
		w[3] = 25.0 / 96;
		break;
	/*case 4:
		r[0] = 1.0 / 3;
		s[0] = 1.0 / 3;
		r[1] = 2.0 / 15;
		s[1] = 11. / 15;
		r[2] = 2.0 / 15;
		s[2] = 2.0 / 15;
		r[3] = 11. / 15;
		s[3] = 2.0 / 15;
		w[0] = -27.0 / 96;
		w[1] = 25.0 / 96;
		w[2] = 25.0 / 96;
		w[3] = 25.0 / 96;
		break;*/
	case 15:
		// Pontos obtidos por RENAN
		r[0] = 0.1797236328241150;
		r[1] = 0.0457456529856319;
		r[2] = 0.2177963752056270;
		r[3] = 0.4077636158173610;
		r[4] = 0.7381034332277130;
		r[5] = 0.8920605026597790;
		r[6] = 0.1413987265248490;
		r[7] = 0.4817353755077130;
		r[8] = 0.0000001252236083;
		r[9] = 0.6118332814722450;
		r[10] = 0.5228044030918780;
		r[11] = 0.3826087943722490;
		r[12] = 0.2046656101634270;
		r[13] = 0.0395901191931948;
		r[14] = 0.2811516336340470;
		s[0] = 0.0000001252236083;
		s[1] = 0.6118332814722450;
		s[2] = 0.5228044030918780;
		s[3] = 0.3826087943722490;
		s[4] = 0.2046656101634270;
		s[5] = 0.0395901191931948;
		s[6] = 0.2811516336340470;
		s[7] = 0.4817353755185290;
		s[8] = 0.1797236328241150;
		s[9] = 0.0457456529856319;
		s[10] = 0.2177963752056270;
		s[11] = 0.4077636158173610;
		s[12] = 0.7381034332277130;
		s[13] = 0.8920605026597790;
		s[14] = 0.1413987265248490;
		w[0] = 0.0214753306806812;
		w[1] = 0.0416320980181636;
		w[2] = 0.0488400720765520;
		w[3] = 0.0194825463863865;
		w[4] = 0.0323576332257816;
		w[5] = 0.0176310155862559;
		w[6] = 0.0538794193200105;
		w[7] = 0.0294097198767623;
		w[8] = 0.0214753306806812;
		w[9] = 0.0416320980181636;
		w[10] = 0.0488400720765520;
		w[11] = 0.0194825463863865;
		w[12] = 0.0323576332257816;
		w[13] = 0.0176310155862559;
		w[14] = 0.0538794193200105;
		break;
	case 16:
		r[0] = 0.333333333;
		r[1] = 0.459292588;
		r[2] = 0.459292588;
		r[3] = 0.081414823;
		r[4] = 0.170569308;
		r[5] = 0.170569308;
		r[6] = 0.658861384;
		r[7] = 0.050547228;
		r[8] = 0.050547228;
		r[9] = 0.898905543;
		r[10] = 0.26311283;
		r[11] = 0.728492393;
		r[12] = 0.008394777;
		r[13] = 0.728492393;
		r[14] = 0.26311283;
		r[15] = 0.008394777;
		s[0] = 0.333333333;
		s[1] = 0.459292588;
		s[2] = 0.081414823;
		s[3] = 0.459292588;
		s[4] = 0.170569308;
		s[5] = 0.658861384;
		s[6] = 0.170569308;
		s[7] = 0.050547228;
		s[8] = 0.898905543;
		s[9] = 0.050547228;
		s[10] = 0.728492393;
		s[11] = 0.008394777;
		s[12] = 0.26311283;
		s[13] = 0.26311283;
		s[14] = 0.008394777;
		s[15] = 0.728492393;
		w[0] = 0.144315608 / 2;
		w[1] = 0.095091634 / 2;
		w[2] = 0.095091634 / 2;
		w[3] = 0.095091634 / 2;
		w[4] = 0.103217371 / 2;
		w[5] = 0.103217371 / 2;
		w[6] = 0.103217371 / 2;
		w[7] = 0.032458498 / 2;
		w[8] = 0.032458498 / 2;
		w[9] = 0.032458498 / 2;
		w[10] = 0.027230314 / 2;
		w[11] = 0.027230314 / 2;
		w[12] = 0.027230314 / 2;
		w[13] = 0.027230314 / 2;
		w[14] = 0.027230314 / 2;
		w[15] = 0.027230314 / 2;
		break;
	case 25:
		r[0] = 0.333333333;
		r[1] = 0.485577633;
		r[2] = 0.485577633;
		r[3] = 0.028844733;
		r[4] = 0.109481575;
		r[5] = 0.109481575;
		r[6] = 0.781036849;
		r[7] = 0.550352942;
		r[8] = 0.550352942;
		r[9] = 0.307939839;
		r[10] = 0.307939839;
		r[11] = 0.141707219;
		r[12] = 0.141707219;
		r[13] = 0.728323905;
		r[14] = 0.728323905;
		r[15] = 0.246672561;
		r[16] = 0.246672561;
		r[17] = 0.025003535;
		r[18] = 0.025003535;
		r[19] = 0.923655934;
		r[20] = 0.923655934;
		r[21] = 0.066803251;
		r[22] = 0.066803251;
		r[23] = 0.009540815;
		r[24] = 0.009540815;
		s[0] = 0.333333333;
		s[1] = 0.485577633;
		s[2] = 0.028844733;
		s[3] = 0.485577633;
		s[4] = 0.109481575;
		s[5] = 0.781036849;
		s[6] = 0.109481575;
		s[7] = 0.307939839;
		s[8] = 0.141707219;
		s[9] = 0.550352942;
		s[10] = 0.141707219;
		s[11] = 0.550352942;
		s[12] = 0.307939839;
		s[13] = 0.246672561;
		s[14] = 0.025003535;
		s[15] = 0.728323905;
		s[16] = 0.025003535;
		s[17] = 0.728323905;
		s[18] = 0.246672561;
		s[19] = 0.066803251;
		s[20] = 0.009540815;
		s[21] = 0.923655934;
		s[22] = 0.009540815;
		s[23] = 0.923655934;
		s[24] = 0.066803251;
		w[0] = 0.045408995;
		w[1] = 0.0183629788782335;
		w[2] = 0.0183629788782335;
		w[3] = 0.0183629788782335;
		w[4] = 0.0226605295;
		w[5] = 0.0226605295;
		w[6] = 0.0226605295;
		w[7] = 0.0363789585;
		w[8] = 0.0363789585;
		w[9] = 0.0363789585;
		w[10] = 0.0363789585;
		w[11] = 0.0363789585;
		w[12] = 0.0363789585;
		w[13] = 0.0141636215;
		w[14] = 0.0141636215;
		w[15] = 0.0141636215;
		w[16] = 0.0141636215;
		w[17] = 0.0141636215;
		w[18] = 0.0141636215;
		w[19] = 0.0047108335;
		w[20] = 0.0047108335;
		w[21] = 0.0047108335;
		w[22] = 0.0047108335;
		w[23] = 0.0047108335;
		w[24] = 0.0047108335;
		break;
	}
}

void elpol2d::monta_n()
{
#ifdef ALEATORIO
	aleatorio
#else
	double
#endif
	// Inicializacao de variaveis ---
		r, s, J[2][2], invJ[2][2];
	double rpg[ptg], spg[ptg], wpg[ptg];
	int p = ptg;
	double r1[2], r2[2];
	double detJ1;
	const double pi = 3.14159265358979323846;
	int i, j, n;
	i = j = n = 0;
	for (i = 0; i < 2; i++)
	for (n = 0; n < qnno(); n++)
		dn[2 * n + i] = dN[2 * n + i] = 0.0;
	// -------------------------------

	// Mudança de coordenadas dos pontos de Gauss. Coordenadas do triângulo
	// padrao para o elemento padrao ----------------------------------------
	// Pontos das extremidades do triangulo (coordenadas do elemento padrao)
	for (i = 0; i < 2; i++){
		r1[i] = cos(2 * pi*(tri + i + 1) / qnno());
		r2[i] = sin(2 * pi*(tri + i + 1) / qnno());
	}
	detJ1 = r1[0] * r2[1] - r2[0] * r1[1];
	// Esse determinante nao muda conforme o ponto de Gauss, so depende do triangulo

	// Pontos de Gauss estão no sistema de coordenadas do triangulo,
	//entao, ele sao transformados para o sistema de coordenadas do elemento.
	// r e s: pontos de Gauss nas coordenadas do elemento.
	pontos_de_gauss(p, rpg, spg, wpg);	// Tem necessidade de chamar esse método de novo? (já é chamado em monta_rigidez)
	r = r1[0] * rpg[pg] + r1[1] * spg[pg];
	s = r2[0] * rpg[pg] + r2[1] * spg[pg];
	peso = wpg[pg];
	// -----------------------------------------------------------------------

	// Calcula N e dn para os pontos r e s (geralmente, os pontos de Gauss nas coordenadas do elemento)
	funcao_Forma(r, s, N, dn);

	// Matriz Jacobiana e Jacobiano
	// Esse Jacobiano está certo? J2 com essa mudança de coordenadas é mesmo J2?
	J[0][0] = J[0][1] = J[1][0] = J[1][1] = 0.0;
	for (i = 0; i < 2; i++){
		for (j = 0; j < 2; j++){
			for (n = 0; n < qnno(); n++){
				J[i][j] += dn[2 * n + i] * this->pno[n]->qx(j); // N�o entendi esse this -> ...
			}
		}
	}
	detJ = J[0][0] * J[1][1] - J[1][0] * J[0][1];

	//if (detJ > 100 || detJ < 0.001){
	//	ofstream myfile;
	//	string str;
	//	str = "Entradas e Saídas/Debug_" + to_string(qnno()) + "n.txt";
	//	myfile.open(str);			
	//	myfile << "detJ = " << detJ << "\npg = " << pg << "\ntri = " << tri;
	//	myfile.close();
	//}

	invJ[0][0] = J[1][1] / detJ;
	invJ[1][1] = J[0][0] / detJ;
	invJ[0][1] = -J[0][1] / detJ;
	invJ[1][0] = -J[1][0] / detJ;
	for (i = 0; i < 2; i++)
	for (j = 0; j < 2; j++)
	for (n = 0; n < qnno(); n++)
		dN[2 * n + i] += invJ[i][j] * dn[2 * n + j];
	peso *= fabs(double(detJ)) * fabs(double(detJ1));	// peso = peso * (detJ * detJ1)
}

void elpol2d::monta_rigidez()
{
#ifdef ALEATORIO
	aleatorio *xx, *yy;
	xx = new aleatorio[qnno()];
	yy = new aleatorio[qnno()];
#else
	double *xx, *yy;
	xx = new double[qnno()];
	yy = new double[qnno()];
#endif
	double *rpg, *spg, *wpg;
	rpg = new double[qptg()];
	spg = new double[qptg()];
	wpg = new double[qptg()];
	for (int i = 0; i<qnno()*qipn(); i++)
	for (int j = 0; j<qnno()*qipn(); j++)
		this->k[qnno()*qipn()*i + j] = 0.0;
	pontos_de_gauss(qptg(), rpg, spg, wpg);
	for (tri = 0; tri < qnno(); tri++){	// Para cada triangulo dentro do elemento
		// ATENCAO: quando estava somente tri < nno, o valor de tri = 5 entrava no loop nao sei o porquê.
		for (pg = 0; pg < qptg(); pg++){
			// Revisar se os pontos de Gauss são escolhidos no elemento ou no triangulo.
			// Se forem dentro do triangulo, acho que o loop tri deve estar acima dos pontos de Gauss
			// (ou nao faz diferenca)
			monta_b();
			monta_c();
			for (int i = 0; i < qnno()*qipn(); i++)
			for (int j = 0; j < qnlb(); j++)
			for (int l = 0; l < qnlb(); l++)
			for (int m = 0; m < qnno()*qipn(); m++)
				k[qnno()*qipn()*i + m] +=
				b[qnno()*qipn()*j + i] * c[qnlb()*j + l] * b[qnno()*qipn()*l + m] * peso;
		}
	}
	//// Nao da pra fazer assim, pois o monta_rigidez zeraria o k a cada entrada no loop do tri
	//for (tri = 0; tri < nno; tri++){
	//	isop2d::monta_rigidez();
	//}
};



#ifdef ALEATORIO
void elpol2d::p_processa(aleatorio *xx)
{
#else
void elpol2d::p_processa(double *xx)
{
#endif
	double *xpg, *ypg, *wpg;
	xpg = new double[qptg()];
	ypg = new double[qptg()];	// Nao havia esta linha
	wpg = new double[qptg()];
	pg = qptg();
	for (int i = 0; i<qnno()*qipn(); i++)
	{
		f[i] = 0.0;
		for (int n = 0; n<qnno(); n++)
		for (int j = 0; j<qipn(); j++)
			f[j] += qk(i, n*qipn() + j)*xx[qno(n)*qipn() + j];
	}
	for (int n = 0; n<qnno(); n++)
	for (int i = 0; i<qipn(); i++)
		x[n*qipn() + i] = xx[qno(n)*qipn() + i];
	pontos_de_gauss(pg, xpg, ypg, wpg);
	//int lpg = qptg();
	//if (qdim() == 2) lpg *= lpg;
	//if (qdim() == 3) lpg *= lpg*lpg;
	for (tri = 0; tri < qnno(); tri++){
		//for (pg = 0; pg < lpg; pg++)
		for (pg = 0; pg < qptg(); pg++)
		{
			monta_b();
			for (int i = 0; i < qnlb(); i++)
			{
				// Adicionei o  + tri*qptg()*qnlb() para computar os pontos de Gauss em cada triângulo
				// para 3 pontos de Gauss por triangulo, um elemento de 5 nós terá 15 pontos de Gauss.
				// Mas ainda falta escrever no arquivo de saída todos os pontos de Gauss.
				def[pg*qnlb() + i + tri*qptg()*qnlb()] = ten[pg*qnlb() + i + tri*qptg()*qnlb()] = 0;
				for (int j = 0; j < qnno()*qipn(); j++)
					def[pg*qnlb() + i + tri*qptg()*qnlb()] += b[i*qnno()*qipn() + j] * x[j];
			}
			monta_c();
			for (int i = 0; i < qnlb(); i++)
			{
				for (int j = 0; j < qnlb(); j++)
					ten[pg*qnlb() + i + tri*qptg()*qnlb()] += c[i*qnlb() + j] * def[j];
			}
		}
	}
};