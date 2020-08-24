#include "Text.h"
Text::Text()
{
	art.setArt(" ");
	weight = 1000;
}
Text::Text(std::string text)
{
	art.setArt(text);
	weight = 1000;
}
Text::Text(std::string text, WORD bg)
{
	art.setArt(text, bg);
	weight = 1000;
}
void Text::setText(std::string text)
{
	art.deleteArt();
	art.setArt(text);
}
void Text::setText(std::string text, WORD bg)
{
	art.deleteArt();
	art.setArt(text, bg);
}
std::string Text::getType()
{
	return "Text";
}
Text::~Text()
{
	//Intentionally left blank.
}
