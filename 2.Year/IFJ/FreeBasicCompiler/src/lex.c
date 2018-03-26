//******************************************//
//part:       IFJ/ lex.c                    //
//team members: M. Kastak      <xkasta02>   //
//              J. Drab        <xdrabj00>   //
//              Ch. Farkas     <xfarka06>   //
//              V. Cervenanska <xcerve23>   //
//written by: M. Kastak, J. Drab            //
//******************************************//

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

#include "symtable.h"
#include "debug.h"
#include "err.h"
#include "lex.h"

/**
 * Globalna premenna specifikujuca spracovavany subor.
 */
static FILE * source_file;

const char * token_string_name[] = {
	"token_integer_literal",
	"token_floatingpoint_literal",
	"token_string_literal",
	"token_as",
	"token_asc",
	"token_declare",
	"token_dim",
	"token_do",
	"token_double",
	"token_else",
	"token_end",
	"token_function",
	"token_if",
	"token_input",
	"token_integer",
	"token_length",
	"token_loop",
	"token_print",
	"token_return",
	"token_scope",
	"token_string",
	"token_substr",
	"token_then",
	"token_while",
	"token_and",
	"token_boolean",
	"token_continue",
	"token_elseif",
	"token_exit",
	"token_false",
	"token_for",
	"token_next",
	"token_not",
	"token_or",
	"token_shared",
	"token_static",
	"token_true",
	"token_lt",
	"token_gt",
	"token_le",
	"token_ge",
	"token_ne",
	"token_eq",
	"token_add",
	"token_sub",
	"token_mul",
	"token_div_int",
	"token_div_double",
	"token_add_eq",
	"token_sub_eq",
	"token_mul_eq",
	"token_div_int_eq",
	"token_div_double_eq",
	"token_eol",
	"token_eof",
	"token_comma",
	"token_semicolon",
	"token_id",
	"token_parenthesis_left",
	"token_parenthesis_right",
	"token_shift",
	"token_reduce",
	"token_expression",
	"token_equal",
	"token_symbol_end"
};

/* Typ premennej */
const char * var_string_type[] = {
	"var_invalid",
	"var_double",
	"var_integer",
	"var_string",
	"var_bool"
};

inline void print_token(TToken * t) {
	if(t == NULL) {
		parameter_error();
	}

	// Tu je fprintf namiesto debug_print pretoze nas nezaujima kde sme a len potrebujeme
	// vypisat obsah tokenu na vystup(chybovy)
	fprintf(stderr,
	        "[LEX] token->type = %s \ttoken->line = %lu \ttoken->name = %s \ttoken->var_type = %s\n",
	        token_string_name[t->type], t->line, t->name, var_string_type[t->var_type]);
}

void lex_init(FILE * f) {
	if(f == NULL) {
		parameter_error();
	}

	source_file = f;
}

TToken * token_init() {
	TToken * token = ( TToken * ) malloc( sizeof( struct TToken ));

	if(token == NULL) {
		allocation_error();
	}

	token->name = NULL;
	token->line = 0;

	token->var_type = var_invalid;
	token->data.s   = NULL;

	token->type = token_eof;
	return token;
}

void token_free(TToken * t) {
	if(t == NULL) {
		parameter_error();
	}

	free(t->name);
	free(t);
}

TToken * token_name_add( TToken * token, dynamic_string * text ) {
	token->name = text->str;
	ds_free(text);
	return token;
}

bool isTokenOperator(TToken * t) {
	if(t->type == token_add ||
	        t->type == token_sub ||
	        t->type == token_mul ||
	        t->type == token_div_int ||
	        t->type == token_div_double ||
	        t->type == token_eq ||
	        t->type == token_gt ||
	        t->type == token_lt ||
	        t->type == token_ge ||
	        t->type == token_le ) {
		return true;
	}

	return false;
}

