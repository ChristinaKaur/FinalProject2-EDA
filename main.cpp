/// Christina Kaur Krishan
/// Usuari u1980983
/// Pràctica 1

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#ifdef _WIN32
#include<windows.h>
#endif

#include "Pressupost.h"

using namespace std;

string centimsEuros(long long int i) {
    ///< Pre:
    ///< Post: retorna i passat a centims i string
    stringstream s;
    s << fixed << setprecision(2) << (i / 100.00) << " €";
    return s.str();
}

void mostra_menu() {
    ///< Pre: --
    ///< Post: mostra per pantalla el menu
    cout << "******************************************" << endl;
    cout << "*  [0 ] - Acabar                         *" << endl;
    cout << "*  [01] - Llegir dades                   *" << endl;
    cout << "*  [02] - Mostrar capitols dun any       *" << endl;
    cout << "*  [03] - Mostrar articles dun any       *" << endl;
    cout << "*  [04] - Resum per any                  *" << endl;
    cout << "*  [05] - Resum dun concepte             *" << endl;
    cout << "*  [06] - Resum per capitol              *" << endl;
    cout << "*  [07] - Resum per article              *" << endl;
    cout << "*  [08] - Resum per concepte             *" << endl;
    cout << "*  [09] - Resum per aplicacio            *" << endl;
    cout << "*  [10] - Discrepancies capitols         *" << endl;
    cout << "*  [11] - Discrepancies articles         *" << endl;
    cout << "*  [12] - Discrepancies conceptes        *" << endl;
    cout << "*  [13] - Discrepancies aplicacions      *" << endl;
    cout << "*  [14] - Capitols deficitaris dun any   *" << endl;
    cout << "******************************************" << endl;
}

void mostra_linies_cap(vector<string> ll, char tipus, const Pressupost& p) {
    ///< Pre: --
    ///< Post: mostra per pantalla el contingut de ll
    string titol = "INGRESSOS:";
    if (tipus == 'D') titol = "DESPESES:";
    cout << titol << endl;

    for (int i = 0; i < 10; i++) {
        cout << i << " --> " << ll.at(i) << endl;
    }
}

void capitol_any(Pressupost& p) {
    ///< Pre: --
    ///< Post: demana any i mostra els seus capitols
    string any;
    getline(cin, any);
    if (p.existeixAny(stoi(any))) {
        vector<string> ingressos = p.obtenirCapitols(stoi(any), 'I');
        mostra_linies_cap(ingressos, 'I', p);
        vector<string>  despeses = p.obtenirCapitols(stoi(any), 'D');
        mostra_linies_cap(despeses, 'D', p);
    }
    else
        cerr << "\tERROR [" << any << "] Any inexistent" << endl;
}

void mostra_linies_art(list<pair<string, string>> ll, char tipus, const Pressupost& p) {
    ///< Pre: --
    ///< Post: mostra per pantalla el contingut de ll
    string titol = "INGRESSOS:";
    if (tipus == 'D') titol = "DESPESES:";
    cout << titol << endl;

    for (list<pair<string, string>>::const_iterator iter = ll.begin(); iter != ll.end(); iter++) {
        cout << iter->first << " --> " << iter->second << endl;
    }
}

void article_any(Pressupost& p) {
    ///< Pre: --
    ///< Post: demana any i mostra els seus articles
    string any;
    getline(cin, any);
    if (p.existeixAny(stoi(any))) {
        list<pair<string, string>> ingressos = p.obtenirArticles(stoi(any), 'I');
        mostra_linies_art(ingressos, 'I', p);
        list<pair<string, string>> despeses = p.obtenirArticles(stoi(any), 'D');
        mostra_linies_art(despeses, 'D', p);
    }
    else
        cerr << "\tERROR [" << any << "] Any inexistent" << endl;
}

