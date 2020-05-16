//
// File: test_io.cpp
// Created by: Julien Dutheil
// Created on: Mon Nov 01 10:16 2010
//

/*
Copyright or © or Copr. Bio++ Development Team, (November 17, 2004)

This software is a computer program whose purpose is to provide classes
for numerical calculus. This file is part of the Bio++ project.

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

#include <Bpp/Seq/Alphabet/IntegerAlphabet.h>
#include <Bpp/Seq/Alphabet/ChromosomeAlphabet.h>
#include <Bpp/Seq/Alphabet/BinaryAlphabet.h>
#include <Bpp/Seq/Alphabet/DNA.h>
#include <Bpp/Seq/Alphabet/LexicalAlphabet.h>
#include <Bpp/Seq/Io/AbstractISequence.h>
#include <Bpp/Seq/Io/ISequence.h>
#include <Bpp/Seq/Container/VectorSequenceContainer.h>
#include <Bpp/Seq/Container/VectorSiteContainer.h>
#include <Bpp/Seq/Alphabet/NucleicAlphabet.h>
#include <Bpp/Seq/Io/Fasta.h>
#include <iostream>

using namespace bpp;
using namespace std;
unsigned int _MAX_CHR_NUM= 15;


//int get_max_chr_number(const std::string &path);

//VectorSequenceContainer* resizeAlphabetForSequenceContainer(VectorSequenceContainer* vs, unsigned int max_chr_number);
VectorSiteContainer* resizeAlphabetForSequenceContainer(VectorSequenceContainer* vs, unsigned int max_chr_number);

/* VectorSequenceContainer* resizeAlphabetForSequenceContainer(VectorSequenceContainer* vs, unsigned int max_chr_number){

  size_t number_of_sequences = vs->getNumberOfSequences();
  vector <string> sequence_names = vs->getSequencesNames();
  ChromosomeAlphabet* new_alphabet = new ChromosomeAlphabet(max_chr_number);
  VectorSequenceContainer* resized_alphabet_sequence_container = new VectorSequenceContainer(new_alphabet);
  for (size_t i = 0; i < number_of_sequences; i++){
    BasicSequence seq = vs->getSequence(sequence_names[i]);
    BasicSequence new_seq = BasicSequence(seq.getName(), seq.getChar(0), new_alphabet);
    resized_alphabet_sequence_container->addSequence(new_seq);

  }
  return resized_alphabet_sequence_container;

} */
VectorSiteContainer* resizeAlphabetForSequenceContainer(VectorSequenceContainer* vs, unsigned int max_chr_number){

  size_t number_of_sequences = vs->getNumberOfSequences();
  vector <string> sequence_names = vs->getSequencesNames();
  ChromosomeAlphabet* new_alphabet = new ChromosomeAlphabet(1, max_chr_number);
  VectorSiteContainer* resized_alphabet_site_container = new VectorSiteContainer(new_alphabet);
  for (size_t i = 0; i < number_of_sequences; i++){
    BasicSequence seq = vs->getSequence(sequence_names[i]);
    BasicSequence new_seq = BasicSequence(seq.getName(), seq.getChar(0), new_alphabet);
    resized_alphabet_site_container->addSequence(new_seq);

  }
  return resized_alphabet_site_container;

}




int main() {
  string path = "/home/anats/phd_project/example1.fasta";
  //const vector <std :: string> vocabulary = create_vocabulary();
  //IntegerAlphabet* alpha = new IntegerAlphabet(_MAX_CHR_NUM);
  unsigned int global_max = 25;
  ChromosomeAlphabet* alpha = new ChromosomeAlphabet(1, global_max);
  Fasta fasta;
  VectorSequenceContainer* initial_set_of_sequences = fasta.readSequences(path, alpha);
  size_t number_of_sequences = initial_set_of_sequences->getNumberOfSequences();
  vector <string> sequence_names = initial_set_of_sequences->getSequencesNames();
  unsigned int max_number_of_chr = 1; //the minimal number of chromosomes cannot be zero
  for (size_t i = 0; i < number_of_sequences; i++){
    //Sequence* seq_pointer = new BasicSequence(alpha);
    BasicSequence seq = initial_set_of_sequences->getSequence(sequence_names[i]);
    int sequence_content = seq.getValue(0);
    if ((sequence_content == -1) | (sequence_content == static_cast<int>(global_max)+1)){
      continue;
    }
    if ((unsigned int) sequence_content > max_number_of_chr){
      max_number_of_chr = sequence_content;
    }
    
    //cout << sequence_content <<endl;    
  }
  max_number_of_chr += 10;
  std :: cout <<"max chr number is: "<< max_number_of_chr <<endl;
  //VectorSequenceContainer* new_vs = resizeAlphabetForSequenceContainer(initial_set_of_sequences, max_number_of_chr);
  VectorSiteContainer* new_vs = resizeAlphabetForSequenceContainer(initial_set_of_sequences, max_number_of_chr);
  delete initial_set_of_sequences;
  for (size_t i = 0; i < new_vs->getNumberOfSequences(); i++){
    //Sequence* seq_pointer = new BasicSequence(alpha);
    vector <string> sequence_names_new = new_vs->getSequencesNames();
    BasicSequence seq = new_vs->getSequence(sequence_names_new[i]);
    int sequence_content = seq.getValue(0);
    cout << sequence_content <<endl;    
  }
   

  return 0;
}
