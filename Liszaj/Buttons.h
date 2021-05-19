#pragma once
#include <iostream>
#include <cstdlib>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

enum button_states { unactive, active };	//wyp wyliczeniowy z listπ wartoúci


class Buttons	//klasa tworzπca i obs≥ugujπca przyciski i teksty na nich
{
private:
	short unsigned buttonState;	//zmienna okreúlajπca stan
	RectangleShape shape;	//deklaracja obiektu RectangleShape z biblioteki sfml
	Font *font;	//deklaracja wskaünika na obiekt Font z biblioteki sfml
	Text text;	//deklaracja obiektu Text z biblioteki sfml
	Color nColor;	//deklaracja obiektu Color z biblioteki sfml
public:
	Buttons(int x, int y, int width, int heigth, Font *font, string text, Color nColor, int size);	//konstruktor
	bool isOver(RenderWindow &window);	//metoda sprawdzajπca, czy myszka jest nad przyciskiem
	void Render(RenderTarget *target);	//metoda rysujπca
	bool change();	//metoda zmieniajπca stan przycisku
	void Resize(int xsize, int ysize, int x, int y, int width, int heigth, int size);	//metoda zmieniajπca rozmiar przycisku
};

class Strings	//klasa tworzπca i obs≥ugujπca teksty
{
private:
	Font* font;	//deklaracja wskaünika na obiekt Font z biblioteki sfml
	Text text;	//deklaracja obiektu Text z biblioteki sfml
public:
	Strings(int x, int y, Font *font, string text, int size);	//konstruktor
	void Render(RenderTarget *target);	//metoda wypisujπca tekst
	void ChangeText(string text);	//metoda zmieniajπca ≥aÒcuch w tekúcie
	void Resize(int xsize, int ysize, int x, int y, int size);
};