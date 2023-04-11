#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <math.h>
#include <world_render.hpp>

bool updateCheck = true;

int draw(int i, int j);
void create(int i, int j, short id);

particle world[winSize_y][winSize_x] = {};
particle worldCopy[winSize_y][winSize_x] = {};
sf::RenderWindow window(sf::VideoMode(winSize_x, winSize_y), "Another Physics Simulator");
bool randomBool()
{
	return rand() > (RAND_MAX / 2);
}
float deltaTime;
short c_id = 1;
int create_dim = 1;

int main()
{
	sf::Font font;
			font.loadFromFile("assets/ari.ttf");
	sf::Clock dt;
	bool dragging = false;

	float deltatime = 0.f;
	sf::Clock clock;
	while (window.isOpen())
	{

		double frameTime = dt.restart().asSeconds();
		deltaTime = (frameTime < 1 / 60.0) ? frameTime : 1 / 60.0;
		sf::Event event;

		sf::Vector2i point;

		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					dragging = true;
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					sf::Vector2u s = window.getSize();
					sf::Vector2i p = sf::Mouse::getPosition(window);
					p.x = round(p.x * (((float)winSize_x) / s.x));
					p.y = round(p.y * (((float)winSize_y) / s.y));
					std::cout << p.y << " " << p.x << " id: " << world[p.y][p.x].id <<"\n";
				}
				break;

			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					dragging = false;
				}
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::D)
					c_id = 0;
				else if (event.key.code == sf::Keyboard::A)
					c_id = 1;
				else if (event.key.code == sf::Keyboard::W)
					c_id = 2;
				else if (event.key.code == sf::Keyboard::S)
					c_id = 3;
				else if (event.key.code == sf::Keyboard::P)
					c_id = 4;
				else if (event.key.code == sf::Keyboard::Down)
					create_dim = __max(1, create_dim - 1);
				else if (event.key.code == sf::Keyboard::Up)
					create_dim = __min(10, create_dim + 1);
			}
		}
		if (dragging)
		{
			sf::Vector2u s = window.getSize();
			sf::Vector2i point = sf::Mouse::getPosition(window);
			point.x = round(point.x * (((float)winSize_x) / s.x));
			point.y = round(point.y * (((float)winSize_y) / s.y));
			create(point.y, point.x, c_id);
		}
		if (clock.getElapsedTime().asSeconds() >= 0)
		{
			int totalDrawn = 0;
			for (int i = 0; i < winSize_y; i++)
			{
				for (int j = 0; j < winSize_x; j++)
				{
					if (world[i][j].id != 0 && world[i][j].hasUpdated != updateCheck)
					{
						
						update(i, j);
					}
					if (world[i][j].id != 0)
					{
						totalDrawn += 1;
					}
				}
			}

			sf::VertexArray points(sf::Quads, winSize_y*winSize_x * 4);
			int index = 0;
			for (int i = 0; i < winSize_y ; i++)
			{
				for (int j = 0; j < winSize_x ; j++)
				{
					if (world[i][j].id == 0)
						continue;
					points[index].position = sf::Vector2f(j - 0.5, i - 0.5);
					points[index].color = world[i][j].color;
					points[index+1].position = sf::Vector2f(j - 0.5, i + 0.5);
					points[index+1].color = world[i][j].color;
					points[index+2].position = sf::Vector2f(j + 0.5, i + 0.5);
					points[index+2].color = world[i][j].color;
					points[index+3].position = sf::Vector2f(j + 0.5, i - 0.5);
					points[index+3].color = world[i][j].color;
					index += 4;
				}
			}
			window.draw(points);

			sf::Text text(std::to_string(((int)floor(1 / deltaTime))) + "\n" + std::to_string(totalDrawn), font);
			text.setCharacterSize(10);
			text.setPosition(winSize_x * 0.05, winSize_y * 0.05);
			window.draw(text);

			window.display();
			window.clear();
			clock.restart();
			updateCheck = !updateCheck;


		}

	}

	return 0;
}

void create(int i, int j, short id)
{
	for (int x = -create_dim; x <= create_dim; x++)
	{
		for (int y = -create_dim; y <= create_dim; y++)
		{
			inicialize(i + x, j + y, id);
		}
	}

}

void inicialize(int i, int j, short id)
{
	particle *k = &world[i][j];
	switch (id)
	{
	case 1:
		k->id = 1;
		k->color = sf::Color::Yellow;
		k->density = 3;
		k->weight = 0.1;
		break;
	case 2:
		k->id = 2;
		k->color = sf::Color::Blue;
		k->density = 2;
		k->weight = 100;
		break;
	case 3:
		world[i][j].id = 3;
		k->color.a = 255;
		k->color.r = 180;
		k->color.g = 180;
		k->color.b = 180;
		k->life_time = 3 * (randomBool() ? 2 : 1);
		k->density = 1;
		k->weight = 0.01;
		break;
	case 4: // Wood
		world[i][j].id = 4;
		k->color.a = 255;
		k->color.r = 139;
		k->color.g = 69;
		k->color.b = 19;
		k->density = 4;
		break;
	default:
		k->id = 0;
		k->density = 0;
		break;
	}
}

