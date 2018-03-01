//
// INibblerDisplay.hh for INibblerDisplay in /home/bechad_p/rendu/cpp_nibbler/project/INibblerDisplay
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Sun Mar 29 12:19:34 2015 Pierre Bechade
// Last update Fri Apr  3 20:39:38 2015 Pierre Bechade
//

#ifndef INibblerDisplay_HH_
# define INibblerDisplay_HH_

#include <iostream>
#include <list>
#include "object.hh"

typedef enum	d_event
    {
      EVENT_UP = 0,
      EVENT_DOWN = 1,
      EVENT_LEFT = 2,
      EVENT_RIGHT = 3,
      EVENT_EXIT = 4,
      EVENT_UNKNOWN = 5,
      EVENT_SPEED = 6
    }		d_event;

class INibblerDisplay
{
public:
  virtual ~INibblerDisplay() { };
  virtual d_event getEvent() const = 0;
  virtual void	setEvent(d_event ev) = 0;
  virtual void	setIsOver(bool b) = 0;
  virtual void	affNibbler(Object *obj, std::pair<int, int> const &pos) = 0;
};

#endif /* INibblerDisplay_HH_ */
