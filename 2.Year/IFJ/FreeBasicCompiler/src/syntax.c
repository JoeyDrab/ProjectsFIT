//******************************************//
//part:       IFJ/ syntax.c                 //
//team members: M. Kastak      <xkasta02>   //
//              J. Drab        <xdrabj00>   //
//              Ch. Farkas     <xfarka06>   //
//              V. Cervenanska <xcerve23>   //
//written by: M. Kastak, J. Drab            //
//******************************************//

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "generator.h"
#include "lex.h"
#include "debug.h"
#include "syntax.h"
#include "expression.h"
#include "symtable.h"
#include "err.h"

bool in_scope = false;

void next_token() {
	token = token_get();
#ifdef DEBUG
	print_token(token);
#endif /* DEBUG */

	while(token->type == token_eol) {
		debug_puts("Skipping new line\n");
		token = token_get();
		print_token(token);
	}
}

void next_expect_eol() {
	token = token_get();
#ifdef DEBUG
	print_token(token);
#endif /* DEBUG */
}

bool parse_prog() {
	debug_puts("[D] Parsing program\n");
	next_token();

	if((token->type == token_scope) || (token->type == token_declare)
	        || (token->type == token_function)) {
		TToken * main_label = token_init();
		main_label->name = malloc(sizeof(char) * 8);
		strncpy(main_label->name, "$main\0", 8);
		InsListInsert(genIns(NULL, NULL, main_label, ins_JUMP));

		if(parse_declaration_part()) {
			if(parse_main_scope()) {
				if(token->type == token_eof) {
					return true;
				}
			}
		}
	}

	return false;
}

bool parse_function() {
	debug_puts("[D] Parsing function\n");

	if(token->type == token_declare) {
		declar_define = true;
		Insert_ParListNode = true;
		next_token();

		if(token->type == token_function) {
			next_token();

			if(token->type == token_id) {
				if(BSTSearchNode(GlobalTree, token->name) == false) {
					func_set_id(token->name);
					next_token();

					if(token->type == token_parenthesis_left) {
						next_token();

						if(parse_definelist()) {
							if(token->type == token_parenthesis_right) {
								next_token();

								if(token->type == token_as) {
									next_token();

									TType_var var_type;

									if(parse_type(&var_type)) {
										func_set_type_and_write(&GlobalTree, identif_type);
										Insert_ParListNode = false;

										if(token->type == token_eol) {
											next_token();
											return true;
										}
									}
								}
							}
						}
					}
				} else
					add_err("[E] Function already declared!\n", RV_SEMA_OTHER, 0);
			}
		}
	} else if(token->type == token_function) {
		declar_define = false;
		next_token();


		if(token->type == token_id) {
			// TODO: definicia funkcie
			if(BSTSearchNode(GlobalTree, token->name))
				declar_yet = true;
			else {
				declar_yet = false;
				Insert_ParListNode = true;
			}

			InsListInsert(genIns(NULL, NULL, token, ins_LABEL));

			func_set_id(token->name);
			switch_scope_func = true;
			next_token();

			if(token->type == token_parenthesis_left) {
				next_token();

				if(parse_definelist()) {
					if(token->type == token_parenthesis_right) {
						next_token();

						if(token->type == token_as) {
							next_token();

							TType_var tmp;

							if(parse_type(&tmp)) { // TODO: EOL
								if(((declar_yet == true
								        && BSTSearchType (GlobalTree, my_func_id, identif_type)))
								        || declar_yet == false) {
									write_to_tree(declar_yet);

									if(token->type == token_eol) {
										if(declar_yet == false) {
											func_set_type_and_write(&GlobalTree, identif_type);
											Insert_ParListNode = false;
										}

										next_token();

										if(parse_slist()) {
											if(token->type == token_end) {
												next_token();

												if(token->type == token_function) {
													annul_func_name();
													DisposeListFunc();
													next_token();
													return true;
												}
											}
										}
									}
								} else
									add_err("[E] Invalid function type!\n", RV_SEMA_OTHER, 0);
							}
						}
					}
				}

			}
		}
	} else if(token->type == token_scope) {
		return true;
	}

	return false;
}

bool parse_declaration_part() {
	debug_puts("[D] Parsing declaration part\n");

	if((token->type == token_declare) || (token->type == token_function)) {
		/*
		bool declaration_part = parse_function();
		return declaration_part && parse_declaration_part();
		*/
		if(parse_function()) {
			if(parse_declaration_part()) {
				return true;
			}
		}
	} else if(token->type == token_scope) {
		return true;
	}

	return false;
}

