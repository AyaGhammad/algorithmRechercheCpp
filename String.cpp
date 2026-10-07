#include "String.h"
using namespace std;

String::String(const string& mot) : mot(mot) {}

bool String::contient(const String& recherche) const {
    size_t j = 0;
    for (char c : mot) {
        if (j < recherche.mot.size() && c == recherche.mot[j]) {
            ++j;
            if (j == recherche.mot.size()) {
                return true;
            }
        }
    }
    return false;
}

bool String::contientConsecutive(const String& recherche) const {
    if (recherche.mot.empty()) {
        return true;
    }

    if (recherche.mot.size() > mot.size()) {
        return false;
    }

    for (size_t i = 0; i <= mot.size() - recherche.mot.size(); ++i) {
        bool trouve = true;
        for (size_t j = 0; j < recherche.mot.size(); ++j) {
            if (mot[i + j] != recherche.mot[j]) {
                trouve = false;
                break;
            }
        }
        if (trouve) {
            return true;
        }
    }
    return false;
}

bool String::contientAvecFind(const String& recherche) const {
    return mot.find(recherche.mot) != string::npos;
}

istream& operator>>(istream& in, String& leMot) {
    in >> leMot.mot;
    return in;
}