void mostra_resum_any(Pressupost& p) {
    ///< Pre: --
    ///< Post: mostra el resum de cada any mostrant, a cada fila, l’any, el nombre de files llegides, la suma d’ingressos i la suma de despeses.
    map<int, int> linies_any = p.obtenirNLiniesAny();
    int linia_total = 0;
    long long ing_total = 0, desp_total = 0;
    for (map<int, int>::const_iterator iter = linies_any.begin(); iter != linies_any.end(); iter++) {
        pair<long long, long long> import = p.obtenirImportAny(iter->first);
        cout << iter->first << "\tLínies:" << setw(6) << iter->second << setw(4) << "I:" << setw(20) << centimsEuros(import.first) << setw(4) << "D:" << setw(20) << centimsEuros(import.second) << endl;
        linia_total += (iter->second);
        ing_total += import.first;
        desp_total += import.second;
    }
    cout << "TOTAL :" << setw(14) << linia_total << setw(4) << "I:" << setw(20) << centimsEuros(ing_total) << setw(4) << "D:" << setw(20) << centimsEuros(desp_total) << endl;
}

void mostra_resum_un_concepte(Pressupost& p) {
    ///< Pre: --
    ///< Post: mostra la suma dingressos i despeses d’aquest concepte en aquest any
    string any, codi;
    getline(cin, any);
    getline(cin, codi);
    if (p.existeixAny(stoi(any))) {
        pair<long long, long long> res = p.obtenirImportConcepte(stoi(any), stoi(codi.substr(0, 1)), stoi(codi.substr(1, 1)), stoi(codi.substr(2, 1)));
        cout << "\tI:" << setw(20) << centimsEuros(res.first) << setw(4) << "D:" << setw(20) << centimsEuros(res.second) << endl;
    }
    else
        cerr << "\tERROR [" << any << "] Any inexistent" << endl;
}

void mostra_import(const string import) {
    ///< Pre: --
    ///< Post: si import és 0 mostra per pantalla import com a "--"
    if (import == "0.00 €") cout << "--";
    else cout << import;
}

void mostra_resum_capitol(Pressupost& p) {
    ///< Pre: --
    ///< Post: mostra el resum de cada capitol
    Resum res = p.resumCapitols();
    for (map<unsigned int, map<string, pair<long long, long long>>>::const_iterator iter = res.begin(); iter != res.end(); iter++) {
        cout << iter->first << setw(31) << "INGRES" << setw(20) << "DESPESA" << endl;
        for (map<string, pair<long long, long long>>::const_iterator cap = iter->second.begin(); cap != iter->second.end(); cap++) {
            cout << "\t" << cap->first << setw(26);
            mostra_import(centimsEuros(cap->second.first));
            cout << setw(20);
            mostra_import(centimsEuros(cap->second.second));
            cout << endl;
        }
        cout << endl;
    }
}

void mostra_resum_article(Pressupost& p) {
    ///< Pre: --
    ///< Post: mostra el resum de cada article
    Resum res = p.resumArticles();
    for (map<unsigned int, map<string, pair<long long, long long>>>::const_iterator iter = res.begin(); iter != res.end(); iter++) {
        cout << iter->first << setw(31) << "INGRES" << setw(20) << "DESPESA" << endl;
        for (map<string, pair<long long, long long>>::const_iterator cap = iter->second.begin(); cap != iter->second.end(); cap++) {
            cout << "\t" << cap->first << setw(25);
            mostra_import(centimsEuros(cap->second.first));
            cout << setw(20);
            mostra_import(centimsEuros(cap->second.second));
            cout << endl;
        }
        cout << endl;
    }
}

void mostra_resum_concepte(Pressupost& p) {
    ///< Pre: --
    ///< Post: mostra el resum de cada concepte
    Resum res = p.resumConceptes();
    for (map<unsigned int, map<string, pair<long long, long long>>>::const_iterator iter = res.begin(); iter != res.end(); iter++) {
        cout << iter->first << setw(31) << "INGRES" << setw(20) << "DESPESA" << endl;
        for (map<string, pair<long long, long long>>::const_iterator cap = iter->second.begin(); cap != iter->second.end(); cap++) {
            cout << "\t" << cap->first << setw(24);
            mostra_import(centimsEuros(cap->second.first));
            cout << setw(20);
            mostra_import(centimsEuros(cap->second.second));
            cout << endl;
        }
        cout << endl;
    }
}

