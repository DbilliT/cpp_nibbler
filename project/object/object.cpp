//
// object.cpp for object in /home/bechad_p/rendu/cpp_nibbler/project/object
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Thu Mar 26 21:07:33 2015 Pierre Bechade
// Last update Sat Apr  4 14:37:50 2015 Pierre Bechade
//

#include "nibbler.hh"

Object::Object(bool fruit, int hightscore) : _is_fruit(fruit), _hightscore(hightscore)
{
  this->_score = 0;
  this->_time = 300000;
  this->_is_bonus = false;
}

Object::~Object()
{
}

std::list<std::pair<Object::Type_block, std::pair<int, int> > > const &Object::getObject() const
{
  return (this->_object);
}

std::list<std::pair<Object::Type_block, std::pair<int, int> > > const &Object::getFruit() const
{
  return (this->_fruit);
}

std::pair<int, int> const &Object::getPosBonus() const
{
  return (this->_pos_bonus);
}

int	Object::getScore() const
{
  return (this->_score);
}

int	Object::getTime() const
{
  return (this->_time);
}

int	Object::getHightScore() const
{
  return (this->_hightscore);
}

bool	Object::getIsBonus() const
{
  return (this->_is_bonus);
}

void	Object::setObject(std::list<std::pair<Object::Type_block, std::pair<int, int> > > const &list)
{
  this->_object = list;
}

void	Object::setIsFruit(bool fruit)
{
  this->_is_fruit = fruit;
}

void   Object::setIsBonus(bool bonus)
{
  this->_is_bonus = bonus;
}

void	Object::setScore(int score)
{
  this->_score = score;
}

void	Object::addScore(int score)
{
  this->_score += score;
}

void    Object::addTime(int t)
{
  this->_time += t;
  if (this->_time < 80000)
    this->_time = 80000;
}

void	Object::addObject(Object::Type_block type, int x, int y)
{
  if (type == this->FRUIT || type == this->BONUS)
    this->_fruit.push_back(std::make_pair(type, std::make_pair(x, y)));
  else
    this->_object.push_back(std::make_pair(type, std::make_pair(x, y)));
}

bool	Object::isEmpty(int x_rand, int y_rand)
{
  int	x;
  int	y;
  Object::Type_block	def;

  if (x_rand == -1)
    return (false);
  for (std::list<std::pair<Object::Type_block, std::pair<int, int> > >::iterator it = this->_object.begin(); it != this->_object.end(); ++it)
    {
      x = (*it).second.first;
      y = (*it).second.second;
      def = (*it).first;
      if (x == x_rand && y == y_rand && def != EMPTY)
	return (false);
    }
  for (std::list<std::pair<Object::Type_block, std::pair<int, int> > >::iterator it = this->_fruit.begin(); it != this->_fruit.end(); ++it)
    {
      x = (*it).second.first;
      y = (*it).second.second;
      def = (*it).first;
      if (x == x_rand && y == y_rand && def != EMPTY)
	return (false);
    }
  return (true);
}

int	Object::addFruit(Type_block block, int size_x, int size_y)
{
  std::srand(std::time(0));

  if (block == this->FRUIT && this-> _is_fruit == true)
    return (EXIT_FAILURE);
  else
    {
      int	x = -1;
      int	y = -1;
      while (isEmpty(x, y) == false)
	{
	  x = (std::rand() % (size_x - 1)) + 1;
	  y = (std::rand() % (size_y - 1)) + 1;
	}
      if (block == this->FRUIT)
	this->_is_fruit = true;
      else if (block == this->BONUS)
	this->_pos_bonus = std::make_pair(x, y);
      this->addObject(block, x, y);
    }
  return (EXIT_SUCCESS);
}

void			Object::affList()
{
  for (std::list<std::pair<Object::Type_block, std::pair<int, int> > >::iterator it = this->_object.begin(); it != this->_object.end(); ++it)
    {
      std::cout << "x = " << (*it).second.first << std::endl; 
      std::cout << "y = " << (*it).second.second << std::endl; 
      std::cout << "Block = " << (*it).first << std::endl; 
    }
}

void			Object::affFruit()
{
  for (std::list<std::pair<Object::Type_block, std::pair<int, int> > >::iterator it = this->_fruit.begin(); it != this->_fruit.end(); ++it)
    {
      std::cout << "Fruit x = " << (*it).second.first << std::endl; 
      std::cout << "Fruit y = " << (*it).second.second << std::endl; 
      std::cout << "Fruit Block = " << (*it).first << std::endl; 
    }
}

void    Object::createSnake(int size_x, int size_y)
{
  try
    {
      if (size_x == 0 || size_y == 0)
        throw std::invalid_argument("Nibbler error : bad size_map_x or size_map_y");
      else
        {
	  addObject(HEAD, (size_x / 2), size_y / 2);
	  addObject(SNAKE, (size_x / 2) + 1, size_y / 2);
	  addObject(SNAKE, (size_x / 2) + 2, size_y / 2);
	  addObject(QUEUE, (size_x / 2) + 3, size_y / 2);
        }
    }
  catch (std::invalid_argument& e)
    {
      std::cerr << e.what() << std::endl;
    }
}

void    Object::popFruit(std::pair<int, int> const &pos, Type_block typ)
{
  this->_fruit.remove(std::make_pair(typ, pos));
}
