#include "jeu.h"

jeu::jeu(char *nomJoueurHumain, char *nomJoueurIA) {

	/*constructeur*/

	joueurs = new joueur*[2];
	joueurs[0] = new joueur(nomJoueurHumain);
	joueurs[1] = new joueur(nomJoueurIA);
	this->regle = NULL;
	this->creerRegles();
	plateauH = new plateau(this->regle->largGrille, this->regle->hautGrille, false);
	plateauIA = new plateau(this->regle->largGrille, this->regle->hautGrille, this->regle->debug);
	this->iaRealiste = this->regle->realiste;
	this->regle = this->regle;
	this->initialiser(this->regle);


}


jeu::~jeu(void) {

	/*destructeur*/

	delete joueurs[0];
	delete joueurs[1];
	delete[] joueurs;

	for (int i = 0; i < this->regle->getNombrebateauxParJoueur(); i++) {
		delete listeBateauxJoueur1[i];
		delete listeBateauxJoueur2[i];
	}
	delete[] listeBateauxJoueur1;
	delete[] listeBateauxJoueur2;

	delete plateauH;
	delete plateauIA;

}

void jeu::creerRegles() {


	do {

		if (this->regle) delete this->regle;


		this->saisirRegles();

	} while (!this->regle->valides);


}


void jeu::saisirRegles(void) {

	int largGrille = 0,
		hautGrille = 0,

		totalBateaux = 0,
		reste = 0,

		nombrePorteAvions = 0,
		longueurPorteAvion = 0,

		nombreCroiseurs = 0,
		longueurCroiseurs = 0,

		nombreContreTorpilleurs = 0,
		longueurContreTorpilleurs = 0,

		nombreSousMarins = 0,
		longueurSousMarins = 0,

		nombreTorpilleurs = 0,
		longueurTorpilleurs = 0;

	bool realiste = false, random = false, debug = false;
	int rea = 0, rando = 0, deb = 0;

	largGrille = saisieEntier("Entrez la largeur de la grille: ", 5, 100);

	hautGrille = saisieEntier("Entrez la hauteur de la grille: ", 5, 100);

	totalBateaux = saisieEntier("\nEntrez le nombre total de bateaux desires par joueur: ", 1, 20);

	totalBateaux *= 2;

	reste = totalBateaux;

	nombrePorteAvions = saisieEntier("\nEntrez le nombre total de Porte-Avions desires: ", 0, 20);

	nombrePorteAvions *= 2;
	reste -= nombrePorteAvions;
	if (nombrePorteAvions > 0) {

		longueurPorteAvion = saisieEntier("\nEntrez le nombre de cases d'un Porte-Avions: ", 1, 20);

		cout << "\nReste " << reste << " batiments disponibles!\n";
	}


	if (reste > 0) {

		nombreCroiseurs = saisieEntier("\nEntrez le nombre total de Croiseurs desires: ", 0, 20);

		nombreCroiseurs *= 2;
		reste -= nombreCroiseurs;
		if (nombreCroiseurs > 0) {

			longueurCroiseurs = saisieEntier("\nEntrez le nombre de cases d'un Croiseur: ", 1, 20);

			cout << "\nReste " << reste << " batiments disponibles!\n";
		}
	}


	if (reste > 0) {

		nombreContreTorpilleurs = saisieEntier("\nEntrez le nombre total de Contre-Torpilleurs desires: ", 0, 20);


		nombreContreTorpilleurs *= 2;
		reste -= nombreContreTorpilleurs;
		if (nombreContreTorpilleurs > 0) {

			longueurContreTorpilleurs = saisieEntier("\nEntrez le nombre de cases d'un Contre-Torpilleur: ", 1, 20);

			cout << "\nReste " << reste << " batiments disponibles!\n";
		}
	}

	if (reste > 0) {

		nombreSousMarins = saisieEntier("\nEntrez le nombre total de Sous-Marins desires: ", 0, 20);

		nombreSousMarins *= 2;
		reste -= nombreSousMarins;
		if (nombreSousMarins > 0) {

			longueurSousMarins = saisieEntier("\nEntrez le nombre de cases d'un Sous-Marin: ", 1, 20);

			cout << "\nReste " << reste << " batiments disponibles!\n";
		}
	}


	if (reste > 0) {

		nombreTorpilleurs = saisieEntier("\nEntrez le nombre total de Torpilleurs desires: ", 0, 20);

		nombreTorpilleurs *= 2;
		reste -= nombreTorpilleurs;
		if (nombreTorpilleurs > 0) {

			longueurTorpilleurs = saisieEntier("\nEntrez le nombre de cases d'un Torpilleur: ", 1, 20);

			cout << "\nReste " << reste << " batiments disponibles!\n\n";
		}
	}

	if (reste > 0) {

		totalBateaux -= reste;
		cout << "Le nouveau nombre total de bateaux est de " << totalBateaux << "!\n\n";

	}

	rea = saisieEntier("Souhaitez vous une IA realiste? [1:oui;0:non]: ", 0, 1);

	deb = saisieEntier("\nSouhaitez vous executer le jeu en mode debug? [1:oui;0:non]: ", 0, 1);

	rando = saisieEntier("\nSouhaitez vous que votre flotte soit generee aleatoirement? [1:oui;0:non]: ", 0, 1);
	cout << "\n\n";

	rea == 1 ? realiste = true : realiste = false;

	deb == 1 ? debug = true : debug = false;

	rando == 1 ? random = true : random = false;



	this->regle = new regles(largGrille,
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
		longueurTorpilleurs,
		realiste,
		debug,
		random);


}

