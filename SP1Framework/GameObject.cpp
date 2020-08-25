#include "GameObject.h"

GameObject::GameObject() : relativePosition(nullptr) {
	weight = 0;
	worldPosition = { 0,0 };
	interactable = true;
	active = true;
}

GameObject::~GameObject() {
	if (relativePosition != nullptr) {
		delete relativePosition;
	}
}

bool GameObject::isCollided(GameObject& otherObj) {
	if (!(*this).isActive()) return false;
	if (!(*this).isInteractable() || !otherObj.isInteractable()) return false;
	if ((*this).getWorldPosition().X < otherObj.getWorldPosition().X + (int)otherObj.getXLength() &&
		(*this).getWorldPosition().X + (int)(*this).getXLength() > otherObj.getWorldPosition().X &&
		(*this).getWorldPosition().Y < otherObj.getWorldPosition().Y + (int)otherObj.getYLength() &&
		(*this).getWorldPosition().Y + (int)(*this).getYLength() > otherObj.getWorldPosition().Y) {
		return true;
	}
	return false;
}

bool GameObject::isInLocation(COORD coord) {
	if (!(*this).isActive()) return false;
	if ((*this).getWorldPosition().X < coord.X &&
		(*this).getWorldPosition().X + (int)(*this).getXLength() > coord.X &&
		(*this).getWorldPosition().Y < coord.Y &&
		(*this).getWorldPosition().Y + (int)(*this).getYLength() > coord.Y) {
		return true;
	}
	return false;
}

bool GameObject::isInLocation(int x, int y) {
	COORD coord = { x,y };
	if (!(*this).isActive()) return false;
	if ((*this).getWorldPosition().X < coord.X &&
		(*this).getWorldPosition().X + (int)(*this).getXLength() > coord.X &&
		(*this).getWorldPosition().Y < coord.Y &&
		(*this).getWorldPosition().Y + (int)(*this).getYLength() > coord.Y) {
		return true;
	}
	return false;
}

bool GameObject::hasRelativePos() {
	if (relativePosition != nullptr) {
		return true;
	}
	return false;
}

bool GameObject::setRelativePos(COORD cord) {
	if (relativePosition == nullptr) {
		relativePosition = new COORD(cord);
	}
	else {
		relativePosition->X = cord.X;
		relativePosition->Y = cord.Y;
	}
	return true;
}

COORD GameObject::getRelativePos() {
	return *relativePosition;
}

bool GameObject::removeRelativePos() {
	if (relativePosition != nullptr) {
		delete relativePosition;
		return true;
	}
	return false;
}

bool GameObject::isInteractable() {
	return interactable;
}

CHAR_INFO GameObject::getArtAtLoc(COORD cord) {
	return art.getArtAtLoc(cord);
}

CHAR_INFO GameObject::getArtAtLoc(int x, int y) {
	COORD a = { x,y };
	return art.getArtAtLoc(a);
}

COORD GameObject::getWorldPosition() {
	return worldPosition;
}

short GameObject::getWeight() {
	return weight;
}

unsigned int GameObject::getXLength() {
	return art.getXLength();
}

unsigned int GameObject::getYLength() {
	return art.getYLength();
}

bool GameObject::isActive() {
	return active;
}

void GameObject::setActive(bool active) {
	(*this).active = active;
}

void GameObject::setInteractable(bool interactable) {
	(*this).interactable = interactable;
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