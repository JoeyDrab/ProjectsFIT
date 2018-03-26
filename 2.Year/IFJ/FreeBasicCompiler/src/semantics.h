//******************************************//
//part:       IFJ/ semantics.h              //
//team members: M. Kastak      <xkasta02>   //
//              J. Drab        <xdrabj00>   //
//              Ch. Farkas     <xfarka06>   //
//              V. Cervenanska <xcerve23>   //
//written by: M. Kastak                     //
//******************************************//

#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "lex.h"

TType_var resultType(TToken * operand1, TToken_type operation,
                     TToken * operand2);

#endif /* SEMANTICS_H */
