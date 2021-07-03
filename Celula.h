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
		//s� soma se n�o tiver bomba naquele lugar
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