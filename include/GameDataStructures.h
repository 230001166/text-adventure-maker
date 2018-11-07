#ifndef GAMEDATASTRUCTURES_H
#define GAMEDATASTRUCTURES_H
#include "Flag.h"
#include "GameInteger.h"
#include "Scene.h"

class GameDataStructures
{
    public:
        GameDataStructures() {};
        virtual ~GameDataStructures() {};

        std::vector <Flag> flags;
        std::vector <GameInteger> gameIntegers;
        std::vector <Scene> scenes;

    protected:

    private:
};

#endif // GAMEDATASTRUCTURES_H
