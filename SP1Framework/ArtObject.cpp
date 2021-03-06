#include "ArtObject.h"

ArtObject::ArtObject(ARTTYPE artType, short weight, std::string type) : type(type) {
	(*this).weight = weight;
	(*this).artType = artType;
	art.setArt(artType);
}

ArtObject::ArtObject(short width, short height, WORD bg, WORD border, short weight, std::string type) : type(type) {
	(*this).weight = weight;
	artType = DEFAULT_ART;
	art.setArt(width, height, bg, border);
}

ArtObject::~ArtObject() {

}

std::string ArtObject::getType() {
	return type;
}

void ArtObject::setType(std::string type) {
	(*this).type = type;
}

void ArtObject::setArtType(ARTTYPE artType) {
	(*this).artType = artType;
	art.setArt(artType);
}