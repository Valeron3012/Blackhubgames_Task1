#include <vector>
#include <cstdint>
#include <algorithm>

class Solution {
public:
    int numIslands(std::vector<uint32_t>& grid, int m, int n) {
        if (m <= 0 || n <= 0) return 0;
        uint32_t* __restrict data = grid.data();
        
        std::vector<uint32_t> parent;
        parent.reserve(m * n / 12);
        parent.push_back(0);
        
        uint32_t label = 0;
        
        // Path splitting + inline
        auto find = [&](std::vector<uint32_t>& p, uint32_t x) __attribute__((always_inline)) {
            while (p[x] != x) {
                uint32_t px = p[x];
                p[x] = p[px];
                x = px;
            }
            return x;
        };
        
        for (int r = 0; r < m; ++r) {
            // Prefetch следующей строки в L1/L2
            if (r + 2 < m) __builtin_prefetch(data + (r + 2) * n, 0, 3);
            
            uint32_t* curr = data + r * n;
            uint32_t* prev = (r > 0) ? curr - n : nullptr;
            
            for (int c = 0; c < n; ++c) {
                if (__builtin_expect(curr[c] == 0, 1)) continue; // branch hint: вода чаще
                
                uint32_t up   = prev ? prev[c] : 0;
                uint32_t left = c > 0 ? curr[c-1] : 0;
                uint32_t new_lbl;
                
                if (up && left) {
                    uint32_t ru = find(parent, up);
                    uint32_t rl = find(parent, left);
                    new_lbl = (ru < rl) ? ru : rl;
                    parent[ru > rl ? ru : rl] = new_lbl;
                } else {
                    new_lbl = up ? find(parent, up) : (left ? find(parent, left) : ++label);
                    if (!up && !left) parent.push_back(new_lbl);
                }
                curr[c] = new_lbl;
            }
        }
        
        int islands = 0;
        for (uint32_t l = 1; l <= label; ++l) {
            if (parent[l] == l) ++islands;
        }
        return islands;
    }
};
