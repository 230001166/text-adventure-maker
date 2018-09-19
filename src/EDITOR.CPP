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

    while (input != "E" && input != "e" && input != "C" && input != "c" && input != "P" && input != "p" && input != "F" && input != "f") {

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

Choice Editor::createChoiceFromPlayerInput () {

    Choice newChoice;

    std::cout << "New Choice Name: ";

    std::cin.ignore ();

    std::getline (std::cin, newChoice.name); std::cout << "> " << newChoice.name << std::endl;

    std::cout << "Scene number to switch to: ";

    std::cin >> newChoice.sceneIDToSwitchTo;

    return newChoice;

}

void Editor::editScene (int integerInput) {

    bool stillEditing = true;

    while (stillEditing) {

        std::cout << game.scenes [integerInput].name << "\n" << game.scenes [integerInput].description << std::endl;

        for (unsigned int i = 0; i < game.scenes [integerInput].choices.size (); i++) {

            std::cout << "[" << i << "] " << game.scenes [integerInput].choices [i].name << std::endl;

        }

        std::cout << "[S]ave Scene | [A]dd Choice | [E]dit Choice | [D]elete Choice | Edit [N]ame and Description" << std::endl;

        std::string textInput = "";

        std::cin >> textInput;

        if (textInput == "S" || textInput == "s") { stillEditing = false; }

        if (textInput == "A" || textInput == "a") {

            Choice newChoice = createChoiceFromPlayerInput ();

            game.scenes [integerInput].choices.push_back (newChoice);

        }

        if (textInput == "D" || textInput == "d") {

            std::cout << "Input scene number to delete: ";

            int input;

            std::cin >> input;

            if (input >= 0 && input < game.scenes.size ()) {

                game.scenes.erase (game.scenes.begin () + input);

            }

        }

        if (textInput == "N" || textInput == "n") {

            std::cout << "New Scene Name: ";

            std::cin.ignore ();

            std::getline (std::cin, game.scenes [integerInput].name);

            std::cout << "New Scene Description: ";

            std::cin.ignore ();

            std::getline (std::cin, game.scenes [integerInput].description);

        }

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

        if (input == 'F' || input == 'f') {

            std::string textInput = "";

            std::cout << "Enter filename of game: ";

            std::cin >> textInput;

            game.filename = textInput;

        }

        if (input == 's' || input == 'S') {

            std::cout << "[E]dit Scene [A]dd Scene [D]elete Scene\nScenes:" << std::endl;

            for (unsigned int i = 0; i < game.scenes.size (); i++) {

                std::cout << "[" << i << "] " << game.scenes [i].name << std::endl;

            }

            std::cin >> input;

            if (input == 'e') {

                std::cout << "Enter scene number to edit: ";

                int integerInput;

                std::cin >> integerInput;

                editScene (integerInput);

            }

            if (input == 'a') {

                Scene test;

                std::cout << "New Scene Name: ";

                std::cin.ignore ();

                std::getline (std::cin, test.name);

                std::cout << "New Scene Description: ";

                std::cin.ignore ();

                std::getline (std::cin, test.description);

                bool loop = true;

                while (loop) {

                    std::cout << "[A]dd Choice [D]elete Choice" << std::endl;

                    std::cin >> input;

                    if (input == 'a' || input == 'A') {

                        Choice newChoice;

                        std::cout << "New Choice Name: ";

                        std::cin.ignore ();

                        std::getline (std::cin, newChoice.name); std::cout << "> " << newChoice.name << std::endl;

                        std::cout << "Scene number to switch to: ";

                        std::cin >> newChoice.sceneIDToSwitchTo;

                        std::cout << "Saving choice..." << std::endl;

                        test.choices.push_back (newChoice);

                    }

                    if (input == 'd' || input == 'D') {

                        std::cout << "Which choice do you want to delete? ";

                        int choiceNumber = 0;

                        std::cin >> choiceNumber;

                        if (choiceNumber >= 0 && choiceNumber < test.choices.size ()) {

                            test.choices.erase (test.choices.begin () + choiceNumber);

                            std::cout << "choice " << choiceNumber << " erased!" << std::endl;

                        }

                    }

                    if (input == 's' || input == 'S') {

                        loop = false;

                    }

                }

                game.scenes.push_back (test);

            }

            if (input == 'd') {

                std::cout << "Which scene do you want to delete? ";

                int sceneNumber = 0;

                std::cin >> sceneNumber;

                if (sceneNumber >= 0 && sceneNumber < game.scenes.size ()) {

                    game.scenes.erase (game.scenes.begin () + sceneNumber);

                    std::cout << "Scene " << sceneNumber << " erased!" << std::endl;

                }

            }

        }

    }

}
