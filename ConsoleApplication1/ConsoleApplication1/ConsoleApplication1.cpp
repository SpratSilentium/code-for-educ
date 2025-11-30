#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

// Глобальные переменные для удобства (или можно передавать по ссылке)
int timer;
std::vector<int> tin; // Время входа (time in)
std::vector<int> fup; // Минимальное время, достижимое из вершины (аналог вашего 'a')
std::vector<bool> visited;
std::vector<bool> is_bridge; // Храним статус моста по индексу ребра
// Граф хранит пары: {сосед, индекс_ребра}
std::vector<std::vector<std::pair<int, int>>> adj;

// p = parent (номер ребра, по которому пришли, а не вершина!)
void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = fup[v] = timer++;

    for (auto& edge : adj[v]) {
        int to = edge.first;
        int id = edge.second;

        // Если это то же самое ребро, по которому мы пришли - пропускаем
        if (id == p)
            continue;

        if (visited[to]) {
            // Обратное ребро
            // Обновляем fup текущей вершины значением времени входа предка
            fup[v] = std::min(fup[v], tin[to]);
        }
        else {
            // Ребро дерева
            dfs(to, id);
            // Обновляем fup текущей вершины значением fup потомка
            fup[v] = std::min(fup[v], fup[to]);

            // Проверка на мост
            if (fup[to] > tin[v]) {
                is_bridge[id] = true;
            }
        }
    }
}

int main() {
    // Ускорение ввода-вывода
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    if (!(std::cin >> n >> m)) return 0;

    adj.resize(n);
    tin.resize(n);
    fup.resize(n);
    visited.assign(n, false);
    is_bridge.assign(m, false);
    timer = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--; v--; // 0-индексация
        adj[u].push_back({ v, i });
        adj[v].push_back({ u, i });
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    // Подсчет количества мостов
    int bridge_count = 0;
    std::vector<int> result_indices;

    for (int i = 0; i < m; i++) {
        if (is_bridge[i]) {
            bridge_count++;
            result_indices.push_back(i + 1); // Вывод в 1-индексации
        }
    }

    // Вывод результатов
    std::cout << bridge_count << '\n';
    // Сортировка нужна, если требуется вывод по возрастанию (хотя цикл 0..m уже дает сортировку)
    // std::sort(result_indices.begin(), result_indices.end()); 

    for (int i = 0; i < result_indices.size(); i++) {
        std::cout << result_indices[i] << (i == result_indices.size() - 1 ? "" : " ");
    }
    std::cout << '\n';

    return 0;
}