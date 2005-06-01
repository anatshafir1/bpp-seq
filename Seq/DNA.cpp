//
// File: DNA.cpp
// Created by: Guillaume Deuchst
// Created on: Tue Jul 22 2003
//

/*
Copyright ou � ou Copr. CNRS, (17 Novembre 2004) 

Julien.Dutheil@univ-montp2.fr

Ce logiciel est un programme informatique servant � fournir des classes
pour l'analyse de s�quences.

Ce logiciel est r�gi par la licence CeCILL soumise au droit fran�ais et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffus�e par le CEA, le CNRS et l'INRIA 
sur le site "http://www.cecill.info".

En contrepartie de l'accessibilit� au code source et des droits de copie,
de modification et de redistribution accord�s par cette licence, il n'est
offert aux utilisateurs qu'une garantie limit�e.  Pour les m�mes raisons,
seule une responsabilit� restreinte p�se sur l'auteur du programme,  le
titulaire des droits patrimoniaux et les conc�dants successifs.

A cet �gard  l'attention de l'utilisateur est attir�e sur les risques
associ�s au chargement,  � l'utilisation,  � la modification et/ou au
d�veloppement et � la reproduction du logiciel par l'utilisateur �tant 
donn� sa sp�cificit� de logiciel libre, qui peut le rendre complexe � 
manipuler et qui le r�serve donc � des d�veloppeurs et des professionnels
avertis poss�dant  des  connaissances  informatiques approfondies.  Les
utilisateurs sont donc invit�s � charger  et  tester  l'ad�quation  du
logiciel � leurs besoins dans des conditions permettant d'assurer la
s�curit� de leurs syst�mes et ou de leurs donn�es et, plus g�n�ralement, 
� l'utiliser et l'exploiter dans les m�mes conditions de s�curit�. 

Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez 
pris connaissance de la licence CeCILL, et que vous en avez accept� les
termes.
*/

/*
Copyright or � or Copr. CNRS, (November 17, 2004)

Julien.Dutheil@univ-montp2.fr

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

#include "DNA.h" // class's header file

// class constructor
DNA::DNA()
{
	// Alphabet size definition
	alphabet.resize(20);

	// Alphabet content definition
	// all unresolved bases use n�14
	alphabet[0].num = -1;
  alphabet[0].letter = "-";
  alphabet[0].name = "gap";
	
  alphabet[1].num = 0;
  alphabet[1].letter = "A";
  alphabet[1].name = "Adenine";
	
  alphabet[2].num = 1;
  alphabet[2].letter = "C";
  alphabet[2].name = "Cytosine";
	
  alphabet[3].num = 2;
  alphabet[3].letter = "G";
  alphabet[3].name = "Guanine";
	
  alphabet[4].num = 3;
  alphabet[4].letter = "T";
  alphabet[4].name = "Thymine";
		
  alphabet[5].num = 4;
  alphabet[5].letter = "M";
  alphabet[5].name = "Adenine or Cytosine";
		
  alphabet[6].num = 5;
  alphabet[6].letter = "R";
  alphabet[6].name = "Purine (Adenine or Guanine)";
		
  alphabet[7].num = 6;
  alphabet[7].letter = "W";
  alphabet[7].name = "Adenine or Thymine";
		
  alphabet[8].num = 7;
  alphabet[8].letter = "S";
  alphabet[8].name = "Cytosine or Guanine";
		
  alphabet[9].num = 8;
  alphabet[9].letter = "Y";
  alphabet[9].name = "Pyrimidine (Cytosine or Thymine)";
		
  alphabet[10].num = 9;
  alphabet[10].letter = "K";
  alphabet[10].name = "Guanine or Thymine";
		
  alphabet[11].num = 10;
  alphabet[11].letter = "V";
  alphabet[11].name = "Adenine or Cytosine or Guanine";
		
  alphabet[12].num = 11;
  alphabet[12].letter = "H";
  alphabet[12].name = "Adenine or Cytosine or Thymine";
		
  alphabet[13].num = 12;
  alphabet[13].letter = "D";
  alphabet[13].name = "Adenine or Guanine or Thymine";
		
  alphabet[14].num = 13;
  alphabet[14].letter = "B";
  alphabet[14].name = "Cytosine or Guanine or Thymine";
		
  alphabet[15].num = 14;
  alphabet[15].letter = "N";
  alphabet[15].name = "Unresolved base";
  alphabet[16].num = 14;
  alphabet[16].letter = "X";
  alphabet[16].name = "Unresolved base";
  alphabet[17].num = 14;
  alphabet[17].letter = "O";
  alphabet[17].name = "Unresolved base";
  alphabet[18].num = 14;
  alphabet[18].letter = "0";
  alphabet[18].name = "Unresolved base";
  alphabet[19].num = 14;
  alphabet[19].letter = "?";
  alphabet[19].name = "Unresolved base";
}

/****************************************************************************************/

