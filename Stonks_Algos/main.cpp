#include <iostream>
#include <assert.h>
#include <fstream>
#include <conio.h>
#include "aktie.h"

using namespace std;

void getLine(ifstream& bigStonk, int var);
int64_t poti(int n);
int64_t Hash(string name);

void printLastCSV(ifstream& bigStonk, Aktie hashTabelle){
    if(!bigStonk.is_open()) cout << "Fucky Wucky" << endl;
    cout << "Aktienname: " << hashTabelle.getAktienName() << endl;
    cout << "Aktienkuerzel: " << hashTabelle.getAktienKuerzel() << endl;
    cout << "WKN: " << hashTabelle.getWKN() << endl;
    cout << "Hashwert: " << hashTabelle.getHashWert() << endl;
    getLine(bigStonk, 0);
    getLine(bigStonk, 2);
    cout << "#____________________________________________________________________________________#" << endl;
}

int main(){

    Aktie hashTabelle[2011];
    string selAktKuerzel = "0";
    string csvCall = "../CSV/"+selAktKuerzel+".csv";
    int64_t hashWert = 0;
    char input = '\0';
    while(input != 'q'){
        system("CLS");
        if(selAktKuerzel != "0"){
            cout << "Aktuell hinterlegte Aktie => " << hashTabelle[hashWert].getAktienName() << endl;
        }
        cout << "Was wollen Sie machen?\nADD (a), DEL (d), IMPORT (i), SEARCH (s), PLOT (p), SAVE (c), LOAD (v), QUIT (q): " << endl;
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
                hashWert = Hash(aktienKuerzel);
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
                if(selAktKuerzel == "="){
                    cout << "Keine Aktie ausgewaehlt. Bitte mit SEARCH eine Aktie zum importieren aussuchen!" << endl;
                }
                else{
                    ifstream bigStonk(csvCall);
                    if(selAktKuerzel != "0"){
                        if(!bigStonk.is_open()) cout << "Fucky Wucky" << endl;
                        getLine(bigStonk, 0);
                        while(bigStonk.good()){
                            getLine(bigStonk, 1);
                    }
                    cout << "#____________________________________________________________________________________#" << endl;
                    bigStonk.close();
                    /*cout << "\n Hash test: \n" << endl;
                    int64_t hashed = Hash(selAktKuerzel);
                    cout << selAktKuerzel << endl;
                    cout << hashed << endl;*/
                    }
                }

            }
            break;
            case 's':{
                cout << "Aktienkuerzel nach dem Sie suchen: " << endl;
                cin >> selAktKuerzel;
                cout << "AktienName nach dem Sie suchen: " << endl;
                string selAktName;
                cin >> selAktName;
                hashWert = Hash(selAktKuerzel);
                if(hashTabelle[hashWert].getHashWert() == 0){
                    selAktKuerzel = "0";
                    cout << "Aktie nicht gefunden!" << endl;
                }
                else if(hashTabelle[hashWert].getAktienName() != selAktName){
                    while(hashTabelle[hashWert].getAktienName() != selAktName){
                        hashWert = (hashWert * hashWert) % 2011;
                        if(hashTabelle[hashWert].getHashWert() == 0){
                            selAktKuerzel = "0";
                            cout << "Aktie nicht gefunden! Tiefe Suche." << endl;
                            break;
                        }
                    }
                    if(selAktKuerzel != "0"){
                        csvCall = "../CSV/"+selAktKuerzel+".csv";
                        ifstream bigStonk(csvCall);
                        printLastCSV(bigStonk, hashTabelle[hashWert]);
                        bigStonk.close();
                    }
                }
                else{
                    csvCall = "../CSV/"+selAktKuerzel+".csv";
                    ifstream bigStonk(csvCall);
                    printLastCSV(bigStonk, hashTabelle[hashWert]);
                    bigStonk.close();
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
        cout << "To continue press any button" << endl;
        getch();
    }
    return 0;
}


void getLine(ifstream& bigStonk, int var){
    if(var == 2){                                       //Looks for the last line when called in a search
        bigStonk.seekg(-1,ios_base::end);
        int loop = 1;
        while(loop) {
            char ch;
            bigStonk.get(ch);                            // Get current byte's data

            if((int)bigStonk.tellg() <= 1){             // If the data was at or before the 0th byte
                bigStonk.seekg(0);                       // The first line is the last line
                loop = 0;                               // So stop there
            }
            else if(ch == '\n') {                       // If the data was a newline
                loop = 0;                               // Stop at the current position.
            }
            else {                                      // If the data was neither a newline nor at the 0 byte
                bigStonk.seekg(-2,ios_base::cur);        // Move to the front of that data, then to the front of the data before it
            }
        }
    }
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
        cout << "   " << date << "    |    " << open << "    |    " << high << "    |     " << low << "    |    " << close << "   |  " << adjClose << " |  " << volume << "\n";
    else
        cout << date << " | " << open << " | " << high << " | " << low << " | " << close << " | " << adjClose << " | " << volume << "\n";
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
