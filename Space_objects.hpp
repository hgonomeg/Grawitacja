#include "Celestial_body.hpp"

class Planet :public Celestial_body
{
	
	//W przyszlosci dodac mechanike teksturowania

	public:
	
	enum planetary_classification 
	{
		gas,
		liquid,
		rock
	} planet_type; 
	
	Planet(int mass=10, const sf::Vector2f& location={0,0},const sf::Vector2f& velocity={0,0});
};

class Star :public Celestial_body
{
	
	public:
	
	enum class stellar_classification :sf::Uint32
	{
		O =0x9bb0ff,
		B =0xaabfff,
		A =0xcad7ff,
		F =0xf8f7ff,
		G =0xfff4ea,
		K =0xffd2a1,
		M =0xffcc6f
	} star_type; //tak jak w przypadku planety; zgodnie z diagramem Hertzsprung–Russella będzie można  znieniać kolor czy teksture gwiazdy

	
	Star(int mass=100, const sf::Vector2f& location={0,0},const sf::Vector2f& velocity={0,0});
};