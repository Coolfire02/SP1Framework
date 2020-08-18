#include "GameObject.h"

GameObject::GameObject(int x, int y) {
	objectCords_ptr = new CHAR_INFO* [x];
	for (int i = 0; i < x; i++) {
		objectCords_ptr[i] = new CHAR_INFO [y];
	}
	objXLength = x;
	objYLength = y;
	//ascii art loading
	
}

GameObject::~GameObject() {
	for (int i = 0; i < objXLength; i++) {
		delete[] objectCords_ptr[i];
	}
	delete[] objectCords_ptr;
}