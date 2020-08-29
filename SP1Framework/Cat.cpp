#include "Cat.h"

std::string Cat::getType()
{
    return "Cat";
}

Cat::Cat()
{
    art.setArt(CAT_ART);
    weight = 1000;
}

Cat::~Cat()
{

}