/// Christina Kaur Krishan
/// Usuari u1980983
/// Pràctica 1

#include "Element.h"

Element::Element() {
    _id = DESPESA;
    _codi = " ";
    _descrip = vector<string>();
}

Element::Element(char id, string codi, string descrip) {
    _id = id;
    _codi = codi;
    _descrip.push_back(descrip);
}

void Element::inserir_desc(const string descrip) {
    _descrip.push_back(descrip);
}

bool Element::operator>(const Element e) {
    return (*this)._codi > e._codi;
}

string Element::codi() const{
    return _codi;
}

vector<string> Element::descrip() const {
    return _descrip;
}