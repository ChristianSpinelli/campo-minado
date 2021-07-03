#include <SFML/Graphics.hpp>
#include <iostream>
#include "Mapa.h"

int main()
{
    Mapa mapa = Mapa(15, 20, 99);
    mapa.gerarMatriz();

    return 0;
}