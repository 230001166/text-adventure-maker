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

    std::string line, filenameString = filename + ".game";
    std::ifstream file (filenameString.c_str ());

    Game::filename = filename;

    if (file.is_open())  {

        int sceneSize;

        file >> sceneSize;

        gamedata.scenes.clear ();

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

                readFileInputUntilDelimiter (file, choice.integerComparisionType, "|");

                file >> choice.requiresAmountToBeAvailable;

                file >> choice.integerIndex;

                file >> choice.amount;

                tempScene.choices.push_back (choice);

            }

            gamedata.scenes.push_back (tempScene);

        }

        int flagSize;

        file >> flagSize;

        gamedata.flags.clear ();

        for (unsigned int i = 0; i < flagSize; i++) {

            Flag tempFlag;

            tempFlag.name = "";

            readFileInputUntilDelimiter (file, tempFlag.name, "|");

            file >> tempFlag.isTrue;

            gamedata.flags.push_back (tempFlag);

        }

        int gameIntegerSize;

        file >> gameIntegerSize;

        gamedata.gameIntegers.clear ();

        for (unsigned int i = 0; i < gameIntegerSize; i++) {

            GameInteger gameInteger;

            gameInteger.name = "";

            readFileInputUntilDelimiter (file, gameInteger.name, "|");

            file >> gameInteger.value;

            gamedata.gameIntegers.push_back (gameInteger);
        }

        std::cout << "Game loaded!" << std::endl;

        file.close ();

    }

}