void mostra_resum_aplicacions(Pressupost& p) {
    ///< Pre: --
    ///< Post: mostra el resum de les aplicacions
    Resum res = p.resumAplicacions();
    for (map<unsigned int, map<string, pair<long long, long long>>>::const_iterator iter = res.begin(); iter != res.end(); iter++) {
        cout << iter->first << setw(31) << "INGRES" << setw(20) << "DESPESA" << endl;
        for (map<string, pair<long long, long long>>::const_iterator cap = iter->second.begin(); cap != iter->second.end(); cap++) {
            cout << "\t" << cap->first << setw(20);
            mostra_import(centimsEuros(cap->second.first));
            cout << setw(20);
            mostra_import(centimsEuros(cap->second.second));
            cout << endl;
        }
        cout << endl;
    }
}

void mostra_discrapancies_capitols(Pressupost& p) {
    ///< Pre: --
    ///< Post: mostra les discrapancies dels capitols
    /*Discrepancies res = p.obtenirDiscrepanciesCapitols();
    for (map<char, map<string, set<pair<string, unsigned int>>>>::const_iterator iter = res.begin(); iter != res.end(); iter++) {
        for (map<string, set<pair<string, unsigned int>>>::const_iterator iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++) {
            cout << iter->first << iter2->first << "==>" << endl;
            for (set<pair<string, unsigned int>>::const_iterator iter3 = iter2->second.begin(); iter3 != iter2->second.end(); iter3++) {
                cout << "\t- " << iter3->first << ": " << iter3->second << "," << endl;
            }
        }
        cout << endl;
    }*/
}

void mostra_discrapancies_articles(Pressupost& p) {
    ///< Pre: --
    ///< Post: mostra les discrapancies dels articles
    /*Discrepancies res = p.obtenirDiscrepanciesArticles();
    for (map<char, map<string, set<pair<string, unsigned int>>>>::const_iterator iter = res.begin(); iter != res.end(); iter++) {
        for (map<string, set<pair<string, unsigned int>>>::const_iterator iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++) {
            cout << iter->first << iter2->first << "==>" << endl;
            for (set<pair<string, unsigned int>>::const_iterator iter3 = iter2->second.begin(); iter3 != iter2->second.end(); iter3++) {
                cout << "\t- " << iter3->first << ": " << iter3->second << "," << endl;
            }
        }
        cout << endl;
    }
*/
}

void mostra_discrapancies_conceptes(Pressupost& p) {
    ///< Pre: --
    ///< Post: mostra les discrapancies dels conceptes
    /*Discrepancies res = p.obtenirDiscrepanciesConceptes();
    for (map<char, map<string, set<pair<string, unsigned int>>>>::const_iterator iter = res.begin(); iter != res.end(); iter++) {
        for (map<string, set<pair<string, unsigned int>>>::const_iterator iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++) {
            cout << iter->first << iter2->first << "==>" << endl;
            for (set<pair<string, unsigned int>>::const_iterator iter3 = iter2->second.begin(); iter3 != iter2->second.end(); iter3++) {
                cout << "\t- " << iter3->first << ": " << iter3->second << "," << endl;
            }
        }
        cout << endl;
    }
*/
}

void mostra_discrapancies_aplicacions(Pressupost& p) {
    ///< Pre: --
    ///< Post: mostra les discrapancies de les aplicacions
    /*Discrepancies res = p.obtenirDiscrepanciesAplicacions();
    for (map<char, map<string, set<pair<string, unsigned int>>>>::const_iterator iter = res.begin(); iter != res.end(); iter++) {
        for (map<string, set<pair<string, unsigned int>>>::const_iterator iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++) {
            cout << iter->first << iter2->first << "==>" << endl;
            for (set<pair<string, unsigned int>>::const_iterator iter3 = iter2->second.begin(); iter3 != iter2->second.end(); iter3++) {
                cout << "\t- " << iter3->first << ": " << iter3->second << "," << endl;
            }
        }
        cout << endl;
    }
*/
}

