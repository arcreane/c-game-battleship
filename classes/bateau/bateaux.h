#pragma once


/*class qui regroupe es attributs et methodes communes à chaque type de bateau */
class bateaux {

protected:

	int numCases, ligne, colonne, orientation, numero, numeroJoueur;
	bool randomPlacement, coule;

	_case **listeCases;  //liste des cases de la grilles sur lesquelles le bateau est placé



public:

	//constructeur
	bateaux(int numCase, int numero, int numJ, bool randomCoord) {

		this->numCases = numCase;
		this->numero = numero;
		this->numeroJoueur = numJ;
		this->listeCases = new _case*[numCase];
		this->randomPlacement = randomCoord;
		this->coule = false;
	}

	virtual ~bateaux(void) {

		delete[] listeCases;  //la liste de cases est le seul élément isntancié dynamiquement
							   //on ne doit pas delete le contenu de la liste ici, seulement la liste elle même
	}

	bool estCoule(void);
	bool getStatus(void);
	bool estPlaceParJoueur(void);
	int getNum(void);
	int getNumJoueur(void);
	int getLig(void);
	int getCol(void);
	int getNumCases(void);
	int getOrientation(void);
	_case **getCases(void);
	_case *getCaseTouchee(void);
	void setCoule(bool c);
	void setLig(int ligne);
	void setCol(int colonne);
	void setOrientation(int orientation);

	virtual char *getType(void) = 0;
};

class porteAvion :public bateaux {

	/*class porteAvion héritée de batiment*/

public:


	porteAvion(int numCase, int numero, int numJ, bool randomCoord) : bateaux(numCase, numero, numJ, randomCoord) {}
	char *getType(void);
};


class croiseur :public bateaux {

	/*class croiseur héritée de batiment*/

public:

	croiseur(int numCase, int numero, int numJ, bool randomCoord) : bateaux(numCase, numero, numJ, randomCoord) {}
	char *getType(void);


};


class sousMarin :public bateaux {

	/*class sousMarin héritée de batiment*/

public:
	sousMarin(int numCase, int numero, int numJ, bool randomCoord) : bateaux(numCase, numero, numJ, randomCoord) {}
	char *getType(void);

};


class torpilleur :public bateaux {

	/*class torpilleur héritée de batiment*/

public:
	torpilleur(int numCase, int numero, int numJ, bool randomCoord) : bateaux(numCase, numero, numJ, randomCoord) {}
	char *getType(void);
};


};
