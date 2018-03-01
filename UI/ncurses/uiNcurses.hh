//
// uiNcurses.hh for uiNcurses in /home/bechad_p/rendu/cpp_nibbler/UI/ncurses
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Thu Apr  2 11:10:21 2015 Pierre Bechade
// Last update Sun Apr  5 15:57:28 2015 Pierre Bechade
//

#ifndef __UINCURSES_HH__
# define __UINCURSES_HH__

#include <iostream>
#include <list>
#include <ncurses.h>
#include "exception.hpp"

class UIncurses : public INibblerDisplay
{
public:
  UIncurses();
  ~UIncurses();
  d_event getEvent() const;
  void  setIsOver(bool b);
  void  setEvent(d_event ev);
  void  affNibbler(Object *obj, std::pair<int, int> const &size);
private:
  void	affEmpty(WINDOW *screen) const;
  void	drawBorders(WINDOW *screen) const;
  d_event _event;
  bool    _isOver;
};


#endif /* __UINCURSES_HH__ */
