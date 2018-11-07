#include "Scene.h"
#include <iostream>

Scene::Scene()
{
    //ctor
}

Scene::~Scene()
{
    //dtor
}

void Scene::render () {

    printCenteredText(name, 120);

    std::cout << "\n" << description << std::endl;

    for (unsigned int i = 0; i < choices.size (); i++) {

        if (!choices [i].requiresAmountToBeAvailable && !choices [i].requiresFlagToBeAvailable) {

            std::cout << "[" << i+1 << "] - " << choices [i].name << std::endl;

        }

    }

}

void Scene::printCenteredText (std::string message, int width) {

    int messageLength = message.length ();

    int offset = (width / 2) - (messageLength / 2);

    for (int i = 0; i < offset; i++) {

        std::cout << " ";

    }

    std::cout << message << std::endl;

}
