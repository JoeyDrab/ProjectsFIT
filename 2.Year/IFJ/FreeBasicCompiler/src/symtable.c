//__________________________________________//
//******************************************//
//part:   IFJ/ ial.h      				    //
//team members: M. Kastak, J. Drab, 	    //
//        Ch. Farkas, V. Cervenanska  		//
//written by: 	J.Drab	            			//
//__________________________________________//
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#include "symtable.h"



void BSTInit(tBSTNodePtr * RootPtr) {
	*RootPtr = NULL;
}

bool BSTSearchNode (tBSTNodePtr RootPtr, char * K)	{
	signed int left = 0;
	signed int right = 0;

	if(RootPtr != NULL) {
		if( strcmp( RootPtr->Key, K) != 0 ) {
			if((RootPtr->LPtr != NULL) && (strcmp(RootPtr->Key, K) > 0 )) {
				left = BSTSearchNode(RootPtr->LPtr, K);
			}

			if((left == 0) && (RootPtr->RPtr != NULL) && (strcmp(RootPtr->Key, K) < 0)) {
				right = BSTSearchNode(RootPtr->RPtr, K);
			}

			if(left != 0)
				return left;
			else
				return right;

		} else { // if RootPtr->Key == K
			return true;
		}
	} else return false;

}

bool BSTCheckType (tBSTNodePtr RootPtr, char * K, TType_var typ)	{
	signed int left = 0;
	signed int right = 0;

	if(RootPtr != NULL) {
		if( strcmp( RootPtr->Key, K) != 0 ) {
			if((RootPtr->LPtr != NULL) && (strcmp(RootPtr->Key, K) > 0 )) {
				left = BSTCheckType(RootPtr->LPtr, K, typ);
			}

			if((left == 0) && (RootPtr->RPtr != NULL) && (strcmp(RootPtr->Key, K) < 0)) {
				right = BSTCheckType(RootPtr->RPtr, K, typ);
			}

			if(left != 0)
				return left;
			else
				return right;

		} else { // if RootPtr->Key == K
			if(typ == RootPtr->type) {
				return true;
			}
			else 
				return false;
		}
	} else return false;

}

bool BSTSearchFunc (tBSTNodePtr RootPtr, char * K)	{
	signed int left = 0;
	signed int right = 0;

	if(RootPtr != NULL) {
		if( strcmp( RootPtr->Key, K) != 0 ) {
			if((RootPtr->LPtr != NULL) && (strcmp(RootPtr->Key, K) > 0 )) {
				left = BSTSearchFunc(RootPtr->LPtr, K);
			}

			if((left == 0) && (RootPtr->RPtr != NULL) && (strcmp(RootPtr->Key, K) < 0)) {
				right = BSTSearchFunc(RootPtr->RPtr, K);
			}

			if(left != 0)
				return left;
			else
				return right;

		} else { // if RootPtr->Key == K
			if (RootPtr->is_fnce == true)
				return true;
			else
				return false;
		}
	} else return false;

}

int BSTSearchType (tBSTNodePtr RootPtr, char * K, TType_var * type) {
	signed int left = 0;
	signed int right = 0;

	if(RootPtr != NULL) {
		if( strcmp( RootPtr->Key, K) != 0 ) {
			if((RootPtr->LPtr != NULL) && (strcmp(RootPtr->Key, K) > 0 )) {
				left = BSTSearchType(RootPtr->LPtr, K, type);
			}

			if((left == 0) && (RootPtr->RPtr != NULL) && (strcmp(RootPtr->Key, K) < 0)) {
				right = BSTSearchType(RootPtr->RPtr, K, type);
			}

			if(left != 0)
				return left;
			else
				return right;

		} else { // if RootPtr->Key == K
			*type = RootPtr->type;
			return 1;
		}
	} else return 0;

}

int BSTSearchInitialized (tBSTNodePtr RootPtr, char * K)	{
	signed int left = 0;
	signed int right = 0;

	if(RootPtr != NULL) {
		if((RootPtr->LPtr != NULL) && (strcmp(RootPtr->Key, K) > 0 )) {
			if(RootPtr->LPtr != NULL) {
				left = BSTSearchInitialized(RootPtr->LPtr, K);
			}

			if((left == 0) && (RootPtr->RPtr != NULL) && (strcmp(RootPtr->Key, K) < 0)) {
				right = BSTSearchInitialized(RootPtr->RPtr, K);
			}

			if(left != 0)
				return left;
			else
				return right;

		} else { // if RootPtr->Key == K
			if (RootPtr->is_initialized == true)
				return 1;
			else
				return 2;
		}
	} else return 0;

}

