#pragma once
#include "Celula.h"
#include<iostream>
#include <ctime>
#include <vector>
/*Classe que representa o Mapa do campo Minado
	
	Definição dos Atributos:

	linhas - número de linhas do mapa
	colunas - número de colunas do mapa
	qtdBombas - é o número de bombas que terá no mapa
	matrizCelulas - É o mapa em si, ele é formado por uma matriz de Célula
*/
class Mapa {
	private:
		int linhas = 1;
		int colunas = 1;
		int qtdBombas = 5;
		Celula** matrizCelulas;
		
	public:
		/* Construtor da Classe Mapa*/
		Mapa(int l, int c, int b) {
			
			linhas = l;
			colunas = c;
			qtdBombas = b;

			/* Aloca memória para a matriz */
			matrizCelulas = new Celula*[linhas];
			for (int i = 0; i < linhas; i++) {
				matrizCelulas[i] = new Celula[colunas];
			}

			//Guarda na celula a sua posição no mapa
			for (int x = 0; x < linhas; x++) {
				for (int y = 0; y < colunas; y++) {
					matrizCelulas[x][y].setLinha(x);
					matrizCelulas[x][y].setColuna(y);
				}
			}

		}
		
		/* Destrutor da Classe Mapa*/
		~Mapa() {
			/* deleta a memória alocada */
			for (int i = 0; i < linhas; i++) {
				delete[] matrizCelulas[i];
			}
			delete[] matrizCelulas;
		}
		
		/*gera a Matriz*/
		void gerarMatriz() {
			int posicoes = linhas * colunas;
			std::vector<int> posicoesBombas(qtdBombas);
			
			//inicializa o rand
			srand(time(0));
			
			/*gera uma lista com posições aleatórias, para cada bomba ocupar na matriz*/
			for (int i = 0; i < qtdBombas; i++) {
				int resultado = rand() % posicoes;
				if (std::find(posicoesBombas.begin(), posicoesBombas.end(), resultado) != posicoesBombas.end()) {
					i--;
				}
				else {
					posicoesBombas[i] = resultado;
				}
			}

			/*preenche a matriz com as bombas e atualiza os adjacentes com a quantidade correspondente
			de bombas que está próxima deles*/
			int contador = 0;
			/*percorre a matriz*/
			for (int i = 0; i < linhas; i++) {
				for (int j = 0; j < colunas; j++ ) {
					/*percorre a lista de posicoes das bombas*/
					for (int b = 0; b < posicoesBombas.size(); b++) {
						/* se a posição da celula atual for a posição que corresponde há uma bomba*/
						if (contador == posicoesBombas[b]) {
							/* adiciona a celula selecionada o valor que corresponde as bombas*/
							matrizCelulas[i][j].setValor(-1);
							
							/*Soma um aos campos que são adjacentes a bomba selecionada*/
							std::vector<Celula> adjacentes = getAdjacentes(i,j);
							for (int a = 0; a < adjacentes.size(); a++) {
								Celula celulaAdjacente = adjacentes[a];
								celulaAdjacente.addValor(1);
								matrizCelulas[celulaAdjacente.getLinha()][celulaAdjacente.getColuna()] = celulaAdjacente;
								//lista de adjacentes
								//std::cout << "X: " + std::to_string(celulaAdjacente.getLinha()) + " Y: " + std::to_string(celulaAdjacente.getColuna()) << std::endl;
							}
						
						}
					}	
					contador++;
				}
			}
			
			
		}

		/*Retorna a matriz gerada*/
		Celula** getMatrizCelulas() {
			return matrizCelulas;
		}

		/*imprimi a matriz no console
			*método utilizado para debug*/
		void imprimirMatriz() {
			for (int i = 0; i < linhas; i++) {
				for (int j = 0; j < colunas; j++) {
					std::cout << matrizCelulas[i][j].getValor() << "\t";
				}
				std::cout << "\n";
			}
		}

		/* Define a quantidade de linhas da matriz*/
		void setLinhas(int l) {
			linhas = l;
		}

		/* Retorna a quantidade de linhas da matriz*/
		int getLinhas() {
			return linhas;
		}

		/*Define a quantidade de colunas da matriz*/
		void setColunas(int c) {
			colunas = c;
		}
		
		/*Retorna a quantidade de colunas da matriz*/
		int getColunas() {
			return colunas;
		}

		/*Retorna todas as células adjacentes a uma célula específica.*/
		std::vector<Celula> getAdjacentes(int i, int j) {
			std::vector<Celula> adjacentes(8);
			int position = 0;

			if (i > 0 && j < colunas - 1) {
				adjacentes[position] = matrizCelulas[i - 1][j + 1];
				position++;
			}
			if (i > 0) {
				adjacentes[position] = matrizCelulas[i - 1][j];
				position++;
			}
			if (i > 0 && j > 0) {
				adjacentes[position] = matrizCelulas[i - 1][j - 1];
				position++;
			}
			if (j > 0) {
				adjacentes[position] = matrizCelulas[i][j - 1];
				position++;		
			}
			if (i < linhas - 1 && j > 0) {
				adjacentes[position] = matrizCelulas[i + 1][j - 1];
				position++;
				
			}
			if (i < linhas - 1) {
				adjacentes[position] = matrizCelulas[i + 1][j];
				position++;
			}
			if (i < linhas - 1 && j < colunas - 1) {
				adjacentes[position] = matrizCelulas[i + 1][j + 1];
				position++;
			}
			if (j < colunas - 1) {
				adjacentes[position] = matrizCelulas[i][j + 1];
				position++;
			}
		
			/*caso a célula não tenha 8 adjacentes remove aqueles que não foram incializados*/
			int restantes = 8 - position;
			for (int r = 0; r < restantes; r++) {
				adjacentes.pop_back();
			}

			return adjacentes;
		}
		

		
};
