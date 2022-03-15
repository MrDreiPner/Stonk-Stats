#include <iostream>
#include <assert.h>
#include <fstream>
#include "aktie.h"

using namespace std;

void getLine(ifstream& bigStonk, int var)
{
    string date;
    string open;
    string high;
    string low;
    string close;
    string adjClose;
    string volume;

    getline(bigStonk, date, ',');
    getline(bigStonk, open, ',');
    getline(bigStonk, high, ',');
    getline(bigStonk, low, ',');
    getline(bigStonk, close, ',');
    getline(bigStonk, adjClose, ',');
    getline(bigStonk, volume, '\n');
    if(var == 1)
        cout << date << " | " << open << " | " << high << " | " << low << " | " << close << " | " << adjClose << " | " << volume << "\n";
    else
        cout << "   " << date << "    |    " << open << "    |    " << high << "    |     " << low << "    |    " << close << "   |  " << adjClose << " |  " << volume << "\n";
}

int main()
{
    ifstream bigStonk("../CSV/MSFT.csv");

    if(!bigStonk.is_open()) cout << "Fucky Wucky" << endl;

    getLine(bigStonk, 0);

    while(bigStonk.good())
    {
        getLine(bigStonk, 1);
    }
    cout << "#____________________________________________________________________________________#" << endl;


    return 0;
}
