# Problem Solving Practice - Coding Problem #1

> 출처: `ps_coding_assignment_01.pdf`, 전체 13페이지.
> 영어 원문을 페이지 순서대로 보존하고, 그림 속 관계와 이미지로 삽입된 표를 텍스트로 전사했다. 줄바꿈과 목록 구조를 Markdown에 맞추고, 아래첨자는 `x_1`, 거듭제곱은 `a^n`으로 표기했다. 예제의 따옴표는 ASCII 작은따옴표로 통일했다. 한국어로 된 전사 설명은 원문과 구분된다. PDF에 없는 풀이 또는 추가 조건은 포함하지 않았다.

## PDF 1페이지 - 표지

**Problem Solving Practice**

**Coding Problem #1**

**CSE4152**

Sogang University

그림: 서강대학교 교표. 교표에 `서강대학교`, `1960`, `IHS`, `SOGANG UNIVERSITY`가 표시되어 있다.

하단 표기: `CSE4152 F’26` / `1`

## PDF 2페이지 - Finding Celebrities

A celebrity is defined as a person who is known by everybody but does not know anyone. How can you find any celebrities among N people?

You can freely ask anyone as follows: "Hey, you know Mr. (or Ms.) X?"

Suppose that there are N people. Design a method that

a) determines whether there is some celebrities among the people

b) if there is any celebrities, find them efficiently (minimizing the number of questions you make).

하단 표기: `CSE4152 F’26` / `2`

## PDF 3페이지 - Finding Celebrities

In this problem, you will only be working within the `main.cpp` file. The following two functions are provided for you to interact with the problem:

### `ask_a_to_know_b(int a, int b)`

- Ask person A if they know person B.
- return 1 if A knows B, otherwise return 0.
- Never call `ask_a_to_know_b(i, i)` (i.e., do not ask if someone knows themselves)

### `answer(int x)`

- verifies if person x is a celebrity
- if there is no celebrity, call -1

Your task is to implement the logic within the `main()` function in `main.cpp`

하단 표기: `CSE4152 F’26` / `3`

## PDF 4페이지 - Finding Celebrities

### Interaction

#### Your Output:

- You will print interactions using the provided `ask_a_to_know_b(a, b)` function to ask if one person knows another.
- Example: `? 1 2` asks if person 1 knows person 2.

#### Judge's Response:

- The judge will respond with `1` (Yes) or `0` (No) based on the relationship.
- Example: `0` means person 1 does not know person 2 if the question is “`? 1 2`”.

#### Final Answer:

- After determining the celebrity (or finding there is none), call `answer(x)` with the candidate's index or `-1`.
- Example: `! 1` means you believe person 1 is the celebrity. The judge will then confirm if this is correct.

하단 표기: `CSE4152 F’26` / `4`

## PDF 5페이지 - Finding Celebrities

### Steps to test your algorithm.

You should test your program by interacting with it by yourself.

#### Step 1. Create your own celebrity graph

- Before diving into the code, start by visualizing the relationships as a graph.

#### Step 2. Run the program and answer function `ask_a_to_know_b` by your hand.

- based on your graph, manually type the output of `ask_a_to_know_b(a, b)` for various pairs (a, b).
- For example, if Person 1 knows Person 2 (`ask_a_to_know_b(1, 2)`), draw an edge from 1 to 2.

#### Step 3. Type the response for `answer(x)`

- Check if the celebrity identified in the code (`answer(x)`) matches the one you set in your created celebrity graph

하단 표기: `CSE4152 F’26` / `5`

## PDF 6페이지 - Finding Celebrities

### Example

#### Step 1. Create your own celebrity graph

- Before diving into the code, start by visualizing the relationships as a graph.

### 그림 전사: celebrity graph

- 정점: `1`, `2`, `3`, `4`.
- 배치: 왼쪽 위 `1`, 오른쪽 위 `2`, 왼쪽 아래 `4`, 오른쪽 아래 `3`.
- 그림에 표시된 방향 간선 전체:
  - `2 → 1`: 2가 1을 안다.
  - `3 → 1`: 3이 1을 안다.
  - `4 → 1`: 4가 1을 안다.
- 그 외 간선은 그려져 있지 않다. 정점 1에서 나가는 간선도 없다.
- 그림 캡션: `celebrity graph`.

### 그림 전사: 범례

`A → B`

원문 설명: **A knows B**

하단 표기: `CSE4152 F’26` / `6`

## PDF 7페이지 - Finding Celebrities

### Example

#### Step 2. Reply to every call `ask_a_to_know_b` called by your program.

### 그림 전사: celebrity graph

- 정점 배치: 왼쪽 위 `1`, 오른쪽 위 `2`, 왼쪽 아래 `4`, 오른쪽 아래 `3`.
- 방향 간선 전체: `2 → 1`, `3 → 1`, `4 → 1`.
- 그 외 간선은 그려져 있지 않다.
- 그림 캡션: `celebrity graph`.

