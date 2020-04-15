#ifndef TIANCHE_WRAPPER_HPP
#define TIANCHE_WRAPPER_HPP
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>
#include <functional>
#include <utility>
#include <tuple>
#include <queue>
#include <vector>
#include <list>


#if __cplusplus==201703L
#include <numeric>
using std::gcd;
#else
int gcd(int p1, int p2)
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

template <typename T>
	class tianche_wrapper
	{
		using iter_type = typename std::list<T>::iterator;
		using fx_type = std::function<void(const iter_type&,const iter_type&)>;
		
		std::list<T>& subject_list;
		std::condition_variable thread_sleeper;
		std::vector<std::thread> thread_pool;
		std::queue<std::pair<unsigned int,fx_type>> work_queue; //A queue that holds the tianche multipliers and the function to be applied to each unique pair of objects
		std::mutex queue_mutex;
		
		bool destruction_pending; 
		bool current_computation_ready;
        std::mutex global_state;
        
        void work_thread(); 
		bool not_quit();
        
		void cycle_internal_iterator(iter_type&,unsigned int);
		public:
		tianche_wrapper(std::list<T>&);
		~tianche_wrapper();
		void async_pairwise_apply(const fx_type&);
	};

template <typename T>
	tianche_wrapper<T>::tianche_wrapper(std::list<T>& li)
	:subject_list(li)
	{
		destruction_pending = false;
		current_computation_ready = true;
		unsigned int thread_count = std::thread::hardware_concurrency();
		if(thread_count<2) thread_count = 2;
		for(unsigned i=0;i<thread_count;i++) thread_pool.push_back(std::thread(&tianche_wrapper<T>::work_thread,this));
	}


template <typename T>
	tianche_wrapper<T>::~tianche_wrapper()
	{
		global_state.lock();
		destruction_pending = true;
		global_state.unlock();
		thread_sleeper.notify_all();
		for(auto& x: thread_pool) x.join();
	}

template <typename T>
	bool tianche_wrapper<T>::not_quit() //whether the work threads should finish and join
	{
		std::lock_guard<std::mutex> lol(global_state);
        {
            return !destruction_pending;
        }
	}
template <typename T>
	void tianche_wrapper<T>::async_pairwise_apply(const fx_type& fu)
	{
		queue_mutex.lock();
		for(unsigned int i=1;(float)i<=subject_list.size()/2.f;i++) work_queue.push(std::pair(i,fu));
		queue_mutex.unlock();
		global_state.lock();
		current_computation_ready = false;
		global_state.unlock();
		do{
			thread_sleeper.notify_all(); //prompt the thread pool to start processing the queue
			std::this_thread::yield();
			std::this_thread::yield();
			std::this_thread::yield();
		}while([this]{ //while not done
			std::lock_guard<std::mutex> loko(global_state);
			return !current_computation_ready;
		}());
		
	}

template <typename T>
	void tianche_wrapper<T>::cycle_internal_iterator(iter_type& xe,unsigned int delta)
	{
		if(delta!=0)
		{
			for(unsigned int i=0;i<delta;i++)
			{
				if(xe==subject_list.end()) xe=subject_list.begin();
				xe++;
			}
		}
		if(xe==subject_list.end()) xe=subject_list.begin();
	}

template <typename T>
	void tianche_wrapper<T>::work_thread()
	{
		std::unique_lock<std::mutex> lok(queue_mutex,std::defer_lock); //prevents deadlock
		while(true)
		{
			lok.lock();

			if(work_queue.empty()) thread_sleeper.wait(lok,[this]{ //thread_sleeper.wait(lok,true) <- does not wait
				if(!not_quit()) return true; //don't pause the thread when it is necessary to deconstruct the object
				return !work_queue.empty(); //only pause when the queue is empty
				});
			if(!not_quit()) return; //return from the thread if deconstruction is required

			unsigned int jmpnum = work_queue.front().first;
			fx_type fu = work_queue.front().second;
			work_queue.pop();
			auto queue_size = work_queue.size();
			lok.unlock(); //allow other threads to access the queue
			
			iter_type curref = subject_list.begin();
			for(unsigned int jmpcount=0;jmpcount<(unsigned int)gcd((int)subject_list.size(),(int)jmpnum);jmpcount++)
			{
				iter_type traveller = curref;
				cycle_internal_iterator(traveller,jmpnum);
				iter_type chaser = curref;

				fu(chaser,traveller); 
				chaser = traveller;
				cycle_internal_iterator(traveller,jmpnum);
				if(jmpnum*2==subject_list.size()) {curref++; continue; }

				do
				{
					fu(chaser,traveller); 
					chaser = traveller;
					cycle_internal_iterator(traveller,jmpnum);
				} while (chaser!=curref);
				curref++;
			}
			if(queue_size==0)
			{
				global_state.lock();
				current_computation_ready = true;
				global_state.unlock();
			}
		}
	}

#endif
