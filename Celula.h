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
	int linha = 0;
	int coluna = 0;
	bool estado = false;
	bool bandeira = false;
public:
	/*Construtor default da classe celula*/
	Celula() {
		valor = 0;
		estado = false;
		bandeira = false;
	}
	
	/*Construtor da classe celula passando o valor*/
	Celula(int v) {
		valor = v;
		estado = false;
		bandeira = false;
	}

	/* Define o valor da celula*/
	void setValor(int v) {
		valor = v;
	}

	/*Adiciona um número inteiro ao campo valor*/
	void addValor(int v) {
		//só soma se não tiver bomba naquele lugar
		if (valor != -1) {
			valor += v;
		}
	}
	
	/*Retorna o valor */
	int getValor() {
		return valor;
	}

	/* Define o estado da célula*/
	void isEstado(bool e) {
		estado = e;
	}

	/* Retorna o estado*/
	bool getEstado() {
		return estado;
	}

	/* Define se a célula está com a bandeira*/
	void isBandeira(bool b) {
		bandeira = b;
	}

	/* Retorna se a célula está com a bandeira*/
	bool getBandeira() {
		return bandeira;
	}

	void setLinha(int l) {
		linha = l;
	}

	int getLinha() {
		return linha;
	}

	void setColuna(int c) {
		coluna = c;
	}

	int getColuna() {
		return coluna;
	}
};