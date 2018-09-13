#ifndef GAME_H
#define GAME_H
#include "Flag.h"
#include "GameInteger.h"
#include "Scene.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        std::vector <Flag> flags;
        std::vector <GameInteger> gameIntegers;
        std::vector <Scene> scenes;

        std::string filename = "";

        void loadGame (std::string filename);
        void saveGame (std::string filename);

        void loop ();

    protected:

    private:

        void readFileInputUntilDelimiter (std::ifstream &file, std::string &input, std::string delimiter);

        bool choiceIsValid (int choiceIndex);

        int returnIndexOfGameIntegerFromName (std::string name);

        int currentScene = 0;
};

#endif // GAME_H
