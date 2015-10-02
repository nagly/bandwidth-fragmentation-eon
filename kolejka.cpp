#include "kolejka.hpp"
#include "funkcje.hpp"

CKolejka::CKolejka()
{
    m_psKolejka = new SZadania[m_uIloscUni+m_uIloscMulti];
}
CKolejka::CKolejka(const CKolejka& fKolejka)
{
    m_psKolejka = new SZadania[m_uIloscUni+m_uIloscMulti];
    for (unsigned i = 0; i < m_uIloscMulti+m_uIloscUni; i++){
        m_psKolejka[i].nIndeksZadania = fKolejka.m_psKolejka[i].nIndeksZadania;
        m_psKolejka[i].nLiczbaSlotow = fKolejka.m_psKolejka[i].nLiczbaSlotow;
        m_psKolejka[i].nNumerSciezki = fKolejka.m_psKolejka[i].nNumerSciezki;
        m_psKolejka[i].nPrzepust = fKolejka.m_psKolejka[i].nPrzepust;
        m_psKolejka[i].typ = fKolejka.m_psKolejka[i].typ;
        m_psKolejka[i].vKrawedzieSciezki = fKolejka.m_psKolejka[i].vKrawedzieSciezki;
    }
}
CKolejka::~CKolejka()
{
    delete[] m_psKolejka;
    for (unsigned i = 0; i<m_uIloscUni; i++)
            delete[] m_ppnKolejkaUni[i];
        delete[] m_ppnKolejkaUni;
}
bool CKolejka::TabUnicast()
{
    m_ppnKolejkaUni = new int* [m_uIloscUni];
    for (unsigned i = 0; i<m_uIloscUni; i++)
        m_ppnKolejkaUni[i] = new int [3];

    fstream file(DEM.c_str(), ios::in);
    GotoLine(file, 2);
    for (unsigned i = 0; i<m_uIloscUni; i++){
        for (unsigned j = 0; j<3; j++){
            file >> m_ppnKolejkaUni[i][j];
        }
    }
    file.close();
    return true;
}
void CKolejka::WyczyscKrawedzieSciezki()
{
    for (unsigned i = 0; i<m_uIloscUni+m_uIloscMulti; i++){
        m_psKolejka[i].vKrawedzieSciezki.clear();
    }
}
void CKolejka::WyczyscKrawedzieSciezki2(unsigned uIndeksKolejki)
{
    m_psKolejka[uIndeksKolejki].vKrawedzieSciezki.clear();
}
bool CKolejka::FirstFitUM()
{
    int k = 0;
    for (unsigned i = 0; i<m_uIloscUni; i++)
    {
        m_psKolejka[i].typ = "U";
        m_psKolejka[i].nIndeksZadania = i;
        m_psKolejka[i].nNumerSciezki = 1;
        m_psKolejka[i].nPrzepust = m_ppnKolejkaUni[i][2];
    }
    fstream fDMC(DMC.c_str(), ios::in);
    int linia = 2;
    GotoLine(fDMC, linia);
    for (unsigned j = m_uIloscUni; j<m_uIloscMulti+m_uIloscUni; j++)
    {
        m_psKolejka[j].typ = "M";
        m_psKolejka[j].nIndeksZadania = k;
        m_psKolejka[j].nNumerSciezki = 1;
        fDMC >> m_psKolejka[j].nPrzepust;
        linia++;
        k++;
        GotoLine(fDMC, linia);
    }
    fDMC.close();
    return true;
}
bool CKolejka::FirstFitMU()
{
    fstream fDMC(DMC.c_str(), ios::in);
    int linia = 2;
    GotoLine(fDMC, linia);
    int k = 0;
    for (unsigned i = 0; i<m_uIloscMulti; i++)
    {
        m_psKolejka[i].typ = "M";
        m_psKolejka[i].nIndeksZadania = i;
        m_psKolejka[i].nNumerSciezki = 1;
        fDMC >> m_psKolejka[i].nPrzepust;
        linia++;
        GotoLine(fDMC, linia);
    }
    fDMC.close();
    for (unsigned j = m_uIloscMulti; j<m_uIloscMulti+m_uIloscUni; j++)
    {
        m_psKolejka[j].typ = "U";
        m_psKolejka[j].nIndeksZadania = k;
        m_psKolejka[j].nNumerSciezki = 1;
        m_psKolejka[j].nPrzepust = m_ppnKolejkaUni[k][2];
        k++;
    }
    return true;
}
bool CKolejka::RandomMU()
{
    srand( time( NULL ) );
    int liczba;
    vector<int> wylosowaneM, wylosowaneU;
    fstream fDMC(DMC.c_str(), ios::in);
    int linia = 2;
    GotoLine(fDMC, linia);
    for (unsigned i = 0; i<m_uIloscMulti; i++){
        do{
            liczba = rand() % m_uIloscMulti;
        }
        while (SprawdzCzyJest(wylosowaneM, liczba) == true);
        wylosowaneM.push_back(liczba);
    }
    for (unsigned j = 0; j<m_uIloscUni; j++){
        do{
            liczba = rand() % m_uIloscUni;
        }
        while (SprawdzCzyJest(wylosowaneU, liczba));
        wylosowaneU.push_back(liczba);
    }
    for (unsigned k = 0; k<m_uIloscMulti; k++){
        m_psKolejka[k].typ = "M";
        m_psKolejka[k].nIndeksZadania = wylosowaneM[k];
        m_psKolejka[k].nNumerSciezki = ( rand() % LiczbaDrzew ) + 1;
        fDMC >> m_psKolejka[k].nPrzepust;
        linia++;
        GotoLine(fDMC, linia);
    }
    fDMC.close();
    int k = 0;
    for (unsigned j = m_uIloscMulti; j<m_uIloscMulti+m_uIloscUni; j++){
        m_psKolejka[j].typ = "U";
        m_psKolejka[j].nIndeksZadania = wylosowaneU[k];
        m_psKolejka[j].nNumerSciezki = ( rand() % LiczbaSciezek ) + 1;
        m_psKolejka[j].nPrzepust = m_ppnKolejkaUni[wylosowaneU[k]][2];
        k++;
    }
    return true;
}
bool CKolejka::RandomUM()
{
    srand( time( NULL ) );
    int liczba;
    vector<int> wylosowaneM, wylosowaneU;
    fstream fDMC(DMC.c_str(), ios::in);
    int linia = 2;
    GotoLine(fDMC, linia);
    for (unsigned i = 0; i<m_uIloscUni; i++){
        do{
            liczba = rand() % m_uIloscUni;
        }
        while (SprawdzCzyJest(wylosowaneU, liczba) == true);
        wylosowaneU.push_back(liczba);
    }
    for (unsigned i = 0; i<m_uIloscMulti; i++){
        do{
            liczba = rand() % m_uIloscMulti;
        }
        while (SprawdzCzyJest(wylosowaneM, liczba));
        wylosowaneM.push_back(liczba);
    }
    for (unsigned j = 0; j<m_uIloscUni; j++){
        m_psKolejka[j].typ = "U";
        m_psKolejka[j].nIndeksZadania = wylosowaneU[j];
        m_psKolejka[j].nNumerSciezki = ( rand() % LiczbaSciezek ) + 1;
        m_psKolejka[j].nPrzepust = m_ppnKolejkaUni[wylosowaneU[j]][2];
    }
    int k = 0;
    for (unsigned j = m_uIloscUni; j<m_uIloscUni+m_uIloscMulti; j++){
        m_psKolejka[j].typ = "M";
        m_psKolejka[j].nIndeksZadania = wylosowaneM[k];
        m_psKolejka[j].nNumerSciezki = ( rand() % LiczbaDrzew ) + 1;
        fDMC >> m_psKolejka[j].nPrzepust;
        linia++;
        k++;
        GotoLine(fDMC, linia);
    }
    fDMC.close();
    return true;
}
bool CKolejka::RandomUMU()
{
    srand( time( NULL ) );
    int liczba;
    vector<int> wylosowane;
    SZadania* m_psBufor = new SZadania[m_uIloscUni+m_uIloscMulti];
    unsigned zakres = m_uIloscUni+m_uIloscMulti;
    //-----------------------wladowanie zadan-------------
    fstream fDMC(DMC.c_str(), ios::in);
    int linia = 2;
    GotoLine(fDMC, linia);
    int k = 0;
    for (unsigned i = 0; i<m_uIloscMulti; i++)
    {
        m_psKolejka[i].typ = "M";
        m_psKolejka[i].nIndeksZadania = i;
        m_psKolejka[i].nNumerSciezki = ( rand() % LiczbaDrzew ) + 1;
        fDMC >> m_psKolejka[i].nPrzepust;
        linia++;
        GotoLine(fDMC, linia);
    }
    fDMC.close();
    for (unsigned i = m_uIloscMulti; i<m_uIloscMulti+m_uIloscUni; i++)
    {
        m_psKolejka[i].typ = "U";
        m_psKolejka[i].nIndeksZadania = k;
        m_psKolejka[i].nNumerSciezki = ( rand() % LiczbaSciezek ) + 1;
        m_psKolejka[i].nPrzepust = m_ppnKolejkaUni[k][2];
        k++;
    }
    //--------------------koniec wladowania zadan-------------
    //-------mieszanie zadan-----------
    for (unsigned j = 0; j<zakres; j++){
        liczba = rand() % zakres;
        do{
            liczba = rand() % zakres;
        }
        while (SprawdzCzyJest(wylosowane, liczba) == true);
        m_psBufor[j] = m_psKolejka[liczba];
        wylosowane.push_back(liczba);
    }
    for (unsigned j = 0; j<m_uIloscUni+m_uIloscMulti; j++){
        m_psKolejka[j] = m_psBufor[j];
    }
    return true;
}
bool CKolejka::BiggerDemFirst()
{
    vector<int> vPrzepustowosci, vIndeksyZadan;
    SZadania* m_psBufor = new SZadania[m_uIloscUni+m_uIloscMulti];
    int nBufor = 0;
    unsigned j;
    //-----------------------wladowanie zadan-------------
    fstream fDMC(DMC.c_str(), ios::in);
    int linia = 2;
    GotoLine(fDMC, linia);
    int k = 0;
    for (unsigned i = 0; i<m_uIloscMulti; i++)
    {
        m_psKolejka[i].typ = "M";
        m_psKolejka[i].nIndeksZadania = i;
        m_psKolejka[i].nNumerSciezki = ( rand() % LiczbaDrzew ) + 1;
        fDMC >> m_psKolejka[i].nPrzepust;
        linia++;
        GotoLine(fDMC, linia);
    }
    fDMC.close();
    for (unsigned i = m_uIloscMulti; i<m_uIloscMulti+m_uIloscUni; i++)
    {
        m_psKolejka[i].typ = "U";
        m_psKolejka[i].nIndeksZadania = k;
        m_psKolejka[i].nNumerSciezki = ( rand() % LiczbaSciezek ) + 1;
        m_psKolejka[i].nPrzepust = m_ppnKolejkaUni[k][2];
        k++;
    }
    //--------------------koniec wladowania zadan-------------
    //wybieranie najwyzszej przepustowosci
    for (unsigned i = 0; i<m_uIloscUni+m_uIloscMulti; i++){
            if (nBufor <= m_psKolejka[i].nPrzepust){
                nBufor = m_psKolejka[i].nPrzepust;
                j = i;
            }
        }
    vPrzepustowosci.push_back(nBufor);
    vIndeksyZadan.push_back(j);
    nBufor = 0;
    int indeksWektora = 0;
    //wybieranie przpustowosci malejaco i zapisywanie ich indeksow
    while (vIndeksyZadan.size() != m_uIloscUni+m_uIloscMulti){

        for (unsigned i = 0; i<m_uIloscUni+m_uIloscMulti; i++){
            if ((nBufor <= m_psKolejka[i].nPrzepust) and (vPrzepustowosci[indeksWektora] >= nBufor) and (SprawdzCzyJest(vIndeksyZadan, i) == false)){
                nBufor = m_psKolejka[i].nPrzepust;
                j = i;
            }
        }
        vPrzepustowosci.push_back(nBufor);
        vIndeksyZadan.push_back(j);
        nBufor = 0;
    }
    for (unsigned j = 0; j<vIndeksyZadan.size(); j++)
            cout << "[" << vIndeksyZadan[j] << "] " << vPrzepustowosci[j] << endl;
    //teraz sortowanie kolejki malejaco wg przepustowosci
    for (unsigned k = 0; k<m_uIloscUni+m_uIloscMulti; k++){
        m_psBufor[k] = m_psKolejka[vIndeksyZadan[k]];
    }
    for (unsigned k = 0; k<m_uIloscUni+m_uIloscMulti; k++){
        m_psKolejka[k] = m_psBufor[k];
    }
    return true;
}
int CKolejka::NrSciezki(unsigned uIndeksKolejki)
{
    if (uIndeksKolejki < m_uIloscMulti+m_uIloscUni) return m_psKolejka[uIndeksKolejki].nNumerSciezki;
    else return 0;
}
int CKolejka::IndeksZadania(unsigned uIndeksKolejki)
{
    if (uIndeksKolejki < m_uIloscMulti+m_uIloscUni) return m_psKolejka[uIndeksKolejki].nIndeksZadania;
    else return 0;
}
int CKolejka::Przepust(unsigned uIndeksKolejki)
{
    if (uIndeksKolejki < m_uIloscMulti+m_uIloscUni) return m_psKolejka[uIndeksKolejki].nPrzepust;
    else return 0;
}
string CKolejka::Typ(unsigned uIndeksKolejki)
{
    if (uIndeksKolejki < m_uIloscMulti+m_uIloscUni) return m_psKolejka[uIndeksKolejki].typ;
    else return "?";
}
int CKolejka::Wielkosc()
{
    return m_uIloscMulti+m_uIloscUni;
}
int CKolejka::ObliczWierszSciezki(unsigned uIndeksZadania, unsigned uIndeksKolejki)
{
    unsigned uWierzchPocz = m_ppnKolejkaUni[uIndeksZadania][0];
    unsigned uWierzchKon = m_ppnKolejkaUni[uIndeksZadania][1];
    unsigned uNrSciezki = m_psKolejka[uIndeksKolejki].nNumerSciezki;
    if (uWierzchPocz < uWierzchKon) return (uWierzchPocz*(LiczbaW-1)*LiczbaSciezek)+(uWierzchKon-1)*LiczbaSciezek+uNrSciezki-1;
    else return (uWierzchPocz*(LiczbaW-1)*LiczbaSciezek)+uWierzchKon*LiczbaSciezek+uNrSciezki-1;
}
int CKolejka::ObliczWierszDrzewa(unsigned uIndeksZadania, unsigned uIndeksKolejki)
{
    unsigned uNrSciezki = m_psKolejka[uIndeksKolejki].nNumerSciezki;
    return uIndeksZadania*LiczbaDrzew+uNrSciezki-1; //zwraca nam numer wiersza w tablicy drzew w ktorym jest interesujace nas drzewo
}
void CKolejka::UzupelnijKrawedzie(unsigned uIndeksKolejki, unsigned uWartosc)
{
    m_psKolejka[uIndeksKolejki].vKrawedzieSciezki.push_back(uWartosc);
}
void CKolejka::UzupelnijSloty(unsigned uIndeksKolejki, unsigned uWartosc)
{
    m_psKolejka[uIndeksKolejki].nLiczbaSlotow = uWartosc;
}
vector<int> CKolejka::KrawedzieSciezki(unsigned uIndeksKolejki)
{
    return m_psKolejka[uIndeksKolejki].vKrawedzieSciezki;
}
int CKolejka::Sloty(unsigned uIndeksKolejki)
{
    return m_psKolejka[uIndeksKolejki].nLiczbaSlotow;
}
void CKolejka::Wypisz(unsigned uIndeksKolejki)
{
    if (uIndeksKolejki < m_uIloscMulti+m_uIloscUni){
        cout << "Typ: " << m_psKolejka[uIndeksKolejki].typ << endl;
        cout << "Indeks Zadania: " << m_psKolejka[uIndeksKolejki].nIndeksZadania << endl;
        cout << "Numer Sciezki: " << m_psKolejka[uIndeksKolejki].nNumerSciezki << endl;
        cout << "Przepustowosc: " << m_psKolejka[uIndeksKolejki].nPrzepust << endl;
        cout << "Indeksy krawedzi: ";
        for (unsigned i = 0; i< m_psKolejka[uIndeksKolejki].vKrawedzieSciezki.size(); i++)
            cout << m_psKolejka[uIndeksKolejki].vKrawedzieSciezki[i] << " ";
        cout << endl;
        cout << "Liczba slotow: " << m_psKolejka[uIndeksKolejki].nLiczbaSlotow << endl;
    }
    else
        cout << "Problem z wczytaniem tego zadania." << endl;
}
void CKolejka::Swap(unsigned uIndeksZad1, unsigned uIndeksZad2)
{
//    SZadania* m_psBufor = new SZadania [2];
//    m_psBufor[0] = m_psKolejka[uIndeksZad1];
//    m_psBufor[1] = m_psKolejka[uIndeksZad2];
//    m_psKolejka[uIndeksZad1] = m_psBufor[1];
//    m_psKolejka[uIndeksZad2] = m_psBufor[0];
//    delete[] m_psBufor;
    swap(m_psKolejka[uIndeksZad1], m_psKolejka[uIndeksZad2]);
}

