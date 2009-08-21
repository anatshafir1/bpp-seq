//
// File: WordAlphabet.h
// Authors: Laurent Gueguen
//          Sylvain Gaillard
// Created on: Sun Dec 28 2008
//

/*
Copyright or © or Copr. CNRS, (November 17, 2004)

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

#include "WordAlphabet.h"

// From Utils:
#include <Utils/TextTools.h>

using namespace bpp;

// From the STL:
#include <iostream>

using namespace std;

WordAlphabet::WordAlphabet(const vector<const Alphabet* >& Valpha) :
  AbstractAlphabet(), _VAbsAlph(Valpha)
{
  build_();
}

WordAlphabet::WordAlphabet(const Alphabet* palpha, unsigned int num) :
  AbstractAlphabet()
{
  _VAbsAlph.clear();

  for (unsigned int i = 0; i < num; i++)
    _VAbsAlph.push_back(palpha);

  build_();
}

WordAlphabet::~WordAlphabet()
{
  _VAbsAlph.clear();  
}

void WordAlphabet::build_()
{
  unsigned int size = 1;
  
  for (unsigned int i = 0; i < _VAbsAlph.size(); i++)
    size *= _VAbsAlph[i]->getSize();
  
  resize(size + 2);
  
  string s = "";
  for (unsigned int i = 0; i < _VAbsAlph.size(); i++)
    s += "-";
      
  setState(0, AlphabetState(-1, s, "gap"));

  for (unsigned int i = 0; i < size; i++)
  {
    setState(i+1, AlphabetState(i, "", ""));
  }

  unsigned lr = size;
  char c;
  for (unsigned int na = 0; na < _VAbsAlph.size(); na++)
  {
    lr /= _VAbsAlph[na]->getSize();
    unsigned int j = 1;
    unsigned int i = 0;
    while (j <= size)
    {
      c = _VAbsAlph[na]->intToChar(i)[0];
      
      for (unsigned int k = 0; k < lr; k++) {
        getStateAt(j).setLetter(getStateAt(j).getLetter() + c);
        j++;
        //alphabet[j++].letter += c;
      }
      
      if (++i == _VAbsAlph[na]->getSize())
        i = 0;
    }
  }
  
  s = "";
  for (unsigned i = 0; i < _VAbsAlph.size(); i++)
    s += "N";
      
  setState(size+1, AlphabetState(size, s, "Unresolved"));
  remap();
}

/******************************************************************************/

string WordAlphabet::getAlphabetType() const
{
  string s = "Word alphabet:";
  for (unsigned int i = 0; i< _VAbsAlph.size(); i++)
    s += " " +  _VAbsAlph[i]->getAlphabetType();
  
  return s;
}

bool WordAlphabet::hasUniqueAlphabet() const
{
  string s = _VAbsAlph[0]->getAlphabetType();
  for (unsigned int i = 1; i < _VAbsAlph.size(); i++)
    if (_VAbsAlph[i]->getAlphabetType() != s)
      return false;
  return true;
}

bool WordAlphabet::containsUnresolved(const string & state) const throw (BadCharException)
{
  unsigned int s = _VAbsAlph.size();
  if (state.length() != s)
    throw BadCharException(state, "WordAlphabet::containsUnresolved", this);
  
  for (unsigned int i = 0; i < _VAbsAlph.size(); i++)
  {
    if (_VAbsAlph[i]->isUnresolved(state.substr(i, 1)))
    {
      return true;
    }
  }
  return false;
}

/******************************************************************************/

bool WordAlphabet::containsGap(const string & state) const throw (BadCharException)
{
  unsigned int s = _VAbsAlph.size();
  if (state.length() != s)
    throw BadCharException(state, "WordAlphabet::containsGap", this);
  
  for (unsigned int i = 0; i < _VAbsAlph.size(); i++)
  {
    if (_VAbsAlph[i]->isGap(state.substr(i, 1)))
      return true;
  }

  return false;
}

/******************************************************************************/

