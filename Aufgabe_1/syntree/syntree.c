#include "syntree.h"
#include <stdio.h>
#include <stdlib.h>


/**@brief Initialisiert einen neuen Syntaxbaum.
 * @param self  der zu initialisierende Syntaxbaum
 * @return 0, falls keine Fehler bei der Initialisierung aufgetreten sind,
 *      != 0 ansonsten
 */
int syntreeInit(Syntree *self){
    /*erstellt die Baumstruktur*/
    self->number = (struct num*) malloc(sizeof(struct num));
    if(self->number == NULL){
        fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
        exit(2);
    }

    self->container = (struct con*) malloc(sizeof(struct con));
    if(self->container == NULL){
        fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
        exit(2);
    }

    self->container_len = (int*) malloc(sizeof(int));
    if(self->container_len == NULL){
        fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
        exit(2);
    }
    self->container_len[0] = 0;
    self->container[self->container_len[0]].elem_count = 0;

    self->number_len = (int*) malloc(sizeof(int));
    if(self->number_len == NULL){
        fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
        exit(2);
    }
    self->number_len[0] = 0;

    self->identifier = (unsigned int*) malloc(sizeof(int));
    if(self->identifier == NULL){
        fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
        exit(2);
    }
    self->identifier[0] = 4999;

    return 0;
}

/**@brief Gibt den Syntaxbaum und alle assoziierten Strukturen frei.
 * @param self  der freizugebende Syntaxbaum
 */
void syntreeRelease(Syntree *self){
    for(int i=0; i<self->container_len[0]; i++){
        free(self->container[i].elem_ids);
    }
    free(self->container);
    free(self->container_len);
    free(self->number);
    free(self->number_len);
    free(self->identifier);
}

/**@brief Erstellt einen neuen Knoten mit einem Zahlenwert als Inhalt.
 * @param self    der Syntaxbaum
 * @param number  die Zahl
 * @return ID des neu erstellten Knoten
 */
SyntreeNodeID syntreeNodeNumber(Syntree *self, int number){
    self->number = (struct num*) realloc(self->number, sizeof(struct num)*(self->number_len[0]+1));
    if(self->number == NULL){
        fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
        exit(2);
    }
    self->number[self->number_len[0]].numb = number;
    self->number[self->number_len[0]].num_id = self->identifier[0]++;

    return self->number[self->number_len[0]++].num_id;
}

/**@brief Kapselt einen Knoten innerhalb eines anderen Knotens.
 * @param self  der Syntaxbaum
 * @param id    der zu kapselnde Knoten
 * @return ID des neu erstellten Knoten
 */
SyntreeNodeID syntreeNodeTag(Syntree *self, SyntreeNodeID id){
    self->container = (struct con*) realloc(self->container, sizeof(struct con)*(self->container_len[0]+1));
    if(self->container == NULL){
        fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
        exit(2);
    }
    self->container[self->container_len[0]].list_ID = self->identifier[0]++;
    self->container[self->container_len[0]].elem_count = 0;
    self->container[self->container_len[0]].elem_ids = (SyntreeNodeID *) malloc(sizeof(SyntreeNodeID));

    self->container[self->container_len[0]].elem_ids = (SyntreeNodeID *) realloc(self->container[self->container_len[0]].elem_ids, sizeof(SyntreeNodeID)*(self->container[self->container_len[0]].elem_count+1));
    if(self->container[self->container_len[0]].elem_ids == NULL){
        fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
        exit(2);
    }
    self->container[self->container_len[0]].elem_ids[self->container[self->container_len[0]].elem_count] = id;
    self->container[self->container_len[0]].elem_count++;

    return self->container[self->container_len[0]++].list_ID;
}

/**@brief Kapselt zwei Knoten innerhalb eines Knoten.
 * @param self  der Syntaxbaum
 * @param id1   erster Knoten
 * @param id2   zweiter Knoten
 * @return ID des neu erstellten Knoten
 */
SyntreeNodeID syntreeNodePair(Syntree *self, SyntreeNodeID id1, SyntreeNodeID id2){
    self->container = (struct con*)realloc(self->container, sizeof(struct con)*(self->container_len[0]+1));
    if(self->container == NULL){
        fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
        exit(2);
    }

    self->container[self->container_len[0]].elem_count = 0;
    self->container[self->container_len[0]].elem_ids = (SyntreeNodeID *) malloc(sizeof(SyntreeNodeID));
    self->container[self->container_len[0]].list_ID = self->identifier[0]++;
    self->container[self->container_len[0]].elem_ids = (SyntreeNodeID *) realloc(self->container[self->container_len[0]].elem_ids, sizeof(SyntreeNodeID)*(self->container[self->container_len[0]].elem_count+1));
    if(self->container[self->container_len[0]].elem_ids == NULL){
        fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
        exit(2);
    }

    self->container[self->container_len[0]].elem_ids[self->container[self->container_len[0]].elem_count++] = id1;
    self->container[self->container_len[0]].elem_ids[self->container[self->container_len[0]].elem_count++] = id2;

    return self->container[self->container_len[0]++].list_ID;
}

/**@brief Hängt einen Knoten an das Ende eines Listenknotens.
 * @param self  der Syntaxbaum
 * @param list  Listenknoten
 * @param elem  anzuhängender Knoten
 * @return ID des Listenknoten
 */
SyntreeNodeID syntreeNodeAppend(Syntree *self, SyntreeNodeID list, SyntreeNodeID elem){
    for(int i = 0; i<self->container_len[0]; i++){
        if(self->container[i].list_ID == list){
            self->container[i].elem_ids = (SyntreeNodeID *) realloc(self->container[i].elem_ids, sizeof(SyntreeNodeID)*(self->container[i].elem_count+1));
            if(self->container[i].elem_ids == NULL){
                fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
                exit(2);
            }
            self->container[i].elem_ids[self->container[i].elem_count++] = elem;
        }
    }

    return list;
}

/**@brief Hängt einen Knoten an den Anfang eines Listenknotens.
 * @param self  der Syntaxbaum
 * @param elem  anzuhängender Knoten
 * @param list  Listenknoten
 * @return ID des Listenknoten
 */
SyntreeNodeID syntreeNodePrepend(Syntree* self, SyntreeNodeID elem, SyntreeNodeID list){
    for(int i = 0; i<self->container_len[0];i++){
        if(self->container[i].list_ID == list){
            self->container[i].elem_ids = (SyntreeNodeID *)realloc(self->container[i].elem_ids,sizeof(SyntreeNodeID)*(self->container[i].elem_count+1));
            if(self->container[i].elem_ids == NULL){
                fprintf(stderr, "Es konnte kein Speicher allokiert werden!");
                exit(2);
            }

            for(int j = self->container[i].elem_count; j>0; j--){
                self->container[i].elem_ids[j] = self->container[i].elem_ids[j-1];
            }

            self->container[i].elem_ids[0] = elem;
            self->container[i].elem_count++;
        }
    }

    return list;
}

/**@brief Gibt alle Zahlenknoten rekursiv (depth-first) aus.
 * @param self  der Syntaxbaum
 * @param root  der Wurzelknoten
 */
void syntreePrint(const Syntree *self, SyntreeNodeID root){
    for(int i = 0; i < self->container_len[0]; i++){
        if(self->container[i].list_ID == root){
            printf("{");

            for(int k = 0; k <self->container[i].elem_count; k++){
                syntreePrint(self,self->container[i].elem_ids[k]);
            }
            printf("}");
        }
    }

    for(int j = 0; j < self->number_len[0]; j++){
        if(self->number[j].num_id == root){
            printf("(%i)", self->number[j].numb);
        }
    }
}
