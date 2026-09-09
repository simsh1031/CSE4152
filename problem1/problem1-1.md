# HW Problem #1 — Programming Guide

## 1. Finding Celebrities

### 1.1 문제 목표

N명의 사람 중 다음 두 조건을 모두 만족하는 **Celebrity**를 찾는다.

Celebrity를 `C`라고 하면:

1. `C`는 자신을 제외한 모든 사람을 **모른다**.
2. 자신을 제외한 모든 사람은 `C`를 **안다**.

즉,

```text
모든 i != C에 대해

knows(C, i) == false
knows(i, C) == true
```

Celebrity는 존재하지 않을 수도 있으며, 존재한다면 **최대 1명**이다.

---

### 1.2 사용할 연산

두 사람 `A`, `B`에 대해 다음 질문이 가능하다고 가정한다.

```text
knows(A, B)
```

결과:

```text
true  : A가 B를 안다.
false : A가 B를 모른다.
```

---

### 1.3 핵심 조건

두 사람 `A`, `B`를 비교할 때:

```text
if knows(A, B) == true:
    A는 Celebrity가 될 수 없음
    -> B를 후보로 유지

else:
    B는 Celebrity가 될 수 없음
    -> A를 후보로 유지
```

#### 이유

```text
A가 B를 안다
→ A는 누군가를 알고 있음
→ Celebrity 조건 위반
→ A 제거
```

반대로,

```text
A가 B를 모른다
→ B는 모든 사람에게 알려져 있어야 한다는 조건 위반
→ B 제거
```

따라서 **질문 1번마다 반드시 후보 1명을 제거할 수 있다.**

---

## 1.4 전체 알고리즘

알고리즘은 크게 두 단계이다.

```text
[1단계] Celebrity 후보 찾기
        ↓
[2단계] 최종 후보 검증
        ↓
Celebrity / 없음 결정
```

### Step 1. 후보 찾기

처음 사람을 후보로 설정한다.

```text
candidate = 0
```

그다음 `1 ~ N-1`번 사람을 차례대로 비교한다.

```text
for i = 1 ~ N-1:

    if knows(candidate, i):
        candidate = i
```

`candidate`가 `i`를 안다면 기존 candidate는 Celebrity가 아니므로 `i`를 새로운 후보로 만든다.

반대로 모른다면 `i`가 Celebrity일 수 없으므로 candidate를 그대로 유지한다.

#### 예시

```text
사람: A B C D E

candidate = A

A knows B?
YES
→ A 제거
→ candidate = B

B knows C?
NO
→ C 제거
→ candidate = B

B knows D?
YES
→ B 제거
→ candidate = D

D knows E?
NO
→ E 제거
→ candidate = D
```

최종적으로 `D` 하나만 후보로 남는다.

---

### Step 2. 후보 검증

후보 제거 과정은 **Celebrity일 가능성이 있는 사람 하나를 찾은 것일 뿐** 실제 Celebrity 존재를 보장하지 않는다.

따라서 모든 사람 `i != candidate`에 대해 확인한다.

```text
knows(candidate, i) == false
AND
knows(i, candidate) == true
```

하나라도 실패하면:

```text
Celebrity 없음
```

모두 만족하면:

```text
candidate가 Celebrity
```

---

## 1.5 의사코드

```text
FindCelebrity(N):

    candidate = 0

    // 1. 후보 선정
    for i = 1 to N-1:
        if knows(candidate, i):
            candidate = i

    // 2. 후보 검증
    for i = 0 to N-1:

        if i == candidate:
            continue

        if knows(candidate, i):
            return NO_CELEBRITY

        if not knows(i, candidate):
            return NO_CELEBRITY

    return candidate
```

---

## 1.6 구현 시 필요한 변수

```text
N           : 전체 사람 수
candidate   : 현재 Celebrity 후보
i           : 반복문 인덱스
```

제거된 사람 목록은 저장할 필요가 없다.

한 번 제거된 사람은 이후 다시 후보가 될 필요가 없기 때문이다.

---

## 1.7 복잡도

### 시간 복잡도

후보 선정:

```text
N - 1
```

후보 검증:

```text
2(N - 1)
```

따라서 보고서에서 계산한 최대 질문 수는

```text
(N-1) + 2(N-1)

= 3(N-1)
= 3N - 3
```

따라서

```text
Time Complexity = O(N)
```

단, 실제 구현에서 검증 중 조건 위반을 발견하면 즉시 종료할 수 있으므로 항상 `3N-3`번 질문하는 것은 아니다. **최악의 경우 최대 `3N-3`번**이라고 표현하는 것이 정확하다.

### 공간 복잡도

후보 목록이나 제거된 사람을 저장하지 않는다.

```text
candidate
i
```

등 상수 개수의 변수만 사용한다.

```text
Space Complexity = O(1)
```

---

# 최종 구현 요약

| 문제                       | 핵심 알고리즘    | 구현 핵심                  | 시간 복잡도 | 공간 복잡도 |
| -------------------------- | ---------------- | -------------------------- | ----------- | ----------- |
| **1. Finding Celebrities** | 후보 제거 + 검증 | 질문 1회마다 후보 1명 제거 | **O(N)**    | **O(1)**    |
