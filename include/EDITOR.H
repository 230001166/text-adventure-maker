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
};

#endif // EDITOR_H
