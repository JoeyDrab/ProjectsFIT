//******************************************//
//part:       IFJ/ expression.h             //
//team members: M. Kastak      <xkasta02>   //
//              J. Drab        <xdrabj00>   //
//              Ch. Farkas     <xfarka06>   //
//              V. Cervenanska <xcerve23>   //
//written by: M. Kastak                     //
//******************************************//

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stdbool.h>

#include "lex.h"

typedef struct sPsaElem {
	TToken * token;
	struct sPsaElem * next;
} tPsaElem;

typedef struct sPsaStack {
	tPsaElem * top;
} tPsaStack;

bool parse_expression(TToken * t, TType_var expected_res_type);

TToken * psaTopTerminal(tPsaStack * s);
void psaFindRule(tPsaStack * s);
void psaReplaceTopTerminal(tPsaStack * s);

/**
 * Funkcie implementujuce zasobnik
 */
void psaStackInit(tPsaStack * s);
void psaPush(tPsaStack * s, TToken * token);
TToken * psaPop(tPsaStack * s);
TToken * psaTop(tPsaStack * s);
bool psaEmpty(tPsaStack * s);
void psaStackPrint(tPsaStack * s);
void psaStackDispose(tPsaStack * s);

#endif /* EXPRESSION_H */
