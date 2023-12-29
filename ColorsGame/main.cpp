#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstring>

#define RESET   "\033[0m"
#define CERVENA   "\033[31m"
#define MODRA    "\033[34m"
#define ZELENA  "\033[0;32m"
#define HNEDA   "\033[0;33m"
#define ORANZOVA  "\033[38;5;208m"
#define FIALOVA  "\033[0;35m"
#define BILA  "\e[0;37m"
#define RUZOVA    "\033[38;5;206m"


class Colors {


private:

    enum class barva {
        modra,
        cervena,
        zelena,
        oranzova,
        ruzova,
        hneda,
        fialova,
        bila
    };

    std::vector<std::vector<barva>> plocha;

    int velikost;

    int sadaBarev;

    int modulo;

    static std::vector<std::vector<barva>> inicializace(int n) {
        std::vector<std::vector<barva>> tmp;
        for (int i = 0; i < n; ++i) {
            std::vector<barva> tt;
            for (int j = 0; j < n; ++j) {
                tt.push_back(static_cast<barva>(0));
            }
            tmp.push_back(tt);
        }
        return tmp;
    }

    int generator_cisel(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribution(min, max);
        return distribution(gen);
    }

    int generovat_index() {
        return generator_cisel(0,velikost-1);
    }

    int generovat_pohyb(){
        return generator_cisel(0,1);
    }


public:


    explicit Colors(int i, int  colorset){
        plocha= inicializace(i);
        velikost=i;
        sadaBarev=colorset;
        switch (sadaBarev) {
            default:
                modulo=4;
                break;
            case 2:
                modulo=6;
                break;
            case 3:
                modulo=8;
                break;
        }
    }

    virtual ~Colors() = default;

    static void vypis_barvu(barva col) {
        switch (col) {
            case barva::modra :
                std::cout<<MODRA<< "█ "<<RESET;
                break;
            case barva::cervena :
                std::cout <<CERVENA<< "█ "<<RESET;
                break;
            case barva::hneda :
                std::cout <<HNEDA<< "█ "<<RESET;
                break;
            case barva::oranzova :
                std::cout <<ORANZOVA<< "█ "<<RESET;
                break;
            case barva::zelena :
                std::cout <<ZELENA<< "█ "<<RESET;
                break;
            case barva::fialova:
                std::cout <<FIALOVA<< "█ "<<RESET;
                break;
            case barva::bila:
                std::cout <<BILA<< "█ "<<RESET;
                break;
            case barva::ruzova:
                std::cout <<RUZOVA<< "█ "<<RESET;
                break;
        }
    }




    void vypis_plochu() {
        if(sadaBarev==1){
            std::cout<<MODRA<< "█ "<<RESET<< "->" <<CERVENA<< " █ " <<RESET<< "->"<<ZELENA<< " █ "<<RESET<< "->"<<ORANZOVA<< " █ "<<RESET;
        } else if(sadaBarev==2){
            std::cout<<MODRA<< "█ "<<RESET<< "->" <<CERVENA<< " █ " <<RESET<< "->"<<ZELENA<< " █ "<<RESET
            << "->"<<ORANZOVA<< " █ "<<RESET<< "->"<<RUZOVA<< " █ "<<RESET<< "->"<<HNEDA<< " █ "<<RESET;
        } else {
            std::cout << MODRA << "█ " << RESET << "->" << CERVENA << " █ " << RESET << "->" << ZELENA << " █ " << RESET
            << "->" << ORANZOVA << " █ " << RESET << "->" << RUZOVA << " █ " << RESET << "->" << HNEDA
            << " █ " << RESET << "->" << FIALOVA << " █ " << RESET << "->" << BILA << " █ " << RESET;
        }
        std::cout<<std::endl<<std::endl;
        std::cout<<"     ";
        for (int k = 0; k < velikost; k++) {
            std::cout << k+1<<". ";
        }
        std::cout<<std::endl;
        std::cout<<"     ";
        for (int k = 0; k < velikost; k++) {
            std::cout << "-- ";
        }
        std::cout << std::endl;
        for (int i = 0; i < velikost; ++i) {
            std::cout<<i+1<<". ";
            std::cout<<"| ";
            for (int j = 0; j < velikost; ++j) {
                vypis_barvu(plocha[i][j]);
                std::cout << " ";
            }
            std::cout<<"|";
            std::cout << std::endl;
            if(i!= velikost-1){
            std::cout << std::endl;
            }
        }
        std::cout<<"     ";
        for (int k = 0; k < velikost; k++) {
            std::cout << "-- ";
        }
        std::cout << std::endl;
    }

    void zmenit_barvu(barva &puvodni) {
        puvodni = static_cast<barva> ((static_cast<int>(puvodni) + 1) % modulo);
    }

    void rotace_radek(int radek) {
        for (int j = 0; j < velikost; ++j) {
            zmenit_barvu(plocha[radek][j]);
        }
    }

    void rotace_sloupec(int sloupec) {
        for (int j = 0; j < velikost; ++j) {
            zmenit_barvu(plocha[j][sloupec]);
        }
    }

