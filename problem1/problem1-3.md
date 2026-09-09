# HW Problem #1 — Programming Guide

# 3. Minimum Calculation

## 3.1 문제 목표

주어진:

```text
a
n
```

에 대해

```text
b = a^n
```

을 계산한다.

사용 가능한 주요 계산 연산은 **곱셈**이며, 이전에 계산한 값을 변수에 저장하여 다시 사용할 수 있다.

목표:

> `a^n`을 만드는 데 필요한 곱셈 횟수를 최소화한다.

---

# 3.2 핵심 개념 — Addition Chain

다음과 같은 지수의 수열을 생각한다.

```text
1 = e0 < e1 < e2 < ... < ek = n
```

새로운 지수 `ei`는 반드시 앞에서 이미 만들어진 두 지수의 합이어야 한다.

```text
ei = ej + el

j < i
l < i
```

왜냐하면

```text
a^ej × a^el
= a^(ej + el)
```

이기 때문이다.

이러한 수열을 **Addition Chain**이라고 한다.

---

# 3.3 예시 — n = 15

가능한 Addition Chain:

```text
1
2 = 1 + 1
3 = 2 + 1
5 = 3 + 2
10 = 5 + 5
15 = 10 + 5
```

따라서:

```text
1 → 2 → 3 → 5 → 10 → 15
```

곱셈은 5번이다.

실제 계산:

```text
x1 = a × a          // a²
x2 = x1 × a         // a³
x3 = x2 × x1        // a⁵
x4 = x3 × x3        // a¹⁰
x5 = x4 × x3        // a¹⁵
```

---

# 3.4 이론적인 최소 깊이

곱셈 한 번으로 현재 가장 큰 지수를 최대 2배까지 증가시킬 수 있다.

```text
1
→ 2
→ 4
→ 8
→ 16
...
```

따라서 n을 만들기 위해서는 최소한

```text
ceil(log2(n))
```

번의 곱셈이 필요하다.

즉:

```text
lower_bound = ceil(log2(n))
```

이다.

다만 이것은 **하한(lower bound)**이지 항상 그 횟수만으로 만들 수 있다는 뜻은 아니다.

예:

```text
n = 15

ceil(log2 15) = 4
```

하지만 4번으로는 15를 만들 수 없고 최소 5번이 필요하다.

---

# 3.5 탐색 전략 — IDDFS

보고서의 최종 알고리즘은 **IDDFS(Iterative Deepening Depth First Search)**이다.

탐색 깊이를:

```text
ceil(log2 n)
```

부터 시작한다.

```text
depth = ceil(log2 n)

while true:

    DFS로 depth번의 곱셈만 사용해서
    n을 만들 수 있는지 탐색

    성공:
        종료

    실패:
        depth++
```

처음 성공한 depth가 최소 곱셈 횟수이다.

---

# 3.6 DFS에서 저장할 정보

현재 Addition Chain을 저장한다.

예:

```text
chain = [1, 2, 3, 5]
```

현재까지 계산 가능한 값은:

```text
a¹
a²
a³
a⁵
```

이다.

다음 값은 이 중 두 값을 선택해서 만든다.

예:

```text
5 + 5 = 10
5 + 3 = 8
5 + 2 = 7
5 + 1 = 6
3 + 3 = 6
3 + 2 = 5
...
```

단, 이미 만든 값이나 현재 최대 지수보다 작거나 같은 값은 새 chain의 증가 조건에 맞지 않으므로 제외할 수 있다.

---

# 3.7 다음 노드 생성

현재:

```text
chain = [e0, e1, ..., ek]
```

라고 하자.

가능한 다음 값:

```text
next = chain[i] + chain[j]
```

조건:

```text
0 <= i <= k
0 <= j <= i
```

그리고 Addition Chain을 증가하는 형태로 유지한다면:

```text
next > chain[k]
```

이어야 한다.

목표를 초과하는 값은 필요 없으므로:

```text
next <= n
```

조건도 적용할 수 있다.

따라서:

```text
if next <= current_max:
    skip

if next > n:
    skip
```

한다.

---

# 3.8 가지치기 — 가장 중요한 조건

현재 가장 큰 지수를:

```text
current
```

남은 연산 횟수를:

```text
remaining
```

이라고 하자.

한 번의 연산으로 지수를 최대 두 배 만들 수 있으므로 남은 모든 연산에서 계속 제곱하더라도 최대:

```text
current × 2^remaining
```

까지만 도달할 수 있다.

따라서:

```text
current × 2^remaining < n
```

이라면 절대로 목표에 도달할 수 없다.

즉:

```text
if current * 2^remaining < n:
    return false
```

로 해당 가지 전체를 제거한다.

---

# 3.9 탐색 순서

큰 값을 먼저 시도하면 목표 `n`에 빠르게 접근할 가능성이 높다.

따라서 현재 chain을 뒤에서부터 탐색한다.

```text
for i = last down to 0:
    for j = i down to 0:
```

예:

```text
chain = [1, 2, 3, 5]
```

이면 우선:

```text
5 + 5 = 10
5 + 3 = 8
5 + 2 = 7
5 + 1 = 6
...
```

순으로 시도할 수 있다.

이 순서는 **최적성을 보장하는 조건 자체는 아니며**, 원하는 chain을 빨리 찾기 위한 탐색 우선순위다.

최적성은 IDDFS가 작은 깊이부터 완전 탐색한다는 사실에서 나온다.

---

# 3.10 DFS 의사코드

