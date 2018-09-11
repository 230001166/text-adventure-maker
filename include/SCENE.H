#ifndef SCENE_H
#define SCENE_H
#include <string>
#include <vector>
#include "Choice.h"

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        std::string name = "default";
        std::string description = "test";

        std::vector <Choice> choices;

        void render();
    protected:

    private:
        void printCenteredText(std::string message, int width);
};

#endif // SCENE_H
