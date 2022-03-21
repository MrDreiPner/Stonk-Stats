#ifndef AKTIE_H
#define AKTIE_H
#include <iostream>

using namespace std;

class Aktie
{
    public:
        Aktie();
        virtual ~Aktie();
        string getAktienName(){return aktienName;};
        string getAktienKuerzel(){return aktienKuerzel;};
        string getWKN(){return WKN;};
        int64_t getHashWert(){return hashWert;};
        void setAktienName(string x){aktienName = x;};
        void setAktienKuerzel(string x){aktienKuerzel = x;};
        void setWKN(string x){WKN = x;};
        void setHashWert(int64_t x){hashWert = x;};


    protected:

    private:
        string aktienName;
        string aktienKuerzel;
        string WKN;
        int64_t hashWert;

};

#endif // AKTIE_H
