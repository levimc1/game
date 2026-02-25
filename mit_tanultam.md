## OpenGL

Az OpenGL egy state machine, objektumokkal, kb így képzeld el:
struct State {
    Object;
    Object;
}
Ezeket state mutáló és olvasó függvények módosítják:
glBufferData(...) -> mutáló
glDraw*(...) -> olvasó

Egy rajzolás folyamata:

1. lépés - Bufferek létrehozása, feltöltése 
-- Adat változók
-- glGenVertexArrays
-- glGenBuffers 
-- Bufferenként:
--- glBufferData() -> Ha static draw
--- glVertexAttribPointer + haverjai
-- VAO kész!
2. lépés - shaderek létreozása hozzá
-- Ezt a részt gyűlölöm, unalmas, de szerencsére elég egyszer megírni. 
-- majd glUseProgram()
3. lépés - Rajzolás! - LOOPBAN!
-- VAO-t aktiválod 
-- Shadert aktiválod 
-- glDraw*(...)
4. lépés - Adat módosítás - LOOPBAN!
-- !Csak ha kell. Ezek lehetnek:
--- uniformok
-- Vagy akár bufferek módosítása, ami nem ajánlott mert nem szereti a GPU :(
