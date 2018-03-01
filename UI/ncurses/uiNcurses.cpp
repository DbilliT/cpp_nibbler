//
// uiNcurses.cpp for uiNcurses in /home/bechad_p/rendu/cpp_nibbler/UI/ncurses
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Thu Apr  2 11:10:13 2015 Pierre Bechade
// Last update Sun Apr  5 15:57:39 2015 Pierre Bechade
//

#include "uiNcurses.hh"
#include <unistd.h>

extern "C"
{
  INibblerDisplay *create_object() { return new UIncurses(); }
}

UIncurses::UIncurses()
{
  this->_event = EVENT_UNKNOWN;
  this->_isOver = false;
}

UIncurses::~UIncurses()
{
}

d_event UIncurses::getEvent() const
{
  return (this->_event);
}

void    UIncurses::setIsOver(bool b)
{
  this->_isOver = b;
}

void    UIncurses::setEvent(d_event ev)
{
  (void) ev;
  this->_event = EVENT_UNKNOWN;
}

void	UIncurses::affEmpty(WINDOW *screen) const
{
  int	x, y;
  int	i = 0, i2 = 0;

  getmaxyx(screen, y, x);
  y -= 101;
  x -= 101;
  while (i++ < y)
    {
      while (i2++ < x)
	mvwprintw(screen, i, i2, " ");
      i2 = 0;
    }
}

void	UIncurses::drawBorders(WINDOW *screen) const
{
  int x, y, i;

  getmaxyx(screen, y, x);
  y -= 99;
  x -= 99;

  mvwprintw(screen, 0, 0, "+");
  mvwprintw(screen, y - 1, 0, "+");
  mvwprintw(screen, 0, x - 1, "+");
  mvwprintw(screen, y - 1, x - 1, "+");
  for (i = 1; i < (y - 1); i++) {
    mvwprintw(screen, i, 0, "|");
    mvwprintw(screen, i, x - 1, "|");
  }
  for (i = 1; i < (x - 1); i++) {
    mvwprintw(screen, 0, i, "-");
    mvwprintw(screen, y - 1, i, "-");
  }
}
void    UIncurses::affNibbler(Object *obj, std::pair<int, int> const &size)
{
  int	x = size.first;
  int	y = size.second;
  int	ch;
  std::list<std::pair<Object::Type_block, std::pair<int, int> > > snake;
  std::list<std::pair<Object::Type_block, std::pair<int, int> > > fruit;
  std::string score;
  std::string hightscore;
  std::string speed;

  initscr();
  start_color();
  init_pair(1, COLOR_RED, COLOR_RED);
  init_pair(2, COLOR_GREEN, COLOR_GREEN);
  init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(4, COLOR_BLUE, COLOR_BLUE);

  clear();
  noecho();
  curs_set(FALSE);

  WINDOW *field = newwin(y + 100, x + 100, 0, 0);

  keypad(field, TRUE);
  this->drawBorders(field);
  mvwprintw(field, 0, x + 4, "Nibbler Ncurses");
  mvwprintw(field, 1, x + 4, "Backspace to exit");
  mvwprintw(field, 3, x + 4, "Your score : ");
  mvwprintw(field, 6, x + 4, "Hightscore : ");
  mvwprintw(field, 9, x + 4, "Speed Statut: ");
  wrefresh(field);

  nodelay(field, TRUE);
  cbreak();

  while(this->_isOver == false)
    {
      snake = obj->getObject();
      fruit = obj->getFruit();
      this->drawBorders(field);
      this->affEmpty(field);
      score = std::to_string(obj->getScore());
      hightscore = std::to_string(obj->getHightScore());
      speed = std::to_string((obj->getTime() - 300000) * -1);
      mvwprintw(field, 4, x + 4, score.c_str());
      mvwprintw(field, 7, x + 4, hightscore.c_str());
      mvwprintw(field, 10, x + 4, speed.c_str());

      for (std::list<std::pair<Object::Type_block, std::pair<int, int> > >::iterator it = snake.begin(); it != snake.end(); ++it)
        {
          if ((*it).first == 4)
            {
	      wattron(field, COLOR_PAIR(2)); 
	      mvwprintw(field, (*it).second.second, (*it).second.first, " ");
	      wattroff(field, COLOR_PAIR(2));
            }
          else if ((*it).first == 5)
            {
	      wattron(field, COLOR_PAIR(2)); 
	      mvwprintw(field, (*it).second.second, (*it).second.first, " ");
	      wattroff(field, COLOR_PAIR(2));
            }
          else if ((*it).first == 3)
            {
	      wattron(field, COLOR_PAIR(1)); 
	      mvwprintw(field, (*it).second.second, (*it).second.first, " ");
	      wattroff(field, COLOR_PAIR(1));
            }
	  else
	    mvwprintw(field, (*it).second.second, (*it).second.first, " ");
        }
      for (std::list<std::pair<Object::Type_block, std::pair<int, int> > >::iterator it = fruit.begin(); it != fruit.end(); ++it)
        {
	  if ((*it).first == 2)
	    {
	      wattron(field, COLOR_PAIR(3)); 
	      mvwprintw(field, (*it).second.second, (*it).second.first, " ");
	      wattroff(field, COLOR_PAIR(3));
	    }
	  else if ((*it).first == 6)
	    {
	      wattron(field, COLOR_PAIR(4)); 
	      mvwprintw(field, (*it).second.second, (*it).second.first, " ");
	      wattroff(field, COLOR_PAIR(4));
	    }
	}
      wrefresh(field);
      ch = wgetch(field);

      switch(ch)
      	{
      	case KEY_LEFT:
	  this->_event = EVENT_LEFT;
	  break;
      	case KEY_RIGHT:
      	  this->_event = EVENT_RIGHT;
      	  break;
	case 32:
      	  this->_event = EVENT_SPEED;
      	  break;
	case KEY_BACKSPACE:
	  this->_isOver = true;
      	  this->_event = EVENT_EXIT;
      	  break;
      	}
    }
  wclear(field);
  delwin(field);
  clear();
  endwin();
  return ;
}