bool parse_main_scope() {
	debug_puts("[D] Parsing main scope\n");

	if(token->type == token_scope) {
		in_scope = true;
		switch_scope_func = false;
		annul_func_name();
		next_token();

		TToken * main_label = token_init();
		main_label->name = malloc(sizeof(char) * 8);
		strncpy(main_label->name, "$main\0", 8);
		InsListInsert(genIns(NULL, NULL, main_label, ins_LABEL));

		InsListInsert(genIns(NULL, NULL, NULL, ins_CREATEFRAME));
		InsListInsert(genIns(NULL, NULL, NULL, ins_PUSHFRAME));

		if(parse_slist()) {
			if(token->type == token_end) {
				next_token();

				if(token->type == token_scope) {
					next_token();
					InsListInsert(genIns(NULL, NULL, NULL, ins_POPFRAME));
					return true;
				}
			}
		}
	}

	return false;
}

bool parse_slist() {
	debug_puts("[D] Parsing statement list\n");

	if((token->type == token_id) ||
	        (token->type == token_input) ||
	        (token->type == token_print) ||
	        (token->type == token_if) ||
	        (token->type == token_do) ||
	        (token->type == token_return) ||
	        (token->type == token_dim)) {
		//bool slist = parse_smt();
		if(parse_smt()) {
			if(token->type == token_eol) {
				next_token();
				return parse_slist();
			}
		}
	} else if((token->type == token_end) ||
	          (token->type == token_loop) ||
	          (token->type == token_else)) {
		return true;
	}

	return false;
}

