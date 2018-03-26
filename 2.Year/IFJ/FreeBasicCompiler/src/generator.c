//******************************************//
//part:       IFJ/ generator.h              //
//team members: M. Kastak      <xkasta02>   //
//              J. Drab        <xdrabj00>   //
//              Ch. Farkas     <xfarka06>   //
//              V. Cervenanska <xcerve23>   //
//written by: Ch. Farkas, M. Kastak         //
//******************************************//

#include <stdlib.h>
#include <string.h>

#include "err.h"
#include "generator.h"
#include "debug.h"

const char * instruction_string_type[] = {
	"ins_MOVE",
	"ins_CREATEFRAME",
	"ins_PUSHFRAME",
	"ins_POPFRAME",
	"ins_DEFVAR",
	"ins_CALL",
	"ins_RETURN",
	"ins_PUSHS",
	"ins_POPS",
	"ins_CLEARS",
	"ins_ADD",
	"ins_SUB",
	"ins_MUL",
	"ins_DIV",
	"ins_LT",
	"ins_GT",
	"ins_EQ",
	"ins_AND",
	"ins_OR",
	"ins_NOT",
	"ins_ADDS",
	"ins_SUBS",
	"ins_MULS",
	"ins_DIVS",
	"ins_LTS",
	"ins_GTS",
	"ins_EQS",
	"ins_ANDS",
	"ins_ORS",
	"ins_NOTS",
	"ins_INT2FLOAT",
	"ins_FLOAT2INT",
	"ins_FLOAT2R2EINT",
	"ins_FLOAT2R2OINT",
	"ins_INT2CHAR",
	"ins_STRI2INT",
	"ins_INT2FLOATS",
	"ins_FLOAT2INTS",
	"ins_FLOAT2R2EINTS",
	"ins_FLOAT2R2OINTS",
	"ins_INT2CHARS",
	"ins_STRI2INTS",
	"ins_READ",
	"ins_WRITE",
	"ins_CONCAT",
	"ins_STRLEN",
	"ins_GETCHAR",
	"ins_SETCHAR",
	"ins_TYPE",
	"ins_LABEL",
	"ins_JUMP",
	"ins_JUMPIFEQ",
	"ins_JUMPIFNEQ",
	"ins_JUMPIFEQS",
	"ins_JUMPIFNEQS",
	"ins_BREAK",
	"ins_DPRINT"
};

tIns * genIns (TToken * op1, TToken * op2, TToken * res, tInsType type) {
	tIns * newIns = malloc(sizeof(struct sIns));

	if (newIns == NULL)
		allocation_error();

	newIns->op1 = op1;
	newIns->op2 = op2;
	newIns->res = res;
	newIns->type = type;

	return newIns;
}

tInsList * initInsList() {
	tInsList * list = malloc(sizeof(struct sInsList));

	if (list == NULL)
		allocation_error();

	list->active = NULL;
	list->first = NULL;
	list->last = NULL;

	globalList = list;
	return list;
}

void freeInsList(tInsList * l) {
	tListItem * tmpItem = l->first;

	while (l->first != NULL) {
		tmpItem = l->first;
		l->first = l->first->next;

		free(tmpItem->instruction);
		free(tmpItem);
	}

}

tListItem * InsListInsert(tIns * ins) {
	tListItem * newItem = malloc(sizeof(struct sListItem));

	if (newItem == NULL)
		allocation_error();

	newItem->next = NULL;
	newItem->instruction = ins;

	if(globalList->first == NULL) {
		globalList->first = newItem;
		globalList->last = newItem;
		newItem->prev = NULL;
	} else {
		globalList->last->next = newItem;
		newItem->prev = globalList->last;
		globalList->last = newItem;
	}

	return newItem;
}

void generateCode() {
	debug_puts(ANSI_COLOR_CYAN "Generating instructions...\n" ANSI_COLOR_RESET);
	printf(".IFJcode17\n");
	tListItem * iter = globalList->first;

	while(iter != NULL) {
#ifdef DEBUG
		print_instruction(iter->instruction);
#endif /* DEBUG */
		generateStringIns(iter->instruction);
		iter = iter->next;
	}

	debug_puts(ANSI_COLOR_CYAN "End of generating instructions...\n"
	           ANSI_COLOR_RESET);
}

void print_string_for_instruction(char * s) {
	size_t i;

	for(i = 0; i < strlen(s); ++i) {
		if((s[i] >= 0 && s[i] <= 32) || s[i] == 92) {
			printf("\\%03d", s[i]);
		} else {
			putchar(s[i]);
		}
	}
}

void generate_operation(TToken * o) {
	switch(o->type) {
	case token_add:
		InsListInsert(genIns(NULL, NULL, NULL, ins_ADDS));
		return;

	case token_sub:
		InsListInsert(genIns(NULL, NULL, NULL, ins_SUBS));
		return;

	case token_mul:
		InsListInsert(genIns(NULL, NULL, NULL, ins_MULS));
		return;

	case token_div_int:
	case token_div_double:
		InsListInsert(genIns(NULL, NULL, NULL, ins_DIVS));
		return;

	default:
		return;
	}

}