bool CKolejka::ZmienSciezke(unsigned uIndeksZad)
{
    if (m_psKolejka[uIndeksZad].typ == "U"){
        if (m_psKolejka[uIndeksZad].nNumerSciezki+1 <= LiczbaSciezek){
            m_psKolejka[uIndeksZad].nNumerSciezki++;
        }
        else{
            m_psKolejka[uIndeksZad].nNumerSciezki--;
        }
    }
    else{
        if (m_psKolejka[uIndeksZad].nNumerSciezki+1 <= LiczbaDrzew){
            m_psKolejka[uIndeksZad].nNumerSciezki++;
        }
        else{
            m_psKolejka[uIndeksZad].nNumerSciezki--;
        }
    }
    return true;
}

void CKolejka::ZmienSciezkeRev(unsigned uIndeksZad)
{
    if (m_psKolejka[uIndeksZad].nNumerSciezki-1 >= 1){
        m_psKolejka[uIndeksZad].nNumerSciezki--;
    }
}

SZadania CKolejka::Bufor(unsigned uIndeksZad)
{
    return m_psKolejka[uIndeksZad];
}
void CKolejka::WstawZadanie(unsigned uIndeksZad, SZadania sBufor)
{
    m_psKolejka[uIndeksZad] = sBufor;
}
void CKolejka::UstawNrSciezki(unsigned uIndeksKolejki, unsigned uWartosc)
{
    m_psKolejka[uIndeksKolejki].nNumerSciezki = uWartosc;
}
void CKolejka::Wypelnij(CKolejka fKolejka)
{
    for (unsigned i = 0; i < m_uIloscMulti+m_uIloscUni; i++){
        m_psKolejka[i].nIndeksZadania = fKolejka.m_psKolejka[i].nIndeksZadania;
        m_psKolejka[i].nLiczbaSlotow = fKolejka.m_psKolejka[i].nLiczbaSlotow;
        m_psKolejka[i].nNumerSciezki = fKolejka.m_psKolejka[i].nNumerSciezki;
        m_psKolejka[i].nPrzepust = fKolejka.m_psKolejka[i].nPrzepust;
        m_psKolejka[i].typ = fKolejka.m_psKolejka[i].typ;
        m_psKolejka[i].vKrawedzieSciezki = fKolejka.m_psKolejka[i].vKrawedzieSciezki;
    }
}
