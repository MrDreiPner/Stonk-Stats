#include "aktie.h"

Aktie::Aktie()
{
   aktienName = "\0";
   aktienKuerzel = "\0";
   WKN = "\0";
   hashWert = -1;
}

Aktie::~Aktie()
{
    //dtor
}