int BSTCheckFunc ( tBSTNodePtr RootPtr, char * K, TType_var typ) {
	signed int left = 0;
	signed int right = 0;

	if(RootPtr != NULL) {

		if( strcmp( RootPtr->Key, K) != 0 ) {
			if((RootPtr->LPtr != NULL) && (strcmp(RootPtr->Key, K) > 0 )) {
				left = BSTCheckFunc(RootPtr->LPtr, K, typ);
			}

			if((left == 0) && (RootPtr->RPtr != NULL) && (strcmp(RootPtr->Key, K) < 0)) {
				right = BSTCheckFunc(RootPtr->RPtr, K, typ);
			}

			if(left != 0)
				return left;
			else
				return right;

		} else {
			/* if RootPtr->Key == K  */
			if (((RootPtr)->is_fnce == true) && ((RootPtr)->type == typ)) {
				return 1;
			} else
				return 2;
		}
	} else return 0;
}

void BSTInsert (tBSTNodePtr * RootPtr, char * K, bool boolfunc, bool boolinit,
                TType_var typ)	{

	if( boolfunc == true && boolinit == true) {
		fprintf(stderr,
		        "Err: implicit statement for '%s': static = true, function = true \n", K);
		return;
	}

	if(*RootPtr == NULL) {
		*RootPtr = malloc(sizeof(struct tBSTNode));

		if(*RootPtr != NULL) {
			//(*RootPtr)->Key = malloc((strlen(K)+1)*sizeof(char));
			(*RootPtr)->Key = K;
			(*RootPtr)->is_fnce = boolfunc;
			(*RootPtr)->is_initialized = boolinit;
			(*RootPtr)->type = typ;
			(*RootPtr)->LPtr = NULL;
			(*RootPtr)->RPtr = NULL;
			debug_print("[SYM][J] Ientifikator v strome: %s\n", (*RootPtr)->Key);
		} else
			return;
	} else {

		if( strcmp((*RootPtr)->Key, K) > 0 ) {
			BSTInsert(&(*RootPtr)->LPtr, K, boolfunc, boolinit, typ);
		} else if( strcmp((*RootPtr)->Key, K) < 0 ) {
			BSTInsert(&(*RootPtr)->RPtr, K, boolfunc, boolinit, typ);
		} else if( strcmp((*RootPtr)->Key, K) == 0 ) {
			return;
		}
	}
			

}

