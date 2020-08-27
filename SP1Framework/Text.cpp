#include "Text.h"
Text::Text()
{
	text = " ";
	art.setArt(text);
	weight = 1500;
}
Text::Text(std::string text) : text(text)
{
	bgColour = 0x20;
	art.setArt(this->text, bgColour);
	weight = 1500;
}
Text::Text(std::string text, WORD bg) : text(text)
{
	bgColour = bg;
	art.setArt(this->text, bgColour);
	weight = 1500;
}
void Text::setText(std::string text)
{
	this->text = text;
	art.deleteArt();
	art.setArt(this->text, bgColour);
}
void Text::setText(std::string text, WORD bg)
{
	bgColour = bg;
	this->text = text;
	art.deleteArt();
	art.setArt(this->text, bgColour);
}
std::string Text::getType()
{
	return "Text";
}

std::string Text::getText() {
	return text;
}

Text::~Text()
{
	//Intentionally left blank.
}
