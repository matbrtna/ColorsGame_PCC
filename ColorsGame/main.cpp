#include <iostream>
#include <string>
#include <cstring>
#include "Game.cpp"



int main(int argc, char* argv[]) {

    // Kontrola jestli uživatel chce spustit nápovědu k programu
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        napoveda();
        return 0;
    }

    int gameSize = 4;
    int colorset=2;


    //kontrola existence zbylých argumentů
    try{
        for(int i=1; i<argc; i++) {

            //kontorla existence argumentu -v
            if ((std::string) argv[i] == "-v") {
                //načtení hodnoty po argumentu -v
                gameSize = atoi(argv[i + 1]);
                if (gameSize != 4 && gameSize != 6 && gameSize != 8 && gameSize != 16) {
                    std::cout << "Špatně zadaná velikost plochy - povoleno je pouze 4, 6, 8 nebo 16";
                    std::cout << std::endl;
                    return 0;
                }
            }

            //kontorla existence argumentu -v
            if ((std::string) argv[i] == "-b") {
                colorset = atoi(argv[i + 1]);

                //načtení hodnoty po argumentu -v
                if (colorset != 1 && colorset != 2 && colorset != 3) {
                    std::cout << "Špatně vybraná obtížnost - povoleny jsou jen obtížnosti 1, 2 a 3";
                    std::cout << std::endl;
                    return 0;
                }
            }
        }

    //Zachycení errorů při špatném zvolení argumentů
    }catch (std::invalid_argument){
        std::cout<<"Špatně zvolený argument";
    }catch(std::out_of_range){
        std::cout<<"Šaptně zvolený argument";
    }


    Colors barvy(gameSize,colorset); //Vytvoření nové insatnce hry se zvolenými parametry
    barvy.zamichat_plochu(); //Náhodné zamíchání plochy
    GameHandler hra=GameHandler(barvy); //Vtvoření nového controleru hry
    hra.game_loop(); //Spuštění herního cyklu
    return 0;
}
