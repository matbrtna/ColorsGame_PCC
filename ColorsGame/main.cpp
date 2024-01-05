#include <iostream>
#include <string>
#include <cstring>
#include "Game.cpp"



int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        napoveda();
        return 0;
    }

    int gameSize = 4;
    int colorset=2;

    for(int i=1; i<argc; i++) {
        if ((std::string) argv[i] == "-v") {
            gameSize = atoi(argv[i + 1]);
            if (gameSize != 4 && gameSize != 6 && gameSize != 8 && gameSize != 16) {
                std::cout << "Špatně zadaná velikost plochy - povoleno je pouze 4, 6, 8 nebo 16";
                std::cout<<std::endl;
                return 0;
            }
        }
        if ((std::string) argv[i] == "-b") {
            colorset = atoi(argv[i + 1]);
            if (colorset != 1 && colorset!= 2 && colorset!= 3) {
                std::cout << "Špatně vybraná obtížnost - povoleny jsou jen obtížnosti 1, 2 a 3";
                std::cout<<std::endl;
                return 0;
            }
        }
    }
    Colors barvy(gameSize,colorset);
    barvy.zamichat_plochu();
    GameHandler hra=GameHandler(barvy);
    hra.game_loop();
    return 0;
}
