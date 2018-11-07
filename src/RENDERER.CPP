#include "Renderer.h"
#include <iostream>

Renderer::Renderer()
{
    //ctor
}

Renderer::~Renderer()
{
    //dtor
}

void Renderer::render (Scene scene, GameDataStructures gamedata) {

    printCenteredText (scene.name);

    std::cout << "\n" << scene.description << std::endl;

    for (unsigned int i = 0; i < scene.choices.size (); i++) {

        if (!scene.choices [i].requiresAmountToBeAvailable && !scene.choices [i].requiresFlagToBeAvailable) {

            std::cout << "[" << i+1 << "] - " << scene.choices [i].name << std::endl;

        } else if (scene.choices [i].requiresAmountToBeAvailable
            && scene.choices [i].amount == gamedata.gameIntegers [scene.choices [i].integerIndex].value) {

            std::cout << "[" << i+1 << "] - " << scene.choices [i].name << std::endl;

        } else if (scene.choices [i].requiresFlagToBeAvailable
            && scene.choices [i].flagComparisionType == gamedata.flags [scene.choices [i].flagIndex].isTrue) {

            std::cout << "[" << i+1 << "] - " << scene.choices [i].name << std::endl;

        }

    }

}

void Renderer::printCenteredText (std::string message) {

    int messageLength = message.length ();

    int offset = (consoleWidth / 2) - (messageLength / 2);

    for (int i = 0; i < offset; i++) {

        std::cout << " ";

    }

    std::cout << message << std::endl;

}
