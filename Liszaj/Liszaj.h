#pragma once
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Buttons.h"

using namespace sf;
using namespace std;

class TileMap : public Drawable, public Transformable	//klasa tworz�ca i obs�uguj�ca grafik� zara�anych kom�rek
{
private:
	void Copy(int* states, int* statescopy, int width, int height);	//metoda kopiuj�ca warto�ci stan�w do tablicy pomocniczej
	void Change(int i, int j, int* times, int* states, int prob);	//metoda zara�aj�ca kom�rk� z pewnym prawdopodobie�stwem
	int chance;	//zmienna przechowuj�ca liczbe pseudolosow� okre�laj�c� szanse na zara�enie
public:
	VertexArray m_vertices;	//deklaracja obiektu VertexArray z biblioteki sfml
	Texture m_tileset;	//deklaracja obiektu Texture z biblioteki sfml
	TileMap();	//konstruktor
    void load(const string& tileset, Vector2u tileSize, int width, int height);	//metoda ustawiaj�ca graficzny wygl�d stan�w kom�rek
	void draw(RenderTarget& target, RenderStates states) const;	//metoda rysuj�ca grafik� kom�rek
	void Cells(Vector2u tileSize, int* states, int width, int height);	//metoda zmieniaj�ca grafiki kom�rek
	void States(int* times, int* states, int* statescopy, int width, int height, int sicktime, int immunitytime, int prob);	//metoda zmieniaj�ca stany oraz czasy kom�rek
	int sicktime, immunitytime, prob;	//zmienne przechowuj�ce warto�ci czas�w choroby, odporno�ci kom�rek i prawdopodobie�stwo zachorowania
	int width, heigth, Xsize, Ysize;	//zmienne informuj�ce o ilo�ci kratek na szeroko�� i wysoko��, oraz wielko�� w pikselach kom�rek na szeroko�� i wysoko��
};

class Liszaj	//klasa tworz�ca i obs�uguj�ca okno, oraz zajmuj�ca si� mechanikami w programie
{
private:
	RenderWindow *window;	//deklaracja obiektu RenderWindow z biblioteki sfml
	Event event;	//deklaracja obiektu Event z biblioteki sfml
	Buttons* exit, * start, * reset, * sick, * sick2, * immunity, * immunity2, * probability, * probability2, * numberX, * numberX2, * numberY, * numberY2;	//deklaracja wska�nik�w do obiekt�w klasy Buttons
	Strings* s_probability, *s_immunity, *s_sick, * s_size;	//deklaracja wska�nik�w do obiekt�w klasy Strings
	Font font;	//deklaracja obiektu Font z bibliteki sfml
	void Okno();	//inicjalizacja okna 
	void Reset();	//fk resetuj�ca symujacje
	void Change();	//fk zmieniaj�ca wielko��
	bool stop;	//zmienna informuj�ca, czy symulacja jest zatrzymana, czy uruchomiona
public:
    TileMap map;	//deklaracja obiektu Font z bibliteki sfml	
	int *states;	//tablica stan�w kom�rek
	int *statescopy;	//tablica pomocnicza stan�w kom�rek
	int *times;	//tablica czas�w kom�rek
	Liszaj();	//konstruktor okna
	~Liszaj();	//destruktor okna
	void Start(); //g��wna p�tla
	void Render();	//renderowanie
	void Grafika();	//eventy w oknie
};