bool jeu::initialiser(regles *r) {

	if (!r->valides) return false;

	creerFlotte(r);

	return true;
}



void jeu::creerFlotte(regles *r) {

	int compteur = 0;

	this->listeBateauxJoueur1 = new bateaux*[r->totalBateaux / 2];
	this->listeBateauxJoueur2 = new bateaux*[r->totalBateaux / 2];

	srand(time(NULL));

	for (int i = 0; i < r->nombrePorteAvions / 2; i++) {

		if (r->random) {
			this->listeBateauxJoueur1[i] = new porteAvion(r->longueurPorteAvion, i + 1, 1, true);

			do {

				this->plateauH->randomCoordonnee(*this->listeBateauxJoueur1[i]);
				*this->plateauH += *this->listeBateauxJoueur1[i];


			} while (!this->plateauH->ajoutEstValide());

		}
		else {
			this->listeBateauxJoueur1[i] = new porteAvion(r->longueurPorteAvion, i + 1, 1, false);

			do {

				this->plateauH->manuelCoordonnee(*this->listeBateauxJoueur1[i]);
				*this->plateauH += *this->listeBateauxJoueur1[i];


			} while (!this->plateauH->ajoutEstValide());


		}

		this->listeBateauxJoueur2[i] = new porteAvion(r->longueurPorteAvion, i + 1, 2, true);


		do {

			this->plateauIA->randomCoordonnee(*this->listeBateauxJoueur2[i]);
			*this->plateauIA += *this->listeBateauxJoueur2[i];


		} while (!this->plateauIA->ajoutEstValide());


		compteur++;

	}

	for (int i = 0; i < r->nombreCroiseurs / 2; i++) {


		if (r->random) {

			this->listeBateauxJoueur2[compteur] = new croiseur(r->longueurCroiseurs, i + 1, 1, true);

			do {

				this->plateauH->randomCoordonnee(*this->listeBateauxJoueur2[compteur]);
				*this->plateauH += *this->listeBateauxJoueur2[compteur];


			} while (!this->plateauH->ajoutEstValide());

		}
		else {

			this->listeBateauxJoueur1[compteur] = new croiseur(r->longueurCroiseurs, i + 1, 1, false);

			do {

				this->plateauH->manuelCoordonnee(*this->listeBateauxJoueur1[compteur]);
				*this->plateauH += *this->listeBateauxJoueur1[compteur];


			} while (!this->plateauH->ajoutEstValide());


		}

		this->listeBateauxJoueur2[compteur] = new croiseur(r->longueurCroiseurs, i + 1, 2, true);

		do {

			this->plateauIA->randomCoordonnee(*this->listeBateauxJoueur2[compteur]);
			*this->plateauIA += *this->listeBateauxJoueur2[compteur];


		} while (!this->plateauIA->ajoutEstValide());

		compteur++;


	}



	for (int i = 0; i < r->nombreContreTorpilleurs / 2; i++) {

		if (r->random) {

			this->listeBateauxJoueur1[compteur] = new contreTorpilleur(r->longueurContreTorpilleurs, i + 1, 1, true);

			do {

				this->plateauH->randomCoordonnee(*this->listeBateauxJoueur1[compteur]);
				*this->plateauH += *this->listeBateauxJoueur1[compteur];


			} while (!this->plateauH->ajoutEstValide());

		}
		else {

			this->listeBateauxJoueur1[compteur] = new contreTorpilleur(r->longueurContreTorpilleurs, i + 1, 1, false);

			do {

				this->plateauH->manuelCoordonnee(*this->listeBateauxJoueur1[compteur]);
				*this->plateauH += *this->listeBateauxJoueur1[compteur];


			} while (!this->plateauH->ajoutEstValide());


		}
		this->listeBateauxJoueur2[compteur] = new contreTorpilleur(r->longueurContreTorpilleurs, i + 1, 2, true);
		do {

			this->plateauIA->randomCoordonnee(*this->listeBateauxJoueur2[compteur]);
			*this->plateauIA += *this->listeBateauxJoueur2[compteur];


		} while (!this->plateauIA->ajoutEstValide());
		compteur++;


	}

	for (int i = 0; i < r->nombreSousMarins / 2; i++) {

		if (r->random) {

			this->listeBateauxJoueur1[compteur] = new sousMarin(r->longueurSousMarins, i + 1, 1, true);

			do {

				this->plateauH->randomCoordonnee(*this->listeBateauxJoueur1[compteur]);
				*this->plateauH += *this->listeBateauxJoueur1[compteur];


			} while (!this->plateauH->ajoutEstValide());

		}
		else {

			this->listeBateauxJoueur1[compteur] = new sousMarin(r->longueurSousMarins, i + 1, 1, false);

			do {

				this->plateauH->manuelCoordonnee(*this->listeBateauxJoueur1[compteur]);
				*this->plateauH += *this->listeBateauxJoueur1[compteur];


			} while (!this->plateauH->ajoutEstValide());


		}
		this->listeBateauxJoueur2[compteur] = new sousMarin(r->longueurSousMarins, i + 1, 2, true);
		do {

			this->plateauIA->randomCoordonnee(*this->listeBateauxJoueur2[compteur]);
			*this->plateauIA += *this->listeBateauxJoueur2[compteur];


		} while (!this->plateauIA->ajoutEstValide());
		compteur++;


	}




	for (int i = 0; i < r->nombreTorpilleurs / 2; i++) {

		if (r->random) {

			this->listeBateauxJoueur1[compteur] = new torpilleur(r->longueurTorpilleurs, i + 1, 1, true);

			do {

				this->plateauH->randomCoordonnee(*this->listeBateauxJoueur1[compteur]);
				*this->plateauH += *this->listeBateauxJoueur1[compteur];


			} while (!this->plateauH->ajoutEstValide());

		}
		else {

			this->listeBateauxJoueur1[compteur] = new torpilleur(r->longueurTorpilleurs, i + 1, 1, false);

			do {

				this->plateauH->manuelCoordonnee(*this->listeBateauxJoueur1[compteur]);
				*this->plateauH += *this->listeBateauxJoueur1[compteur];


			} while (!this->plateauH->ajoutEstValide());


		}

		this->listeBateauxJoueur2[compteur] = new torpilleur(r->longueurTorpilleurs, i + 1, 2, true);

		do {

			this->plateauIA->randomCoordonnee(*this->listeBateauxJoueur2[compteur]);
			*this->plateauIA += *this->listeBateauxJoueur2[compteur];


		} while (!this->plateauIA->ajoutEstValide());
		compteur++;
	}

}



