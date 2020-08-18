#include "ASCII.h"

ASCII::ASCII() {
	xLength = 0;
	yLength = 0;
	art = nullptr;
}

ASCII::ASCII(ARTTYPE type) {
	xLength = 0;
	yLength = 0;
	switch (type) {
	case FIREFIGHTER:
		xLength = 5;
		yLength = 5;
	case FIRE_TRUCK:
		xLength = 5;
		yLength = 5;
	//case etc:

	}
	if (xLength > 0 && yLength > 0) {
		art = new CHAR_INFO * [xLength];
		for (unsigned int i = 0; i < xLength; i++) {
			art[i] = new CHAR_INFO[yLength];
		}

		CHAR_INFO a;
		WORD c = 0xFF;
		a.Attributes = c;
		a.Char.AsciiChar = ' ';

		for (unsigned int i = 0; i < xLength; i++) {
			for (unsigned  int j = 0; j < yLength; j++) {
				art[i][j] = a;
			}
		}

		//for every line in text
		//art[x][y] = ada;

	}
	else {
		art = nullptr;
	}
}

ASCII::~ASCII() {
	for (unsigned int i = 0; i < xLength; i++) {
		delete[] art[i];
	}
	delete[] art;
}

unsigned int ASCII::getXLength() {
	return xLength;
}

unsigned int ASCII::getYLength() {
	return yLength;
}

CHAR_INFO ASCII::getArtAtLoc(COORD cord) {
	if (art != nullptr)
		return art[cord.X][cord.Y];
}