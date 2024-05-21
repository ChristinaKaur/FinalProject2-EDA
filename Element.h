/// Christina Kaur Krishan
/// Usuari u1980983
/// Pràctica 1

#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <list>
#include <sstream>
#include <map>
#include <set>
#include <fstream>

#include "Linia.h"
#include "eines.h"
const char DESPESA = 'D';
const char INGRES = 'I';
using namespace std;

class Element {
public:
    Element();
    ///< Pre: --
    ///< Post: constructor per defecte

    Element(char id, string codi, string descrip);
    ///< Pre: --
    ///< Post: constructor per parametres

    void inserir_desc(const string descrip);
    ///< Pre: cert
    ///< Post: incereix nova descrip a l'element

    bool operator>(const Element e);
    ///< Pre: --
    ///< Post: retorna si this es mes gran que e

    string codi() const;
    ///< Pre: --
    ///< Post: retorna el codi de l'element

    vector<string> descrip() const;
    ///< Pre: --
    ///< Post: retorna la primera descripcio de l'element

private:
    char _id;
    string _codi;
    vector<string> _descrip;
};

#endif //ELEMENT_H
