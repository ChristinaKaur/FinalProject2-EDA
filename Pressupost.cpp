/// Christina Kaur Krishan
/// Usuari u1980983
/// Pràctica 1

#include "Pressupost.h"

Pressupost::Pressupost() {
    _capitol = map<char, vector<Element>>();
    _capitol[DESPESA] = vector<Element>(10);
    _capitol[INGRES] = vector<Element>(10);

    _article = map<char, map<string, Element>>();
    _article[DESPESA] = map<string, Element>();
    _article[INGRES] = map<string, Element>();

    _app = map<char, map<string, Element>>();
    _app[DESPESA] = map<string, Element>();
    _app[INGRES] = map<string, Element>();

    _concepte = map<char, map<string, Element>>();
    _concepte[DESPESA] = map<string, Element>();
    _concepte[INGRES] = map<string, Element>();

    _linia = map<unsigned int, Any>();
}

void Pressupost::llegirDades(const string& path) {
    /// Pre: path valid
    /// Post: llegir el fitxer a path i afegir les linies i els capitols al pressupost actual

    ifstream f;
    string linia;
    vector<string> items;

    f.open(path);
    if (!f.fail()) {
        int num_lin = 0;
        getline(f, linia);
        getline(f, linia);
        while (!f.eof()) {
            items = tokens(linia, ',', true);
            
            unsigned short int any = stoi(items[INDEX_EXERCICI]);
            long long import = stoll(items[INDEX_IMPORT]);
            char tipus = items[INDEX_ID][0];
            string codi_cap = items[INDEX_CODI_CAP],
                desc_cap = items[INDEX_DES_CAP],
                codi_article = items[INDEX_CODI_ARTICLE],
                desc_article = items[INDEX_DES_ARTICLE],
                codi_concepte = items[INDEX_CODI_CONCEPTE],
                desc_concepte = items[INDEX_DES_CONCEPTE],
                codi_aplicacio = items[INDEX_CODI_APLICACIO],
                desc_aplicacio = items[INDEX_DES_APLICACIO];

            afegirCapitol(tipus, codi_cap, desc_cap);
            afegirLinia(any, tipus, codi_aplicacio, import);
            afegirArticle(tipus,codi_article, desc_article);
            afegirConcepte(tipus, codi_concepte, desc_concepte);
            afegirAplicacio(tipus, codi_aplicacio, desc_aplicacio);
            getline(f, linia);
            num_lin++;
        }
        cout << "Numero de linies: " << num_lin-1 << endl;
    }
    else
        cout << "Path incorrecte" << endl;
}

void Pressupost::afegirCapitol(char ingresDespesa, const string& codi, const string& descripcio) {
    // Pre: ingresDespesa correcte
    // Post: Posa la informacio del cap�tol a la posici� codi del vector associat a la clau ingresDespesa del map<char, vector<Element>>
    if (!_capitol.find(ingresDespesa)->second.empty() and !_capitol.find(ingresDespesa)->second.at(stoi(codi)).descrip().empty() and existeix(descripcio, _capitol.find(ingresDespesa)->second.at(stoi(codi)).descrip()) == -1)
        _capitol.find(ingresDespesa)->second.at(stoi(codi)).inserir_desc(descripcio);
    else
        _capitol[ingresDespesa][stoi(codi)] = Element(ingresDespesa, codi, descripcio);
}

void Pressupost::afegirArticle(char ingresDespesa, const string& codi, const string& descripcio) {
    // Pre: ingresDespesa correcte
    // Post: Posa la informaci� de l�article al map associat a la clau ingresDespesa del map<char, map<string, Element>>
    if (_article.find(ingresDespesa)->second.find(codi) != _article.find(ingresDespesa)->second.end() and existeix(descripcio, _article[ingresDespesa][codi].descrip()) == -1)
        _article[ingresDespesa][codi].inserir_desc(descripcio);
    else
        _article[ingresDespesa].insert({ codi, Element(ingresDespesa, codi, descripcio) });
}

