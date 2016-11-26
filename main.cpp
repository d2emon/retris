#include <SFML/Graphics.hpp>
#include <time.h>

const int M=20;
const int N=10;

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
    sf::RenderWindow app(sf::VideoMode(800, 600), "Retris");

    // Load a sprite to display
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;

    if (!texture1.loadFromFile("res/tiles.png"))
        return EXIT_FAILURE;
    if (!texture2.loadFromFile("res/background.png"))
        return EXIT_FAILURE;

    sf::Sprite background(texture2);
    // Select one sprite from texture
    sf::Sprite sprite(texture1);
    sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));

    int dx=0; // Horizontal movement
    bool rotate=0; // Rotation
    int colorNum=1; // ColorID
    float timer=0;  // Elapsed time
    float delay=0.3; // FPS delay

    sf::Clock clock; // Clock

    //
    // Change color
    colorNum = 1 + rand() % 7;
    // Change figure ID
    int n = rand() % 7;
    if(a[0].x == 0)
    for(int i=0; i<4; i++)
    {
        a[i].x = figures[n][i] % 2;
        a[i].y = figures[n][i] / 2;
    }
    //

	// Start the game loop
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
            // Close window : exit
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
            a[i].x += dx; // Move by dx
        }

        // Don't move if on ground
        if(!check())
            for(int i=0; i<4; i++)
                a[i] = b[i];

        // Rotation
        if (rotate)
        {
            Point p = a[1]; // Rotation center
            for(int i=0; i<4; i++)
            {
                // Vector from center
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;

                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }

            // ???
            // Don't rotate if on ground
            if(!check())
                for(int i=0; i<4; i++)
                    a[i] = b[i];
        }

        // Tick
        if(timer > delay)
        {
            // Drop one square down
            for(int i=0; i<4; i++)
            {
                b[i] = a[i];
                a[i].y += 1;
            }

            // If on ground
            if(!check())
            {
                // Add figure to field
                for(int i=0; i<4; i++)
                    field[b[i].y][b[i].x] = colorNum;

                // Change color
                colorNum = 1 + rand() % 7;
                // Change figure ID
                int n = rand() % 7;
                // Add new figure
                for(int i=0; i<4; i++)
                {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            }

            // Reset timer
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

        // Clear screen
        app.clear(sf::Color::White);
        app.draw(background);

        // Draw field
        for(int i=0; i<M; i++)
            for(int j=0; j<N; j++)
            {
                // Skip if empty
                if(field[i][j] == 0)
                    continue;
                sprite.setTextureRect(sf::IntRect(field[i][j] * 18, 0, 18, 18));
                // Set point position
                sprite.setPosition(j * 18, i * 18);
                sprite.move(28, 31);
                app.draw(sprite);
            }

        // Draw the sprite
        for(int i=0; i<4; i++)
        {
            sprite.setTextureRect(sf::IntRect(colorNum * 18, 0, 18, 18));
            sprite.setPosition(a[i].x * 18, a[i].y * 18);
            sprite.move(28, 31);
            app.draw(sprite);
        }

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