void jeu::arreter(void) {

	delete this;

}



bool jeu::updateGrille(int x, int y, bool IA) {


	if (IA)
		return this->plateauIA->tireSurCase(x, y);
	else
		return this->plateauH->tireSurCase(x, y);


}

bool jeu::verifAppartenance(int x, int y, int numeroJoueur) {



	if (numeroJoueur == 1) {

		for (int i = 0; i < this->regle->getNombrebateauxParJoueur(); i++) { //pour chaque bateau

			for (int j = 0; j < this->listeBateauxJoueur1[i]->getNumCases(); j++) { //et pour chaque case de chaque bateau

				if (this->listeBateauxJoueur1[i]->getCases()[j] == this->plateauH->getCase(x, y)) //si les cases correspondent
					return true;// la case x y appartient au bateau i

			}
		}
	}

	if (numeroJoueur == 2) {

		for (int i = 0; i < this->regle->getNombrebateauxParJoueur(); i++) {

			for (int j = 0; j < this->listeBateauxJoueur2[i]->getNumCases(); j++) {

				if (this->listeBateauxJoueur2[i]->getCases()[j] == this->plateauIA->getCase(x, y))
					return true;

			}
		}
	}


	return false;
}


bool jeu::verifVictoire(int numeroJoueur) {

	if (numeroJoueur == 1) {

		for (int i = 0; i < this->regle->getNombrebateauxParJoueur(); i++) { //pour chaque bateau du joueur

			if (!this->listeBateauxJoueur2[i]->estCoule()) //si un de ces bateau n'est pas coulé
				return false; //pas de victoire

		}

	}

	if (numeroJoueur == 2) {

		for (int i = 0; i < this->regle->getNombrebateauxParJoueur(); i++) {

			if (!this->listeBateauxJoueur1[i]->estCoule())
				return false;

		}

	}

	return true;

}