    void rotace_ctverec( int radek, int sloupec) {
        zmenit_barvu(plocha[radek][sloupec]);
        zmenit_barvu(plocha[radek + 1][sloupec]);
        zmenit_barvu(plocha[radek][sloupec + 1]);
        zmenit_barvu(plocha[radek + 1][sloupec + 1]);
    }

    void zamichat_plochu(){
        for(int i=0;i<40;i++){
            int pohyb=generovat_pohyb();
            if(pohyb==0){
                int sloupec=generovat_index();
                rotace_sloupec(sloupec);
            } else {
                int radek=generovat_index();
                rotace_radek(radek);
            }
        }
    }

    bool zjistit_vyhru(){
        for(std::vector<barva> radek : plocha){
            for(barva barva:radek){
                if(barva!=barva::modra){
                    return false;
                }
            }
        }
        return true;
    }

    [[nodiscard]] int getVelikost() const {
        return velikost;
    }

};

class GameHandler{
private:


    std::string userInput;
    bool win;
    bool end;

public:

    Colors colors;
    explicit GameHandler(Colors& colors) : colors(colors) {
        win= false;
        end= false;

        std::cout<<'\n'<<"Vitejte ve hre Colors - cílem hry je mít na ploše pouze modré bloky"<<'\n'<<'\n';
    };

    void game_loop(){
        colors.zamichat_plochu();
        while (!win && !end) {
            colors.vypis_plochu();
            std::string vyber_tahu;
            std::cout<<"Zvolte akci: 1 - změnit sloupec, 2 - změnit řádek, 3 - změnit čtverec "<<'\n';
            std::cin >> vyber_tahu;
            click_handle(vyber_tahu);
            win=colors.zjistit_vyhru();
        }
        if(win) {
            std::cout<<std::endl;
            colors.vypis_plochu();
            std::cout<<std::endl;
            std::cout << "Vyhrál/a jste!!!"<<std::endl;

        }
        if(end){
            std::cout<<"Ukončeno"<<std::endl;
        }
    }

    void click_handle(std::string tah){
        if(tah=="1"){
            std::cout<<"Který sloupec chcete změnit?"<<'\n';
            int sloupec;
            std::cin>>sloupec;
            if(sloupec<colors.getVelikost()+1) {
                colors.rotace_sloupec(sloupec-1);
            }
        }else if(tah=="2"){
            std::cout<<"Který řádek chcete změnit?"<<'\n';
            int radek;
            std::cin>>radek;
            if(radek<colors.getVelikost()+1) {
                colors.rotace_radek(radek-1);
            }
        }else if(tah=="3"){
            std::cout<<"Který čtverec chcete změnit? (napište indexy levého horního rohu)"<<'\n';
            int ctverec_radek;
            int ctverec_sloupec;
            std::cout<<"Index řádku: "<<'\n';
            std::cin>>ctverec_radek;
            std::cout<<"Index sloupceš: "<<'\n';
            std::cin>>ctverec_sloupec;
            if(ctverec_radek<colors.getVelikost()+1 && ctverec_sloupec<colors.getVelikost()+1 && (ctverec_radek-1)%2==0 && (ctverec_sloupec-1)%2==0) {
                colors.rotace_ctverec(ctverec_radek-1,ctverec_sloupec-1);
            } else{
                std::cout<<"Tento čtverec nelze měnit"<<'\n';
            }
//            std::cout<<"Který kvadrant chcete změnit?"<<'\n';
//            int kvadrant;
//            std::cin>>kvadrant;
//            switch (kvadrant) {
//                case 1:
//                    colors.rotace_ctverec(0,colors.getVelikost()/2);
//                    break;
//                case 2:
//                    colors.rotace_ctverec(0,0);
//                    break;
//                case 3:
//                    colors.rotace_ctverec(colors.getVelikost(),0);
//                    break;
//                case 4:
//                    colors.rotace_ctverec(colors.getVelikost(),colors.getVelikost());
//                    break;
//                default:
//                    std::cout<<"Špatně vybraný kvadrant"<<std::endl;
//            }
        }else if(tah=="q"){
            end= true;
            exit(0);
        }else{
            std::cout<<"Špatně zvolená akce"<<'\n';
        }
    }



};

void napoveda(){
    std::cout << "Nápověda ke hře:" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout<< std::endl;
    std::cout << "Možnosti spuštění:" << std::endl;
    std::cout << "  --help     Vypísše nápovědu k tomuto programu" << std::endl;
    std::cout<< std::endl;
    std::cout << "Pro ukočení zmáčkněte klávesu q a následně enter" << std::endl;
    std::cout<< std::endl;
    std::cout << "Pravidla hry:" << std::endl;
    std::cout << "Cílem hry je nastavit všechny čverce pole na modré" << std::endl;
    std::cout << "Hráč může měnit řádek, sloupec nebo kvadrant plochy" << std::endl;
    std::cout<< std::endl;
    std::cout << "Barvy se cyklicky mění v pořadí:" << std::endl;
    std::cout << "Modrá -> Červená -> Hnědá -> Oranžová -> Zelená -> Modrá" << std::endl;

}


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
