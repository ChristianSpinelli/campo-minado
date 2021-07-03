#include <SFML/Graphics.hpp>
#include <iostream>
#include "Mapa.h"

int main()
{
    /*Configurações do jogo*/
    int linhas = 40;
    int colunas = 40;
    int qtdBombas = 99;
    int qtdCelulas = linhas * colunas;
    int celula_tamanho= 13;
 

    /*Gerando o Mapa do Jogo*/
    Mapa mapa = Mapa(linhas, colunas, qtdBombas);
    mapa.gerarMatriz();
    Celula** matriz = mapa.getMatrizCelulas();
  
    /*janela do jogo*/
    sf::RenderWindow window(sf::VideoMode(linhas * celula_tamanho, colunas*celula_tamanho, 32U),"Campo Minado");
    
    /*Carrega as imagens*/
    sf::Image imgCelula, imgCelulaRevelada, imgBandeira, imgBomba;
    
    imgCelula.loadFromFile("Assets/celula.png");
    imgCelulaRevelada.loadFromFile("Assets/celula-revelada.png");
    imgBandeira.loadFromFile("Assets/bandeira.png");
    imgBomba.loadFromFile("Assets/bomba.png");
    
    /*Cria as texturas*/
    sf::Texture texCelula, texCelulaRevelada, texBandeira, texBomba;
    std::vector<sf::Color> textColors(8);
    textColors[0] = sf::Color(0, 0, 255, 255);
    textColors[1] = sf::Color(0, 121, 0, 255);
    textColors[2] = sf::Color(253, 6, 6, 255);
    textColors[3] = sf::Color(0, 0, 127, 255);
    textColors[4] = sf::Color(122, 4, 4, 255);
    textColors[5] = sf::Color(0, 123, 123, 255);
    textColors[6] = sf::Color(0, 0, 0, 255);
    textColors[7] = sf::Color(85, 85, 85, 255);

    texCelula.loadFromImage(imgCelula);
    texCelulaRevelada.loadFromImage(imgCelulaRevelada);
    texBomba.loadFromImage(imgBomba);
    texBandeira.loadFromImage(imgBandeira);


    /*Criando o mapa na tela*/
    std::vector<sf::Sprite> sprites(qtdCelulas);
    int contador = 0;
    float position_linha = 0.0;
    float position_coluna = 0.0;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            sf::Sprite sprite;

            /*Cria o sprite e define a posicao na tela*/
            sprite.setTexture(texCelula);
            sprite.setPosition(position_linha, position_coluna);

            sprites[contador] = sprite;
            contador++;
            position_coluna+= celula_tamanho;
        }
        position_linha+= celula_tamanho;
        position_coluna = 0;
    }
   

    /*Lista de textos que irão aparecer na tela*/
    sf::Font font;
    font.loadFromFile("Assets/unispace bd.ttf");
    std::vector<sf::Text> texts(qtdCelulas);
    int textPosition = 0;
    
    while (window.isOpen()) {
        sf::Event event;
        sf::Color color(192, 192, 192, 0);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //pega a posição do click do mouse
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                Celula celulaClicada;
                sf::Sprite sprite;
                /*percorre os sprites*/
                for (int i = 0; i < sprites.size(); i++) {
                    sprite = sprites[i];
                    sf::FloatRect bounds = sprite.getGlobalBounds();
                    if (bounds.contains(mouse)) {
                        /*pega linha e coluna da celula que foi clicada e seleciona ela*/
                        int linha = (int)sprite.getPosition().x / celula_tamanho;
                        int coluna = (int)sprite.getPosition().y / celula_tamanho;
                        celulaClicada = matriz[linha][coluna];
                        /*se ela não foi revelada, revela e mostra o resultado*/
                        if (!celulaClicada.getEstado()) {
                            celulaClicada.isEstado(true);
                            matriz[linha][coluna] = celulaClicada;
                            if (celulaClicada.getValor() >= 0) {
                                sprite.setTexture(texCelulaRevelada);
                                if (celulaClicada.getValor() > 0) {
                                    sf::Text text;
                                    text.setString(std::to_string(celulaClicada.getValor()));
                                    text.setFont(font);
                                    text.setPosition(sprite.getPosition());
                                    text.setFillColor(textColors[celulaClicada.getValor() - 1]);
                                    text.setCharacterSize(10);

                                    texts[textPosition] = text;
                                    textPosition++;
                                }
                                
                            }
                            else {
                                sprite.setTexture(texBomba);
                            }
                            sprites[i] = sprite;
                        }
                        break;
                    }
                }
                
            }   
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                //pega a posição do click do mouse
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                Celula celulaClicada;
                sf::Sprite sprite;
                /*percorre os sprites*/
                for (int i = 0; i < sprites.size(); i++) {
                    sprite = sprites[i];
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
                            }
                            else {
                                sprite.setTexture(texCelula);
                                celulaClicada.isBandeira(false);
                            }
                            matriz[linha][coluna] = celulaClicada;
                            
                            sprites[i] = sprite;
                        }
                        break;
                    }
                }
            }
            
        }

        window.clear(color);
        //Desenha os sprites na tela
        for (sf::Sprite sprite : sprites) {
            window.draw(sprite);
        }
        //Desenha os textos das celulas na tela
        for (sf::Text text : texts) {
            window.draw(text);
        }
        window.display();
    }


    return 0;
}