bool jeu::calcTirIA(int &x, int &y, int X, int Y, int orientation) {

	bool retour = true;

	switch (orientation) {

		/*calcul des coordonnées du prochain tir en fonction de l'orientation.
		  puis vérification de la validité du tir qui suit en second*/

	case OUEST:
		if ((!this->plateauH->getCase(Y, X - 1)->occupee) || (X - 2 < 0))
			retour = false;
		else
			if (X - 2 >= 0)
				if (this->plateauH->getCase(Y, X - 2)->touche)
					retour = false;


		x = X - 1;
		y = Y;
		break;

	case NORD:
		if ((!this->plateauH->getCase(Y - 1, X)->occupee) || (Y - 2 < 0))
			retour = false;
		else
			if (Y - 2 >= 0)
				if (this->plateauH->getCase(Y - 2, X)->touche)
					retour = false;


		x = X;
		y = Y - 1;
		break;



	case EST:
		if ((!this->plateauH->getCase(Y, X + 1)->occupee) || (X + 2 > this->plateauH->getNumCol() - 1))
			retour = false;
		else
			if (X + 2 >= 0)
				if (this->plateauH->getCase(Y, X + 2)->touche)
					retour = false;


		x = X + 1;
		y = Y;
		break;

	case SUD:
		if ((!this->plateauH->getCase(Y + 1, X)->occupee) || (Y + 2 > this->plateauH->getNumLig() - 1))
			retour = false;
		else
			if (Y + 2 >= 0)
				if (this->plateauH->getCase(Y + 2, X)->touche)
					retour = false;

		x = X;
		y = Y + 1;

		break;

	}

	return retour; //renvoi false si la prévision à 2 coups n'est pas valide
}

bool jeu::verifIAOrientation(grille *g, int orgX, int orgY, int orientation) {

	bool retour;

	switch (orientation) {

	case OUEST: g->getCase(orgY, orgX - 1)->touche ? retour = false : retour = true; break;
	case NORD: g->getCase(orgY - 1, orgX)->touche ? retour = false : retour = true; break;
	case EST: g->getCase(orgY, orgX + 1)->touche ? retour = false : retour = true; break;
	case SUD: g->getCase(orgY + 1, orgX)->touche ? retour = false : retour = true; break;

	default: retour = false;

	}

	return retour;
}