string WordAlphabet::getName(const string& state) const throw (BadCharException)
{
  if(state.size() != _VAbsAlph.size())
    throw BadCharException(state, "WordAlphabet::getName", this);
  if(containsUnresolved(state))
    return getStateAt(getSize()+1).getName();
  if(containsGap(state))
    return getStateAt(0).getName();
  else
    return AbstractAlphabet::getName(state);
}
		
/******************************************************************************/

vector<int   > WordAlphabet::getAlias(      int      state) const throw (BadIntException)
{
  if(!isIntInAlphabet(state)) throw BadIntException(state, "WordAlphabet::getAlias(int): Specified base unknown.");
  vector<int> v;
  int i, s=getSize();

  if (state == s) {
    v.resize(s);
    for (i=0;i<s;i++)
      v[i]=i;
  } else {
    v.resize(1); v[0] = state;
  }
  return v;
    
}

/******************************************************************************/

vector<string> WordAlphabet::getAlias(const string & state) const throw (BadCharException)
{
  string locstate = TextTools::toUpper(state);
  if(!isCharInAlphabet(locstate)) throw BadCharException(locstate, "WordAlphabet::getAlias(string): Specified base unknown.");
  vector<string> v;

  int i, s=getSize();
  
  string st = "";
  for ( i = 0; i < _VAbsAlph.size(); i++)
    st += "N";

  if (locstate == st) {
    v.resize(s);
    for (i=0;i<s;i++)
      v[i]=intToChar(i);
  } else {
    v.resize(1); v[0] = state;
  }		
  return v;

}

/******************************************************************************/

int    WordAlphabet::getGeneric(const vector<int   > & states) const throw (BadIntException)
{
  return states[0];
}

/******************************************************************************/

string WordAlphabet::getGeneric(const vector<string> & states) const throw (BadCharException)
{
  return states[0];
}



/******************************************************************************/

int WordAlphabet::getWord(vector<int>& vint, unsigned int pos) const throw (BadIntException)
{
  if (vint.size() < pos + _VAbsAlph.size())
    throw BadIntException(vint.size(), "WordAlphabet::getWord", this);
  
  vector<string> vs;
  for (unsigned int i = 0; i < _VAbsAlph.size(); i++)
    vs.push_back(_VAbsAlph[i]->intToChar(vint[i + pos]));

  return charToInt(getWord(vs));//This can't throw a BadCharException!
}

/****************************************************************************************/

string WordAlphabet::getWord(const vector<string>& vpos, unsigned int pos) const throw (BadIntException, BadCharException)
{
  if (vpos.size() < pos + _VAbsAlph.size())
    throw BadIntException(vpos.size(), "WordAlphabet::getWord", this);
  
  string s = "";
  for (unsigned int i = 0; i < _VAbsAlph.size(); i++)
    s += vpos[pos + i];
  // test
  charToInt(s);
  return s;
}

/****************************************************************************************/

Sequence * WordAlphabet::translate(const Sequence & sequence, int pos) const throw (AlphabetMismatchException, Exception)
{
  if ((! hasUniqueAlphabet()) or
      (sequence.getAlphabet()->getAlphabetType() != _VAbsAlph[0]->getAlphabetType()))
    throw AlphabetMismatchException("No matching alphabets", sequence.getAlphabet(), _VAbsAlph[0]);


  vector<int> v1 = sequence.getContent();
  vector<int> v2;

  unsigned int s = sequence.size();
  unsigned int l = getLength();
  unsigned int i = pos;
  
  while (i + l < s)
  {
    v2.push_back(getWord(v1, i));
    i += l;
  }

  return new Sequence(sequence.getName(), v2, this);
}

/****************************************************************************************/

Sequence * WordAlphabet::reverse(const Sequence & sequence) const throw (AlphabetMismatchException, Exception)
{
  if ((! hasUniqueAlphabet()) or
      (sequence.getAlphabet()->getAlphabetType() != getAlphabetType()))
    throw AlphabetMismatchException("No matching alphabets");

  Sequence* pseq = new Sequence(sequence.getName(), "", getNAlphabet(0));

  unsigned int s = sequence.size();
  for (unsigned int i = 0; i < s; i++)
    pseq->append(getPositions(sequence[i]));

  return pseq;
}

