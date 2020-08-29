#pragma once
#include "GameObject.h"
class ArtObject : public GameObject
{
private:
	ARTTYPE artType;
	std::string type;
public:
	void setArtType(ARTTYPE type);
	void setType(std::string type);
	std::string getType();
	ArtObject(ARTTYPE type, short, std::string);
	ArtObject(short width, short height, WORD bg, WORD fill, short weight, std::string type);
	~ArtObject();

	ArtObject* clone() const { return new ArtObject(*this); };
};

