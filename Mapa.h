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
	matrizCelulas - É o mapa em si, ele é formado por uma matriz de Células
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
							if (i > 0 && j < colunas -1) {
								matrizCelulas[i - 1][j + 1].addValor(1);
							}
							if (i > 0) {
								matrizCelulas[i - 1][j].addValor(1);
							}
							if (i > 0 && j > 0) {
								matrizCelulas[i - 1][j - 1].addValor(1);
							}
							if (j > 0) {
								matrizCelulas[i][j - 1].addValor(1);
							}
							if(i < linhas -1 && j > 0){
								matrizCelulas[i + 1][j - 1].addValor(1);
							}
							if (i < linhas - 1) {
								matrizCelulas[i + 1][j].addValor(1);
							}
							if (i < linhas - 1 && j < colunas - 1) {
								matrizCelulas[i + 1][j + 1].addValor(1);
							}
							if (j < colunas - 1) {
								matrizCelulas[i][j + 1].addValor(1);
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

		

		
};
