//'Light2' follows 'Light1' with some additional improvements
// IMPROVEMENT 1 : Light illumination data is preallocated outside of the Event loop
// IMPROVEMENT 2 : Reduced TIME COMPLEXITY from merging two seperate nested for loops (refresh and light) (On^2)

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int width{ 1500 }, height{ 1000 };

// This function checks if the coordinates are within the window bounds
bool isIn(int xPos, int yPos) {
    return xPos >= 0 && xPos < width && yPos >= 0 && yPos < height;
}

int main()
{
    // Setup Window
    sf::RenderWindow window(sf::VideoMode(width, height), "Light   ----   To close Press [ Space ]");
    window.setVerticalSyncEnabled(true);

    // Display Background Image setup
    sf::Image image;
    image.create(width, height, sf::Color::Black);
    sf::Texture texture;
    texture.loadFromImage(image); // Load the image data into the texture
    sf::Sprite sprite;
    sprite.setTexture(texture); // Set the texture to the sprite

    // Variables
    const int lightIntensity = 3000; // How far the light reaches
    int brightness = 250; // Strength of the light
    int halfIntensity = lightIntensity / 2; // Radius of how far light reaches
    sf::Color colorBG = sf::Color::Black;

    // Light Collection Data - using dynamic allocation with std::vector
    std::vector<std::vector<int>> lightCollectionData(lightIntensity, std::vector<int>(lightIntensity, 0));
    int px = halfIntensity, py = halfIntensity;
    for (int i = 0; i < lightIntensity; i++) {
        for (int j = 0; j < lightIntensity; j++) {
            if ((i - px) * (i - px) + (j - py) * (j - py) <= halfIntensity * halfIntensity) {
                float pixelDistance = sqrt((abs(px - i)) * (abs(px - i)) + (abs(py - j)) * (abs(py - j))); // Distance from the light source
                float normalDistance = pixelDistance / halfIntensity; // Linear distribution of the Distance
                float intensity = 1.0f - normalDistance; // Intensity (0-1)f to be multiplied with brightness
                //if (intensity < 0.999f) { intensity *= 0.5f; } // Brighter radius of light around source

                lightCollectionData[i][j] = brightness * intensity;
            }
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // To close game window Press [ Space ]
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                window.close();
        }

        // Movement of Light
        int mx = sf::Mouse::getPosition(window).x;
        int my = sf::Mouse::getPosition(window).y;

        int lightx1 = mx - halfIntensity;
        int lighty1 = my - halfIntensity;
        int lightx2 = mx + halfIntensity;
        int lighty2 = my + halfIntensity;

        // Screen Refresh and Light Application in a Single Loop
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                // Refresh Color and Background
                image.setPixel(i, j, colorBG);

                // Apply Light Effect
                int localX = i - lightx1;
                int localY = j - lighty1;
                if (localX >= 0 && localX < lightIntensity && localY >= 0 && localY < lightIntensity) {
                    int c = lightCollectionData[localX][localY];
                    sf::Color pixelColor = sf::Color(c, c, c, 255);
                    if (isIn(i, j)) {
                        image.setPixel(i, j, pixelColor); // Set pixel color
                    }
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
