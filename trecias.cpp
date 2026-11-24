#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
 
int main() {
 
    int pasirinkimas;

    const int max = 100;

    string kategorijos[max];
    string pavadinimai[max];
    double kainos[max];
    int kiekiai[max];

    cout << fixed << setprecision(2);

 //nuo algoritmu iki funkciju, funkcijos ne//
 //paprastieji duomenu tipai nieko//
    
    ifstream fin("uzsakymas.txt");

    if (!fin.is_open()) {
        cout << "Uzsakymo failas neatsidare, del klaidos." << endl;
        return 1;
    }

    int eiluciuKiekis;
    fin >> eiluciuKiekis;

    char skirtukas;
    string eiluciuLiekana;

    getline(fin, eiluciuLiekana);

    for (int i = 0; i < eiluciuKiekis; i++) {
        getline(fin, kategorijos[i], ';');
        getline(fin, pavadinimai[i], ';');
        fin >> kainos[i];
        fin.ignore();
        fin >> kiekiai[i];
        getline(fin, eiluciuLiekana);
    }
    




    do {
        cout << "Sveiki, pasirinkite funkcija:" << endl;
        cout << "1. Perziureti visas uzsakymo prekes" << endl;
        cout << "2. Perziureti pasirinktos kategorijos prekes" << endl;
        cout << "3. Perziureti viso uzsakymo sumas" << endl;
        cout << "4. Perziureti sumas pagal kategorijas" << endl;
        cout << "5. Parodyti visa uzsakymo ataskaita" << endl;
        cout << "6. Issaugoti visa ataskaita i faila" << endl;
        cout << "7. Iseiti" << endl;
        cout << "Jusu pasirinkimas: ";
        cin >> pasirinkimas;

        // Neteisingas //
        if (pasirinkimas < 1 || pasirinkimas > 7) {
            cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 7." << endl;
        }

        // Pabaiga //
        if (pasirinkimas == 7) {
            cout << "Grazios dienos." << endl;
            return 0;
        }
        
        if (pasirinkimas == 1) {

        }







    } while (pasirinkimas != 7);

    return 0;
}