#define MAX_LICZBA_POZIOMOW 2

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <random>
#include <cmath>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>
const float PI = 3.14159265;

class pocisk {
private:
	sf::Vector2f position;//wspolrzedne
public:
	void destroy() {
		visible = 1;
	}
	sf::Vector2f acceleration;
	sf::RectangleShape rectangle;
	int ticksLeft = 50;
	bool visible = 1;
	void givePociskXY(float x_in, float y_in, float rotation);
	sf::RectangleShape getRect() { return rectangle; }
	float GetRotationToMouse(sf::RenderWindow* window, sf::RectangleShape rectangle) {
		sf::Vector2f curPos = rectangle.getPosition();
		sf::Vector2i position = static_cast<sf::Vector2i>(window->mapPixelToCoords(sf::Mouse::getPosition(*(window))));

		float dx = curPos.x - position.x;
		float dy = curPos.y - position.y;

		float rotation = (atan2(dy, dx)) * 180 / PI;
		rotation += 180;
		return rotation;
	}
};

void pocisk::givePociskXY(float x_in, float y_in, float rotation)
{

	rectangle.setSize(sf::Vector2f(50, 8));
	rectangle.setOrigin(25.f, 4.f);

	rectangle.setRotation(rotation);
	float x = 0, y = 0;
	acceleration.x = 8 * cos((360 - rotation) * PI / 180);
	acceleration.y = -8 * sin((360 - rotation) * PI / 180);

	position.x = x_in + (10 * acceleration.x);
	position.y = y_in + (10 * acceleration.y);
	rectangle.setPosition(position);
}

class pilka {
private:
	sf::Vector2f position;//wspolrzedne
public:
	sf::CircleShape ball;//pilka
	sf::RectangleShape rectangle;
	void givePilkaXY(float x_in, float y_in);//tworz pilke w polozeniu (x,y)
	sf::CircleShape getPilka() { return ball; }//zwroc pilke
	sf::RectangleShape getRect() { return rectangle; }//zwroc pilke
	bool visible = 1;
	sf::Vector2f getPos() { return ball.getPosition(); }
	float GetRotationToMouse(sf::RenderWindow* window, sf::RectangleShape rectangle) {
		sf::Vector2f curPos = rectangle.getPosition();
		sf::Vector2i position = static_cast<sf::Vector2i>(window->mapPixelToCoords(sf::Mouse::getPosition(*(window))));


		float dx = curPos.x - position.x;
		float dy = curPos.y - position.y;

		float rotation = (atan2(dy, dx)) * 180 / PI;
		rotation += 180;
		return rotation;
	}
};

void pilka::givePilkaXY(float x_in, float y_in)
{
	position.x = x_in;
	position.y = y_in;
	//kolo o promieniu 15px
	ball.setRadius(30);
	ball.setPosition(position);//pozycja poczatkowa

	rectangle.setSize(sf::Vector2f(90, 75));
	rectangle.setOrigin(37.5, 37.5);;
	rectangle.setPosition(position);
}

bool sprawdzKolizje(pilka* p1, pocisk* p2) {
	sf::FloatRect intersection;
	if (p1->ball.getGlobalBounds().intersects(p2->rectangle.getGlobalBounds(), intersection)) {
		return true;
	}
	return false;

}
class Menu
{
private:
	sf::Font font;
	sf::Text menu[MAX_LICZBA_POZIOMOW];//maksymalna liczba poziomow
	int selectedItem = 0;
public:
	Menu(float width, float height);
	~Menu() {};
	void przesunG();//przesun do gory
	void przesunD();//przesun w dol
	int getSelectedItem() { return selectedItem; }//zwroc poziom menu
	void draw(sf::RenderWindow& window);//rysuj menu w oknie
};
Menu::Menu(float width, float height)
{ //laduj czcionke
	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}
	//rysowanie elementow menu
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("Nowa gra");
	menu[0].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 1));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Wyjscie");
	menu[1].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 2));
}
//rysowanie menu w biezacym oknie
void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
	{
		window.draw(menu[i]);
	}
}
void Menu::przesunG() {
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = MAX_LICZBA_POZIOMOW - 1;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}
void Menu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MAX_LICZBA_POZIOMOW)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}
//funkcja opozniajaca
void myDelay(int opoznienie)
{
	sf::Clock zegar;
	sf::Time czas;
	while (1)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}
	}
}

