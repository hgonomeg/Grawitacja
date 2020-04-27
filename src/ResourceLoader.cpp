#include "ResourceLoader.hpp"

Resource_Manager::Resource_Manager() noexcept
{	
	main_font.loadFromMemory(arimo.data,arimo.size);

	auto button_tex_gen = [this](std::string txt, const sf::Color col, bool blackorwhite) -> sf::Texture {
		sf::RenderTexture ren;
		sf::Text textext(txt,main_font,12);
		ren.create(15,15); //the tile
		textext.setOrigin({textext.getLocalBounds().width/2.f,textext.getLocalBounds().height/2.f});
		textext.setPosition(7.5,5); //this is roughly the center of the tile
		textext.setFillColor(blackorwhite? sf::Color::White : sf::Color::Black);
		ren.clear(col);
		ren.draw(textext);
		ren.display();
		return ren.getTexture();
	};
	
	button_CB_gen = button_tex_gen("G",sf::Color::Green,false);
	button_CB_selector = button_tex_gen("S",sf::Color::Green,false);
	button_left = button_tex_gen("<",sf::Color::Red,false);
	button_right = button_tex_gen(">",sf::Color::Red,false);
	button_toggle_traces = button_tex_gen("L",sf::Color::Cyan,false);
	button_cycle_collision = button_tex_gen("R",sf::Color::Cyan,false);
	button_deltraces = button_tex_gen("^L",sf::Color::Yellow,false);
	button_gen_mode = button_tex_gen("M",sf::Color::Red,false);
	button_predtraces = button_tex_gen("T",sf::Color::Cyan,false);
	
	button_accuracy_plus = button_tex_gen("A+",sf::Color(48,48,142),true);
	button_accuracy_minus = button_tex_gen("A-",sf::Color(48,48,142),true);
	button_speed_plus = button_tex_gen("S+",sf::Color(48,48,142),true);
	button_speed_minus = button_tex_gen("S-",sf::Color(48,48,142),true);
	button_debug = button_tex_gen("^[",sf::Color(200,50,200),true);
}


void Resource_Manager::finish_loading()
{
	//empty
	//will load external resources from files in the future
}

