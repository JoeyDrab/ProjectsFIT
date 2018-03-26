/* ******************************* c204.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c204 - Převod infixového výrazu na postfixový (s využitím c202)     */
/*  Referenční implementace: Petr Přikryl, listopad 1994                      */
/*  Přepis do jazyka C: Lukáš Maršík, prosinec 2012                           */
/*  Upravil: Bohuslav Křena, říjen 2013                                       */
/* ************************************************************************** */
/*
** Implementujte proceduru pro převod infixového zápisu matematického
** výrazu do postfixového tvaru. Pro převod využijte zásobník (tStack),
** který byl implementován v rámci příkladu c202. Bez správného vyřešení
** příkladu c202 se o řešení tohoto příkladu nepokoušejte.
**
** Implementujte následující funkci:
**
**    infix2postfix .... konverzní funkce pro převod infixového výrazu 
**                       na postfixový
**
** Pro lepší přehlednost kódu implementujte následující funkce:
**    
**    untilLeftPar .... vyprázdnění zásobníku až po levou závorku
**    doOperation .... zpracování operátoru konvertovaného výrazu
**
** Své řešení účelně komentujte.
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c204.h"

int solved;


/*
** Pomocná funkce untilLeftPar.
** Slouží k vyprázdnění zásobníku až po levou závorku, přičemž levá závorka
** bude také odstraněna. Pokud je zásobník prázdný, provádění funkce se ukončí.
**
** Operátory odstraňované ze zásobníku postupně vkládejte do výstupního pole
** znaků postExpr. Délka převedeného výrazu a též ukazatel na první volné
** místo, na které se má zapisovat, představuje parametr postLen.
**
** Aby se minimalizoval počet přístupů ke struktuře zásobníku, můžete zde
** nadeklarovat a používat pomocnou proměnnou typu.
*/
void untilLeftPar ( tStack* s, char* postExpr, unsigned* postLen ) {

	char c;

	stackTop(s, &c);
	//ak je zasobnik neprazdny rob..
	if (stackEmpty(s) == 0)
	{
		//inac toc cyklus dokym nebude prazdny
		while (stackEmpty(s) == 0)
		{
			if (c =='(') 
			{	//ak je zatvorka znakom, nacitaj ju do zasobnika
				stackPop(s);
				return;
			}
			else 
			{				
				postExpr[*postLen] = c;	//zapisem do pola
				*postLen+=1;
				stackPop(s);	//mazem znak
				stackTop(s, &c); //vraciam znak
			}
		} 

	}	
}

