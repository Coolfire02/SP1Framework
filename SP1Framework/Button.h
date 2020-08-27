#pragma once
#include "GameObject.h"
#include "Text.h"

class Button : public GameObject
{
private:
	std::string buttonType;
public:
	Text text;
	std::string getType();
	std::string getButtonType();
	Button();
	~Button();

	Button* clone() const { return new Button(*this); };
};