inline bool isTokenPsa(TToken * t) {
	if(t->type == token_add ||
	        t->type == token_sub ||
	        t->type == token_mul ||
	        t->type == token_div_int ||
	        t->type == token_div_double ||
	        t->type == token_eq ||
	        t->type == token_gt ||
	        t->type == token_lt ||
	        t->type == token_ge ||
	        t->type == token_le ||
	        t->type == token_ne ||
	        t->type == token_comma ||
	        t->type == token_string_literal ||
	        t->type == token_floatingpoint_literal ||
	        t->type == token_integer_literal ||
	        t->type == token_parenthesis_left ||
	        t->type == token_parenthesis_right ||
	        t->type == token_symbol_end ||
	        t->type == token_id) {
		return true;
	}

	return false;
}

void find_identifier(TToken * token, dynamic_string * name_buff) {
	char * keywords[] = {"as", "asc", "declare", "dim", "do", "double", "else", "end",
	                     "function", "if", "input", "integer", "length", "loop", "print", "return",
	                     "scope", "string", "subStr", "then", "while", "and", "boolean", "continue",
	                     "elseif", "exit", "false", "for", "next", "not", "or", "shared", "static", "true", NULL
	                    };

	TToken_type  tokens[] = {token_as, token_asc, token_declare, token_dim, token_do, token_double, token_else, token_end,
	                         token_function, token_if, token_input, token_integer, token_length, token_loop, token_print,
	                         token_return, token_scope, token_string, token_substr, token_then, token_while, token_and, token_boolean,
	                         token_continue, token_elseif, token_exit, token_false, token_for, token_next, token_not, token_or,
	                         token_shared, token_static, token_true,
	                        };

	// NULL na konci keywords sluzi ako zarazka
	// po ktoru sa len pohybujeme po poli a nasledne ak ju najdeme
	// vieme ze identifikator nie je klucove slovo
	int i;

	for(i = 0; keywords[i] != NULL; ++i) {
		if (strcmp(keywords[i], name_buff->str) == 0) {
			token->type = tokens[i];
			free(name_buff->str);
			ds_free(name_buff);
			return;
		}
	}

	token->type = token_id;
	token = token_name_add(token, name_buff);
}

