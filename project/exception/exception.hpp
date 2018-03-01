// file: exception.hpp
//
// by: deluss_c, bechad_p
//
// desc: class exception

#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <list>
#include <exception>
#include <stdexcept> 
#include "nibbler.hh"

class Exception : public std::exception
{
public:
  Exception(std::string const &error) throw() : _error(error) {}
  virtual ~Exception() throw() {}
  virtual const char *what() const throw()
  {
    return _error.c_str();
  }
protected:
  std::string const _error;
};

class Wrong_file : public Exception
{
public:
  Wrong_file(std::string const &error, std::string const &content) throw() : Exception(error), _content(content) {}
  virtual ~Wrong_file() throw() {}
  virtual const char *what() const throw()
  {
    std::cerr << _error << " " << _content << " is not a lib.so or does'nt exist" << std::endl;
    return _error.c_str();
  }
private:
  std::string const _content;
};

#endif /* EXCEPTION_HPP */