void jeu::demarrer(void) {

	/*démarrage de la boucle de jeu*/

	int x, y, prevX, prevY, prevOrientation = 0, orgX, orgY, orientation = 0;

	bool continues = false, iaTouche = false, essaiOppose = true;

	this->termine = false;


	while (!termine) {    //tant que la partie n'est pas terminée

		/*Partie humaine du jeu*/

		cout << "Grille du joueur Humain: " << this->joueurs[0]->getNom() << "\n\n"
			<< "Nombre de bateaux coules: " << this->joueurs[0]->getNumBateauxCoule()
			<< "\n\n";

		cout << *this->plateauH << "\n\n";

		cout << "Grille du joueur IA: " << this->joueurs[1]->getNom();

		this->debug ? cout << " (debug mode)\n\n" : cout << "\n\n"
			<< "Nombre de bateaux coules: " << this->joueurs[1]->getNumBateauxCoule()
			<< "\n\n",

			cout << *this->plateauIA << "\n\n";

		cout << "Instructions de tir: \n";

		x = saisieEntier("Entrez le numero de colonne: ", 0, this->plateauIA->getNumCol() - 1);

		y = saisieEntier("Entrez le numero de ligne: ", 0, this->plateauIA->getNumLig() - 1);

		if ((x < 0) || (x > this->plateauIA->getNumCol() - 1) || (y < 0) || (y > this->plateauIA->getNumLig() - 1))
			continue;

		if (this->plateauIA->getCase(y, x)->touche) {

			cout << "\n!!!!Vous ne pouvez pas tirer sur cette case!!!!\n";
			continue;
		}

		this->updateGrille(y, x, true);
		if (verifAppartenance(y, x, 2))
			cout << "\n\n!**Bateaux Ennemi touche**!\n\n";


		for (int i = 0; i < this->regle->getNombrebateauxParJoueur(); i++) {

			if (this->listeBateauxJoueur2[i]->estCoule() && this->listeBateauxJoueur2[i]->getStatus()) {

				this->listeBateauxJoueur2[i]->setCoule(true);
				this->joueurs[1]->decrementNumBateaux();
				cout << "\n\n!***!Un " << this->listeBateauxJoueur1[i]->getType() << " de l'ennemi a ete coule!***!\n\n";
				break;
			}
		}


		if (this->verifVictoire(1)) {

			cout << *this->plateauIA << "\n";

			cout << "\n\n****Le joueur 1 a gagne!****\n\n";
			termine = true;

		}

		/*Partie IA du jeu*/

		//IA réaliste

		if (iaRealiste && !termine) {

			if (!iaTouche) {

				while (!continues) {

					y = RAND_NUM(0, this->plateauH->getNumCol() - 1);
					x = RAND_NUM(0, this->plateauH->getNumLig() - 1);

					if (!this->plateauH->getCase(y, x)->touche)
						continues = true;
				}
				continues = false;

			}
			else {

				if (!calcTirIA(x, y, prevX, prevY, orientation)) {

					for (int i = 1; i < 5; i++) {
						if ((i == OUEST && orgX == 0) ||
							(i == NORD && orgY == 0) ||
							(i == EST && orgX == this->plateauH->getNumCol() - 1) ||
							(i == SUD && orgY == this->plateauH->getNumLig() - 1))
							continue;
						continues |= verifIAOrientation(this->plateauH, orgX, orgY, i);
					}
					continues = !continues;

					if (orientation != 0 && essaiOppose && !continues) {

						switch (orientation) {

						case NORD: orientation = SUD; break;
						case SUD: orientation = NORD; break;
						case OUEST: orientation = EST; break;
						case EST: orientation = OUEST; break;

						}

					}

					while (!continues) {

						if (!essaiOppose)
							orientation = RAND_NUM(1, 4);
						else
							essaiOppose = false;

						if ((orientation == OUEST && orgX == 0) ||
							(orientation == NORD && orgY == 0) ||
							(orientation == EST && orgX == this->plateauH->getNumCol() - 1) ||
							(orientation == SUD && orgY == this->plateauH->getNumLig() - 1) ||
							(orientation == prevOrientation))
							continue;
						else {
							prevX = orgX;
							prevY = orgY;

							continues = verifIAOrientation(this->plateauH, orgX, orgY, orientation);
						}
					}
					continues = false;
					prevOrientation = orientation;

				}
				else {

					prevX = x;
					prevY = y;
					essaiOppose = true;

				}
			}



			cout << "\nL'IA tire en (" << x << " , " << y << ") \n";

			this->updateGrille(y, x, false);
			if (verifAppartenance(y, x, 1)) {
				cout << "\n!**Un de vos bateaux est touche**!\n";

				if (!iaTouche) {
					iaTouche = true;
					orgX = x;
					orgY = y;
					prevX = x;
					prevY = y;

					while (!continues) {
						orientation = RAND_NUM(1, 4);
						if ((orientation == OUEST && x == 0) ||
							(orientation == NORD && y == 0) ||
							(orientation == EST && x == this->plateauH->getNumCol() - 1) ||
							(orientation == SUD && y == this->plateauH->getNumLig() - 1))
							continue;
						else {

							continues = verifIAOrientation(this->plateauH, orgX, orgY, orientation);

						}
					}
					continues = false;
					prevOrientation = orientation;
				}

				for (int i = 0; i < this->regle->getNombrebateauxParJoueur(); i++) {

					if (this->listeBateauxJoueur1[i]->estCoule() && this->listeBateauxJoueur1[i]->getStatus()) {

						this->listeBateauxJoueur1[i]->setCoule(true);
						this->joueurs[0]->decrementNumBateaux();
						iaTouche = false;
						orientation = 0;
						prevOrientation = 0;
						cout << "\n\n!***!Un de vos " << this->listeBateauxJoueur1[i]->getType() << " a ete coule!***!\n\n";

						for (int i = 0; i < this->regle->getNombrebateauxParJoueur(); i++) {

							if (this->listeBateauxJoueur1[i]->estPartiellementTouche()) {

								_case *temp = this->listeBateauxJoueur1[i]->getCaseTouchee();

								iaTouche = true;
								orgX = temp->X;
								orgY = temp->Y;
								prevX = orgX;
								prevY = orgY;

								while (!continues) {
									orientation = RAND_NUM(1, 4);
									if ((orientation == OUEST && x == 0) ||
										(orientation == NORD && y == 0) ||
										(orientation == EST && x == this->plateauH->getNumCol() - 1) ||
										(orientation == SUD && y == this->plateauH->getNumLig() - 1))
										continue;
									else {

										continues = verifIAOrientation(this->plateauH, orgX, orgY, orientation);
									}
								}
								continues = false;
							}

						}
						break;
					}

				}

			}

			if (this->verifVictoire(2)) {

				cout << *this->plateauH << "\n";

				cout << "\n\n****Le joueur 2 a gagne!****\n\n";
				termine = true;

			}

		}
		else {  //IA de base

			if (!termine) {

				while (!continues) {

					y = RAND_NUM(0, this->plateauH->getNumCol() - 1);
					x = RAND_NUM(0, this->plateauH->getNumLig() - 1);

					if (!this->plateauH->getCase(y, x)->touche)
						continues = true;
				}
				continues = false;

				cout << "\nL'IA tire en (" << x << " , " << y << ") \n";

				this->updateGrille(y, x, false);

				if (verifAppartenance(y, x, 1))
					cout << "\n\nUn de vos bateaux est touche!\n\n";

				for (int i = 0; i < this->regle->getNombrebateauxParJoueur(); i++) {

					if (this->listeBateauxJoueur1[i]->estCoule() && this->listeBateauxJoueur1[i]->getStatus()) {

						this->listeBateauxJoueur1[i]->setCoule(true);
						this->joueurs[0]->decrementNumBateaux();
						cout << "\n\n!***!Un de vos " << this->listeBateauxJoueur1[i]->getType() << " a ete coule!***!\n\n";
					}
				}

				if (this->verifVictoire(2)) {

					cout << *this->plateauH << "\n";

					cout << "\n\nLe joueur 2 a gagne!\n\n";
					termine = true;

				}

			}

		}

	}

}