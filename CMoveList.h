#ifndef _C_MOVELIST_H_
#define _C_MOVELIST_H_

#include <iostream>
#include <vector>

#include "CMove.h"

/***************************************************************
 * declaration of CMoveList
 *
 * This is a wrapper for the std::vector class.
 * It contains an array of moves.
 ***************************************************************/

class CMoveList
{
    public:
        CMoveList()
        {
            // Pre-allocate space for a large number of moves.
            // This is a slight optimization.
            m_moveList.reserve(100);//allocation of 100 space for m_moveList
        }

        friend std::ostream& operator <<(std::ostream &os, const CMoveList &rhs);

        void push_back(const CMove& move)
        {
            m_moveList.push_back(move);//appending of object in vector m_moveList
        }

        void clear()
        {
            m_moveList.clear();    //clearing of object from vector
        }

        unsigned int size() const
        {
            return m_moveList.size();//Number of elements in m_moveList vector
        }

        const CMove & operator [] (unsigned int ix) const { return m_moveList[ix]; }
        
    private:
    	std::vector<CMove> m_moveList;
        //create of vector of object

}; /* end of CMoveList */

#endif // _C_MOVELIST_H_