```text
DFS(chain, currentDepth, maxDepth, n):

    current = chain[last]

    if current == n:
        return true

    if currentDepth == maxDepth:
        return false

    remaining = maxDepth - currentDepth

    // 최대한 두 배씩 증가해도 n에 도달 불가능
    if current * 2^remaining < n:
        return false

    // 이전에 만든 지수들의 조합
    for i = last down to 0:

        for j = i down to 0:

            next = chain[i] + chain[j]

            if next <= current:
                continue

            if next > n:
                continue

            chain.push(next)

            if DFS(chain,
                   currentDepth + 1,
                   maxDepth,
                   n):

                return true

            chain.pop()

    return false
```

---

# 3.11 IDDFS 전체 의사코드

```text
MinimumCalculation(n):

    if n == 1:
        return 0

    depth = ceil(log2(n))

    while true:

        chain = [1]

        if DFS(chain, 0, depth, n):
            return depth

        depth++
```

실제로 계산기용 코드까지 생성해야 한다면 `chain`뿐 아니라 각 지수가 **어떤 두 이전 지수의 합으로 생성됐는지**도 저장해야 한다.

예를 들어:

```text
exponent = 15
parents = (10, 5)
```

를 저장하면 나중에

```text
a^15 = a^10 × a^5
```

형태의 곱셈 코드를 생성할 수 있다.

---

# 3.12 n = 15 동작 예시

초기 하한:

```text
ceil(log2 15)
= 4
```

### depth = 4

```text
[1]
 ↓
가능한 Addition Chain 탐색
 ↓
15 생성 실패
```

따라서:

```text
depth = 5
```

### depth = 5

탐색 중:

```text
[1]
[1, 2]
[1, 2, 3]
[1, 2, 3, 5]
[1, 2, 3, 5, 10]
[1, 2, 3, 5, 10, 15]
```

발견.

따라서:

```text
최소 곱셈 횟수 = 5
```

---

# 3.13 시간 복잡도

이 문제는 앞의 두 문제와 달리 **탐색 자체가 매우 비싸다.**

현재 chain에 `k`개의 지수가 존재한다고 하면 두 지수를 선택하는 경우는 중복 선택까지 포함하여 최대:

```text
k(k+1) / 2
```

개이다.

즉 깊이가 커질수록 branching factor 자체가 증가한다.

보고서에서 이를 단순화하여 깊이 `d`에서 대략:

```text
O(d²)
```

개의 후보가 생성된다고 보았다.

따라서 깊이 `D`까지 가지치기가 전혀 효과를 내지 못하는 매우 거친 상한을 잡으면:

```text
O(1² × 2² × 3² × ... × D²)
```

즉,

```text
O((D!)²)
```

형태로 볼 수 있다.

보고서에서 사용한 더 느슨한 상한으로는 각 단계의 branching factor를 최대 `D²`로 통일하여:

```text
O((D²)^D)
= O(D^(2D))
```

로 둘 수 있다.

그리고 탐색 깊이 `D`를 `O(log n)` 수준이라고 **가정하여 표현하면** 보고서의 식:

```text
O((log n)^(2 log n))
```

을 얻는다.

다만 여기서 중요한 점은 **최적 addition chain의 실제 길이 D가 항상 정확히 `ceil(log₂ n)`인 것은 아니라는 것**이다. `ceil(log₂ n)`은 탐색을 시작하는 하한이다. 따라서 구현 관점에서 더 정확하게는:

```text
D = 실제로 처음 성공한 최소 Addition Chain 길이
```

라고 두고

```text
Worst-case search upper bound
≈ O(D^(2D))
```

로 표현한 뒤, `D`가 `log n`과 관련된 작은 값이라는 점을 별도로 설명하는 것이 안전하다.

가지치기가 적용되면 실제 탐색량은 이 단순 상한보다 크게 줄어든다.

---

# 3.14 공간 복잡도

DFS에서는 BFS와 달리 모든 탐색 노드를 동시에 저장하지 않는다.

현재 탐색 중인 chain:

```text
[1, e1, e2, ..., eD]
```

만 유지한다.

따라서:

```text
chain 크기 = D + 1
```

재귀 호출 스택 역시:

```text
O(D)
```

이다.

따라서:

```text
Space Complexity = O(D)
```

이며 `D`를 `O(log n)` 규모로 놓는 보고서의 분석에서는:

```text
Space Complexity = O(log n)
```

으로 정리할 수 있다.

---

# 최종 구현 요약

| 문제                       | 핵심 알고리즘                    | 구현 핵심                           | 시간 복잡도                              | 공간 복잡도           |
| -------------------------- | -------------------------------- | ----------------------------------- | ---------------------------------------- | --------------------- |
| **3. Minimum Calculation** | Addition Chain + IDDFS + Pruning | 작은 깊이부터 DFS로 최적 chain 탐색 | **O(D^(2D))**의 거친 탐색 상한           | **O(D)**              |
|                            |                                  | `D`: 최소 addition chain 길이       | 보고서식 근사 시 **O((log n)^(2log n))** | 보고서식 **O(log n)** |

특히 **3번을 실제 프로그래밍할 때 가장 중요한 것은 `chain`만 저장해서 최소 횟수를 찾는 것과, 실제 계산기 코드를 출력하는 것은 조금 다르다는 점**입니다. 문제 정의가 단순히 최소 횟수가 아니라 **"계산기용 코드를 생성"**하는 것까지 요구한다면, `a^15`를 찾았을 때 `15 = 10 + 5`라는 **부모 지수 정보까지 저장**해서 최종적으로 `x5 = x4 * x3` 같은 코드를 복원하도록 구현해야 보고서의 문제 정의를 완전히 만족시킬 수 있습니다.
