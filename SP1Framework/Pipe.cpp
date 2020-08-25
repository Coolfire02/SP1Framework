#include "Pipe.h"


Pipe::Pipe()
{
	art.setArt(PIPE_ART);
	weight = 700;
}

Pipe::~Pipe()
{
}

std::string Pipe::getType()
{
	return "Pipe";
}
