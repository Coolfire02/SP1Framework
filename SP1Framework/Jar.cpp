#include "Jar.h"

std::string Jar::getType()
{
    return "Jar";
}

Jar::Jar()
{
    art.setArt(JAR_ART);
    weight = 1000;
}

Jar::~Jar()
{

}
