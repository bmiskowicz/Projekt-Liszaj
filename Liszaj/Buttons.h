#pragma once
#include <iostream>
#include <cstdlib>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

enum button_states { unactive, active };	//wyp wyliczeniowy z list� warto�ci


class Buttons	//klasa tworz�ca i obs�uguj�ca przyciski i teksty na nich
{
private:
	short unsigned buttonState;	//zmienna okre�laj�ca stan
	RectangleShape shape;	//deklaracja obiektu RectangleShape z biblioteki sfml
	Font *font;	//deklaracja wska�nika na obiekt Font z biblioteki sfml
	Text text;	//deklaracja obiektu Text z biblioteki sfml
	Color nColor;	//deklaracja obiektu Color z biblioteki sfml
public:
	Buttons(int x, int y, int width, int heigth, Font *font, string text, Color nColor, int size);	//konstruktor
	bool isOver(RenderWindow &window);	//metoda sprawdzaj�ca, czy myszka jest nad przyciskiem
	void Render(RenderTarget *target);	//metoda rysuj�ca
	bool change();	//metoda zmieniaj�ca stan przycisku
	void Resize(int xsize, int ysize, int x, int y, int width, int heigth, int size);	//metoda zmieniaj�ca rozmiar przycisku
};

class Strings	//klasa tworz�ca i obs�uguj�ca teksty
{
private:
	Font* font;	//deklaracja wska�nika na obiekt Font z biblioteki sfml
	Text text;	//deklaracja obiektu Text z biblioteki sfml
public:
	Strings(int x, int y, Font *font, string text, int size);	//konstruktor
	void Render(RenderTarget *target);	//metoda wypisuj�ca tekst
	void ChangeText(string text);	//metoda zmieniaj�ca �a�cuch w tek�cie
	void Resize(int xsize, int ysize, int x, int y, int size);
};