void Pressupost::afegirAplicacio(char ingresDespesa, const string& codi, const string& descripcio) {
    // Pre: ingresDespesa correcte i aplicacio correcte
    // Post: Posa la informaci� de l�aplicaci� al map associat a la clau ingresDespesa del map<char, map<string, Element>>
    if (_app.find(ingresDespesa)->second.find(codi) != _app.find(ingresDespesa)->second.end() and existeix(descripcio, _app[ingresDespesa][codi].descrip()) == -1)
        _app[ingresDespesa][codi].inserir_desc(descripcio);
    else
        _app[ingresDespesa].insert({ codi, Element(ingresDespesa, codi, descripcio) });
}

void Pressupost::afegirConcepte(char ingresDespesa, const string& codi, const string& descripcio) {
    // Pre: ingresDespesa correcte
    // Post: Posa la informaci� del concepte al map associat a la clau ingresDespesa del map<char, map<string, Element>>
    if (_concepte.find(ingresDespesa)->second.find(codi) != _concepte.find(ingresDespesa)->second.end() and existeix(descripcio, _concepte[ingresDespesa][codi].descrip()) == -1)
        _concepte[ingresDespesa][codi].inserir_desc(descripcio);
    else
        _concepte[ingresDespesa].insert({ codi, Element(ingresDespesa, codi, descripcio) });
}

void Pressupost::afegirLinia(unsigned short int any, char ingresDespesa, const string& codi, long long import) {
    // Pre:  ingresDespesa correcte i linia correcte
    /* Post: Afegeix la l�nia a l�any corresponent.La l�nia s�afegir� a la dada associada a la clau any del map<unsigned int, Any>.Dins de l�Any, la l�nia s�afegir� a la
        dada associada a la clau ingresDespesa del map<char, set<Linia>>.En el cas que l�any no exist�s, primer s�afegiria l�any a la llista d�anys del pressupost */
    if (_linia.empty() or (!_linia.empty() and _linia.find(any) == _linia.end())) // s'inisereix l'ingres o la despesa a l'any ja existent
        _linia.insert({ any, Any(any) });
    _linia[any]._in_des[ingresDespesa].insert({ Linia(any, ingresDespesa, codi, import) });
}

string Pressupost::descripcioCapitol(const string& codiCapitol, char ingresDespesa) const {
    // Pre: ingresDespesa correcte
    // Post: Retorna la descripci� corresponent al cap�tol codiCapitol d�ingresDespesa('D' o 'I').
    if (!_capitol.at(ingresDespesa).empty() and *_capitol.at(ingresDespesa).at(stoi(codiCapitol)).descrip().begin() == " ")
        cerr << "Error! Capitol inexistent";
    return *_capitol.find(ingresDespesa)->second[stoi(codiCapitol)].descrip().begin();
}

string Pressupost::descripcioArticle(const string& codiArticle, char ingresDespesa) const {
    // Pre: ingresDespesa correcte
    // Post: Retorna la descripci� corresponent a l�article codiArticle d�ingresDespesa('D' o 'I').
    return *_article.find(ingresDespesa)->second.find(codiArticle)->second.descrip().begin();
}

string Pressupost::descripcioConceptes(const string& codiConcepte, char ingresDespesa) const {
    // Pre: ingresDespesa correcte
    // Post: Retorna la descripci� corresponent al concepte codiConcepte d�ingresDespesa('D' o 'I').
    return *_concepte.find(ingresDespesa)->second.find(codiConcepte)->second.descrip().begin();
}

string Pressupost::descripcioAplicacio(const string& codiAplicacio, char ingresDespesa) const {
    // Pre: ingresDespesa correcte
    // Post: Retorna la descripci� corresponent a l�aplicaci� amb codi codiAplicacio d�ingresDespesa ('D' o 'I').
    return *_app.find(ingresDespesa)->second.find(codiAplicacio)->second.descrip().begin();
}

map<int, int> Pressupost::obtenirNLiniesAny() const {
    // Pre: --
    // Post: Retorna, per cada exercici, el nombre de linies de pressupostos que tenim emmagatzemades.
    map<int, int> res;
    for (map<unsigned int, Any>::const_iterator iter = _linia.begin(); iter != _linia.end(); iter++) {
        int num_lin = iter->second._in_des.find(DESPESA)->second.size() + iter->second._in_des.find(INGRES)->second.size();
        res.insert({ iter->second._any, num_lin });
    }
    return res;
}

