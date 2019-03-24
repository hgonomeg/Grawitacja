#include "sequential.hpp"

seq_ns::seq_ns(const std::list<node>& nds, wuxing* wx)
:node_stepper(nds,wx)
{
	thds.push_back(std::thread(main_action,this));
}

void seq_ns::main_action()
{
	for(auto j=nodes.begin(); j!=(--nodes.end())&&!finished(); j++)
		{
			
			auto ekaj=j;
			ekaj++;
			for(auto i=ekaj; i!=nodes.end()&&!finished(); i++)
			{
				patris->consider_pair(j,i);
				std::this_thread::sleep_for(interval);
			}
			
		
		}
	std::unique_lock<std::mutex>* locc = new std::unique_lock<std::mutex>(kon_mut);
	koniec = true;
	delete locc;
}