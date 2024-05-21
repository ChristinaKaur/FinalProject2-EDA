/// Christina Kaur Krishan
/// Usuari u1980983
/// Pràctica 1

#include "Linia.h"

Linia::Linia() {
	// Pre: --
	// Post: Constructor que deixa tots els atributs amb els valors per defecte.
	_any = 2003;
	_in_des = 'd';
	_codi = "0";
	_import = 0;
}

Linia::Linia(unsigned short int any, char id, const string& c, long long import) {
	// Pre: --
	// Post: Un constructor amb els quatre valors que defineixen una Linia i que els assigna als atributs corresponents.
	_any = any;
	_in_des = id;
	_codi = c;
	_import = import;
}

unsigned short int Linia::any() const {
	// Pre: --
	// Post: Retorna l�any de la l�nia.
	return _any;
}

char Linia::ingresDespesa() const {
	// Pre: --
	// Post: Retorna si �s de despesa(D) o d�ingr�s(I).
	return _in_des;
}

string Linia::aplicacio() const {
	// Pre: --
	// Post: Retorna el codi de laplicacio.
	return _codi;
}

long long Linia::import() const {
	// Pre: --
	// Post: Retorna l�import de la l�nia.
	return _import;
}

string Linia::capitol() const {
	// Pre: --
	// Post: Retorna el codi del cap�tol (primer car�cter del codi de l�aplicaci�).
	return _codi.substr(0, 1);
}

string Linia::article() const {
	// Pre: --
	// Post: Retorna el codi de l'article (primers dos car�cter del codi de l�aplicaci�).
	return _codi.substr(0, 2);
}

string Linia::concepte() const {
	// Pre: --
	// Post: Retorna el codi de l'article (primers dos car�cter del codi de l�aplicaci�).
	return _codi.substr(0, 3);
}

bool Linia::operator < (const Linia& l) const {
	// Pre:
	// Post: Retorna cert si this < l. Primer es compara el tipus ingr�s / despesa i, si �s el mateix, es compara el codi de l�aplicaci�
	return ((*this)._in_des < l._in_des) or ((*this)._in_des == l._in_des and (*this)._codi < l._codi);
}
