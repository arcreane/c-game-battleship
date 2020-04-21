#pragma once

class joueurs //declare la class joueur
{
    private:

	char nom[255];
	int nombreBateauxCoule; //nombre de bateaux coulÈs parmis les propres bateaux du joueur


public:

    joueur(char *nom); //prototype du constructeur
	
	char *getNom(void); //renvoi le nom du joueur sous forme de chaine de caractËres
	int getNumBateauxCoule(void); //retourne le nombre de bateaux coulé au joueur
	void decrementNumBateaux(void); //specifie qu'un bateau du joueur est coulé

};

};

