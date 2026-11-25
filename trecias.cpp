#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

// Sk. dabartines eilutes suma//
double eilutesSuma(double kaina, int kiekis) {
    double kiekiokaina = kaina * kiekis;
    return kiekiokaina;
}
 
//Kokio dydzio, jeigu is viso, nuolaida?//
double galimaNuolaida(double sumanuolaida, int kiekis) {
    if (kiekis >= 10) {
        return sumanuolaida * 0.10;
    }
    return 0;
}

double sumaPriesNuolaidas(double kainos[], int kiekiai[], int prekiuKiekis) {
    double viskoPriesNuolaidaSuma = 0;
    for (int i = 0; i < prekiuKiekis; i++) {
        viskoPriesNuolaidaSuma += eilutesSuma(kainos[i], kiekiai[i]);
    }
    return viskoPriesNuolaidaSuma;
}


double viskoNuolaida(double kainos[], int kiekiai[], int prekiuKiekis) {
    double visosNuolaidos = 0;
    for (int i = 0; i < prekiuKiekis; i++)
    {
        double eilute = eilutesSuma(kainos[i], kiekiai[i]);
        visosNuolaidos += galimaNuolaida(eilute, kiekiai[i]);
    }
    return visosNuolaidos;
}

//Kiek konkreti kategorija kainuoja//
double kategorijosSuma(string kategorijos[], double kainos[], int kiekiai[], int prekiuKiekis, string kategorija) {
    double kategorijosViskas = 0;
    for (int i = 0; i < prekiuKiekis; i++) {
        if (kategorijos[i] == kategorija) {
            double eilute = eilutesSuma(kainos[i], kiekiai[i]);
            kategorijosViskas += eilute - galimaNuolaida(eilute, kiekiai[i]);
            }
        }
        return kategorijosViskas;
}


void spausdintiAtaskaita(ostream& out, string kategorijos[], string pavadinimai[], double kainos[], int kiekiai[], int prekiuKiekis) {
    out << fixed << setprecision(2);
    out << "--------------------------------------------------------------------------------------------------------------------------------------------------------"<< endl;

    //Spausdintuvas 9000//

    for (int i = 0; i < prekiuKiekis; i++) {
        double suma = eilutesSuma(kainos[i], kiekiai[i]);
        double nuolaida = galimaNuolaida(suma, kiekiai[i]);
            out << kategorijos[i] << " | "
            << pavadinimai[i] << " | "
            << "Kaina: " << kainos[i] << " Eur | "
            << "Kiekis: " << kiekiai[i] << " | "
            << "Suma: " << suma << " Eur | "
            << "Nuolaida: " << nuolaida << " Eur | "
            << "Moketi: " << suma - nuolaida << " Eur" << endl;
    }
    out << "--------------------------------------------------------------------------------------------------------------------------------------------------------"<< endl;
    out << endl;

    double visaSuma = sumaPriesNuolaidas(kainos, kiekiai, prekiuKiekis);
    double visaNuolaida = viskoNuolaida(kainos, kiekiai, prekiuKiekis);

    out << "Suma pries nuolaidas: " << visaSuma << " Eur" << endl;
    out << "Pritaikyta nuolaidu: " << visaNuolaida << " Eur" << endl;
    out << "Galutine suma: " << visaSuma - visaNuolaida << " Eur" << endl << endl;

    out << "Kategoriju suma:" << endl;
    out << "Dviraciai: " << kategorijosSuma(kategorijos, kainos, kiekiai, prekiuKiekis, "Dviraciai") << " Eur" << endl;
    out << "Dalys: " << kategorijosSuma(kategorijos, kainos, kiekiai, prekiuKiekis, "Dalys") << " Eur" << endl;
    out << "Aksesuarai: " << kategorijosSuma(kategorijos, kainos, kiekiai, prekiuKiekis, "Aksesuarai") << " Eur" << endl << endl;
}

