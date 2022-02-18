#include<iostream>
#include<SFML/Graphics.hpp>

void main(int argc, char** argv[]) {

	//Window Setup
	sf::RenderWindow win(sf::VideoMode(800, 360), "Second Try");
	std::cout << "STOP WATCH" << std::endl;
	std::cout << "Tap on []Green to Start []Blue to Pause []Red to reset\n" << std::endl;
	float xx = win.getSize().x / 6; //Space Evenly between them
	float yy = win.getSize().y / 2;

	sf::RectangleShape StartButton(sf::Vector2f(200.0f, 100.0f));
	sf::RectangleShape StopButton(sf::Vector2f(200.0f, 100.0f));
	sf::RectangleShape ResetButton(sf::Vector2f(200.0f, 100.0f));

	float midx = StartButton.getSize().x / 2; //To set Origin
	float midy = StartButton.getSize().y / 2;

	StartButton.setOrigin(midx, midy);
	StartButton.setPosition(xx, yy);
	StopButton.setOrigin(midx, midy);
	StopButton.setPosition(3 * xx, yy);
	ResetButton.setOrigin(midx, midy);
	ResetButton.setPosition(5 * xx, yy);

	StartButton.setFillColor(sf::Color::Green);
	StopButton.setFillColor(sf::Color::Blue);
	ResetButton.setFillColor(sf::Color::Red);

	//Clock Setup
	sf::Clock clock;
	sf::Time t = clock.getElapsedTime();
	sf::Time exchange;
	sf::Clock zeroclock;
	sf::Time zero = zeroclock.getElapsedTime();
	bool firstinstance = true;

	while (win.isOpen()) {
		sf::Event event;
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				win.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					if (sf::Mouse::getPosition(win).y > (yy - midy) && sf::Mouse::getPosition(win).y < (yy + midy)) {
						// Start Button
						if (sf::Mouse::getPosition(win).x > (xx - midx) && sf::Mouse::getPosition(win).x < (xx + midx)) {
							if (firstinstance == true) {
								sf::Clock clock;
								sf::Time t = clock.getElapsedTime();
								std::cout << "Started : \n" << t.asSeconds();
								std::cout << "\n\n";
							}
							else if (firstinstance != true) {
								std::cout << "Continued : \n" << exchange.asSeconds();
								t = exchange;
								std::cout << "\n\n";
							}
						}
						// Pause Button
						else if (sf::Mouse::getPosition(win).x > (3 * xx - midx) && sf::Mouse::getPosition(win).x < (3 * xx + midx)) {
							sf::Time t = clock.getElapsedTime();
							std::cout << "Paused : \n" << t.asSeconds() << std::endl;
							exchange = t;
							std::cout << "\n";
							firstinstance = false;
						}
						// End Button
						else if (sf::Mouse::getPosition(win).x > (5 * xx - midx) && sf::Mouse::getPosition(win).x < (5 * xx + midx)) {
							std::cout << "Reset : \n" << exchange.asSeconds() << "\n" << std::endl;
							t = zero;
							exchange = zero;
							clock.restart();
						}
					}
				}
			}
		}//pollevent
		win.clear(sf::Color::Cyan);
		win.draw(StartButton);
		win.draw(StopButton);
		win.draw(ResetButton);
		win.display();
	}//IsOpen
}
