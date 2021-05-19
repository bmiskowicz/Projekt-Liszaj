#pragma once
#include "Liszaj.h" 

int main()
{
	Liszaj liszaj;	//stworzenie obiektu klasy Liszaj o nazwie liszaj
	srand((unsigned int) time(NULL));	//ustawienie punktu startowego do generowania liczb pseudolosowych
	liszaj.Start();	//wywo³anie metody Start dla obiektu liszaj
	return 0;
}