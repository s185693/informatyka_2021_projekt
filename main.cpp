#define MAX_LICZBA_POZIOMOW 3
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <random>
#include <cmath>

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
{	//laduj czcionke
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
	menu[1].setString("Pomoc");
	menu[1].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 2));
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Wyjscie");
	menu[2].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 3));
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
//funklcja opozniajaca
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
class Menu2
{

private:
	sf::Font font;
	sf::Text menu[MAX_LICZBA_POZIOMOW];//maksymalna liczba poziomow
	int selectedItem = 0;


public:
	Menu2(float width, float height);
	~Menu2() {};
	int getSelectedItem() { return selectedItem; }//zwroc poziom menu
	void draw(sf::RenderWindow& window);//rysuj menu w oknie
};
Menu2::Menu2(float width, float height)
{	//laduj czcionke
	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}
	//rysowanie elementow menu2
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::White);
	menu[0].setString("Poruszaj sie klawiszem Alt + W,A,S,D");
	menu[0].setPosition(sf::Vector2f(width / 4, height / (MAX_LICZBA_POZIOMOW + 1) * 1));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Aby wyjsc wcisnij ESC");
	menu[1].setPosition(sf::Vector2f(width / 4, height / (MAX_LICZBA_POZIOMOW + 1) * 2));
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Aby powrocic wcisnij ENTER");
	menu[2].setPosition(sf::Vector2f(width / 4, height / (MAX_LICZBA_POZIOMOW + 1) * 3));
}
//rysowanie menu w biezacym oknie
void Menu2::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
	{
		window.draw(menu[i]);
	}
}

int main()
{
	std::cout << "helo world";
	int menu_gry = 0;
	int exit = 0;
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
							myDelay(250);
							menu.przesunG();
						}
						if (event.key.code == sf::Keyboard::Down)
						{
							myDelay(250);
							menu.przesunD();
						}
						if (menu_selected_flag == 0)
						{//uruchamianie procedur na skutek wyboru menu (wybor poziomu menu to ENTER))
							if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
							{
								std::cout << "Uruchamiam gre..." << std::endl;
								menu_selected_flag = 1;
								menu_gry = 1;
								window.clear();
								std::cout << "Uruchamiaaaaam gre..." << std::endl;
								window.close();
								break;
							}
							if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
							{
								std::cout << "Pomoc" << std::endl;
								menu_selected_flag = 1;
								menu_gry = 2;
								window.clear();
								std::cout << "Otwieram pomoc..." << std::endl;
								window.close();
								break;
							}
							if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
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
		if (menu_gry == 2) {
			int menu_selected_flag = 0;
			sf::RenderWindow window(sf::VideoMode(800, 600), "Pomoc");// utworz okno
			Menu2 menu2(window.getSize().x, window.getSize().y);
			// petla wieczna - dopoki okno jest otwarte
			while (window.isOpen() && exit == 0)
			{
				// w kazdej iteracji petli sprawdzaj zdarzenia
				sf::Event event;
				while (window.pollEvent(event) && exit == 0)
				{
					//jezeli nacisnieto jakikolwiek przycisk
					if (event.type == sf::Event::KeyPressed)
					{//obsluga menu z poziomu klawiszy (strzalki)
						if (event.key.code == sf::Keyboard::Enter)
						{
							std::cout << "Uruchamiam gre..." << std::endl;
							menu_selected_flag = 1;
							menu_gry = 0;
							window.clear();
							std::cout << "Powracam do MENU" << std::endl;
							window.close();
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
				// wyczysc obszar rysowania
				window.clear();
				if (menu_selected_flag == 0)
					menu2.draw(window);
				// ostatnia czynnosc - wyswietl okno wraz zawartoscia
				window.display();
			}
		}
	}
}
