#include "scenariusze.hpp"
#include "funkcje.hpp"

CScenariusze::CScenariusze()
{
    ifstream file("scenariusze20.txt");
    file >> m_uLiczbaScen;
    LiczbaScenariuszy = m_uLiczbaScen;
    m_pnScenariusze = new string [m_uLiczbaScen];
    file.close();
}
bool CScenariusze::Wypelnij()
{
    fstream file("scenariusze20.txt");
    GotoLine(file, 2);
    string linia;
    for (unsigned i = 0; i<m_uLiczbaScen; i++){
        getline(file, linia);
        m_pnScenariusze[i] = linia;
        //cout << m_pnScenariusze[i] << endl;
    }
    file.close();
    return true;
}
void CScenariusze::PodajPliki(unsigned uIndeksScen)
{
    string wiersz, m_NET, m_DEM, m_DMC, m_PAT, m_TREE, m_SPEC, m_sciezki, m_drzewa;
    wiersz = m_pnScenariusze[uIndeksScen];
    for (unsigned i = 0; i<2; i++)
        m_NET += wiersz[i];
    m_NET += ".net";
    NET = m_NET;
    //cout << "Plik z grafem: " << NET << endl;

    for (unsigned j = 2; j<4; j++)
        m_DEM += wiersz[j];
    m_DEM += ".dem";
    DEM = m_DEM;
    //cout << "Plik z unicast: " << DEM << endl;

    for (unsigned k = 4; k<6; k++)
        m_DMC += wiersz[k];
    DMC = m_DMC;
    DMC += ".dmc";
    //cout << "Plik z multicast: " << DMC << endl;

    m_PAT += wiersz[0];
    m_PAT += ".pat";
    PAT = m_PAT;
    //cout << "Plik ze sciezkami kandydujacymi: " << PAT << endl;

    m_TREE = m_DMC;
    m_TREE += ".tree";
    TREE = m_TREE;
    //cout << "Plik z drzewami kandydujacymi: " << TREE << endl;

    m_SPEC = m_DMC;
    m_SPEC += ".spec";
    SPEC = m_SPEC;
    //cout << "Plik z liczba slotow dla multicast: " << SPEC << endl;

    bool flaga = false;
    for (unsigned k = 6; k < 8; k++){
        if (wiersz[k] != 0)
            flaga = true;
        if (flaga == true)
            m_sciezki += wiersz[k];
    }
    LiczbaSciezek = atoi(m_sciezki.c_str());
    //cout << "Liczba sciezek: " << LiczbaSciezek << endl;
    flaga = false;
    for (unsigned k = 8; k < 12; k++){
        if (wiersz[k] != 0)
            flaga = true;
        if (flaga == true)
            m_drzewa += wiersz[k];
    }
    LiczbaDrzew = atoi(m_drzewa.c_str());
    //cout << "Liczba drzew: " << LiczbaDrzew << endl;

}
string CScenariusze::KodScenariusza(unsigned uIndeksScen)
{
    return m_pnScenariusze[uIndeksScen];
}
