#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstring>

class Colors {


private:

    enum class barva {
        modra,
        cervena,
        hneda,
        oranzova,
        zelena,
    };

    std::vector<std::vector<barva>> plocha;

    int velikost;

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


    explicit Colors(int n){
        plocha= inicializace(n);
        velikost=n;
    }

    virtual ~Colors() = default;

    static void vypis_barvu(barva col) {
        switch (col) {
            case barva::modra :
                std::cout << "MM";
                break;
            case barva::cervena :
                std::cout << "CC";
                break;
            case barva::hneda :
                std::cout << "HH";
                break;
            case barva::oranzova :
                std::cout << "OO";
                break;
            case barva::zelena :
                std::cout << "ZZ";
                break;
        }
    }




    void vypis_plochu() {
        std::cout<<"MM -> CC -> HH -> OO -> ZZ -> MM"<<"\n";
        for (int k = 0; k < velikost+1; k++) {
            std::cout << "-- ";
        }
        std::cout << std::endl;
        for (int i = 0; i < velikost; ++i) {
            std::cout<<"| ";
            for (int j = 0; j < velikost; ++j) {
                vypis_barvu(plocha[i][j]);
                std::cout << " ";
            }
            std::cout<<"|";

            std::cout << std::endl;
        }
        for (int k = 0; k < velikost+1; k++) {
            std::cout << "-- ";
        }
        std::cout << std::endl;
    }

    void zmenit_barvu(barva &puvodni) {
        puvodni = static_cast<barva> ((static_cast<int>(puvodni) + 1) % 5);
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
        std::cout<<"Vitejte ve hre Colors - cílem hry je mít na ploše pouze modré bloky"<<'\n';
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
            std::cout << "Vyhrál/a jste"<<std::endl;
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

    std::string userInput;
    Colors barvy(4);
    barvy.zamichat_plochu();
    GameHandler hra=GameHandler(barvy);
    hra.game_loop();
    return 0;
}