pair<long long, long long> Pressupost::obtenirImportAny(int exercici) const {
    // Pre: exercici correcte 
    // Post: Retorna la suma de tots els ingressos i la suma de totes les despeses d�un exercici. Retorna els imports en centims d�euro.
    long long ing = 0, des = 0;
    for (set<Linia>::const_iterator iter = _linia.find(exercici)->second._in_des.find(DESPESA)->second.begin(); iter != _linia.find(exercici)->second._in_des.find(DESPESA)->second.end(); iter++) {
        des += iter->import();
    }
    for (set<Linia>::const_iterator iter = _linia.find(exercici)->second._in_des.find(INGRES)->second.begin(); iter != _linia.find(exercici)->second._in_des.find(INGRES)->second.end(); iter++) {
        ing += iter->import();
    }
    return { ing, des };
}

pair<long long, long long> Pressupost::obtenirImportConcepte(int exercici, int capitol, int article, int concepte) const {
    // Pre: exercici correcte
    /* Post: Retorna la suma de tots els ingressos i la suma de totes les despeses dun concepte identificat per lany, el codi de capitol(0 - 9), el subcodi de larticle(0 - 9)
       i el subcodi del concepte(0 - 9). Retorna els imports en centims deuro.*/
    long long ing = 0, des = 0;
    string codi_concepte = to_string(capitol*100 + article * 10 + concepte);
    for (set<Linia>::const_iterator iter = _linia.find(exercici)->second._in_des.find(INGRES)->second.begin(); iter != _linia.find(exercici)->second._in_des.find(INGRES)->second.end(); iter++) {
        if (iter->concepte() == codi_concepte) {
            ing += iter->import();
        }
    }
    for (set<Linia>::const_iterator iter = _linia.find(exercici)->second._in_des.find(DESPESA)->second.begin(); iter != _linia.find(exercici)->second._in_des.find(DESPESA)->second.end(); iter++) {
        if (iter->concepte() == codi_concepte) {
            des += iter->import();
        }
    }
    return { ing, des };
}

vector<string> Pressupost::obtenirCapitols(int exercici, char tipus) const {
    /// Pre: exercici i tipus valid 
    // Post: Retorna un vector<string> amb les descripcions dels capitols d�aquest exercici i del tipus indicat
    vector<string> res = vector<string>(10, "");
    set<Linia>::const_iterator iter = _linia.at(exercici)._in_des.at(tipus).begin();
    int i = 0;
    while (iter != _linia.at(exercici)._in_des.at(tipus).end()) {
        if (stoi(iter->capitol()) == i) {
            res[i] = descripcioCapitol((iter->capitol()), tipus);
            iter++;
        }
        else
            i++;
    }

    return res;
}

list<pair<string, string>> Pressupost::obtenirArticles(int exercici, char tipus) const {
    /// Pre: exercici i tipus valid 
    // Post: Retorna una list amb tots els articles d�aquest exercici i del tipus indicat. codi i la descripcio
    list<pair<string, string>> res = list<pair<string, string>>();
    string ant = "";
    for (set<Linia>::const_iterator iter = _linia.find(exercici)->second._in_des.find(tipus)->second.begin(); iter != _linia.find(exercici)->second._in_des.find(tipus)->second.end(); iter++) {
        if (iter->article() != ant) {
            res.push_back({ iter->article(), descripcioArticle(iter->article(), tipus) });
            ant = iter->article();
        }
    }

    return res;
}

Resum Pressupost::resumCapitols() const {
    // Pre: --
    // Post: Retorna per cada exercici, tots els capitols identificats pel seu codi(ex. 2, 0...), i la suma dels ingressos i despeses.
    Resum res = map<unsigned int, map<string, pair<long long, long long>>>();
    for (map<unsigned int, Any>::const_iterator iter = _linia.begin(); iter != _linia.end(); iter++) {
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(INGRES)->second.begin(); iter_id != iter->second._in_des.find(INGRES)->second.end(); iter_id++) {
            res[iter->first][iter_id->capitol()].first += iter_id->import();
        }
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(DESPESA)->second.begin(); iter_id != iter->second._in_des.find(DESPESA)->second.end(); iter_id++) {
            res[iter->first][iter_id->capitol()].second += iter_id->import();
        }
    }
    return res;
}

