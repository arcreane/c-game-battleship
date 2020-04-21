#include "bateaux.h"
#include "_case.h"

void bateaux::setCoule(bool c) {
	this->coule = c;
}

bool bateaux::getStatus(void) {
	return !this->coule;
}

bool bateaux::estCoule(void) {
	for (int i = 0; i < this->numCases; i++) { //pour chaque case du bateau
		if (!(this->listeCases[i])->touche) //si uen case n'est pas touchée
			return false;  //on retourne false car le bateau n'est pas coulé
	}
	return true; //toutes les cases sont touchées
}

_case *bateaux::getCaseTouchee(void) {
	for (int i = 0; i < this->numCases; i++) { //pour chaque case du bateau
		if (this->listeCases[i]->touche) //si la case est touchée
			return this->listeCases[i]; // on retourne directement le pointeur de la case
	}
	return NULL; //aucune case n'est touchée
}

bool bateaux::estPlaceParJoueur(void) {
	return !this->randomPlacement;
}


int bateaux::getNum(void) {
	return this->numero;
}


int bateaux::getNumJoueur(void) {
	return this->numeroJoueur;
}

void bateaux::setLig(int ligne) {
	this->ligne = ligne;
}
void bateaux::setCol(int colonne) {
	this->colonne = colonne;
}

void batiment::setOrientation(int orientation) {
	this->orientation = orientation;
}

int batiment::getLig(void) {
	return this->ligne;
}

int batiment::getCol(void) {
	return this->colonne;
}

int batiment::getOrientation(void) {
	return this->orientation;
}

int batiment::getNumCases(void) {
	return this->numCases;
}

_case **batiment::getCases(void) {
	return this->listeCases;
}


/*Fonctions des class filles*/

char *porteAvion::getType(void) {
	return "Porte-Avion";
}

char *croiseur::getType(void) {
	return "Croiseur";
}

char *sousMarin::getType(void) {
	return "Sous-Marin";
}

char *torpilleur::getType(void) {
	return "Torpilleur";
}
