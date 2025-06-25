***Konrad El-Hagin 203652***
***Mikołaj Poździk 203689***

Dzwig (Zad. 4)
===============

vector RECT **objekty** - zapisuje współrzędne poszczególnych objektów (nie tylko kwadratów)<br>
vector int **ksztalt** - zapisuje kształty poszczególnych objektów<br>

bool **moving...** - zmienna bulowska true - w trakcie poruszania<br>
bool **wieza_ktk/kkt** - true - w trakcie tworzenia wież<br>
bool **wieza_1,2,3** - zmienne bulowskie określające, czy poszczególne klocki są już ustawione<br>

Przyciski
---------

**kolko** - tworzy kółko HMENU 5<br>
**kwadrat** - tworzy kwadrat HMENU 6<br>
**trojkat** - tworzy trójkąt HMENU 7<br>
**left** - porusza stworzony objekt w lewo HMENU 1<br>
**right** - porusza stworzony objekt w prawo HMENU 2<br>
**up** - porusza stworzony objekt w górę HMENU 3<br>
**down** - porusza stworzony objekt w dół HMENU 4<br>
**wieza_ktk** - tworzy wieżę kwadrat->trójkąt->koło<br>
**wieza_kkt** - tworzy wieżę koło->kwadrat->trójkąt<br>
