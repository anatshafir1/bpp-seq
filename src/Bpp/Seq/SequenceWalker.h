//
// File: SequenceWalker.h
// Created by: Julien Dutheil
// Created on: Thu Nov 24 2011
//

/*
Copyright or © or Copr. Bio++ Development Team, (November 17, 2011)

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

#ifndef _SEQUENCEWALKER_H_
#define _SEQUENCEWALKER_H_

#include "Sequence.h"

namespace bpp
{

/**
 * @brief A helper class to easily convert coordinates between sequence and alignments.
 *
 * Coordinates are 0-based.
 * The walker will be more efficient if coordinates are called in pre-ordered way.
 */
class SequenceWalker
{
  private:
    const Sequence* seq_;
    unsigned int seqPos_, alnPos_;
    int gap_;

  public:
    SequenceWalker(const Sequence& seq):
      seq_(&seq), seqPos_(0), alnPos_(0), gap_(seq.getAlphabet()->getGapCharacterCode()) {
      if (seq_->size() > 0) {
        while ((*seq_)[alnPos_] == gap_)
          ++alnPos_;
      }
    }
    SequenceWalker(const SequenceWalker& walker):
      seq_(walker.seq_), seqPos_(walker.seqPos_), alnPos_(walker.alnPos_), gap_(walker.gap_) {}
    SequenceWalker& operator=(const SequenceWalker& walker) {
      seq_    = walker.seq_;
      seqPos_ = walker.seqPos_;
      alnPos_ = walker.alnPos_;
      gap_    = walker.gap_;
      return *this;
    }
    virtual ~SequenceWalker() {}

  public:
    unsigned int getAlignmentPosition(unsigned int seqPos) throw (Exception);
    unsigned int getSequencePosition(unsigned int alnPos) throw (Exception);
};

} //end of namespace bpp.

#endif //_SEQUENCEWALKER_H_
