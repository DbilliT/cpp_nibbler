//
// nibbler.hh for nibbler in /home/bechad_p/rendu/cpp_nibbler/project/nibbler/include
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Thu Mar 26 11:31:26 2015 Pierre Bechade
// Last update Fri Jul 10 15:11:07 2015 Pierre Bechade
//

#ifndef NIBBLER_HH_
# define NIBBLER_HH_

#include "game.hh"

class Nibbler
{

public:
  Nibbler();
  Nibbler(int ac, char **av);
  ~Nibbler();

public:
  void			handling_arg(int ac, char **av) const;
  void			runGame(Game *game, std::string const &lib);
  void			FileHightScore(Object *object) const;
  INibblerDisplay	*checkLib(std::string const &lib);

private:
  void	*_dhandle;
};

#endif /* NIBBLER_HH_ */
