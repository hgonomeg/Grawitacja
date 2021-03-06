#ifndef TIANCHE_HPP
#define TIANCHE_HPP
#include "unit_base.hpp"
#include "wuxing.hpp"

#if __cplusplus==201703L
#include <numeric>
using std::gcd;
#else
inline int gcd(int p1, int p2)
	{
	p1=abs(p1);
	p2=abs(p2);
	while(p1!=p2)
		{
		if(p2>p1)
			p2=p2-p1;
		else
			p1=p1-p2;
		}
	return p1;
	}
#endif	

class tianche :public node_stepper
{
 protected:
	//when iterator reaches end, it is moved back to the beginning
	void cycle_nodes_iterator(std::list<node>::const_iterator&,unsigned int);
	void jump_evaluator(std::size_t jump_number);
 public:
	tianche(const std::list<node>&, wuxing*);
	virtual void main_action() override;
};


#endif