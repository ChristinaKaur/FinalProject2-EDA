/// Christina Kaur Krishan
/// Usuari u1980983
/// Pràctica 1

#ifndef PRESSUPOST_H
#define PRESSUPOST_H
#include "Element.h"

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

using namespace std;

const int INDEX_EXERCICI = 1;
const int INDEX_ID = 2;
const int INDEX_IMPORT = 30;
const int INDEX_CODI_CAP = 15;
const int INDEX_DES_CAP = 16;
const int INDEX_CODI_ARTICLE = 17;
const int INDEX_DES_ARTICLE = 18;
const int INDEX_CODI_CONCEPTE = 19;
const int INDEX_DES_CONCEPTE = 20;
const int INDEX_CODI_APLICACIO = 21;
const int INDEX_DES_APLICACIO = 22;

typedef map<unsigned int, map<string, pair<long long, long long>>> Resum;
typedef map<char, map<string, set<pair<string, unsigned int>>>> Discrepancies;

struct Any {
    Any() {
        ///< Pre: --
        ///< Post: constructor per defecte
        _any = 0;

        _in_des = map<char, set<Linia>>();
        _in_des[DESPESA] = set<Linia>();
        _in_des[INGRES] = set<Linia>();
    }
    Any(unsigned int any) {
        ///< Pre: --
        ///< Post: constructor per parametres
        _any = any;

        _in_des = map<char, set<Linia>>();
        _in_des[DESPESA] = set<Linia>();
        _in_des[INGRES] = set<Linia>();
    }
    unsigned int _any;
    map<char, set<Linia>> _in_des;
};

class Pressupost {
public:
    Pressupost();
    ///< Pre: --
    ///< Post: constructor per defecte

    void llegirDades(const string& path);
    ///< Pre: --
    ///< Post: llegir path i afegir les linies a pressupost actual

    bool existeixAny(int exercici) const;
    ///< Pre: --
    ///< Post: retorna si exercici existeix dins de capitols

    vector<string> obtenirCapitols(int exercici, char tipus) const;
    ///< Pre: exercici i tipus valid
    ///< Post: retorna un vector<string> amb les descripcions dels cap´ıtols d’aquest exercici i del tipus indicat

    list<pair<string, string>> obtenirArticles(int exercici, char tipus) const;
    ///< Pre: exercici i tipus valid
    ///< Post: retorna una list amb tots els articles d’aquest exercici i del tipus indicat. codi i la descripcio

    map<int, int> obtenirNLiniesAny() const;
    ///< Pre: --
    ///< Post: retorna, per cada exercici, el nombre de linies de pressupostos que tenim emmagatzemades

    pair<long long, long long> obtenirImportAny(int exercici) const;
    ///< Pre: exercici correcte
    ///< Post: retorna la suma de tots els ingressos i la suma de totes les despeses d’un exercici. Retorna els imports en centims d’euro

    pair<long long, long long> obtenirImportConcepte(int exercici, int capitol, int article, int concepte) const;
    ///< Pre: exercici correcte
    ///< Post: retorna la suma de tots els ingressos i la suma de totes les despeses d’un concepte identificat per l’any, el codi de capitol(0 - 9), el subcodi de l’article(0 - 9) i el subcodi del concepte(0 - 9).Retorna els imports en centims d’euro.

    Resum resumCapitols() const;
    ///< Pre: --
    ///< Post: retorna per cada exercici, tots els capitols identificats pel seu codi(ex. 2, 0...), i la suma dels ingressos i despeses

    Resum resumArticles() const;
    ///< Pre: --
    ///< Post: retorna per cada exercici, tots els articles identificats pel seu codi(ex. 23, 01...), i la suma dels ingressos i despeses

    Resum resumConceptes() const;
    ///< Pre: --
    ///< Post: retorna per cada exercici, tots els conceptes identificats pel seu codi(ex. 235, 010...), i la suma dels ingressos i despeses

    Resum resumAplicacions() const;
    ///< Pre: --
    ///< Post: retorna per cada exercici, totes les aplicacions identificades pel seu codi (ex. 2351234, 0103845...), i la suma dels ingressos i despeses

    Discrepancies obtenirDiscrepanciesCapitols() const;
    ///< Pre: --
    ///< Post: retorna les Discrepancies de les descripcions dels capitols al llarg dels anys(exercicis)

    Discrepancies obtenirDiscrepanciesArticles() const;
    ///< Pre: --
    ///< Post: retorna les Discrepancies de les descripcions dels articles al llarg dels anys(exercicis)

