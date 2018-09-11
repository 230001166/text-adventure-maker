#ifndef CHOICE_H
#define CHOICE_H

struct Choice {

    std::string name;

    int sceneIDToSwitchTo = 0;

    std::vector <std::string> modifiedValueNames;
    std::vector <int> modifiedValueAmounts;

};

#endif // CHOICE_H
