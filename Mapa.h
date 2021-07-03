#pragma once
#include "Celula.h"
#include<iostream>
#include <ctime>
#include <vector>
/*Classe que representa o Mapa do campo Minado
	
	Definição dos Atributos:

	linhas - número de linhas do mapa
	colunas - número de colunas do mapa
	matrizCelulas - É o mapa em si, ele é formado por uma matriz de Células
*/
class Mapa {
	private:
		int linhas = 1;
		int colunas = 1;
		int qtdBombas = 5;
		Celula** matrizCelulas;
		
	public:
		
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

		~Mapa() {
			/* deleta a memória alocada */
			for (int i = 0; i < linhas; i++) {
				delete[] matrizCelulas[i];
			}
			delete[] matrizCelulas;
		}

		Celula** getMatrizCelulas() {
			return matrizCelulas;
		}

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
			
			
			for (int b = 0; b < posicoesBombas.size(); b++) {
				std::cout << posicoesBombas[b] << std::endl;
			}

			/*preenche a matriz com as bombas e soma 1 aos adjacentes*/
			int contador = 0;
			for (int i = 0; i < linhas; i++) {
				for (int j = 0; j < colunas; j++ ) {
					for (int b = 0; b < posicoesBombas.size(); b++) {
						if (contador == posicoesBombas[b]) {
							matrizCelulas[i][j].setValor(-1);
							/*Adjacentes das celulas*/
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

		void imprimirMatriz() {
			for (int i = 0; i < linhas; i++) {
				for (int j = 0; j < colunas; j++) {
					std::cout << matrizCelulas[i][j].getValor() << "\t";
				}
				std::cout << "\n";
			}
		}

		void setLinhas(int l) {
			linhas = l;
		}

		int getLinhas() {
			return linhas;
		}

		void setColunas(int c) {
			colunas = c;
		}

		int getColunas() {
			return colunas;
		}

		

		
};
