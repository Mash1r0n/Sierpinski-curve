#include <windows.h>
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);

int Size = 64;
int Pow = 0;

void Slash(int x, int y) {
    if (GetPixel(hdc, x, y) == RGB(11, 12, 12)) {
        return;
    }

    for (int i = 0; i < Size / 2 / 2; i++)
    {
        SetPixel(hdc, x - i, y - i, RGB(255, 255, 255));
        SetPixel(hdc, x + i, y + i, RGB(255, 255, 255));
    }
}

void BackSlash(int x, int y) {
    if (GetPixel(hdc, x, y) == RGB(11, 12, 12)) {
        return;
    }
    for (int i = 0; i < Size / 2 / 2; i++)
    {
        SetPixel(hdc, x - i, y + i, RGB(255, 255, 255));
        SetPixel(hdc, x + i, y - i, RGB(255, 255, 255));
    }
}

void HideSlash(int x, int y) {
    for (int i = 0; i < Size / 2 / 2; i++)
    {
        SetPixel(hdc, x - i, y - i, RGB(11, 12, 12));
        SetPixel(hdc, x + i, y + i, RGB(11, 12, 12));
    }
}

void HideBackSlash(int x, int y) {
    for (int i = 0; i < Size / 2 / 2; i++)
    {
        SetPixel(hdc, x - i, y + i, RGB(11, 12, 12));
        SetPixel(hdc, x + i, y - i, RGB(11, 12, 12));
    }
}

void VerLine(int x, int y, bool side) {
    for (int i = 0; i < Size; i++)
    {
        SetPixel(hdc, x, y - i, RGB(255, 255, 255));
        SetPixel(hdc, x, y + i, RGB(255, 255, 255));
        if (i == Size / 2) {
            if (side) {
                BackSlash(x + Size / 2 / 2, y - i - Size / 2 / 2);
                Slash(x + Size / 2 / 2, y + i + Size / 2 / 2);
            }
            else {
                Slash(x - Size / 2 / 2, y - i - Size / 2 / 2);
                BackSlash(x - Size / 2 / 2, y + i + Size / 2 / 2);
            }
            break;
        }
    }
}

void HorLine(int x, int y, bool side) {
    for (int i = 0; i < Size; i++)
    {
        SetPixel(hdc, x - i, y, RGB(255, 255, 255));
        SetPixel(hdc, x + i, y, RGB(255, 255, 255));
        if (i == Size / 2) {
            if (side) {
                BackSlash(x - Size + Size / 2 / 2, y + i - Size / 2 / 2);
                Slash(x + Size - Size / 2 / 2, y + i - Size / 2 / 2);
            }
            else {
                Slash(x - Size + Size / 2 / 2, y - i + Size / 2 / 2);
                BackSlash(x + Size - Size / 2 / 2, y - i + Size / 2 / 2);
            }
            break;
        }
    }
}

void DrawCorners(int x, int y, string Corners) {
    if (Corners.find('1') == string::npos) Slash(x - Size - Size / 2 / 2 + 1, y + Size + Size / 2 / 2 - 1); //Левый низ
    else HideSlash(x - Size + Size / 2 / 2 - 1, y + Size - Size / 2 / 2 + 1);

    if (Corners.find('2') == string::npos) BackSlash(x + Size + Size / 2 / 2 - 1, y + Size + Size / 2 / 2 - 1); //Правый низ
    else HideBackSlash(x + Size - Size / 2 / 2 + 1, y + Size - Size / 2 / 2 + 1);

    if (Corners.find('3') == string::npos) BackSlash(x - Size - Size / 2 / 2 + 1, y - Size - Size / 2 / 2 + 1); //Левый верх
    else HideBackSlash(x - Size + Size / 2 / 2 - 1, y - Size + Size / 2 / 2 - 1);

    if (Corners.find('4') == string::npos) Slash(x + Size + Size / 2 / 2 - 1, y - Size - Size / 2 / 2 + 1); //Правый верх
    else HideSlash(x + Size - Size / 2 / 2 + 1, y - Size + Size / 2 / 2 - 1);
}

void DegZero(int x, int y, string Corners) { //true - Право/Вниз false - Лево/Вверх
    VerLine(x + Size, y, true);
    VerLine(x - Size, y, false);
    HorLine(x, y + Size, true);
    HorLine(x, y - Size, false);
    DrawCorners(x, y, Corners);
}

void PathOne(int, int, int, int, int);
void PathTwo(int, int, int, int, int);
void PathThree(int, int, int, int, int);
void PathFour(int, int, int, int, int);
void SierpinskiCurve(int, int, int);
void Drawing(int, int, int, int, int);

void PathOne(int StartX, int StartY, int Degree, int Plus, int Minus) {
    Drawing(StartX, StartY, Degree - 1, Plus / 2, Minus / 2);
}

void PathTwo(int StartX, int StartY, int Degree, int Plus, int Minus) {
    Drawing(StartX, StartY, Degree - 1, Plus / 2, Minus / 2);
}

void PathThree(int StartX, int StartY, int Degree, int Plus, int Minus) {
    Drawing(StartX, StartY, Degree - 1, Plus / 2, Minus / 2);
}

void PathFour(int StartX, int StartY, int Degree, int Plus, int Minus) {
    Drawing(StartX, StartY, Degree - 1, Plus / 2, Minus / 2);
}

void Drawing(int StartX, int StartY, int Degree, int Plus, int Minus) {
    if (Degree == 0) {
        DegZero(StartX, StartY,"");
        return;
    }
    DegZero(StartX, StartY,"1234");
    PathOne(StartX + Minus, StartY - Plus, Degree, Plus, Minus); //Если тут поиграться с Plus и Minus, то можно треугольник сделать такой в рекурсии. Например: PathOne(StartX + Minus - Plus, StartY, Degree, Plus, Minus);
    PathTwo(StartX - Plus, StartY - Plus, Degree, Plus, Minus);
    PathThree(StartX - Plus, StartY + Minus, Degree, Plus, Minus);
    PathFour(StartX + Minus, StartY + Minus, Degree, Plus, Minus);
}

void SierpinskiCurve(int StartX, int StartY, int Degree) {
    if (Degree < 0 || Degree > 6) {
        cout << "Далі вже розмір не дозволяє";
        return;
    }
    Size = 64;
    Pow = pow(2, Degree);
    Size /= Pow;
    Drawing(StartX, StartY, Degree, Size * Pow, Size * Pow);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int a;
    cout << "Введіть порядок кривої серпінського від 0 до 6: ";
    cin >> a;

    SierpinskiCurve(500, 300, a);

    //Кривая серпинского зеркально в новом стандарте через многопоточность

    ReleaseDC(hwnd, hdc);
    cin.ignore();
    return 0;
}
