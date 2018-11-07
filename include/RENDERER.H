#ifndef RENDERER_H
#define RENDERER_H
#include "GameDataStructures.h"

class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();

        void render (Scene scene, GameDataStructures gamedata);
    protected:

    private:

        const int consoleWidth = 120;

        void printCenteredText(std::string message);
};

#endif // RENDERER_H
