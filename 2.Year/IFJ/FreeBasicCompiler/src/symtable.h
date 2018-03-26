//__________________________________________//
//******************************************//
//part:   IFJ/ ial.h         //
//team members: M. Kastak, J. Drab,     //
//        Ch. Farkas, V. Cervenanska  //
//written by: J.Drab            //
//__________________________________________//

#ifndef SYMTABLE_H
#define SYMTABLE_H

#include "debug.h"
#include "lex.h"

char * my_func_id;
char * temp_param;
char * identif_name;
char * identif_type;

/* Uzol stromu */
typedef struct tBSTNode {
	char * Key;			      // kluc = nazov premennej / funkcie
	bool is_fnce;			   // bool hodnota -> if (funkcia) then true
	bool is_initialized;			   // bool hodnota -> if (static) then true
	TType_var type;			   // tType_var hodnota, akeho typu je
	struct tBSTNode *
		LPtr;    // pointer na lavy podstrom
	struct tBSTNode *
		RPtr;    // pointer na pravy podstrom
} * tBSTNodePtr;

/*
func(int a, string b, double c) as bool
	char * name;	-> a , b , c
	TType_func type;	-> int , string , double
	struct tParam* Prev;	-> NULL , a , b
*/

/* Parametre funkcie */
typedef struct tParam {
	char * name;					// nazov (kluc) parametru (premennej)
	TType_var type;					// datovy typ parametru
	struct tParam * next;
} * tParamPtr;

typedef struct {
	tParamPtr Head;			// pointer na predchadzajuci prvok
} tList;

tList FuncList;

/* Funkcie pre binarny strom */
void BSTInit(tBSTNodePtr *);
/****************************************************/
/* 	BSTSearchNode  (Tree, Key);
	case  	true -> found
			false -> variable is not in a Tree
 */
bool BSTSearchNode  (tBSTNodePtr, char *);
/****************************************************/
/* 	BSTSearchFunc  (Tree, temp);
	case: 	true -> is_func = true
			false -> is_func = false
			false -> func is not in a Tree
 */
bool BSTSearchFunc  (tBSTNodePtr, char *);
/****************************************************/
/* 	n = BSTSearchType  (Tree, temp, typ);
	case n: 1 -> found .. type written to the 'typ'
			0 -> not found
 */
int BSTSearchType  (tBSTNodePtr, char *, TType_var *);
/****************************************************/
/* 	n = BSTSearchStatic  (Tree, temp);
	case n: 1 -> is_static = true
			2 -> is_static = false
			0 -> variable is not in a Tree
 */
int BSTSearchInitialized  (tBSTNodePtr, char *);
/****************************************************/
/* 	n = BSTCheckFunc  (Tree, func, subTree, integer);
	case n: 1 -> if inserted parameters are equel to node parameters
			2 -> if inserted parameters are not equel to node parameters
			0 -> function is not in a Tree
 */
int BSTCheckFunc ( tBSTNodePtr, char *, TType_var );
/*********************************************************************************/
/* 	BSTInsert  (Tree, variable, false, false, integer);
	- assign (*RootPtr)->Key = variable, (*RootPtr)->is_fnce = false,
			 (*RootPtr)->subtree = NULL, (*RootPtr)->is_stat = false,
			 (*RootPtr)->type = integer, (*RootPtr)->LPtr && RPtr = NULL;
 */
void BSTInsert (tBSTNodePtr *, char *, bool, bool, TType_var);
/************************************************************/
void BSTDispose(tBSTNodePtr *);

/* Funkcie pre linearny seznam funkcii */
void InitListFunc (tList *);
void DisposeListFunc (tList *);
void WriteToTree (tList *, tBSTNodePtr * );
void InsertParam (tList *, char *, TType_var);
void func_set_id( char * );
void func_set_type_and_write(tBSTNodePtr *,  char * );
void func_set_type_and_write_all(tBSTNodePtr *, tBSTNodePtr *,char * );
void function_set_param_name(char * );
void function_set_param_type( char * );
void DisposeAll(tBSTNodePtr *, tBSTNodePtr * );
void remember_id(char * );
void remember_type(char * );
#endif /* SYMTABLE_H */
