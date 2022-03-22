#include <iostream>
#include <assert.h>
#include <fstream>
#include <conio.h>
#include "aktie.h"

using namespace std;

void getLine(ifstream& bigStonk, int var);
int createPlot(ifstream& bigStonk, int prevClose);
void printLastCSV(ifstream& bigStonk, Aktie hashTabelle);
int64_t poti(int n);
int64_t Hash(string name);


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
            cout << "Aktuelles Aktienkuerzel => " << hashTabelle[hashWert].getAktienKuerzel() << endl;
        }
        cout << "Was wollen Sie machen?\nADD (a), DEL (d), IMPORT (i), SEARCH (s), PLOT (p), SAVE (c), LOAD (v), QUIT (q): " << endl;
        cin >> input;
        switch(input){
            case 'a':{
                string aktienKuerzel;
                cout << "Aktienkuerzel: " << endl;
                cin >> aktienKuerzel;
                string aktienName;
                cout << "Aktienname: " << endl;
                cin >> aktienName;
                string WKN;
                cout << "WKN: " << endl;
                cin >> WKN;
                hashWert = Hash(aktienKuerzel);
                //Falls Werte tiefer eingesetzt wurden, wird der Platz mit 2012 markiert um die Suche tiefer voranzutreiben
                while(hashTabelle[hashWert].getHashWert() != -1 && hashTabelle[hashWert].getHashWert() != 2012){
                    hashWert = (hashWert * hashWert) % 2011;
                }
                hashTabelle[hashWert].setAktienName(aktienName);
                hashTabelle[hashWert].setAktienKuerzel(aktienKuerzel);
                hashTabelle[hashWert].setWKN(WKN);
                hashTabelle[hashWert].setHashWert(hashWert);
            }
            break;
            case 'd':{
                cout << "Zu loeschnde Aktie => Aktienkuerzel: ";
                string delAktKuerzel;
                cin >> delAktKuerzel;
                cout << "Zugehoeriger Aktienname: ";
                string delAktName;
                cin >> delAktName;
                selAktKuerzel = "0";
                hashWert = Hash(delAktKuerzel);
                if(hashTabelle[hashWert].getHashWert() == -1){
                    delAktKuerzel = "0";
                    cout << "Aktie nicht gefunden!" << endl;
                }
                else if(hashTabelle[hashWert].getAktienName() != delAktName){
                    while(hashTabelle[hashWert].getAktienName() != delAktName){
                        hashWert = (hashWert * hashWert) % 2011;
                        if(hashTabelle[hashWert].getHashWert() == -1){
                            delAktKuerzel = "0";
                            cout << "Aktie nicht gefunden! Tiefe Suche." << endl;
                            break;
                        }
                    }
                    if(delAktKuerzel != "0"){
                        hashTabelle[hashWert].setAktienKuerzel("0");
                        hashTabelle[hashWert].setAktienName("0");
                        hashTabelle[hashWert].setWKN("0");
                        hashTabelle[hashWert].setHashWert(2012);
                    }
                }
                else{
                    hashTabelle[hashWert].setAktienKuerzel("0");
                    hashTabelle[hashWert].setAktienName("0");
                    hashTabelle[hashWert].setWKN("0");
                    hashTabelle[hashWert].setHashWert(2012);
                }

            }
            break;
            case 'i':{
                if(selAktKuerzel == "0"){
                    cout << "Keine Aktie ausgewaehlt. Bitte mit SEARCH eine Aktie zum importieren aussuchen!" << endl;
                }
                else{
                    ifstream bigStonk(csvCall);
                    cout << "\nImport" << endl;
                    cout << "Aktienname => " << hashTabelle[hashWert].getAktienName() << endl;
                    cout << "Aktienkuerzel => " << hashTabelle[hashWert].getAktienKuerzel() << endl;
                    if(!bigStonk.is_open()) cout << "Fucky Wucky" << endl;
                    getLine(bigStonk, 0);
                    while(bigStonk.good()){
                            getLine(bigStonk, 1);
                    }
                    cout << "#____________________________________________________________________________________#" << endl;
                    bigStonk.close();
                }
            }
            break;
            case 's':{
                cout << "Aktienkuerzel nach dem Sie suchen: " << endl;
                cin >> selAktKuerzel;
                cout << "Aktienname nach dem Sie suchen: " << endl;
                string selAktName;
                cin >> selAktName;
                hashWert = Hash(selAktKuerzel);
                if(hashTabelle[hashWert].getHashWert() == -1){
                    selAktKuerzel = "0";
                    cout << "Aktie nicht gefunden!" << endl;
                }
                else if(hashTabelle[hashWert].getAktienName() != selAktName){
                    while(hashTabelle[hashWert].getAktienName() != selAktName){
                        hashWert = (hashWert * hashWert) % 2011;
                        if(hashTabelle[hashWert].getHashWert() == -1){
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
                if(selAktKuerzel == "0"){
                    cout << "Keine Aktie ausgewaehlt. Bitte mit SEARCH eine Aktie zum importieren aussuchen!" << endl;
                }
                else{
                    ifstream bigStonk(csvCall);
                    if(!bigStonk.is_open()) cout << "Fucky Wucky" << endl;
                    string trash;
                    getline(bigStonk,trash, '\n');
                    int prevClose = 0;
                    cout << "\nPlot" << endl;
                    cout << "Aktienname => " << hashTabelle[hashWert].getAktienName() << endl;
                    cout << "Aktienkuerzel => " << hashTabelle[hashWert].getAktienKuerzel() << endl;
                    prevClose = createPlot(bigStonk, prevClose);
                    while(bigStonk.good()){
                        prevClose = createPlot(bigStonk, prevClose);
                    }
                    cout << endl;
                    cout << "\n_ <= Plateau\n\\ <= Niedriger\n/ <= Hoeher" << endl;
                    bigStonk.close();
                }
            }
            break;
            case 'c':{
                cout << "SPEICHERN\nFilename eingeben (OHNE .csv): " << endl;
                string fileName;
                cin >> fileName;
                fileName = "../Saved_Files/"+fileName+".csv";
                ofstream file;
                file.open(fileName);
                for(int i = 0; i < 2011; i++){
                    if(hashTabelle[i].getHashWert() == -1)
                        continue;
                    file << hashTabelle[i].getAktienName();
                    file << ",";
                    file << hashTabelle[i].getAktienKuerzel();
                    file << ",";
                    file << hashTabelle[i].getWKN();
                    file << ",";
                    file << hashTabelle[i].getHashWert();
                    file << "\n";
                }
            }
            break;
            case 'v':{
                cout << "LADEN\nFilename eingeben (OHNE .csv): " << endl;
                string fileName;
                cin >> fileName;
                fileName = "../Saved_Files/"+fileName+".csv";
                ifstream fileIn(fileName);
                if(!fileIn.is_open()) cout << "No File found" << endl;
                else{
                    while(fileIn.good()){
                    string name;
                    string kuerzel;
                    string wkn;
                    string hashNum;
                    getline(fileIn, name, ',');
                    getline(fileIn, kuerzel, ',');
                    getline(fileIn, wkn, ',');
                    getline(fileIn, hashNum, '\n');
                    int64_t hashy = Hash(kuerzel);
                    while(hashTabelle[hashWert].getHashWert() != -1 && hashTabelle[hashWert].getHashWert() != 2012){
                        hashWert = (hashWert * hashWert) % 2011;
                    }

                    hashTabelle[hashy].setAktienName(name);
                    hashTabelle[hashy].setAktienKuerzel(kuerzel);
                    hashTabelle[hashy].setWKN(wkn);
                    hashTabelle[hashy].setHashWert(hashy);
                    }
                    cout << "Success!" << endl;
                }
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

int createPlot(ifstream& bigStonk, int prevClose){
    string trash;
    string close;

    getline(bigStonk, trash, ',');
    getline(bigStonk, trash, ',');
    getline(bigStonk, trash, ',');
    getline(bigStonk, trash, ',');
    getline(bigStonk, close, ',');
    getline(bigStonk, trash, ',');
    getline(bigStonk, trash, '\n');
    int currentClose;
    currentClose = stoi(close);
    if(currentClose == prevClose){
        cout << "_";
    }
    else if(currentClose < prevClose){
        cout << "\\";
    }
    else{
        cout << "/";
    }
    return currentClose;
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
