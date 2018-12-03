#include<vector>
#include<iostream>
using namespace std;


class do_
{
	public:
		
		do_(char *name){
			cout<<"do_object "<<name+2<<endl;
			
		}
		void display() const
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
    	void append(const do_& mo)//passing reference of objectd do_
    	{
    		m_moveList.push_back(mo);
		}
        
        const do_& operator [] (unsigned int ix) const{ return m_moveList[ix]; }

    private:
        std::vector<do_> m_moveList;//create of vector of object

}; /* end of CMoveList */
int main()
{
	CMoveList c1;
	do_ dd1("sangam"),dd2("sashi");
	c1.append(dd1);
	c1.append(dd2);
    const do_& dd3=c1[0];
 	dd3.display();
		
//	c1[0]=5;
	
}
