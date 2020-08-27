#pragma once
#include "GameObject.h"
class Text :
    public GameObject
{
private:
    std::string text;
    WORD bgColour;
public:
    std::string getText();
    Text();
    Text(std::string text);
    Text(std::string text, WORD bg);
    void setText(std::string text);
    void setText(std::string text, WORD bg);
    std::string getType();
    ~Text();

    Text* clone() const { return new Text(*this); };
};

