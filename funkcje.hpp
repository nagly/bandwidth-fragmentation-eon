#ifndef funkcje_hpp
#define funkcje_hpp
#include <string>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

extern unsigned LiczbaW, LiczbaK, LiczbaUni, LiczbaMulti;

void ParametryGrafu(string sNET, string sDEM, string sDMC);
fstream& GotoLine(fstream& file, unsigned int num);
bool SprawdzCzyJest(vector<int> vWylosowane, int nLiczba);


#endif // funkcje_hpp
