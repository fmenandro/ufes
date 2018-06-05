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
/***************************************************************************

Detalhes das diretivas de compilação:

O arquivo defaleat.h define, ou não, o parâmetro ALEATORIO. Caso este
parâmetro esteja definido os dados de entrada são fornecidos para números
definidos como um intervalo de probabilidade. Caso o parâmetro não esteja
definido todos os dados (e variáveis internas) serão definidos como double.

Descrição do Arquivo de entrada:
0. A linha zero contém 1 variável inteira:
   0 -> Análise linear
   1 -> Análise iterativa

1. A primeira linha contém 4 variáveis inteiras:

1.1. Número de nós
1.2. Número de elementos
1.3. Número de materiais
1.4. Número de condições de contorno

2. A segunda e terceira linhas especificam o tipo e as propriedades dos materiais:
   Os materias possuem somente um tipo cadastrado, que corresponde ao
   material elástico linear.
   (haverão tantas segundas linhas quanto materiais)
2.1 Tipo (0 para térmico, 1 para elástico, 2 para térmico não-linear)
Caso O
3.1 Capacidade de calor
Caso 1
3.1 Módulo de Elasticidade
3.2 Coeficiente de Poisson
Caso 2   K= K1 + K2 T
3.1 Capacidade de calor fixa
3.2 Capacidade de calor proporcional à temperatura

4.
5. A quarta e a quinta linhas especificam a tabela de coordenadas nodais
   É necessário definir o tipo de nó (dimensionalidade: 1, 2 ou 3).
   (haverão tantos conjuntos de terceiras e quartas linhas quanto nós)

4.1 Tipo (1 corresponde a um nó unidimensional, 2 a um nó bidimensional e
    3 a um nó tridimensional).

5.1 Coordenadas nodais (tantas quanto tipo)

6.
7. A sexta e a sétima linhas especificam a tabela de conectividade
   É necessário definir o tipo de elemento.
   (haverão tantos conjuntos de quintas e sextas linhas quanto elementos)

6.1 Tipo:
1  barra unidimensional;
2  barra bidimensional;
3  viga bidimensional;
4  barra tridimensional;
5  elemento 2D 3 Nós;
6  elemento 2D 4 Nós;
7  Viga 3D;
8  elemento 2D 8 Nós;
9  elemento 2D 9 Nós;
10 Tubo;
11 elemento de propagação de calor 2d 4 nós;
12 elementos não-linear de calor 2d 4nós;


7.1 A linha 7 é representada na realidade em 3 linhas

   7.1[1] Número do material do elemento (o primeiro é zero).
   7.1[2] Nós que compõe o elemento (tantos quanto o tipo pressupõe, identificados pelo número)
   7.1[3] Propriedades específicas (características tais como espessura, momento de inércia, área, etc...)
          Tipo      Descrição      Número de nós    Número de propriedades reais
          1         Barra 1-D      2                1
          2         Barra 2-D      2                1
          3         Viga 2-D       2                2
          4         Barra 3-D      2                1
          5  elemento 2D 3 Nós     3                1
          6  elemento 2D 4 Nós     4                1
          7  Viga 3D               2                3
          8  elemento 2D 8 Nós     8                1
          9  elemento 2D 9 Nós     9                1
          10 Tubo                  2                ?
          11 calor 2d 4 nós        4                1
          12 não-linear calor2d4n  4                1

8.
9. A oitava e a nona linhas especificam as condições de contorno
   É necessário definir o tipo de condição.
   (haverão tantos conjuntos de oitavas e a nonas linhas quanto condições)

8.1 Tipo (0 corresponde a apoio fixo, 1 a deslocamento prescrito e
    2 a força prescrita, 3 múltipla, 4, múltipla especial, 5 mista, 6 mista especial).

0	A condição de apoio fixo prevê um grau de liberdade fixo (zero, após a resolução
do sistema). Pode ser um apoio fixo, para problemas de deformação, ou uma temperatura
nula, para problemas térmicos.
1	A condição de deslocamento prescrito prevê que após a resolução do sistema o
grau de liberdade especificado terá o valor prescrito. Pode ser um deslocamento
especificado, para problemas de deformação, ou uma temperatura prescrita, para
problemas térmicos.
2	A condição de força prescrita indica um valor a ser especificado para o vetor à
direita do sistema de equações a ser resolvido. Significa força, ou fluxo, conforme a
natureza do problema.
3	A condição múltipla é assim chamada por relacionar dois (ou mais, no caso da especial)
graus de liberdade. É especialmente útil no caso de apoios inclinados ou de condições de
simetria. São lidos duas linhas 9 (para o grau de liberdade zero e grau de liberdade 1),
de tal forma que estes estão relacionados pela fórmula
valor(0)*gl(0)+valor(1)*gl(1)=0.
4	A condição múltipla especial relaciona mais de dois graus de liberdade,
de tal forma que estes estão relacionados pela fórmula
valor(0)*gl(0)+valor(1)*gl(1)+...+valor(n)*gl(n)=0.
OBS: Para a condição múltipla especial deve-se primeiro ler o número de graus de liberdade.
5	A condição mista refere-se a relação entre o vetor à direita e o vetor à esquerda na
equação a ser resolvida. Basicamente representa uma condição de contorno de Robin.
Acrescentam-se à linha 9 dois valores adicionais, para obediência a uma equação do tipo
valor(0)*força=valor(1)*gl+valor(2), ou
valor(0)*fluxo=valor(1)*T+valor(2).
5	A condição mista especial refere-se a relação entre o vetor à direita e o vetor à esquerda na
equação a ser resolvida. Basicamente representa uma condição de contorno de Robin.
Acrescentam-se à linha 9 dois valores adicionais, para obediência a uma equação do tipo
valor(0)*força=valor(1)*gl+valor(2), ou
valor(0)*fluxo=valor(1)*T+valor(2).
9.1 Nó a que se refere a condição
9.2 Grau de liberdade (0 para x, 1 para y, 2 para z)
9.3 Valor prescrito (caso tipo 1 ou 2)(Caso mista, haverão mais 2 valores)

Caso a análise seja não linear, serão necessárias mais linhas:

10. Número de grupos de condições de contorno incrementais

11. Número de condições de cada grupo (tantas quanto 10)
12.
13. Tipo e Condições (conforme 8 e 9), tantas quanto 11 acima.

14. Intervalo de tempo
15. número de passos

16. Fatores de carga (multiplicação)(número de passos) para cada passo, para cada grupo de condições.
16.1 Tipo
16.2 Valores
****************************************************************************/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "analise.h"
#include "analise_incremental.h"
#include "analise_termica.h"


