#ifndef scenariusze_hpp
#define scenariusze_hpp
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
extern string NET, DEM, DMC, PAT, TREE, SPEC;
extern unsigned LiczbaScenariuszy, LiczbaSciezek, LiczbaDrzew;

class CScenariusze
{
private:
    string* m_pnScenariusze;
    unsigned m_uLiczbaScen;
public:
    CScenariusze();
    bool Wypelnij();
    void PodajPliki(unsigned uIndeksScen);
    string KodScenariusza(unsigned uIndeksScen);

};

#endif // scenariusze_hpp
