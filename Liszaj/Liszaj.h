#pragma once
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Buttons.h"

using namespace sf;
using namespace std;

class TileMap : public Drawable, public Transformable	//klasa tworz¹ca i obs³uguj¹ca grafikê zara¿anych komórek
{
private:
	void Copy(int* states, int* statescopy, int width, int height);	//metoda kopiuj¹ca wartoœci stanów do tablicy pomocniczej
	void Change(int i, int j, int* times, int* states, int prob);	//metoda zara¿aj¹ca komórkê z pewnym prawdopodobieñstwem
	int chance;	//zmienna przechowuj¹ca liczbe pseudolosow¹ okreœlaj¹c¹ szanse na zara¿enie
public:
	VertexArray m_vertices;	//deklaracja obiektu VertexArray z biblioteki sfml
	Texture m_tileset;	//deklaracja obiektu Texture z biblioteki sfml
	TileMap();	//konstruktor
    void load(const string& tileset, Vector2u tileSize, int width, int height);	//metoda ustawiaj¹ca graficzny wygl¹d stanów komórek
	void draw(RenderTarget& target, RenderStates states) const;	//metoda rysuj¹ca grafikê komórek
	void Cells(Vector2u tileSize, int* states, int width, int height);	//metoda zmieniaj¹ca grafiki komórek
	void States(int* times, int* states, int* statescopy, int width, int height, int sicktime, int immunitytime, int prob);	//metoda zmieniaj¹ca stany oraz czasy komórek
	int sicktime, immunitytime, prob;	//zmienne przechowuj¹ce wartoœci czasów choroby, odpornoœci komórek i prawdopodobieñstwo zachorowania
	int width, heigth, Xsize, Ysize;	//zmienne informuj¹ce o iloœci kratek na szerokoœæ i wysokoœæ, oraz wielkoœæ w pikselach komórek na szerokoœæ i wysokoœæ
};

class Liszaj	//klasa tworz¹ca i obs³uguj¹ca okno, oraz zajmuj¹ca siê mechanikami w programie
{
private:
	RenderWindow *window;	//deklaracja obiektu RenderWindow z biblioteki sfml
	Event event;	//deklaracja obiektu Event z biblioteki sfml
	Buttons* exit, * start, * reset, * sick, * sick2, * immunity, * immunity2, * probability, * probability2, * numberX, * numberX2, * numberY, * numberY2;	//deklaracja wskaŸników do obiektów klasy Buttons
	Strings* s_probability, *s_immunity, *s_sick, * s_size;	//deklaracja wskaŸników do obiektów klasy Strings
	Font font;	//deklaracja obiektu Font z bibliteki sfml
	void Okno();	//inicjalizacja okna 
	void Reset();	//fk resetuj¹ca symujacje
	void Change();	//fk zmieniaj¹ca wielkoœæ
	bool stop;	//zmienna informuj¹ca, czy symulacja jest zatrzymana, czy uruchomiona
public:
    TileMap map;	//deklaracja obiektu Font z bibliteki sfml	
	int *states;	//tablica stanów komórek
	int *statescopy;	//tablica pomocnicza stanów komórek
	int *times;	//tablica czasów komórek
	Liszaj();	//konstruktor okna
	~Liszaj();	//destruktor okna
	void Start(); //g³ówna pêtla
	void Render();	//renderowanie
	void Grafika();	//eventy w oknie
};