### Interaction

아래 표는 PDF의 이미지 표 전체를 행 순서대로 전사한 것이다. 빈 칸은 원문의 빈 칸이다.

| Your Output | Judge | Explanation         |
| ----------- | ----- | ------------------- |
|             | `4`   | N = 4.              |
| `? 1 2`     |       | Does 1 know 2?      |
|             | `0`   | 1 does not know 2.  |
| `? 2 1`     |       | Does 2 know 1?      |
|             | `1`   | 2 does know 1.      |
| `? 1 3`     |       | Does 1 know 3?      |
|             | `0`   | 1 does not know 3.  |
| `? 3 1`     |       | Does 3 know 1?      |
|             | `1`   | 3 does know 1.      |
| `? 1 4`     |       | Does 1 know 4?      |
|             | `0`   | 1 does not know 4.  |
| `? 4 1`     |       | Does 4 know 1?      |
|             | `1`   | 4 does know 1.      |
| `! 1`       |       | Is 1 the celebrity? |
|             | `1`   | 1 is the celebrity. |

하단 표기: `CSE4152 F’26` / `7`

## PDF 8페이지 - Finding Celebrities

### Example

#### Step 3. Reply to `answer(x)` function

### 그림 전사: celebrity graph

- 정점 배치: 왼쪽 위 `1`, 오른쪽 위 `2`, 왼쪽 아래 `4`, 오른쪽 아래 `3`.
- 방향 간선 전체: `2 → 1`, `3 → 1`, `4 → 1`.
- 그 외 간선은 그려져 있지 않다.
- 그림 캡션: `celebrity graph`.

### Interaction

이 페이지에도 다음 표 전체가 반복되어 있다.

| Your Output | Judge | Explanation         |
| ----------- | ----- | ------------------- |
|             | `4`   | N = 4.              |
| `? 1 2`     |       | Does 1 know 2?      |
|             | `0`   | 1 does not know 2.  |
| `? 2 1`     |       | Does 2 know 1?      |
|             | `1`   | 2 does know 1.      |
| `? 1 3`     |       | Does 1 know 3?      |
|             | `0`   | 1 does not know 3.  |
| `? 3 1`     |       | Does 3 know 1?      |
|             | `1`   | 3 does know 1.      |
| `? 1 4`     |       | Does 1 know 4?      |
|             | `0`   | 1 does not know 4.  |
| `? 4 1`     |       | Does 4 know 1?      |
|             | `1`   | 4 does know 1.      |
| `! 1`       |       | Is 1 the celebrity? |
|             | `1`   | 1 is the celebrity. |

### 그림 전사: answer

- 원 안의 정점: `1`.
- 원 아래 문구: **call answer(1)**.
- 그림 캡션: `answer`.

하단 표기: `CSE4152 F’26` / `8`

## PDF 9페이지 - 2 Keys Keyboard

Initially, there is only one character 'A' on the screen. You can perform one of two operations:

- **Copy All:** copy all characters on the screen (partial copy is not allowed).
- **Paste:** paste the characters that were copied last time.

Given an integer N, return the minimum number of operations required to display exactly N 'A' characters on the screen.

하단 표기: `CSE4152 F’26` / `9`

## PDF 10페이지 - Example

### Example

- **Input:** N = 6
- **Output:** 5

### Explanation:

- Step 1: Copy All → 'A' (clipboard = 'A')
- Step 2: Paste → 'AA'
- Step 3: Paste → 'AAA'
- Step 4: Copy All → 'AAA'
- Step 5: Paste → 'AAAAAA'

하단 표기: `CSE4152 F’26` / `10`

## PDF 11페이지 - Minimum calculation

Imagine an electric calculator which has only two arithmetic operations, i.e., assignment operation(`:=`) and multiplication operation (`*`). We want to let this machine compute `b = a^n` for given numbers a and n.

Previously computed results can be stored in separate variables and reused in later multiplications. Design a method that produces a code for this machine, minimizing the number of multiplications.

하단 표기: `CSE4152 F’26` / `11`

## PDF 12페이지 - Example when n = 16

원문의 아래첨자를 `_`로, 위첨자를 `^`로 전사한 예제 코드:

```text
x_1 := a;

x_2 := x_1 * x_1; // a^2
x_3 := x_2 * x_2; // a^4

x_4 := x_3 * x_3; // a^8
x_5 := x_4 * x_4; // a^16
b:=x_5
```

하단 표기: `CSE4152 F’26` / `9`

전사 주: 실제 PDF의 12번째 페이지지만, 원문 슬라이드 하단에는 `9`로 표기되어 있다.

## PDF 13페이지 - Minimum calculation

### Input

```text
16
```

### Output

```text
4 1 2 4 8 16
```

하단 표기: `CSE4152 F’26` / `13`