Resum Pressupost::resumArticles() const {
    // Pre: --
    // Post: Retorna per cada exercici, tots els articles identificats pel seu codi(ex. 23, 01...), i la suma dels ingressos i despeses.
    Resum res = map<unsigned int, map<string, pair<long long, long long>>>();
    for (map<unsigned int, Any>::const_iterator iter = _linia.begin(); iter != _linia.end(); iter++) {
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(INGRES)->second.begin(); iter_id != iter->second._in_des.find(INGRES)->second.end(); iter_id++) {
            res[iter->first][iter_id->article()].first += iter_id->import();
        }
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(DESPESA)->second.begin(); iter_id != iter->second._in_des.find(DESPESA)->second.end(); iter_id++) {
            res[iter->first][iter_id->article()].second += iter_id->import();
        }
    }
    return res;
}

Resum Pressupost::resumConceptes() const {
    // Pre: --
    // Post: Retorna per cada exercici, tots els conceptes identificats pel seu codi(ex. 235, 010...), i la suma dels ingressos i despeses.
    Resum res = map<unsigned int, map<string, pair<long long, long long>>>();
    for (map<unsigned int, Any>::const_iterator iter = _linia.begin(); iter != _linia.end(); iter++) {
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(INGRES)->second.begin(); iter_id != iter->second._in_des.find(INGRES)->second.end(); iter_id++) {
            res[iter->first][iter_id->concepte()].first += iter_id->import();
        }
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(DESPESA)->second.begin(); iter_id != iter->second._in_des.find(DESPESA)->second.end(); iter_id++) {
            res[iter->first][iter_id->concepte()].second += iter_id->import();
        }
    }
    return res;
}

Resum Pressupost::resumAplicacions() const {
    // Pre: --
    // Post: Retorna per cada exercici, totes les aplicacions identificades pel seu codi (ex. 2351234, 0103845...), i la suma dels ingressos i despeses.
    Resum res = map<unsigned int, map<string, pair<long long, long long>>>();
    for (map<unsigned int, Any>::const_iterator iter = _linia.begin(); iter != _linia.end(); iter++) {
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(INGRES)->second.begin(); iter_id != iter->second._in_des.find(INGRES)->second.end(); iter_id++) {
            res[iter->first][iter_id->aplicacio()].first += iter_id->import();
        }
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(DESPESA)->second.begin(); iter_id != iter->second._in_des.find(DESPESA)->second.end(); iter_id++) {
            res[iter->first][iter_id->aplicacio()].second += iter_id->import();
        }
    }
    return res;
}

Discrepancies Pressupost::obtenirDiscrepanciesCapitols() const {
    // Pre: --
    // Post: Retorna les Discrepancies de les descripcions dels capitols al llarg dels anys(exercicis).
    // En el resultat hi veurem, per cada tipus(I / D) + codi de capitol(ex.I3, D5...), les diferents descripcions que podem trobar al llarg dels anys.
    // I, per cada descripcio, tindrem els exercicis en els quals apareix.
    Discrepancies res = map<char, map<string, set<pair<string, unsigned int>>>>();
    //                      tipus,   codi_cap,       descripcio
    for (map<unsigned int, Any>::const_iterator iter = _linia.begin(); iter != _linia.end(); iter++) {
        map<string, set<pair<string, unsigned int>>> res_nou = map<string, set<pair<string, unsigned int>>>();
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(INGRES)->second.begin(); iter_id != iter->second._in_des.find(INGRES)->second.end(); iter_id++) {
            vector<string> descripcions = descripcionsCapitol(INGRES, iter_id->capitol());
            if (descripcions.size() > 1) {
                for (int i = 0; i < descripcions.size(); i++) {
                    res_nou[iter_id->capitol()].insert({ descripcions[i], iter->second._any});
                }
                res.insert({ INGRES,res_nou });
            }
        }
        res_nou.clear();
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(DESPESA)->second.begin(); iter_id != iter->second._in_des.find(DESPESA)->second.end(); iter_id++) {
            vector<string> descripcions = descripcionsCapitol(DESPESA, iter_id->capitol());
            if (descripcions.size() > 1) {
                for (int i = 0; i < descripcions.size(); i++) {
                    res_nou[iter_id->capitol()].insert({ descripcions[i], iter->second._any});
                }
                res.insert({ DESPESA,res_nou });
            }
        }
    }
    return res;
}

