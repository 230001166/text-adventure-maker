#include <iostream>
#include <windows.h>
#include "Game.h"

int main()
{

    Game testing;
    testing.loadGame ("test_save");
    testing.loop ();

    return 0;

}
