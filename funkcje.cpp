#include "funkcje.hpp"

void ParametryGrafu(string sNET, string sDEM, string sDMC)
{
    ifstream NET(sNET.c_str(), ios::in);
    NET >> LiczbaW;
    NET >> LiczbaK;
    NET.close();
    ifstream DEM(sDEM.c_str(), ios::in);
    DEM >> LiczbaUni;
    DEM.close();
    ifstream DMC(sDMC.c_str(), ios::in);
    DMC >> LiczbaMulti;
    DMC.close();
}


fstream& GotoLine(fstream& file, unsigned int num){
    file.seekg(ios::beg);
    for(unsigned i=0; i < num - 1; ++i){
        file.ignore(numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

bool SprawdzCzyJest(vector<int> vWylosowane, int nLiczba)
{
    if (vWylosowane.size() == 0 ) return false;
    else{
        for (unsigned i= 0; i<vWylosowane.size(); i++){
            if (vWylosowane[i] == nLiczba) return true;
        }
    }
    return false;
}
