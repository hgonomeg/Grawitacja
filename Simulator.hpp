#include <SFML/Graphics.hpp>
#include <list>
#include <math.h>
#include "Celestial_body.hpp"
#include <memory>

class Simulator :public sf::Drawable
{
	public:
	enum class collision_approach :unsigned short
	{
		merge = 1,
		bounce
	};
	private:
	
	static const float G;
	static const unsigned short CA_count;
	static float STEPPPING_RATE;
	collision_approach ca;
	bool paused, draw_traces;
	
	std::list<std::unique_ptr<Celestial_body>> ciala;
	
	public:
	
	void tick();
	void pause(bool);
	bool pause();
	void add_body(Celestial_body*);
	void toggle_traces();
	Simulator();
	Simulator(const Simulator& sim);
	virtual void draw(sf::RenderTarget&,sf::RenderStates) const override;
	
	std::list<std::unique_ptr<Celestial_body>>::iterator at_pos(const sf::Vector2f&); //funkcja at_pos(int,int) zwraca iterator listy do elementu który znajduje się na podanych koordynatach. W razie braku ciał niebieskich o podobnych koordynatach, zwraca list::end().
	std::list<std::unique_ptr<Celestial_body>>::iterator erase_body(const std::list<std::unique_ptr<Celestial_body>>::iterator& el);
	void erase_body(unsigned int);
	std::list<std::unique_ptr<Celestial_body>>::const_iterator get_end();
	
	collision_approach cycle_collision_approach();
};


