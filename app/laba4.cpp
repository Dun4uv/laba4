#include <vector>
#include <iostream>
#include <SFML/Audio.hpp>


#include "io_utils/io_utils.h"
#include "Knight/Knight.h"
#include "Battle/Battle.h"
#include "GameLoop/GameLoop.h"
#include "print_header/print_header.h"

int main() {
    io_setup();
    print_header(4);
    sf::Music music;
    if (!music.openFromFile("Assets/Banger.flac")) {
        std::cerr << "Музыки не будет, оркестр заболел!\n";
    }
    else {
        music.setLooping(true);
        music.setVolume(100);
        music.play();
    }

    std::vector<Knight> knights;
    runGameLoop(knights);
   
    return 0;
}
