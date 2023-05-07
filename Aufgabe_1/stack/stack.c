#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


/**@brief Initialisiert einen neuen Stack.
 * @param self  der zu initialisierende Stack
 * @return 0, falls keine Fehler bei der Initialisierung aufgetreten sind,
 *      != 0, ansonsten
 */
int stackInit(IntStack *self){
    self->items = (int*)malloc(sizeof(int));
    if(self->items == NULL){
        fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
        exit(2);
    }

    self->top = (int*)malloc(sizeof(int));
    if(self->top == NULL){
        fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
        exit(2);
    }
    self->top[0] = -1;

    return 0;
}

/**@brief Gibt den Stack und alle assoziierten Strukturen frei.
 * @param self  der Stack
 */
void stackRelease(IntStack *self){
    free(self->items);
    free(self->top);
}

/**@brief Legt einen Wert auf den intstack.
 * @param self  der intstack
 * @param i     der Wert
 */
void stackPush(IntStack *self, int i){
    self->items = (int *) realloc(self->items, sizeof(int)*(self->top[0]+2));
    if(self->items==NULL){
        fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
        exit(2);
    }
    self->items[++self->top[0]] = i;
}

/**@brief Gibt das oberste Element des Stacks zurück.
 * @param self  der Stack
 * @return das oberste Element
 */
int stackTop(const IntStack *self){
    if(stackIsEmpty(self) == 1){
        printf("Stack ist leer!\n");
        return -1;
    }

    return self->items[self->top[0]];
}

/**@brief Entfernt und liefert das oberste Element des Stacks.
 * @param self  der Stack
 * @return das oberste Element
 */
int stackPop(IntStack *self){
    if(stackIsEmpty(self) == 1){
        printf("Stack ist leer!\n");
        return -1;
    }

    return self->items[self->top[0]--];
}

/**@brief Gibt zurück, ob der Stack leer ist.
 * @param self  der Stack
 * @return 0, falls nicht leer,
        != 0, falls leer
 */
int stackIsEmpty(const IntStack *self){
    if(self->top[0] < 0) return 1;
    return 0;
}

/**@brief Gibt den Inhalt des Stacks beginnend mit dem obersten Element auf der
 * Standardausgabe aus.
 * @param self  der Stack
 */
void stackPrint(const IntStack *self){
    if(stackIsEmpty(self) == 1) printf("Empty Stack!");

    int top = self->top[0];
    while(top > -1){
        printf("%i \n", self->items[top]);
        top--;
    }
}
