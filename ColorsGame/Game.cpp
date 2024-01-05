
#include <iostream>
#include <vector>
#include <string>
#include <random>

// Přiřazení názvů pro ansi kódy barev
#define RESET   "\033[0m"
#define CERVENA   "\033[31m"
#define MODRA    "\033[34m"
#define ZELENA  "\033[0;32m"
#define HNEDA   "\033[0;33m"
#define ORANZOVA  "\033[38;5;208m"
#define FIALOVA  "\033[0;35m"
#define BILA  "\e[0;37m"
#define RUZOVA    "\033[38;5;206m"



//Model hry - obsahuje plochu a všechny potřebné funkce pro správnou změnu čtverců
class Colors {


private:

    //Výčet všech možných barev ve hře jako enum
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


    //Číslo kterým se pomocí početní operace modulu vypočítá násladejucí barva při změně čtverce
    int modulo;


    //Generuje hrací pole jako dvourozměrný vector - argument n slouží k určení velikosti pole
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


    //Generuje náhodné číslo v rozmezí prametrů min - max
    int generator_cisel(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribution(min, max);
        return distribution(gen);
    }

    //Generuje index v poli od 0 až po maximální možný index
    int generovat_index() {
        return generator_cisel(0,velikost-1);
    }

    //Generuje náhodný pohyb - změna řádku/změna sloupce
    int generovat_pohyb(){
        return generator_cisel(0,1);
    }


public:

