#include <vector>
#include <algorithm>
#include <cstdint>

class Solution {
public:
    int numIslands(std::vector<uint32_t>& grid, int m, int n) {
        if (m <= 0 || n <= 0) return 0;
        
        const int total = m * n;
        int islands = 0;
        uint32_t* data = grid.data();
        
        std::vector<int> stk;
        stk.reserve(total); 

        for (int i = 0; i < total; ++i) {
            if (data[i] == 1) {
                ++islands;
                data[i] = 0;          
                stk.push_back(i);

                while (!stk.empty()) {
                    int curr = stk.back();
                    stk.pop_back();

                    int r = curr / n; 
                    int c = curr % n; 

                    if (c < n - 1 && data[curr + 1] == 1) {
                        data[curr + 1] = 0;
                        stk.push_back(curr + 1);
                    }
                    if (r < m - 1 && data[curr + n] == 1) {
                        data[curr + n] = 0;
                        stk.push_back(curr + n);
                    }
                    if (c > 0 && data[curr - 1] == 1) {
                        data[curr - 1] = 0;
                        stk.push_back(curr - 1);
                    }
                    if (r > 0 && data[curr - n] == 1) {
                        data[curr - n] = 0;
                        stk.push_back(curr - n);
                    }
                }
            }
        }
        return islands;
    }
};

int main() {
    // 1 1 0 0
    // 0 1 0 1
    // 0 0 1 1
    std::vector<uint32_t> grid = {1,1,0,0, 0,1,0,1, 0,0,1,1};
    int m = 3;
    int n = 4;

    std::cout << Solution{}.numIslands(grid, m, n) << "\n";
    return 0;
}
