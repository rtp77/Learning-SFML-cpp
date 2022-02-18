#include<SFML/Graphics.hpp>
#include<iostream>
int main(int argc, char** argv[]) {
	sf::RenderWindow window(sf::VideoMode(400, 240), "New Window Created");
	int temp = 0, a = 0;
	int s = 0;
	sf::RectangleShape recta(sf::Vector2f(100.0f, 240.0f));  
	recta.setFillColor(sf::Color::Blue);
	recta.setPosition(s, 0);  //s assigns the x position on the screen
	sf::RectangleShape rectb(sf::Vector2f(100.0f, 240.0f));
	rectb.setFillColor(sf::Color::Green);
	rectb.setPosition(s + 100, 0);  //s + 100 avoids overlapping of shapes
	sf::RectangleShape rectc(sf::Vector2f(100.0f, 240.0f));
	rectc.setFillColor(sf::Color::Yellow);
	rectc.setPosition(s + 200, 0);
	sf::RectangleShape rectd(sf::Vector2f(100.0f, 240.0f));
	rectd.setFillColor(sf::Color::Black);
	rectd.setPosition(s + 300, 0);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					temp = sf::Mouse::getPosition(window).x / 100 + 1; //To ratio the x axis of screen
					switch (temp) {
					case 1:
						std::cout << "Blue" << std::endl;
						break;
					case 2:
						std::cout << "Green" << std::endl;
						break;
					case 3:
						std::cout << "Yellow" << std::endl;
						break;
					case 4:
						std::cout << "Black" << std::endl;
						break;
					deafult:
						std::cout << "Wrong Input" << std::endl;
					}

					}
			}
			
		}//poll event
		window.clear(sf::Color::Cyan); //To clear the screen
		window.draw(recta); //To draw each of the shapes
		window.draw(rectb);
		window.draw(rectc);
		window.draw(rectd);
		window.display();
	}//is open
}
