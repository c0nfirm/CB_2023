#ifndef SYNTREE_H_INCLUDED
#define SYNTREE_H_INCLUDED

/* *** Strukturen *********************************************************** */

typedef /* muss noch definiert werden */ SyntreeNodeID;

/**@brief Struktur des abstrakten Syntaxbaumes.
 */
typedef struct {
    /* hier sollte noch etwas dazu kommen */
} Syntree;

/* *** öffentliche Schnittstelle ******************************************** */

/**@brief Initialisiert einen neuen Syntaxbaum.
 * @param self  der zu initialisierende Syntaxbaum
 * @return 0, falls keine Fehler bei der Initialisierung aufgetreten sind,
 *      != 0 ansonsten
 */
extern int
syntreeInit(Syntree *self);

/**@brief Gibt den Syntaxbaum und alle assoziierten Strukturen frei.
 * @param self  der freizugebende Syntaxbaum
 */
extern void
syntreeRelease(Syntree *self);

/**@brief Erstellt einen neuen Knoten mit einem Zahlenwert als Inhalt.
 * @param self    der Syntaxbaum
 * @param number  die Zahl
 * @return ID des neu erstellten Knoten
 */
extern SyntreeNodeID
syntreeNodeNumber(Syntree *self, int number);

/**@brief Kapselt einen Knoten innerhalb eines anderen Knotens.
 * @param self  der Syntaxbaum
 * @param id    der zu kapselnde Knoten
 * @return ID des neu erstellten Knoten
 */
extern SyntreeNodeID
syntreeNodeTag(Syntree *self, SyntreeNodeID id);

/**@brief Kapselt zwei Knoten innerhalb eines Knoten.
 * @param self  der Syntaxbaum
 * @param id1   erster Knoten
 * @param id2   zweiter Knoten
 * @return ID des neu erstellten Knoten
 */
extern SyntreeNodeID
syntreeNodePair(Syntree *self, SyntreeNodeID id1, SyntreeNodeID id2);

/**@brief Hängt einen Knoten an das Ende eines Listenknotens.
 * @param self  der Syntaxbaum
 * @param list  Listenknoten
 * @param elem  anzuhängender Knoten
 * @return ID des Listenknoten
 */
extern SyntreeNodeID
syntreeNodeAppend(Syntree *self, SyntreeNodeID list, SyntreeNodeID elem);

/**@brief Hängt einen Knoten an den Anfang eines Listenknotens.
 * @param self  der Syntaxbaum
 * @param elem  anzuhängender Knoten
 * @param list  Listenknoten
 * @return ID des Listenknoten
 */
extern SyntreeNodeID
syntreeNodePrepend(Syntree *self, SyntreeNodeID elem, SyntreeNodeID list);

/**@brief Gibt alle Zahlenknoten rekursiv (depth-first) aus.
 * @param self  der Syntaxbaum
 * @param root  der Wurzelknoten
 */
extern void
syntreePrint(const Syntree *self, SyntreeNodeID root);

#endif /* SYNTREE_H_INCLUDED */
