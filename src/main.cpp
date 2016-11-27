#include <SFML/Graphics.hpp>
#include <time.h>
#include "settings.hpp"

// Game field
int field[M][N]={0};

// Active figure
struct Point
{int x, y;} a[4], b[4];

// Figures list
int figures[7][4]={
    1, 3, 5, 7, // I
    2, 4, 5, 7, // Z
    3, 4, 5, 6, // S
    3, 4, 5, 7, // T
    2, 4, 6, 7, // L
    3, 5, 6, 7, // J
    2, 3, 4, 5, // O
};

// Check if figure points intersect box or other figure
bool check()
{
    for(int i=0; i<4; i++)
        if(a[i].x < 0 || a[i].x >= N || a[i].y >= M)
            return 0;
        else if(field[a[i].y][a[i].x])
            return 0;

    return 1;
}

int main()
{
    srand(time(0));

    // Create the main window
    sf::RenderWindow app(sf::VideoMode(winSize[0], winSize[1]), gameTitle);

    // Load a sprite to display
    int backgroundId = rand() % backgroundsCount;

    sf::Texture tBackground;
    if (!tBackground.loadFromFile(backgrounds[backgroundId]))
        return EXIT_FAILURE;
    sf::Sprite sBackground(tBackground);

    sf::Texture tInterface;
    if (!tInterface.loadFromFile(interface))
        return EXIT_FAILURE;
    sf::Sprite sInterface(tInterface);

    sf::Texture tTiles;
    if (!tTiles.loadFromFile("res/tiles.png"))
        return EXIT_FAILURE;
    sf::Sprite sTiles(tTiles);

    sTiles.setTextureRect(sf::IntRect(0, 0, pointSize[0], pointSize[1]));

    // Initialize
    int dx = 0;
    bool rotate = 0;
    int colorNum = 1 + rand() % 7;

    // Clock
    float timer = 0;
    float delay = 0.3;
    sf::Clock clock;

    // Change figure ID
    int n = rand() % 7;
    if(a[0].x == 0)
        for(int i=0; i<4; i++)
        {
            a[i].x = figures[n][i] % 2;
            a[i].y = figures[n][i] / 2;
        }

    // Clear screen
    //app.clear(sf::Color::White);
    app.draw(sBackground);

    while (app.isOpen())
    {
        // Updating timer
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                app.close();

            // Key events
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Up) rotate = true;
                else if (event.key.code == sf::Keyboard::Left) dx = -1;
                else if (event.key.code == sf::Keyboard::Right) dx = 1;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            delay = 0.05;

        // Movement
        for(int i=0; i<4; i++)
        {
            b[i] = a[i];
            a[i].x += dx;
        }

        if(!check())
            for(int i=0; i<4; i++)
                a[i] = b[i];

        // Rotation
        if (rotate)
        {
            Point p = a[1];
            for(int i=0; i<4; i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;

                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }

            if(!check())
                for(int i=0; i<4; i++)
                    a[i] = b[i];
        }

        // Tick
        if(timer > delay)
        {
            for(int i=0; i<4; i++)
            {
                b[i] = a[i];
                a[i].y += 1;
            }

            if(!check())
            {
                for(int i=0; i<4; i++)
                    field[b[i].y][b[i].x] = colorNum;

                colorNum = 1 + rand() % 7;
                int n = rand() % 7;
                for(int i=0; i<4; i++)
                {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            }

            timer = 0;
        }

        // Check lines
        int k = M - 1;
        for(int i=M - 1; i > 0; i--)
        {
            int count=0;
            for(int j=0; j<N; j++)
            {
                if(field[i][j])
                    count++;
                field[k][j] = field[i][j];
            }
            if(count < N)
               k--;
        }

        dx = 0;
        rotate = 0;
        delay = 0.3;

        app.draw(sInterface);

        // Draw field
        for(int i=0; i<boxSize[1]; i++)
            for(int j=0; j<boxSize[0]; j++)
            {
                if(field[i][j] == 0)
                    continue;

                sTiles.setTextureRect(sf::IntRect(field[i][j] * pointSize[0], 0, pointSize[0], pointSize[1]));
                sTiles.setPosition(j * pointSize[0], i * pointSize[1]);
                sTiles.move(boxPosition[0], boxPosition[1]);
                app.draw(sTiles);
            }

        // Draw the sprite
        for(int i=0; i<4; i++)
        {
            sTiles.setTextureRect(sf::IntRect(colorNum * pointSize[0], 0, pointSize[0], pointSize[1]));
            sTiles.setPosition(a[i].x * pointSize[0], a[i].y * pointSize[1]);
            sTiles.move(boxPosition[0], boxPosition[1]);
            app.draw(sTiles);
        }

        app.display();
    }

    return EXIT_SUCCESS;
}
