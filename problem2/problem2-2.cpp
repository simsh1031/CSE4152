#include <iostream>
#include <cassert>
#include <cstdlib>

/**
 * @brief Queries the value stored at cell (r, c).
 * @param r The row index, where 1 <= r <= n.
 * @param c The column index, where 1 <= c <= n.
 * @return The integer stored at cell (r, c).
 */
int query_cell(int r, int c) {
    int result;
    std::cout << "? " << r << ' ' << c << std::endl;

    if (!(std::cin >> result)) {
        std::exit(0);
    }

    return result;
}

/**
 * @brief Submits cell (r, c) as the position of K and terminates the program.
 * @param r The row index, where 1 <= r <= n.
 * @param c The column index, where 1 <= c <= n.
 */
void answer_with_cell(int r, int c) {
    int result;
    std::cout << "! " << r << ' ' << c << std::endl;

    if (!(std::cin >> result)) {
        std::exit(0);
    }

    assert(result == 0 || result == 1);
    std::exit(0);
}

/**
 * @brief Submits that K does not occur in the matrix and terminates the program.
 */
void answer_without_cell() {
    int result;
    std::cout << "! -1 -1" << std::endl;

    if (!(std::cin >> result)) {
        std::exit(0);
    }

    assert(result == 0 || result == 1);
    std::exit(0);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    // TODO: write your logic here!
    // Each row is sorted in non-decreasing order from left to right.
    // Each column is sorted in non-increasing order from top to bottom.
    // You can use the functions `query_cell`, `answer_with_cell`,
    // and `answer_without_cell`.
    // You may call `query_cell` at most 2 * n - 1 times.
    // Call exactly one of the two answer functions, exactly once.
    // Do not modify the provided functions or perform additional
    // standard input/output operations outside these functions.
    // 왼쪽 위 (1, 1) 위치에서 탐색 시작
    int r = 1;
    int c = 1;

    while (r <= n && c <= n) {
        int val = query_cell(r, c);

        if (val == k) {
            // k를 찾은 경우 해당 좌표 제출 후 종료
            answer_with_cell(r, c);
            return 0;
        } else if (val < k) {
            // 현재 값이 k보다 작다면, 이 열(c)의 아래쪽 셀들은 
            // 내림차순 정렬 특성상 전부 k보다 작으므로 
            // 오른쪽(c + 1)으로 이동하여 더 큰 값을 탐색
            c++;
        } else { // val > k
            // 현재 값이 k보다 크다면, 이 행(r)의 오른쪽 셀들은 
            // 오름차순 정렬 특성상 전부 k보다 크므로 
            // 아래쪽(r + 1)으로 이동하여 더 작은 값을 탐색
            r++;
        }
    }

    // 탐색 범위를 벗어날 때까지 k를 찾지 못한 경우
    answer_without_cell();
    

    return 0;
}