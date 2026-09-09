#include <iostream>
#include <cassert>

/**
 * @brief Asks person A if they know person B.
 * @param a The number of person A.
 * @param b The number of person B.
 * @return true if A knows B, otherwise returns false.
 */
bool ask_a_to_know_b(int a, int b) {
    int result;
    std::cout << "? " << a << ' ' << b << std::endl;
    std::cin >> result;
    assert(result == 0 || result == 1);
    return result;
}

/**
 * @brief Verifies if person x is a celebrity.
 * @param x The number of the person to verify, or -1 if there is no celebrity.
 * @return true if the answer is correct, otherwise returns false.
 */
bool answer(int x) {
    int result;
    std::cout << "! " << x << std::endl;
    std::cin >> result;
    assert(result == 0 || result == 1);
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    // TODO: write your logic here!

    int candidate = 1;

    // candidate가 새롭게 선택될 때
    // 이미 candidate를 알고 있다고 확인된 사람
    int known_incoming = -1;

    for (int i = 2; i <= n; ++i) {

        // 지금까지 살아 있는 후보가 없다면
        // 새 사람 i를 후보로 설정
        if (candidate == -1) {
            candidate = i;
            known_incoming = -1;
            continue;
        }

        // candidate가 i를 안다면 candidate는 Celebrity가 될 수 없음
        if (ask_a_to_know_b(candidate, i)) {
            known_incoming = candidate;
            candidate = i;
        }
        else {
            // candidate가 i를 모르는데,
            // i도 candidate를 모른다면 둘 다 Celebrity가 아님
            if (!ask_a_to_know_b(i, candidate)) {
                candidate = -1;
                known_incoming = -1;
            }
        }
    }

    // 마지막까지 후보가 없다면 Celebrity 없음
    if (candidate == -1) {
        answer(-1);
        return 0;
    }

    /*
     * candidate보다 뒤의 사람들은 위의 반복문에서
     *
     * candidate -> i == 0
     * i -> candidate == 1
     *
     * 을 이미 확인했으므로 다시 검사할 필요가 없다.
     *
     * 따라서 candidate 이전 사람들만 검사한다.
     */
    for (int i = 1; i < candidate; ++i) {

        // Celebrity는 다른 사람을 알면 안 됨
        if (ask_a_to_know_b(candidate, i)) {
            answer(-1);
            return 0;
        }

        /*
         * known_incoming은
         *
         * known_incoming -> candidate == 1
         *
         * 을 이미 확인했으므로 다시 물어볼 필요 없음
         */
        if (i != known_incoming &&
            !ask_a_to_know_b(i, candidate)) {

            answer(-1);
            return 0;
        }
    }

    answer(candidate);

    return 0;
}