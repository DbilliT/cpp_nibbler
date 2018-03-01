//
// game.cpp for game in /home/bechad_p/rendu/cpp_nibbler/project/game
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Fri Mar 27 19:54:18 2015 Pierre Bechade
// Last update Sat Apr  4 16:12:57 2015 Pierre Bechade
//

#include "nibbler.hh"

Game::Game(int x, int y, std::string lib) : _size_x(x), _size_y(y), _lib(lib)
{
  this->_state = true;
  this->_direction = LEFT;
  this->_coef = 1;
}

Game::~Game()
{
}

int	Game::getSizeX() const
{
  return (this->_size_x);
}

int	Game::getSizeY() const
{
  return (this->_size_y);
}

std::string const &Game::getLib() const
{
  return (this->_lib);
}

void	Game::setObject(Object *object)
{
  this->_object = object;
}

void	Game::setLib(std::string const &str)
{
  this->_lib = str;
}

void	Game::setDirection(INibblerDisplay *Display)
{
  d_event dir = Display->getEvent();

  if (dir == EVENT_RIGHT)
    {
      switch (this->_direction)
	{
	case LEFT:
	  this->_direction = UP;
	  break;
	case UP:
	  this->_direction = RIGHT;
	  break;
	case DOWN:
	  this->_direction = LEFT;
	  break;
	default:
	  this->_direction = DOWN;
	  break;
	}
    }
  else if (dir == EVENT_LEFT)
    {
      switch (this->_direction)
	{
	case LEFT:
	  this->_direction = DOWN;
	  break;
	case UP:
	  this->_direction = LEFT;
	  break;
	case DOWN:
	  this->_direction = RIGHT;
	  break;
	default:
	  this->_direction = UP;
	  break;
	}
    }
  else if (dir == EVENT_SPEED)
    {
      switch (this->_coef)
	{
	case 2:
	  this->_coef = 1;
	  break;
	case 1:
	  this->_coef = 2;
	  break;
	}
    }
  else if (dir == EVENT_EXIT)
    std::exit (EXIT_FAILURE);
  Display->setEvent(EVENT_UNKNOWN);
}

void	sendAff(INibblerDisplay *Display, Object *obj, int x, int y)
{
  Display->affNibbler(obj, std::make_pair(x, y));
}

void	Game::handleBonus()
{
  static int bonus_f = -1;

  this->_object->addTime(-500);
  if (bonus_f > 50)
    {
      bonus_f = -1;
      this->_object->addFruit(this->_object->BONUS, this->_size_x, this->_size_y);
      this->_object->setIsBonus(true);
    }
  if (bonus_f > 20 && this->_object->getIsBonus() == true)
    {
      this->_object->popFruit(this->_object->getPosBonus(), this->_object->BONUS);
      this->_object->setIsBonus(false);
    }
  ++bonus_f;
}

int	Game::run(INibblerDisplay *Display)
{
  std::thread affichage(sendAff, Display, this->_object, this->_size_x, this->_size_y);
  
  while (this->_state == true)
    {
      this->setDirection(Display);
      this->sendMove(this->_direction);
      this->handleBonus();
      std::this_thread::sleep_for (std::chrono::microseconds(this->_object->getTime() / this->_coef));
    }
  Display->setIsOver(true);
  affichage.join();
  return (0);
}

bool	Game::sendMove(Type_mouv mv)
{
  switch (mv)
    {
    case UP:
      this->move(std::make_pair(0, -1));
      break;
    case LEFT:
      this->move(std::make_pair(-1, 0));
      break;
    case RIGHT:
      this->move(std::make_pair(1, 0));
      break;
    default:
      this->move(std::make_pair(0, 1));
      break;
    }
  return (true);
}

void			Game::move(std::pair<int, int> const &pos)
{
  int			x_head = 0;
  int			y_head = 0;

  std::list<std::pair<Object::Type_block, std::pair<int, int> > > tmp = this->_object->getObject();
  std::list<std::pair<Object::Type_block, std::pair<int, int> > >::iterator it = tmp.begin();

  (*it).first = this->_object->SNAKE;                    
  x_head = (*it).second.first;                                                                               
  y_head = (*it).second.second;
  it = --tmp.end();
  (*it).first = this->_object->HEAD;
  (*it).second.first = x_head + pos.first;
  (*it).second.second = y_head + pos.second;
  this->_head = std::make_pair(
(*it).second.first, (*it).second.second);
  tmp.push_front(tmp.back());
  tmp.pop_back();
  if (this->isDeath(tmp) == true)
    return ;
  this->_object->setObject(tmp);
  if (this->isFruit() == true)
    {
      tmp.back().first = this->_object->SNAKE;
      tmp.push_back(tmp.back());
    }
  else
    tmp.back().first = this->_object->QUEUE;
  this->_object->setObject(tmp);
}

bool    Game::isDeath(std::list<std::pair<Object::Type_block, std::pair<int, int> > > &tmp)
{
  if (this->_head.second <= 0 || this->_head.first <= 0 || this->_head.first >= this->_size_x || this->_head.second >= this->_size_y)
    {
      this->_state = false;
      return (true);
    }
  for (std::list<std::pair<Object::Type_block, std::pair<int, int> > >::iterator it = ++tmp.begin(); it != tmp.end(); ++it)
    {
      if ((*it).second.first == this->_head.first && (*it).second.second == this->_head.second)
	{
	  this->_state = false;
	  return (true);
	}
    }
  return (false);
}

bool	Game::isFruit() const
{
  std::list<std::pair<Object::Type_block, std::pair<int, int> > > tmp = this->_object->getFruit();
  
  for (std::list<std::pair<Object::Type_block, std::pair<int, int> > >::iterator it = tmp.begin(); it != tmp.end(); ++it)
    {
      if ((*it).second.first == this->_head.first && (*it).second.second == this->_head.second && (*it).first == this->_object->FRUIT)
	{
	  this->_object->popFruit(this->_head, this->_object->FRUIT);
	  this->_object->setIsFruit(false);
	  this->_object->addFruit(this->_object->FRUIT, this->_size_x, this->_size_y);
	  if (this->_coef == 1)
	    this->_object->addScore(1);
	  else
	    this->_object->addScore(2);
	  this->_object->addTime(2000);
	  return (true);
	}
      else if ((*it).second.first == this->_head.first && (*it).second.second == this->_head.second && (*it).first == this->_object->BONUS)
	{
	   this->_object->popFruit(this->_head, this->_object->BONUS);
	   this->_object->addTime(-5000);
	   this->_object->addScore(10);
	   return (false);
	}
    }
  return (false);
}
