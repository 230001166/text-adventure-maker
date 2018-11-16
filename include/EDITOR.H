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

        std::string returnBooleanAsString (bool booleanInput);

        void displayAllFlags ();

        void editFlag (int flagIndex);

        void editFlags ();

        void displayAllGameIntegers ();

        void editGameInteger (int integerIndex);

        void editGameIntegers ();

        Choice createChoiceFromPlayerInput ();

        Scene createSceneFromPlayerInput ();
};

#endif // EDITOR_H
