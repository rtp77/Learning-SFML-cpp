//ImGui window updated to change the color of the light source using (R,G,B)


#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "imgui.h"
#include "imgui-SFML.h"

const int width = 1500;
const int height = 1000;

bool isIn(int xPos, int yPos) {
    return xPos >= 0 && xPos < width && yPos >= 0 && yPos < height;
}

int main() {
    // Setup window
    sf::RenderWindow window(sf::VideoMode(width, height), "Dynamic Lighting - Press [Space] to close");
    window.setVerticalSyncEnabled(true);

    // Setup ImGui
    ImGui::SFML::Init(window);

    // Background image setup
    sf::Image image;
    image.create(width, height, sf::Color::Black);
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);

    // Light parameters
    int lightIntensity = 3000; // How far the light reaches
    int brightness = 250; // Strength of the light
    int halfIntensity = lightIntensity / 2; // Radius of how far light reaches
    int red = 255, green = 255, blue = 255;

    // Precompute light intensity data
    std::vector<std::vector<int>> lightCollectionData(lightIntensity, std::vector<int>(lightIntensity, 0));
    for (int i = 0; i < lightIntensity; ++i) {
        for (int j = 0; j < lightIntensity; ++j) {
            int dx = i - halfIntensity;
            int dy = j - halfIntensity;
            if (dx * dx + dy * dy <= halfIntensity * halfIntensity) {
                float pixelDistance = std::sqrt(dx * dx + dy * dy);
                float normalDistance = pixelDistance / halfIntensity;
                float intensity = 1.0f - normalDistance;
                lightCollectionData[i][j] = static_cast<int>(brightness * intensity);
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                window.close();
        }

        // Start ImGui frame
        ImGui::SFML::Update(window, sf::seconds(1.f / 60.f));

        // ImGui UI Setup
        ImGui::Begin("Light Settings");
        ImGui::SliderInt("Red", &red, 0, 255);
        ImGui::SliderInt("Green", &green, 0, 255);
        ImGui::SliderInt("Blue", &blue, 0, 255);
        ImGui::End();

        // Light movement based on mouse position
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int lightx1 = mousePos.x - halfIntensity;
        int lighty1 = mousePos.y - halfIntensity;

        // Update image with lighting effect
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                image.setPixel(i, j, sf::Color::Black); // Reset to background color

                int localX = i - lightx1;
                int localY = j - lighty1;

                if (localX >= 0 && localX < lightIntensity && localY >= 0 && localY < lightIntensity) {
                    int intensity = lightCollectionData[localX][localY];
                    sf::Color pixelColor = sf::Color(
                        std::min(red * intensity / 255, 255),
                        std::min(green * intensity / 255, 255),
                        std::min(blue * intensity / 255, 255),
                        255
                    );
                    if (isIn(i, j)) {
                        image.setPixel(i, j, pixelColor); // Apply lighting
                    }
                }
            }
        }

        // Rendering
        texture.update(image);
        window.clear();
        window.draw(sprite);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
