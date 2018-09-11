#ifndef FLAG_H
#define FLAG_H
#include <string>

class Flag
{
    public:
        Flag();
        virtual ~Flag();

        std::string name;

        bool isTrue;
};

#endif // FLAG_H
