#include "Game.h"
#include <fstream>
#include <iostream>

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::loadGame (std::string filename) {

    std::string line;
    std::ifstream file (filename + ".game");

    Game::filename = filename;

    if (file.is_open())  {

        int sceneSize;

        file >> sceneSize;

        scenes.clear ();

        for (unsigned int i = 0; i < sceneSize; i++) {

            Scene tempScene;

            tempScene.name = "";

            readFileInputUntilDelimiter (file, tempScene.name, "|");

            readFileInputUntilDelimiter (file, tempScene.description, "|");

            int choicesSize;

            file >> choicesSize;

            for (unsigned int j = 0; j < choicesSize; j++) {

                Choice choice;

                readFileInputUntilDelimiter (file, choice.name, "|");

                file >> choice.sceneIDToSwitchTo;

                int valuesSize = 0;

                file >> valuesSize;

                for (unsigned int k = 0; k < valuesSize; k++) {

                    std::string name = ""; int amount = 0;

                    readFileInputUntilDelimiter (file, name, "|");

                    file >> amount;

                    choice.modifiedValueAmounts.push_back (amount);
                    choice.modifiedValueNames.push_back (name);

                }

                file >> valuesSize;

                for (unsigned int k = 0; k < valuesSize; k++) {

                    std::string name = ""; bool value = false;

                    readFileInputUntilDelimiter (file, name, "|");

                    file >> value;

                    choice.flagValues.push_back (value);
                    choice.modifiedFlagNames.push_back (name);

                }

                file >> choice.flagComparisionType;

                file >> choice.requiresFlagToBeAvailable;

                file >> choice.flagIndex;

                tempScene.choices.push_back (choice);

            }

            scenes.push_back (tempScene);

        }

        int flagSize;

        file >> flagSize;

        flags.clear ();

        for (unsigned int i = 0; i < flagSize; i++) {

            Flag tempFlag;

            tempFlag.name = "";

            readFileInputUntilDelimiter (file, tempFlag.name, "|");

            file >> tempFlag.isTrue;

            flags.push_back (tempFlag);

        }

        int gameIntegerSize;

        file >> gameIntegerSize;

        gameIntegers.clear ();

        for (unsigned int i = 0; i < gameIntegerSize; i++) {

            GameInteger gameInteger;

            gameInteger.name = "";

            readFileInputUntilDelimiter (file, gameInteger.name, "|");

            file >> gameInteger.value;

            gameIntegers.push_back (gameInteger);
        }

        std::cout << "Game loaded!" << std::endl;

        file.close ();

    }

}

void Game::saveGame (std::string filename) {

    std::ofstream file (filename);

    if (file.is_open()) {

        file << scenes.size () << "\n";

        for (unsigned int i = 0; i < scenes.size (); i++) {

            file << scenes [i].name << " | " << "\n";

            file << scenes [i].description << " | " << "\n";

            file << scenes [i].choices.size () << "\n";

            for (unsigned int j = 0; j < scenes [i].choices.size (); j++) {

                file << scenes [i].choices [j].name << " | " << "\n";

                file << scenes [i].choices [j].sceneIDToSwitchTo << "\n";

                file << scenes [i].choices [j].modifiedValueAmounts.size () << "\n";

                for (unsigned int k = 0; k < scenes [i].choices [j].modifiedValueAmounts.size (); k++) {

                    file << scenes [i].choices [j].modifiedValueNames [k] << " | " << "\n";

                    file << scenes [i].choices [j].modifiedValueAmounts [k] << "\n";

                }

                file << scenes [i].choices [j].flagValues.size () << "\n";

                for (unsigned int k = 0; k < scenes [i].choices [j].flagValues.size (); k++) {

                    file << scenes [i].choices [j].modifiedFlagNames [k] << " | " << "\n";

                    file << scenes [i].choices [j].flagValues [k] << "\n";

                }

                file << scenes [i].choices [j].flagComparisionType << "\n";

                file << scenes [i].choices [j].requiresFlagToBeAvailable << "\n";

                file << scenes [i].choices [j].flagIndex << "\n";

            }

        }

        file << flags.size () << "\n";

        for (unsigned int i = 0; i < flags.size (); i++) {

            file << flags [i].name << " | " << "\n";

            file << flags [i].isTrue << "\n";

        }

        file << gameIntegers.size () << "\n";

        for (unsigned int i = 0; i < gameIntegers.size (); i++) {

            file << gameIntegers [i].name << " | " << "\n";

            file << gameIntegers [i].value << "\n";
        }

        file.close ();

    }

}

void Game::readFileInputUntilDelimiter (std::ifstream &file, std::string &input, std::string delimiter) {

    std::string line;

    input = "";

    if (file.is_open()) {

        while (line != delimiter) {

            file >> line;

            if (line != delimiter) {

                input += line + " ";

            }

        }

    }

}

void Game::loop () {

    bool isLooping = true;

    while (isLooping) {

        scenes [currentScene].render ();

        bool loopingInput = true;

        int choice = 0;

        while (loopingInput) {

            std::cin >> choice;

            if (choiceIsValid (choice)) {

                for (unsigned int i = 0; i < scenes [currentScene].choices [choice-1].modifiedValueAmounts.size (); i++) {

                    int index = returnIndexOfGameIntegerFromName (scenes [currentScene].choices [choice-1].modifiedValueNames [i]);

                    if (index != -1) {

                        gameIntegers [index].value += scenes [currentScene].choices [choice-1].modifiedValueAmounts [i];

                    }

                }

                for (unsigned int i = 0; i < scenes [currentScene].choices [choice-1].flagValues.size (); i++) {

                    int index = returnIndexOfFlagFromName (scenes [currentScene].choices [choice-1].modifiedFlagNames [i]);

                    if (index != -1) {

                        flags [index].isTrue = scenes [currentScene].choices [choice-1].flagValues [i];

                    }

                }

                currentScene = scenes [currentScene].choices [choice-1].sceneIDToSwitchTo;

                loopingInput = false;

            } else {

                std::cout << "Invalid input!" << std::endl;

            }

        }

    }

}

bool Game::flagComparisionIsTrue (bool flagComparision, Flag flag) {

    if (flag.isTrue == flagComparision) { return true; } else { return false; }

}

bool Game::choiceIsValid (int choiceIndex) {

    if (choiceIndex-1 >= scenes [currentScene].choices.size () || choiceIndex-1 < 0) {

        return false;

    } else {

        if (flagComparisionIsTrue (scenes [currentScene].choices [choiceIndex].flagComparisionType,
                flags [scenes [currentScene].choices [choiceIndex].flagIndex])
            || scenes [currentScene].choices [choiceIndex].requiresFlagToBeAvailable == false) {

            return true;

        } else {

            return false;

        }


    }

}

int Game::returnIndexOfGameIntegerFromName (std::string name) {

    for (unsigned int i = 0; i < gameIntegers.size (); i++) {

        if (gameIntegers [i].name == name) {

            return i;

        }

    }

    return -1;

}

int Game::returnIndexOfFlagFromName (std::string name) {

    for (unsigned int i = 0; i < flags.size (); i++) {

        if (flags [i].name == name) {

            return i;

        }

    }

    return -1;

}

