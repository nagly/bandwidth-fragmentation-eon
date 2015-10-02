#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <math.h>
#include "scenariusze.hpp"
#include "funkcje.hpp"
#include "Kolejka.hpp"
#include "krawedzie.hpp"
#include "sciezki.hpp"
#include "drzewa.hpp"
#include "modulacje.hpp"

using namespace std;

unsigned LiczbaW, LiczbaK, LiczbaUni, LiczbaMulti, LiczbaScenariuszy;
unsigned LiczbaSciezek;
unsigned LiczbaDrzew;
string NET, DEM, DMC, PAT, TREE, SPEC;
string PAR = "mod.par";


int main()
{
    CScenariusze Scenariusze;
    Scenariusze.Wypelnij();

    CModulacje Modulacje;
    Modulacje.Uzupelnij(PAR);

    fstream fWyniki;
    fWyniki.open("wyniki20.txt", ios::in | ios::out);
    fWyniki << "Kod\tMapa\tUnicast\tMulticast\tLiczba_Sciezek\tLiczba_Drzew\tNFR\tCzas[ms]\n";
    unsigned licznik = 1;
    for (unsigned liczScen = 0; liczScen < LiczbaScenariuszy; liczScen++){
    for (unsigned lol = 0; lol < 10; lol++){
    clock_t start = clock();
    Scenariusze.PodajPliki(liczScen);

    ParametryGrafu(NET, DEM, DMC);

    CSciezki* Sciezki = new CSciezki(LiczbaSciezek);
    Sciezki->WladujSciezki(PAT);

    CDrzewa* Drzewa = new CDrzewa(LiczbaDrzew, DMC);
    Drzewa->WladujDrzewa(TREE, SPEC);

    CKrawedzie* Krawedzie = new CKrawedzie;
    Krawedzie->WladujKrawedzie(NET);

    CKolejka* Kolejka = new CKolejka;
    Kolejka->TabUnicast();
    Kolejka->FirstFitUM();


//-------------------------------------POOBRANIE ODPOWIEDNIEJ SCIEZKI, WPISANIE INDEKSOW KRAWEDZI I ILOSCI SLOTOW DLA KAZDEGO ZADANIA--------
    for (int i = 0; i<Kolejka->Wielkosc(); i++){
        unsigned IndeksZadania = Kolejka->IndeksZadania(i);

        if (Kolejka->Typ(i) == "U"){
            int SumaDlugosci = 0;
            unsigned IndeksSciezki = Kolejka->ObliczWierszSciezki(IndeksZadania, i);
            for (unsigned j = 0; j<LiczbaK; j++){ //uzupelnienie wektora krawedzi w strukturze kolejki zadan
                if (Sciezki->Pobierz(IndeksSciezki, j) == 1){
                    Kolejka->UzupelnijKrawedzie(i, j);
                    SumaDlugosci += Krawedzie->Dlugosc(j);
                }
            }
            Kolejka->UzupelnijSloty(i, Modulacje.IleSlotow(Kolejka->Przepust(i), SumaDlugosci)); //obliczenie ilosci slotow i wpisanie do struktury
        }
        else{
            unsigned IndeksDrzewa = Kolejka->ObliczWierszDrzewa(IndeksZadania, i);
            for (unsigned k = 0; k<LiczbaK; k++){
                if (Drzewa->Pobierz(IndeksDrzewa, k) == 1){
                    Kolejka->UzupelnijKrawedzie(i, k);
                }
            }
            Kolejka->UzupelnijSloty(i, Drzewa->Pobierz(IndeksDrzewa, LiczbaK));
        }
    }
//---------------------------ALOKACJA ZADAN---------
    for (int j = 0; j<Kolejka->Wielkosc(); j++){
        Krawedzie->Ulokuj(Kolejka->KrawedzieSciezki(j), Kolejka->Sloty(j));
    }
//---------------------------------------------------
    Krawedzie->ObliczFR(2);

    cout << "[" << licznik << "] " << Scenariusze.KodScenariusza(liczScen) <<"\t";
    double nfrCurrent = Krawedzie->NFR();
    //KOPIA
    //CKolejka KolejkaKopia( * Kolejka );

                    double Temper = Krawedzie->NFR()*2500;
                    int imax = 14000;
                    int powtorzeniaMax = 50;
                    double skok = 0.999;
                    int powtorzenia = 0;
                    bool bSwap = true;
                    SZadania sZadBufor;

                    for (int i = 0; i<imax; i++){
                        Krawedzie->WyczyscSloty();
                        unsigned zakres = LiczbaUni+LiczbaMulti;
                        unsigned d1 = rand() % zakres;
                        unsigned d2;
                        if (Kolejka->Typ(d1) == "U")
                            d2 = rand() % LiczbaUni + LiczbaMulti;
                        else
                            d2 = rand() % LiczbaMulti;

                        if (powtorzenia < powtorzeniaMax){
                            Kolejka->Swap(d1, d2);
                            //alokacja
                            for (int j = 0; j<Kolejka->Wielkosc(); j++){
                                Krawedzie->Ulokuj(Kolejka->KrawedzieSciezki(j), Kolejka->Sloty(j));
                            }
                            Krawedzie->ObliczFR(2);
                            bSwap = true;
                        }
                        else{
                            sZadBufor = Kolejka->Bufor(d1);
                            Kolejka->WyczyscKrawedzieSciezki2(d1);
                            Kolejka->ZmienSciezke(d1);
                            bSwap = false;
                            unsigned IndeksZadania = Kolejka->IndeksZadania(d1);

                            if (Kolejka->Typ(d1) == "U"){
                                int SumaDlugosci = 0;
                                unsigned IndeksSciezki = Kolejka->ObliczWierszSciezki(IndeksZadania, d1);
                                for (unsigned j = 0; j<LiczbaK; j++){ //uzupelnienie wektora krawedzi w strukturze kolejki zadan
                                    if (Sciezki->Pobierz(IndeksSciezki, j) == 1){
                                        Kolejka->UzupelnijKrawedzie(d1, j);
                                        SumaDlugosci += Krawedzie->Dlugosc(j);
                                    }
                                }
                                Kolejka->UzupelnijSloty(d1, Modulacje.IleSlotow(Kolejka->Przepust(d1), SumaDlugosci)); //obliczenie ilosci slotow i wpisanie do struktury
                            }
                            else{
                                unsigned IndeksDrzewa = Kolejka->ObliczWierszDrzewa(IndeksZadania, d1);
                                for (unsigned k = 0; k<LiczbaK; k++){
                                    if (Drzewa->Pobierz(IndeksDrzewa, k) == 1){
                                        Kolejka->UzupelnijKrawedzie(d1, k);
                                    }
                                }
                                Kolejka->UzupelnijSloty(d1, Drzewa->Pobierz(IndeksDrzewa, LiczbaK));
                            }
                            for (int j = 0; j<Kolejka->Wielkosc(); j++){
                                Krawedzie->Ulokuj(Kolejka->KrawedzieSciezki(j), Kolejka->Sloty(j));
                            }
                            Krawedzie->ObliczFR(2);
                        }

                        double nfrBufor = Krawedzie->NFR();
                        if (nfrBufor < nfrCurrent){
                            nfrCurrent = nfrBufor;
                            powtorzenia = 0;
                        }
                        else{
                            double x = 1.0 * rand() / (RAND_MAX - 1);
                            if (x < exp(-2000*(nfrBufor-nfrCurrent)/Temper)){
                                nfrCurrent = nfrBufor;
                                powtorzenia = 0;
                            }
                            else{
                                if (bSwap == true){
                                    Kolejka->Swap(d1, d2);
                                    powtorzenia++;
                                }
                                else{
                                    Kolejka->WstawZadanie(d1, sZadBufor);
                                    powtorzenia++;
                                }
                            }
                        }
                        Temper = Temper*skok;
                    }
                    //Krawedzie->WyczyscSloty(); //STRASZNIE WAZNE!!!!!
                    //Kolejka->WyczyscKrawedzieSciezki(); //TAK SAMO WAZNE!!! ZAPOMNIALEM O CZYSZCZENIU WEKTOROW!!!!!!!!!11ONE11!!!
                cout << nfrCurrent << "\t" << clock() - start << "\n";
                fWyniki << Scenariusze.KodScenariusza(liczScen)<< "\t" << NET << "\t" << DEM << "\t" << DMC << "\t" << LiczbaSciezek << "\t" << LiczbaDrzew << "\t" << nfrCurrent << "\t" << clock() - start << "\n";

    //usuwanie obiektow
    delete Sciezki;
    delete Drzewa;
    delete Krawedzie;
    delete Kolejka;
    licznik++;
    } //--koniec lola---
    } //--koniec petli for---
    fWyniki.close();
    return 0;
}
