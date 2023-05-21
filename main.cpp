#include <iostream>
#include <iomanip>
#include <conio.h>
#include <vector>
#include <sstream>
#include "ConsoleColor.h"

#define YELLOW "\x1b[33m"
#define COLS 120
#define T_SU 72
#define T_GIU 80
#define INVIO 13

using namespace std;

void stampaCaratteri(char c, int n) {
    for (int i = 0; i < n; i++) {
        cout << c;
    }
}

void centra(const string &str) {
    int len;
    len = str.length();
    stampaCaratteri(' ', (COLS - len) / 2);
    cout << str << endl;
}

void centra(int len) {
    stampaCaratteri(' ', (COLS - len) / 2);
}

void stampaLogo() {
    printf(YELLOW);
    centra(R"(  /$$$$$$            /$$                     /$$                 /$$   /$$      /$$$$$$ )");
    centra(R"( /$$__  $$          | $$                    | $$                | $$  | $$     /$$$_  $$)");
    centra(R"(| $$  \__/  /$$$$$$ | $$  /$$$$$$$  /$$$$$$ | $$  /$$$$$$       | $$  | $$    | $$$$\ $$)");
    centra(R"(| $$       |____  $$| $$ /$$_____/ /$$__  $$| $$ /$$__  $$      | $$$$$$$$    | $$ $$ $$)");
    centra(R"(| $$        /$$$$$$$| $$| $$      | $$  \ $$| $$| $$  \ $$      |_____  $$    | $$\ $$$$)");
    centra(R"(| $$    $$ /$$__  $$| $$| $$      | $$  | $$| $$| $$  | $$            | $$    | $$ \ $$$)");
    centra(R"(|  $$$$$$/|  $$$$$$$| $$|  $$$$$$$|  $$$$$$/| $$|  $$$$$$/            | $$ /$$|  $$$$$$/)");
    centra(R"( \______/  \_______/|__/ \_______/ \______/ |__/ \______/             |__/|__/ \______/ )");
    cout << white;
}

char toUpperCase(char c) {
    if (c >= 'a' && c <= 'z') {
        c -= 'a' - 'A';
    }
    return c;
}

int stampareScelte(string head, vector<string> str) {
    char tasto;
    int scelta = 0;
    do {
        system("cls");  //pulisco console
        stampaLogo();
        cout << endl << endl;
        centra(head);
        cout << endl;
        for (int i = 0; i < str.size(); i++) {
            if (scelta == i) {
                cout << green;
                centra(">" + str[i] + "<");
                cout << white;
            } else {
                centra(str[i]);
            }
        }

        do {  //aspetto un input adatto a muovere il cursore
            tasto = getch();
            tasto = toUpperCase(tasto);
            fflush(stdin);
        } while (tasto != T_SU && tasto != T_GIU && tasto != INVIO && tasto != 'W' && tasto != 'S');

        if (tasto == T_SU || tasto == 'W') {
            scelta--;
            if (scelta < 0) {
                scelta = str.size() - 1;
            }
        }

        if (tasto == T_GIU || tasto == 'S') {
            scelta++;
            if (scelta >= str.size()) {
                scelta = 0;
            }
        }
    } while (tasto != INVIO);
    return scelta;
}

int main() {
    double cim, ind, irap = 4.82, ires;
    int scelta;
    stringstream stream;
    system("title Calcolo 4.0");
    system("mode con: cols=120 lines=30");
    scelta = stampareScelte("Quanto e' grande l'impresa?", {"Piccola", "Media"});
    if (scelta == 0) {
        cim = 45.0;
    } else {
        cim = 35.0;
    }
    scelta = stampareScelte("In che anno e' stato versato l'acconto del 20%?", {"2020", "2021", "2022", "2023"});
    switch (scelta) {
        case 0:
        case 2:
            ind = 40.0;
            break;
        case 1:
            ind = 50.0;
            break;
        case 3:
            ind = 30.0;
            break;
        default:
            ind = 0.0;
            break;
    }
    scelta = stampareScelte("Di che tipo di azienda si tratta?", {"s.r.l.", "Societa' di persone"});
    if (scelta == 0) {
        ires = 24.0;
    } else {
        ires = 0.0;
    }
    system("cls");
    stampaLogo();
    cout << endl << endl;
    if (cim + ind + (irap + ires) * ind / 100.0 <= 100.0) {
        stream << "Le percentuali sono sotto il 100%, non si applicano modifiche!";
        centra(stream.str().length());
        cout << "Le percentuali sono " << green << "sotto il 100%," << white << " non si applicano modifiche!" << endl;
    } else {
        stream << "Le percentuali superano il 100%, ridimensiono il Credito 4.0 come segue!";
        centra(stream.str().length());
        cout << "Le percentuali " << red << "superano il 100%," << white << " ridimensiono il Credito 4.0 come segue!" << endl;
        ind = (100.0 - cim) / (1.0 + (irap + ires) / 100.0);
    }
    cout << endl;

    stream.str("");
    stream << fixed << setprecision(2) << "CIM = " << cim << "%       Credito 4.0 = " << ind << "%";
    centra(stream.str().length());
    cout << fixed << setprecision(2) << "CIM = " << yellow << cim << "%" << white << "       Credito 4.0 = " << yellow << ind << "%" << white << endl;
    cout << endl;

    stream.str("");
    stream << fixed << setprecision(2) << "IRES = " << ires << "%       IRAP = " << irap << "%";
    centra(stream.str().length());
    cout << fixed << setprecision(2) << "IRES = " << yellow << ires << "%" << white << "       IRAP = " << yellow << irap << "%" << white << endl;
    cout << endl;

    stream.str("");
    stream << fixed << setprecision(2) << "LA PERCENTUALE FINALE E' DEL " << cim + ind + (irap + ires) * ind / 100.0 << "%";
    centra(stream.str().length());
    cout << fixed << setprecision(2) << "LA PERCENTUALE FINALE E' DEL " << green << cim + ind + (irap + ires) * ind / 100.0 << "%" << white << endl;
    cout << endl;

    system("PAUSE");
}