bool stuck(int i, int j)
{

	particle x = world[i][j];
	if (i + 1 < winSize_y && world[i + 1][j].density < x.density)
	{
		return false;
	}
	else if (i + 1 < winSize_y && j + 1 < winSize_x && world[i + 1][j + 1].density < x.density)
	{
		return false;
	}
	else if (i + 1 < winSize_y && j - 1 >= 0 && world[i + 1][j - 1].density < x.density)
	{
		return false;
	}
	if (x.id == 2 || x.id == 3)
	{
		if (j + 1 < winSize_x && world[i][j + 1].density < x.density)
		{
			return false;
		}
		else if (j - 1 >= 0 && world[i][j - 1].density < x.density)
		{
			return false;
		}
	}
	if (x.id == 3 && i - 1 >= 0)
	{
		if (world[i - 1][j].density <= x.density)
		{
			return false;
		}
		else if (j + 1 < winSize_x && world[i - 1][j + 1].density <= x.density)
		{
			return false;
		}
		else if (j - 1 >= 0 && world[i - 1][j - 1].density <= x.density)
		{
			return false;
		}
	}
	return true;
}

void update(int i, int j)
{

    world[i][j].hasUpdated = updateCheck;
	world[i][j].velocity.y = (world[i][j].velocity.y + G);
	world[i][j].life_time -= deltaTime;
	if (stuck(i, j))
	{
		return;
	}
	switch (world[i][j].id)
	{

	case 1:
		updateSand(i, j);
		break;
	case 2:
		updateWater(i, j);
		break;
	case 3:
		updateSmoke(i, j);
		break;
	default:
		break;
	}
}

void fall(int i, int j)
{
	int maxD = (world[i][j].velocity.y * deltaTime);

	for (int d = 0; d < maxD; d++)
	{
	}
}

void updateSand(int i, int j)
{

	int maxD = (world[i][j].velocity.y * deltaTime);

	for (int d = 0; d < maxD; d++)
	{
		if (i + 1 < winSize_y)
		{
			int k = randomBool() ? 1 : -1;
			particle down = world[i + 1][j];

			if (down.density < world[i][j].density)
			{
				world[i + 1][j] = world[i][j];
				world[i][j] = down;
			}
			else if (j + k < winSize_x && j + k >= 0 && world[i + 1][j + k].density < world[i][j].density)
			{
				particle t = world[i + 1][j + k];
				world[i + 1][j + k] = world[i][j];
				world[i][j] = t;
				j += k;
			}
			else
			{
				world[i][j].velocity.y = 0;
				break;
			}
			i++;
		}
	}
}

void updateSmoke(int i, int j)
{
	if (world[i][j].life_time <= 0)
	{
		world[i][j].id = 0;
		return;
	}

	int h = randomBool() ? 1 : -1;
	h += (randomBool() && h > -1) ? -1 : 0;
	int k = randomBool() ? 1 : -1;
	if (i + h < winSize_y && i + h >= 0)
	{
		if (world[i + h][j].id == 0)
		{
			if (j + k < winSize_x && j + k >= 0 && world[i + h][j + k].id == 0)
			{
				world[i + h][j + k] = world[i][j];
			}
			else
				world[i + h][j] = world[i][j];
			world[i][j].id = 0;
		}
	}

}

void switch_particles(int i1, int j1, int i2, int j2)
{
	particle temp = world[i2][j2];
	world[i2][j2] = world[i1][j1];
	world[i1][j1] = temp;
}

void updateWater(int i, int j)
{
	updateSand(i, j);
	int k = randomBool() ? 1 : -1;

	if (j + k < winSize_x && j + k >= 0)
	{
		if (world[i][j + k].density < world[i][j].density)
		{
			switch_particles(i, j, i, j + k);
		}
	}
	else if (j - k < winSize_x && j - k >= 0)
	{
		if (world[i][j - k].density < world[i][j].density)
		{
			switch_particles(i, j, i, j - k);
		}
	}
	
	
}

int draw(int i, int j)
{

	if (world[i][j].id != 0)
	{
		sf::RectangleShape s = sf::RectangleShape(sf::Vector2f(1, 1));
		s.setFillColor(world[i][j].color);
		s.setPosition(sf::Vector2f(j, i));
		window.draw(s);
		
		return 1;
	}

	return 0;
}
