	
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, říjen 2017
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu, 
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek, 
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku, 
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu, 
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem, 
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu, 
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam 
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
    
	L->First=NULL;
	L->Act=NULL;
	L->Last=NULL;
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLDisposeList (tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free. 
**/
	L->First=NULL;
	L->Act=NULL;
	
	tDLElemPtr mainLem = L->Last;			// ulozenie ukazatela posledneho prvku do prvku viazaneho zoznamu (mainLem)

	while (mainLem != NULL)				
	{
		tDLElemPtr mainLemNext = mainLem->lptr;	//ulozenie ukazatela na předchozí prvek seznamu do mainLemNext
		free(mainLem);						//uvolnenie prvku
		mainLem = mainLemNext;					//ulozenie předchozího prveku do mainLem
	}

	L->Last = NULL;
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	//Alokujem novy prvok
	tDLElemPtr newItem = malloc(sizeof(struct tDLElem));

	//ak sa alokacia nepodari
	if (newItem == NULL)
	{
		DLError();
		return;
	}

	newItem->data = val;
	newItem->lptr = NULL;
	newItem->rptr = L->First;
	
	if (L->First == NULL)
		L->Last = newItem;
	else
		L->First->lptr = newItem;

	L->First = newItem;
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/ 	
	//Alokujem novy prvok
	tDLElemPtr newItem = malloc(sizeof(struct tDLElem));

	////ak sa alokacia nepodari
	if (newItem == NULL)
	{
		DLError();
		return;
	}
	newItem->data = val;
	newItem->lptr = L->Last;
	newItem->rptr = NULL;

	if (L->Last == NULL)
		L->First = newItem;
	else
		L->Last->rptr = newItem;

	L->Last = newItem;
	
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	L->Act = L->First;

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	L->Act = L->Last;
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

	if (L->First == NULL)
	{
		DLError();
		return;
	}

	*val = L->First->data;
	
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
	if (L->First == NULL)
	{
		DLError();
		return;
	}

	*val = L->Last->data;
	
	
 solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLDeleteFirst (tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita 
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
	//ak je oznam je prazdny
	if (L->First == NULL)
		return;

	//ak je aktivny prvok prvym prvkom
	if (L->Act == L->First)
		L->Act = NULL;

	// do nextToFirst si ulozim nasledovnika prveho prvku
	tDLElemPtr nextToFirst = L->First->rptr;

	// prechadzajuci prvok sa zrusi
	if (nextToFirst != NULL)
		nextToFirst->lptr = NULL;

	free(L->First);

	// prvy prvok je nextToFirst
	L->First = nextToFirst;

	if (L->First == NULL)
		L->Last = NULL;
	
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}	

void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/ 

	//ak je zoznam je prazdny
	if (L->First == NULL)
		return;

	//ak je aktivny prvok poslednym prvkom
	if (L->Act == L->Last)
		L->Act = NULL;

	// ulozim si predchadzajuci prvok od last
	tDLElemPtr PrevToLast = L->Last->lptr;

	//predchadzajuci prvok zrusim
	if (PrevToLast == NULL)
		L->First = NULL;
	else
		PrevToLast->rptr = NULL;
	
	// uvolnim posledny prvok zo zoznamu
	free(L->Last);

	//Posledny prvok zoznamu je PrevToLast
	L->Last = PrevToLast;
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/
	//ak je zoznam je neaktivny
	if (L->Act == NULL) 
		return;
	//posledny prvok je aktivny
	if(L->Act == L->Last)
		return;

	//do nextToAct si ulozim nasledujuci prvok 
	tDLElemPtr nextToAct = L->Act->rptr;

	if (nextToAct->rptr == NULL)
	{
		L->Act->rptr = nextToAct->rptr;
		L->Last = L->Act;
	}	
	else
	{
		//Nasledujuci prvok nextToAct ukazuje na aktivny
		nextToAct->rptr->lptr = L->Act;

		//Nasledujuci prvok aktivneho je prvok za nextToAct
		L->Act->rptr = nextToAct->rptr;
	}

	//Uvolnim nextToAct
	free(nextToAct);
		
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/	
	if (L->Act == NULL) 	//ak je zoznam je neaktivny
		return;
	
	if(L->Act == L->First)		//posledny prvok je aktivny
		return;
	
	tDLElemPtr PrevToAct = L->Act->lptr;	//do PrevToAct si ulozim nasledujuci prvok 

	if (PrevToAct->lptr == NULL)
	{
		//L->Act->lptr = PrevToAct->lptr;
		L->First = L->Act;
	}	
	else	
		PrevToAct->lptr->rptr = L->Act;	//predchadzajuci prvok PrevToAct ukazuje na aktivny

	free(PrevToAct);	//Uvolnim PrevToAct
			
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	if (L->Act == NULL) //ak je zoznam je neaktivny
		return;
	
	tDLElemPtr newItem = malloc(sizeof(struct tDLElem));	//Alokujem pamat pre novy prvok

	if (newItem == NULL)			//ak sa alokace nepodarila
	{
		DLError();
		return;
	}

	//Do nextAct si ulozim nasledujuci prvok aktivneho
	tDLElemPtr nextAct = L->Act->rptr;

	//Vlozim novy prvok do zoznamu
	L->Act->rptr = newItem;

	newItem->lptr = L->Act;		// hodnoty noveho item
	newItem->rptr = nextAct;
	newItem->data = val;

	if (nextAct == NULL)
		L->Last = newItem;
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	if (L->Act == NULL) //ak je zoznam je neaktivny
		return;
	
	tDLElemPtr newItem = malloc(sizeof(struct tDLElem));	//Alokujem pamat pre novy prvok

	if (newItem == NULL)			//ak sa alokace nepodarila
	{
		DLError();
		return;
	}

	//Do PrevAct si ulozim nasledujuci prvok aktivneho
	tDLElemPtr PrevAct = L->Act->lptr;

	//Vlozim novy prvok do zoznamu
	L->Act->lptr = newItem;

	newItem->rptr = L->Act;		// hodnoty noveho item
	newItem->lptr = PrevAct;
	newItem->data = val;

	if (PrevAct == NULL)
		L->Last = newItem;
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
	if (L->Act == NULL)
	{
		DLError();
		return;
	}
	*val = L->Act->data;
	
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLActualize (tDLList *L, int val) {
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/
	if (L->Act == NULL)
	{
		DLError();
		return;
	}
	L->Act->data = val;
	
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/
	if (L->Act == NULL)
		return;
	L->Act = L->Act->rptr;
	
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/
	if (L->Act == NULL)
		return;
	L->Act = L->Act->lptr;
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/
	return L->Act != NULL ?  1 : 0;
	
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

/* Konec c206.c*/
