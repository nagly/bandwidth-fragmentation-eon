#ifndef modulacje_hpp
#define modulacje_hpp
#include <string>
#include <fstream>
using namespace std;
class CModulacje
{
    static const unsigned WIERSZE = 40;
    static const unsigned KOLUMNY = 12;

private:
    int** m_ppnModulacje;
public:
    CModulacje();
    bool Uzupelnij(string sPAR);
    int Pobierz(unsigned uIndeksW, unsigned uIndeksK) const;
    int IleSlotow(int nPrzepust, int nDlugosc);
};
#endif // modulacje_hpp