TToken * token_get() {

	// staticka premenna obsahujuca riadok, na ktorom sa token nachadza
	// kedze je staticka jej hodnota je zachovana medzi roznymi volaniami funkcie
	static unsigned long line = 1;

	// buffer drzi v sebe cislo pri prevode escape, num_buff[4] je vyhradeny pre '\0'
	char num_buff[4] = {0};

	TToken * token;

	if((token = token_init()) == NULL) {
		//alokacia noveho tokenu
		return NULL;
	}

	token->line = line;

	dynamic_string name_buff;
	ds_init(&name_buff, 32);

	TState state = state_initial;

	int c;

	do {
		c = tolower(fgetc(source_file));

		//debug_print("[LEX] spracovavany znak: %c | chr(%d)\n", c, c);

		switch (state) {
		case state_initial:

			if (c == '!') {
				state = state_scream;
			} else if (c == ',') {
				token->type = token_comma;
				return token;
			} else if (c == '+') {    // if + or +=
				state = state_add;
			} else if (c == '*') {    // if * or *=
				state = state_multip;
			} else if (c == '-') {    // if - or -=
				state = state_sub;
			} else if (c == '/') {    // if / or /=
				state = state_slash;
			} else if (c == '\'') {
				state = state_oneline_comment;
			} else if (c == '\\') {      // if \ or \=
				state = state_int_div;
			} else if (c == '=') {
				token->type = token_eq;
				return token;
			} else if (c == '>') {
				state = state_greater;
			} else if (c == '<') {
				state = state_less;
			} else if (c == '(') {
				token->type = token_parenthesis_left;
				return token;
			} else if (c == ')') {
				token->type = token_parenthesis_right;
				return token;
			} else if (c == ';') {
				token->type = token_semicolon;
				return token;
			} else if (isalpha(c) || c == '_') {
				ds_insert_char(&name_buff, c);
				state = state_identifier; //founded :D identifier or keyword
			} else if (isdigit(c)) {
				ds_insert_char(&name_buff, c);
				state = state_int;
			} else if (c == '\n') {
				line++; // lexikalna analyza presla na dalsi riadok
				token->type = token_eol;
				return token;
			} else if (c == EOF) {
				token->type = token_eof;
				return token;
			} else if (isspace(c)) {
				; // ignorovanie ostatnych bielych znakov
				// \n musime mat uz osetreny kedze ho potrebujeme ako token
			} else {
				debug_print("Symbol found [%c] -> %d\n", c, c);
				add_err("[E] Unsupported symbol found in source code\n", RV_LEX, line);
			}

			break;

		case state_scream:
			if(c == '"') {
				state = state_string_literal;
			} else {
				add_err("[E] After '!' in string literal \" is expected\n", RV_LEX, line);
			}

			break;

		case state_string_escape:
			if(c == 'n') {
				ds_insert_char(&name_buff, '\n');
				state = state_string_literal;
			} else if(c == '"') {
				ds_insert_char(&name_buff, '"');
				state = state_string_dquote;
			} else if(c == 't') {
				ds_insert_char(&name_buff, '\t');
				state = state_string_literal;
			} else if(isdigit(c)) {
				memset(num_buff, '\0', sizeof(num_buff));
				num_buff[0] = c;
				state = state_o_escape_first;
			} else if(c == '\\') {
				ds_insert_char(&name_buff, '\\');
				state = state_string_literal;
			} else {
				add_err("[E] Uknown escape sequence in string literal\n", RV_LEX, line);
			}

			break;

		case state_string_dquote:
			if(c == '\\') {
				state = state_string_escape;
			} else if (c != '\n') {
				ds_insert_char(&name_buff, c);
				state = state_string_literal;
			} else {
				add_err("[E] String literal is not corectly finished\n", RV_LEX, line);
			}

			break;

		case state_string_literal:
			if(c == '\\') {
				state = state_string_escape;
			} else if(c == '"') {
				state = state_initial;
				token_name_add(token, &name_buff);
				token->type = token_string_literal;
				return token;
			} else if (c != '\n' && c != EOF && c > 31) {
				ds_insert_char(&name_buff, c);
			} else {
				add_err("[E] String can be only expressed on one line\n", RV_LEX, line);
			}

			break;

		case state_o_escape_first:
			if(isdigit(c)) {
				num_buff[1] = c;
				state = state_o_escape_second;
			} else {
				add_err("[E] Expected digit in string escape sequence\n", RV_LEX, line);
			}

			break;

		case state_o_escape_second:
			if(isdigit(c)) {
				char * err;
				num_buff[2] = c;
				num_buff[3] = '\0';
				debug_print("[LEX][M] num_buff = %s\n", num_buff);
				long escapeNumLong = strtol(num_buff, &err, 10); // long kvoli osetreniu chyby

				// Osetrenie chyby pri prevode cisla
				if(*err != '\0') {
					parameter_error();
				}

				if(escapeNumLong > 255 || escapeNumLong <= 0) {
					add_err("[E] String escape sequence is out of bounds\n", RV_LEX, line);
				}

				char escapeNum = escapeNumLong;

				debug_print("[LEX][M] Escape cislo bolo prevedene na: %c\n", escapeNum);
				ds_insert_char(&name_buff, escapeNum);
				state = state_string_literal;
			} else {
				add_err("[E] Expected digit in string escape sequence\n", RV_LEX, line);
			}

			break;

		case state_identifier: {
			if(isalnum(c) || c == '_') {
				ds_insert_char(&name_buff, c);
			} else {
				ungetc(c, source_file); //posun znaku o 1 spat
				token->type = token_id;
				find_identifier(token, &name_buff); //hladaj keyword
				return token;
			}
		}
		break;

		case state_int: {
			if(isdigit(c)) {
				ds_insert_char(&name_buff, c);
			} else if(c == '.') {
				ds_insert_char(&name_buff, c);
				state = state_dot;
			} else if (c == 'e') {
				ds_insert_char(&name_buff, c);
				state = state_exp_begin;
			} else {
				ungetc(c, source_file);
				token->type = token_integer_literal;
				token = token_name_add(token, &name_buff);
				return token;
			}
		}

		break;

		case state_dot:
			if(isdigit(c)) {
				ds_insert_char(&name_buff, c);
				state = state_double;
			} else {
				add_err("[E] Expected digit after '.' in floating point literal\n", RV_LEX,
				        line);
			}

			break;

		case state_exp_begin:
			if(isdigit(c)) {
				ds_insert_char(&name_buff, c);
				state = state_exp;
			} else if(c == '+' || c == '-') {
				ds_insert_char(&name_buff, c);
				state = state_exp_sign;
			} else {
				add_err("[E] Expected digit or sign(+/-) after 'E' in floating point exponent notation\n",
				        RV_LEX, line);
			}

			break;

		case state_exp_sign:
			if(isdigit(c)) {
				state = state_exp;
			} else {
				add_err("[E] Expected digit after sign(+/-) in floating point exponent notation\n",
				        RV_LEX, line);
			}

			break;

		case state_double:
			if(isdigit(c)) {
				ds_insert_char(&name_buff, c);
			} else if (c == 'e') {
				ds_insert_char(&name_buff, c);
				state = state_exp_begin;
			} else {
				ungetc(c, source_file);
				token->type = token_floatingpoint_literal;
				token = token_name_add(token, &name_buff);
				return token;
			}

			break;

		case state_exp:
			if(isdigit(c)) {
				ds_insert_char(&name_buff, c);
			} else {
				ungetc(c, source_file);
				token->type = token_floatingpoint_literal;
				token = token_name_add(token, &name_buff);
				return token;
			}

			break;

		case state_add: { // +
			if(c == '=') { // +=
				token->type = token_add_eq;
				token = token_name_add(token, &name_buff);
				return token;
			} else {
				ungetc(c, source_file);
				token->type = token_add;
				token = token_name_add(token, &name_buff);
				return token;
			}
		}
		break;

		case state_sub: { // -
			if(c == '=') { // -=
				token->type = token_sub_eq;
				token = token_name_add(token, &name_buff);
				return token;
			} else {
				ungetc(c, source_file);
				token->type = token_sub;
				token = token_name_add(token, &name_buff);
				return token;
			}
		}
		break;

		case state_multip: { // *
			if(c == '=') { // *=
				token->type = token_mul_eq;
				token = token_name_add(token, &name_buff);
				return token;
			} else {
				ungetc(c, source_file);
				token->type = token_mul;
				token = token_name_add(token, &name_buff);
				return token;
			}
		}
		break;

		case state_int_div: {

			if(c == '=') { // \=
				token->type = token_div_int_eq;
				token = token_name_add(token, &name_buff);
				return token;
			} else {
				ungetc(c, source_file);
				token->type = token_div_int;
				token = token_name_add(token, &name_buff);
				return token;
			}
		}
		break;

		case state_slash:
			if (c == '=') {
				token->type = token_div_double_eq;
				token = token_name_add(token, &name_buff);
				return token;

			} else if(c == '\'') {
				state = state_multiline_comment;
			} else {
				ungetc(c, source_file);
				token->type = token_div_double;
				token = token_name_add(token, &name_buff);
				return token;
			}

			break;

		case state_less:
			if (c == '=') {
				token->type = token_le;
				token = token_name_add(token, &name_buff);
				return token;
			} else if (c == '>') {
				token->type = token_ne;
				token = token_name_add(token, &name_buff);
				return token;
			} else {
				token->type = token_lt;
				token = token_name_add(token, &name_buff);
				return token;
			}

			break;

		case state_greater: {
			if (c == '=') {
				token->type = token_ge;
				token = token_name_add(token, &name_buff);
				return token;
			} else {
				token->type = token_gt;
				token = token_name_add(token, &name_buff);
				return token;
			}
		}
		break;

		case state_multiline_comment:
			if (c == '\'') {
				state = state_multiline_comment_end;
			} else if (c == '\n') {
				line++;
				token->line = line;
			} else if (c == EOF) {
				add_err("[E] Unfinished multiline comment\n", RV_LEX, line);
			}

			break;

		case state_oneline_comment:
			if (c == '\n') {
				line++;
				token->type = token_eol;
				state = state_initial;
				return token;
			} else if (c == EOF) {
				add_err("[E] Unfinished single line comment\n", RV_LEX, line);
			}

			break;

		case state_multiline_comment_end:
			if (c == '/') {
				state = state_initial;
			} else if(c != '\'') {
				state = state_multiline_comment;
			} else if(c == EOF) {
				add_err("[E] Unfinished multiline comment\n", RV_LEX, line);
			}

			break;

		}
	} while(1);
}

