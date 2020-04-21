// battleship1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include "jeu.h"
#include <iostream>



//////////////////////////////////////////////////////
//                                                                         
// Bataille_Navale.cpp : Point d'entrée du programme 
//                                                                            
//////////////////////////////////////////////////////


int main(int argc, char* argv[])
{

	cout << "          *********************************************************\n"
		<< "          *                                                       *\n"
		<< "          *                                                       *\n"
		<< "          *       BATAILLE NAVALE OF THE DEATH THAT KILL!!!       *\n"
		<< "          *                                                       *\n"
		<< "          *                                                       *\n"
		<< "          *********************************************************\n\n\n\n";

	int arret = 0;

	char *nomJoueurHumain, *nomJoueurIA;

	nomJoueurHumain = saisieChaine("Entrez Votre nom: ", 50);  //saisie du nom du joueur humain

	cout << "\n";


	nomJoueurIA = saisieChaine("Entrez un nom pour l'IA: ", 50);  //saisie du nom du joueur IA

	while (!arret) { //Tant que le joueur souhaite jouer, on recrée une partie

		cout << "\n\n";

		jeu *jeu = new jeu(nomJoueurHumain, nomJoueurIA);  //création du jeu

		jeu->demarrer();  //démarrage du jeu

		jeu->arreter();   //arret du jeu (appel des destructeurs...)

		arret = saisieEntier("Souhaitez vous refaire une partie? [oui:0,non:1] ", 0, 1);

	}

	free(nomJoueurHumain);
	free(nomJoueurIA);

	return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
