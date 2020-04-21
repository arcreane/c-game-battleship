#include "regles.h"


// regles.cpp : contient les définitions des fonction le la class regles


regles::regles(int largGrille,
	int hautGrille,
	int totalBateaux,
	int nombrePorteAvions,
	int longueurPorteAvion,
	int nombreCroiseurs,
	int longueurCroiseurs,
	int nombreContreTorpilleurs,
	int longueurContreTorpilleurs,
	int nombreSousMarins,
	int longueurSousMarins,
	int nombreTorpilleurs,
	int longueurTorpilleurs,
	bool realiste,
	bool random) {

	//constructeur

	this->nombreBateauxParJoueur = totalBateaux / 2;


	this->largGrille = largGrille;
	this->hautGrille = hautGrille;
	this->totalBateaux = totalBateaux;
	this->nombrePorteAvions = nombrePorteAvions;
	this->longueurPorteAvion = longueurPorteAvion;
	this->nombreCroiseurs = nombreCroiseurs;
	this->longueurCroiseurs = longueurCroiseurs;
	this->nombreContreTorpilleurs = nombreContreTorpilleurs;
	this->longueurContreTorpilleurs = longueurContreTorpilleurs;
	this->nombreSousMarins = nombreSousMarins;
	this->longueurSousMarins = longueurSousMarins;
	this->nombreTorpilleurs = nombreTorpilleurs;
	this->longueurTorpilleurs = longueurTorpilleurs;
	this->realiste = realiste;
	this->random = random;

	this->valides = true;


	/*tests de validation des règles*/

	if (largGrille < 5 ||
		largGrille>100 ||
		hautGrille < 5 ||
		hautGrille>100 ||
		totalBateaux < 2 ||
		nombrePorteAvions < 0 ||
		longueurPorteAvion < 0 ||
		nombreCroiseurs < 0 ||
		longueurCroiseurs < 0 ||
		nombreContreTorpilleurs < 0 ||
		longueurContreTorpilleurs < 0 ||
		nombreSousMarins < 0 ||
		longueurSousMarins < 0 ||
		nombreTorpilleurs < 0 ||
		longueurTorpilleurs < 0
		)this->valides = false;



	if ((totalBateaux != nombrePorteAvions +
		nombreCroiseurs +
		nombreContreTorpilleurs +
		nombreSousMarins +
		nombreTorpilleurs) ||
		(totalBateaux % 2 != 0) ||
		(totalBateaux > (largGrille*hautGrille * 25 / 100))
		)this->valides = false;

	if ((largGrille*hautGrille) < ((nombrePorteAvions*longueurPorteAvion) +
		(nombreCroiseurs*longueurCroiseurs) +
		(nombreContreTorpilleurs*longueurContreTorpilleurs) +
		(nombreSousMarins*longueurSousMarins) +
		(nombreTorpilleurs*longueurTorpilleurs))
		)this->valides = false;

}

bool regles::sontValides(void) {

	return this->valides;

}

int regles::getNombrebateauxParJoueur(void) {

	return this->nombreBateauxParJoueur;
}
