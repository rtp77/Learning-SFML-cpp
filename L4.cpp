#include<iostream>
#include<SFML/Graphics.hpp>
int main(int argc, char** argv[]){
    sf::RenderWindow window(sf::VideoMode(800,600),"Custom Window");
    float width = window.getSize().x, height = window.getSize().y;
    bool ready = false;
    
    //draw start box
    sf::RectangleShape startBox(sf::Vector2f(50,50));
    startBox.setPosition(0,height/2);
    startBox.setOrigin(0,startBox.getSize().y/2);
    startBox.setFillColor(sf::Color::Blue);
    //draw end box
    sf::RectangleShape endBox(sf::Vector2f(50,50));
    endBox.setPosition(width-endBox.getSize().y,height/2);
    endBox.setOrigin(0,endBox.getSize().y/2);
    endBox.setFillColor(sf::Color::Blue);
    //draw the wire
    sf::RectangleShape rec(sf::Vector2f(1000,20));
    rec.setOrigin(0,rec.getSize().y/2);
    rec.setPosition(0,window.getSize().y / 2);
    rec.setFillColor(sf::Color::Green);

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                window.close();
            }
            else if(event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button==sf::Mouse::Left){
                            //To check if cursor is over the box
                                if(sf::Mouse::getPosition(window).x<startBox.getSize().x){
                                    if(sf::Mouse::getPosition(window).y>(height/2-25) && sf::Mouse::getPosition(window).y<(height/2+25)){
                                                                ready=true;
                                                                std::cout<<"Game Started\n\n"<<std::endl;
                                    }
                                }
                                if(sf::Mouse::getPosition(window).x>(width-endBox.getSize().y)){
                                    if(sf::Mouse::getPosition(window).y>(height/2-25) && sf::Mouse::getPosition(window).y<(height/2+25)){
                                                                window.close();
                                                                std::cout<<"You have won the game, Congratulations !!"<<std::endl;
                                    }
                                }
                    }//LeftButtonpress
            }
            else if(ready == true){
                if(event.type==sf::Event::MouseMoved){
                        float pos = sf::Mouse::getPosition(window).y;
                        if(pos>(rec.getPosition().y+rec.getSize().y/2) or pos<(rec.getPosition().y-rec.getSize().y/2)){
                            window.close();
                            std::cout<<"Well Nice Play, Try again you can do it !!"<<std::endl;
                        }
                }
            }
        }//pollEvent
        window.clear(sf::Color::Red);
        window.draw(rec);
        window.draw(startBox);
        window.draw(endBox);
        window.display();
    }//isopen
}
///NEXT UP TRY 
///TIMER FOR SCORE COUNTING, AND IMPLEMENTATION OF AUDIO   
