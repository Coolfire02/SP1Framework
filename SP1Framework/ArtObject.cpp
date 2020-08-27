#include "ArtObject.h"

ArtObject::ArtObject(ARTTYPE artType, short weight) {
	(*this).artType = artType;
	art.setArt(artType);
	(*this).type = "ArtObject";
}

ArtObject::~ArtObject() {

}

std::string ArtObject::getType() {
	return "ArtObject";
}

void ArtObject::setType(std::string type) {
	(*this).type = type;
}

void ArtObject::setArtType(ARTTYPE artType) {
	(*this).artType = artType;
	art.setArt(artType);
}