void Game::saveGame (std::string filename) {

    std::ofstream file (filename.c_str ());

    if (file.is_open()) {

        file <<  gamedata.scenes.size () << "\n";

        for (unsigned int i = 0; i < gamedata.scenes.size (); i++) {

            file <<  gamedata.scenes [i].name << " | " << "\n";

            file << gamedata.scenes [i].description << " | " << "\n";

            file << gamedata.scenes [i].choices.size () << "\n";

            for (unsigned int j = 0; j < gamedata.scenes [i].choices.size (); j++) {

                file << gamedata.scenes [i].choices [j].name << " | " << "\n";

                file << gamedata.scenes [i].choices [j].sceneIDToSwitchTo << "\n";

                file << gamedata.scenes [i].choices [j].modifiedValueAmounts.size () << "\n";

                for (unsigned int k = 0; k < gamedata.scenes [i].choices [j].modifiedValueAmounts.size (); k++) {

                    file << gamedata.scenes [i].choices [j].modifiedValueNames [k] << " | " << "\n";

                    file << gamedata.scenes [i].choices [j].modifiedValueAmounts [k] << "\n";

                }

                file << gamedata.scenes [i].choices [j].flagValues.size () << "\n";

                for (unsigned int k = 0; k < gamedata.scenes [i].choices [j].flagValues.size (); k++) {

                    file << gamedata.scenes [i].choices [j].modifiedFlagNames [k] << " | " << "\n";

                    file << gamedata.scenes [i].choices [j].flagValues [k] << "\n";

                }

                file << gamedata.scenes [i].choices [j].flagComparisionType << "\n";

                file << gamedata.scenes [i].choices [j].requiresFlagToBeAvailable << "\n";

                file << gamedata.scenes [i].choices [j].flagIndex << "\n";

                file << gamedata.scenes [i].choices [j].integerComparisionType << " | " << "\n";

                file << gamedata.scenes [i].choices [j].requiresAmountToBeAvailable << "\n";

                file << gamedata.scenes [i].choices [j].integerIndex << "\n";

                file << gamedata.scenes [i].choices [j].amount << "\n";

            }

        }

        file << gamedata.flags.size () << "\n";

        for (unsigned int i = 0; i < gamedata.flags.size (); i++) {

            file << gamedata.flags [i].name << " | " << "\n";

            file << gamedata.flags [i].isTrue << "\n";

        }

        file << gamedata.gameIntegers.size () << "\n";

        for (unsigned int i = 0; i < gamedata.gameIntegers.size (); i++) {

            file << gamedata.gameIntegers [i].name << " | " << "\n";

            file << gamedata.gameIntegers [i].value << "\n";
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

        input.pop_back ();

    }

}

void Game::loop () {

    bool isLooping = true;

    while (isLooping) {

        renderer.render (gamedata.scenes [currentScene], gamedata);

        std::cout << "Flags" << std::endl;

        for (unsigned int i = 0; i < gamedata.flags.size (); i++) {

            std::cout << "[" << i << "] - " << gamedata.flags [i].name << " - " << gamedata.flags [i].isTrue << std::endl;

        }

        bool loopingInput = true;

        int choice = 0;

        while (loopingInput) {

            std::cin >> choice;

            if (choiceIsValid (choice-1)) {

                for (unsigned int i = 0; i < gamedata.scenes [currentScene].choices [choice-1].modifiedValueAmounts.size (); i++) {

                    int index = returnIndexOfGameIntegerFromName (gamedata.scenes [currentScene].choices [choice-1].modifiedValueNames [i]);

                    if (index != -1) {

                        gamedata.gameIntegers [index].value += gamedata.scenes [currentScene].choices [choice-1].modifiedValueAmounts [i];

                    }

                }

                for (unsigned int i = 0; i < gamedata.scenes [currentScene].choices [choice-1].flagValues.size (); i++) {

                    int index = returnIndexOfFlagFromName (gamedata.scenes [currentScene].choices [choice-1].modifiedFlagNames [i]);

                    if (index != -1) {

                        gamedata.flags [index].isTrue = gamedata.scenes [currentScene].choices [choice-1].flagValues [i];

                    }

                }

                currentScene = gamedata.scenes [currentScene].choices [choice-1].sceneIDToSwitchTo;

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

bool Game::integerComparisionIsTrue (std::string integerComparision, GameInteger gameInteger, int amount) {

    if (integerComparision == "equal to" && gameInteger.value == amount) { return true; }

    if (integerComparision == "greater than" && gameInteger.value > amount) { return true; }

    if (integerComparision == "less than" && gameInteger.value < amount) { return true; }

    return false;

}

bool Game::choiceIsValid (int choiceIndex) {

    if (choiceIndex >= gamedata.scenes [currentScene].choices.size () || choiceIndex < 0) {

        return false;

    } else {

        if (gamedata.scenes [currentScene].choices [choiceIndex].requiresFlagToBeAvailable == false
            && gamedata.scenes [currentScene].choices [choiceIndex].requiresAmountToBeAvailable == false) {

            return true;

        } else {

            if (gamedata.flags.size () > 0 && gamedata.scenes [currentScene].choices [choiceIndex].requiresFlagToBeAvailable) {

                if (flagComparisionIsTrue (gamedata.scenes [currentScene].choices [choiceIndex].flagComparisionType,
                    gamedata.flags [gamedata.scenes [currentScene].choices [choiceIndex].flagIndex])) {

                    return true;

                } else {

                    return false;

                }

            } else if (gamedata.scenes [currentScene].choices [choiceIndex].requiresFlagToBeAvailable) {

                return false;

            }

            if (gamedata.gameIntegers.size () > 0) {

                if (integerComparisionIsTrue (gamedata.scenes [currentScene].choices [choiceIndex].integerComparisionType,
                    gamedata.gameIntegers [gamedata.scenes [currentScene].choices [choiceIndex].integerIndex],
                    gamedata.scenes [currentScene].choices [choiceIndex].amount)) {

                    return true;

                } else {

                    return false;

                }

            } else {

                return false;

            }

        }


    }

}

int Game::returnIndexOfGameIntegerFromName (std::string name) {

    for (unsigned int i = 0; i < gamedata.gameIntegers.size (); i++) {

        if (gamedata.gameIntegers [i].name == name) {

            return i;

        }

    }

    return -1;

}

int Game::returnIndexOfFlagFromName (std::string name) {

    for (unsigned int i = 0; i < gamedata.flags.size (); i++) {

        if (gamedata.flags [i].name == name) {

            return i;

        }

    }

    return -1;

}

