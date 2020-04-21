#pragma once

/*class qui regroupe es attributs et methodes communes à chaque type de bateau */
class batiment{

protected:

	int numCases,ligne,colonne,orientation,numero,numeroJoueur;
	bool randomPlacement,coule;

	_case **listeCases;  //liste des cases de la grilles sur lesquelles le bateau est placé



public:

//constructeur
	batiment(int numCase,int numero,int numJ,bool randomCoord){
		
		this->numCases = numCase;
		this->numero = numero;
		this->numeroJoueur = numJ;
		this->listeCases = new _case*[numCase];
		this->randomPlacement = randomCoord;
		this->coule = false;	

	}

	virtual ~batiment(void){

		delete [] listeCases;  //la liste de cases est le seul élément isntancié dynamiquement
                               //on ne doit pas delete le contenu de la liste ici, seulement la liste elle même
	}

	bool estCoule(void); 
	bool getStatus(void); 
	bool estPlaceParJoueur(void);
	int getNumero(void); 
	int getNumeroJoueur(void);
	int getLigne(void); 
	int getColonne(void); 
	int getNumCases(void); 
	int getOrientation(void); 
	_case **getCases(void); 
	_case *getCaseTouchee(void); 
	void setCoule(bool c); 
	void setLigne(int ligne); 
	void setColonne(int colonne); 
	void setOrientation(int orientation);

	virtual char *getType(void)=0;


};

class porteAvion :public batiment{

	/*class porteAvion héritée de batiment*/

public:


	porteAvion(int numCase,int numero,int numJ,bool randomCoord) : batiment(numCase,numero,numJ,randomCoord){}
	char *getType(void);
};


class croiseur :public batiment{

	/*class croiseur héritée de batiment*/

public:

	croiseur(int numCase,int numero,int numJ,bool randomCoord) : batiment(numCase,numero,numJ,randomCoord){}
	char *getType(void);


};


class sousMarin :public batiment{

	/*class sousMarin héritée de batiment*/

public:
	sousMarin(int numCase,int numero,int numJ,bool randomCoord) : batiment(numCase,numero,numJ,randomCoord){}
	char *getType(void);



};


class torpilleur :public batiment{

	/*class torpilleur héritée de batiment*/

public:
	torpilleur(int numCase,int numero,int numJ,bool randomCoord) : batiment(numCase,numero,numJ,randomCoord){}
	char *getType(void);


};


};

