#include <vector>
#include <cstdint>

class Solution {
public:
    int numIslands(std::vector<uint32_t>& grid, int m, int n) {
        if (m <= 0 || n <= 0) return 0;
        const int total = m * n;
        int islands = 0;
        uint32_t* data = grid.data();

        // Стек хранит координаты в виде: (row << 16) | col
        // uint32_t гарантирует 4 байта, битовые операции вместо деления
        uint32_t* stk = new uint32_t[total];
        int top = 0;

        for (int i = 0; i < total; ++i) {
            if (data[i] != 1) continue;
            ++islands;
            data[i] = 0;
            stk[top++] = (static_cast<uint32_t>(i / n) << 16) | (i % n);

            while (top > 0) {
                uint32_t val = stk[--top];
                int r = val >> 16;
                int c = val & 0xFFFF;
                int base = r * n + c;

                // Порядок: Right → Down → Left → Up (оптимизация под LIFO и кэш)
                if (c + 1 < n) { 
                    int idx = base + 1; 
                    if (data[idx] == 1) { data[idx] = 0; stk[top++] = (val & 0xFFFF0000) | (c + 1); } 
                }
                if (r + 1 < m) { 
                    int idx = base + n; 
                    if (data[idx] == 1) { data[idx] = 0; stk[top++] = ((r + 1) << 16) | (val & 0xFFFF); } 
                }
                if (c > 0) {     
                    int idx = base - 1; 
                    if (data[idx] == 1) { data[idx] = 0; stk[top++] = (val & 0xFFFF0000) | (c - 1); } 
                }
                if (r > 0) {     
                    int idx = base - n; 
                    if (data[idx] == 1) { data[idx] = 0; stk[top++] = ((r - 1) << 16) | (val & 0xFFFF); } 
                }
            }
        }
        delete[] stk;
        return islands;
    }
};
