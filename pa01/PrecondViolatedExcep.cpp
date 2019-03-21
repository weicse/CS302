/**
  * @file PrecondViolatedExcep.cpp
  *
  * @brief Implementation file for precondition violated exception creation
  *
  * @details Creates function prototype for the precondition violated exceptions used in the linked list
  *
  * @version 1.00
  *		Wei Tong (15 September 2016)
  *		Initial development of the precondition violated exception class
  *
  * @note
  * 	Adapted from Frank M. Carrano and Timothy M. Henry
  * 	Copyright (c) 2012 Pearson Education, Hoboken, New Jersey.
  */
#include "PrecondViolatedExcep.h"
PrecondViolatedExcep::PrecondViolatedExcep(const string& message) : logic_error("Precondition Violated Exception: " + message){

}