void BSTDispose (tBSTNodePtr * RootPtr) {
	if((*RootPtr) != NULL) {
		if ((*RootPtr)->LPtr != NULL)
			BSTDispose(&(*RootPtr)->LPtr);

		if ((*RootPtr) != NULL)
			BSTDispose(&(*RootPtr)->RPtr);

		*RootPtr = NULL;
		free(*RootPtr);
	} else
		return;

}
///////////////////////////////////////////////////////////////////////
void InitListFunc (tList * L) {
	//*L = NULL;
	L->Head = NULL;
}
///////////////////////////////////////////////////////////////////////
void DisposeListFunc (tList * L) {
	tParamPtr temp = L->Head;
	L->Head = NULL;


	while (temp != NULL) {
		tParamPtr tempPrev = temp->next;
		free(temp);
		temp = tempPrev;
	}

}
///////////////////////////////////////////////////////////////////////
void WriteToTree (tList * L, tBSTNodePtr * RootPtr) {
	tParamPtr temp = L->Head;
	L->Head = NULL;

	while (temp != NULL) {
		tParamPtr tempPrev = temp->next;
		BSTInsert(&(*RootPtr), temp->name, false, false, temp->type);
		temp = tempPrev;
	}
}
///////////////////////////////////////////////////////////////////////
void InsertParam (tList * L, char * name, TType_var typ) {
	tParamPtr param = malloc(sizeof(struct tParam));

	if (param == NULL)
		return;

	//Ulozim nazov a typ do parametru
	//do ukazovatela na prvok vlozim ukazovatel na predchadzajuci prvok zoznamu
	param->name = name;
	param->type = typ;
	param->next = L->Head;
	L->Head = param;

	debug_print("[SYM][J] ID parametru v liste: %s\n", param->name);
	//debug_print("[SYM][J] 257sym|||||Typ parametru v liste: %d\n", param->type);

}
///////////////////////////////////////////////////////////////////////
void func_set_id(char * name) {
	my_func_id = malloc((strlen(name) + 1) * sizeof(char));

	if(my_func_id != NULL) {
		strcpy(my_func_id, name);
	}
	debug_print("[SYM][J] ID funkcie: %s\n", my_func_id);
	InitListFunc (&FuncList);
}
///////////////////////////////////////////////////////////////////////
void func_set_type_and_write(tBSTNodePtr * RootGlob, char * typ) {

	if( strcmp("integer", typ) == 0 ) {
		BSTInsert(&(*RootGlob), my_func_id, true, false, var_integer);
	} else if( strcmp("double", typ) == 0 ) {
		BSTInsert(&(*RootGlob), my_func_id, true, false, var_double);
	} else if( strcmp("string", typ) == 0 ) {
		BSTInsert(&(*RootGlob), my_func_id, true, false, var_string);
	} else if( strcmp("bool", typ) == 0 ) {
		BSTInsert(&(*RootGlob), my_func_id, true, false, var_bool);
	} else {
		fprintf(stderr, "Err: implicit statement in symtable.c/func_set_id()"
		        " '%s': type is incopatibile! \n", typ);
		return;
	}
	DisposeListFunc (&FuncList);
	/*strcpy(my_func_id, "");
	free(my_func_id);*/
	//printf("AFTER FREE, AFTER FREE, AFTER, FREE: %s\n", my_func_id);
	/*strcpy(temp_param, "");
	free(temp_param);*/

}
///////////////////////////////////////////////////////////////////////
void func_set_type_and_write_all(tBSTNodePtr * RootGlob, tBSTNodePtr * RootLoc,
                             char * typ) {

	if( strcmp("integer", typ) == 0 ) {
		BSTInsert(&(*RootGlob), my_func_id, true, false, var_integer);
	} else if( strcmp("double", typ) == 0 ) {
		BSTInsert(&(*RootGlob), my_func_id, true, false, var_double);
	} else if( strcmp("string", typ) == 0 ) {
		BSTInsert(&(*RootGlob), my_func_id, true, false, var_string);
	} else if( strcmp("bool", typ) == 0 ) {
		BSTInsert(&(*RootGlob), my_func_id, true, false, var_bool);
	} else {
		fprintf(stderr, "Err: implicit statement in symtable.c/func_set_id()"
		        " '%s': type is incopatibile! \n", typ);
		return;
	}
	WriteToTree(&FuncList, &(*RootLoc));
	DisposeListFunc (&FuncList);

}
///////////////////////////////////////////////////////////////////////
void function_set_param_name( char * name) { 
	temp_param = malloc((strlen(name) + 1) * sizeof(char));

	if(temp_param != NULL) {
		strcpy(temp_param, name);	// "parameter"
	}

	char * temp_name_param;
	temp_name_param = malloc((strlen(name) + 1) * sizeof(char));
	strcpy(temp_name_param, my_func_id); // "func"
	strcat(my_func_id, "$");	// my_func_id = "func$"
	strcat(my_func_id, temp_param);	// "my_func_id = func$parameter"
	strcpy(temp_param, my_func_id);
	strcpy(my_func_id, temp_name_param);
	free(temp_name_param);

	debug_print("[SYM][J] ID parametru: %s\n", temp_param);
}
///////////////////////////////////////////////////////////////////////
void function_set_param_type(char * type) { 
	if( strcmp("integer", type) == 0 ) {
		InsertParam (&FuncList, temp_param, var_integer);
	} else if( strcmp("double", type) == 0 ) {
		InsertParam (&FuncList, temp_param, var_double);
	} else if( strcmp("string", type) == 0 ) {
		InsertParam (&FuncList, temp_param, var_string);
	} else if( strcmp("bool", type) == 0 ) {
		InsertParam (&FuncList, temp_param, var_bool);
	} else {
		fprintf(stderr, "Err: symtable.c/func_set_type_and_write()"
		        " '%s': type is incopatibile! \n", type);
		return;
	}
}
///////////////////////////////////////////////////////////////////////
void DisposeAll(tBSTNodePtr * GlobalRoot, tBSTNodePtr * LocalRoot) {
	free(my_func_id);
	free(temp_param);
	DisposeListFunc (&FuncList);
	BSTDispose(GlobalRoot);
	BSTDispose(LocalRoot);
}

void remember_id(char * name) {
	identif_name = malloc((strlen(name) + 1) * sizeof(char));

	if(identif_name != NULL) {
		strcpy(identif_name, name);
	}
	debug_print("[SYM][J] remember_id: %s\n", identif_name);
}

void remember_type(char * name) {
	identif_type = malloc((strlen(name) + 1) * sizeof(char));

	if(identif_type != NULL) {
		strcpy(identif_type, name);
	}
	debug_print("[SYM][J] remember_type: %s\n", identif_type);
}
