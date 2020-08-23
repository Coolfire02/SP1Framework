#include "Jar.h"

std::string Jar::getType()
{
    art.setArt(JAR_ART);
    return "Jar";
}

Jar::Jar()
{
    weight = 800;
}

Jar::~Jar()
{

}