bool tinkamaKategorija(string kategorija) {
    if (kategorija == "Dviraciai" || kategorija == "Dalys" || kategorija == "Aksesuarai") {
        return true;
    }
    return false;
}

int duomenuSkaitytojas(string kategorijos[], string pavadinimai[], double kainos[], int kiekiai[]) {
    ifstream fin("uzsakymas.txt");

    if (!fin.is_open()) {
        cout << "Failas neatsidare, del kazkokios klaidos." << endl;
        return 0;
    }

    int eiluciuKiekis;
    fin >> eiluciuKiekis;

    if (fin.fail() || eiluciuKiekis < 1 || eiluciuKiekis > 100) {
        cout << "Irasu skaicius turi buti nuo 1 iki 100." << endl;
        return 0;
    }

    string eiluciuLiekana;
    getline(fin, eiluciuLiekana);

    for (int i = 0; i < eiluciuKiekis; i++) {
        getline(fin, kategorijos[i], ';');
        getline(fin, pavadinimai[i], ';');
        fin >> kainos[i];
        fin.ignore();
        fin >> kiekiai[i];

        if (fin.fail()) {
            cout << "Ivyko klaida failo skaityme." << endl;
            return 0;
        }

        getline(fin, eiluciuLiekana);

        if (!tinkamaKategorija(kategorijos[i])) {
            cout << "Prekes kategorija netinkama." << endl;
            return 0;
        }

        if (kainos[i] <= 0) {
            cout << "Prekes kaina turi buti teigiama." << endl;
            return 0;
        }

        if (kiekiai[i] <= 0) {
            cout << "Prekes kiekis turi buti teigiamas." << endl;
            return 0;
        }
    }

    fin.close();
    return eiluciuKiekis;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
 
    int pasirinkimas;

    const int max = 100;

    string kategorijos[max];
    string pavadinimai[max];
    double kainos[max];
    int kiekiai[max];

    double suma;
    double nuolaida;

    cout << fixed << setprecision(2);

 //kontrolinis//
 //nuo algoritmu iki funkciju, funkcijos ne//
 //paprastieji duomenu tipai nieko//

  int eiluciuKiekis = duomenuSkaitytojas(kategorijos, pavadinimai, kainos, kiekiai);

    if (eiluciuKiekis == 0) {
        cout << "Duomenys nenuskaityti. Klaida su failo skaitymu." << endl;
        return 1;
    }


    do {
        cout << "Sveiki, pasirinkite funkcija:" << endl;
        cout << "1. Perziureti visas uzsakymo prekes" << endl;
        cout << "2. Perziureti pasirinktos kategorijos prekes" << endl;
        cout << "3. Perziureti viso uzsakymo sumas" << endl;
        cout << "4. Perziureti sumas pagal kategorijas" << endl;
        cout << "5. Parodyti visa uzsakymo ataskaita" << endl;
        cout << "6. Issaugoti visa ataskaita i faila" << endl;
        cout << "7. Iseiti" << endl << endl;
        cout << "Jusu pasirinkimas: ";
        cin >> pasirinkimas;
        cout << endl;

        // Neteisingas //
        if (cin.fail() || pasirinkimas < 1 || pasirinkimas > 7) {
            cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 7." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // Pabaiga //
        if (pasirinkimas == 7) {
            return 0;
        }
        
        //

        if (pasirinkimas == 1) {
            for (int i = 0; i < eiluciuKiekis; i++) {
                suma = eilutesSuma(kainos[i], kiekiai[i]);
                nuolaida = galimaNuolaida(suma, kiekiai[i]);

                cout << " | " << kategorijos[i] << " | "
                     << pavadinimai[i] << " | "
                     << kainos[i] << " Eur | "
                     << kiekiai[i] << " vnt. | "
                     << suma << " Eur | "
                     << nuolaida << " Eur | "
                     << suma - nuolaida << " Eur" << endl;

            }
            cout << endl;

        }

        if (pasirinkimas == 2) {
            int katPasirinkimas;
            string pasirinktaKategorija;

            do {
                cout << endl;
                cout << "Pasirinkite kategorija:" << endl;
                cout << "1. Dviraciai" << endl;
                cout << "2. Dalys" << endl;
                cout << "3. Aksesuarai" << endl;
                cout << "Jusu pasirinkimas: ";
                cin >> katPasirinkimas;
                
                //Neteisingas//

                if (cin.fail() || katPasirinkimas < 1 || katPasirinkimas > 3) {
                    cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 3." << endl << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }

            } while (katPasirinkimas < 1 || katPasirinkimas > 3);

            if (katPasirinkimas == 1) {
                pasirinktaKategorija = "Dviraciai";
            } else if (katPasirinkimas == 2) {
                pasirinktaKategorija = "Dalys";
            } else {
                pasirinktaKategorija = "Aksesuarai";
            }

            //Kategorijos prekiu spausdintuvas

            for (int i = 0; i < eiluciuKiekis; i++) {
                if (kategorijos[i] == pasirinktaKategorija) {
                    suma = eilutesSuma(kainos[i], kiekiai[i]);
                    nuolaida = galimaNuolaida(suma, kiekiai[i]);

                    cout << " | " << kategorijos[i] << " | "
                         << pavadinimai[i] << " | "
                         << kainos[i] << " Eur | "
                         << kiekiai[i] << " vnt. | "
                         << suma << " Eur | "
                         << nuolaida << " Eur | "
                         << suma - nuolaida << " Eur" << endl;
                }
            }

            suma = kategorijosSuma(kategorijos, kainos, kiekiai, eiluciuKiekis, pasirinktaKategorija);

            if (suma == 0) {
                cout << "Sios kategorijos prekiu nera." << endl << endl;
            } else {
                cout << "Suma uz visa kategorija: " << suma << " Eur" << endl << endl;
            }
        }

        if (pasirinkimas == 3) {
            suma = sumaPriesNuolaidas(kainos, kiekiai, eiluciuKiekis);
            nuolaida = viskoNuolaida(kainos, kiekiai, eiluciuKiekis);

            cout << "Suma pries nuolaidas: " << suma << " Eur" << endl;
            cout << "Pritaikyta nuolaidu: " << nuolaida << " Eur" << endl;
            cout << "Galutine suma: " << suma - nuolaida << " Eur" << endl << endl;
        }

        if (pasirinkimas == 4) {
            cout << "Dviraciai: " << kategorijosSuma(kategorijos, kainos, kiekiai, eiluciuKiekis, "Dviraciai") << " Eur" << endl;
            cout << "Dalys: " << kategorijosSuma(kategorijos, kainos, kiekiai, eiluciuKiekis, "Dalys") << " Eur" << endl;
            cout << "Aksesuarai: " << kategorijosSuma(kategorijos, kainos, kiekiai, eiluciuKiekis, "Aksesuarai") << " Eur" << endl << endl;
        }

        if (pasirinkimas == 5) {
            spausdintiAtaskaita(cout, kategorijos, pavadinimai, kainos, kiekiai, eiluciuKiekis);
            cout << endl;
        }

        if (pasirinkimas == 6) {
        ofstream fout("ataskaita.txt");

            if (!fout.is_open()) {
                cout << "Nutiko klaida, nepavyko sukurti failo ataskaita.txt." << endl << endl;
            } else {
                spausdintiAtaskaita(fout, kategorijos, pavadinimai, kainos, kiekiai, eiluciuKiekis);
                fout.close();

                if (fout.fail()) {
                    cout << "Nutiko klaida, nepavyko irasyti ataskaitos." << endl << endl;
                } else {
                    cout << "Ataskaita issaugota faile ataskaita.txt." << endl << endl;
                }
            }
        }

    } while (pasirinkimas != 7);

    return 0;
}