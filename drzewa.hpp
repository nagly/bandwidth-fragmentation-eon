#ifndef drzewa_hpp
#define drewa_hpp
#include <string>
#include <fstream>
using namespace std;
extern unsigned LiczbaK;
class CDrzewa
{
private:
    int** m_ppnTablica;
    unsigned m_uRozmiarW, m_uRozmiarK, m_uLiczbaDrzew, m_uLiczbaZad;

public:
    CDrzewa(unsigned uLiczbaDrzew, string sDMC);
    ~CDrzewa();
    int Pobierz(unsigned uIndeksW, unsigned uIndeksK) const;
    unsigned RozmiarW() const;
    unsigned RozmiarK() const;
    unsigned LiczbaDrzew() const;
    bool WladujDrzewa(string sTREE, string sSPEC);
};
#endif // drzewa_hpp
