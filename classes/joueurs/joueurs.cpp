#include "joueur.h"

joueur::joueur(char *nom){

	/*constructeur*/

	strcpy(this->nom,nom);
	this->nombreBateauxCoule = 0;

}

char *joueur::getNom(void){

	return this->nom;

}

int joueur::getNumBateauxCoule(void){

	return this->nombreBateauxCoule;

}

void joueur::decrementNumBateaux(void){
    
    this->nombreBateauxCoule++;
