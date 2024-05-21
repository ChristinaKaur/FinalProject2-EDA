/// Christina Kaur Krishan
/// Usuari u1980983
/// Pràctica 1

#ifndef LINIA_H
#define LINIA_H

#include <iostream>
#include <string>

using namespace std;

class Linia {
public:
	Linia();
	///< Pre: --
    ///< Post: constructor que deixa tots els atributs amb els valors per defecte.

	Linia(unsigned short int any, char id, const string& c, long long import);
    ///< Pre: --
    ///< Post: constructor amb els quatre valors que defineixen una Linia i que els assigna als atributs corresponents.

	unsigned short int any() const;
    ///< Pre: --
    ///< Post: retorna l'any de la linia.

	char ingresDespesa() const;
    ///< Pre: --
    ///< Post: retorna si es de despesa(D) o d'ingres(I).

	string aplicacio() const;
    ///< Pre: --
	///< Post: retorna el codi de l'aplicacio.

	long long import() const;
    ///< Pre: --
    ///< Post: retorna l'import de la linia.

	string capitol() const;
    ///< Pre: --
    ///< Post: retorna el codi del capitol (primer caracter del codi de l'aplicacio).

	string article() const;
    ///< Pre: --
    ///< Post: retorna el codi de l'article (primers dos caracter del codi de l'aplicacio).

	string concepte() const;
    ///< Pre: --
	///< Post: retorna el codi del concepte (primers tres caracter del codi de l'aplicacio).

	bool operator < (const Linia& l) const;
	///< Pre: --
	///< Post: retorna cert si this < l

private:
	unsigned short int _any;
	char _in_des;
	string _codi;
	long long _import;
}; 
#endif

