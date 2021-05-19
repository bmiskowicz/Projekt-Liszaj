#include "Liszaj.h"
#include <windows.h>

Liszaj::Liszaj()
{ 
    //stworzenie tablic dynamicznych 
    states = new int[121];
    times = new int[121];
    statescopy = new int[121];
    this->font.loadFromFile("odi.ttf"); //wczytanie fontu tekstów
    //utworzenie napisów
    this->s_probability = new Strings(402, 235, &this->font, "Prawdopodobieñstwo zarazenia: 50%", 14);
    this->s_immunity = new Strings(402, 178, &this->font, "Ilosc sekund odpornosci: 4s", 14);
    this->s_sick = new Strings(402, 118, &this->font, "Ilosc sekund chorowania: 6s", 14);
    this->s_size = new Strings(402, 58, &this->font, "Ilosc kratek X: 11           Ilosc kratek Y: 11", 14);
    //utworzenie przycisków
    this->start = new Buttons(402, 15, 99, 40, &this->font, "Start/Stop", Color::Black, 16);
    this->reset = new Buttons(503, 15, 99, 40, &this->font, "Reset", Color::Black, 16);
    this->numberX = new Buttons(402, 75, 48, 40, &this->font, "+1 X", Color::Black, 16);
    this->numberX2 = new Buttons(452, 75, 48, 40, &this->font, "-1 X", Color::Black, 16);
    this->numberY = new Buttons(503, 75, 48, 40, &this->font, "+1 Y", Color::Black, 16);
    this->numberY2= new Buttons(553, 75, 48, 40, &this->font, "-1 Y", Color::Black, 16);
    this->sick = new Buttons(402, 135, 99, 40, &this->font, "+1s choroby", Color::Black, 16);
    this->sick2 = new Buttons(503, 135, 99, 40, &this->font, "-1s choroby", Color::Black, 16);
    this->immunity = new Buttons(402, 195, 99, 40, &this->font, "+1s odpornosci", Color::Black, 16);
    this->immunity2 = new Buttons(503, 195, 99, 40, &this->font, "-1s odpornosci", Color::Black, 16);
    this->probability = new Buttons(402, 255, 99, 40, &this->font, "+1% szans zarazenia", Color::Black, 12);
    this->probability2 = new Buttons(503, 255, 99, 40, &this->font, "-1% szans zarazenia", Color::Black, 12);
    this->exit = new Buttons(402, 300, 200, 40, &this->font, "Exit", Color::Black, 16);
    Okno();
}

void Liszaj::Okno()
{
    //wype³nienie tablic zerami
    for (int i = 0; i < map.width*map.heigth; i++)   //dla ka¿dego elementu
    {
        states[i] = 0;  //wartoœci stanów i czasów ustawione na 0
        times[i] = 0;
    }
    //ustawienie wartoœci pocz¹tkowych symulacji
    stop = 1;
    states[60] = 1;
    times[60] = 6;
    map.load("liszaj.png", Vector2u(map.Xsize, map.Ysize), map.width, map.heigth);   //wczytanie grafik
    map.Cells(Vector2u(32, 32), states, map.width, map.heigth);   //wczytanie grafik
	this->window = new RenderWindow(VideoMode(640, 352), "Liszaj by Brajan Miœkowicz", Style::Resize);    //utworzenie okna programu

}

Liszaj::~Liszaj()
{
    delete [] states;
    delete [] statescopy;
    delete [] times;
    //usuniêcie napisów
    delete this->s_probability;
    delete this->s_immunity;
    delete this->s_sick;
    delete this->s_size;
    //usuniêcie przycisków
    delete this->exit;
    delete this->start;
    delete this->reset;
    delete this->numberX;
    delete this->numberX2;
    delete this->numberY;
    delete this->numberY2;
    delete this->sick;
    delete this->sick2;
    delete this->immunity;
    delete this->immunity2;
    delete this->probability;
    delete this->probability2;
    //usuniêcie okona
	delete this->window;
}

