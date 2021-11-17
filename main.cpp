/*
Temat projektu: Gra bitwa morska
Gracz wciela siê w kapitana statku 
aaaaa

*/
#define MAX_LICZBA_POZIOMOW 3
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <random>
#include <cmath>

class pilka {
private:
	sf::Vector2f position;//wspolrzedne
public:
	sf::CircleShape ball;//pilka
	pilka(float x_in, float y_in);//tworz pilke w polozeniu (x,y)
	void przesun(float x_in, float y_in);//przesun pilke
	sf::CircleShape getPilka() { return ball; }//zwroc pilke	
	sf::Vector2f getPos() { return ball.getPosition(); }
};
pilka::pilka(float x_in, float y_in)
{
	position.x = x_in;
	position.y = y_in;
	//kolo o promieniu 10px
	ball.setRadius(20);
	ball.setFillColor(sf::Color(150, 50, 250));
	// obramowka kola o grubosci 2px
	ball.setOutlineThickness(2);
	ball.setOutlineColor(sf::Color(250, 150, 100));
	ball.setPosition(position);//pozycja poczatkowa
}
void pilka::przesun(float x_in, float y_in)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	ball.move(pos);
}
void sprawdzKolizje(pilka& p1, pilka& p2, pilka& p3, pilka& p4, pilka& p5, pilka& p6, int dx, int dy) {
	p1.przesun(dx, dy);
	sf::FloatRect intersection;
	if (p1.ball.getGlobalBounds().intersects(p2.ball.getGlobalBounds(), intersection)) {
		p1.przesun(-dx, -dy);
	}
	else if (p1.ball.getGlobalBounds().intersects(p3.ball.getGlobalBounds(), intersection)) {
		p1.przesun(-dx, -dy);
	}
	else if (p1.ball.getGlobalBounds().intersects(p4.ball.getGlobalBounds(), intersection)) {
		p1.przesun(-dx, -dy);
	}
	else if (p1.ball.getGlobalBounds().intersects(p5.ball.getGlobalBounds(), intersection)) {
		p1.przesun(-dx, -dy);
	}
	else if (p1.ball.getGlobalBounds().intersects(p6.ball.getGlobalBounds(), intersection)) {
		p1.przesun(-dx, -dy);
	}


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
		if (menu_gry == 1)
		{
			int tab[5][3];
			for (int i = 0; i < 5; i++)
			{
				tab[i][0] = i;
			}
			//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			//std::default_random_engine generator(seed);
			//std::uniform_int_distribution<int> distributionInteger(1, 100);
			for (int i = 0; i < 5; i++)
			{
				std::random_device dev;
				std::mt19937 rng(dev());
				std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 760);
				tab[i][1] = dist6(rng);
				std::cout << "p" << i + 1 << " x: " << tab[i][1] << std::endl;
			}
			//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			//std::default_random_engine generator(seed);
			//std::uniform_int_distribution<int> distributionInteger(1, 100);
			for (int i = 0; i < 5; i++)
			{
				std::random_device dev;
				std::mt19937 rng(dev());
				std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 560);
				tab[i][2] = dist6(rng);
				std::cout << "p" << i + 1 << " y: " << tab[i][2] << std::endl;
			}
			// stworz okno
			sf::RenderWindow window(sf::VideoMode(800, 600), "GRA v.01");
			pilka p2(tab[0][1], tab[0][2]);//stworz pilke
			pilka p3(tab[1][1], tab[1][2]);//stworz pilke
			pilka p4(tab[2][1], tab[2][2]);//stworz pilke
			pilka p5(tab[3][1], tab[3][2]);//stworz pilke
			pilka p6(tab[4][1], tab[4][2]);//stworz pilke
			pilka p1(400, 300);//stworz pilke
			int x = 0, y = 0;//pozycja pilki
			int dx = 3, dy = 3;//kierunek x, kierunek y
			sf::Clock zegar;//zegarek
			// okno widoczne, dopoki nie [x]
			while (window.isOpen() && exit == 0)
			{
				// petla sprawdzajace zdarzenia
				sf::Event event;
				while (window.pollEvent(event) && exit == 0)
				{
					//jezeli nacisnieto jakikolwiek przycisk
					if (event.type == sf::Event::KeyPressed)
					{//obsluga menu z poziomu klawiszy (strzalki)
						if (event.key.code == sf::Keyboard::Escape)
						{
							std::cout << "Koniec gry..." << std::endl;
							exit = 1;
							break;
						}
					}
				}
				while (window.pollEvent(event))
				{
					// jezeli zdarzenie zamknij - zamykamy okno
					if (event.type == sf::Event::Closed)
						window.close();
				}
				//procedura animacji odswiezana co 33.3ms
				if (zegar.getElapsedTime().asMilliseconds() > 33.3f) {
					//sprawdz brzegi okna w poziomie
					if (p1.getPos().x < 10)
						p1.przesun(dx, 0);
					if (p1.getPos().x > window.getSize().x - 50)
						p1.przesun(-dx, 0);

					if (p1.getPos().y < 10)
						p1.przesun(0, dy);
					if (p1.getPos().y > window.getSize().y - 50)
						p1.przesun(0, -dy);

					if (event.type == sf::Event::KeyPressed)
					{
						if (event.key.code == sf::Keyboard::W)
						{
							sprawdzKolizje(p1, p2, p3, p4, p5, p6, 0, -dy);
						}
						if (event.key.code == sf::Keyboard::S)
						{
							sprawdzKolizje(p1, p2, p3, p4, p5, p6, 0, dy);
						}
						if (event.key.code == sf::Keyboard::A)
						{
							sprawdzKolizje(p1, p2, p3, p4, p5, p6, -dx, 0);
						}
						if (event.key.code == sf::Keyboard::D)
						{
							sprawdzKolizje(p1, p2, p3, p4, p5, p6, dx, 0);
						}
					}
					//p1.przesun(dx, dy);
					zegar.restart();
					std::cout << "rozmiar okna: " << window.getSize().x << ", " << window.getSize().y << std::endl;
					std::cout << "x = " << p1.getPos().x << "y= " << p1.getPos().y << std::endl;
				}
				//rysowanie z buforowaniem
				// czysci okno, wypelniajac kolorem
				window.clear(sf::Color::White);
				// procedura rysujaca poszczegolne obiekty w oknie
				// umieszcza obiekty w buforze
				// window.draw(...);
				window.draw(p1.getPilka());
				window.draw(p2.getPilka());
				window.draw(p3.getPilka());
				window.draw(p4.getPilka());
				window.draw(p5.getPilka());
				window.draw(p6.getPilka());
				// finalizacja - wyswietlenie elementow okna
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