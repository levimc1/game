# Engine Design

## Célok

1. Írt kód ne változzon ha a design változik.
2. Erős Data / Behavior szeparáció.
3. Minden kód újrahasználható legyen.

## Namespace konvenciók

**Ezek konkrét szabályok, és a motor konvenciója**!
1. Minden namespace az engine namespace tagja.
2. Minden rendszer namespace-e a snake_case, _ nélkül (snakecase) változatja. (engine::spriterenderer2d, engine::somesystem)
- Ez a a rendszer fő namespace-e.
3. Minden rendszer fő namespace-e alatt:
- publikus függvények, azaz ezt használja a játékfeljesztő
- internal:: alatt olyan amit a többi rendszer használ
- private:: alatt csak az a rendszeré
Ezek csak ilyen jelzések, ha internal/private alatt vagy tudod hogy rosszul csinálod. Vizuális figyelmeztetés.
4. Fő namespace alatt egy fizikális objektum.

## Rendszerek értelme