void Liszaj::Start()
{
    Render();   //wyrysowanie okna
    Time mytime = seconds(0.5);   //zadeklarowaniu czasu co jaki wzmienia³y bêd¹ siê stany
    Clock clock;    //w³¹czenie zegarka
	while (this->window->isOpen())  //puki okno jest otwarte
	{
        Grafika();  //wywo³anie funkcji odpowiedzialnej za wydarzenia w oknie
        if (stop == 0)  //je¿eli symulacja nie jest zatrzymana
        {
            Time time1 = clock.getElapsedTime();    //pobranie czasu z zegarka
            if (time1 >= mytime)  //jeœli minie zadeklarowany czas
            {
                map.States(times, states, statescopy, map.width, map.heigth, map.sicktime, map.immunitytime, map.prob);    //zmiana stanów
                map.Cells(Vector2u(32, 32), states, map.width, map.heigth);    //zmiana kolorów komórek
                Render();   //wyrysowanie zmian
                time1 = clock.restart();    //zresetowanie czasu zegarka
            }
        }
    }
}

void Liszaj::Render()
{
    this->window->clear(Color(57, 0, 137)); //wyczyszczenie okna i ustalenie t³a
    //rysuj¹ca grafiki napisów
    this->s_probability->Render(window);
    this->s_immunity->Render(window);
    this->s_sick->Render(window);
    this->s_size->Render(window);
    //rysuj¹ca grafiki przycisków
    this->exit->Render(window);
    this->start->Render(window);
    this->reset->Render(window);
    this->numberX->Render(window);
    this->numberX2->Render(window);
    this->numberY->Render(window);
    this->numberY2->Render(window);
    this->sick->Render(window);
    this->sick2->Render(window);   
    this->immunity->Render(window);
    this->immunity2->Render(window);
    this->probability->Render(window);
    this->probability2->Render(window);
    this->window->draw(map);    //zmiana grafiki komórek
    this->window->display();    //rysowanie ca³oœci
}

void Liszaj::Reset()   //funkcja resetuj¹ca
{
    for (int i = 0; i < map.width * map.heigth; i++)   //dla ka¿dego elementu
    {
        states[i] = 0;  //zresetowane zostaj¹ wartoœci stanów i czasów
        times[i] = 0;
    }
    states[(map.heigth / 2) * map.width + map.width / 2] = 1; //œrodkowa komórka zostaje zara¿ona
    times[(map.heigth / 2) * map.width + map.width/2] = map.sicktime - 1;
    map.Cells(Vector2u(32, 32), states, map.width, map.heigth);    //zmiana kolorów komórek
}

void Liszaj::Change()
{
    s_size->ChangeText("Ilosc kratek X: " + to_string(map.width) + "           Ilosc kratek Y:" + to_string(map.heigth));   //zmiana napisu
    delete[]states; //usuniêcie tablic
    delete[]statescopy;
    delete[]times;
    states = new int[map.width * map.heigth];   //stworzenie nowych tablic o zmienionej wielkoœci
    times = new int[map.width * map.heigth];
    statescopy = new int[map.width * map.heigth];
    for (int i = 0; i < map.width * map.heigth; i++)   //dla ka¿dego elementu
    {
        states[i] = 0;  //zresetowane zostaj¹ wartoœci stanów i czasów
        times[i] = 0;
    }
    map.Xsize = window->getSize().y / map.width;    //zmiana wielkoœci komórek
    map.Ysize = window->getSize().y / map.heigth;
    map.load("liszaj.png", Vector2u(map.Xsize, map.Ysize), map.width, map.heigth);   //wczytanie grafik
    Reset();   //zresetowanie symulacji
}

