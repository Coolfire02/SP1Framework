#include "GameObject.h"

GameObject::GameObject() {
	worldPosition = { 0,0 };
}

GameObject::~GameObject() {
}

bool GameObject::isCollided(GameObject& otherObj) {
	if ((*this).getWorldPosition().X < otherObj.getWorldPosition().X + (int)otherObj.getXLength() &&
		(*this).getWorldPosition().X + (int)(*this).getXLength() > otherObj.getWorldPosition().X &&
		(*this).getWorldPosition().Y < otherObj.getWorldPosition().Y + (int)otherObj.getYLength() &&
		(*this).getWorldPosition().Y + (int)(*this).getYLength() > otherObj.getWorldPosition().Y) {
		return true;
	}
	return false;
}

CHAR_INFO GameObject::getArtAtLoc(COORD cord) {
	return art.getArtAtLoc(cord);
}

COORD GameObject::getWorldPosition() {
	return worldPosition;
}

unsigned int GameObject::getXLength() {
	return art.getXLength();
}

unsigned int GameObject::getYLength() {
	return art.getYLength();
}

bool GameObject::setWorldPosition(unsigned int x, unsigned int y) {
	COORD a = { (short)x, (short)y };
	(*this).worldPosition = a;
	return true;
}

bool GameObject::setWorldPosition(COORD a) {
	(*this).worldPosition = a;
	return true;
}