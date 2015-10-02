#ifndef krawedzie_hpp
#define krawedzie_hpp
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;
extern unsigned LiczbaW, LiczbaK;
struct SKrawedzie
{
    int wierz_pocz;
    int wierz_kon;
    int dlugosc;
    vector<int> sloty;
    vector<int> pomocFR;
    float FR;
};

class CKrawedzie
{
private:
    SKrawedzie* m_psKrawedzie;
    unsigned m_uLiczbaK = LiczbaK;
    unsigned m_uLiczbaW = LiczbaW;
public:
    CKrawedzie();
    ~CKrawedzie();
    bool WladujKrawedzie(string sNET);
    bool Pobierz(unsigned uIndeksStruk);
    int WierzchPocz(unsigned uIndeksStruk);
    int WierzchKon(unsigned uIndeksStruk);
    int Dlugosc(unsigned uIndeksStruk);
    void WyczyscSloty();
    void Ulokuj(vector<int> vKrawedzie, unsigned uIloscSlotow);
    void ObliczFR(unsigned uParamP);
    //pomoc!
    void WypiszFR();
    double NFR();
    void WypiszSloty(unsigned uIndeksStruk);
    void WypiszDlugSlot(unsigned uIndeksStruk);
};

#endif // krawedzie_hpp
