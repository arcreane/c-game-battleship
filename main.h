#pragma once
#include "plateau.h"
#include "_case.h"
#include "joueur.h"
#include "bateaux.h"
#include "regles.h"

////////////////////////////////////
//                                                                         
// joueur.h : d�clare la class jeu 
//                                                                            
////////////////////////////////////


class jeu {


private:

	bool termine;

	joueur **joueurs; // liste des joueurs

	bateaux **listeBateauxJoueur1, **listeBateauxJoueur2; //listes des bateauxs pour chaque joueur

	regles *regle;

	bool iaRealiste, debug;

	bool initialiser(regles *r); //lance la cr�ation des flottes par rapport aux r�gles en param�tre
	void saisirRegles(void); //permet de saisir les r�gles
	void creerFlotte(regles *r); //cr�e la la flotte de navires
	bool verifVictoire(int numeroJoueur); //v�rifie si le joueur dont le numero est pass� en param�tre a gagn�
	bool updateplateau(int x, int y, bool IA); // met � jour la plateau aux coordonn�es x et y
	bool verifAppartenance(int x, int y, int numeroJoueur);//v�rifie si la case en x et y appartient � un joueur
	bool calcTirIA(int &x, int &y, int X, int Y, int orientation);//calcul le prochain tir de l'iA (IA r�aliste)
	bool verifIAOrientation(plateau *g, int orgX, int orgY, int orientation);//v�rifie si l'orientation de tir de l'IA est valide


public:
	plateau *plateauH, *plateauIA;

	jeu(char *nomJoueurHumain, char *nomJoueurIA); //prototype du constructeur
	~jeu(void); //prototype du d�structeur

	void creerRegles(); //d�clanche la saisie des r�gles en boucle tant que celles-ci ne sont pas correctes
	void demarrer(void); //d�marre la boucle de jeu
	void arreter(void); //lib�re toutes les ressources utilis�es par le jeu

};