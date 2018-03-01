//
// uiOpenGl.hh for uiOpenGl in /home/bechad_p/rendu/cpp_nibbler/UI/OpenGl
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Wed Apr  1 11:56:36 2015 Pierre Bechade
// Last update Sun Apr  5 15:45:52 2015 Pierre Bechade
//

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <cmath>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include "exception.hpp"

#ifndef __UIOPENGL_H__
# define __UIOPENGL_H__

class	UIOpenGl : public INibblerDisplay
{
public:
  UIOpenGl();
  ~UIOpenGl();
  d_event getEvent() const;
  void  setIsOver(bool b);
  void  setEvent(d_event ev);
  void  affNibbler(Object *obj, std::pair<int, int> const &size);
private:
  d_event _event;
  bool    _isOver;
  void    addCube(int x, int y, int type) const;
  void    view(std::list<std::pair<Object::Type_block, std::pair<int, int> > > &snake) const;
  void    addUnder(int x_max, int y_max) const;
  void    addTop(int x_max, int y_max) const;
  void    addGround(int x_max, int y_max) const;
};

#endif /* __UIOPENGL_H __ */
