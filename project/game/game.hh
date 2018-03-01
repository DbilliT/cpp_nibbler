//
// game.hh for game in /home/bechad_p/rendu/cpp_nibbler/project/game
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Fri Mar 27 19:51:03 2015 Pierre Bechade
// Last update Sat Apr  4 15:54:01 2015 Pierre Bechade
//

#ifndef GAME_HH_
# define GAME_HH_

#include "INibblerDisplay.hh"
#include <dlfcn.h>
#include <thread>
#include <chrono>

class Game
{
public:
  Game(int x = 0, int y = 0, std::string lib = NULL);
  ~Game();
  enum	Type_mouv
    {
      UP = 1,
      LEFT = 2,
      RIGHT = 3,
      DOWN = 4
    };
  int	getSizeX() const;
  int	getSizeY() const;
  std::string const &getLib() const;
  void	setLib(std::string const &str);
  void	setObject(Object *object);
  void	setDirection(INibblerDisplay *bob);
  bool	sendMove(Type_mouv mv);
  void	createMap() const;
  void	move(std::pair<int, int> const &mov);
  void	eatFruit() const;
  int	run(INibblerDisplay *Display);
  bool	isDeath(std::list<std::pair<Object::Type_block, std::pair<int, int> > > &tmp);
  bool	isFruit() const;
  void	addTime(int);
  void	handleBonus();
private:
  int		_size_x;
  int		_size_y;
  int		_coef;
  std::string	_lib;
  bool		_state;
  Type_mouv	_direction;
  Object	*_object;
  std::pair<int, int> _head;
};

#endif /* GAME_HH_ */
