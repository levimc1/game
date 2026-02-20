# game
Játék a versenynre!

## Kód
A kódban az engine alatt lévő dolgok nem egy igazi játékmotor részei!
csak moduláritás és az "engine" név illik rá.
A engine mappa alatt lévő almappák azok egy-egy "modul"
### Egy modul
Egy modul az a "filozófiám" része hogy adat és viselkedés kell csak akármihez. 
Ebben ahogy a neve is állítsa adat van amit különböző függvények módosítanak és semmi extra. 
Egy "viselkedés" lehet stage alapú, vagy API alapú. Ezek a nevek csupán számomra vannak. 
Egy Stage viselkedés valahol be van illesztve a main függvénybe. 
Még egy API-t másik modulok hívnak hogy ne direkt módosítsák a contextusát.
Egy modul contextusa az maga az adat amiről szó esett.
Ezek a file struktúrában a modul mappa alatt:
context.h -> contextus változók 
renderer.h -> Attribútumok.
stages/ -> felhasználható stage-ek main()-ben
api/ -> felhasználható API függvények többi modulból state mutálásra
Egy attribútum célja hogy a modulok modulárisam újrahasználhatóak legyenek.
Ezek úgy működnek hogy megadunk pár létfontosságú adatot / "flag"-et a modulnak.
Például az FPS limitet
Mindezt az OpenGL-ről mintáztam, ami egy state machine.
### A globális
engine/-en kívül is van egy context, ez a tick és stbkre van, amik nem egy modul dolga.
### Engine/-en kívül
Az assets/ mappában textúrák shaderek, stb.
main.cpp csupán a stage-kért és globális contextusért felelős.
extern/ az akármilyen nem általam írt kód.
### Minden egy mappába?
Mivel nem fog iteraktálni semmivel, egy játék, nincsen szükség include és src ra.
Helyette ez a struktúra van.
### Kommentelés
