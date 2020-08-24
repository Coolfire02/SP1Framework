#include "Text.h"
Text::Text()
{
	text = " ";
	art.setArt(text);
	weight = 1500;
}
Text::Text(std::string text) : text(text)
{
	art.setArt(this->text);
	weight = 1500;
}
Text::Text(std::string text, WORD bg) : text(text)
{
	art.setArt(this->text, bg);
	weight = 1500;
}
void Text::setText(std::string text)
{
	this->text = text;
	art.deleteArt();
	art.setArt(this->text);
}
void Text::setText(std::string text, WORD bg)
{
	this->text = text;
	art.deleteArt();
	art.setArt(this->text, bg);
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