/*
** Pomocná funkce doOperation.
** Zpracuje operátor, který je předán parametrem c po načtení znaku ze
** vstupního pole znaků.
**
** Dle priority předaného operátoru a případně priority operátoru na
** vrcholu zásobníku rozhodneme o dalším postupu. Délka převedeného 
** výrazu a taktéž ukazatel na první volné místo, do kterého se má zapisovat, 
** představuje parametr postLen, výstupním polem znaků je opět postExpr.
*/
void doOperation ( tStack* s, char c, char* postExpr, unsigned* postLen ) {

	char temp;	//pomocna premenna
	// ak nie je stuck prazdny, vytiahnem znak
	if (stackEmpty(s) == 0)
		stackTop(s, &temp);
		//stackPush(s, c);
	if (stackEmpty(s) != 0) stackPush(s, c);
	else if (temp=='(') stackPush(s, c);		//ak je predchadzajuci znak zatvorka, pushnem c
	else if ((temp=='+') && (c!='+') && (c!='-')) stackPush(s, c);	//ak je predchadzajuci znak  operand..
	else if ((temp=='-') && (c!='+') && (c!='-')) stackPush(s, c);	// .. a znak c nie je, pushnem ho do zasobnika
	else 
	{
			postExpr[*postLen] = temp;	//inac zapisem do pola znak
			*postLen+=1;
			stackPop(s);				//odstranim najvyssi znak zo zasobnika
			doOperation(s, c, postExpr, postLen);	//rekurzivne volam funkciu dokym zasobnik nebude prazdny
	}	
}
/* 
** Konverzní funkce infix2postfix.
** Čte infixový výraz ze vstupního řetězce infExpr a generuje
** odpovídající postfixový výraz do výstupního řetězce (postup převodu
** hledejte v přednáškách nebo ve studijní opoře). Paměť pro výstupní řetězec
** (o velikosti MAX_LEN) je třeba alokovat. Volající funkce, tedy
** příjemce konvertovaného řetězce, zajistí korektní uvolnění zde alokované
** paměti.
**
** Tvar výrazu:
** 1. Výraz obsahuje operátory + - * / ve významu sčítání, odčítání,
**    násobení a dělení. Sčítání má stejnou prioritu jako odčítání,
**    násobení má stejnou prioritu jako dělení. Priorita násobení je
**    větší než priorita sčítání. Všechny operátory jsou binární
**    (neuvažujte unární mínus).
**
** 2. Hodnoty ve výrazu jsou reprezentovány jednoznakovými identifikátory
**    a číslicemi - 0..9, a..z, A..Z (velikost písmen se rozlišuje).
**
** 3. Ve výrazu může být použit předem neurčený počet dvojic kulatých
**    závorek. Uvažujte, že vstupní výraz je zapsán správně (neošetřujte
**    chybné zadání výrazu).
**
** 4. Každý korektně zapsaný výraz (infixový i postfixový) musí být uzavřen 
**    ukončovacím znakem '='.
**
** 5. Při stejné prioritě operátorů se výraz vyhodnocuje zleva doprava.
**
** Poznámky k implementaci
** -----------------------
** Jako zásobník použijte zásobník znaků tStack implementovaný v příkladu c202. 
** Pro práci se zásobníkem pak používejte výhradně operace z jeho rozhraní.
**
** Při implementaci využijte pomocné funkce untilLeftPar a doOperation.
**
** Řetězcem (infixového a postfixového výrazu) je zde myšleno pole znaků typu
** char, jenž je korektně ukončeno nulovým znakem dle zvyklostí jazyka C.
**
** Na vstupu očekávejte pouze korektně zapsané a ukončené výrazy. Jejich délka
** nepřesáhne MAX_LEN-1 (MAX_LEN i s nulovým znakem) a tedy i výsledný výraz
** by se měl vejít do alokovaného pole. Po alokaci dynamické paměti si vždycky
** ověřte, že se alokace skutečně zdrařila. V případě chyby alokace vraťte namísto
** řetězce konstantu NULL.
*/
char* infix2postfix (const char* infExpr) {

	unsigned postLen=0;
	char *pExpr;	//vystupny retazer (pole)
	tStack *s;
	int strlength;
	int i=0;
	//////////////////////////////////
	pExpr= (char*) malloc(MAX_LEN);	//allokujem vstupny retazec
	s= malloc(sizeof(char*) * STACK_SIZE);	//allokujem zasobnik

	strlength =  snprintf(NULL, 0, "%s", infExpr);	//dlzka retazca (pocet znakov)
													//nemozno pouzit strlen (chyba <string.h>)
	if (pExpr == NULL) 		//ak sa alokacia nepodarila, 
		return NULL;							
	if 	(s == NULL)			//vrat NULL a uvolni alokovany retazec
	{
		free(pExpr);
		return NULL;
	}	

	//inicializacia zasobniku
	stackInit(s);

	while (i<=strlength)
	{	// do pola znakov (retazca) zapisem alfanumericky znak
		if (infExpr[i] >= '0' && infExpr[i] <= '9')
		{
			pExpr[postLen] = infExpr[i];
			postLen++;
		}
		else if (infExpr[i] >= 'a' && infExpr[i] <= 'z') 
		{
			pExpr[postLen] = infExpr[i];
			postLen++;
		}	
		else if (infExpr[i] >= 'A' && infExpr[i] <= 'Z')
		{
			pExpr[postLen] = infExpr[i];
			postLen++;
		}	
		//ak je znakom lava zatvorka 
		else if (infExpr[i] == '(')
			stackPush(s, infExpr[i]);

		else if (infExpr[i] == ')')
			// ake je znakom pravá závorka, pouzijem funkciu 
			//na odoberanie poloziek z vrcholu zasobnika do vystupneho retazca
			untilLeftPar(s, pExpr, &postLen);

		else if (infExpr[i] == '=') 
		{
			// ak je znakom '=', zacnem odstranovat polozky 
			//zasobnika a pridavat ich do vystupneho retazca 
			while (stackEmpty(s) == 0) 
			{
				stackTop(s, &pExpr[postLen]);
				stackPop(s);
				postLen++;
			}
				pExpr[postLen] = '=';
				postLen++;
				pExpr[postLen] = '\0';
		}
		else 
			doOperation(s, infExpr[i], pExpr, &postLen);	
	i++;
	}
	free(s);

	return pExpr;
  //solved = 0;                        /* V případě řešení smažte tento řádek! */
  //return NULL;                /* V případě řešení můžete smazat tento řádek. */
}

/* Konec c204.c */