int main()
{
	int menu_gry = 0;
	int exit = 0;
	sf::Font font;
	font.loadFromFile("arial.ttf");
	while (exit == 0)
	{
		if (menu_gry == 0)
		{
			int menu_selected_flag = 0;
			sf::RenderWindow window(sf::VideoMode(800, 600), "SFML demo");// utworz okno
			Menu menu(window.getSize().x, window.getSize().y);
			// petla wieczna - dopoki okno jest otwarte
			while (window.isOpen() && exit == 0)
			{
				// w kazdej iteracji petli sprawdzaj zdarzenia
				sf::Event event;
				while (window.pollEvent(event) && exit == 0)
				{
					// jezeli odebrano zdarzenie "Closed" zamknij okno
					if (event.type == sf::Event::Closed)
						window.close();
					//jezeli nacisnieto jakikolwiek przycisk
					if (event.type == sf::Event::KeyPressed)
					{//obsluga menu z poziomu klawiszy (strzalki)
						if (event.key.code == sf::Keyboard::Up)
						{
							myDelay(25);
							menu.przesunG();
						}
						if (event.key.code == sf::Keyboard::Down)
						{
							myDelay(25);
							menu.przesunD();
						}
						if (menu_selected_flag == 0)
						{//uruchamianie procedur na skutek wyboru menu (wybor poziomu menu to ENTER))
							if (event.key.code == sf::Keyboard::Enter &&
								menu.getSelectedItem() == 0)
							{
								std::cout << "Uruchamiam gre..." << std::endl;
								menu_selected_flag = 1;
								menu_gry = 1;
								window.clear();
								std::cout << "Uruchamiaaaaam gre..." <<
									std::endl;
								window.close();
								break;
							}
							if (event.key.code == sf::Keyboard::Enter &&
								menu.getSelectedItem() == 1)
							{
								std::cout << "Koniec gry..." << std::endl;
								menu_selected_flag = 1;
								exit = 1;
								break;
							}
							if (event.key.code == sf::Keyboard::Escape)
							{
								std::cout << "Koniec gry..." << std::endl;
								menu_selected_flag = 1;
								exit = 1;
								break;
							}
						}
					}
				}
				// wyczysc obszar rysowania
				window.clear();
				if (menu_selected_flag == 0)
					menu.draw(window);
				// ostatnia czynnosc - wyswietl okno wraz zawartoscia
				window.display();
			}
		}
		if (menu_gry == 1)
		{
			int ticks = 0;
			pilka gracze[100];
			pocisk pociski[200];
			// stworz okno
			sf::RenderWindow window(sf::VideoMode(800, 600), "GRA v.03");
			pilka p0;
			p0.givePilkaXY(400, 337.5);//stworz wie¿ê
			sf::Texture texture;
			texture.loadFromFile("textures/pngegg.png");
			p0.rectangle.setTexture(&texture);

			sf::Texture texture2;
			texture2.loadFromFile("textures/toppngcom-soldier-png.png");

			sf::Texture texture3;
			texture3.loadFromFile("textures/pngwing.com.png");

			sf::RectangleShape zamek, zamek2;
			zamek.setSize(sf::Vector2f(250, 100));
			zamek2.setSize(sf::Vector2f(250, 100));
			zamek.setPosition(550, 490);
			zamek2.setPosition(550, 90);

			sf::Texture texture4;
			texture4.loadFromFile("textures/pngwingcom.png");
			zamek.setTexture(&texture4);
			zamek2.setTexture(&texture4);


			sf::Text text;
			text.setFont(font);
			text.setFillColor(sf::Color::Black);
			text.setPosition(sf::Vector2f(50, 50));

			sf::Text text2;
			text2.setFont(font);
			text2.setFillColor(sf::Color::Black);
			text2.setPosition(sf::Vector2f(250, 50));

			sf::Text text3;
			text3.setFont(font);
			text3.setFillColor(sf::Color::Black);
			text3.setPosition(sf::Vector2f(500, 50));

			sf::Text exitText;
			exitText.setFont(font);
			exitText.setFillColor(sf::Color::Black);
			exitText.setPosition(sf::Vector2f(200, 400));
			exitText.setString("Czy napewno chcesz wyjsc?\nTAK [ENTER]         NIE [ESC]");

			sf::Text pomocText;
			pomocText.setFont(font);
			pomocText.setFillColor(sf::Color::Black);
			pomocText.setPosition(sf::Vector2f(150, 150));
			pomocText.setString("Sterowanie dzialem: Myszka\nStrzelanie z dziala: Lewy przycisk myszy\nPauza: P\nZmiana trybu szybkosci: 1-3\nZapis gry: F5\nOdczyt gry: F8\nPomoc: F1\nWyjscie: ESC");

			sf::Text pauzaText;
			pauzaText.setFont(font);
			pauzaText.setFillColor(sf::Color::Black);
			pauzaText.setPosition(sf::Vector2f(350, 150));
			pauzaText.setString("*PAUZA*");

			sf::ConvexShape convex;
			convex.setPointCount(5);
			convex.setFillColor(sf::Color::Red);
			convex.setPoint(0, sf::Vector2f(0, 0));
			convex.setPoint(1, sf::Vector2f(180, 10));
			convex.setPoint(2, sf::Vector2f(170, 50));
			convex.setPoint(3, sf::Vector2f(70, 55));
			convex.setPoint(4, sf::Vector2f(0, 50));
			convex.setPosition(sf::Vector2f(40, 40));

			int przeciwnicy = 0;
			int pociski_count = 0;

			sf::Clock zegar;//zegarek
			sf::Clock zegar2;//zegarek
			bool pause = 0;
			bool escape = 0;
			bool pomoc = 0;
			bool pausePause = 0;
			bool zapis = 0;
			bool odczyt = 0;
			int punkty = 0;
			int difficulty = 1;
			// okno widoczne, dopoki nie [x]
			while (window.isOpen() && exit == 0) {
				// petla sprawdzajace zdarzenia

				sf::Event event;
				while (window.pollEvent(event) && exit == 0) {//escape
					//jezeli nacisnieto jakikolwiek przycisk
					if (event.type == sf::Event::KeyPressed)
					{//obsluga menu z poziomu klawiszy (strzalki)
						if (event.key.code == sf::Keyboard::Escape && pomoc == 0 && pausePause == 0) {
							pause = !pause;
							escape = !escape;
							pomoc = 0;
						}
						if (event.key.code == sf::Keyboard::P && escape == 0 && pomoc == 0) {
							pause = !pause;
							pausePause = !pausePause;
							pomoc = 0;
							escape = 0;
						}
						if (event.key.code == sf::Keyboard::F1 && escape == 0 && pausePause == 0) {
							pause = !pause;
							pomoc = !pomoc;
							escape = 0;
						}
						if (event.key.code == sf::Keyboard::Enter) {
							if (escape == 1)
								exit = 1;
						}
						if (event.key.code == sf::Keyboard::F5) {
							zapis = 1;
						}
						if (event.key.code == sf::Keyboard::F8) {
							odczyt = 1;
						}
						if (event.key.code == sf::Keyboard::Num1) {
							difficulty = 1;
						}
						if (event.key.code == sf::Keyboard::Num2) {
							difficulty = 2;
						}
						if (event.key.code == sf::Keyboard::Num3) {
							difficulty = 3;
						}
					}
				}
				while (window.pollEvent(event))
				{
					// jezeli zdarzenie zamknij - zamykamy okno
					if (event.type == sf::Event::Closed)
						window.close();
				}

				sf::Vector2f pos, sss;
				pos.x = 1.5 * difficulty;
				pos.y = 0;

				sss.x = 0;
				sss.y = 0;
				if (zapis) {
					std::ofstream plik;
					plik.open("example.txt", std::ios::binary);
					plik.write((char*)(gracze), sizeof(pilka) * 100);
					plik.write((char*)(pociski), sizeof(pocisk) * 200);
					plik.close();
					zapis = 0;
				}
				if (odczyt) {
					pause = 1;
					std::ifstream plik;
					plik.open("example.txt", std::ios::binary);
					plik.read((char*)(gracze), sizeof(gracze) * 100);
					plik.read((char*)(pociski), sizeof(pociski) * 200);
					plik.close();
					odczyt = 0;
					pause = 0;
				}

				if (pause == 0) {
					p0.rectangle.setRotation(p0.GetRotationToMouse(&window, p0.rectangle));
					if (zegar2.getElapsedTime().asMilliseconds() > 380 && pociski_count < 200) {
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							pociski[pociski_count].givePociskXY(400, 337.5, p0.GetRotationToMouse(&window, p0.rectangle));
							pociski[pociski_count].rectangle.setTexture(&texture3);
							pociski[pociski_count].visible = 1;
							pociski_count++;
							zegar2.restart();
						}
					}

					//procedura animacji odswiezana co 33.3ms
					if (zegar.getElapsedTime().asMilliseconds() > 33.3f) {
						//sprawdz brzegi okna w poziomie
						for (int i = 0; i < przeciwnicy; i++) {
							if (gracze[i].visible == 1) {
								if (gracze[i].ball.getPosition().x > 600) {
									std::cout << "Koniec gry..." << std::endl;
									exit = 1;
									break;
								}
								for (int j = 0; j < difficulty; j++)
									gracze[i].ball.move(pos);
							}

						}
						for (int i = 0; i < pociski_count; i++) {
							pociski[i].ticksLeft -= 1;
							if (pociski[i].ticksLeft < 1) {
								pociski[i].rectangle.setPosition(sss);
								pociski[i].visible = 0;
								pociski[i].acceleration.x = 0;
								pociski[i].acceleration.y = 0;
							}
						}
						for (int i = 0; i < pociski_count; i++) {
							if (pociski[i].visible == 1) {
								pociski[i].rectangle.move(pociski[i].acceleration);
								for (int j = 0; j < przeciwnicy; j++) {
									if (sprawdzKolizje(&gracze[j], &pociski[i])) {
										pociski[i].rectangle.setPosition(sss);
										pociski[i].visible = 0;
										pociski[i].acceleration.x = 0;
										pociski[i].acceleration.y = 0;
										gracze[j].ball.setPosition(sss);
										gracze[j].visible = 0;
										punkty++;
									}
								}
							}
						}

						if (ticks >= 35) {
							if (przeciwnicy < 100) {
								if (przeciwnicy % 2 == 0) gracze[przeciwnicy].givePilkaXY(-50, 500);
								else gracze[przeciwnicy].givePilkaXY(-50, 100);

								gracze[przeciwnicy].ball.setTexture(&texture2);
								przeciwnicy++;
							}
							ticks = 0;
						}

						sf::Text mytext;
						std::stringstream ss;

						ss << "Pociski: " << 200 - pociski_count;
						text.setString(ss.str().c_str());
						ss.str("");
						ss << "Przeciwnicy: " << 100 - przeciwnicy;
						text2.setString(ss.str().c_str());
						ss.str("");
						ss << "Punkty: " << punkty;
						text3.setString(ss.str().c_str());
						ticks++;
						zegar.restart();
					}

				}
				//rysowanie z buforowaniem
				// czysci okno, wypelniajac kolorem
				window.clear(sf::Color::White);
				// procedura rysujaca poszczegolne obiekty w oknie
				// umieszcza obiekty w buforze

				if (pause) {
					if (escape)
						window.draw(exitText);
					if (pomoc)
						window.draw(pomocText);
					if (pausePause)
						window.draw(pauzaText);
				}
				else {
					window.draw(p0.getRect());
					window.draw(gracze[2].getRect());
					for (pilka ss : gracze)
						if (ss.visible == 1)
							window.draw(ss.getPilka());

					for (pocisk ss : pociski)
						if (ss.visible == 1)
							window.draw(ss.getRect());

					window.draw(zamek);
					window.draw(zamek2);
					// finalizacja - wyswietlenie elementow okna
					window.draw(convex);
					window.draw(text);
					window.draw(text2);
					window.draw(text3);
				}


				window.display();
			}
		}
	}
}