void Liszaj::Grafika()
{
	while (this->window->pollEvent(event))  //jeœli pojawi siê wydarzenie w oknie
	{
        if (event.type == Event::Resized)   //jeœli zmieni siê wielkoœæ okna
        {
            
            if (window->getSize().x < map.width * 1.7 || window->getSize().y < map.heigth) window->setSize(Vector2u(map.width*1.7, map.heigth));    //zabezpieczenie przed znikniêciem kratek przy zbyt ma³ym oknie
            map.load("liszaj.png", Vector2u(map.Xsize, map.Ysize), map.width, map.heigth);   //wczytanie grafik

            if (window->getSize().x < window->getSize().y * 1.7)   window->setSize(Vector2u(window->getSize().y * 1.7, window->getSize().y));   //zabezpieczenie przed wejœciem przycisków i napisów pod kratki
            window->setView(View(FloatRect(0, 0, event.size.width, event.size.height)));    //zablokowanie automatycznej zmiany wielkoœci 
            map.Xsize = window->getSize().y / map.width;    //zmiana wielkoœci komórek rêcznie
            map.Ysize = window->getSize().y / map.heigth;

            //rêczna zmiana wielkoœci przycisków
            exit->Resize(window->getSize().x, window->getSize().y, 402, 300, 200, 40, 16);
            start->Resize(window->getSize().x, window->getSize().y, 402, 15, 99, 40, 16);
            reset->Resize(window->getSize().x, window->getSize().y, 503, 15, 99, 40, 16);
            numberX->Resize(window->getSize().x, window->getSize().y, 402, 75, 48, 40, 16);
            numberX2->Resize(window->getSize().x, window->getSize().y, 452, 75, 48, 40, 16);
            numberY->Resize(window->getSize().x, window->getSize().y, 503, 75, 48, 40, 16);
            numberY2->Resize(window->getSize().x, window->getSize().y, 553, 75, 48, 40, 16);
            sick->Resize(window->getSize().x, window->getSize().y, 402, 135, 99, 40, 16);
            sick2->Resize(window->getSize().x, window->getSize().y, 503, 135, 99, 40, 16);
            immunity->Resize(window->getSize().x, window->getSize().y, 402, 195, 99, 40, 16);
            immunity2->Resize(window->getSize().x, window->getSize().y, 503, 195, 99, 40, 16);
            probability->Resize(window->getSize().x, window->getSize().y, 402, 255, 99, 40, 12);
            probability2->Resize(window->getSize().x, window->getSize().y, 503, 255, 99, 40, 12);

            //rêczna zmiana wielkoœci tekstów
            s_probability->Resize(window->getSize().x, window->getSize().y, 402, 235, 14);
            s_immunity->Resize(window->getSize().x, window->getSize().y, 402, 178, 14);
            s_sick->Resize(window->getSize().x, window->getSize().y, 402, 118, 14);
            s_size->Resize(window->getSize().x, window->getSize().y, 402, 58, 14);

            map.load("liszaj.png", Vector2u(map.Xsize, map.Ysize), map.width, map.heigth);   //wczytanie grafik
            Render(); //wyrysowanie nowego wygl¹du
        }
        if (Mouse::isButtonPressed(Mouse::Left))    //je¿eli zostanie naciœniêty lewy przycisk myszy
        {
            if (exit->isOver(*window) == true)  // je¿eli mysz znajduje siê nad przyciskiem exit
                this->window->close();
            else if (start->isOver(*window) == true)  //lub je¿eli mysz znajduje siê nad przyciskiem start/stop
            {
                if (start->change() == false)  stop = 0;    //jeœli symulacja jest zatrzymana, zostaje uruchomiona ponownie
                else stop = 1;  //i przeciwnie
            }
            else if (reset->isOver(*window) == true)  //lub je¿eli mysz znajduje siê nad przyciskiem reset
            {
                Reset();   //wywo³anie fk resetuj¹cej
            }
            else if (numberX->isOver(*window) == true && map.width < window->getSize().y)  //lub je¿eli mysz znajduje siê nad pierwszym przyciskiem +
            {
                map.width += 1;  //zwiêksza siê iloœæ kratek X
                Change();  //wywo³anie zmiany wielkoœci
            }
            else if (numberX2->isOver(*window) == true && map.width > 10)  //lub je¿eli mysz znajduje siê nad pierwszym przyciskiem -
            {
                map.width -= 1;  //zmniejsza siê iloœæ kratek X
                Change();  //wywo³anie zmiany wielkoœci
            }
            else if (numberY->isOver(*window) == true && map.heigth < window->getSize().y)  //lub je¿eli mysz znajduje siê nad pierwszym przyciskiem +
            {
                map.heigth += 1;  //zwiêksza siê iloœæ kratek Y
                Change();  //wywo³anie zmiany wielkoœci
            }
            else if (numberY2->isOver(*window) == true && map.heigth > 10)  //lub je¿eli mysz znajduje siê nad pierwszym przyciskiem -
            {
                map.heigth -= 1;  //zmniejsza siê iloœæ kratek Y
                Change();  //wywo³anie zmiany wielkoœci
            }
            else if (sick->isOver(*window) == true && map.sicktime < 10)  //lub je¿eli mysz znajduje siê nad pierwszym przyciskiem +
            {
                map.sicktime += 1;  //zwiêksza siê czas choroby
                s_sick->ChangeText("Ilosc sekund chorowania: " + to_string(map.sicktime) + "s");   //zmiana napisu
            }
            else if (sick2->isOver(*window) == true && map.sicktime > 1 )  //lub je¿eli mysz znajduje siê nad pierwszym przyciskiem -
            {
                map.sicktime -= 1;  //zmniejsza siê czas choroby
                s_sick->ChangeText("Ilosc sekund chorowania: " + to_string(map.sicktime) + "s");   //zmiana napisu
            }
            else if (immunity->isOver(*window) == true && map.immunitytime < 10)  //lub je¿eli mysz znajduje siê nad drugim przyciskiem +
            {
                map.immunitytime += 1;  //zwiêksza siê czas odpornoœci
                s_immunity->ChangeText("Ilosc sekund odpornosci: " + to_string(map.immunitytime) + "s");   //zmiana napisu
            }
            else if (immunity2->isOver(*window) == true && map.immunitytime > 1)  //lub je¿eli mysz znajduje siê nad drugim przyciskiem -
            {
                map.immunitytime -= 1;  //zmniejsza siê czas odpornoœci
                s_immunity->ChangeText("Ilosc sekund odpornosci: " + to_string(map.immunitytime) + "s");   //zmiana napisu
            }
            else if (probability->isOver(*window) == true && map.prob < 100)  //lub je¿eli mysz znajduje siê nad trzecim przyciskiem +
            {
                map.prob += 1;  //zwiêksza siê prawdopodobieñstwo zachorowania
                s_probability->ChangeText("Prawdopodobieñstwo zarazenia: " + to_string(map.prob) + "%");   //zmiana napisu
            }
            else if (probability2->isOver(*window) == true && map.prob > 1)  //lub je¿eli mysz znajduje siê nad trzecim przyciskiem -
            {
                map.prob -= 1;  //zmniejsza siê prawdopodobieñstwo zachorowania
                s_probability->ChangeText("Prawdopodobieñstwo zarazenia: " + to_string(map.prob) + "%");   //zmiana napisu
            }
            else if (Mouse::getPosition(*window).x <= map.Xsize * map.width && Mouse::getPosition(*window).y <= map.Ysize*map.heigth)
            {
                int j = Mouse::getPosition(*window).x / map.Xsize; //podanie pozycji x myszy do zmiennej j
                int i = Mouse::getPosition(*window).y / map.Ysize; //podanie pozycji y myszy do zmiennej i
                if (states[j + i * map.width] == 0)     //zmiana zdrowej na chor¹
                {
                    states[j + i * map.width] = 1;
                    times[j + i * map.width] = map.sicktime - 1;
                }
                else if (states[j + i * map.width] > 0 && states[j + i * map.width] < 11)   //zmiana chorej na odporn¹
                {
                    states[j + i * map.width] = 11;
                    times[j + i * map.width] = map.immunitytime - 1;
                }
                else    //zmiana odpornej na zdrow¹
                {
                    states[j + i * map.width] = 0;
                    times[j + i * map.width] = 0;
                }
                map.Cells(Vector2u(32, 32), states, map.width, map.heigth);    //zmiana kolorów komórek
                this->window->draw(map);    //zmiana grafiki komórek
                this->window->display();    //rysowanie ca³oœci
            }
        }
        if (Mouse::isButtonPressed(Mouse::Right))   //dla przyciœniêtego lewego przycisku
        {
            if (Mouse::getPosition(*window).x <= map.Xsize * map.width && Mouse::getPosition(*window).y <= map.Ysize * map.heigth) //jeœli mysz jest nad kratkami
            {
                int j = Mouse::getPosition(*window).x / map.Xsize; //podanie pozycji x myszy do zmiennej j
                int i = Mouse::getPosition(*window).y / map.Ysize; //podanie pozycji y myszy do zmiennej i
                if (times[j + i * map.width] == 0)   //jeœli pozosta³ czas
                {
                    if (states[j + i * map.width] == 0) //jeœli jest zdrowa to zamienia j¹ na chor¹
                    {
                        states[j + i * map.width] = 1;
                        times[j + i * map.width] = map.sicktime - 1;
                    }
                    else if (states[j + i * map.width] > 0 && states[j + i * map.width] < 11)   //jeœli jest chora to zamienia j¹ na odporn¹
                    {
                        states[j + i * map.width] = 11;
                        times[j + i * map.width] = map.immunitytime - 1;
                    }
                    else    //je¿eli jest odporna to zamienia j¹ w zdrow¹
                    {
                        states[j + i * map.width] = 0;
                        times[j + i * map.width] = 0;
                    }
                }
                else //jeœli pozosta³ czas
                {
                    states[j + i * map.width] += 1; //gradacja kolorów
                    times[j + i * map.width]--; //czas jest zmniejszony o 1
                }
                map.Cells(Vector2u(32, 32), states, map.width, map.heigth);    //zmiana kolorów komórek
                this->window->draw(map);    //zmiana grafiki komórek
                this->window->display();    //rysowanie ca³oœci
            }
        }
        Render();   //wyrysowanie zmian
    }
}

