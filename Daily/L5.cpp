#include<iostream>
#include<SFML/Graphics.hpp>
#include<cmath>

float speedsolver(int pass[3][2]);

int main(){
    sf::RenderWindow win(sf::VideoMode(1800,800),"Gravity Mode");
    int Pos [3][2];
    bool stop = false;
    int i = 1, speed;
  
  //Texture
    sf::Texture texture;
    if(!texture.loadFromFile("res/1.png")){std::cout<<"Invalid file input\n";}
    sf::Sprite box(texture);
    box.setPosition(450,200);
    box.setOrigin(texture.getSize().x/2,texture.getSize().y/2);
    bool follow = false, action = false;


    while(win.isOpen()){
        sf::Event event;
        while(win.pollEvent(event)){

            if(event.type==sf::Event::Closed){
                win.close();
            }

            else if(event.type==sf::Event::MouseButtonPressed && event.type != sf::Event::MouseButtonReleased){
                follow = true;
            }
            else if(event.type==sf::Event::MouseButtonReleased && event.type!=sf::Event::MouseButtonPressed){
                for(int l = 0;l<3;l++){
                        for(int m = 0;m<2;m++){
                            std::cout<<Pos[l][m]<<"  "; //Printing Last three positions
                        }
                        std::cout<<"\n";
                    }
                    std::cout<<"\n";
                    speed = speedsolver(Pos);
                    action = true;
                follow = false;
            }

        } //pollEvent


        //Action (reaction)
        if(action==true){
            int momentum = speed * 0.5;
            box.move(momentum,0);
        }


        //To attain the Last three positions
        if(sf::Event::MouseMoved){
                int x = sf::Mouse::getPosition(win).x;
                int y = sf::Mouse::getPosition(win).y;

                    Pos[2][0] = Pos[1][0];//last position
                    Pos[2][1] = Pos[1][1];

                    Pos[1][0] = Pos[0][0];
                    Pos[1][1] = Pos[0][1];

                    Pos[0][0] = x;//first position
                    Pos[0][1] = y;
        }

        //follow
        if(follow==true){
            box.setPosition(sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y);
        }

        //wall on right side
        if(box.getPosition().x>(win.getSize().x-(texture.getSize().x/2))){
            action = false;
        }


        win.clear(sf::Color::Cyan);
        win.draw(box);
        win.display();
    }   //isOpen
}

//calculates the avg speed using three points
float speedsolver(int pass [3][2]){
    std::cout<<"\nSPEED = ";
    float horizontal = pass[0][0] - pass[1][0] + (pass[1][0] - pass[2][0]);
    std::cout<<horizontal<<"\n\n";
    float c;
    if(horizontal<25){c= 0.05;}
    if(horizontal>25&&horizontal<50){c=0.12;}
    if(horizontal>50&&horizontal<75){c=0.24;}
    if(horizontal>75&&horizontal<100){c=0.3;}
    if(horizontal>100&&horizontal<125){c=0.4;}
    if(horizontal>125&&horizontal<150){c=0.5;}
    if(horizontal>150&&horizontal<170){c=0.7;}
    if(horizontal>175&&horizontal<200){c=0.9;}
    if(horizontal>200){c=1.02;}
    return horizontal;
}
