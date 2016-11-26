#include <SFML/Graphics.hpp>

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "Retris");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("res/cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                app.close();
        }

        // Clear screen
        app.clear(sf::Color::White);

        // Draw the sprite
        app.draw(sprite);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
