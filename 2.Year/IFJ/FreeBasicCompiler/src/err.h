//__________________________________________//
//******************************************//
//part:		IFJ/ err.h						//
//team members: M. Kascak, J. Drab, 		//
//				Ch. Farkas, V. Cervenanska	//
//written by: J.Drab						//
//__________________________________________//

#ifndef ERR_H
#define ERR_H

#include <stdbool.h>

/**
 * Navratove hodnoty podla zadania
 */
#define RV_SUCCESS    0
#define RV_LEX        1
#define RV_SYNTAX     2
#define RV_SEMA_UNDEF 3
#define RV_SEMA_ARIT  4
#define RV_SEMA_OTHER 6
#define RV_INTERN     99

/**
 * Struktura reprezentujuca chybu ktora nastala pocas prekladu
 */
typedef struct {
    char * message;
    unsigned long line;
    int return_value;
} error_t;

/**
 * Struktura reprezentujuca jednu polozku haldy
 */
typedef struct qelem_s{
    error_t *e;
    struct qelem_s *next;
} qelem_t;

/**
 * Struktura reprezentujuca haldu ako taku
 */ 
typedef struct {
    struct qelem_s *q_begin;
    struct qelem_s *q_end;
} queue_t;

/**
 * Enum obsahujuce typy chyb ktore mozu nastat pocas prekladu
 */
typedef enum {
    error_lex             = RV_LEX, // chybna struktura lexemu
    error_syntax          = RV_SYNTAX, // chybna syntax programu
    error_semantics_undef = RV_SEMA_UNDEF, // semanticka chyba, nedeklarovana premenna/funkcia
    error_semantics_arit  = RV_SEMA_ARIT, // semanticka chyba typovej kompatibility
    error_other_semantics = RV_SEMA_OTHER, // ostatne semanticke chyby
    error_intern          = RV_INTERN // chyba neovplyvnena vstupnym programom(malloc)
} error_type;

/**
 * Funckcia ktora riesi chyby pri alokacii
 *
 * Kedze pri chybnej alokacii nie je mozne dalej pokracovat,
 * funkcia ukonci program s navratovou hodnout 99(intern error)
 */
void allocation_error(); // TODO: inline?
void file_open_error(); // TODO: inline?

/**
 * Funckcia prida chybu na koniec rady
 *
 * @param[in] message Sprava ktora ma byt pre uzivatela vypisana
 * @param[in] type    Typ chyby ktora nastala.
 */
void add_err(char * message, error_type type, unsigned long line);
// TODO: refaktor parametrov, enum mozno nie je najlepsie riesenie

/**
 * Inicializuje strukturu obsahujucu chybu
 * 
 * @param[in, out] e struktura ktora ma byt inicializovana
 */
void init_err(error_t * e);

/**
 * Funkcia inicializuje vypis chyb v programe
 * 
 * Inicializuje haldu, do ktorej sa chyby nasledne budu pridavat
 */
void init_error_handling();

/**
 * Funkcie overi stav programu, v pripade ze nastali nejake chyby
 * vypise ich a program ukonci so spravnou navratovou hodnotou.
 */
void finalize_error_handling();

// Funckcie nad pomocnou haldou, ktora obsahuje zaznam o chybach
// Vzdy ked pride nova chyba zaradi sa do rady
// Nasledne pri ukonceni programu sa vsetky chyby vypisu a program
// sa ukonci s navratovou hodnotou prvej chyby
void qInit(queue_t *q);
bool qEmpty(queue_t *q);
void queUp(queue_t *q, error_t *e);
error_t * qFront(queue_t *q);
void qRemove (queue_t *q);
void qFree(queue_t *q);

#endif /* ERR_H */
