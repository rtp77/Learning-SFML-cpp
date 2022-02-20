//PRESS SPACE TO BEGIN AND MOVE YOUR MOUSE
#include<iostream>
#include<SFML/Graphics.hpp>
#include<cmath>

float getSpeed(float h);

int main(){
    sf::RenderWindow win(sf::VideoMode(1200,800),"Space Run Game");

    //Creating a box
    sf::RectangleShape box(sf::Vector2f(20.f,20.0f));
    box.setFillColor(sf::Color::White);
    box.setPosition(450,400);
    box.setOrigin(box.getSize().x/2,box.getSize().y/2);

    bool action = false, temp = false;
    float speed = 0.15;
    int Px,Py,Bx,By; //position of Pointer(mouse) and box
    
    //Creating a line
    sf::RectangleShape line(sf::Vector2f(1,600));
    line.setPosition(20,20);
    line.setFillColor(sf::Color::White);


    while(win.isOpen()){
        sf::Event event;
        while(win.pollEvent(event)){
            //Close window
            if(event.type==sf::Event::Closed){
                win.close();
            }
            //Game Start
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    action = true;
            }
        }

        //Getting Positions of box and mouse
        Bx = box.getPosition().x;
        By = box.getPosition().y;
        Px = sf::Mouse::getPosition(win).x;
        Py = sf::Mouse::getPosition(win).y;


        //Wall boundary
        if(box.getPosition().x>=(win.getSize().x-10) or box.getPosition().x<(10)){
            action = false;
        }
        if(box.getPosition().y>=(win.getSize().y-10) or box.getPosition().y<(10)){
            action = false;
        }

        //Basic angles
        int Hx = Px, Hy = By,Vx = Bx,Vy = Py; //Horizontal and Vertical axis interms of Px and Py
        float horizontal;
        float vertical;
        float hypo=sqrt(horizontal*horizontal + vertical * vertical); //pythagoras
        float angle;

        //Line Drawing
        if(Hx<Bx and Vy>By){ //Quad I bottom left
            horizontal = Bx-Hx; //Horizontal length
            vertical = Vy-By; //Vertical length
            angle = (atan(horizontal/vertical)*180/3.1415); //angle using inverse sin
            line.setPosition(Bx,By); //origin position of the line
            line.setSize(sf::Vector2f(1,hypo)); // length of the line
            line.setRotation(angle);
            line.setFillColor(sf::Color::Yellow);
        }
        if(Hx<Bx and Vy<By){ //Quad II top left
            horizontal = Bx-Hx;
            vertical = By-Vy;
            float angle = (atan(horizontal/vertical)*180/3.1415);
            angle = 180-angle;
            line.setPosition(Bx,By);
            line.setSize(sf::Vector2f(1,hypo));
            line.setRotation(angle);
            line.setFillColor(sf::Color::Red);
        }
        if(Hx>Bx and Vy<By){ //Quad III top right
            horizontal = Hx-Bx;
            vertical = By-Vy;
            float angle = (atan(horizontal/vertical)*180/3.1415);
            angle = angle + 180;
            line.setPosition(Bx,By);
            line.setSize(sf::Vector2f(1,hypo));
            line.setRotation(angle);
            line.setFillColor(sf::Color::Green);
        }
        if(Hx>Bx and Vy>By){ //Quad IV bottom right
            horizontal = Hx-Bx;
            vertical = Vy-By;
            float angle = (atan(horizontal/vertical)*180/3.1415);
            angle = 360-angle;
            line.setPosition(Bx,By);
            line.setSize(sf::Vector2f(1,hypo));
            line.setRotation(angle);
            line.setFillColor(sf::Color::Blue);
        }

        //Setting up colors
        if(Bx%3==0){box.setFillColor(sf::Color::Blue);}
        if(Bx%4==0){box.setFillColor(sf::Color::Cyan);}
        if(Bx%5==0){box.setFillColor(sf::Color::Red);}
        if(Bx%6==0 or Bx%7==0){box.setFillColor(sf::Color::Yellow);}


        //Speed in terms of length
        speed = getSpeed(hypo); 


        //Reaction -Next update will feature proper movement of the box
        if(action == true){
            if(Bx>Px){
                box.move(-speed,0);
            }
            if (Bx<Px){
                box.move(speed,0);
            }
            if(By>Py){
                box.move(0,-speed);
            }
            if(By<Py){
                box.move(0,speed);
            }
        }

        win.clear(sf::Color::Black);
        win.draw(line);
        win.draw(box);
        win.display();
    }   //isOpen
}


float getSpeed(float h){
    float speed;
    if(h<60){speed = 0.15;}
    if(h>60 and h<100){speed = 0.23;}
    if(h>100 and h<200){speed = 0.28;}
    if(h>200 and h<300){speed = 0.34;}
    if(h>300 and h<400){speed = 0.38;}
    if(h>400 and h<500){speed = 0.43;}
    if(h>500 and h<600){speed = 0.48;}
    if(h>600 and h<700){speed = 0.55;}
    if(h>700){speed = 0.59;}
    return speed;
}