int printType(TToken * op) {
	if (op->type == token_integer_literal) {
		printf("int@%s", op->name);
	} else if (op->type == token_floatingpoint_literal) {
		printf("double@%s", op->name);
	} else if (op->type == token_string_literal) {
		printf("string@");
		print_string_for_instruction(op->name);
	} else if (op->type == token_id) {
		printf("LF@%s", op->name);
	} else return 1;

	return 0;
}


void generateStringIns(tIns * ins) {

	switch (ins->type) {
	case ins_MOVE:
		printf("MOVE LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		break;

	case ins_CREATEFRAME:
		printf("CREATEFRAME");
		break;

	case ins_PUSHFRAME:
		printf("PUSHFRAME");
		break;

	case ins_POPFRAME:
		printf("POPFRAME");
		break;

	case ins_DEFVAR:
		printf("DEFVAR LF@%s", ins->res->name);
		break;

	case ins_CALL:
		printf("CALL %s", ins->res->name);
		break;

	case ins_RETURN:
		printf("RETURN");
		break;

	case ins_PUSHS:
		printf("PUSHS ");
		printType(ins->res);

		break;

	case ins_POPS:
		printf("POPS ");
		printType(ins->res);
		break;

	case ins_CLEARS:
		printf("CLEARS");
		break;

	case ins_ADD:
		printf("ADD LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_SUB:
		printf("SUB LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_MUL:
		printf("MUL LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_DIV:
		printf("DIV LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_LT:
		printf("LT LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_GT:
		printf("GT LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_EQ:
		printf("EQ LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_AND:
		break;

	case ins_OR:
		break;

	case ins_NOT:
		break;

	case ins_ADDS:
		printf("ADDS\n");
		break;

	case ins_SUBS:
		printf("SUBS\n");
		break;

	case ins_MULS:
		printf("MULS\n");
		break;

	case ins_DIVS:
		printf("DIVS\n");
		break;

	case ins_LTS:
		printf("LTS LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_GTS:
		printf("GTS LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_EQS:
		printf("EQS LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_ANDS:
		break;

	case ins_ORS:
		break;

	case ins_NOTS:
		break;

	case ins_INT2FLOAT:
		printf("INT2FLOAT LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		break;

	case ins_FLOAT2INT:
		printf("FLOAT2INT LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		break;

	case ins_FLOAT2R2EINT:
		printf("FLOAT2R2EINT LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		break;

	case ins_FLOAT2R2OINT:
		printf("FLOAT2R2OINT LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		break;

	case ins_INT2CHAR:
		printf("INT2CHAR LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		break;

	case ins_STRI2INT:
		printf("STRI2INT LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_INT2FLOATS:
		printf("INT2FLOATS LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		break;

	case ins_FLOAT2INTS:
		printf("FLOAT2INTS LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		break;

	case ins_FLOAT2R2EINTS:
		printf("FLOAT2R2EINTS LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		break;

	case ins_FLOAT2R2OINTS:
		printf("FLOAT2R2OINTS LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		break;

	case ins_INT2CHARS:
		printf("INT2CHARS LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		break;

	case ins_STRI2INTS:
		printf("STRI2INTS LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_READ:
		printf("READ LF@%s ", ins->res->name);

		switch(ins->op1->type) {
		case var_integer:
			printf("int");
			break;

		case var_double:
			printf("float");
			break;

		case var_bool:
			printf("bool");
			break;

		case var_string:
			printf("string");
			break;

		default:
			break;
		}

		break;

	case ins_WRITE:
		printf("WRITE LF@%s ", ins->res->name);
		break;

	case ins_CONCAT:
		printf("CONCAT LF@%s LF@%s LF@%s",
		       ins->res->name,
		       ins->op1->name,
		       ins->op2->name);
		break;

	case ins_STRLEN:
		printf("STRLEN LF@%s LF@%s",
		       ins->res->name,
		       ins->op1->name);
		break;

	case ins_GETCHAR:
		printf("GETCHAR LF@%s LF@%s ",
		       ins->res->name,
		       ins->op1->name);

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_SETCHAR:
		printf("SETCHAR LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		printf("LF@%s", ins->op2->name);

		break;

	case ins_TYPE:
		printf("TYPE LF@%s ", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		break;

	case ins_LABEL:
		printf("LABEL %s", ins->res->name);
		break;

	case ins_JUMP:
		printf("JUMP %s", ins->res->name);
		break;

	case ins_JUMPIFEQ:
		printf("JUMPIFEQ %s", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_JUMPIFNEQ:
		printf("JUMPIFNEQ %s", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_JUMPIFEQS:
		printf("JUMPIFEQS %s", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_JUMPIFNEQS:
		printf("JUMPIFNEQS %s", ins->res->name);

		if (printType(ins->op1))
			printf("LF@%s", ins->op1->name);

		printf(" ");

		if (printType(ins->op2))
			printf("LF@%s", ins->op2->name);

		break;

	case ins_BREAK:
		printf("BREAK");
		break;

	case ins_DPRINT:
		printf("DPRINT %s", ins->res->name);
		break;

	default:
		break;
	}

	printf("\n");
}

void print_instruction(tIns * i) {

	fprintf(stderr, "[GEN] Instruction i: i->type = [%s]\n",
	        instruction_string_type[i->type]);

	if (i->op1 != NULL)
		print_token(i->op1);

	if (i->op2 != NULL)
		print_token(i->op2);

	if (i->res != NULL)
		print_token(i->res);

}
