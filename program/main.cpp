#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
    RenderWindow window(VideoMode(500,500), "SFML works!");
    //CircleShape shape(100.0f);

    // Load a texture from a PNG file
    Texture texture;
    if (!texture.loadFromFile("../assets/players/img_64.png")) {
        return EXIT_FAILURE;
    }

    Sprite sprite;
    sprite.setTexture(texture);

    sprite.setPosition(200,100);

    // Main loop
    while (window.isOpen()) {

        // Handle events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // Clear the window
        window.clear();
        //window.draw(shape);

        // Draw the sprite
        window.draw(sprite);

        // Display the contents of the window
        window.display();
    }

    return EXIT_SUCCESS;
}