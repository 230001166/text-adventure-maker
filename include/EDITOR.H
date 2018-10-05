#ifndef EDITOR_H
#define EDITOR_H

#include "Game.h"

class Editor
{
    public:
        Editor();
        virtual ~Editor();

        Game game;

        void start ();

        void loop ();

    protected:

    private:

        void editScene (int integerInput);

        void outputInvalidChoices (int sceneIndex);

        Choice createChoiceFromPlayerInput ();
};

#endif // EDITOR_H
