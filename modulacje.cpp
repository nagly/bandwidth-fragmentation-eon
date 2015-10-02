#include "modulacje.hpp"


CModulacje::CModulacje()
{
    m_ppnModulacje = new int* [WIERSZE];
    for (unsigned i = 0; i<WIERSZE; i++)
        m_ppnModulacje[i] = new int [KOLUMNY];
}
bool CModulacje::Uzupelnij(string sPAR)
{
    fstream file(sPAR.c_str(), ios::in);
    for (unsigned i = 0; i<WIERSZE; i++){
        for (unsigned j = 0; j<KOLUMNY; j++){
            file >> m_ppnModulacje[i][j];
        }
    }
    file.close();
    return true;
}
int CModulacje::Pobierz(unsigned uIndeksW, unsigned uIndeksK) const
{
    if (uIndeksW < WIERSZE and uIndeksK < KOLUMNY) return m_ppnModulacje[uIndeksW][uIndeksK];
    else return 0;
}
int CModulacje::IleSlotow(int nPrzepust, int nDlugosc)
{
    int wiersz = (nPrzepust/10)-1;
    if (nDlugosc > m_ppnModulacje[wiersz][1])
        return m_ppnModulacje[wiersz][6];
    else
        if (nDlugosc <= m_ppnModulacje[wiersz][1] and nDlugosc > m_ppnModulacje[wiersz][2])
            return m_ppnModulacje[wiersz][7];
        else
            if (nDlugosc <= m_ppnModulacje[wiersz][2] and nDlugosc > m_ppnModulacje[wiersz][3])
                return m_ppnModulacje[wiersz][8];
            else
                if (nDlugosc <= m_ppnModulacje[wiersz][3] and nDlugosc > m_ppnModulacje[wiersz][4])
                    return m_ppnModulacje[wiersz][9];
                else
                    if (nDlugosc <= m_ppnModulacje[wiersz][4] and nDlugosc > m_ppnModulacje[wiersz][5])
                        return m_ppnModulacje[wiersz][10];
                    else
                        return m_ppnModulacje[wiersz][11];
}
