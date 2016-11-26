#include <SFML/Graphics.hpp>

const int M=20;
const int N=10;

int field[M][N]={0};

struct Point
{int x, y;} a[4], b[4];

int figures[7][4]={
    1, 3, 5, 7, // I
    2, 4, 5, 7, // Z
    3, 4, 5, 6, // S
    3, 4, 5, 7, // T
    2, 4, 6, 7, // L
    3, 5, 6, 7, // J
    2, 3, 4, 5, // O
};

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "Retris");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("res/tiles.png"))
        return EXIT_FAILURE;

    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));

    int dx=0;
    bool rotate=0;
    int colorNum=1;
    float timer=0;
    float delay=0.3;

    sf::Clock clock;

	// Start the game loop
    while (app.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                app.close();

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Up) rotate = true;
                else if (event.key.code == sf::Keyboard::Left) dx = -1;
                else if (event.key.code == sf::Keyboard::Right) dx = 1;
        }

        // Movement
        for(int i=0; i<4; i++)
            a[i].x += dx;

        // Rotation
        if (rotate)
        {
            Point p = a[1];
            for(int i=0; i<4; i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;

                a[i].x = p.x - x;
                a[i].y = p.y - y;
            }
        }

        // Tick
        if(timer > delay)
        {
            for(int i=0; i<4; i++)
                a[i].y += 1;
            timer = 0;
        }

        int n=3;
        if(a[0].x == 0)
        for(int i=0; i<4; i++)
        {
            a[i].x = figures[n][i] % 2;
            a[i].y = figures[n][i] / 2;
        }

        dx = 0;
        rotate = 0;

        // Clear screen
        app.clear(sf::Color::White);

        for(int i=0; i<4; i++)
        {
            sprite.setPosition(a[i].x * 18, a[i].y * 18);

            // Draw the sprite
            app.draw(sprite);
        }

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
