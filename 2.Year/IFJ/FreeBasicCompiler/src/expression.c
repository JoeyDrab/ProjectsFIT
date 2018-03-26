//******************************************//
//part:       IFJ/ expression.c             //
//team members: M. Kastak      <xkasta02>   //
//              J. Drab        <xdrabj00>   //
//              Ch. Farkas     <xfarka06>   //
//              V. Cervenanska <xcerve23>   //
//written by: M. Kastak                     //
//******************************************//

#include <stdlib.h>

#include "generator.h"
#include "expression.h"
#include "debug.h"
#include "err.h"
#include "lex.h"
#include "syntax.h"
#include "semantics.h"
#include "symtable.h"

tPsaStack * psaStack = NULL;

/**
 * Precedencna tabulka pre PSA
 * Symobly:
 * '>'
 * '<'
 * '='
 * 'E' error
 */

// TODO: prepisat podla zadania
// precedenceTable[stlpec][riadok]
char precedenceTable[][18] = {
	//  + ,  - ,  * ,  / ,  \ ,  neg,  = ,  < ,  > , <= , >= , <> ,  ( ,  ) ,  f ,  , , var,  $
	{  '>', '>', '<', '<', '<',  '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '>'}, // +
	{  '<', '>', '<', '<', '<',  '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '>'}, // -
	{  '>', '>', '>', '>', '>',  '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '>'}, // *
	{  '>', '>', '>', '>', '>',  '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '>'}, // /
	{  '>', '>', '>', '>', '>',  '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '>'}, // \.

	{  '>', '<', '<', '<', '<',  '<', '<', '<', '<', '<', '<', '<', '<', '>', '<', '>', '<', '>'}, // neg
	{  '<', '<', '<', '<', '<',  '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '>'}, // =
	{  '<', '<', '<', '<', '<',  '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '>'}, // <
	{  '<', '<', '<', '<', '<',  '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '>'}, // >
	{  '<', '<', '<', '<', '<',  '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '>'}, // <=
	{  '<', '<', '<', '<', '<',  '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '>'}, // >=
	{  '<', '<', '<', '<', '<',  '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>', '<', '>'}, // <>

	{  '<', '<', '<', '<', '<',  '<', '<', '<', '<', '<', '<', '<', '<', '=', '<', '=', '<', 'E'}, // (
	{  '>', '>', '>', '>', '>',  '<', '<', '<', '<', '<', '<', '<', 'E', '>', 'E', '>', 'E', '>'}, // )
	{  'E', 'E', 'E', 'E', 'E',  'E', 'E', 'E', 'E', 'E', 'E', 'E', '=', 'E', 'E', 'E', 'E', 'E'}, // f

	{  '>', '<', '<', '<', '<',  '<', '<', '<', '<', '<', '<', '<', '<', '=', '<', '=', '<', 'E'}, // ,
	{  '>', '>', '>', '>', '>',  '>', '>', '>', '>', '>', '>', '>', 'E', '>', '>', '>', 'E', '>'}, // var
	{  '<', '<', '<', '<', '<',  '<', '<', '<', '<', '<', '<', '<', '<', 'E', '<', '>', '<', '>'}, // $
};

unsigned int translateToken(TToken * t) {
	switch(t->type) {
	case token_add:
		return 0;

	case token_sub:
		return 1;

	case token_mul:
		return 2;

	case token_div_int:
		return 3;

	case token_div_double:
		return 4;

	case token_eq:
		return 6;

	case token_lt:
		return 7;

	case token_gt:
		return 8;

	case token_le:
		return 9;

	case token_ge:
		return 10;

	case token_ne:
		return 11;

	case token_parenthesis_left:
		return 12;

	case token_parenthesis_right:
		return 13;

	case token_comma:
		return 15;

	case token_id:
		if(BSTSearchNode(GlobalTree, t->name) || BSTSearchNode(LocalTree, t->name)) {
			if(BSTSearchFunc(GlobalTree, t->name)) {
				return 14;
			} else { // TODO: Ako sa da vyhladat premenna v symtable?
				return 16;
			}
		} else {
			debug_print("Identifer [%s] was not declared\n", t->name);
			add_err("[E] Identifier was not declared\n", RV_SEMA_UNDEF, t->line);
		}

		return 0;
		break;

	case token_integer_literal:
	case token_string_literal:
	case token_floatingpoint_literal:
		return 16;

	case token_symbol_end:
		return 17;

	default:
		add_err("[E] Precedence table out of bounds\n", RV_INTERN, 0);
		return 0;
	}
}

bool parse_expression(TToken * t, TType_var expected_res_type) {
	debug_puts(ANSI_COLOR_GREEN "[SYN][M] Parsing expression\n" ANSI_COLOR_RESET);

	if(!isTokenPsa(t)) {
		add_err("[E] Wrong token in expression\n", RV_SYNTAX, t->line);
	}

	TToken * dolar = token_init();
	dolar->type = token_symbol_end;

	if(psaStack == NULL) {
		psaStack = (tPsaStack *) malloc(sizeof(tPsaStack));

		if(psaStack == NULL) {
			allocation_error();
		}
	}

	psaStackInit(psaStack);
	psaPush(psaStack, dolar);
	TToken * a;
	TToken * b = t;

	do {

		if(!isTokenPsa(b)) {
			token = b;
			debug_puts("[PSA] Token was: ");
			print_token(b);
			b = dolar;
		}

		a = psaTopTerminal(psaStack);

		debug_puts("Znak na vstupe je ");
		print_token(b);
		debug_puts("Top terminal je   ");
		print_token(a);
		debug_print("%d, %d, %c\n", translateToken(a), translateToken(b),
		            precedenceTable[translateToken(a)][translateToken(b)]);
#ifdef DEBUG
		psaStackPrint(psaStack);
#endif /* DEBUG */

		switch(precedenceTable[translateToken(a)][translateToken(b)]) {
		case '<' :
			debug_puts("[PSA][M] < rule\n");
			psaReplaceTopTerminal(psaStack);
			psaPush(psaStack, b);
			b = token_get();
			break;

		case '>':
			debug_puts("[PSA][M] > rule\n");
			psaFindRule(psaStack);
			break;

		case '=':
			debug_puts("[PSA][M] = rule\n");
			psaPush(psaStack, b);
			b = token_get();
			break;

		case 'E':
			debug_puts("[PSA][M] E rule\n");
			add_err("[E] Chyba pri syntaktickej analyze vyrazov\n", 0, 0);
			break;

		default:
			add_err("[E] Chyba precedencnej tabulky\n", 0, 0);

		}

		// b = aktualny token na vstupe
		// a = najvyssi neterminal na zasobniku
	} while(b->type != token_symbol_end
	        || psaTopTerminal(psaStack)->type != token_symbol_end);

	debug_print(ANSI_COLOR_GREEN
	            "[PSA] End of parsing expression, result is [%s] expected [%s]\n"
	            ANSI_COLOR_RESET, var_string_type[psaTop(psaStack)->var_type],
	            var_string_type[expected_res_type]);

	if(expected_res_type == var_invalid
	        || expected_res_type == psaTop(psaStack)->var_type) {
		psaStackDispose(psaStack);
		return true;
	}

	add_err("[E] Conflicting result type of expression\n", RV_SEMA_ARIT,
	        0); // TODO: RV_SEMA_OTHER?
	psaStackDispose(psaStack);
	return false;
}

void psaFindRule(tPsaStack * s) {
	debug_puts("[PSA][M] Looking for rule\n");
	// Bud pravidlo pre premennu alebo funkciu
	TToken * tmp = token_init();
	tmp->type = token_expression;

	TToken * oper1, *oper2, *operation;

	// Ak je na vrchole zasobnika var moze to byt len pravidlo E -> var
	if(psaTop(psaStack)->type == token_id
	        && BSTSearchNode(GlobalTree, psaTop(psaStack)->name)) {
		debug_puts("[SEM][M] Identifikator je funkcia\n");
	} else if(psaTop(psaStack)->type == token_id ||
	          psaTop(psaStack)->type == token_string_literal ||
	          psaTop(psaStack)->type == token_integer_literal ||
	          psaTop(psaStack)->type == token_floatingpoint_literal) {
		TToken * var = psaPop(psaStack);

		if(psaPop(psaStack)->type ==
		        token_shift) { // skontrolujeme ci je dalsi znak shift
			tmp->var_type = getVarType(var);
			psaPush(psaStack, tmp);
			InsListInsert(genIns(NULL, NULL, var, ins_PUSHS));
			return;
		}

		add_err("[E] Chyba pri vyrazoch!\n", RV_SYNTAX, 0);
	} else if(psaTop(s)->type == token_expression) {
		oper1 = psaPop(psaStack);
	} else if(psaTop(psaStack)->type == token_parenthesis_right) {
		// ak je na vrchole zasobnika ) tak to moze byt pravidlo E -> ( E )
		// alebo sa dostavame k volaniu funkcii
		psaPop(psaStack);
		TToken * func;

		if(psaTop(psaStack)->type == token_expression) {
			TToken * exp_last = psaPop(psaStack);

			if(psaTop(psaStack)->type == token_parenthesis_left) {
				psaPop(psaStack);

				if(psaTop(psaStack)->type == token_shift) {
					psaPop(psaStack);
					tmp->var_type = exp_last->var_type;
					psaPush(psaStack, tmp);
					return;
				} else if(psaTop(psaStack)->type == token_id) {
					if(BSTSearchFunc(GlobalTree, psaTop(psaStack)->name)) {
						func = psaPop(psaStack);
						tmp->var_type = searchFuncReturnType(func->name);
						psaPop(psaStack);
						psaPush(psaStack, tmp);
						return;
					} else {
						func = psaPop(psaStack);
						add_err("[E] Function was not declared\n", RV_SEMA_UNDEF, func->line);
					}
				} else {
					add_err("[E] Error in E -> ...(E)\n", RV_SEMA_OTHER,
					        0); // TODO(xkasta02) nema to byt syntax error?
				}

			} else if (psaTop(psaStack)->type == token_comma) {
				TToken * cur_expr;
				psaPop(psaStack);

				if(psaTop(psaStack)->type == token_expression) {
					cur_expr = psaPop(psaStack);

					while(psaTop(psaStack)->type != token_parenthesis_left) {
						if(psaTop(psaStack)->type == token_comma) {
							psaPop(psaStack); //

							if(psaTop(psaStack)->type == token_expression) {
								cur_expr = psaPop(psaStack);
							}
						}
					}

					if(psaTop(psaStack)->type == token_parenthesis_left) {
						psaPop(psaStack); // (

						if(psaTop(psaStack)->type == token_id) {
							if(BSTSearchFunc(GlobalTree, psaTop(psaStack)->name)) {
								func = psaPop(psaStack);
								tmp->var_type = searchFuncReturnType(func->name);
								psaPop(psaStack);
								psaPush(psaStack, tmp);
								return;
							} else {
								func = psaPop(psaStack);
								add_err("[E] Function was not declared\n", RV_SEMA_UNDEF, func->line);
							}
						} else {
							add_err("[E] Error in E -> ...f(E,E)\n", RV_SEMA_OTHER,
							        0); // TODO(xkasta02) nema to byt syntax error?
						}

					} else {
						add_err("[E] Error in E -> ...E,E)\n", RV_SEMA_OTHER,
						        0); // TODO(xkasta02) nema to byt syntax error?
					}
				} else {
					add_err("[E] Error in E -> ...,E) | Expected Expression\n", RV_SEMA_OTHER,
					        0); // TODO(xkasta02) nema to byt syntax error?
				}
			} else {
				add_err("[E] Error in E -> ... )\n", RV_SEMA_OTHER, 0);
			}

		} else if(psaTop(psaStack)->type == token_parenthesis_left) {
			psaPop(psaStack);

			if(psaTop(psaStack)->type == token_id) {
				if(BSTSearchFunc(GlobalTree, psaTop(psaStack)->name)) {
					func = psaPop(psaStack);
					tmp->var_type = searchFuncReturnType(func->name);
					psaPop(psaStack); // Musime popnut aj ten shift co tam je
					psaPush(psaStack, tmp);
					return;
				} else {
					func = psaPop(psaStack);
					add_err("[E] Function was not declared\n", RV_SEMA_UNDEF, func->line);
				}
			}
		}

		add_err("[E] Error in E -> ( E ) rule\n", RV_SEMA_ARIT, 0);
	} else {
		add_err("[E] Chyba pri vyrazoch!\n", RV_SEMA_UNDEF, 0);
	}

	// vsetky ostatne pravidla su v tvare E -> E op E
	if(isTokenOperator(psaTop(psaStack))) {
		operation = psaPop(psaStack);
		generate_operation(operation);

		if(psaTop(psaStack)->type == token_expression) {
			oper2 = psaPop(psaStack);

			if(psaPop(psaStack)->type ==
			        token_shift) { // TODO: overit, moze byt take pravidlo ktore by to nemalo?
				tmp->var_type = resultType(oper1, operation->type, oper2);
				psaPush(psaStack, tmp);
			}
		}
	}
}

void psaReplaceTopTerminal(tPsaStack * s) {
	tPsaElem * tmp = s->top;
	tPsaElem * prev;

	// Ak mame len jeden prvok v zasobniku
	if(!(tmp->token->type == token_shift ||
	        tmp->token->type == token_reduce ||
	        tmp->token->type == token_equal ||
	        tmp->token->type == token_expression)) {
		// Staci ked spravime push shift
		TToken * shift = token_init();
		shift->type    = token_shift;

		psaPush(psaStack, shift);
		return;
	}

	while(tmp != NULL) {
		if(!(tmp->token->type == token_shift ||
		        tmp->token->type == token_reduce ||
		        tmp->token->type == token_equal ||
		        tmp->token->type == token_expression)) {
			tPsaElem * newElem = (tPsaElem *) malloc(sizeof(tPsaElem));

			if(newElem == NULL) {
				allocation_error();
			}

			TToken * shift = token_init();
			shift->type    = token_shift;
			newElem->token = shift;
			newElem->next  = tmp;

			prev->next = newElem;
			debug_puts("[PSA][M] Replace top terminal stack is \n");
#ifdef DEBUG
			psaStackPrint(psaStack);
#endif /* DEBUG */
			return;
		}

		prev = tmp;
		tmp  = tmp->next;
	}
}

TToken * psaTopTerminal(tPsaStack * s) {
	tPsaElem * tmp = s->top;

	while(tmp != NULL) {
		if(!(tmp->token->type == token_shift ||
		        tmp->token->type == token_reduce ||
		        tmp->token->type == token_equal ||
		        tmp->token->type == token_expression)) {
			//debug_puts("[PSA][M] Top terminal je: ");
			//print_token(tmp->token);
			return tmp->token;
		}

		tmp = tmp->next;
	}

	return NULL;
}

// PSA stack
void psaStackInit(tPsaStack * s) {
	if(s == NULL) {
		parameter_error();
		return;
	}

	s->top = NULL;
}

void psaPush(tPsaStack * s, TToken * token) {
	tPsaElem * newElem = (tPsaElem *) malloc(sizeof(tPsaElem));

	if(newElem == NULL) {
		allocation_error();
		return;
	}

	newElem->token = token;
	newElem->next = s->top;
	s->top = newElem;
}

TToken * psaPop(tPsaStack * s) {
	tPsaElem * elem;
	TToken * ret = NULL;

	if(s->top != NULL) {
		elem = s->top;
		s->top = s->top->next;
		ret = elem->token;
		free(elem); // Uvolnime len tPsaElem a nie *token v nom
	}

	return ret;
}

TToken * psaTop(tPsaStack * s) {
	return (s != NULL) ? s->top->token : NULL;
}

bool psaEmpty(tPsaStack * s) {
	return (s->top == NULL);
}

void psaStackPrint(tPsaStack * s) {
	tPsaElem * tmp = s->top;

	while(tmp != NULL) {
		//debug_puts("[PSA] stack contains token ");
		fprintf(stderr, "[PSA] stack contains token ");
		print_token(tmp->token);
		tmp = tmp->next;
	}
}

void psaStackDispose(tPsaStack * s) {
	tPsaElem * tmp = s->top;

	while(tmp != NULL) {
		tPsaElem * del = tmp;
		tmp = tmp->next;
		free(del);
	}
}

