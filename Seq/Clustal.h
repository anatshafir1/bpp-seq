//
// File: Clustal.h
// Created by: Julien Dutheil
// Created on: ?
//

/*
Copyright or � or Copr. CNRS, (November 17, 2004)

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

#ifndef _CLUSTAL_H_
#define _CLUSTAL_H_

#include "AbstractISequence2.h"
#include "AlignedSequenceContainer.h"

// From the STL:
#include <iostream>
using namespace std;

namespace bpp
{

/**
 * @brief The clustal sequence file format.
 *
 * An AlignedSequenceContainer object is used instead of a VectorSequenceContainer.
 */
class Clustal:
  public virtual AbstractISequence2
{
  public:
    bool checkNames_;
    unsigned int nbSpacesBeforeSeq_;

	public:
    /**
     * @brief Build a new Clustal object.
     *
     * @param checkNames Tell if the names in the file should be checked for unicity (slower, in o(n*n) where n is the number of sequences).
     * @param nbExtraSpacesBeforeSeq Specify the number of extra space characters separating the sequence name form content. The default is 5 (hence 6 spaces in total) for backward compatibility, using 0 will not allow for any space in the sequence names.
     */
		Clustal(bool checkNames = true, unsigned int nbExtraSpacesBeforeSeq = 5) throw (Exception): checkNames_(checkNames), nbSpacesBeforeSeq_(nbExtraSpacesBeforeSeq + 1) {};
		virtual ~Clustal() {};

	public:

		/**
		 * @name The AbstractISequence2 interface.
  	 *
		 * @{
		 */	
		void appendFromStream(istream & input, AlignedSequenceContainer & sc) const throw (Exception);
		/** @} */

		/**
		 * @name The IOSequence interface.
		 *
		 * @{
		 */
		const string getFormatName() const { return "Clustal"; }

		const string getFormatDescription() const { return "The Clustal alignment tool output format."; }

		/** @} */

    /**
     * @return true if the names are to be checked when reading sequences from files.
     */
    bool checkNames() const { return checkNames_; }

    /**
     * @brief Tell whether the sequence names should be checked when reading from files.
     *
     * @param yn whether the sequence names should be checked when reading from files.
     */
    void checkNames(bool yn) { checkNames_ = yn; }
};

} //end of namespace bpp.

#endif // _CLUSTAL_H_