    //Constructor třídy Colors
    explicit Colors(int i, int  colorset){
        //Vytvoření hrací plochy
        plocha= inicializace(i);
        velikost=i;
        //Určení obtížnosti hry podle které se budou měnit bravy
        sadaBarev=colorset;


        //Přiřazení hodnoty modula na základě obtižnosti
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


    //Destruktor
    virtual ~Colors() = default;



    //Funkce vypíše obarvený čtverec na základě parametru col
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



    //Funkce vypíše do konzole celou hrací plochu
    void vypis_plochu() {

        //Výpis logiky měnění barev
        if(sadaBarev==1){
            std::cout<<'\n'<<MODRA<< "█ "<<RESET<< "->" <<CERVENA<< " █ " <<RESET<< "->"<<ZELENA<< " █ "<<RESET<< "->"<<ORANZOVA<< " █ "<<RESET;
        } else if(sadaBarev==2){
            std::cout<<'\n'<<MODRA<< "█ "<<RESET<< "->" <<CERVENA<< " █ " <<RESET<< "->"<<ZELENA<< " █ "<<RESET
                     << "->"<<ORANZOVA<< " █ "<<RESET<< "->"<<RUZOVA<< " █ "<<RESET<< "->"<<HNEDA<< " █ "<<RESET;
        } else {
            std::cout <<'\n'<< MODRA << "█ " << RESET << "->" << CERVENA << " █ " << RESET << "->" << ZELENA << " █ " << RESET
                      << "->" << ORANZOVA << " █ " << RESET << "->" << RUZOVA << " █ " << RESET << "->" << HNEDA
                      << " █ " << RESET << "->" << FIALOVA << " █ " << RESET << "->" << BILA << " █ " << RESET;
        }



        //Výpis plochy a jejího ohraničení
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

    //Změní barvu čtverce který přijde jako parametr na základě obtižnosti pomocí proměnné modulo
    void zmenit_barvu(barva &puvodni) {
        puvodni = static_cast<barva> ((static_cast<int>(puvodni) + 1) % modulo);
    }

    //Projde všechny bravy v daném řádku a změní je
    void rotace_radek(int radek) {
        for (int j = 0; j < velikost; ++j) {
            zmenit_barvu(plocha[radek][j]);
        }
    }

    //Projde všechny bravy v daném sloupci a změní je
    void rotace_sloupec(int sloupec) {
        for (int j = 0; j < velikost; ++j) {
            zmenit_barvu(plocha[j][sloupec]);
        }
    }


    //Projde postupně všechny 4 čtverce daného bloku určeného pomocí indexů v parametrech funkce
    void rotace_ctverec( int radek, int sloupec) {
        zmenit_barvu(plocha[radek][sloupec]);
        zmenit_barvu(plocha[radek + 1][sloupec]);
        zmenit_barvu(plocha[radek][sloupec + 1]);
        zmenit_barvu(plocha[radek + 1][sloupec + 1]);
    }



    //Zamíchá plochu 40 náhodnými pohyby s náhodnými čtverci
    void zamichat_plochu(){
        for(int i=0;i<40;i++){
            int pohyb=generovat_pohyb(); //Výběr náhodného pohybu
            if(pohyb==0){
                int sloupec=generovat_index(); //Výběr náhodného indexu
                rotace_sloupec(sloupec); //Rotace s náhodným sloupcem
            } else {
                int radek=generovat_index(); //Výběr náhodného indexu
                rotace_radek(radek);//Rotace s náhodným řádkem
            }
        }
    }



    //Vrací true pokud všechny čtverce na hrací ploše jsou modré a hráč tedy vyhrál
    bool zjistit_vyhru(){
        for(std::vector<barva> radek : plocha){ //Porchází postupně všechny řádky na ploše
            for(barva barva:radek){
                if(barva!=barva::modra){
                    return false; //Vrací false pokud je nalezen čtverec který není modrý
                }
            }
        }
        return true;
    }

    //Getter velikolsti
    [[nodiscard]] int getVelikost() const {
        return velikost;
    }

};


//Třída pro ovládání hry a hýbaní se čtverci na ploše
class GameHandler{
private:


    std::string userInput;
    bool win;
    bool end;


public:


    Colors colors;

    //Konstruktor který přiřadí do proměnné colors objekt který dostane jako parametr a vytiskně uvítací zprávu
    explicit GameHandler(Colors& colors) : colors(colors) {
        win= false;
        end= false;

        std::cout<<'\n'<<"Vitejte ve hre Colors - cílem hry je mít na ploše pouze modré bloky"<<'\n'<<'\n';
    };


    //Začne smyčku hry kde se opakují kroky: počkání na vstup od uživatele, změna plochy, kontrola výhry
    void game_loop(){
        colors.zamichat_plochu(); //Před zobrazení plochy plochu zamícha
        while (!win && !end) { //Smyčka opakující se dokud uživatel nevyhrál nebo neukončil hru
            colors.vypis_plochu(); //Zobrazí aktualní plochu
            std::string vyber_tahu;
            std::cout<<"Zvolte akci: 1 - změnit sloupec, 2 - změnit řádek, 3 - změnit čtverec "<<'\n';
            std::cin >> vyber_tahu; //Zapíše do proměnné uživatelem zvolenou akci
            click_handle(vyber_tahu); //Obslouží uživatelův vstup
            win=colors.zjistit_vyhru(); //Zkontroluje zda uživatel vyhrál
        }

        //Pokud uživatel vyhrál, ukončí hru
        if(win) {
            std::cout<<std::endl;
            colors.vypis_plochu();
            std::cout<<std::endl;
            std::cout << "Vyhrál/a jste!!!"<<std::endl;

        }

        //Pokud je uloženo že člověk chce ukončit hru, hru ukončí
        if(end){
            std::cout<<"Ukončeno"<<std::endl;
        }
    }

    //Rozhoduje o tom jaká akce bude provedena na základě parametru tah
    void click_handle(const std::string& tah){
        try{

            //Když se uživatel rozhold pro rotaci sloupce, zeptá na index sloupce který chce změnit
            if(tah=="1"){
                std::cout<<'\n'<<"Který sloupec chcete změnit?"<<'\n';
                std::string vstup;
                int sloupec;
                std::cin>>vstup;
                sloupec=std::stoi(vstup);

                //Pokud je index sloupce validní tak změní sloupec
                if(sloupec<colors.getVelikost()+1) {
                    colors.rotace_sloupec(sloupec-1);
                }

                //Když se uživatel rozhold pro rotaci řádku, zeptá na index řádku, který chce změnit
            }else if(tah=="2"){
                std::cout<<'\n'<<"Který řádek chcete změnit?"<<'\n';
                int radek;
                std::cin>>radek;

                //Pokud je index řádku validní tak změní řádek
                if(radek<colors.getVelikost()+1) {
                    colors.rotace_radek(radek-1);
                }

            //Pokud uživatel zovlil akci rotace bloku, zeptá se na index levého horního rohu bloku, který chce změnit
            }else if(tah=="3"){
                std::cout<<'\n'<<"Který čtverec chcete změnit? (napište indexy levého horního rohu)"<<'\n';
                int ctverec_radek;
                int ctverec_sloupec;
                std::cout<<"Index řádku: "<<'\n';
                std::cin>>ctverec_radek;
                std::cout<<"Index sloupce: "<<'\n';
                std::cin>>ctverec_sloupec;

                //Pokud se jedná o validní levý horní roh, změní tento blok
                if(ctverec_radek<colors.getVelikost()+1 && ctverec_sloupec<colors.getVelikost()+1 && (ctverec_radek-1)%2==0 && (ctverec_sloupec-1)%2==0) {
                    colors.rotace_ctverec(ctverec_radek-1,ctverec_sloupec-1);
                } else{
                    std::cout<<"Tento čtverec nelze měnit"<<'\n';
                }

                //Pokud místo tahu uživatel zvolil "q", program se ukončí
            }else if(tah=="q"){
                end= true;
                exit(0);

                //Pokud ani jedna z předchozích podmínek nebyla uskutečněnan, je uživateli sděleno že špatně zvolil akci
            }else{
                std::cout<<"Špatně zvolená akce"<<'\n';
            }

            //Zachycuje invalidní a moc dlouhé argumenty ve výběru indexů
        }catch (std::invalid_argument){
            std::cout<<"Špatný argument"<<'\n';
        }catch(std::out_of_range){
            std::cout<<"Moc dlouhý argument"<<'\n'<<'\n';
        }
    }



};


//Vytiskne nápovědu k programu
void napoveda(){
    std::cout << "Nápověda ke hře:" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout<< std::endl;
    std::cout << "Možnosti spuštění:" << std::endl;
    std::cout << "  --help     Vypísše nápovědu k tomuto programu" << std::endl;
    std::cout<< std::endl;
    std::cout << "  -b    Upraví obtížnost změnou barev: 1 - Lehká, 2 - Střední, 3 - Těžká"  << std::endl;
    std::cout<< std::endl;
    std::cout << "  -v    Upraví velikost herního pole: 4 -  4x4, 6 - 6x6, 8 - 8x8, 16 - 16x16"  << std::endl;
    std::cout<< std::endl;
    std::cout << "Bez specifikace se hra spustí na střední obtížnost s velikostí 4x4." << std::endl;
    std::cout<< std::endl;
    std::cout << "Pro ukočení zmáčkněte klávesu q a následně enter" << std::endl;
    std::cout<< std::endl;
    std::cout << "Pravidla hry:" << std::endl;
    std::cout << "Cílem hry je nastavit všechny čverce pole na modré" << std::endl;
    std::cout << "Hráč může měnit řádek, sloupec nebo kvadrant plochy" << std::endl;
    std::cout<< std::endl;
    std::cout << "Barvy se cyklicky mění na základě zvolené obtížnosti." << std::endl;

}