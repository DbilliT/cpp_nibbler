#include "ui_sfml.hh"

extern "C"
{
  INibblerDisplay *create_object() { return new UI(); }
}

UI::UI()
{
  this->_event = EVENT_UNKNOWN;
  this->_isOver = false;
}

UI::~UI()
{
}

d_event UI::getEvent() const
{
  return (this->_event);
}

void	UI::setIsOver(bool b)
{
  this->_isOver = b;
}

void	UI::setEvent(d_event ev)
{
  (void) ev;
  this->_event = EVENT_UNKNOWN;
}

void	UI::affNibbler(Object *obj, std::pair<int, int> const &size)
{
  int	x = size.first;
  int	y = size.second;
  int	max;

  if (x > y)
    max = x;
  else
    max = y;
  sf::RenderWindow window(sf::VideoMode(1000 + (3 * (1000 / max)), 1000 + (3 * (1000 / max))), "Nibbler SFML", sf::Style::Fullscreen);
  sf::RectangleShape rectangle(sf::Vector2f(1000 / max - 2, 1000 / max - 2));
  sf::RectangleShape bordure(sf::Vector2f(x * (1000 / x) - (1000 / x), y * (1000 / y) - (1000 / y)));
  sf::Font font;
  sf::Text current_s;
  sf::Text current_h;
  sf::Text current_speed;
  
  sf::Text w_score;
  sf::Text h_score;
  sf::Text s_score;

  std::list<std::pair<Object::Type_block, std::pair<int, int> > > snake;
  std::list<std::pair<Object::Type_block, std::pair<int, int> > > fruit;
  std::string score;
  std::string hightscore;
  std::string speed;

  if (!font.loadFromFile("cs.tff"))
    std::exit (EXIT_FAILURE);
  current_s.setFont(font);
  current_s.setString("Your score :");
  current_s.setCharacterSize(75);
  current_s.setColor(sf::Color::Red);
  current_s.move(1200, 10);

  current_h.setFont(font);
  current_h.setString("Highscore is :");
  current_h.setCharacterSize(75);
  current_h.setColor(sf::Color::Red);
  current_h.move(1200, 210);

  current_speed.setFont(font);
  current_speed.setString("Current Speed :");
  current_speed.setCharacterSize(75);
  current_speed.setColor(sf::Color::Red);
  current_speed.move(1200, 410);

  w_score.setFont(font);
  w_score.setCharacterSize(75);
  w_score.setColor(sf::Color::Red);
  w_score.move(1400, 110);

  h_score.setFont(font);
  h_score.setCharacterSize(75);
  h_score.setColor(sf::Color::Red);
  h_score.move(1400, 310);

  s_score.setFont(font);
  s_score.setCharacterSize(75);
  s_score.setColor(sf::Color::Red);
  s_score.move(1400, 510);

  rectangle.setFillColor(sf::Color::Green);
  bordure.setFillColor(sf::Color::Black);
  bordure.setOutlineThickness(1000 / max);
  bordure.setOutlineColor(sf::Color(250, 150, 100));
  bordure.setPosition(0 + (1000 / x), 0 + (1000 / y));
  sf::Event my_event;
  while (this->_isOver == false)
    {
      window.setKeyRepeatEnabled(false);
      window.clear();
      window.draw(current_s);
      window.draw(current_h);
      window.draw(current_speed);
      snake = obj->getObject();
      fruit = obj->getFruit();
      score = std::to_string(obj->getScore());
      hightscore = std::to_string(obj->getHightScore());
      speed = std::to_string((obj->getTime() - 300000) * -1);
      w_score.setString(score);
      h_score.setString(hightscore);
      s_score.setString(speed);
      window.draw(w_score);
      window.draw(h_score);
      window.draw(s_score);
      window.draw(bordure);
      
      for (std::list<std::pair<Object::Type_block, std::pair<int, int> > >::iterator it = snake.begin(); it != snake.end(); ++it)
	{
	  if ((*it).first == 4)
	    {
	      rectangle.setFillColor(sf::Color::Green);
	      rectangle.setPosition(((*it).second.first * (1000 / x)), ((*it).second.second * (1000 / y)));
	      window.draw(rectangle);
	    }
	  if ((*it).first == 5)
	    {
	      rectangle.setFillColor(sf::Color::Green);
	      rectangle.setPosition(((*it).second.first * (1000 / x)), ((*it).second.second * (1000 / y)));
	      window.draw(rectangle);
	    }
	  if ((*it).first == 3)
	    {
	      rectangle.setFillColor(sf::Color::Red);
	      rectangle.setPosition(((*it).second.first * (1000 / x)), ((*it).second.second * (1000 / y)));
	      window.draw(rectangle);
	    }
	}
      for (std::list<std::pair<Object::Type_block, std::pair<int, int> > >::iterator it = fruit.begin(); it != fruit.end(); ++it)
	{
	  if ((*it).first == 2)
	    {
	      rectangle.setFillColor(sf::Color::Yellow);
	      rectangle.setPosition(((*it).second.first * (1000 / x)), ((*it).second.second * (1000 / y)));
	      window.draw(rectangle);
	    }
	  if ((*it).first == 6)
	    {
	      rectangle.setFillColor(sf::Color::Blue);
	      rectangle.setPosition(((*it).second.first * (1000 / x)), ((*it).second.second * (1000 / y)));
	      window.draw(rectangle);
	    }
	}
      while (window.pollEvent(my_event))
	{
	  if (my_event.type == sf::Event::KeyPressed)
	    {
	      if (my_event.key.code == sf::Keyboard::Left)
		this->_event = EVENT_LEFT;
	      if (my_event.key.code == sf::Keyboard::Right)
		this->_event = EVENT_RIGHT;
	      if (my_event.key.code == sf::Keyboard::Escape)
		this->_event = EVENT_EXIT;
	      if (my_event.key.code == sf::Keyboard::Space)
		this->_event = EVENT_SPEED;
	    }
	}
      window.display();
    }
  window.close();
  return ;
}
