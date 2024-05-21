//
// Created by jordir
//

#include "eines.h"

vector<string> tokens(const string& s, char separador, bool cometes) {
    vector<string> resultat;
    if (!s.empty()) {
        long primer = 0, ultim = 0;
        while (ultim != string::npos) {
            resultat.push_back(token(s, separador, cometes, primer, ultim));
        }
    }
    return resultat;
}

string token(const string& s, char separador, bool cometes, long& primer, long& ultim) {
    string t;

    if (!cometes || s[primer] != '"') { // No volem tenir en compte les " o no comença per "
        while (s[primer] == ' ' && primer < s.length()) { // ens  mengem els espais inicials si no hi ha cometes
            primer++;
        }
        ultim = s.find(separador, primer);
        if (ultim == string::npos) {
            t = s.substr(primer);
        }
        else {
            t = s.substr(primer, ultim - primer);
            primer = ultim + 1; // ens mengem la ,
        }
    } else { // comença per " i les volem tenir en compte com a delimitadors
        primer++;
        ultim = s.find('"', primer);
        while (s.length() > ultim + 1 && s[ultim + 1] == '"') {
            ultim = s.find('"', ultim + 2); // saltem "" (cometes dobles seguides)
        }
        if (ultim == string::npos) {
            throw ("cometes no tancades");
        }
        else {
            t = s.substr(primer, ultim - primer);
            primer = ultim + 2; // ens mengem els ",
            if (primer > s.length()) {
                ultim = string::npos; //era l'últim token
            }
        }
    }
    return t;
}