//__________________________________________//
//******************************************//
//part:		IFJ/ syntax.h					//
//team members: M. Kastak, J. Drab, 		//
//				Ch. Farkas, V. Cervenanska	//
//written by: J.Drab						//
//__________________________________________//

#ifndef LEX_H
#define LEX_H

#include <stdio.h>

/* stavy konečnýho automatu */
typedef enum {
	state_initial,	// symbol
	state_scream,
	state_add,
	state_multip,
	state_sub,
	state_div,
	state_slash,
	state_greater,
	state_less,
	state_identifier, // identifier or keyword
	state_int,	// number
	state_string_literal,
	state_double,
	state_exp,
	state_multiline_comment,
	state_multiline_comment_end,
	state_exp_begin,
	state_exp_sign,
	state_dot,

	state_opened_string,
	state_string_escape,
	state_o_escape_first,
	state_o_escape_second,
} TState;

typedef enum {
	variable_Double,
	variable_Chr,
	variable_Integer,
	variable_String,
	variable_Boolean,
} TType;

typedef struct _TypeVar {
	union {
		int integ;
		double doub;
		char * str;
	} data;
	TType	type;
} TypeVar;

/*tokens*/
typedef enum {
	token_err,			// 0 //error
	token_comma,		// 1 // ","
	// matematic...
	token_add,			// 3 // "+"
	token_add_eq,		// 4 // "+="
	token_sub_eq,		// 5 // "-="
	token_mul_eq,		// 6 // "*="
	token_div_int_eq,	// 7 // "/="
	token_div_double_eq,// 8 // "\="
	token_sub,			// 9 // "-"
	token_mul,			// 10 // "*"
	token_div_int,		// 11 // "/"
	token_div_double,	// 12 // "\"
	token_expon,		// 13 // "^"
	token_line_comm,	// 14 // "'"
	//token_multi_comm,	// 15 // " /" "
	//token_end_multi_com,// 16 // " "/ "
	//comparing
	token_eq,				// 17 // "=="
	token_lt,				// 18 // "<"
	token_gt,				// 19 // ">"
	token_ne,				// 20 // "<>"
	token_ge,				// 21 // ">="
	token_le,				// 22 // "<="
	token_semicolon,		// 23 // ";"
	token_parenthesis_left,	// 24 // "("
	token_parenthesis_right,// 25 // ")"
	token_square_left,		// 26 // "["
	token_square_right,		// 27 // "]"

	token_double,				// 20
	token_floatingpoint_literal,	// 21 // desatinny literal
	token_string,				// 22
	token_string_literal, 		// 23 // slovny literal
	token_integer,				// 24
	token_integer_literal, 		// 25 // celociselny literal
	token_id,					// 26
	// reserved keywords
	token_as,			// 27
	token_asc,			// 28
	token_declare,		// 29
	token_dim,			// 30
	token_do,			// 31
	token_if,			// 32
	token_else,			// 33
	token_end,			// 34
	token_function,		// 35
	token_input,		// 36
	token_length,		// 37
	token_loop,			// 38
	token_print,		// 39
	token_return,		// 40
	token_scope,		// 41
	token_then,			// 42
	token_while,		// 43
	token_and,			// 44
	token_continue,		// 45
	token_elseif,		// 46
	token_exit,			// 47
	token_true,			// 48
	token_false,		// 49
	token_for,			// 50
	token_next,			// 51
	token_not,			// 52
	token_or,			// 53
	token_boolean,		// 54
	token_chr,			// 55
	token_shared,		// 56
	token_static,		// 57
	token_subStr,		// 58
	token_eof,			// 59	// end of file
	token_eol,			// 60 	// end of line
	token_mod,			// 61

	token_exp_literal,

} TToken_type;

typedef struct TToken {
	TToken_type type;
	int length;
	int allocated;
	unsigned long line;
	char * name;
} TToken;

TToken * token;

/**
 * Funkcia inicializuje lexikalnu analyzu.
 *
 * Funckcia je volana bud podla zadania s stdin alebo
 * inicializuje lexikalnu analyzu aby pouzivala pouzivatelom
 * specifikovany subor.
 *
 * @param[in] source_file zdrojovy subor pouzity
 */
void     lex_init(FILE * f);

/**
 * Funkcia ktora vypise token.
 *
 * @param[in] t ukazatel na token, ktory ma byt vypisany
 */
void     print_token(TToken * t);

/**
 * Funkcia ktora uvolni alokovanu pamat tokenu.
 *
 * Uvolnovanie tokenov bude prebiehat po ukonceni vsetkych analyz a
 * vygenerovani kodu
 *
 * @param[in, out] t token ktory ma byt uvolneni
 */
void token_free(TToken * t);

TToken * token_init();
void find_identifier(TToken * token, char * name_buff);
void token_free( TToken * token );
void token_return_token(TToken * token);
TToken * token_get();
TToken * token_data_add( TToken * token, char * text );
TToken * token_last;

#endif /* LEX_H */