bool parse_smt() {
	debug_puts("[D] Parsing statement\n");

	if(token->type == token_id) {
		TToken * ident = token;

		func_id_dollar(my_func_id, switch_scope_func);
		dollar_tok_name(id_dollar_is_or_not, token->name);

		next_token();

		if(token->type == token_eq) {
			next_token();
			TType_var expr_type;

			if(BSTSearchNode(GlobalTree, tokname) ||
			        BSTSearchNode(LocalTree, tokname) ) {
				debug_puts("[SYM][J] Premenna v strome najdena!\n");

				if((expr_type = searchVarType(GlobalTree, tokname)) == var_invalid) {
					if((expr_type = searchVarType(LocalTree, tokname)) == var_invalid) {
						add_err("[E] Identificator not declared!\n", RV_SEMA_UNDEF, 0);
					}
				}

				if(parse_expression(token, expr_type)) {
					return true;
				}
			} else {
				add_err("[E] Identificator not declared!\n", RV_SEMA_UNDEF, 0);
			}
		}
	} else if(token->type == token_input) {
		next_token();

		if(token->type == token_id) {
			if(BSTSearchNode(GlobalTree, token->name) ||
			        BSTSearchNode(LocalTree, token->name) ) {
				//debug_print("[SYM][J] Premenna v strome najdena!\n");
				next_expect_eol();
				return true;
			} else {
				add_err("[E] Identificator not declared!\n", RV_SEMA_UNDEF, 0);
			}

		}
	} else if(token->type == token_print) {
		next_token();

		if(parse_expression(token, var_invalid)) {
			TToken * tmp_var = token_init();
			token_gen_uniq_name(tmp_var);
			tmp_var->type = token_id;
			InsListInsert(genIns(NULL, NULL, tmp_var, ins_DEFVAR));
			InsListInsert(genIns(NULL, NULL, tmp_var, ins_POPS));
			InsListInsert(genIns(NULL, NULL, tmp_var, ins_WRITE));

			if(token->type == token_semicolon) {
				next_expect_eol();

				if(parse_output()) {
					return true;
				}
			}
		}
	} else if(token->type == token_if) {
		next_token();

		if(parse_expression(token, var_invalid)) { // TODO: var_invalid?
			if(token->type == token_then) {
				next_expect_eol();

				if(token->type == token_eol) {
					next_token();

					if(parse_slist()) {
						if(token->type == token_else) {
							next_expect_eol();

							if(token->type == token_eol) {
								next_token();

								if(parse_slist()) {
									if(token->type == token_end) {
										next_token();

										if(token->type == token_if) {
											next_expect_eol();
											return true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	} else if(token->type == token_do) {
		next_token();

		if(token->type == token_while) {
			next_token();

			if(parse_expression(token, var_invalid)) {
				if(token->type == token_eol) {
					next_token();

					if(parse_slist()) {
						if(token->type == token_loop) {
							next_expect_eol();
							return true;
						}
					}
				}
			}
		}
	} else if(token->type == token_return && !in_scope) {
		next_token();

		if(parse_expression(token, var_invalid)) {
			return true;
		}
	} else if(token->type == token_dim) {
		return parse_definelocal();
	}

	return false;
}

bool parse_define(TType_var * var_type) {
	debug_puts("[D] Parsing define\n");

	if(token->type == token_id) {
		remember_id(token->name);
		next_token();

		if(token->type == token_as) {
			next_token();

			if(parse_type(var_type)) {
				return true;
			}
		}
	}

	return false;
}

bool parse_definelocal() {
	debug_puts("[D] Parsing local declaration\n");

	if(token->type == token_dim) {
		next_token();

		if(token->name == NULL) { // TODO: dirty fix
			add_err("[E] Expected identifier\n", RV_SYNTAX, token->line);
		}

		TToken * var = token;

		remember_id(token->name);
		debug_print("[SYM][J] rmmbr_id(tok->name): %s\n", token->name);
		debug_print("[SYM][J] my_func_id: %s\n", my_func_id);
		debug_print("[SYM][J] switch_scope_func: %d\n", switch_scope_func);
		func_id_dollar(my_func_id, switch_scope_func);
		dollar_tok_name(id_dollar_is_or_not, identif_name);

		InsListInsert(genIns(NULL, NULL, token, ins_DEFVAR));

		if(BSTSearchNode(LocalTree, tokname) == false) {
			TType_var var_type;

			if(parse_define(&var_type)) {
				if(parse_initialization(var_type)) {
					InsListInsert(genIns(NULL, NULL, var, ins_POPS));
					return true;
				}
			}
		} else {
			add_err("[E] Variable already declared!\n", RV_SEMA_OTHER, 0);
		}
	}

	return false;
}

bool parse_type(TType_var * type) {
	if(token->type == token_string) {
		remember_type("string");
		next_expect_eol();
		*type = var_string;
		return true;
	} else if(token->type == token_double) {
		remember_type("double");
		next_expect_eol();
		*type = var_double;
		return true;
	} else if(token->type == token_integer) {
		remember_type("integer");
		next_expect_eol();
		*type = var_integer;
		return true;
	}

	*type = var_invalid;
	return false;
}

bool parse_definelist() {
	debug_puts("[D] Parsing define list\n");

	TType_var tmp;

	if(parse_define(&tmp)) {
		debug_print("[SYM][J] identif_name: %s\n", identif_name);
		function_set_param_name(identif_name, declar_define);
		debug_print("[SYM][J] identif_type: %s\n", identif_type);
		function_set_param_type(identif_type, declar_define);

		if(parse_deflistcomma()) {
			return true;
		}
	} else if(token->type == token_parenthesis_right) {
		return true;
	}

	return false;
}

bool parse_deflistcomma() {
	debug_puts("[D] Parsing define list comma\n");

	if(token->type == token_comma) {
		next_token();

		TType_var tmp; // TODO: Co uz narobim

		if(parse_define(&tmp)) {
			debug_print("[SYM][J] 11111 identif_name: %s\n", identif_name);
			function_set_param_name(identif_name, declar_define);
			debug_print("[SYM][J] 22222 identif_type: %s\n", identif_type);
			function_set_param_type(identif_type, declar_define);

			if(parse_deflistcomma()) {
				return true;
			}
		}
	} else if(token->type == token_parenthesis_right) {
		return true;
	}

	return false;
}

bool parse_initialization(TType_var init_type) {
	debug_puts("[D] Parsing initialization\n");

	if(token->type == token_eq) {
		convert_and_insert (&LocalTree, tokname, true, identif_type);
		next_token();

		if(parse_expression(token, init_type)) {
			return true;
		}
	} else if(token->type == token_eol) { // TODO: riesenie novych riadkov
		convert_and_insert (&LocalTree, tokname, false, identif_type);
		return true;
	}

	return false;
}

bool parse_output() {
	debug_puts("[D] Parsing output\n");

	if(token->type == token_eol) {
		return true;
	}

	if(parse_expression(token, var_invalid)) {
		TToken * tmp_var = token_init();
		token_gen_uniq_name(tmp_var);
		tmp_var->type = token_id;
		InsListInsert(genIns(NULL, NULL, tmp_var, ins_DEFVAR));
		InsListInsert(genIns(NULL, NULL, tmp_var, ins_POPS));
		InsListInsert(genIns(NULL, NULL, tmp_var, ins_WRITE));

		if(token->type == token_semicolon) {
			next_expect_eol();
			return parse_output();
		}
	}

	return false;
}
