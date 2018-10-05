#include "textGraphics.h"
#include <windows.h>

namespace textGraphics {

    void changeTextColor (int colorcode) {

        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute (hConsole, colorcode);

    }

}
