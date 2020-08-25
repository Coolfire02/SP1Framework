#include "Pipe.h"


Pipe::Pipe()
{
	art.setArt(PIPE_ART);
	weight = 100;
}

Pipe::~Pipe()
{
}

std::string Pipe::getType()
{
	return "Pipe";
}
