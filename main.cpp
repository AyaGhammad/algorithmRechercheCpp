#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <vector>
#include "String.h"
using namespace std;


int main() {
   /* --version 1--
    String mot1;
    String mot2;

    cout << "Mot 1 : ";
    cin >> mot1;
    cout << "Mot 2 : ";
    cin >> mot2;

    cout << "Sous-sequence : "
            << (mot1.contient(mot2) ? "Oui" : "Non") << '\n';
    cout << "Sous-chaine avec find() : "
            << (mot1.contientAvecFind(mot2) ? "Oui" : "Non") << '\n';
    */

   /* --version2--
    string mots[] = {"chat", "chien", "oiseau", "poisson"};
    int nombreMots = 4;

    string recherche;

    cout << "Mot a rechercher : ";
    cin >> recherche;

    bool trouve = false;

    for (int i = 0; i < nombreMots; ++i) {
        if (mots[i] == recherche) {
            trouve = true;
            break;
        }
    }

    if (trouve) {
        cout << "Mot trouve." << endl;
    } else {
        cout << "Mot non trouve." << endl;
    }
    */
    /*
    Ancienne version : recherche dans un petit vecteur de 10 mots.
    Elle est conservee uniquement comme exemple, mais n'est plus utilisee.
    vector<String> mots = {
        String("programmation"), String("computer"),
        String("virtualisation"), String("code"), String("objet"),
        String("compilation"), String("conception"), String("hardware"),
        String("software"), String("modelisation")
    };
    */

    /*
    Ancienne version : recherche dans le fichier de 10 000 mots.
    Cette configuration n'est pas utilisée pour la version actuelle.
    constexpr size_t nombreMotsAttendus = 10000;
    ifstream fichier("mots_10000.txt");
    */

    // Version active : recherche dans le fichier mots_1000000.txt.
    constexpr size_t nombreMotsAttendus = 1000000;
    vector<String> mots;
    mots.reserve(nombreMotsAttendus);

    ifstream fichier("lorem_1_million_words.txt");
    if (!fichier) {
        cerr << "Erreur : impossible d'ouvrir le fichier mots_1000000.txt."
             << endl;
        return 1;
    }

    String mot;
    while (fichier >> mot) {
        mots.push_back(mot);
    }
    fichier.close();

    if (mots.size() != nombreMotsAttendus) {
        cerr << "Erreur : le fichier doit contenir exactement "
             << nombreMotsAttendus << " mots, mais il en contient "
             << mots.size() << "." << endl;
        return 1;
    }

    String recherche;

    cout << "Mot a rechercher : ";
    cin >> recherche;

    // 10 repetitions limitent le temps d'execution sur 1 000 000 de mots.
    constexpr int repetitions = 10;
    bool trouveContient = false;
    volatile int confirmationsContient = 0;
    const auto debutContient = chrono::steady_clock::now();

    for (int repetition = 0; repetition < repetitions; ++repetition) {
        trouveContient = false;
        for (const String& mot : mots) {
            if (mot.contient(recherche)) {
                trouveContient = true;
                break;
            }
        }
        if (trouveContient) {
            ++confirmationsContient;
        }
    }

    const auto finContient = chrono::steady_clock::now();
    const auto dureeContient =
        chrono::duration_cast<chrono::microseconds>(finContient - debutContient);

    bool trouveContientConsecutive = false;
    volatile int confirmationsContientConsecutive = 0;
    const auto debutContientConsecutive = chrono::steady_clock::now();

    for (int repetition = 0; repetition < repetitions; ++repetition) {
        trouveContientConsecutive = false;
        for (const String& mot : mots) {
            if (mot.contientConsecutive(recherche)) {
                trouveContientConsecutive = true;
                break;
            }
        }
        if (trouveContientConsecutive) {
            ++confirmationsContientConsecutive;
        }
    }

    const auto finContientConsecutive = chrono::steady_clock::now();
    const auto dureeContientConsecutive =
        chrono::duration_cast<chrono::microseconds>(
            finContientConsecutive - debutContientConsecutive);

    const auto debutFind = chrono::steady_clock::now();
    volatile int confirmationsFind = 0;
    for (int repetition = 0; repetition < repetitions; ++repetition) {
        bool trouveAvecFind = false;
        for (const String& mot : mots) {
            if (mot.contientAvecFind(recherche)) {
                trouveAvecFind = true;
                break;
            }
        }
        if (trouveAvecFind) {
            ++confirmationsFind;
        }
    }
    const auto finFind = chrono::steady_clock::now();
    const auto dureeFind =
        chrono::duration_cast<chrono::microseconds>(finFind - debutFind);

    const bool trouveFind = confirmationsFind > 0;

    cout << "Recherche avec contient() : "
         << dureeContient.count() << " us, "
         << dureeContient.count() / repetitions
         << " us - "
         << (trouveContient ? "Mot trouve." : "Mot non trouve.") << endl;
    cout << "Recherche avec contientConsecutive() : "
         << dureeContientConsecutive.count() << " us, "
         << dureeContientConsecutive.count() / repetitions
         << " us - "
         << (trouveContientConsecutive
                 ? "Mot trouve."
                 : "Mot non trouve.")
         << endl;
    cout << "Recherche avec find() : "
         << dureeFind.count() << " us, "
         << dureeFind.count() / repetitions
         << " us - "
         << (trouveFind ? "Mot trouve." : "Mot non trouve.") << endl;

    return 0;
}