TToken * token_get_ieol() {
	TToken * token = token_get();

#ifdef DEBUG
	print_token(token);
#endif /* DEBUG */

	while(token->type == token_eol) {
		debug_puts("Skipping new line\n");
		token = token_get();
#ifdef DEBUG
		print_token(token);
#endif /* DEBUG */
	}

	return token;
}

TType_var getVarType(TToken * t) {
	switch(t->type) {
	case token_id:
		if(BSTSearchNode(GlobalTree, t->name)) {
			return searchFuncReturnType(t->name);
		} else if (BSTSearchNode(LocalTree, t->name)) {
			return searchVarType(LocalTree, t->name);
		} else {
			return t->var_type;
		}

	case token_string_literal:
		return var_string;

	case token_integer_literal:
		return var_integer;

	case token_floatingpoint_literal:
		return var_double;

	default:
		return var_invalid;
	}

	return var_invalid;
}

void token_gen_uniq_name(TToken * t) {
	static long uniq = 0;
	t->name = malloc(sizeof(char) * 0x30);

	if(t->name == NULL) {
		allocation_error();
	}

	strcpy(t->name, "$uniq");
	sprintf(t->name + 5, "%09ld", uniq);
	uniq++;
}

void ds_init(dynamic_string * s, size_t init_size) {
	if(init_size == 0) {
		parameter_error();
	}

	s->str  = NULL;
	s->size = init_size;
	s->used = 0;
	//s->str[0] = '\0';
}

