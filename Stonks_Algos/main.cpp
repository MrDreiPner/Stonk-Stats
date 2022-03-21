#include <iostream>
#include <assert.h>
#include <fstream>
#include "aktie.h"

using namespace std;

void getLine(ifstream& bigStonk, int var);
int64_t poti(int n);
int64_t Hash(string name);

int main(){

    Aktie hashTabelle[2011];
    string selAktKuerzel = "0";
    string csvCall = "../CSV/"+selAktKuerzel+".csv";
    char input = '\0';
    while(input != 'q'){
        if(selAktKuerzel != "0"){
            cout << "\nCurrently selected Stock => " << selAktKuerzel << endl;
        }
        cout << "What do you want to do?\nADD (a), DEL (d), IMPORT (i), SEARCH (s), PLOT (p), SAVE (c), LOAD (v), QUIT (q): " << endl;
        cin >> input;
        switch(input){
            case 'a':{
                string aktienName;
                cout << "Aktienname: " << endl;
                cin >> aktienName;
                string aktienKuerzel;
                cout << "Aktienkuerzel: " << endl;
                cin >> aktienKuerzel;
                string WKN;
                cout << "WKN: " << endl;
                cin >> WKN;
                int64_t hashWert = Hash(aktienKuerzel);
                int64_t emptyCheck = 0;
                while(hashTabelle[hashWert].getHashWert() != emptyCheck){
                    hashWert = (hashWert * hashWert) % 2011;
                }
                hashTabelle[hashWert].setAktienName(aktienName);
                hashTabelle[hashWert].setAktienKuerzel(aktienKuerzel);
                hashTabelle[hashWert].setWKN(WKN);
                hashTabelle[hashWert].setHashWert(hashWert);
            }
            break;
            case 'd':{

            }
            break;
            case 'i':{

            }
            break;
            case 's':{
                cout << "Aktienkuerzel nach dem Sie suchen: " << endl;
                cin >> selAktKuerzel;
                cout << "AktienName nach dem Sie suchen: " << endl;
                string selAktName;
                cin >> selAktName;
                int64_t hashWert = Hash(selAktKuerzel);
                if(hashTabelle[hashWert].getHashWert() == 0){
                    selAktKuerzel = "0";
                    cout << "Stock not found. Please add it before searching for it!" << endl;
                }
                else if(hashTabelle[hashWert].getAktienName() != selAktName){
                    while(hashTabelle[hashWert].getAktienName() != selAktName){
                        hashWert = (hashWert * hashWert) % 2011;
                        if(hashTabelle[hashWert].getHashWert() == 0){
                            selAktKuerzel = "0";
                            cout << "Stock not found at new place. Please add it before searching for it!" << endl;
                        }
                    }
                    if(selAktKuerzel != "0"){
                        csvCall = "../CSV/"+selAktKuerzel+".csv";
                        ifstream bigStonk(csvCall);
                        if(!bigStonk.is_open()) cout << "Fucky Wucky" << endl;
                        cout << hashTabelle[hashWert].getAktienName() << endl;
                        cout << hashTabelle[hashWert].getAktienKuerzel() << endl;
                        cout << hashTabelle[hashWert].getWKN() << endl;
                        cout << hashTabelle[hashWert].getHashWert() << endl;
                        getLine(bigStonk, 0);
                        getLine(bigStonk, 1);
                    }
                }
                else{
                    csvCall = "../CSV/"+selAktKuerzel+".csv";
                    ifstream bigStonk(csvCall);
                    if(!bigStonk.is_open()) cout << "Fucky Wucky" << endl;
                    cout << hashTabelle[hashWert].getAktienName() << endl;
                    cout << hashTabelle[hashWert].getAktienKuerzel() << endl;
                    cout << hashTabelle[hashWert].getWKN() << endl;
                    cout << hashTabelle[hashWert].getHashWert() << endl;
                    getLine(bigStonk, 0);
                    getLine(bigStonk, 1);
                }
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
            case 'q':continue;
            break;
            default: cout << "\nInvalid Input!" << endl;
        }
    }

    ifstream bigStonk(csvCall);
    if(!bigStonk.is_open()) cout << "Fucky Wucky" << endl;
    getLine(bigStonk, 0);
    while(bigStonk.good()){
        getLine(bigStonk, 1);
    }
    cout << "#____________________________________________________________________________________#" << endl;
    string hashi = "MSFT";
    cout << "\n Hash test: \n" << endl;
    int64_t hashed = Hash(hashi);
    cout << hashed << endl;
    return 0;
}


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

int64_t Hash(string name){ //max 30 Zeichen
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
