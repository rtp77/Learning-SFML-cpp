//This is a personal project written in C++ using libraries SFML and graphics API OpenGL
//The first file 'Light1' is written using no prior knowledge of lighting methods in graphics programming. 
//It is an attempt to interact and experiment my own lighting methods and compare it to established methods later on.

// 'Light1'  manages lighting using a linear distribution of color from lightest shade rgb (255,255,255) upto darkest shade rbg (0,0,0)

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

int width{1500}, height{1000};    //window height and width

//This function overrides the setpixel error if code setspixel outside of window bounds
bool isIn(int xPos, int yPos) {
    if (xPos > 0 and xPos < width) {
        if (yPos > 0 and yPos < height) {
            return true;
        }
    }
    else {
        return false;
    }
}

//This function clears pixels drawn every loop event
//Light is drawn by changing the pixel color every frame
sf::Image refreshScreen(sf::Image ig) {
    //Refresh Image
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            ig.setPixel(i, j, sf::Color::Black);  //Blackbackground for now
        }
    }
    return ig;
}

//   MAIN FUNCTION  //
int main()
{
    // Setup Window
    sf::RenderWindow window(sf::VideoMode(width, height), "Light   ----   To close Press [ Space ]");
    window.setVerticalSyncEnabled(true);
    bool isFS = true;          //For fullscreenmode to be setup late
    
    //Display Background Image setup
    int px{ 0 }, py{ 0 };
    sf::Image image;
    image.create(width, height, sf::Color::Black);
    sf::Texture texture;
    texture.loadFromImage(image); // Load the image data into the texture
    sf::Sprite sprite;
    sprite.setTexture(texture); // Set the texture to the sprite

    //Variables
    int lightIntensity = 2500;  //How far the light reaches
    int brightness = 250;       //Strength of the light
    int brightnessToggle = 255; //Variable to toggle the light strength
    int halfIntensity = 1;      //Radius of how far light reaches (lightIntensity/2)

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //To close game window Press [ Space ]
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                window.close();
        }//MAIN CODE UNDER

        //Refresh Code
        image = refreshScreen(image);

        //Toggle the Brightness
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) { brightness = brightness - 10; std::cout << brightness << std::endl; }

        //Movement of Light
        px=sf::Mouse::getPosition(window).x, py=sf::Mouse::getPosition(window).y;

        //Light fn
        halfIntensity = lightIntensity / 2;
        sf::Color pixelColor = sf::Color::Black;                                                     //Setting up of pixel color, to be altered in the code
        for (int i = (px - halfIntensity); i < (px + halfIntensity); i++) {                          //Loop to set up a sqare working grid around the light source
            for (int j = (py - halfIntensity); j < (py + halfIntensity); j++) {
                if ((i - px) * (i - px) + (j - py) * (j - py) <= halfIntensity * halfIntensity)      //Loop to set up a circle working grid inside the square
                {


                    float pixelDistance = sqrt((abs(px - i)) * (abs(px - i)) + (abs(py - j)) * (abs(py - j)));          //Distance from the light source
                    float normalDistance = pixelDistance / halfIntensity;                                               //Linear distribution of the Distance
                    float intensity = 1.0f - normalDistance;                                                            //Intensity (0-1)f to be multiplied with brightness
                    if (intensity < 0.99f) { intensity = intensity*0.5; }                                               //Brighter radius of light around source

                    sf::Color pixelColor = sf::Color(brightness * intensity, brightness * intensity, brightness * intensity, 255);

                    if (isIn(i, j) == true) { image.setPixel(i, j, pixelColor); }

                }
            }
        }

        window.clear();
        texture.update(image);
        window.draw(sprite);
        window.display();

    }

    return 0;
}
