#ifndef AKTIE_H
#define AKTIE_H
#include <iostream>

using namespace std;

class aktie
{
    public:
        aktie();
        virtual ~aktie();

    protected:

    private:
        string AktienName;
        string AktienKuerzel;
        string WKN;
        string hashWert;

};

#endif // AKTIE_H
