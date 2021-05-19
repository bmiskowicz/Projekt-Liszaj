#include "Buttons.h"


Buttons::Buttons(int x, int y, int width, int heigth, Font *font, string text, Color nColor, int size)
{
	shape.setPosition(Vector2f(x, y));	//ustawienie pozycji lewego roga przycisk
	shape.setSize(Vector2f(width, heigth));	//ustawienie przycisk
	shape.setFillColor(nColor);	//ustawienie koloru, jakim zostanie wyype³niony przycisk
	buttonState = unactive;	//ustawienie stanu przycisku na nieaktywny

	this->font = font;	//przypisanie wartosci fontu
	this->text.setFont(*this->font);	//ustawienie fontu tekstu na przycisku
	this->text.setString(text);	//ustawienie tekstu na przycisku
	this->text.setFillColor(Color::White);	//ustawienie koloru tekstu na przycisku
	this->text.setCharacterSize(size);	//ustawienie wielkoœci tekstu na przycisku
	this->text.setPosition(shape.getPosition().x + shape.getGlobalBounds().width / 2 - this->text.getGlobalBounds().width / 2,
		shape.getPosition().y + shape.getGlobalBounds().height / 3 - this->text.getGlobalBounds().height / 2);	//ustawienie pozycji tekstu na œrodku przycisku
}


bool Buttons::isOver(RenderWindow& window)
{
	int mouseX = Mouse::getPosition(window).x;	//pobranie pozycji myszki na osi x w oknie
	int mouseY = Mouse::getPosition(window).y;	//pobranie pozycji myszki na osi y w oknie

	int buttonX = shape.getPosition().x;	//pobranie pozycji przycisku na osi x w oknie
	int buttonY = shape.getPosition().y;	//pobranie pozycji przycisku na osi y w oknie

	int buttonXend = buttonX + shape.getGlobalBounds().width;	//przypisanie wartoœci koñca przycisku na osi x
	int buttonYend = buttonY + shape.getGlobalBounds().height;	//przypisanie wartoœci koñca przycisku na osi y

	if (mouseX < buttonXend && mouseX > buttonX && mouseY < buttonYend && mouseY > buttonY)	//jeœli myszka znajduje siê nad przyciskiem
	{
		return true;	//zwraca true
	}
	return false;	//w przeciwnym przypadku zwraca false
}

void Buttons::Render(RenderTarget *target)
{
	target->draw(shape);	//wyrysowanie przycisku
	target->draw(this->text);	//wyrysowanie tekstu na przycisku
}

bool Buttons::change()
{
	if (buttonState == active)	//jeœli stan przycisku to active
	{
		buttonState = unactive;	//zmienia go na przeciwny i zwraca true
		return true;
	}
	buttonState = active;	//w przeciwnym przypadku odwrotnie
	return false;
}

void Buttons::Resize(int xsize, int ysize, int x, int y, int width, int heigth, int size)
{
	shape.setPosition(Vector2f(x * xsize / 640, y * ysize / 352));	//ustawienie pozycji lewego roga przycisk
	shape.setSize(Vector2f(width* xsize/ 640, heigth*ysize/352));	//ustawienie wielkoœci przycisku
	if (ysize / 852 > xsize / 640)	this->text.setCharacterSize(size * ysize / 352);	//ustawienie wielkoœci tekstu na przycisku
		else	this->text.setCharacterSize(size * xsize / 640);	//ustawienie wielkoœci tekstu na przycisku
	this->text.setPosition(shape.getPosition().x + shape.getGlobalBounds().width / 2 - this->text.getGlobalBounds().width / 2,
		shape.getPosition().y + shape.getGlobalBounds().height / 3 - this->text.getGlobalBounds().height / 2);	//ustawienie pozycji tekstu na œrodku przycisku
}

Strings::Strings(int x, int y, Font* font, std::string text, int size)
{
	this->font = font;		//przypisanie wartosci fontu
	this->text.setFont(*this->font);	//ustawienie fontu tekstu
	this->text.setString(text);	//ustawienie ³añcucha tekstu
	this->text.setFillColor(Color::White);	//ustawienie koloru tekstu
	this->text.setCharacterSize(size);	//ustawienie wielkoœci tekstu
	this->text.setPosition(Vector2f(x, y));	//ustawienie pozycji tekstu
}

void Strings::ChangeText(std::string text)
{
	this->text.setString(text);	//zmiana ³añcucha tekstu
}

void Strings::Render(RenderTarget *target)
{
	target->draw(this->text);	//wyrysowanie tekstu
}

void Strings::Resize(int xsize, int ysize, int x, int y, int size)
{
	if (ysize / 352 < xsize / 640)	this->text.setCharacterSize(size * ysize / 352);	//ustawienie wielkoœci tekstu na przycisku
	else	this->text.setCharacterSize(size * xsize / 640);	//ustawienie wielkoœci tekstu na przycisku

	this->text.setPosition(Vector2f(x * xsize / 640, y * ysize / 352));	//ustawienie pozycji tekstu
}