using namespace std;
// Função de manipulação de erro
void erro(char* s, char* s2 = "")
{
   cerr << s << ' ' << s2 << '\n';
   exit(1);
}

// Programa Principal
// As variáveis de linha de comando argv e argc não são utilizadas por este programa.
/*int ufesApp::mef(int tipo)
{
//  char stop;
  char arqent[20]="c1d2n2.txt", arqsai[20]="c1d2n2.sai";
                                      //  char arqent[20], arqsai[20];//="saida.txt";

// Leitura e abertura do arquivo de entrada de dados
  cout<<"\nEntre o nome do arquivo de entrada: ";
                                      //  cin>>arqent;
  ifstream ent(arqent);
  if(!ent) erro("Nao e possivel abrir o arquivo de entrada",arqent);
// Leitura e abertura do arquivo de saida de dados
  cout<<"\nEntre o nome do arquivo de saida: ";
                                      //  cin>>arqsai;
  ofstream sai(arqsai,ios::out);
  if(!sai) erro("Nao e possivel abrir o arquivo de saida",arqsai);
// Lê o tipo de análise e cria objeto correspondente
  int tipo;
  ent>>tipo;
  ifstream* ent;
  ent=ifstream(entrada);
  ofstream* sai;
  saida=saida;
//  ifstream ent(entrada);
//  ofstream sai(saida,ios::out);
  if (tipo==0)
  {
    class analise job(*ent);
    *sai<<" Projeto Permanente:\n";
    *sai<<job;
    cout<<" Projeto Permanente:\n";
    cout<<job;
  }
  else if (tipo==1)
  {
    *sai<<" Projeto Incremental:\n";
    cout<<" Projeto Incremental:\n";
    class analise_incremental job(*ent,*sai);
//    sai<<job;
//    cout<<job;
  }
  else
  {
    *sai<<" Projeto Termico:\n";
    cout<<" Projeto Termico:\n";
    class analise_termica job(*ent,*sai);
//    sai<<job;
//    cout<<job;
  }
//  cin>>stop;
//  ent.close();
// Fecha o arquivo de saida
//  sai.close();
// Encerra o programa com sucesso.
  return EXIT_SUCCESS;
}*/
