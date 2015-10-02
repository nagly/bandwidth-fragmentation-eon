#include "drzewa.hpp"
#include "funkcje.hpp"

CDrzewa::CDrzewa(unsigned uLiczbaDrzew, string sDMC)
{
    ifstream file(sDMC.c_str(), ios::in);
    file >> m_uLiczbaZad;
    file.close();
    m_uLiczbaDrzew = uLiczbaDrzew;
    m_uRozmiarW = m_uLiczbaZad*m_uLiczbaDrzew;
    m_uRozmiarK = LiczbaK;
    m_ppnTablica = new int* [m_uRozmiarW];
    for (unsigned i = 0; i<m_uRozmiarW; i++)
        m_ppnTablica[i] = new int [m_uRozmiarK+1];
}
CDrzewa::~CDrzewa() {
    for (unsigned i = 0; i<m_uRozmiarW; i++)
        delete[] m_ppnTablica[i];
    delete[] m_ppnTablica;
}
int CDrzewa::Pobierz(unsigned uIndeksW, unsigned uIndeksK) const
{
    if (uIndeksW < m_uRozmiarW and uIndeksK < m_uRozmiarK+1) return m_ppnTablica[uIndeksW][uIndeksK];
    else return 0;
}
unsigned CDrzewa::RozmiarW() const {return m_uRozmiarW;}
unsigned CDrzewa::RozmiarK() const {return m_uRozmiarK;}
unsigned CDrzewa::LiczbaDrzew() const {return m_uLiczbaDrzew;}
bool CDrzewa::WladujDrzewa(string sTREE, string sSPEC)
{
    unsigned numerLinii = 1;
    int wiersz = 0;
    fstream file(sTREE.c_str(), ios::in);
    fstream spec(sSPEC.c_str(), ios::in);
    for (unsigned i = 0; i<(m_uRozmiarW/m_uLiczbaDrzew); i++){
        for (unsigned j = 0; j<m_uLiczbaDrzew; j++){
            for (unsigned k = 0; k<m_uRozmiarK; k++){
                file >> m_ppnTablica[wiersz][k];
            }
            spec >> m_ppnTablica[wiersz][m_uRozmiarK]; //do tabeli z drzewami wrzucamy od razu liczbe potrzebnych slotow z pliku .spec dla danego drzewa
            wiersz++;
        }
        numerLinii = numerLinii + 1000;
        GotoLine(file, numerLinii);
        GotoLine(spec, numerLinii);
    }
    file.close();
    spec.close();
    return true;
}
