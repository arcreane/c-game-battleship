#include "plateau.h"
#include "_case.h"
#include "bateaux.h"
#include "joueur.h"

plateau::plateau(int col, int lig)
{
	this->casesOccupee = 0;
	this->numLig = lig;
	this->numCol = col;
	this->totalCases = col * lig;
	this->ajoutCourant = true;

	cases = new _case*[lig]; //création des cases de la grille

	for (int i = 0; i < lig; i++) {
		cases[i] = new _case[col];

		for (int j = 0; j < col; j++) {
			cases[i][j].setCoordonnees(i, j);
		}
	}

	bool plateau::ajoutValide(void){
		return this->ajoutCourant;
	}

	bool plateau::plouf(int h, int o) {
		this->cases[h][o].touche = true;
		if (this->cases[h][o].occupee)
			return true;
		else
			return false;
	}

	_case *grille::getCase(int h, int o) {
		return &(this->cases[h][o]);
	}

	int plateau::getNumColonnes(void) {
		return this->numColonnes;
	}

	int plateau::getNumLignes(void) {
		return this->numLignes;
	}
	


	void plateau::manuelCoordonnee(bateau& B) {
		int ligne, colonne, orientation;

		cout << "Entrez la colonne sur laquelle vous ajoutez le "
			<< B.getType()
			<< " numero: "
			<< B.getNumero()
			<< "\n";
		col = saisieEntier("", 0, this->numCol - 1);
		B.setCol(col);

		cout << "Entrez l'orientation du bateau(1: nord, 2: sud, 3: est, 4: ouest): ";
		
		orientation = saisieEntier("", 1, 4);
		B.setOrientation(orientation);
	}

	void plateau::randomCoordonnee(bateau& B) {
		this->ajoutCourant = true;
		B.setLig(RAND_NUM(0, this->numLig - 1));
		B.setCol(RAND_NUM(0, this->numCol - 1));
		B.setOrientation(RAND_NUM(1, 4));
	}

	plateau& plateau::operator+=(bateau& B) {
		int compteur = 0, index = 0;

		switch (B.getOrientation())
		{
		case nord:
		{
			if (B.getLig() - B.getNumCases() < 0 || B.getLig() > this->numLig - 1)
			{

				if (B.estPlaceParJoueur())
					cout << "Mauvaises coordonnees: Depassement des bordures\n\n";
				this->ajoutCourant = false;
				break;
			}

			for (int i = B.getLig(); i > B.getLig() - B.getNumCases(); i--) {

				if (this->cases[i][B.getCol()].occupee == true) {
					if (B.estPlaceParJoueur())
						cout << "Mauvaises coordonnees: Chevauchement\n\n";
					this->ajoutCourant = false;
					break;

				}
			}
			if (!this->ajoutCourant)
				break;


			for (int i = B.getLig(); i > B.getLig() - B.getNumCases(); i--) {
				B.getCases()[index] = &(this->cases[i][B.getCol()]);
				this->cases[i][B.getCol()].occupee = true;
				this->cases[i][B.getCol()].numJoueur = B.getNumJoueur();
				index++;
			}
			this->casesOccupee += B.getNumCases();
			this->ajoutCourant = true;

			break;
		}

		case sud: {

			if (B.getLig() + B.getNumCases() > this->numLig - 1 || B.getLig() < 0) {
				if (B.estPlaceParJoueur())
					cout << "Mauvaises coordonnees: Depassement des bordures\n\n";
				this->ajoutCourant = false;
				break;
			}

			for (int i = B.getLigne(); i < B.getLigne() + B.getNumCases(); i++) {

				if (this->cases[i][B.getColonne()].occupee == true) {
					if (B.estPlaceParJoueur())
						cout << "Mauvaises coordonnees: Chevauchement\n\n";
					this->ajoutCourant = false;
					break;

				}
			}
			if (!this->ajoutCourant)break;

			for (int i = B.getLigne(); i < B.getLigne() + B.getNumCases(); i++) {
				B.getCases()[index] = &(this->cases[i][B.getColonne()]);
				this->cases[i][B.getColonne()].occupee = true;
				this->cases[i][B.getColonne()].numeroJoueur = B.getNumeroJoueur();
				index++;
			}
			this->casesOccupee += B.getNumCases();
			this->ajoutCourant = true;

			break;
		}

		case est: {

			if (B.getCol() < 0 || B.getCol() + B.getNumCases() > this->numCol) {
				if (B.estPlaceParJoueur())
					cout << "Mauvaises coordonnees: Depassement des bordures\n\n";
				this->ajoutCourant = false;
				break;
			}

			for (int i = B.getCol(); i < B.getCol() + B.getNumCases(); i++) {

				if (this->cases[B.getLig()][i].occupee == true) {
					if (B.estPlaceParJoueur())
						cout << "Mauvaises coordonnees: Chevauchement\n\n";
					this->ajoutCourant = false;
					break;

				}
			}
			if (!this->ajoutCourant)break;

			for (int i = B.getCol(); i < B.getCol() + B.getNumCases(); i++) {
				B.getCases()[index] = &(this->cases[B.getLig()][i]);
				this->cases[B.getLig()][i].occupee = true;
				this->cases[B.getLig()][i].numeroJoueur = B.getNumeroJoueur();
				index++;
			}
			this->casesOccupee += B.getNumCases();
			this->ajoutCourant = true;

			break;
		}

		case ouest: {

			if (B.getCol() > this->numCol || B.getCol() - B.getNumCases() < 0) {
				if (B.estPlaceParJoueur())
					cout << "Mauvaises coordonnees: Depassement des bordures\n\n";
				this->ajoutCourant = false;
				break;
			}

			for (int i = B.getCol(); i > B.getCol() - B.getNumCases(); i--) {

				if (this->cases[B.getLig()][i].occupee == true) {
					if (B.estPlaceParJoueur())
						cout << "Mauvaises coordonnees: Chevauchement\n\n";
					this->ajoutCourant = false;
					break;

				}
			}
			if (!this->ajoutCourant)break;

			for (int i = B.getCol(); i > B.getCol() - B.getNumCases(); i--) {
				B.getCases()[index] = &(this->cases[B.getLigne()][i]);
				this->cases[B.getLig()][i].occupee = true;
				this->cases[B.getLig()][i].numeroJoueur = B.getNumeroJoueur();
				index++;
			}
			this->casesOccupee += B.getNumCases();
			this->ajoutCourant = true;

			break;
		}

		default:break;
		}
		return *this;
	

	}

}
