//******************************************//
//part:       IFJ/ semantics.c              //
//team members: M. Kascak      <xkasta02>   //
//              J. Drab        <xdrabj00>   //
//              Ch. Farkas     <xfarka06>   //
//              V. Cervenanska <xcerve23>   //
//written by: M. Kascak                     //
//******************************************//

#include "semantics.h"
#include "err.h"

TType_var resultType(TToken * operand1, TToken_type operation,
                     TToken * operand2) {
	(void) operand1;
	(void) operand2;
	(void) operation;

	if(operand1->var_type == var_string) {
		if(operand2->var_type == var_string && operation == token_add) {
			return var_string;
		} else {
			add_err("[E] Type error: Expected STRING + STRING\n", RV_SEMA_ARIT, 0);
		}
	} else if(operand2->var_type == var_string) {
		if(operand1->var_type == var_string && operation == token_add) {
			return var_string;
		} else {
			add_err("[E] Type error: Expected STRING + STRING\n", RV_SEMA_ARIT, 0);
		}

	}

	if(operand1->var_type == var_double || operand2->var_type == var_double) {
		return var_double;
	} else if(operand1->var_type == var_integer
	          && operand2->var_type == var_integer) {
		return var_integer;
	}

	return var_invalid;
}
