#include "krawedzie.hpp"
#include "funkcje.hpp"

CKrawedzie::CKrawedzie()
{
    m_psKrawedzie = new SKrawedzie[m_uLiczbaK];
}
CKrawedzie::~CKrawedzie()
{
    delete[] m_psKrawedzie;
}
bool CKrawedzie::WladujKrawedzie(string sNET)
{
    unsigned buforGraf[m_uLiczbaW][m_uLiczbaW];
    int x = 0; //indeks struktury w tablicy struktur
    fstream file(sNET.c_str(), ios::in);
    GotoLine(file, 3);

    for (unsigned i = 0; i<m_uLiczbaW; i++){
        for (unsigned j = 0; j<m_uLiczbaW; j++){
            file >> buforGraf[i][j];
            //cout << buforGraf[i][j] << "   "; //opcjonalnie
            if (buforGraf[i][j] != 0){
                m_psKrawedzie[x].wierz_pocz = i;
                m_psKrawedzie[x].wierz_kon = j;
                m_psKrawedzie[x].dlugosc = buforGraf[i][j];
                x++;
            }
        }
        //cout << endl; //opcjonalnie
    }
    return true;
}

bool CKrawedzie::Pobierz(unsigned uIndeksStruk)
{
    if (uIndeksStruk < m_uLiczbaK){
        cout << "Poczatek: " << m_psKrawedzie[uIndeksStruk].wierz_pocz << endl;
        cout << "Koniec: " << m_psKrawedzie[uIndeksStruk].wierz_kon << endl;
        cout << "Dlugosc: " << m_psKrawedzie[uIndeksStruk].dlugosc << endl;
        return true;
    }
    else
        return false;
}
int CKrawedzie::WierzchPocz(unsigned uIndeksStruk)
{
    if (uIndeksStruk < m_uLiczbaK) return m_psKrawedzie[uIndeksStruk].wierz_pocz;
    else return 0;
}
int CKrawedzie::WierzchKon(unsigned uIndeksStruk)
{
    if (uIndeksStruk < m_uLiczbaK) return m_psKrawedzie[uIndeksStruk].wierz_kon;
    else return 0;
}
int CKrawedzie::Dlugosc(unsigned uIndeksStruk)
{
    if (uIndeksStruk < m_uLiczbaK) return m_psKrawedzie[uIndeksStruk].dlugosc;
    else return 0;
}
void CKrawedzie::WyczyscSloty()
{
    for (unsigned i = 0; i<m_uLiczbaK; i++){
        m_psKrawedzie[i].sloty.clear();
    }
}
void CKrawedzie::Ulokuj(vector<int> vKrawedzie, unsigned uIloscSlotow)
{
    unsigned m = 0;
    for (unsigned i = 0; i<vKrawedzie.size(); i++){
        if (m < m_psKrawedzie[vKrawedzie[i]].sloty.size())
            m = m_psKrawedzie[vKrawedzie[i]].sloty.size();
    }
    for (unsigned j = 0; j<vKrawedzie.size(); j++){
        if (m_psKrawedzie[vKrawedzie[j]].sloty.size() < m){
            unsigned r = m - m_psKrawedzie[vKrawedzie[j]].sloty.size();
            for (unsigned k = 0; k<r; k++)
                m_psKrawedzie[vKrawedzie[j]].sloty.push_back(0);
        }
    }
    for (unsigned l = 0; l<vKrawedzie.size(); l++){
        for (unsigned x = 0; x<uIloscSlotow; x++)
            m_psKrawedzie[vKrawedzie[l]].sloty.push_back(1);
    }
}
void CKrawedzie::ObliczFR(unsigned uParamP)
{
    for (unsigned i = 0; i<m_uLiczbaK; i++){
        vector<int> vWolneBloki;
        int slot0 = 1;
        int slot1;
        int licznik = 0;
        bool zero = false; //zabezpieczenie przed tym jakby na jakims laczu byly same zajete sloty

        for (unsigned j = 0; j<m_psKrawedzie[i].sloty.size(); j++){
            slot1 = m_psKrawedzie[i].sloty[j];
            if ((slot0 == 1 and slot1 == 0) or (slot0 == 0 and slot1 == 0)){
                licznik++;
                zero = true;
            }
            else
                if (slot0 == 0 and slot1 == 1){
                    vWolneBloki.push_back(licznik);
                    licznik = 0;
                }
            slot0 = slot1;
        }
        //teraz obliczenie FR
        if (m_psKrawedzie[i].sloty.size() != 0 and zero != false){
            int dzielna = 0; int dzielnik = 0;
            for (unsigned k = 0; k<vWolneBloki.size(); k++){
                dzielna += pow(vWolneBloki[k], uParamP);
                dzielnik += vWolneBloki[k];
            }
            m_psKrawedzie[i].FR = 1-(dzielna/pow(dzielnik, uParamP));
        }
        else
            m_psKrawedzie[i].FR = 0;
        slot0 = 1;
        vWolneBloki.clear();
    }
}
//pomoc!
void CKrawedzie::WypiszFR()
{
    for (unsigned i = 0; i<m_uLiczbaK; i++)
        cout << "[" << i << "] " << m_psKrawedzie[i].FR << endl;
}
double CKrawedzie::NFR()
{
    double dSumaFR = 0;
    for (unsigned i = 0; i<m_uLiczbaK; i++)
        dSumaFR += m_psKrawedzie[i].FR;
    return (dSumaFR/m_uLiczbaK);
}
void CKrawedzie::WypiszSloty(unsigned uIndeksStruk)
{
    if (uIndeksStruk < m_uLiczbaK){
        for (unsigned i = 0; i< m_psKrawedzie[uIndeksStruk].sloty.size(); i++){
            cout << m_psKrawedzie[uIndeksStruk].sloty[i];
        }
    }
}
void CKrawedzie::WypiszDlugSlot(unsigned uIndeksStruk)
{
    cout << "Dlugosc wektora slotow na " << uIndeksStruk+1 << " krawedzi to: " << m_psKrawedzie[uIndeksStruk].sloty.size();
}
