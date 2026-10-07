#ifndef STRING_H
#define STRING_H
using namespace std;
#include <string>

class String {
public:
    String() = default;
    explicit String(const string& mot);
    bool contient(const String& recherche) const;
    bool contientConsecutive(const String& recherche) const;
    bool contientAvecFind(const String& recherche) const;
    friend istream& operator>>(istream& in, String& texte);
private:
    string mot;
};

#endif
