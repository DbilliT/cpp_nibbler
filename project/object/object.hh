//
// object.hh for object in /home/bechad_p/rendu/cpp_nibbler/project/object
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Thu Mar 26 21:04:59 2015 Pierre Bechade
// Last update Sun Apr  5 16:11:25 2015 Pierre Bechade
//

#ifndef OBJECT_HH_
# define OBJECT_HH_

#include "cstdlib"
#include "ctime"
#include "exception.hpp"

class Object
{
public:
  Object(bool _is_fruit = false, int hightscore = 0);
  ~Object();
  enum Type_block
    {
      EMPTY = 0,
      BLOCK = 1,
      FRUIT = 2,
      HEAD = 3,
      SNAKE = 4,
      QUEUE = 5,
      BONUS = 6
    };
  void	addObject(Type_block type, int x, int y);
  int	addFruit(Type_block block, int size_x, int size_y);
  void	addTime(int t);
  void	affList();
  void	affFruit();
  void	createSnake(int size_x, int size_y);
  bool	isEmpty(int x, int y);
  std::list<std::pair<Type_block, std::pair<int, int> > > const &getObject() const;
  std::list<std::pair<Type_block, std::pair<int, int> > > const &getFruit() const;
  std::pair<int, int> const &getPosBonus() const;
  int	getScore() const;
  int	getTime() const;
  int	getHightScore() const;
  bool	getIsBonus() const;
  void	setObject(std::list<std::pair<Type_block, std::pair<int, int> > > const &list);
  void	setIsFruit(bool);
  void	setIsBonus(bool b);
  void	setScore(int score);
  void	addScore(int score);
  void	popFruit(std::pair<int, int> const &pos, Type_block typ);
private:
  std::list<std::pair<Type_block, std::pair<int, int> > > _object;
  std::list<std::pair<Type_block, std::pair<int, int> > > _fruit;
  std::pair<int, int> _pos_bonus;
  bool	_is_fruit;
  bool	_is_bonus;
  int	_score;
  int	_hightscore;
  int	_time;
};

#endif /* OBJECT_HH_ */
