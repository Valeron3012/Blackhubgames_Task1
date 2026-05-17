#include <vector>
#include <cstdint>
#include <numeric> // for iota

class Solution {
public:
    int numIslands(std::vector<uint32_t>& grid, int m, int n) {
        if (m <= 0 || n <= 0) return 0;
        
        const int total = m * n;
        const uint32_t* data = grid.data();
        
        // Union-Find структура
        // parent[i] хранит родителя узла i. Изначально каждый сам себе родитель.
        std::vector<int> parent(total);
        std::iota(parent.begin(), parent.end(), 0);
        
        // Функция Find с полным сжатием путей (path compression)
        // Инлайнинг критичен для скорости
        auto find = [&](int x) {
            while (parent[x] != x) {
                parent[x] = parent[parent[x]]; // Path halving (быстрее полного сжатия на практике)
                x = parent[x];
            }
            return x;
        };
        
        // Функция Union
        auto unite = [&](int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                parent[rootX] = rootY;
            }
        };

        // --- PASS 1: Labeling ---
        // Проходим по каждой ячейке
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                int idx = r * n + c;
                
                // Если вода - пропускаем (метка не нужна, но можно пометить как -1 для ясности, 
                // но здесь мы просто игнорируем water в union-find)
                if (data[idx] == 0) {
                    parent[idx] = -1; // Маркер воды
                    continue;
                }
                
                // Проверяем соседа СВЕРХУ (Up)
                if (r > 0 && data[idx - n] == 1) {
                    unite(idx, idx - n);
                }
                
                // Проверяем соседа СЛЕВА (Left)
                // Важно: если есть и Верх, и Лево, они объединятся транзитивно через текущий узел
                if (c > 0 && data[idx - 1] == 1) {
                    unite(idx, idx - 1);
                }
            }
        }

        // --- PASS 2: Counting Unique Roots ---
        int islands = 0;
        for (int i = 0; i < total; ++i) {
            // Если это земля и она является своим собственным корнем (представителем компонента)
            if (parent[i] != -1 && find(i) == i) {
                ++islands;
            }
        }
        
        return islands
;
    }
};
