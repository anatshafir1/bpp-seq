//
// File: BinaryAlphabet.cpp
// Authors: Laurent Gueguen
// Created on: vendredi 20 septembre 2013, � 23h 10
//

/*
   Copyright or � or Copr. Bio++ Development Team, (November 17, 2004)

   This software is a computer program whose purpose is to provide classes
   for sequences analysis.

   This software is governed by the CeCILL  license under French law and
   abiding by the rules of distribution of free software.  You can  use,
   modify and/ or redistribute the software under the terms of the CeCILL
   license as circulated by CEA, CNRS and INRIA at the following URL
   "http://www.cecill.info".

   As a counterpart to the access to the source code and  rights to copy,
   modify and redistribute granted by the license, users are provided only
   with a limited warranty  and the software's author,  the holder of the
   economic rights,  and the successive licensors  have only  limited
   liability.

   In this respect, the user's attention is drawn to the risks associated
   with loading,  using,  modifying and/or developing or reproducing the
   software by the user in light of its specific status of free software,
   that may mean  that it is complicated to manipulate,  and  that  also
   therefore means  that it is reserved for developers  and  experienced
   professionals having in-depth computer knowledge. Users are therefore
   encouraged to load and test the software's suitability as regards their
   requirements in conditions enabling the security of their systems and/or
   data to be ensured and,  more generally, to use and operate it in the
   same conditions as regards security.

   The fact that you are presently reading this means that you have had
   knowledge of the CeCILL license and that you accept its terms.
 */


#include "ChromosomeAlphabet.h"
#include "AbstractAlphabet.h"
#include "AlphabetState.h"

// From Utils:
#include <Bpp/Text/TextTools.h>

using namespace bpp;

ChromosomeAlphabet::ChromosomeAlphabet(unsigned int min, unsigned int max) : MIN_(min),MAX_(max)
{
  // Alphabet size definition
  //resize(MAX_);

  // Alphabet content definition
  registerState(new AlphabetState(-1, "-", "Gap"));

  for (int i = static_cast<int>(MIN_); i < static_cast<int>(MAX_)+1; i++)
  {
    registerState(new AlphabetState(i, TextTools::toString(i), ""));
  }
  registerState(new AlphabetState(static_cast<int>(MAX_)+1, "X", "Unresolved state"));
}

const AlphabetState& ChromosomeAlphabet::getState(int num) const {
      if (num == 0){
        num = (int)MIN_;
      }
      return(AbstractAlphabet::getState(num));

}

std::vector<int> ChromosomeAlphabet::getAlias(int state) const{
  if (!isIntInAlphabet(state)) throw BadIntException(state, "ChromosomeAlphabet::getAlias(int): Specified chromosome number unknown.");
  std::vector<int> v;
  if (state == static_cast<int>(MAX_+1)){
    for (int i = static_cast<int>(MIN_); i <= static_cast<int>(MAX_); i++){
      v.push_back(i);
    }
  }else{
    v.push_back(state);
  } 
  return v;
}

std::vector<std::string> ChromosomeAlphabet::getAlias(const std::string& state) const{
  if (!isCharInAlphabet(state)) throw BadCharException(state, "ChromosomeAlphabet::getAlias(char): Specified chromosome number unknown.");
  std::vector<std::string> v;
  if (state == "X"){
    for (int i = static_cast<int>(MIN_); i <= static_cast<int>(MAX_); i++){
      v.push_back(intToChar(i));
    }
  }else{
    v.push_back(state);
  }
  return v;
}