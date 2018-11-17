#include "Editor.h"
#include "textGraphics.h"
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

    int numberOfGameVariablesToModify = 0;

    std::cout << "Number of game integers to modify: ";

    std::cin >> numberOfGameVariablesToModify;

    for (int i = 0; i < numberOfGameVariablesToModify; i++) {

        std::string gameIntegerName;

        std::cout << "Enter name of game integer to modify: ";

        std::cin.ignore ();

        std::getline (std::cin, gameIntegerName);

        newChoice.modifiedValueNames.push_back (gameIntegerName);

        int amountToModify = 0;

        std::cout << "Enter the amount to modify this integer: ";

        std::cin >> amountToModify;

        newChoice.modifiedValueAmounts.push_back (amountToModify);

    }

    int numberOfFlagsToModify = 0;

    std::cout << "Number of flags to modify: ";

    std::cin >> numberOfFlagsToModify;

    for (int i = 0; i < numberOfFlagsToModify; i++) {

        std::string flagName;

        std::cout << "Enter name of flag to modify: ";

        std::cin.ignore ();

        std::getline (std::cin, flagName);

        newChoice.modifiedValueNames.push_back (flagName);

        bool value = 0;

        std::cout << "Enter the amount to modify this flag (0 = false, 1 = true): ";

        std::cin >> value;

        newChoice.flagValues.push_back (value);

    }

    return newChoice;

}

void Editor::editChoice (int sceneIndex, int choiceIndex) {

    bool stillEditing = true;

    while (stillEditing) {

        std::cout << game.gamedata.scenes [sceneIndex].choices [choiceIndex].name << std::endl;
        std::cout << "Change Choice [N]ame | Add [F]lag Requirement | Add [I]nteger Requirement | [S]top Editing" << std::endl;

        char input = ' ';

        std::cin >> input;

        if (input == 'N' || input == 'n') {

            std::cout << "Enter the new name for the choice: ";

            std::cin.ignore ();

            std::getline (std::cin, game.gamedata.scenes [sceneIndex].choices [choiceIndex].name);

        }

        if (input == 'F' || input == 'f') {

            game.gamedata.scenes [sceneIndex].choices [choiceIndex].requiresFlagToBeAvailable = true;

            std::cout << "Enter the index of the flag required for this choice: ";

            std::cin >> game.gamedata.scenes [sceneIndex].choices [choiceIndex].flagIndex;

            std::cout << "Should the flag be (0) false or (1) true for this choice to appear? ";

            std::cin >> game.gamedata.scenes [sceneIndex].choices [choiceIndex].flagComparisionType;

        }

        if (input == 'I' || input == 'i') {

            game.gamedata.scenes [sceneIndex].choices [choiceIndex].requiresAmountToBeAvailable = true;

            std::cout << "Enter the index of the integer required for this choice: ";

            std::cin >> game.gamedata.scenes [sceneIndex].choices [choiceIndex].integerIndex;

            std::cout << "Enter a value to compare the integer to: ";

            std::cin >> game.gamedata.scenes [sceneIndex].choices [choiceIndex].amount;

            std::cout << "Should the integer be (0) less than, (1) equal to, or (2) greater than the above amount for this choice to appear? ";

            int tempIntegerInput = 0; std::cin >> tempIntegerInput;

            if (tempIntegerInput == 0 || tempIntegerInput < 0 || tempIntegerInput > 2) {

                game.gamedata.scenes [sceneIndex].choices [choiceIndex].integerComparisionType = "less than";

            } else if (tempIntegerInput == 1) {

                game.gamedata.scenes [sceneIndex].choices [choiceIndex].integerComparisionType = "equal to";

            } else if (tempIntegerInput == 2) {

                game.gamedata.scenes [sceneIndex].choices [choiceIndex].integerComparisionType = "greater than";

            }

        }

        if (input == 'S' || input == 's') {

            stillEditing = false;

        }

    }

}

