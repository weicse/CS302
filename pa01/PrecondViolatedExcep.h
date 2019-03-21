/**
  * @file PrecondViolatedExcep.h
  *
  * @brief Header file for precondition violated exception creation
  *
  * @details Creates function prototype for the precondition violated exceptions used in the linked list
  *
  * @version 1.00
  *			Wei Tong (15 September 2016)
  *			Initial development of the precondition violated exception class
  *
  * @note Reference
  *     Adapted from Frank M. Carrano and Timothy M. Henry
  *     Copyright (c) 2012 Pearson Education, Hoboken, New Jersey.
  */
#ifndef _PRECOND_VIOLATED_EXCEP
#define _PRECOND_VIOLATED_EXCEP
#include <stdexcept>
#include <string>
using namespace std;

class PrecondViolatedExcep : public logic_error{
public:
	PrecondViolatedExcep(const string& message = "");
};

#endif