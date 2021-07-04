#include <SFML/Graphics.hpp>
#include <iostream>
#include "Mapa.h"
#include <Windows.h>    

int main()
{
    /*Configurações do jogo*/
    int linhas = 30;
    int colunas = 30;
    int qtdBombas = 99;
    int qtdCelulas = linhas * colunas;
    int celula_tamanho= 13;
    int camposVazios = qtdCelulas - qtdBombas;
    bool derrota = false;
    bool vitoria = false;
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    
    /*Carrega as imagens*/
    sf::Image imgCelula, imgCelulaRevelada, imgBandeira, imgBomba;
    imgCelula.loadFromFile("Assets/celula.png");
    imgCelulaRevelada.loadFromFile("Assets/celula-revelada.png");
    imgBandeira.loadFromFile("Assets/bandeira.png");
    imgBomba.loadFromFile("Assets/bomba.png");

    /*Cria as texturas*/
    sf::Texture texCelula, texCelulaRevelada, texBandeira, texBomba;
    texCelula.loadFromImage(imgCelula);
    texCelulaRevelada.loadFromImage(imgCelulaRevelada);
    texBomba.loadFromImage(imgBomba);
    texBandeira.loadFromImage(imgBandeira);

    /*Criando o mapa na tela*/
    sf::Sprite** sprites;
    /* Aloca memória para a matriz */
    sprites = new sf::Sprite*[linhas];
    for (int i = 0; i < linhas; i++) {
        sprites[i] = new sf::Sprite[colunas];
    }

    int contador = 0;
    float position_linha = 0.0;
    float position_coluna = 0.0;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            sf::Sprite sprite;

            /*Cria o sprite e define a posicao na tela*/
            sprite.setTexture(texCelula);
            sprite.setOrigin(0,-100);
            sprite.setPosition(position_linha, position_coluna);

            sprites[i][j] = sprite;
            contador++;
            position_coluna += celula_tamanho;
        }
        position_linha += celula_tamanho;
        position_coluna = 0;
    }

    //incializa lista de textos
    std::vector<sf::Text> texts(qtdCelulas);
    int textPosition = 0;

    /*Gerando o Mapa do Jogo*/
    Mapa mapa = Mapa(linhas, colunas, qtdBombas);
    mapa.gerarMatriz();
    Celula** matriz = mapa.getMatrizCelulas();
   
  
    /*janela do jogo*/
    sf::RenderWindow window(sf::VideoMode(linhas * celula_tamanho, (colunas*celula_tamanho)+100, 32U),"Campo Minado");

    /*Define as cores de cada número do campo minado
    de 0-7, pois uma celula pode ter no máximo 8 adjacentes*/
    std::vector<sf::Color> textColors(8);
    textColors[0] = sf::Color(0, 0, 255, 255);//Azul
    textColors[1] = sf::Color(0, 121, 0, 255);//Verde
    textColors[2] = sf::Color(253, 6, 6, 255);//Vermelho
    textColors[3] = sf::Color(0, 0, 127, 255);//Azul Escuro   
    textColors[4] = sf::Color(122, 4, 4, 255);//Vinho
    textColors[5] = sf::Color(0, 123, 123, 255);//Azul Turquesa
    textColors[6] = sf::Color(0, 0, 0, 255);//Preto
    textColors[7] = sf::Color(85, 85, 85, 255);//Cinza
   
    /*Lista de textos que irão aparecer na tela e definição da font*/
    sf::Font font;
    font.loadFromFile("Assets/unispace bd.ttf");

    //texto de derrota
    sf::Text txtDerrota;
    txtDerrota.setString("Você Perdeu!");
    txtDerrota.setFont(font);
    txtDerrota.setPosition((linhas * celula_tamanho)/3, ((colunas * celula_tamanho)+100)/2);
    txtDerrota.setFillColor(textColors[2]);
    txtDerrota.setCharacterSize(25);

    //texto de derrota
    sf::Text txtVitoria;
    txtVitoria.setString("Você Venceu!");
    txtVitoria.setFont(font);
    txtVitoria.setPosition((linhas * celula_tamanho) / 3, ((colunas * celula_tamanho) + 100) / 2);
    txtVitoria.setFillColor(textColors[1]);
    txtVitoria.setCharacterSize(25);

    
    while (window.isOpen()) {
        /*Texto de quantidade de bombas*/
        sf::Text txtQtdBombas;
        txtQtdBombas.setString(std::to_string(qtdBombas));
        txtQtdBombas.setFont(font);
        txtQtdBombas.setPosition((linhas * celula_tamanho)/2, 50);
        txtQtdBombas.setFillColor(textColors[2]);
        txtQtdBombas.setCharacterSize(25);


        sf::Event event;
        //cor da janela
        sf::Color color(192, 192, 192, 0);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !derrota && !vitoria) {             
                //pega a posição do click do mouse
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                Celula celulaClicada;
                sf::Sprite sprite;

                /*percorre os sprites*/
                for (int i = 0; i < linhas; i++) {
                    for (int j = 0; j < colunas; j++) {
                        sprite = sprites[i][j];
                        sf::FloatRect bounds = sprite.getGlobalBounds();
                        if (bounds.contains(mouse)) {
                            celulaClicada = matriz[i][j];
                            /*se ela não foi revelada, revela e mostra o resultado*/
                            if (!celulaClicada.getEstado() && !celulaClicada.getBandeira()) {
                                celulaClicada.isEstado(true);
                                matriz[i][j] = celulaClicada;
                                if (celulaClicada.getValor() >= 0) {
                                    sprite.setTexture(texCelulaRevelada);
                                    /*Se o valor for maior que 0 adiciona um texto no campo para mostra-lo
                                    com a cor selecionada de acordo com a lista de cores.*/
                                    if (celulaClicada.getValor() > 0) {
                                        sf::Text text;
                                        text.setString(std::to_string(celulaClicada.getValor()));
                                        text.setFont(font);
                                        text.setOrigin(sprite.getOrigin());
                                        text.setPosition(sprite.getPosition());
                                        int colorPosition = celulaClicada.getValor() - 1;
                                        text.setFillColor(textColors[colorPosition]);
                                        text.setCharacterSize(10);

                                        texts[textPosition] = text;
                                        textPosition++;
                                    }


                                    camposVazios--;
                                    if (camposVazios == 0) {
                                        vitoria = true;
                                    }
                                }
                                

                                else {
                                    sprite.setTexture(texBomba);
                                    qtdBombas--;
                                    derrota = true;
                                }
                                sprites[i][j] = sprite;
                            }
                            break;
                        }
                    }
                    
                }
            }   
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !derrota && !vitoria) {
                //pega a posição do click do mouse
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                Celula celulaClicada;
                sf::Sprite sprite;
                /*percorre os sprites*/
                for (int i = 0; i < linhas; i++) {
                    for (int j = 0; j < colunas; j++) {
                        sprite = sprites[i][j];
                        sf::FloatRect bounds = sprite.getGlobalBounds();
                        if (bounds.contains(mouse)) {
                            /*pega linha e coluna da celula que foi clicada e seleciona ela*/
                            int linha = (int)sprite.getPosition().x / celula_tamanho;
                            int coluna = (int)sprite.getPosition().y / celula_tamanho;
                            celulaClicada = matriz[linha][coluna];

                            /*se ela não foi revelada, coloca a bandeira*/
                            if (!celulaClicada.getEstado()) {

                                if (!celulaClicada.getBandeira()) {
                                    sprite.setTexture(texBandeira);
                                    celulaClicada.isBandeira(true);
                                    qtdBombas--;
                                }
                                else {
                                    sprite.setTexture(texCelula);
                                    celulaClicada.isBandeira(false);
                                    qtdBombas++;
                                }
                                matriz[linha][coluna] = celulaClicada;

                                sprites[i][j] = sprite;
                            }
                            break;
                        }
                    }
                }
            }
            
        }

        window.clear(color);
        //Desenha os sprites na tela
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                window.draw(sprites[i][j]);
            }
        }
       
        //Desenha os textos das celulas na tela
        for (sf::Text text : texts) {
            window.draw(text);
        }

        if (derrota) {
            window.draw(txtDerrota);
        }

        if (vitoria) {
            window.draw(txtVitoria);
        }

        window.draw(txtQtdBombas);
        window.display();
    }


    return 0;
}