void Editor::editScene (int integerInput) {

    bool stillEditing = true;

    while (stillEditing) {

        std::cout << game.gamedata.scenes [integerInput].name << "\n" << game.gamedata.scenes [integerInput].description << std::endl;

        for (unsigned int i = 0; i < game.gamedata.scenes [integerInput].choices.size (); i++) {

            std::cout << "[" << i << "] " << game.gamedata.scenes [integerInput].choices [i].name << " -> " << game.gamedata.scenes [integerInput].choices [i].sceneIDToSwitchTo << std::endl;

        }

        std::cout << "[S]ave Scene | [A]dd Choice | [E]dit Choice | [D]elete Choice | Edit [N]ame and Description" << std::endl;

        char textInput = ' ';

        std::cin >> textInput;

        if (textInput == 'E' || textInput == 'e') {

            std::cout << "Enter the index of the choice you want to edit: ";

            int choiceIndex = 0;

            std::cin >> choiceIndex;

            if (choiceIndex >= 0 && choiceIndex < game.gamedata.scenes [integerInput].choices.size ()) {

                editChoice (integerInput, choiceIndex);

            }

        }

        if (textInput == 'S' || textInput == 's') { stillEditing = false; }

        if (textInput == 'A' || textInput == 'a') {

            Choice newChoice = createChoiceFromPlayerInput ();

            game.gamedata.scenes [integerInput].choices.push_back (newChoice);

        }

        if (textInput == 'D' || textInput == 'd') {

            std::cout << "Input scene number to delete: ";

            int input;

            std::cin >> input;

            if (input >= 0 && input < game.gamedata.scenes.size ()) {

                game.gamedata.scenes.erase (game.gamedata.scenes.begin () + input);

            }

        }

        if (textInput == 'N' || textInput == 'n') {

            std::cout << "New Scene Name: ";

            std::cin.ignore ();

            std::getline (std::cin, game.gamedata.scenes [integerInput].name);

            std::cout << "New Scene Description: ";

            std::cin.ignore ();

            std::getline (std::cin, game.gamedata.scenes [integerInput].description);

        }

    }

}

void Editor::outputInvalidChoices (int sceneIndex) {

    std::vector <int> invalidChoiceIndices;

    for (unsigned int i = 0; i < game.gamedata.scenes [sceneIndex].choices.size (); i++) {

        if (game.gamedata.scenes [sceneIndex].choices [i].sceneIDToSwitchTo < 0 || game.gamedata.scenes [sceneIndex].choices [i].sceneIDToSwitchTo >= game.gamedata.scenes.size ()) {

            invalidChoiceIndices.push_back (i);

        }

    }

    for (unsigned int i = 0; i < invalidChoiceIndices.size (); i++) {

        if (i == 0) { std::cout << " - Invalid Choices ["; }

        textGraphics::changeTextColor (12);

        std::cout << invalidChoiceIndices [i];

        if (i + 1 == invalidChoiceIndices.size ()) { textGraphics::changeTextColor (15); std::cout << "]"; } else { textGraphics::changeTextColor (15); std::cout << ","; }

    }

}