void TileMap::draw(RenderTarget& target, RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();
    // apply the tileset texture
    states.texture = &m_tileset;
    // draw the vertex array
    target.draw(m_vertices, states);
}

TileMap::TileMap()
{
    //przypisanie wartosci pocz¹tkowych zmiennych z opcji
    chance = 0;
    immunitytime = 4;
    sicktime = 6;
    prob = 50;
    width = 11;
    heigth = 11;
    Xsize = 32;
    Ysize = 32;
}

void TileMap::load(const string& tileset, Vector2u tileSize, int width, int height)
{
    // load the tileset texture
    m_tileset.loadFromFile(tileset);

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
        {
            // get a pointer to the current tile's quad
            Vertex* quad = &m_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
        }
}

void TileMap::Cells(Vector2u tileSize, int* states, int width, int height)
{
    // populate the vertex array, with one quad per tile
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = states[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            Vertex* quad = &m_vertices[(i + j * width) * 4];

            // define its 4 texture coordinates
            quad[0].texCoords = Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
}

void TileMap::Copy(int* states, int* statescopy, int width, int height)
{
    for (int i = 0; i < width * height; i++)    //dla ka¿dego elementu przypisywana jest wartoœæ elementu tablicy stanów do elementu tablicy pomocniczej
        statescopy[i] = states[i];
}

void TileMap::Change(int i, int j, int* times, int* states, int prob)
{
    chance = rand()% 100;  //wylosowanie liczby pseudolosowej
    if (chance < prob) //je¿eli liczba jest mniejsza od prob - zmiennej okreœlaj¹cej % szans na zara¿enie
    {
        states[j + i * width] = 1;  //zmienia stan na chory
        times[j + i * width] = sicktime - 1;    //ustawia czas choroby
    }
}


void TileMap::States(int* times, int* states, int* statescopy, int width, int height, int sicktime, int immunitytime, int prob)
{
    Copy(states, statescopy, width, height);    //skopiowanie wartoœci z tablicy stanów do tablicy pomocniczej
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (statescopy[j + i * width] > 0 && statescopy[j + i * width] < 11)    //jeœli jest chora
            {
                if (i > 0 && statescopy[j + (i - 1) * width] == 0)    //sprawdza s¹siada z góry, jeœli jest zdrowy to próbuje go zaraziæ w metodzie Change
                {
                    Change(i - 1, j, times, states, prob);
                }
                if ((i < height - 1) && statescopy[j + (i + 1) * width] == 0)    //sprawdza s¹siada z do³u, jeœli jest zdrowy to próbuje go zaraziæ w metodzie Change
                {
                    Change(i + 1, j, times, states, prob);
                }
                if (j > 0 && statescopy[j - 1 + i * width] == 0)    //sprawdza s¹siada z lewej, jeœli jest zdrowy to próbuje go zaraziæ w metodzie Change
                {
                    Change(i, j - 1, times, states, prob);
                }
                if ((j < width - 1) && statescopy[j + 1 + i * width] == 0)    //sprawdza s¹siada z prawej, jeœli jest zdrowy to próbuje go zaraziæ w metodzie Change
                {
                    Change(i, j + 1, times, states, prob);
                }
                if (i > 0 && j > 0 && statescopy[j - 1 + (i - 1) * width] == 0)    //sprawdza s¹siada w lewym górnym rogu, jeœli jest zdrowy to próbuje go zaraziæ w metodzie Change
                {
                    Change(i - 1, j - 1, times, states, prob);
                }
                if (i > 0 && (j < width - 1) && statescopy[j + 1 + (i - 1) * width] == 0)    //sprawdza s¹siada w prawym górnym rogu, jeœli jest zdrowy to próbuje go zaraziæ w metodzie Change
                {
                    Change(i - 1, j + 1, times, states, prob);
                }
                if ((i < height - 1) && (j > 0) && statescopy[j - 1 + (i + 1) * width] == 0)    //sprawdza s¹siada w lewym dolnym rogu, jeœli jest zdrowy to próbuje go zaraziæ w metodzie Change
                {
                    Change(i + 1, j - 1, times, states, prob);
                }
                if ((i < height - 1) && (j < width - 1) && statescopy[j + 1 + (i + 1) * width] == 0)    //sprawdza s¹siada w prawym dolnym rogu, jeœli jest zdrowy to próbuje go zaraziæ w metodzie Change
                {
                    Change(i + 1, j + 1, times, states, prob);
                }

                if (times[j + i * width] == 0 ) //jeœli nie ma czasu to staje sie odporna
                {
                    states[j + i * width] = 11;
                    times[j + i * width] = immunitytime - 1;
                }
                else    //w przeciwnym razie zmniejsza siê czas, nastêpuje gradacja
                {
                    states[j + i * width]++;
                    times[j + i * width]--;
                }
            }
            else if (statescopy[j + i * width] > 10)  //je¿eli jest odporna
            {
                if (times[j + i * width] == 0)  //jeœli nie ma ju¿ czasu
                {
                    states[j + i * width] = 0;  //to staje sie zdrowa
                }
                else    //w przeciwnym razie zmniejsza siê czas, nastêpuje gradacja czasu i kolorw
                {
                    states[j + i * width]++;
                    times[j + i * width]--;
                }
            }
        }
    }
}
