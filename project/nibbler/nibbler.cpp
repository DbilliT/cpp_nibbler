//
// nibbler.cpp for nibbler in /home/bechad_p/rendu/cpp_nibbler/project/nibbler/src
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Thu Mar 26 11:22:25 2015 Pierre Bechade
// Last update Sun Apr  5 14:09:02 2015 Pierre Bechade
//

#include "nibbler.hh"

Nibbler::Nibbler()
{
}

Nibbler::Nibbler(int ac, char **av)
{
  this->handling_arg(ac, av);
  std::fstream	fichier("hightscore.txt");
  Object	*object;

  if (!fichier)
    object = new Object(false);
  else
    {
      std::string hscore;

      std::getline(fichier, hscore);
      if (hscore.empty())
	hscore = "0";
      object = new Object(false, std::atoi(hscore.c_str()));
      fichier.close();
    }

  Game		*game = new Game(std::atoi(av[1]), std::atoi(av[2]), av[3]);

  object->createSnake(game->getSizeX(), game->getSizeY());
  object->addFruit(object->FRUIT, game->getSizeX(), game->getSizeY());
  game->setObject(object);
  this->runGame(game, av[3]);
  this->FileHightScore(object);
  dlclose(this->_dhandle);
  delete object;
  delete game;
}

Nibbler::~Nibbler()
{
}

void	Nibbler::runGame(Game *game, std::string const &lib)
{
  game->run(this->checkLib(lib));
}

void	Nibbler::FileHightScore(Object *object) const
{
  std::ofstream outfile("hightscore.txt", std::ofstream::binary);

  if (object->getHightScore() < object->getScore())
    outfile.write(std::to_string(object->getScore()).c_str(), std::to_string(object->getScore()).size());
  else
    outfile.write(std::to_string(object->getHightScore()).c_str(), std::to_string(object->getHightScore()).size());
  outfile.close();
}

INibblerDisplay	*Nibbler::checkLib(std::string const &lib)
{
  try
    {
      INibblerDisplay* (*external_creator)();
      void  *dhandle;

      if ((dhandle = dlopen(lib.c_str(), RTLD_LAZY)) == NULL)
	{
	  std::string conc = "./";
	  conc += lib;
	  if ((dhandle = dlopen(conc.c_str(), RTLD_LAZY)) == NULL)
	    {
	      throw std::runtime_error(dlerror());
	    }
	}
      if ((external_creator = reinterpret_cast<INibblerDisplay* (*)()>(dlsym(dhandle, "create_object"))) == NULL)
	{
	  throw std::runtime_error(dlerror());
	}
      INibblerDisplay *Display = external_creator();

      this->_dhandle = dhandle;
      return (Display);
    }
  catch (std::runtime_error& e)
    {
      std::cerr << e.what() << std::endl;
      std::exit (EXIT_FAILURE);
    }
}

void    Nibbler::handling_arg(int ac, char **av) const
{
  try
    {
      if (ac != 4)
      	throw std::invalid_argument("usage : ./nibbler [AREA_WIDTH] [AREA_HEIGHT] [LIB.so]");
      std::string lib = av[3];
      if (std::atoi(av[1]) < 10 || std::atoi(av[2]) < 10)
	throw std::invalid_argument("nibbler error : area size can't be negative or too small : Need to be superior or egual to 10");
      std::ifstream f(lib.c_str());
      if (std::atoi(av[1]) > 60 || std::atoi(av[2]) > 60)
	throw std::invalid_argument("nibbler error : are size can't be superior to 60 in x or y");
      if (!f.good())
	{
	  throw Wrong_file ("nibbler error : file", lib);
	  f.close();
	} 
      else
	{
	  std::string ext(".so");
	  if (lib.size() <= 3)
	    throw Wrong_file ("nibbler error : file", lib);
	  if (lib.compare(lib.size()-3, 3, ext) != 0)
	    throw Wrong_file ("nibller error : file", lib);
	  f.close();
	}  
    }
  catch (std::invalid_argument& e)
    {
      std::cerr << e.what() << std::endl;
      std::exit(EXIT_FAILURE);
    }
  catch (Wrong_file& e)
    {
      e.what();
      std::exit(EXIT_FAILURE);
    }
}

int		main(int ac, char **av)
{
  Nibbler	nib(ac, av);

  return (EXIT_SUCCESS);
}
