/*Classe que representa cada quadrado do campo minado
	
	Definição dos Atributos:
	
	valor - é o valor da célula, onde 0 representa que não há bomba,
	-1 representa que a célula possui uma bomba, -2 representa que possui
	uma bandeira marcada pelo usuário indicando que há bomba naquela célula, 
	1 representa que há uma célula adjacente que possuiu uma bomba, 2 representa que há duas
	células adjacentes que possuem bombas e assim sucessivamente.

	estado - guarda a informação se a célula foi ativada ou não
*/
class Celula {
private:
	int valor = 0;
	bool estado = false;
public:
	Celula() {
		valor = 0;
		estado = false;
	}

	Celula(int v) {
		valor = v;
		estado = false;
	}

	void setValor(int v) {
		valor = v;
	}

	void addValor(int v) {
		//só soma se não tiver bomba naquele lugar
		if (valor != -1) {
			valor += v;
		}
	}

	int getValor() {
		return valor;
	}

	void isEstado(bool e) {
		estado = e;
	}

	bool getEstado() {
		return estado;
	}
};