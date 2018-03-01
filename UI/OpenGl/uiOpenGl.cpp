//
// uiOpenGl.cpp for uiOpenGL in /home/bechad_p/rendu/cpp_nibbler/UI/OpenGl
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Wed Apr  1 12:02:43 2015 Pierre Bechade
// Last update Sun Jul 19 17:26:52 2015 Pierre Bechade
//

#include "uiOpenGl.hh"

extern "C"
{
  INibblerDisplay *create_object() { return new UIOpenGl(); }
}

UIOpenGl::UIOpenGl()
{
  this->_event = EVENT_UNKNOWN;
  this->_isOver = false;
}

UIOpenGl::~UIOpenGl()
{
}

d_event UIOpenGl::getEvent() const
{
  return (this->_event);
}

void    UIOpenGl::setIsOver(bool b)
{
  this->_isOver = b;
}

void    UIOpenGl::setEvent(d_event ev)
{
  (void) ev;
  this->_event = EVENT_UNKNOWN;
}

void	UIOpenGl::addCube(int x, int y, int type) const
{
  glBegin(GL_QUADS);

  if (type == 1)
    glColor3ub(255, 128, 0);
  else if (type == 2)
    glColor3ub(249, 18, 18);
  else if (type == 3)
    glColor3ub(204, 0, 0);
  else if (type == 4)
    glColor3ub(51, 70, 0);
  else
    glColor3ub(91, 86, 230);

  if (type != 1)
    {
      glVertex3d(x + 1, y + 1, 1);
      glVertex3d(x + 1, y + 1, 0);
      glVertex3d(x, y + 1, 0);
      glVertex3d(x, y + 1, 1);
    }
  else
    {
      glVertex3d(x + 1, y + 1, 0.5);
      glVertex3d(x + 1, y + 1, 0);
      glVertex3d(x, y + 1, 0);
      glVertex3d(x, y + 1, 0.5);
    }

  if (type == 1)
    glColor3ub(100, 0, 0);
  else if (type == 2)
    glColor3ub(249, 18, 18);
  else if (type == 3)
    glColor3ub(204, 0, 0);
  else if (type == 4)
    glColor3ub(51, 154, 0);
  else
    glColor3ub(91, 86, 230);

  if (type != 1)
    {
      glVertex3d(x + 1, y, 1);
      glVertex3d(x + 1, y + 1, 1);
      glVertex3d(x, y + 1, 1);
      glVertex3d(x, y, 1);
    }
  else
    {
      glVertex3d(x + 1, y, 0.5);
      glVertex3d(x + 1, y + 1, 0.5);
      glVertex3d(x, y + 1, 0.5);
      glVertex3d(x, y, 0.5);
    }

  if (type == 1)
    glColor3ub(255, 128, 0);
  else if (type == 2)
    glColor3ub(249, 18, 18);
  else if (type == 3)
    glColor3ub(204, 0, 0);
  else if (type == 4)
    glColor3ub(51, 102, 0);
  else
    glColor3ub(91, 86, 230);

  if (type != 1)
    {
      glVertex3d(x + 1, y, 1);
      glVertex3d(x + 1, y, 0);
      glVertex3d(x + 1, y + 1, 0);
      glVertex3d(x + 1, y + 1, 1);
    }
  else
    {
      glVertex3d(x + 1, y, 0.5);
      glVertex3d(x + 1, y, 0);
      glVertex3d(x + 1, y + 1, 0);
      glVertex3d(x + 1, y + 1, 0.5);
    }

  glEnd();
}

void    UIOpenGl::view(std::list<std::pair<Object::Type_block, std::pair<int, int> > > &snake) const
{
  std::list<std::pair<Object::Type_block, std::pair<int, int> > >::iterator it;

  for (it = snake.begin(); it != snake.end(); ++it)
    {
      if ((*it).first == 3)
        {
          gluLookAt((*it).second.first + 20, (*it).second.second + 20, 20,
                    (*it).second.first, (*it).second.second, 0, 0, 0, 1);
          return ;
        }
    }
}