vector<int> DNA::getAlias(int state) const throw (BadIntException) 
{
	if(!isIntInAlphabet(state)) throw BadIntException(state, "DNA::getAlias(int): Specified base unknown.");
	vector<int> v;
	if(state == 4) {// A or C
		v.resize(2); v[0] = 0; v[1] = 1;
	} else if(state == 5) {// A or G
		v.resize(2); v[0] = 0; v[1] = 2;
	} else if(state == 6) {// A or T
		v.resize(2); v[0] = 0; v[1] = 3;
	} else if(state == 7) {// C or G
		v.resize(2); v[0] = 1; v[1] = 2;
	} else if(state == 8) {// C or T
		v.resize(2); v[0] = 1; v[1] = 3;
	} else if(state == 9) {// G or T
		v.resize(2); v[0] = 2; v[1] = 3;
	} else if(state == 10) {// A, C or G
		v.resize(3); v[0] = 0; v[1] = 1; v[2] = 2;
	} else if(state == 11) {// A, C or T
		v.resize(3); v[0] = 0; v[1] = 1; v[2] = 3;
	} else if(state == 12) {// A, G or T
		v.resize(3); v[0] = 0; v[1] = 2; v[2] = 3;
	} else if(state == 13) {// C, G or T
		v.resize(3); v[0] = 1, v[1] = 2; v[2] = 3;
	} else if(state == 14) {// A, C, G or T
		v.resize(4); v[0] = 0; v[1] = 1; v[2] = 2; v[3] = 3;
	} else {
		v.resize(1); v[0] = state;
	}		
	return v;
}


/****************************************************************************************/

vector<string> DNA::getAlias(const string & state) const throw (BadCharException) 
{
	if(!isCharInAlphabet(state)) throw BadCharException(state, "DNA::getAlias(int): Specified base unknown.");
	vector<string> v;
	if(state == "M") {// A or C
		v.resize(2); v[0] = "A"; v[1] = "C";
	} else if(state == "R") {// A or G
		v.resize(2); v[0] = "A"; v[1] = "G";
	} else if(state == "W") {// A or T
		v.resize(2); v[0] = "A"; v[1] = "T";
	} else if(state == "S") {// C or G
		v.resize(2); v[0] = "C"; v[1] = "G";
	} else if(state == "Y") {// C or T
		v.resize(2); v[0] = "C"; v[1] = "T";
	} else if(state == "K") {// G or T
		v.resize(2); v[0] = "G"; v[1] = "T";
	} else if(state == "V") {// A, C or G
		v.resize(3); v[0] = "A"; v[1] = "C"; v[2] = "G";
	} else if(state == "H") {// A, C or T
		v.resize(3); v[0] = "A"; v[1] = "C"; v[2] = "T";
	} else if(state == "D") {// A, G or T
		v.resize(3); v[0] = "A"; v[1] = "G"; v[2] = "T";
	} else if(state == "B") {// C, G or T
		v.resize(3); v[0] = "C", v[1] = "G"; v[2] = "T";
	} else if(state == "N"
         || state == "X"
	       || state == "O"
	       || state == "0"
	       || state == "?") {// A, C, G or T
		v.resize(4); v[0] = "A"; v[1] = "C"; v[2] = "G"; v[3] = "T";
	} else {
		v.resize(1); v[0] = state;
	}		
	return v;
}

/****************************************************************************************/