Scene Editor::createSceneFromPlayerInput () {

    Scene test;

    std::cout << "New Scene Name: ";

    std::cin.ignore ();

    std::getline (std::cin, test.name);

    std::cout << "New Scene Description: ";

    std::cin.ignore ();

    std::getline (std::cin, test.description);

    bool loop = true;

    while (loop) {

        char input = '0';

        std::cout << "[A]dd Choice [D]elete Choice [S]ave Scene" << std::endl;

        std::cin >> input;

        if (input == 'a' || input == 'A') {

            Choice newChoice = createChoiceFromPlayerInput ();

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

    return test;

}

std::string Editor::returnBooleanAsString (bool booleanInput) {

    if (booleanInput) { return "True"; } else { return "False"; }

}

void Editor::displayAllFlags () {

    for (unsigned int i = 0; i < game.gamedata.flags.size (); i++) {

        std::cout << "[" << i << "] " << game.gamedata.flags [i].name << " | " << returnBooleanAsString (game.gamedata.flags [i].isTrue) << std::endl;

    }

}

void Editor::editFlag (int flagIndex) {

    bool stillEditing = true;

    while (stillEditing) {

        if (flagIndex < 0 || flagIndex >= game.gamedata.flags.size ()) { stillEditing = false; }

        std::cout << game.gamedata.flags [flagIndex].name << " | " << game.gamedata.flags [flagIndex].isTrue << std::endl;

        std::cout << "Change [N]ame | Change [V]alue | [S]top Editing Flag" << std::endl;

        char input;

        std::cin >> input;

        if (input == 'N' || input == 'n') {

            std::cout << "Enter a new name for the flag: ";

            std::cin >> game.gamedata.flags [flagIndex].name;

        }

        if (input == 'V' || input == 'v') {

            std::cout << "Enter a value for the flag (0 is false, 1 is true): ";

            std::cin >> game.gamedata.flags [flagIndex].isTrue;

        }

        if (input == 'S' || input == 's') {

            stillEditing = false;

        }

    }

}

void Editor::editFlags () {

    bool stillEditing = true;

    while (stillEditing) {

        displayAllFlags ();

        std::cout << "[A]dd Flag | [E]dit Flag | [D]elete Flag | [S]top Editing Flags" << std::endl;

        char input = ' ';

        std::cin >> input;

        if (input == 'A' || input == 'a') {

            Flag temp;

            std::cout << "Enter the new flag's name: ";

            std::cin.ignore ();

            std::getline (std::cin, temp.name);

            std::cout << "Enter the flag's value (0 or 1, where 0 is false and 1 is true): ";

            std::cin >> temp.isTrue;

            game.gamedata.flags.push_back (temp);

        }

        if (input == 'E' || input == 'e') {

            std::cout << "Input the flag number to edit: ";

            int flagIndex = -1;

            std::cin >> flagIndex;

            if (flagIndex >= 0 && flagIndex < game.gamedata.flags.size ()) {

                editFlag (flagIndex);

            } else {

                std::cout << "Invalid index!" << std::endl;

            }

        }

        if (input == 'D' || input == 'd') {

            std::cout << "Input the flag number to delete: ";

            int flagIndex = -1;

            std::cin >> flagIndex;

            if (flagIndex >= 0 && flagIndex < game.gamedata.flags.size ()) {

                game.gamedata.flags.erase (game.gamedata.flags.begin () + flagIndex);

            } else {

                std::cout << "Invalid index!" << std::endl;

            }

        }

        if (input == 'S' || input == 's') {

            stillEditing = false;

        }

    }

}

void Editor::displayAllGameIntegers () {

    for (unsigned int i = 0; i < game.gamedata.gameIntegers.size (); i++) {

        std::cout << "[" << i << "] " << game.gamedata.gameIntegers [i].name << " | " << game.gamedata.gameIntegers [i].value << std::endl;

    }

}

void Editor::editGameInteger (int integerIndex) {

    bool stillEditing = true;

    while (stillEditing) {

        if (integerIndex < 0 || integerIndex >= game.gamedata.gameIntegers.size ()) { stillEditing = false; }

        std::cout << game.gamedata.gameIntegers [integerIndex].name << " | " << game.gamedata.gameIntegers [integerIndex].value << std::endl;

        std::cout << "Change [N]ame | Change [V]alue | [S]top Editing Integer" << std::endl;

        char input;

        std::cin >> input;

        if (input == 'N' || input == 'n') {

            std::cout << "Enter a new name for the integer: ";

            std::cin >> game.gamedata.gameIntegers [integerIndex].name;

        }

        if (input == 'V' || input == 'v') {

            std::cout << "Enter a value for the integer: ";

            std::cin >> game.gamedata.gameIntegers [integerIndex].value;

        }

        if (input == 'S' || input == 's') {

            stillEditing = false;

        }

    }

}

void Editor::editGameIntegers () {

    bool stillEditing = true;

    while (stillEditing) {

        displayAllGameIntegers ();

        std::cout << "[A]dd Integer | [E]dit Integer | [D]elete Integer | [S]top Editing Integers" << std::endl;

        char input = ' ';

        std::cin >> input;

        if (input == 'A' || input == 'a') {

            GameInteger temp;

            std::cout << "Enter the new game integer's name: ";

            std::cin.ignore ();

            std::getline (std::cin, temp.name);

            std::cout << "Enter the game integer's value: ";

            std::cin >> temp.value;

            game.gamedata.gameIntegers.push_back (temp);

        }

        if (input == 'E' || input == 'e') {

            std::cout << "Input the index of the integer to edit: ";

            int integerIndex = -1;

            std::cin >> integerIndex;

            if (integerIndex >= 0 && integerIndex < game.gamedata.gameIntegers.size ()) {

                editGameInteger (integerIndex);

            } else {

                std::cout << "Invalid index!" << std::endl;

            }

        }

        if (input == 'D' || input == 'd') {

            std::cout << "Input the index of the integer to delete: ";

            int integerIndex = -1;

            std::cin >> integerIndex;

            if (integerIndex >= 0 && integerIndex < game.gamedata.gameIntegers.size ()) {

                game.gamedata.gameIntegers.erase (game.gamedata.gameIntegers.begin () + integerIndex);

            } else {

                std::cout << "Invalid index!" << std::endl;

            }

        }

        if (input == 'S' || input == 's') {

            stillEditing = false;

        }

    }

}

void Editor::loop () {

    bool isLooping = true;

    char input = '0';

    while (isLooping) {

        std::cout << "[G]ame Save | [L]oad Game | [Q]uit" << std::endl;
        std::cout << "[S]cenes: " << game.gamedata.scenes.size () << " | Fl[a]gs: " << game.gamedata.flags.size ()
            << " | Game [I]ntegers : " << game.gamedata.gameIntegers.size () << " | [F]ilename: " << game.filename << std::endl;

        std::cin >> input;

        if (input == 'g') {

            game.saveGame (game.filename + ".game");

        }

        if (input == 'l') {

            std::cout << "Input a file name to load: ";

            std::cin >> game.filename;

            game.loadGame (game.filename);

        }

        if (input == 'q') { isLooping = false; }

        if (input == 'a') {

            editFlags ();

        }

        if (input == 'I' || input == 'i') {

            editGameIntegers ();

        }

        if (input == 'F' || input == 'f') {

            std::string textInput = "";

            std::cout << "Enter filename of game: ";

            std::cin >> textInput;

            game.filename = textInput;

        }

        if (input == 's' || input == 'S') {

            std::cout << "[S]top Editing Scenes [E]dit Scene [A]dd Scene [D]elete Scene\nScenes:" << std::endl;

            for (unsigned int i = 0; i < game.gamedata.scenes.size (); i++) {

                std::cout << "[" << i << "] " << game.gamedata.scenes [i].name; outputInvalidChoices (i); std::cout << " " << std::endl;

            }

            std::cin >> input;

            if (input == 'e') {

                std::cout << "Enter scene number to edit: ";

                int integerInput;

                std::cin >> integerInput;

                editScene (integerInput);

            }

            if (input == 'a') {

                Scene test = createSceneFromPlayerInput ();

                game.gamedata.scenes.push_back (test);

            }

            if (input == 'd') {

                std::cout << "Which scene do you want to delete? ";

                int sceneNumber = 0;

                std::cin >> sceneNumber;

                if (sceneNumber >= 0 && sceneNumber < game.gamedata.scenes.size ()) {

                    game.gamedata.scenes.erase (game.gamedata.scenes.begin () + sceneNumber);

                    std::cout << "Scene " << sceneNumber << " erased!" << std::endl;

                }

            }

        }

    }

}