Discrepancies Pressupost::obtenirDiscrepanciesArticles() const {
    // Pre: --
    // Post: Retorna les Discrepancies de les descripcions dels articles al llarg dels anys(exercicis).
    // En el resultat hi veurem, per cada tipus(I / D) + codi d�article(ex.I31, D54...), les diferents descripcions que podem trobar al llarg dels anys.
    // I, per cada descripcio, tindrem els exercicis en els quals apareix.
    Discrepancies res = map<char, map<string, set<pair<string, unsigned int>>>>();
    for (map<unsigned int, Any>::const_iterator iter = _linia.begin(); iter != _linia.end(); iter++) {
        map<string, set<pair<string, unsigned int>>> res_nou = map<string, set<pair<string, unsigned int>>>();
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(INGRES)->second.begin(); iter_id != iter->second._in_des.find(INGRES)->second.end(); iter_id++) {
            vector<string> descripcions = descripcionsArticle(INGRES, iter_id->capitol());
            if (descripcions.size() > 1) {
                for (int i = 0; i < descripcions.size(); i++) {
                    res_nou[iter_id->capitol()].insert({ descripcions[i], iter->second._any});
                }
                res.insert({ INGRES,res_nou });
            }
        }
        res_nou.clear();
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(DESPESA)->second.begin(); iter_id != iter->second._in_des.find(DESPESA)->second.end(); iter_id++) {
            vector<string> descripcions = descripcionsArticle(DESPESA, iter_id->capitol());
            if (descripcions.size() > 1) {
                for (int i = 0; i < descripcions.size(); i++) {
                    res_nou[iter_id->capitol()].insert({ descripcions[i], iter->second._any});
                }
                res.insert({ DESPESA,res_nou });
            }
        }
    }
    return res;
}

Discrepancies Pressupost::obtenirDiscrepanciesConceptes() const {
    // Pre: --
    // Post: Retorna les Discrepancies de les descripcions dels conceptes al llarg dels anys(exercicis).
    // En el resultat hi veurem, per cada tipus(I / D) + codi de concepte(ex.I312, D541...), les diferents descripcions que podem trobar al llarg dels anys.
    // I, per cada descripcio, tindrem els exercicis en els quals apareix.
    Discrepancies res = map<char, map<string, set<pair<string, unsigned int>>>>();
    for (map<unsigned int, Any>::const_iterator iter = _linia.begin(); iter != _linia.end(); iter++) {
        map<string, set<pair<string, unsigned int>>> res_nou = map<string, set<pair<string, unsigned int>>>();
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(INGRES)->second.begin(); iter_id != iter->second._in_des.find(INGRES)->second.end(); iter_id++) {
            vector<string> descripcions = descripcionsConcepte(INGRES, iter_id->capitol());
            if (descripcions.size() > 1) {
                for (int i = 0; i < descripcions.size(); i++) {
                    res_nou[iter_id->capitol()].insert({ descripcions[i], iter->second._any});
                }
                res.insert({ INGRES,res_nou });
            }
        }
        res_nou.clear();
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(DESPESA)->second.begin(); iter_id != iter->second._in_des.find(DESPESA)->second.end(); iter_id++) {
            vector<string> descripcions = descripcionsConcepte(DESPESA, iter_id->capitol());
            if (descripcions.size() > 1) {
                for (int i = 0; i < descripcions.size(); i++) {
                    res_nou[iter_id->capitol()].insert({ descripcions[i], iter->second._any});
                }
                res.insert({ DESPESA,res_nou });
            }
        }
    }
    return res;
}

