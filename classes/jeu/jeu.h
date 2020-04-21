#pragma once
#include "plateau.h"
#include "_case.h"
#include "joueur.h"
#include "bateaux.h"
#include "regles.h"

////////////////////////////////////
//                                                                         
// joueur.h : déclare la class jeu 
//                                                                            
////////////////////////////////////


class jeu {


private:

	bool termine;

	joueur **joueurs; // liste des joueurs

	bateaux **listeBateauxJoueur1, **listeBateauxJoueur2; //listes des bateauxs pour chaque joueur

	regles *regle;

	bool iaRealiste, debug;

	bool initialiser(regles *r); //lance la création des flottes par rapport aux règles en paramètre
	void saisirRegles(void); //permet de saisir les règles
	void creerFlotte(regles *r); //crée la la flotte de navires
	bool verifVictoire(int numeroJoueur); //vérifie si le joueur dont le numero est passé en paramètre a gagné
	bool updateplateau(int x, int y, bool IA); // met à jour la plateau aux coordonnées x et y
	bool verifAppartenance(int x, int y, int numeroJoueur);//vérifie si la case en x et y appartient à un joueur
	bool calcTirIA(int &x, int &y, int X, int Y, int orientation);//calcul le prochain tir de l'iA (IA réaliste)
	bool verifIAOrientation(plateau *g, int orgX, int orgY, int orientation);//vérifie si l'orientation de tir de l'IA est valide


public:
	plateau *plateauH, *plateauIA;

	jeu(char *nomJoueurHumain, char *nomJoueurIA); //prototype du constructeur
	~jeu(void); //prototype du déstructeur

	void creerRegles(); //déclanche la saisie des régles en boucle tant que celles-ci ne sont pas correctes
	void demarrer(void); //démarre la boucle de jeu
	void arreter(void); //libère toutes les ressources utilisées par le jeu

};