void ds_insert_char(dynamic_string * s, char c) {
	if(s->str == NULL) {
		s->str  = malloc(sizeof(char) * s->size);

		if(s->str == NULL) {
			allocation_error();
		}

		memset(s->str, '\0', s->size);

		s->used = 1;
		s->str[0] = '\0';
	}

	if(s->used >= s->size - 1) {
		s->size *= 2;
		s->str   = realloc(s->str, s->size * sizeof(char));
		debug_print("[D] Dynamic string realloc size = %zd\n", s->size);
	}

	s->str[s->used - 1] = c;
	s->used++;
	s->str[s->used] = '\0';
}

void ds_insert_string(dynamic_string * s, char * str) {
	if(s->str == NULL) {
		s->str  = malloc(sizeof(char) * s->size);

		if(s->str == NULL) {
			allocation_error();
		}

		s->used = 1;
		s->str[0] = '\0';
	}

	size_t str_len = strlen(str);

	if(s->used + str_len > s->size) {
		s->size *= 2;
		s->str   = realloc(s->str, s->size * sizeof(char));
		debug_print("[D] Dynamic string realloc size = %zd\n", s->size);
	}

	strncat(s->str, str, str_len);
	s->used += str_len;
}

void ds_free(dynamic_string * s) {
	s->size = 0;
	s->used = 0;
}
