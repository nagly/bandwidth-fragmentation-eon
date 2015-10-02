#ifndef kolejka_hpp
#define kolejka_hpp
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;
extern unsigned LiczbaW, LiczbaUni, LiczbaMulti, LiczbaSciezek, LiczbaDrzew;
extern string DEM, DMC;

struct SZadania
{
    string typ;
    int nIndeksZadania;
    int nNumerSciezki;
    int nPrzepust;
    vector<int> vKrawedzieSciezki;
    int nLiczbaSlotow;

};

class CKolejka
{
private:
    SZadania* m_psKolejka;
    int** m_ppnKolejkaUni;
    unsigned m_uIloscUni = LiczbaUni;
    unsigned m_uIloscMulti = LiczbaMulti;
public:
    CKolejka();
    CKolejka(const CKolejka& fKolejka);
    ~CKolejka();
    bool TabUnicast();
    void WyczyscKrawedzieSciezki();
    void WyczyscKrawedzieSciezki2(unsigned uIndeksKolejki);
    bool FirstFitUM();
    bool FirstFitMU();
    bool RandomMU();
    bool RandomUM();
    bool RandomUMU();
    bool BiggerDemFirst();
    int NrSciezki(unsigned uIndeksKolejki);
    int IndeksZadania(unsigned uIndeksKolejki);
    int Przepust(unsigned uIndeksKolejki);
    string Typ(unsigned uIndeksKolejki);
    int Wielkosc();
    int ObliczWierszSciezki(unsigned uIndeksZadania, unsigned uIndeksKolejki);
    int ObliczWierszDrzewa(unsigned uIndeksZadania, unsigned uIndeksKolejki);
    void UzupelnijKrawedzie(unsigned uIndeksKolejki, unsigned uWartosc);
    void UzupelnijSloty(unsigned uIndeksKolejki, unsigned uWartosc);
    vector<int> KrawedzieSciezki(unsigned uIndeksKolejki);
    int Sloty(unsigned uIndeksKolejki);
    void Wypisz(unsigned uIndeksKolejki);
    void Swap(unsigned uIndeksZad1, unsigned uIndeksZad2);
    bool ZmienSciezke(unsigned uIndeksZad);
    void ZmienSciezkeRev(unsigned uIndeksZad);
    SZadania Bufor(unsigned uIndeksZad);
    void WstawZadanie(unsigned uIndeksZad, SZadania sBufor);
    void UstawNrSciezki(unsigned uIndeksKolejki, unsigned uWartosc);
    void Wypelnij(CKolejka fKolejka);
};
#endif // kolejka_hpp
