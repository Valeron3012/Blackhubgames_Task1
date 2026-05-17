#include <vector>
#include <cstdint>

class Solution {
public:
    int numIslands(std::vector<uint32_t>& grid, int m, int n) {
        if (m <= 0 || n <= 0) return 0;
        
        const int total = m * n;
        int islands = 0;
        uint32_t* data = grid.data();
        
        // Храним в стеке сразу {row, col} — избегаем деления в цикле
        struct Cell { uint16_t r, c; };
        std::vector<Cell> stk;
        stk.reserve(total);

        for (int i = 0; i < total; ++i) {
            if (data[i] != 1) continue;
            
            ++islands;
            data[i] = 0;
            stk.push_back({static_cast<uint16_t>(i / n), static_cast<uint16_t>(i % n)});
            
            while (!stk.empty()) {
                Cell cur = stk.back(); stk.pop_back();
                int r = cur.r, c = cur.c;
                int base = r * n + c;  // Один умножение вместо деления
                
                // Проверка соседей: порядок оптимизирован под кэш
                if (c + 1 < n) {
                    int idx = base + 1;
                    if (data[idx] == 1) { data[idx] = 0; stk.push_back({static_cast<uint16_t>(r), static_cast<uint16_t>(c + 1)}); }
                }
                if (r + 1 < m) {
                    int idx = base + n;
                    if (data[idx] == 1) { data[idx] = 0; stk.push_back({static_cast<uint16_t>(r + 1), static_cast<uint16_t>(c)}); }
                }
                if (c > 0) {
                    int idx = base - 1;
                    if (data[idx] == 1) { data[idx] = 0; stk.push_back({static_cast<uint16_t>(r), static_cast<uint16_t>(c - 1)}); }
                }
                if (r > 0) {
                    int idx = base - n;
                    if (data[idx] == 1) { data[idx] = 0; stk.push_back({static_cast<uint16_t>(r - 1), static_cast<uint16_t>(c)}); }
                }
            }
        }
        return islands;
    }
};
