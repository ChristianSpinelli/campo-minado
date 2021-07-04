/*Classe que representa cada quadrado do campo minado
	
	Defini��o dos Atributos:
	
	valor - � o valor da c�lula, onde 0 representa que n�o h� bomba,
	-1 representa que a c�lula possui uma bomba, -2 representa que possui
	uma bandeira marcada pelo usu�rio indicando que h� bomba naquela c�lula, 
	1 representa que h� uma c�lula adjacente que possuiu uma bomba, 2 representa que h� duas
	c�lulas adjacentes que possuem bombas e assim sucessivamente.

	estado - guarda a informa��o se a c�lula foi ativada ou n�o
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

	/*Adiciona um n�mero inteiro ao campo valor*/
	void addValor(int v) {
		//s� soma se n�o tiver bomba naquele lugar
		if (valor != -1) {
			valor += v;
		}
	}
	
	/*Retorna o valor */
	int getValor() {
		return valor;
	}

	/* Define o estado da c�lula*/
	void isEstado(bool e) {
		estado = e;
	}

	/* Retorna o estado*/
	bool getEstado() {
		return estado;
	}

	/* Define se a c�lula est� com a bandeira*/
	void isBandeira(bool b) {
		bandeira = b;
	}

	/* Retorna se a c�lula est� com a bandeira*/
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