Discrepancies Pressupost::obtenirDiscrepanciesAplicacions() const {
    // Pre: --
    // Post: Retorna les Discrepancies de les descripcions de les aplicacions al llarg dels anys(exercicis).
    // En el resultat hi veurem, per cada tipus(I / D) + codi d�aplicacio(ex.I3121234, D5413576...), les diferents descripcions que podem trobar al llarg dels anys.
    // I, per cada descripcio, tindrem els exercicis en els quals apareix.
    Discrepancies res = map<char, map<string, set<pair<string, unsigned int>>>>();
    for (map<unsigned int, Any>::const_iterator iter = _linia.begin(); iter != _linia.end(); iter++) {
        map<string, set<pair<string, unsigned int>>> res_nou = map<string, set<pair<string, unsigned int>>>();
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(INGRES)->second.begin(); iter_id != iter->second._in_des.find(INGRES)->second.end(); iter_id++) {
            vector<string> descripcions = descripcionsAplicacio(INGRES, iter_id->capitol());
            if (descripcions.size() > 1) {
                for (int i = 0; i < descripcions.size(); i++) {
                    res_nou[iter_id->capitol()].insert({ descripcions[i], iter->second._any});
                }
                res.insert({ INGRES,res_nou });
            }
        }
        res_nou.clear();
        for (set<Linia>::const_iterator iter_id = iter->second._in_des.find(DESPESA)->second.begin(); iter_id != iter->second._in_des.find(DESPESA)->second.end(); iter_id++) {
            vector<string> descripcions = descripcionsAplicacio(DESPESA, iter_id->capitol());
            if (descripcions.size() > 1) {
                for (int i = 0; i < descripcions.size(); i++) {
                    res_nou[iter_id->capitol()].insert({ descripcions[i], iter->second._any});
                }
                res.insert({ DESPESA,res_nou });
            }
        }
    }
    return res;
}

vector<string> Pressupost::descripcionsCapitol(const char tipus, const string codi) const {
    // Pre: tipus i codi correcte
    // Post: retorna totes les descripcions gruadades d'un capitol en concret
    return _capitol.find(tipus)->second[stoi(codi)].descrip();
}

vector<string> Pressupost::descripcionsArticle(const char tipus, const string codi) const {
    // Pre: tipus i codi correcte
    // Post: retorna totes les descripcions guardades d'un article en concret
    return _article.find(tipus)->second.find(codi)->second.descrip();
}

vector<string> Pressupost::descripcionsConcepte(const char tipus, const string codi) const {
    // Pre: tipus i codi correcte
    // Post: retorna totes les descripcions guardades d'un concepte en concret
    return _concepte.find(tipus)->second.find(codi)->second.descrip();
}

vector<string> Pressupost::descripcionsAplicacio(const char tipus, const string codi) const {
    // Pre: tipus i codi correcte
    // Post: retorna totes les descripcions guardades d'una aplicacio en concret
    return _app.find(tipus)->second.find(codi)->second.descrip();
}

map<string, long long> Pressupost::capitolsDeficitaris(int exercici) const {
    // Pre: exercici correcte
    // Post: Retorna els codis dels capitols deficitaris(els capitols amb mes despeses que ingressos)
    map<string, long long> res = map<string, long long>();
    Resum resum_cap = resumCapitols();
    for (map<string, pair<long long, long long>>::const_iterator iter = resum_cap.find(exercici)->second.begin(); iter != resum_cap.find(exercici)->second.end(); iter++) {
        if (iter->second.first < iter->second.second) {
            res[iter->first] = iter->second.first - iter->second.second;
        }
    }
    return res;
}

string Pressupost::centimsEuros(long long int i) const {
    stringstream s;
    s << fixed << setprecision(2) << (i / 100.0);
    return s.str();
}

bool Pressupost::existeixAny(int exercici) const {
    /// Pre: --
    /// Post: retorna si exercici existeix dins de capitols
    return _linia.find(exercici) != _linia.end();
}

int Pressupost::existeix(const string desc, const vector<string>& llista) const {
    // Pre: --
    // Post: retorna -1 si descripcio no existeix dins de llista, la posicio altrament
    int trobat = -1;
    for (int i = 0; i < llista.size(); i++)
        if (llista[i] == desc)
            trobat = i;
    return trobat;
}