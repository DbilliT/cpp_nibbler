//
// ui.hh for UI in /home/bechad_p/rendu/cpp_nibbler/UI/sfml
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Mon Mar 30 15:38:50 2015 Pierre Bechade
// Last update Sun Apr  5 12:51:04 2015 Pierre Bechade
//

#ifndef __UI_H__
# define __UI_H__

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "exception.hpp"

class UI : public INibblerDisplay
{
public:
  UI();
  ~UI();
  d_event getEvent() const;
  void	setIsOver(bool b);
  void	setEvent(d_event ev);
  void	affNibbler(Object *obj, std::pair<int, int> const &size);
private:
  d_event _event;
  bool	  _isOver;
};

#endif /* __UI_H__ */
