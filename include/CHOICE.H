#ifndef CHOICE_H
#define CHOICE_H

struct Choice {

    std::string name;

    int sceneIDToSwitchTo = 0;

    std::vector <std::string> modifiedValueNames;
    std::vector <int> modifiedValueAmounts;

    std::vector <std::string> modifiedFlagNames;
    std::vector <int> flagValues;

    bool requiresFlagToBeAvailable = false;
    bool flagComparisionType = true;
    int flagIndex = 0;

    bool requiresAmountToBeAvailable = false;
    std::string integerComparisionType = "equal to";
    int integerIndex = 0;
    int amount = 0;

};

#endif // CHOICE_H
