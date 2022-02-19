#include<iostream>
#include<SFML/Graphics.hpp>
#include<cmath>

int main(){
    sf::RenderWindow win(sf::VideoMode(1200,800),"Space Run Game");

    sf::RectangleShape box(sf::Vector2f(40.0f,40.0f));
    box.setFillColor(sf::Color::White);
    box.setPosition(450,400);
    box.setOrigin(box.getSize().x/2,box.getSize().y/2);

    bool action = false;
    int gas = 1;
    float speed = 0.15;
    int Px,Py,Bx,By;


    while(win.isOpen()){
        sf::Event event;
        while(win.pollEvent(event)){

            if(event.type==sf::Event::Closed){
                win.close();
            }

            //Game Start
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    action = true;
            }

            //Gas Pedal
            if(event.type==sf::Event::MouseButtonPressed){
                if(event.key.code==sf::Mouse::Right){
                    if(gas>0&&gas<3){
                        gas++;
                        std::cout<<gas<<std::endl;
                    }
                }
                if(event.key.code==sf::Mouse::Left){
                    if(gas>1&&gas<4){
                        gas--;
                        std::cout<<gas<<std::endl;
                    }
                }
                switch(gas){
                case 1:
                    speed = 0.15;
                    break;
                case 2:
                    speed = 0.25;
                    break;
                case 3:
                    speed = 0.45;
                    break;
                }
            }
        }

        //Getting Positions
        Bx = box.getPosition().x;
        By = box.getPosition().y;
        Px = sf::Mouse::getPosition(win).x;
        Py = sf::Mouse::getPosition(win).y;

        //Wall
            if(box.getPosition().x>=(win.getSize().x-20) or box.getPosition().x<(20)){
                action = false;
            }
            if(box.getPosition().y>=(win.getSize().y-20) or box.getPosition().y<(20)){
                action = false;
            }

        //Reaction
        if(action == true){
            if(Bx>Px){
                box.move(speed,0);
            }
            if (Bx<Px){
                box.move(-speed,0);
            }
            if(By>Py){
                box.move(0,speed);
            }
            if(By<Py){
                box.move(0,-speed);
            }
        }

        win.clear(sf::Color::Black);
        win.draw(box);
        win.display();
    }   //isOpen
}





