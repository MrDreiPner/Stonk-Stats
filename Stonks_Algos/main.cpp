#include <iostream>
#include <assert.h>
#include <fstream>


int main()
{
    ifstream ip("https://de.finance.yahoo.com/quote/MSFT/history?period1=1644883200&period2=1647302400&interval=1d&filter=history&frequency=1d&includeAdjustedClose=true&output=csv");

    if(!msa.is_open()) std::cout << "Fucky Wucky" << std::endl;

    string Date;
    string Open;
    string High;
    string Low;
    string Close;


    return 0;
}
