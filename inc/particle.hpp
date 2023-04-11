#define G 9.8 // gravity
struct particle_s
{
	short id;
	float weight;
	float life_time;
	sf::Vector2f velocity;
	sf::Color color;
	bool hasUpdated;
	short density;
};

typedef particle_s particle;

void inicialize(int i, int j, short id);
void updateSand(int x, int y);
void updateSmoke(int i, int j);
void updateWater(int i, int j);
void update(int i, int j);