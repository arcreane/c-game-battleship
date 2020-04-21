#pragma once
#include "bateaux.h"
#include "_case.h"
#include "joueur.h"
class plateau
{

	private:
		int numLig, numCol, totalCases, casesOccupee;
		bool ajoutCourant;

	_case **cases;

	public:
		plateau(int col, int li); //constructeur
		~plateau(void); //destructeur

		bool ajoutValide(void);
		void manuelCoordonnee(bateau& B); //saisir les coordonnées d'un bateau pour le joueur humain
		void randomCoordonnee(bateau& B); //saisir les coordonnées d'un bateau pour le joueur ordi
		int getNumColonnes(void); //nombre de colonnes
		int getNumLignes(void); //nombre de lignes
		bool plouf(int h, int o); //permet de marquer la case qui a été touché par le joueur ou l'ordi



};