void    UIOpenGl::addUnder(int x_max, int y_max) const
{
  int           x = 0;
  int           y = y_max + 1;

  while (x <= x_max)
    {
      addCube(x, y, 1);
      ++x;
    }
  y = 0;
  x = x_max + 1;
  while (y <= y_max + 1)
    {
      addCube(x, y, 1);
      ++y;
    }
}

void    UIOpenGl::addTop(int x_max, int y_max) const
{
  int           x = 0;
  int           y = 0;

  while (y != y_max + 1)
    {
      addCube(x, y, 1);
      ++y;
    }
  y = 0;
  x = 1;
  while (x != x_max + 1)
    {
      addCube(x, y, 1);
      ++x;
    }
}


void	UIOpenGl::addGround(int x_max, int y_max) const
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_QUADS);
  glColor3d(255, 255, 255);
  glVertex3i(0, 0, 0);
  glVertex3i(0, x_max + 1, 0);
  glVertex3i(y_max + 1, x_max + 1, 0);
  glVertex3i(y_max + 1, 0, 0);
  glEnd();
}


void    UIOpenGl::affNibbler(Object *obj, std::pair<int, int> const &size)
{
  int	x = size.first;
  int	y = size.second;
  std::list<std::pair<Object::Type_block, std::pair<int, int> > > snake;
  std::list<std::pair<Object::Type_block, std::pair<int, int> > > fruit;
  std::list<std::pair<Object::Type_block, std::pair<int, int> > >::iterator it;
  SDL_Event my_event;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("OpenGl Nibbler", NULL);
  SDL_SetVideoMode(1920, 1080, 32, SDL_OPENGL | SDL_FULLSCREEN);

  glMatrixMode(GL_PROJECTION);
  gluPerspective(35, (double)1920/1080, 1, 1000);

  while (this->_isOver == false)
    {
      snake = obj->getObject();
      fruit = obj->getFruit();

      glEnable(GL_DEPTH_TEST);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      view(snake);

      addGround(y - 1, x - 1);
      addTop(x - 1, y - 1);

      for (it = snake.end(); it != snake.begin(); --it)
	{
	  if ((*it).first == 5)
	    addCube((*it).second.first, (*it).second.second, 4);
	  if ((*it).first == 4)
	    addCube((*it).second.first, (*it).second.second, 4);
	}
      if ((*it).first == 3)
	addCube((*it).second.first, (*it).second.second, 3);
      for (it = fruit.begin(); it != fruit.end(); ++it)
	{
	  if ((*it).first == 2)
	    addCube((*it).second.first, (*it).second.second, 2);
	  if ((*it).first == 6)
	    addCube((*it).second.first, (*it).second.second, 5);
	}
      addUnder(x - 1, y - 1);
      glFlush();
      SDL_GL_SwapBuffers();
      while( SDL_PollEvent( &my_event ) )
	{
	  switch(my_event.type)
	    {
	    case SDL_KEYDOWN:
	      switch (my_event.key.keysym.sym)
		{
		case SDLK_RIGHT:
		  this->_event = EVENT_LEFT;
		  break;
		  while( SDL_PollEvent( &my_event ) )
		    {
		      switch(my_event.type)
			{
			case SDL_KEYDOWN:
			  switch (my_event.key.keysym.sym)
			    {
			    case SDLK_RIGHT:
			      this->_event = EVENT_LEFT;
			      break;
			    case SDLK_LEFT:
			      this->_event = EVENT_RIGHT;
			      break;
			    case SDLK_SPACE:
			      this->_event = EVENT_SPEED;
			      break;
			    case SDLK_ESCAPE:
			      this->_event = EVENT_EXIT;
			      break;
			    default:
			      break;
			    }
			default:
			  break;
			}
		    }
case SDLK_LEFT:
		  this->_event = EVENT_RIGHT;
		  break;
		case SDLK_SPACE:
		  this->_event = EVENT_SPEED;
		  break;
		case SDLK_ESCAPE:
		  this->_event = EVENT_EXIT;
		  break;
		default:
		  break;
		}
	    default:
	      break;
	    }
	}
    }
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
  SDL_Quit();
  return ;
}
