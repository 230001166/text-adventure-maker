#include "Editor.h"
#include <iostream>

Editor::Editor()
{
    //ctor
}

Editor::~Editor()
{
    //dtor
}

void Editor::start () {

    std::cout << "Text Adventure Maker\n\n\n[E]dit Game\n[C]reate New Game\n[P]lay Game" << std::endl;

    std::string input = "";

    while (input != "E" && input != "e" && input != "C" && input != "c" && input != "P" && input != "p") {

        std::cin >> input;

    }

    if (input == "E" || input == "e") {

        std::cout << "Enter filename of game: ";

        std::cin >> input;

        game.loadGame (input);

        loop ();

    }

    if (input == "C" || input == "c") {

        loop ();

    }

    if (input == "P" || input == "p") {

        std::cout << "Enter filename of game: ";

        std::cin >> input;

        game.loadGame (input);

        game.loop ();

    }

}

void Editor::loop () {

    bool isLooping = true;

    char input = '0';

    while (isLooping) {

        std::cout << "[G]ame Save | [L]oad Game" << std::endl;
        std::cout << "[S]cenes: " << game.scenes.size () << " | [F]lags: " << game.flags.size () << " |" << std::endl;

        std::cin >> input;

        if (input == 'g') {

            game.saveGame (game.filename + ".game");

        }

        if (input == 'q') { isLooping = false; }

        if (input == 's' || input == 'S') {

            std::cout << "[E]dit Scene [A]dd Scene [D]elete Scene\nScenes:" << std::endl;

            for (unsigned int i = 0; i < game.scenes.size (); i++) {

                std::cout << "[" << i << "] " << game.scenes [i].name << std::endl;

            }

            std::cin >> input;

            if (input == 'a') {

                Scene test;

                std::cout << "New Scene Name: ";

                std::cin.ignore ();

                std::getline (std::cin, test.name);

                std::cout << "New Scene Description: ";

                std::cin.ignore ();

                std::getline (std::cin, test.description);

                game.scenes.push_back (test);

            }

        }

    }

}
