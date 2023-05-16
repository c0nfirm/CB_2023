# Übungsblatt 2
## Generelles
Diese beiden Aufgaben dienen der Vertiefung Ihrer Erfahrungen mit dem Metawerkzeug flex. Sie implementieren die lexikalische Analyse für unseren Praktikumsinterpreter der Sprache C1. In der nächsten Aufgabe benötigen Sie diese Komponente, um Token für den Parser bereitzustellen.

## Allgemeine Hinweise
Für diese und alle folgenden Praktikumsaufgaben gilt, dass Einsendungen, die in der jeweils mitgegebenen Testumgebung nicht laufen, mit null Punkten bewertet werden! Das beinhaltet insbesondere alle Programme, die sich nicht fehlerfrei kompilieren lassen. Als Testsystem werden wir dabei gruenau6 mit den dort installierten Compilern und Compilerwerkzeugen benutzen. Prüfen Sie bitte rechtzeitig vor der Abgabe, ob ihr Programm auch dort lauffähig ist. Wir akzeptieren keine Entschuldigungen der Form „aber bei mir Zuhause hat es funktioniert“ ;).

Ebenfalls mit null Punkten werden alle Abgaben bewertet, die sich nicht exakt an die vorgegebenen Formate halten.

> Um Ihnen die Abgabe zu erleichtern, geben wir Ihnen ein Makefile mit, welches die folgenden Ziele unterstützt:
> #### all
> Übersetzt die Quelldateien und erzeugt eine ausführbare Datei.
> #### run
> Übersetzt die Quelldateien, erzeugt eine ausführbare Datei und startet das Testprogramm.
> #### clean
> Entfernt alle Zwischendateien und räumt in Ihrem Verzeichnis auf.
> Bitte achten Sie bei Ihrer Implementation auf Speicherleckfreiheit bei korrekter Benutzung, d.h. bei paarweisem Aufruf von init() und release().

## Abgabemodus
Die Quell- und Headerdateien sind in einem Git-Repository abzugeben.  

Zur Lösung der Aufgaben steht für Sie dieses Repository mit  
- ein Unterverzeichnis c1-scanner für Aufgabe 1 mit 
  - einem vorgegebenen Makefile, 
  - einem Testprogramm testscanner.c und einer Header-Datei minako.h 
  - sowie einer Testeingabe demorgan.c1 und der erwarteten Testausgabe demorgan.sol 
- die Dateien im Unterverzeichnis urlscanner für Aufgabe 2
- der [Foliensatz](uebung2.pdf) vom letzten Jahr mit einer kurzen Einführung in reguläre Ausdrücke und flex 

zur Verfügung.

Noch ein Hinweis zu den Compilerwarnungen: Nach wir vor gilt, dass wir für Warnungen bei der Übersetzung Punkte abziehen, es kann allerdings passieren, dass sich Warnungen im von flex generierten Quelltext nicht auf einfache Weise vermeiden lassen. Diese Warnungen tolerieren wir.

## Aufgabe 1 (50 Punkte)
### Kurzbeschreibung
Implementieren Sie mit Hilfe von flex einen Scanner, der in einem Eingabestrom bzw. in einer Eingabedatei die Token der Sprache C1 erkennt.

### Aufgabenstellung
Mittels flex sollen sie einen Scanner implementieren, der aus einem Eingabestrom die Token der Sprache C1 extrahiert.

Die Lexik der Sprache C1 befindet sich [hier](https://amor.cms.hu-berlin.de/~kunert/lehre/material/c1-lexic.php). Zusätzlich sind folgende Punkte zu beachten:

- wenn man den Scanner ohne Kommandozeilenparameter aufruft, soll er von stdin lesen, ansonsten aus der auf der Kommandozeile angegebenen Datei (dabei sollen eventuell auftauchende Dateizugriffsfehler abgefangen werden)
- die Implementation befindet sich in der Datei minako-lexic.l
- Whitespaces (Leerzeichen, Tabulatoren, Zeilenenden) sollen vom Scanner ignoriert werden
- C- (/* */) und C++- (//) Kommentare sollen überlesen werden
- es sind nur die in der Headerdatei minako.h definierten Token (z.B.: "==") als Konstanten (im Bsp.: EQ) zurückzugeben; bei allen nicht in minako.h erwähnten Zeichen (die aber laut Lexikbeschreibung zur Lexik von C1 gehören, z.B.: "+"), soll einfach der ASCII-Code des Zeichens zurückgegeben werden
- alle nicht in C1 erlaubten Zeichen (etwa "&") sollen zu einem lexikalischen Fehler führen (also zu einer sinnvollen Fehlerausgabe gefolgt vom Programmabbruch)
- wenn Sie den Scanner auf das mitgelieferte C1-Beispielprogramm demorgan.c1 ansetzen, sollte genau die in demorgan.sol stehende Ausgabe erfolgen


## Aufgabe 2 (50 Punkte)
### Kurzbeschreibung
Implementieren Sie mit Hilfe von flex einen Scanner, der in einem Eingabestrom bzw. aus einer Eingabedatei URLs und damit verbundene Linkbeschreibungen extrahiert.

### Aufgabenstellung
Der zweite zu implementierende Scanner soll mittels flex aus einem Eingabestrom im xhtml-Format die URLs und die Linktexte extrahieren und ausgeben.

Zur Vereinfachung der Analyse gelten folgende Konventionen:

- der Eingabestrom ist valides xhtml, das keinen CDATA Abschnitt enthält. Die Links haben das Format <a ... href="URL" ... >LINKTEXT</a>, wobei im schließenden Tag nach dem 'a' null oder mehr Leerzeichen und Newlines stehen dürfen. Innerhalb des öffnenden Tags dürfen vor und nach href weitere Attribute auftreten, die überlesen werden
- Newlines innerhalb von LINKTEXT gehören zum Linktext. D.h. alles innerhalb des a-Tags gehört zum Linktext
- zwischen <a ...> und <\/a> treten keine anderen Tags auf
- a-Tags, die kein href-Attribut beinhalten, werden komplett ignoriert
- die Eingabe enthält keinerlei Kommentare

Bitte vergleichen Sie Ihre Ausgabe bei Eingabe der Datei testeingabe.html mit der erwarteten Ausgabe in testeingabe.sol.