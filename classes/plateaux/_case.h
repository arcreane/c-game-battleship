#pragma once
class _case
{
public:

	bool touche, occupee;
	int numJoueur, X, Y;

	_case(void) {
		touche = false;
		occupee = false;
		numJoueur = 0;
		this->X = 0;
		this->Y = 0;
	}

	void setCoordonnees(int x, int y);
};

