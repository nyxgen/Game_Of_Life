#include "Graphics.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

void Graphics::display()
{
	_window->display();
}

void Graphics::clear()
{
	_window->clear(sf::Color::Black);
}

void Graphics::drawBoard(const shared_ptr<Board>& board)
{
	static sf::VertexArray va(sf::Quads);
	va.clear();
	if (board->tilesCount().x > 0 && board->tilesCount().y > 0)
	{
		sf::Vector2u over = sf::Vector2u(15, 15);
		sf::Vector2u size = board->size();
		sf::Vector2u position = board->position();
		sf::RectangleShape rs;
		rs.setSize(sf::Vector2f(size + over + over));
		rs.setPosition(sf::Vector2f(position - over));
		rs.setFillColor(sf::Color(125, 125, 125));
		this->window()->draw(rs);

		sf::RectangleShape rs2;
		rs2.setSize(sf::Vector2f(size));
		rs2.setPosition(sf::Vector2f(position));
		rs2.setFillColor(sf::Color::Red);
		this->window()->draw(rs2);
	}
	for (auto& i : (*board->tiles()))
	{
		for (auto& j : i)
		{
			for (auto& k : j->vertexes())
			{
				va.append(k);
			}
		}
	}
	this->window()->draw(va);
}
const shared_ptr<sf::RenderWindow>& Graphics::window()
{
	return _window;
}

void Graphics::window(const shared_ptr<sf::RenderWindow>& window)
{
	_window = window;
}