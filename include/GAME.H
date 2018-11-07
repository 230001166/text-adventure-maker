#ifndef GAME_H
#define GAME_H
#include "Renderer.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        GameDataStructures gamedata;

        Renderer renderer;

        std::string filename = "";

        void loadGame (std::string filename);
        void saveGame (std::string filename);

        void loop ();

    protected:

    private:

        void readFileInputUntilDelimiter (std::ifstream &file, std::string &input, std::string delimiter);

        bool flagComparisionIsTrue (bool flagComparision, Flag flag);

        bool integerComparisionIsTrue (std::string integerComparision, GameInteger gameInteger, int amount);

        bool choiceIsValid (int choiceIndex);

        int returnIndexOfGameIntegerFromName (std::string name);

        int returnIndexOfFlagFromName (std::string name);

        int currentScene = 0;
};

#endif // GAME_H
