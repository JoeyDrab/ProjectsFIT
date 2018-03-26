#include <string.h>
#include <stdbool.h>

#include "../symtable.h"

tBSTNodePtr GlobalTree;
tBSTNodePtr	LocalTree;
tList Func1;
tList Func2;

char * K;
bool boolfunc;
bool boolstat;
int pravda;
TType_var type;
/*
void print_elements_of_list(tList TL)	{
	tList TempList = TL;
	int i = 0;
	printf("\t------------------------\n");
	while ((TempList.Head != NULL) && (i<100))	{

		printf("\t name: %s | type: %d\n",TempList.Head->name, TempList.Head->type);

		TempList.Head = TempList.Head->next;
		i++;
	}
}
*/

/* .......................... sekce volani jednotlivych testu .............................*/

int main(void)			{

	printf("Binarni vyhledavaci strom\n");
	printf("=========================\n");

	printf("[TEST01]\n");
	printf("Test inicializace....\n");
	BSTInit(&GlobalTree);

	if (GlobalTree == NULL) {
		printf("strom 'GlobalTree' je prazdny\n");

	}

	BSTInit(&LocalTree);

	if (GlobalTree == NULL) {
		printf("strom 'LocalTree' je prazdny\n");

	}

	printf("=================================================\n");

	printf("[TEST02]\n");
	printf("Vlozime prvni prvek:\n"
	       " (GlobalTree Key: Huh,   funkcia: false, staticka: true,  typ: string)\n"
	       " (LocalTree  Key: Fakju, funkcia: false, staticka: false, typ: integer)\n");

	K = "huh";
	boolfunc = false;
	boolstat = true;
	type = var_string;
	BSTInsert(&GlobalTree, K, boolfunc, boolstat, type);

	K = "fakju";
	boolfunc = false;
	boolstat = false;
	type = var_integer;
	BSTInsert(&LocalTree, K, boolfunc, boolstat, type);

	//InitList (Func);
	//InsertLast (Func, "ano" , var_string);
	printf("=================================================\n");

	printf("[TEST3]\n");
	printf("Zistime ci je premenna 'Huh' staticka (mala by byt) \n");

	K = "Huh";
	pravda = BSTSearchStatic(GlobalTree, K);

	if(pravda == 1)
		printf("'%s' je staticka\n", K);
	else if(pravda == 2)
		printf("'%s' nie je staticka\n", K);
	else if(pravda == 0)
		printf("'%s' premenna sa nenasla\n", K);
	else printf("!!!chyba!!!\n");

	printf("=================================================\n");
	printf("[TEST4]\n");
	printf("Zistime ci je premenna 'Fakju' staticka (nemala by byt) \n");

	K = "Fakju";
	pravda = BSTSearchStatic(LocalTree, K);

	if(pravda == 1)
		printf("'%s' je staticka\n", K);
	else if(pravda == 2)
		printf("'%s' nie je staticka\n", K);
	else if(pravda == 0)
		printf("'%s' premenna sa nenasla\n", K);
	else printf("!!!chyba!!!\n");


	printf("=================================================\n");

	printf("[TEST05]\n");
	printf("Vlozime dalsie prvky:\n"
	       "(GlobalTree Key: M,    funkcia: false, staticka: true,  typ: string)\n"
	       "(LocalTree  Key: nana, funkcia: false, staticka: false, typ: integer).\n");

	K = "m";
	boolfunc = false;
	boolstat = true;
	type = var_string;
	BSTInsert(&GlobalTree, K, boolfunc, boolstat, type);

	K = "nana";
	boolfunc = false;
	boolstat = false;
	type = var_integer;
	BSTInsert(&LocalTree, K, boolfunc, boolstat, type);

	printf("=================================================\n");
	printf("[TEST6]\n");
	printf("Zistime ci je premenna 'nana' staticka (nemala by byt). \n");

	K = "nana";
	pravda = BSTSearchStatic(LocalTree, K);

	if(pravda == 1)
		printf("'%s' je staticka\n", K);
	else if(pravda == 2)
		printf("'%s' nie je staticka\n", K);
	else if(pravda == 0)
		printf("'%s' premenna sa nenasla\n", K);
	else printf("!!!chyba!!!\n");

	printf("=================================================\n");
	printf("[TEST7]\n");
	printf("Zistime ci je premenna 'nana' funkcia (nemala by byt). \n");

	K = "nana";
	pravda = BSTSearchFunc(LocalTree, K);

	if(pravda == 1)
		printf("'%s' je funkcia!\n", K);
	else if(pravda == 2)
		printf("'%s' nie je to funkcia!\n", K);
	else if(pravda == 0)
		printf("'%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	printf("=================================================\n");
	printf("[TEST08]\n");
	printf("Vlozime dalsie prvky:"
	       "\t(Key: qwerty, 	funkcia: false, staticka: true,  typ: integer)\n"
	       "\t(Key: click, 	funkcia: true, staticka: false, typ: double)\n"
	       "\t(Key: click$a, 	funkcia: false, staticka: false, typ: double)\n"
	       "\t(Key: click$b, 	funkcia: false, staticka: false, typ: double)\n"
	       "\t(Key: click$c, 	funkcia: false, staticka: false, typ: double)\n"
	       "\t(Key: clack,  	funkcia: false, staticka: false, typ: integer)\n"
	       "\t(Key: result, 	funkcia: false, staticka: false, typ: double)\n"
	       "\t(Key: variab, 	funkcia: false, staticka: false, typ: double)\n"
	       "\t(Key: coco,   	funkcia: false, staticka: true,  typ: string)\n"
	       "\t(Key: new,    	funkcia: false, staticka: false, typ: double)\n"
	       "\t(Key: por,    	funkcia: false, staticka: false, typ: integer)\n"
	       "\t(Key: gandalf,	funkcia: true,  staticka: true,  typ: string)\n"
	       "\t(Key: pocahontas,funkcia: true,  staticka: false, typ: integer)\n");

	BSTInsert(&LocalTree, "qwerty", false, true, var_integer);
	BSTInsert(&LocalTree, "click", true, false, var_double);
	BSTInsert(&LocalTree, "click$a", false, false, var_double);
	BSTInsert(&LocalTree, "click$b", false, false, var_double);
	BSTInsert(&LocalTree, "click$c", false, false, var_double);
	BSTInsert(&LocalTree, "clack", true, false, var_integer);
	BSTInsert(&LocalTree, "result", false, false, var_double);
	BSTInsert(&LocalTree, "variab", false, false, var_double);
	BSTInsert(&LocalTree, "coco", false, true, var_string);
	BSTInsert(&LocalTree, "new", true, false, var_double);
	BSTInsert(&LocalTree, "por", false, false, var_integer);
	BSTInsert(&LocalTree, "gandalf", true, true, var_string);
	BSTInsert(&LocalTree, "pocahontas", true, false, var_integer);


	printf("=================================================\n");
	printf("[TEST9]\n");
	printf("Zistime ci vsetky premenne su v strome \n");

	K = "qwerty";
	pravda = BSTSearchNode  (LocalTree, K);

	if(pravda == 1)
		printf(" '%s' premenna sa v strome nasla!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	K = "click$a";
	pravda = BSTSearchNode  (LocalTree, K);

	if(pravda == 1)
		printf(" '%s' premenna sa v strome nasla!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	K = "clack";
	pravda = BSTSearchNode  (LocalTree, K);

	if(pravda == 1)
		printf(" '%s' premenna sa v strome nasla!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	K = "result";
	pravda = BSTSearchNode  (LocalTree, K);

	if(pravda == 1)
		printf(" '%s' premenna sa v strome nasla!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	K = "variab";
	pravda = BSTSearchNode  (LocalTree, K);

	if(pravda == 1)
		printf(" '%s' premenna sa v strome nasla!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	K = "coco";
	pravda = BSTSearchNode  (LocalTree, K);

	if(pravda == 1)
		printf(" '%s' premenna sa v strome nasla!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	K = "new";
	pravda = BSTSearchNode  (LocalTree, K);

	if(pravda == 1)
		printf(" '%s' premenna sa v strome nasla!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	K = "par";
	pravda = BSTSearchNode  (LocalTree, K);

	if(pravda == 1)
		printf(" '%s' premenna sa v strome nasla!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	K = "gandalf";
	pravda = BSTSearchNode  (LocalTree, K);

	if(pravda == 1)
		printf(" '%s' premenna sa v strome nasla!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	K = "pocahontas";
	pravda = BSTSearchNode  (LocalTree, K);

	if(pravda == 1)
		printf(" '%s' premenna sa v strome nasla!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	printf("=================================================\n");
	printf("[TEST10]\n");
	printf("Zistime ci je premenna 'coco' funkcia (nemala by byt). \n");

	K = "clack";
	pravda = BSTSearchFunc(LocalTree, K);

	if(pravda == 1)
		printf(" '%s' je funkcia!\n", K);
	else if(pravda == 2)
		printf(" '%s' nie je to funkcia!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");


	printf("=================================================\n");
	printf("[TEST11]\n");
	printf("Zistime ci sa v strome nachadza 'result'.\n");

	K = "result";
	pravda = BSTSearchNode(LocalTree, K);

	if(pravda == 1) {
		printf(" '%s' premenna sa v strome nasla !\n", K);
	} else if(pravda == 0)
		printf(" '%s' premenna sa v strome nenasla!\n", K);
	else
		printf("!!!chyba!!!\n");

	/**********************************************************/
	printf("=================================================\n");
	printf("[TEST12]\n");
	printf("Odkontrolujeme deklarovanu funkciu 'pocahontas'\n");
	printf("deklarovana ako::  funkcia: true, staticka: false, typ: integer\n");
	printf("kontrolujeme ako:: funkcia: true, staticka: false, typ: integer\n");
	K = "pocahontas";
	pravda =  BSTCheckFunc (LocalTree, K, var_integer);

	if(pravda == 1)
		printf(" '%s' funkcia ma zhodne parametre so zadanymi !\n", K);
	else if(pravda == 2)
		printf(" '%s' funkcia nema zhodne parametre: ERR !\n", K);
	else if(pravda == 0)
		printf(" '%s' funkcia sa v strome nenasla: ERR !\n", K);
	else printf("!!!chyba!!!\n");

	printf("=================================================\n");
	printf("[TEST13]\n");
	printf("Odkontrolujeme deklarovanu funkciu 'new'\n");
	printf("deklarovana ako::  funkcia: true, staticka: false, typ: double\n");
	printf("kontrolujeme ako:: funkcia: true, staticka: false, typ: integer\n");
	K = "new";
	pravda =  BSTCheckFunc (LocalTree, K, var_integer);

	if(pravda == 1)
		printf(" '%s' funkcia ma zhodne parametre so zadanymi !\n", K);
	else if(pravda == 2)
		printf(" '%s' funkcia nema zhodne parametre: ERR !\n", K);
	else if(pravda == 0)
		printf(" '%s' funkcia sa v strome nenasla: ERR !\n", K);
	else printf("!!!chyba!!!\n");

	printf("=================================================\n");
	printf("[TEST15]\n");
	printf("Zistime typ premennej 'coconutnut'.(neexistuje)\n");

	K = "coconutnut";
	pravda = BSTSearchType(LocalTree, K, &type);

	if(pravda == 1) {
		printf("Premenna sa v strome nasla !\n");

		if(type == 0)	printf("Typ '%s' je 'var_double'\n", K);
		else if(type == 1)	printf("Typ '%s' je 'var_integer'\n", K);
		else if(type == 2)	printf("Typ '%s' je 'var_string'\n", K);
		else if(type == 3)	printf("Typ '%s' je 'var_void'\n", K);
	} else if(pravda == 0)
		printf("Premenna '%s' sa v strome nenasla!\n", K);
	else
		printf("!!!chyba!!!\n");

	/**********************************************************/
	printf("___________________________\n");
	/**********************************************************/
	printf("Zistime typ premennej 'qwerty'.(existuje)\n");
	K = "qwerty";
	pravda = BSTSearchType(LocalTree, K, &type);

	if(pravda == 1) {
		printf("Premenna sa v strome nasla !\n");

		if(type == 0)	printf("Typ '%s' je 'var_double'\n", K);
		else if(type == 1)	printf("Typ '%s' je 'var_integer'\n", K);
		else if(type == 2)	printf("Typ '%s' je 'var_string'\n", K);
		else if(type == 3)	printf("Typ '%s' je 'var_void'\n", K);
	} else if(pravda == 0)
		printf("Premenna '%s' sa v strome nenasla!\n", K);
	else
		printf("!!!chyba!!!\n");

	/**********************************************************/
	printf("___________________________\n");
	/**********************************************************/
	printf("Zistime typ premennej 'click'.(existuje)\n");
	K = "click";
	pravda = BSTSearchType(LocalTree, K, &type);

	if(pravda == 1) {
		printf("Premenna sa v strome nasla !\n");

		if(type == 0)	printf("Typ '%s' je 'var_double'\n", K);
		else if(type == 1)	printf("Typ '%s' je 'var_integer'\n", K);
		else if(type == 2)	printf("Typ '%s' je 'var_string'\n", K);
		else if(type == 3)	printf("Typ '%s' je 'var_void'\n", K);
	} else if(pravda == 0)
		printf("Premenna '%s' sa v strome nenasla!\n", K);
	else
		printf("!!!chyba!!!\n");

	/**********************************************************/
	printf("___________________________\n");
	/**********************************************************/
	printf("Zistime typ premennej 'coco'.(existuje)\n");
	K = "coco";
	pravda = BSTSearchType(LocalTree, K, &type);

	if(pravda == 1) {
		printf("Premenna sa v strome nasla !\n");

		if(type == 0)	printf("Typ '%s' je 'var_double'\n", K);
		else if(type == 1)	printf("Typ '%s' je 'var_integer'\n", K);
		else if(type == 2)	printf("Typ '%s' je 'var_string'\n", K);
		else if(type == 3)	printf("Typ '%s' je 'var_void'\n", K);
	} else if(pravda == 0)
		printf("Premenna '%s' sa v strome nenasla!\n", K);
	else
		printf("!!!chyba!!!\n");

	printf("=================================================\n");
	printf("[TEST14]\n");
	printf("Vlozenie dalsich prvkov (Func1 a Func2 ktore su funkcie) a \n");
	printf("a inicializacia jendosmerneho seznamu pre parametre funkcii\n");

	BSTInsert(&LocalTree, "Func1", true, false, var_double);
	BSTInsert(&LocalTree, "Func2", true, false, var_string);
	printf("zacinam inicializovat 2x\n");
	InitListFunc (&Func1);
	InitListFunc (&Func2);
	printf("zacinam insertovat 3x\n");
	InsertParam (&Func1, "res", var_double);
	InsertParam (&Func1, "res1", var_double);
	InsertParam (&Func1, "res2", var_double);
	printf("zacinam insertovat 3x\n");
	InsertParam (&Func2, "rest", var_string);
	InsertParam (&Func2, "rest1", var_string);
	InsertParam (&Func2, "rest2", var_string);

	/*
		char * Key;						Func1	Func2
		bool is_fnce;					true	true
		struct tBSTNode * subtree;		NULL	NULL
		bool is_stat;					false	false
		TType_var type 					double  string
	*/
	printf("=================================================\n");
	printf("[TEST16]\n");
	printf("Zistime vsetko o funkcii 'Func1' s 0 offset, je funkcia, nie je staticka, vracia double.(existuje)\n");

	/**********************************************************/
	K = "Func1";
	pravda = BSTSearchNode(LocalTree, K);

	if(pravda == 1) {
		printf("'%s' premenna sa v strome nasla !\n", K);
	} else if(pravda == 0)
		printf("'%s' premenna sa v strome nenasla!\n", K);
	else
		printf("!!!chyba!!!\n");

	/**********************************************************/
	pravda = BSTSearchFunc(LocalTree, K);

	if(pravda == 1)
		printf("'%s' je funkcia!\n", K);
	else if(pravda == 2)
		printf("'%s' nie je to funkcia!\n", K);
	else if(pravda == 0)
		printf("'%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	/**********************************************************/
	pravda = BSTSearchStatic(LocalTree, K);

	if(pravda == 1)
		printf("'%s' je staticka!\n", K);
	else if(pravda == 2)
		printf("'%s' nie je staticka!\n", K);
	else if(pravda == 0)
		printf("'%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	/**********************************************************/
	pravda = BSTSearchType(LocalTree, K, &type);

	if(pravda == 1) {
		//printf("4. Premenna sa v strome nasla !\n");
		if(type == 0)	printf("4. Typ '%s' je 'var_double'\n", K);
		else if(type == 1)	printf("4. Typ '%s' je 'var_integer'\n", K);
		else if(type == 2)	printf("4. Typ '%s' je 'var_string'\n", K);
		else if(type == 3)	printf("4. Typ '%s' je 'var_void'\n", K);
	} else if(pravda == 0)
		printf("Premenna %s sa v strome nenasla!\n", K);
	else
		printf("!!!chyba!!!\n");

	printf("=================================================\n");
	printf("[GREATEST TEST17]\n");
	printf("Vypiseme k___a vsetko!\n");

	printf(" func_joey(param1 as string, param2 as integer) as string!\n");
	func_set_id(&GlobalTree, "func_joey");
	function_set_param_name("param1");
	function_set_param_type("string");
	function_set_param_name("param2");
	function_set_param_type("integer");
	func_set_type_and_write(&GlobalTree, &LocalTree, "string");

	printf(" func_raptor(var1 as double, var2 as string) as bool!\n");
	func_set_id(&GlobalTree, "func_raptor");
	function_set_param_name("var1");
	function_set_param_type("double");
	function_set_param_name("var2");
	function_set_param_type("string");

	func_set_type_and_write(&GlobalTree, &LocalTree, "bool");
	/***************************************************************/

	K = "func_joey";
	pravda = BSTSearchNode  (GlobalTree, K);

	if(pravda == 1)
		printf(" '%s' premenna sa v strome nasla!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	K = "func_raptor";
	pravda = BSTSearchNode  (GlobalTree, K);

	if(pravda == 1)
		printf(" '%s' premenna sa v strome nasla!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");



	printf("Zistime ci je premenna 'func_raptor' funkcia (mala by byt). \n");
	K = "func_raptor";
	pravda = BSTSearchFunc(GlobalTree, K);

	if(pravda == 1)
		printf(" '%s' je funkcia!\n", K);
	else if(pravda == 2)
		printf(" '%s' nie je funkcia!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	pravda = BSTSearchType(GlobalTree, K, &type);

	if(pravda == 1) {
		printf("Premenna sa v strome nasla !\n");

		if(type == 0)	printf("Typ '%s' je 'var_double'\n", K);
		else if(type == 1)	printf("Typ '%s' je 'var_integer'\n", K);
		else if(type == 2)	printf("Typ '%s' je 'var_string'\n", K);
		else if(type == 3)	printf("Typ '%s' je 'var_bool'\n", K);
	} else if(pravda == 0)
		printf("Premenna '%s' sa v strome nenasla!\n", K);
	else
		printf("!!!chyba!!!\n");


	/***************************************************************/
	K = "func_joey$param1";
	pravda = BSTSearchNode  (LocalTree, K);

	if(pravda == 1)
		printf(" '%s' premenna sa v strome nasla!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	pravda = BSTSearchType (LocalTree, K, &type);

	if(pravda == 1) {
		printf("Premenna sa v strome nasla !\n");

		if(type == 0)	printf("Typ '%s' je 'var_double'\n", K);
		else if(type == 1)	printf("Typ '%s' je 'var_integer'\n", K);
		else if(type == 2)	printf("Typ '%s' je 'var_string'\n", K);
		else if(type == 3)	printf("Typ '%s' je 'var_bool'\n", K);
	} else if(pravda == 0)
		printf("Premenna '%s' sa v strome nenasla!\n", K);
	else
		printf("!!!chyba!!!\n");

	/***************************************************************/
	K = "func_raptor$var2";
	pravda = BSTSearchNode  (LocalTree, K);

	if(pravda == 1)
		printf(" '%s' premenna sa v strome nasla!\n", K);
	else if(pravda == 0)
		printf(" '%s' premenna sa nenasla!\n", K);
	else printf("!!!chyba!!!\n");

	pravda = BSTSearchType(LocalTree, K, &type);

	if(pravda == 1) {
		printf("Premenna sa v strome nasla !\n");

		if(type == 0)	printf("Typ '%s' je 'var_double'\n", K);
		else if(type == 1)	printf("Typ '%s' je 'var_integer'\n", K);
		else if(type == 2)	printf("Typ '%s' je 'var_string'\n", K);
		else if(type == 3)	printf("Typ '%s' je 'var_bool'\n", K);
	} else if(pravda == 0)
		printf("Premenna '%s' sa v strome nenasla!\n", K);
	else
		printf("!!!chyba!!!\n");

	/***************************************************************/



	printf("=================================================\n");
	printf("[TEST17]\n");
	printf("Nakonec zrusime cely strom.\n");
	DisposeAll(&GlobalTree, &LocalTree);

	//BSTDispose(&GlobalTree);
	if (GlobalTree == NULL)
		printf("strom 'GlobalTree' je prazdny.\n");

	//BSTDispose(&LocalTree);
	if (LocalTree == NULL)
		printf("strom 'LocalTree' je prazdny.\n");

	//DisposeListFunc (&Func1);
	//DisposeListFunc (&Func2);

	printf("=================================================\n");

	printf("------------------------------ konec -------------------------------------\n");
	return(0);
}

