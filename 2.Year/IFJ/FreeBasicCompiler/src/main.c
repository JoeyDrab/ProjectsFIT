#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#include "lex.h"
#include "err.h"

int main (int argc, char * argv[]) {

	if(argc == 2) {
		FILE * source_file = fopen(argv[1], "r");

		if(source_file == NULL) {
		    file_open_error();
		}

		lex_init(source_file);
	} else if (argc == 1) {
		lex_init(stdin);
	} else {
		fprintf(stderr, "[E] Nespravny pocet parametrov!\n");
		return -1;
	}

	// Inicializacia vypisu chyb
	init_error_handling();

	/*
	error_type e = error_lex;
	add_err("Skuska vypisu chyb", e, 42);
	*/
	

	TToken * t;
	do {
		t = token_get();
		print_token(t);

		if(token->type != token_eof) {
			token_free(t);
		}
	} while(token->type != token_eof);

	token_free(t); // sem sa dostne len EOF

	finalize_error_handling();

	return RV_INTERN; // v pripade ze sa nieco pokazi vo finalize, vratime chybu
}
