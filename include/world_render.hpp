#include <SFML/Graphics.hpp>
#include <particle.hpp>
#include <list>
#include <SFML/Graphics/VertexArray.hpp>

enum DIRECTION
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const int winSize_x = 400;
const int winSize_y = 400;

int render_world(particle worldCopy[winSize_y][winSize_x], int total_particles);

std::list<sf::VertexArray> find_shapes(particle worldCopy[winSize_y][winSize_x]);

sf::VertexArray find_vertexes(particle worldCopy[winSize_y][winSize_x], int x, int y);

bool isVertex(particle worldCopy[winSize_y][winSize_x], int x, int y);

void move(int *x, int *y, DIRECTION dir);
