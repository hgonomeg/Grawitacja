#include "Celestial_body.hpp"

void Celestial_body::draw(sf::RenderTarget& tgt,sf::RenderStates st) const
{
	tgt.draw(wyglond,st);
}

int& Celestial_body::get_mass() 
{
	return mass;
}
sf::Vector2f& Celestial_body::get_loc()
{
	return loc;
}
sf::Vector2f& Celestial_body::get_v()
{
	return v;
}

void Celestial_body::refresh()
{
	wyglond.setPosition(loc);
}

Celestial_body::Celestial_body(int imass,const sf::Color& kolorek,const sf::Vector2f& iloc,const sf::Vector2f& iv)
{
	mass = imass;
	loc = iloc;
	v = iv;
	wyglond.setRadius(mass/10.f); //czy zapisz ".f" oznacza że dzielimy przez floata? [TAK]
	wyglond.setPointCount(64);
	wyglond.setOrigin(mass/20.f,mass/20.f);
	wyglond.setOutlineThickness(0);
	wyglond.setFillColor(kolorek);
}