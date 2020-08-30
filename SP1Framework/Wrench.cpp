#include "Wrench.h"

Wrench::Wrench()
{
	//Intentionally left blank.
}

Wrench::Wrench(std::string type)
{
	if (type == "HEAD")
	{
		this->type = type;
		art.setArt(WRENCH_HEAD_ART);
		weight = 900;
	}
	else if (type == "TAIL")
	{
		this->type = type;
		art.setArt(WRENCH_TAIL_ART);
		weight = 800;
	}
}

Wrench::~Wrench()
{
	//Intentionally left blank
}

std::string Wrench::getType()
{
	if (type == "HEAD")
		return "WRENCH_HEAD";
	else if (type == "TAIL")
		return "WRENCH_TAIL";
	else
		return "WRENCH_UNKNOWN";
}
