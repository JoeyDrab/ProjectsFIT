//__________________________________________//
//******************************************//
//part:		IFJ/ err.h						//
//team members: M. Kascak, J. Drab, 		//
//				Ch. Farkas, V. Cervenanska	//
//written by: J.Drab						//
//__________________________________________//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "err.h"
#include "lex.h"

queue_t * error_heap;

void allocation_error() {
    fprintf(stderr, "[E] Allocation error!\n");
    exit(RV_INTERN);
}

void file_open_error() {
    fprintf(stderr, "[E] Error while opening file!\n");
    exit(RV_INTERN);
}

void init_error_handling() {
    error_heap = (queue_t *) malloc(sizeof(queue_t));
    if(error_heap == NULL){
	allocation_error();
    }
    qInit(error_heap);
}

void finalize_error_handling() {
    if(qFront(error_heap) == NULL) {
	qFree(error_heap);
	exit(RV_SUCCESS);
    }

    int final_return = error_heap->q_begin->e->return_value;

    error_t * iter;
    while((iter = qFront(error_heap)) != NULL) {
	fprintf(stderr, "%s on line %lu\n", iter->message, iter->line);
	qRemove(error_heap);
    }
    qFree(error_heap);
    exit(final_return);
}

void add_err(char * message, error_type type, unsigned long line) {
    error_t *new_err = (error_t *) malloc(sizeof(error_t));
    if(new_err == NULL) {
	allocation_error();
    }

    size_t msg_len = strlen(message) + 1;
    new_err->message = (char *) malloc(sizeof(char) * msg_len);
    strncpy(new_err->message, message, msg_len);

    new_err->line = line;
    new_err->return_value = type;

    queUp(error_heap, new_err);
}

// Halda

void qInit(queue_t * q) {
    q->q_begin = NULL;
    q->q_end   = NULL;
}

bool qEmpty(queue_t * q) {
    return (q->q_begin == NULL);
}

void queUp(queue_t * q, error_t * e) {

    qelem_t *new_elem = (qelem_t *) malloc(sizeof(qelem_t));
    if(new_elem == NULL) {
	allocation_error();
    }

    new_elem->e    = e;
    new_elem->next = NULL;

    if(q->q_begin == NULL) {
	q->q_begin = new_elem;
    } else {
	q->q_end->next = new_elem;
    }

    q->q_end = new_elem;

}

error_t * qFront(queue_t * q) {
    return (q->q_begin == NULL) ? NULL : (q->q_begin->e);
}

void qRemove (queue_t * q) {
    if(q->q_begin != NULL) {
	qelem_t *elem = q->q_begin;
	if(q->q_begin == q->q_end) {
	    q->q_end = NULL;
	}
	q->q_begin = q->q_begin->next;
	free(elem);
    }
}

void qFree(queue_t *q) {
    (void) q;
    // TODO: Spravne uvolnenie haldy [a poloziek ktore v nej zostali]
}