void mostra_capitols_deficitaris_any(Pressupost& p) {
    ///< Pre: --
    ///< Post: mostra els capitols deficitaris d'un any
    string any;
    getline(cin, any);
    if (p.existeixAny(stoi(any))) {
        map<string, long long> res = p.capitolsDeficitaris(stoi(any));
        for (map<string, long long>::const_iterator iter = res.begin(); iter != res.end(); iter++)
            cout << iter->first << ": " << setw(20) << centimsEuros(iter->second) << endl;
    }
    else
        cerr << "\tERROR [" << any << "] Any inexistent" << endl;
}

void gestiona_entrada(const string entrada, Pressupost& pres) {
    ///< Pre: --
    ///< Post: gestiona la entrada
    if (entrada == "01") {
        cout << "********************\n* 01: Llegir dades *\n********************" << endl;
        string path;
        getline(cin, path);
        pres.llegirDades(path);
    }
    else if (entrada == "02") {
        //Mostrar capitols dun any
        cout << "*********************************\n* 02: Mostrar capitols d un any *\n*********************************" << endl;
        capitol_any(pres);
    }
    else if (entrada == "03") {
        //Mostrar articles dun any
        cout << "********************************\n* 03: Mostrar aticles d’un any *\n********************************" << endl;
        article_any(pres);
    }
    else if (entrada == "04") {
        //resum per any
        cout << "*********************\n* 04: Resum per any *\n*********************" << endl;
        mostra_resum_any(pres);
    }
    else if (entrada == "05") {
        //resum d'un concepte
        cout << "***************************\n* 05: Resum d’un concepte *\n***************************" << endl;
        mostra_resum_un_concepte(pres);
    }
    else if (entrada == "06") {
        //resum per capitol
        cout << "*************************\n* 06: Resum per capitol *\n*************************" << endl;
        mostra_resum_capitol(pres);
    }
    else if (entrada == "07") {
        //resum per article
        cout << "*************************\n* 07: Resum per article *\n*************************" << endl;
        mostra_resum_article(pres);
    }
    else if (entrada == "08") {
        //resum per concepte
        cout << "**************************\n* 08: Resum per concepte *\n**************************" << endl;
        mostra_resum_concepte(pres);
    }
    else if (entrada == "09") {
        //resum per aplicacions
        cout << "*****************************\n* 09: Resum per aplicacions *\n*****************************" << endl;
        mostra_resum_aplicacions(pres);
    }
    else if (entrada == "10") {
        //Discrepancies capitols
        cout << "******************************\n* 10: Discrepancies capitols *\n******************************" << endl;
        mostra_discrapancies_capitols(pres);
    }
    else if (entrada == "11") {
        //Discrepancies articles
        cout << "******************************\n* 11: Discrepancies articles *\n******************************" << endl;
        mostra_discrapancies_articles(pres);
    }
    else if (entrada == "12") {
        //Discrepancies conceptes
        cout << "*******************************\n* 12: Discrepancies conceptes *\n*******************************" << endl;
        mostra_discrapancies_conceptes(pres);
    }
    else if (entrada == "13") {
        //Discrepancies aplicacions
        cout << "*********************************\n* 13: Discrepancies aplicacions *\n*********************************" << endl;
        mostra_discrapancies_aplicacions(pres);
    }
    else if (entrada == "14") {
        //Capitols deficitaris dun any
        cout << "*************************************\n* 14: Capitols deficitaris d’un any *\n*************************************" << endl;
        mostra_capitols_deficitaris_any(pres);
    }
    else {
        cout << "Entrada incorrecte, torna - ho a intentar!!!" << endl;
        mostra_menu();
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Pressupost pres;

    string entrada = "-1";
    getline(cin, entrada);
    while (entrada != "0") {
        gestiona_entrada(entrada, pres);
        getline(cin, entrada);
    }

    return 0;
}