    Discrepancies obtenirDiscrepanciesConceptes() const;
    ///< Pre: --
    ///< Post: retorna les Discrepancies de les descripcions dels conceptes al llarg dels anys(exercicis)

    Discrepancies obtenirDiscrepanciesAplicacions() const;
    ///< Pre: --
    ///< Post: retorna les Discrepancies de les descripcions de les aplicacions al llarg dels anys(exercicis)

    map<string, long long> capitolsDeficitaris(int exercici) const;
    ///< Pre: exercici correcte
    ///< Post: retorna els codis dels capitols deficitaris(els capitols amb mes despeses que ingressos)

private:
    map<char, vector<Element>> _capitol;
    map<char, map<string, Element>> _article;
    map<char, map<string, Element>> _app;
    map<char, map<string, Element>> _concepte;
    map<unsigned int, Any> _linia;

    vector<string> descripcionsCapitol(const char tipus, const string codi_cap) const;
    ///< Pre: tipus i codi correcte
    ///< Post: retorna totes les descripcions guardades d'un capitol en concret

    vector<string> descripcionsArticle(const char tipus, const string codi) const;
    ///< Pre: tipus i codi correcte
    ///< Post: retorna totes les descripcions guardades d'un article en concret

    vector<string> descripcionsConcepte(const char tipus, const string codi) const;
    ///< Pre: tipus i codi correcte
    ///< Post: retorna totes les descripcions guardades d'un concepte en concret

    vector<string> descripcionsAplicacio(const char tipus, const string codi) const;
    ///< Pre: tipus i codi correcte
    ///< Post: retorna totes les descripcions guardades d'una aplicacio en concret

    int existeix(const string desc, const vector<string>& llista) const;
    ///< Pre: --
    ///< Post: retorna -1 si descripcio no existeix dins de llista, la posicio altrament
    
    void afegirCapitol(char ingresDespesa, const string& codi, const string& descripcio);
    ///< Pre: ingresDespesa correcte
    ///< Post: posa la informació del capítol a la posició codi del vector associat a la clau ingresDespesa del map<char, vector<Element>>

    void afegirArticle(char ingresDespesa, const string& codi, const string& descripcio);
    ///< Pre: ingresDespesa correcte
    ///< Post: posa la informació de l’article al map associat a la clau ingresDespesa del map<char, map<string, Element>>

    void afegirAplicacio(char ingresDespesa, const string& codi, const string& descripcio);
    ///< Pre: ingresDespesa correcte
    ///< Post: posa la informació de l’aplicació al map associat a la clau ingresDespesa del map<char, map<string, Element>>

    void afegirConcepte(char ingresDespesa, const string& codi, const string& descripcio);
    ///< Pre: ingresDespesa correcte
    ///< Post: posa la informació del concepte al map associat a la clau ingresDespesa del map<char, map<string, Element>>

    void afegirLinia(unsigned short int any, char ingresDespesa, const string& codi, long long import);
    ///< Pre:  ingresDespesa correcte
    ///< Post: afegeix la línia a l’any corresponent.La línia s’afegirà a la dada associada a la clau any del map<unsigned int, Any>. En el cas que l’any no existís, primer s’afegiria l’any a la llista d’anys del pressupost

    string descripcioCapitol(const string& codiCapitol, char ingresDespesa) const;
    ///< Pre: ingresDespesa correcte
    ///< Post: retorna la descripció corresponent al capítol codiCapitol d’ingresDespesa('D' o 'I')

    string descripcioArticle(const string& codiArticle, char ingresDespesa) const;
    ///< Pre: ingresDespesa correcte
    ///< Post: retorna la descripció corresponent a l’article codiArticle d’ingresDespesa('D' o 'I')

    string descripcioConceptes(const string& codiConcepte, char ingresDespesa) const;
    ///< Pre: ingresDespesa correcte
    ///< Post: retorna la descripció corresponent al concepte codiConcepte d’ingresDespesa('D' o 'I')

    string descripcioAplicacio(const string& codiAplicacio, char ingresDespesa) const;
    ///< Pre: ingresDespesa correcte
    ///< Post: retorna la descripció corresponent a l’aplicació amb codi codiAplicacio d’ingresDespesa ('D' o 'I')

    string centimsEuros(long long int i) const;
    ///< Pre:
    ///< Post: retorna i passat a centims i string
};
#endif