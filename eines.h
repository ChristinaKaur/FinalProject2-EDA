//
// Created by jordir
//

#ifndef LECTURA_EINES_H
#define LECTURA_EINES_H

#include <string>
#include <vector>

using namespace std;

// pre: --
// post: excepcions: si cometes és cert, el primer caràcter és " i no hi ha unes
//       segones " que tanquin, es genera una excepció
// retorna: cadena entre posició primer i següent separador o final de línia.
//          Si cometes és cert, quan el token comença per " busca la " que ho
//          tanca i les elimina del token (si després de les " inicials es
//          troba "", és a dir, dues " seguides, s'ignoren).
string token(const string& s, char separador, bool cometes, long& primer, long& ultim);

// pre: --
// post: --
// retorna: vector<string> amb tots els components d'una línia CSV bàsica
//          (només tractant separadors).
//          Un component està format per tots els caràcters entre dos
//          separadors, excepte el primer i l'últim.
//          El primer component està format per tots els caràcters abans del
//          primer separador.
//          L'últim component està format per tots els caràcters després de
//          l'últim separador.
vector<string> tokens(const string& s, char separador = ',', bool cometes = false);


#endif //LECTURA_EINES_H
