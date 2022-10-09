#pragma once
#include <functional>
#include <iostream>
using namespace std; 

// Tree-like array

/*
See also: https://blog.csdn.net/flushhip/article/details/79165701
*/

/*
Requirement:
Ty -- copyable, has default constructor (with no parameter / all optional), has adder (given solver)
PosTy -- iterable
The problem -- result can be "added" by smaller questions

Supports:
1. Single-point modifier
2. Space queryer
*/
template <typename Ty, typename PosTy = int>
class tree_array {
	public:
		
		using solver = function<Ty(Ty,Ty)>;
		
		tree_array(PosTy size, solver s) : size(size), my_solver(s) {
			data = new Ty[size+2];
			for (PosTy i = 1; i <= size; i++) data[i] = Ty();
		}
		
		void update(Ty value, PosTy pos) {
			for (PosTy i = pos; i <= size; i += low_bit(i)) {
				data[i] = my_solver(data[i], value);
#ifdef TREE_DEBUG
				cout << "Updating #"  << i << ", value=" << data[i] << " to " << value << endl;
#endif
			}
		}
		
		// This is a result for (0, pos]. Must proceed on
		Ty resolve(PosTy pos) {
			Ty result = Ty();
			for (PosTy i = pos; i > 0; i -= low_bit(i)) {
				result = my_solver(data[i], result);
#ifdef TREE_DEBUG
				cout << "Getting value from #" << i << ", value=" << data[i] << ", and it's " << result << endl;
#endif
			}
			return result;
		}
		
		static PosTy low_bit(PosTy value) {
			return value & -value;
		}
		
	private:
		// Means prefixed sum, biggest value, ... 
		solver my_solver;
		PosTy size;
		Ty *data;
};
