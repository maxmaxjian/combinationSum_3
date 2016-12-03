#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

namespace std {
    template<>
    struct less<std::vector<int>> {
	bool operator()(const std::vector<int> & v1, const std::vector<int> & v2) {
	    return std::lexicographical_compare(v1.begin(), v1.end(),
						v2.begin(), v2.end());
	}
    };

    template<>
    struct equal_to<std::vector<int>> {
	bool operator()(const std::vector<int> & v1, const std::vector<int> & v2) {
	    auto it = std::mismatch(v1.begin(), v1.end(), v2.begin());
	    return it.first == v1.end();
	}
    };
}

class solution {
public:
    std::vector<std::vector<int>> combinationSum(int k, int n) {
	std::vector<std::vector<int>> result;
	if (k == 1) {
	    if (n >= 1 && n <= 9)
		result.push_back(std::vector<int>{n});
	}
	else if (k > 1) {
	    std::vector<int> cands(n-1);
	    int first = 1;
	    std::generate(cands.begin(), cands.end(), [&](){return first++;});
	    for (auto curr : cands) {
		auto temp = combinationSum(k-1, n-curr);
		std::vector<std::vector<int>> tmp;
		std::copy_if(temp.begin(), temp.end(), std::inserter(tmp, tmp.begin()),
			     [&](const std::vector<int> & vec){
				 return std::find(vec.begin(), vec.end(), curr) == vec.end();
			     });
		std::transform(tmp.begin(), tmp.end(), std::inserter(result, result.end()),
			       [&](std::vector<int> vec){
				   vec.push_back(curr);
				   std::sort(vec.begin(), vec.end());
				   return vec;
			       });
	    }
	    
	    std::sort(result.begin(), result.end(), std::less<std::vector<int>>());
	    auto it = std::unique(result.begin(), result.end(), std::equal_to<std::vector<int>>());
	    result.resize(std::distance(result.begin(), it));
	}
	return result;
    }
};

int main() {
    // int k = 3, n = 7;
    int k = 3, n = 9;

    solution soln;
    auto combSum = soln.combinationSum(k,n);
    std::cout << "All the combinations are:\n";
    std::for_each(combSum.begin(), combSum.end(),
		  [](const std::vector<int> & vec){
		      std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
		      std::cout << std::endl;
		  });
}

