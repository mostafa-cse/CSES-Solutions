# 📘 CSES Problem Set – Introductory Problems

This repository contains solutions to the **Introductory Problems** section of the [CSES Problem Set](https://cses.fi/problemset/). Each problem is organized into its own folder, which may contain multiple implementations or approaches in different languages or techniques.

---

## 📁 Folder Structure

```
cses-intro/
├── Weird Algorithm/
│   ├── Iterative solution.cpp
│   └── Recursive Solution.cpp
|
├── Missing Number/
│   ├── Math Solution.cpp
│   ├── Using Xor Elimination.cpp
│   ├── hashing or marking trick.cpp
│   └── using set operation.cpp
|
├── Increasing Array/
│   └── binary Search and Sliding window.cpp
│   └── using two pointer.cpp
|
├── Permutations/
│   └── simple constructive.cpp
|
├── Number Spiral/
│   └── Math-formula-1.cpp
│   └── math formula - 2 more observation.cpp
|
├── Two Knights/
│   └── Another Way.cpp
|   ├── Dp Solution.cpp
|   ├── ONE MORE.cpp
|   ├── Question.txt
│   └── math_solution.cpp
|
├── Bit Strings/
│   └── ModPow iterative.cpp
│   └── ModPow recursive solution.cpp
|
├── Trailing Zeros/
│   └── Using Legendres Algo.cpp
│   └── little bit different implementation.cpp
|
├── Coin Piles/
│   └── math Solution.cpp
|   ├── mathSolution.cpp
│   └── math with simple observation.cpp
|
├── Palindrome Reorder/
│   └── Map Solution.cpp
│   └── vector hash solution.cpp
|
├── Gray Code/
│   └── Solution.cpp
│   └── using Bitset operation.cpp
|
├── Tower of Hanoi/
│   └── Solution.cpp
|
├── Creating Strings/
│   └── Simple Solution.cpp
|   ├── store then Print.cpp
│   └── Using set.cpp
|
├── Apple Division/
│   └── Bitmasking solution.cpp
│   └── using recursion.cpp
|
├── Chessboard and Queens/
│   └── Another one last.cpp
|   ├── Bimasking trick.cpp
|   ├── Resursive Solution.cpp
│   └── Using permutation trick.cpp
|
├── Raab Game I/
│   └── Solution1.cpp
|   ├── Solution2.cpp
│   └── Solution3.cpp
|
├── Mex Grid Construction/
│   └── Solution1.cpp
|
├── Knight Moves Grid/ 
│   └── Using BFS.cpp
|
├── Grid Coloring I/
│   └── Solution1.cpp
│   └── Solution2.cpp
|
├── Digit Queries/
│   └── TryTosolve using Binary Search.cpp
│   └── using math.cpp
|
├── String Reorder/
│   └── Solution1.cpp
│   └── Solution2.cpp
|
└── 24.Grid Paths/ 
│   └── Solution1.cpp
```

* **Each folder** is named after the problem title.
* **Each folder** may contain:

  * Multiple solution files (e.g., `solution.cpp`, `solution.py`, etc.)
  * A `README.md` file (optional) explaining the logic or comparing methods.

---

## 📌 Problem List (Introductory Problems)
| #  | Problem Name          | Link                                       | Folder Name             |
| -- | --------------------- | ------------------------------------------ | ----------------------- |
| 1  | Weird Algorithm       | [🔗](https://cses.fi/problemset/task/1068) | `Weird Algorithm`       |
| 2  | Missing Number        | [🔗](https://cses.fi/problemset/task/1083) | `Missing Number`        |
| 3  | Repetitions           | [🔗](https://cses.fi/problemset/task/1069) | `Repetitions`           |
| 4  | Increasing Array      | [🔗](https://cses.fi/problemset/task/1094) | `Increasing Array`      |
| 5  | Permutations          | [🔗](https://cses.fi/problemset/task/1070) | `Permutations`          |
| 6  | Number Spiral         | [🔗](https://cses.fi/problemset/task/1071) | `Number Spiral`         |
| 7  | Two Knights           | [🔗](https://cses.fi/problemset/task/1072) | `Two Knights`           |
| 8  | Two Sets              | [🔗](https://cses.fi/problemset/task/1092) | `Two Sets`              |
| 9  | Bit Strings           | [🔗](https://cses.fi/problemset/task/1617) | `Bit Strings`           |
| 10 | Trailing Zeros        | [🔗](https://cses.fi/problemset/task/1618) | `Trailing Zeros`        |
| 11 | Coin Piles            | [🔗](https://cses.fi/problemset/task/1754) | `Coin Piles`            |
| 12 | Palindrome Reorder    | [🔗](https://cses.fi/problemset/task/1755) | `Palindrome Reorder`    |
| 13 | Gray Code             | [🔗](https://cses.fi/problemset/task/1632) | `Gray Code`             |
| 14 | Tower of Hanoi        | [🔗](https://cses.fi/problemset/task/1073) | `Tower of Hanoi`        |
| 15 | Creating Strings      | [🔗](https://cses.fi/problemset/task/1626) | `Creating Strings`      |
| 16 | Apple Division        | [🔗](https://cses.fi/problemset/task/1623) | `Apple Division`        |
| 17 | Chessboard and Queens | [🔗](https://cses.fi/problemset/task/1063) | `Chessboard and Queens` |
| 18 | Raab Game I           | [🔗](https://cses.fi/problemset/task/2214) | `Raab Game I`           |
| 19 | Mex Grid Construction | [🔗](https://cses.fi/problemset/task/2215) | `Mex Grid Construction` |
| 20 | Knight Moves Grid     | [🔗](https://cses.fi/problemset/task/2216) | `Knight Moves Grid`     |
| 21 | Grid Coloring I       | [🔗](https://cses.fi/problemset/task/2217) | `Grid Coloring I`       |
| 22 | Digit Queries         | [🔗](https://cses.fi/problemset/task/2431) | `Digit Queries`         |
| 23 | String Reorder        | [🔗](https://cses.fi/problemset/task/2105) | `String Reorder`        |
| 24 | Grid Path Description | [🔗](https://cses.fi/problemset/task/1616) | `Grid Path Description` |

---

## 🚀 Getting Started

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/cses-intro.git
   cd cses-intro
   ```

2. Navigate to a problem folder:

   ```bash
   cd "Weird Algorithm"
   ```

3. Run a solution (example for C++):

   ```bash
   g++ solution.cpp -o solution
   ./solution
   ```

---

## 💡 Why Multiple Solutions?

Some problems include:

* A brute-force and an optimized version
* Solutions in different languages (e.g., C++, Python, Java)
* Commentary or time/space complexity comparisons

This format is helpful for learning, comparing approaches, and revisiting improved strategies.

---

## 🛠️ Language and Style

* 🧠 Clean, readable code with comments
* ⏱️ Time-efficient logic wherever possible
* 💬 Multiple programming languages supported (C++, Python, etc.)

---

## 🤝 Contributing

You’re welcome to contribute:

* Additional solutions (different languages or optimizations)
* Problem explanations in folder-specific `README.md` files
* Improvements in code structure or documentation

---

## 📄 License

Licensed under the MIT License. See `LICENSE` for details.

---

## 🙌 Acknowledgements

* [CSES.fi](https://cses.fi) – for the problem set
* Ville Karavirta – for curating a structured and educational set of challenges

---

Let me know if you want help generating per-problem README templates too!
