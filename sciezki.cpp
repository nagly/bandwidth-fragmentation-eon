#include "sciezki.hpp"
#include "funkcje.hpp"

CSciezki::CSciezki(unsigned uLiczbaSciezek)
{
    m_uLiczbaSciezek = uLiczbaSciezek;
    m_uRozmiarW = LiczbaW*(LiczbaW-1)*m_uLiczbaSciezek;
    m_uRozmiarK = LiczbaK;
    m_ppnTablica = new int* [m_uRozmiarW];
    for (unsigned i = 0; i<m_uRozmiarW; i++)
        m_ppnTablica[i] = new int [m_uRozmiarK];
}
CSciezki::~CSciezki()
{
    for (unsigned i = 0; i<m_uRozmiarW; i++)
        delete[] m_ppnTablica[i];
    delete[] m_ppnTablica;

}
int CSciezki::Pobierz(unsigned uIndeksW, unsigned uIndeksK) const
{
    if (uIndeksW < m_uRozmiarW and uIndeksK < m_uRozmiarK) return m_ppnTablica[uIndeksW][uIndeksK];
    else return 0;
}
//pomoc
void CSciezki::WypiszKrawedzie(unsigned uIndeksSciez)
{
    for (unsigned i=0; i<m_uRozmiarK; i++){
        if (m_ppnTablica[uIndeksSciez][i]==1)
            cout << i << " ";
    }
    cout << endl;
}
unsigned CSciezki::RozmiarW() const {return m_uRozmiarW;}
unsigned CSciezki::RozmiarK() const {return m_uRozmiarK;}
unsigned CSciezki::LiczbaSciezek() const {return m_uLiczbaSciezek;}
bool CSciezki::WladujSciezki(string sPAT)
{
    unsigned numerLinii = 2;
    int wiersz = 0;
    fstream file(sPAT.c_str(), ios::in);
    GotoLine(file, 2);

    for (unsigned i = 0; i<(m_uRozmiarW/m_uLiczbaSciezek); i++){
        for (unsigned j = 0; j<m_uLiczbaSciezek; j++){
            for (unsigned k = 0; k<m_uRozmiarK; k++){
                file >> m_ppnTablica[wiersz][k];
            }
            wiersz++;
        }
        numerLinii = numerLinii + 30;
        GotoLine(file, numerLinii);
    }
    file.close();
    return true;
}
