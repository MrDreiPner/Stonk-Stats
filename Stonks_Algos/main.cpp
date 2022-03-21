#include <iostream>
#include <assert.h>
#include <fstream>
#include "aktie.h"

using namespace std;

void getLine(ifstream& bigStonk, int var){
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

int64_t poti(int n){
    int64_t num = 3;
    for(int i = 0; i < n; i++){
        num *= 3;
    }
    return num;
}

int64_t Hash(string name){ //max 15 Zeichen
    int64_t hashed = 0;
    int64_t n = name.size();
    int64_t m = 1;
    for(int i = 0; i < n; i++){
        int64_t letter = name[i];
        hashed += letter * poti(n-m);
        hashed %= 2011;
        hashed *= name.size();
        m++;
    }
    hashed %= 2011;
    return hashed;
}

int main(){
    char input = '\0';
    while(input != 'q'){
        cout << "What do you want to do?\nADD (a), DEL (d), IMPORT (i), SEARCH (s), PLOT (p), SAVE (c), LOAD (v), QUIT (q): " << endl;
        cin >> input;
        switch(input){
            case 'a':{

            }
            break;
            case 'd':{

            }
            break;
            case 'i':{

            }
            break;
            case 's':{

            }
            break;
            case 'p':{

            }
            break;
            case 'c':{

            }
            break;
            case 'v':{

            }
            break;
            default: cout << "\nInvalid Input!" << endl;
        }
    }

    ifstream bigStonk("../CSV/MSFT.csv");
    if(!bigStonk.is_open()) cout << "Fucky Wucky" << endl;
    getLine(bigStonk, 0);
    while(bigStonk.good()){
        getLine(bigStonk, 1);
    }
    string hashi = "MSFT";
    cout << "#____________________________________________________________________________________#" << endl;
    cout << "\n Hash test: \n" << endl;
    int64_t hashed = Hash(hashi);
    cout << hashed << endl;
    return 0;
}
