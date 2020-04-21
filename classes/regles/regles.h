#pragma once
class regles {

	friend class jeu; //seul la class jeu doit acceder à cette class


private:


	int largGrille,
		hautGrille,

		totalBateaux,

		nombrePorteAvions,
		longueurPorteAvion,

		nombreCroiseurs,
		longueurCroiseurs,

		nombreContreTorpilleurs,
		longueurContreTorpilleurs,

		nombreSousMarins,
		longueurSousMarins,

		nombreTorpilleurs,
		longueurTorpilleurs;



	bool realiste, random, valides;
	int nombreBateauxParJoueur;


public:


	regles(int largGrille,
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
		bool random);  //prototype du constructeur



	bool sontValides(void); //vérifie si les règles sont valides
	int getNombrebateauxParJoueur(void); //retourne le nombre de bateaux par joueur


};

