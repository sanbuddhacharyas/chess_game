#include<vector>
#include<iostream>
using namespace std;


class do_
{
	public:
		void display()
		{
			cout<<"I am doing"<<endl;
		}
};
class CMoveList
{
    public:
    	CMoveList()
        {
            // Pre-allocate space for a large number of moves.
            // This is a slight optimization.
            m_moveList.reserve(100);//allocation of 100 space for m_moveList
        }
    	void append(const do_& move)
    	{
    		m_moveList.push_back(move);
		}
        
        const do_ & operator [] (unsigned int ix) const { return m_moveList[ix]; }

    private:
        std::vector<int> m_moveList;//create of vector of object

}; /* end of CMoveList */
int main()
{
	CMoveList c1;
	do_ dd;
	c1.append(dd);
	
//	c1[0]=5;
	
}
