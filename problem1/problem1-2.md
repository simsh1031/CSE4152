# HW Problem #1 — Programming Guide

# 2. 2 Keys Keyboard

## 2.1 문제 목표

초기 화면:

```text
A
```

사용 가능한 연산:

```text
Copy All
Paste
```

두 연산만 사용해서 정확히 `N`개의 A를 만드는 **최소 연산 횟수**를 구한다.

---

## 2.2 연산의 의미

현재 A가 `x`개 있다고 하자.

```text
Copy All
Paste
Paste
...
```

Copy All 이후 Paste를 `k-1`번 하면:

```text
x
↓
2x
↓
3x
...
↓
kx
```

따라서 `x → kx`로 만드는 데 필요한 연산은

```text
1번 Copy All
+
(k-1)번 Paste

= k번
```

이다.

---

# 2.3 핵심 아이디어

문제를 **곱셈**으로 변환한다.

예를 들어:

```text
N = 6

6 = 2 × 3
```

그러면

```text
1
↓ ×2
2
↓ ×3
6
```

필요한 연산:

```text
2 + 3 = 5
```

실제 키보드 연산:

```text
A

Copy All
Paste
→ AA

Copy All
Paste
Paste
→ AAAAAA
```

총 5번이다.

---

## 2.4 소인수분해와 최소 연산

N을

```text
N = p1 × p2 × ... × pk
```

로 소인수분해하면 최소 연산 횟수는

```text
p1 + p2 + ... + pk
```

가 된다.

### 예시 1 — N = 8

```text
8 = 2 × 2 × 2

최소 연산
= 2 + 2 + 2
= 6
```

### 예시 2 — N = 5

5는 소수이다.

```text
5 = 5

최소 연산 = 5
```

즉,

```text
Copy
Paste
Paste
Paste
Paste
```

이다.

### 예시 3 — N = 6

```text
6 = 2 × 3

최소 연산
= 2 + 3
= 5
```

---

# 2.5 알고리즘

가장 작은 인수 `2`부터 시작한다.

```text
factor = 2
answer = 0
```

현재 N이 factor로 나누어지는 동안:

```text
N = N / factor
answer += factor
```

더 이상 나누어지지 않으면:

```text
factor 증가
```

이를 N이 1이 될 때까지 반복한다.

---

## 2.6 동작 예시

### N = 12

초기:

```text
N = 12
answer = 0
factor = 2
```

12는 2로 나누어진다.

```text
N = 6
answer = 2
```

6도 2로 나누어진다.

```text
N = 3
answer = 4
```

3은 2로 나누어지지 않는다.

```text
factor = 3
```

3은 3으로 나누어진다.

```text
N = 1
answer = 7
```

결과:

```text
12 = 2 × 2 × 3

2 + 2 + 3 = 7
```

---

## 2.7 의사코드

보고서의 `√N` 분석과 맞추려면 다음처럼 구현하는 편이 좋다.

```text
MinSteps(N):

    answer = 0
    factor = 2

    while factor * factor <= N:

        while N % factor == 0:
            answer += factor
            N /= factor

        factor += 1

    // 마지막에 소인수가 남은 경우
    if N > 1:
        answer += N

    return answer
```

---

## 2.8 구현할 때 중요한 조건

### N = 1

처음부터 A가 하나 있으므로:

```text
N = 1
→ 연산 0번
```

### 소수인 경우

예:

```text
N = 13
```

`√13` 이하에서 인수를 발견하지 못한다.

마지막에:

```text
if N > 1:
    answer += N
```

처리를 해야 한다.

결과:

```text
answer = 13
```

---

# 2.9 복잡도

### 시간 복잡도

보고서에서 설명한 방식대로 trial division을 사용하면 최악의 경우 `√N`까지 인수를 검사한다.

특히 N이 소수라면:

```text
2, 3, 4, ..., floor(√N)
```

까지 검사해야 한다.

따라서:

```text
Time Complexity = O(√N)
```

보고서의 `O(√N + log N)`에서 나눗셈이 반복되는 횟수는 별도로 생각할 수 있지만, 전체 점근적 상한은 결국:

```text
O(√N)
```

으로 정리할 수 있다.

### 공간 복잡도

필요한 값:

```text
N
factor
answer
```

정도뿐이며 소인수 목록 자체를 저장하지 않아도 된다.

따라서:

```text
Space Complexity = O(1)
```

---

# 최종 구현 요약

| 문제                   | 핵심 알고리즘 | 구현 핵심              | 시간 복잡도 | 공간 복잡도 |
| ---------------------- | ------------- | ---------------------- | ----------- | ----------- |
| **2. 2 Keys Keyboard** | 소인수분해    | N의 소인수들의 합 계산 | **O(√N)**   | **O(1)**    |
