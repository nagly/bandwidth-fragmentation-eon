#ifndef sciezki_hpp
#define sciezki_hpp
#include <iostream>
#include <string>
using namespace std;
extern unsigned LiczbaW, LiczbaK;

class CSciezki
{
private:
    int** m_ppnTablica;
    unsigned m_uRozmiarW, m_uRozmiarK, m_uLiczbaSciezek;
public:
    CSciezki(unsigned uLiczbaSciezek);
    ~CSciezki();
    int Pobierz(unsigned uIndeksW, unsigned uIndeksK) const;
    void WypiszKrawedzie(unsigned uIndeksSciez);
    unsigned RozmiarW() const;
    unsigned RozmiarK() const;
    unsigned LiczbaSciezek() const;
    bool WladujSciezki(string sPAT);
};
#endif // sciezki_hpp
