//******************************************//
//part:       IFJ/ generator.h              //
//team members: M. Kastak      <xkasta02>   //
//              J. Drab        <xdrabj00>   //
//              Ch. Farkas     <xfarka06>   //
//              V. Cervenanska <xcerve23>   //
//written by: Ch. Farkas, M. Kastak         //
//******************************************//

#ifndef IFJ_GENERATOR_H
#define IFJ_GENERATOR_H

#include "lex.h"

extern const char * instruction_string_type[];

typedef enum {
	//Prace s ramci, volani funkcii
	ins_MOVE,
	ins_CREATEFRAME,
	ins_PUSHFRAME,
	ins_POPFRAME,
	ins_DEFVAR,
	ins_CALL,
	ins_RETURN,
	//Prace s datovym zasobnikem
	ins_PUSHS,
	ins_POPS,
	ins_CLEARS,
	//Aritmeticke, relacni, booleovske
	ins_ADD,
	ins_SUB,
	ins_MUL,
	ins_DIV,
	ins_LT,
	ins_GT,
	ins_EQ,
	ins_AND,
	ins_OR,
	ins_NOT,
	//Pre zasobnik
	ins_ADDS,
	ins_SUBS,
	ins_MULS,
	ins_DIVS,
	ins_LTS,
	ins_GTS,
	ins_EQS,
	ins_ANDS,
	ins_ORS,
	ins_NOTS,
	//Konverzni instrukcie
	ins_INT2FLOAT,
	ins_FLOAT2INT,
	ins_FLOAT2R2EINT,
	ins_FLOAT2R2OINT,
	ins_INT2CHAR,
	ins_STRI2INT,
	//Pre zasobnik
	ins_INT2FLOATS,
	ins_FLOAT2INTS,
	ins_FLOAT2R2EINTS,
	ins_FLOAT2R2OINTS,
	ins_INT2CHARS,
	ins_STRI2INTS,
	//Vstupno-vystupne instrukcie
	ins_READ,
	ins_WRITE,
	//Prace s retezci
	ins_CONCAT,
	ins_STRLEN,
	ins_GETCHAR,
	ins_SETCHAR,
	//Prace s typy
	ins_TYPE,
	//Instrukcie pro rizeni toku programu
	ins_LABEL,
	ins_JUMP,
	ins_JUMPIFEQ,
	ins_JUMPIFNEQ,
	//Pre zasobnik
	ins_JUMPIFEQS,
	ins_JUMPIFNEQS,
	//Ladici instrukce
	ins_BREAK,
	ins_DPRINT
} tInsType;

typedef struct sIns {
	TToken * op1;
	TToken * op2;
	TToken * res;
	tInsType type;
} tIns;

typedef struct sListItem {
	tIns * instruction;
	struct sListItem * next;
	struct sListItem * prev;
} tListItem;

typedef struct sInsList {
	tListItem * first;
	tListItem * last;
	tListItem * active;
} tInsList;

tInsList * globalList;

/**
 * Funkcia pouzivana pri debug, vypise obsah instrukcie
 *
 * @param i[in] instrukcia ktora ma byt vypisana
 */
void print_instruction(tIns * i);

/**
 * Funkcia ktora so zoznamu instrukcii vygeneruje vysledny program pre naslednu interpretaciu
 */
void generateCode();

/**
 * Pomocna funkcia ktora vypise jednu instrukciu
 *
 * @param i instrukcia ktora sa vypise
 */
void generateStringIns(tIns * ins);

/**
 * Funkcia ktora inicializuje zoznam instrukcii
 *
 * @return ukazatel na inicializovany zoznam
 */
tInsList * initInsList();

/**
 * Funkcia ktora z pamete uvolni zoznam instrukcii
 *
 * @param ukazatel na zoznam
 */
void freeInsList(tInsList *);

void generate_operation(TToken * o);

tListItem * InsListInsert(tIns *);

tIns * genIns (TToken * op1, TToken * op2, TToken * res, tInsType type);

int printType(TToken * op);


#endif //IFJ_GENERATOR_H
