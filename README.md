# Smart Delivery Planning – Fractional Knapsack

A menu-driven C program that uses the **Fractional Knapsack Greedy Algorithm** to maximize the total value that can be carried by a delivery vehicle with limited carrying capacity.

---

## 📌 About the Project

**Smart Delivery Planning** is an AOA (Analysis and Design of Algorithms) project based on the **Fractional Knapsack Problem**.

In this project, a delivery vehicle has a fixed carrying capacity and several packages. Each package has a specific **weight** and **value/profit**.

The objective is to maximize the total value carried by the vehicle.

Unlike the 0/1 Knapsack problem, the Fractional Knapsack problem allows a **fraction of a package** to be selected when the complete package cannot fit within the remaining capacity.

The project uses the **Greedy Method** by selecting packages according to their **Value/Weight ratio**.

---

## 🎯 Objectives

- Understand the **Greedy Method**.
- Calculate the **Value/Weight ratio** for each package.
- Sort packages in decreasing order of ratio.
- Select complete packages whenever possible.
- Select a fraction of a package when required.
- Calculate the maximum achievable value.
- Display selected packages and their fractions.
- Analyze the time and space complexity of the algorithm.

---

## 🧠 Algorithm Used

### Fractional Knapsack – Greedy Method

For every package, calculate:

```text
Value/Weight Ratio = Value / Weight
```

Packages are then sorted in **descending order of their ratio**.

The algorithm selects packages as follows:

1. Start with the complete vehicle capacity.
2. Select the package with the highest Value/Weight ratio.
3. If the complete package fits, select it completely.
4. If it does not fit, select the fraction that can fit.
5. Calculate the value obtained from the selected fraction.
6. Continue until the vehicle capacity is full.
7. The total selected value is the maximum achievable value.

---

## 📋 Menu Options

The program provides the following menu:

```text
==================================================
        SMART DELIVERY PLANNING
        FRACTIONAL KNAPSACK
==================================================

1. Enter Package Details
2. Display Package Details
3. Calculate Value/Weight Ratio
4. Sort Packages by Ratio
5. Find Maximum Value
6. Display Selected Packages
7. Exit
```

### 1. Enter Package Details

Allows the user to enter:

- Number of packages
- Package value
- Package weight
- Vehicle carrying capacity

Input validation is included to prevent invalid values such as zero or negative weights.

### 2. Display Package Details

Displays the entered package information along with the calculated ratio when available.

### 3. Calculate Value/Weight Ratio

Calculates:

```text
Ratio = Value / Weight
```

for every package.

### 4. Sort Packages by Ratio

Sorts packages from the **highest Value/Weight ratio to the lowest**.

### 5. Find Maximum Value

Executes the Fractional Knapsack Greedy Algorithm and calculates:

- Selected packages
- Selected fractions
- Selected weight
- Selected value
- Total weight used
- Maximum value obtained

### 6. Display Selected Packages

Displays the packages selected by the algorithm, including the fraction selected from each package.

### 7. Exit

Terminates the program.

---

## 📊 Example

### Input

Consider the following packages:

| Package | Value | Weight | Value/Weight |
|--------:|------:|-------:|-------------:|
| 1 | 40 | 5 | 8.00 |
| 2 | 30 | 10 | 3.00 |
| 3 | 50 | 5 | 10.00 |
| 4 | 20 | 4 | 5.00 |

Vehicle Capacity:

```text
15
```

### Sorted Order

Packages are arranged according to decreasing Value/Weight ratio:

```text
Package 3 → Ratio = 10
Package 1 → Ratio = 8
Package 4 → Ratio = 5
Package 2 → Ratio = 3
```

### Selection

```text
Package 3 → Full package → Weight = 5 → Value = 50
Package 1 → Full package → Weight = 5 → Value = 40
Package 4 → Full package → Weight = 4 → Value = 20
Package 2 → 10%          → Weight = 1 → Value = 3
```

### Final Result

```text
Total Weight Used = 15
Maximum Value     = 113
```

Therefore, the maximum possible value that can be carried is:

```text
113
```

---

## 🔄 Working Flow

```text
Start
  │
  ▼
Enter Package Details
  │
  ▼
Calculate Value/Weight Ratio
  │
  ▼
Sort Packages by Ratio
  │
  ▼
Start Greedy Selection
  │
  ├── Package Fits?
  │       │
  │       ├── Yes → Select Complete Package
  │       │
  │       └── No  → Select Required Fraction
  │
  ▼
Update Remaining Capacity
  │
  ▼
Capacity Full?
  │
  ├── No → Continue
  │
  └── Yes
       │
       ▼
Calculate Maximum Value
       │
       ▼
Display Selected Packages
       │
       ▼
End
```

---

## 🧮 Fraction Calculation

When a complete package cannot fit:

```text
Fraction = Remaining Capacity / Package Weight
```

Then:

```text
Selected Weight = Package Weight × Fraction

Selected Value = Package Value × Fraction
```

### Example

If:

```text
Package Weight = 10
Package Value = 30
Remaining Capacity = 1
```

Then:

```text
Fraction = 1 / 10
         = 0.10
         = 10%
```

Therefore:

```text
Selected Weight = 10 × 0.10 = 1

Selected Value = 30 × 0.10 = 3
```

---

## 💡 Why Greedy Method?

The Fractional Knapsack problem can be solved optimally using the Greedy Method because fractions of packages are allowed.

At every step, the algorithm chooses the package with the **highest value per unit of weight**.

This gives the best possible value for the available capacity at that step.

---

## ⏱️ Time Complexity

The algorithm consists of three major operations.

### 1. Ratio Calculation

For `n` packages:

```text
O(n)
```

### 2. Sorting

Using Bubble Sort or Selection Sort:

```text
O(n²)
```

### 3. Greedy Selection

Each package is processed once:

```text
O(n)
```

### Overall Time Complexity

The sorting operation dominates the other operations.

Therefore:

```text
Overall Time Complexity = O(n²)
```

---

## 💾 Space Complexity

The program stores package information in an array.

For `n` packages:

```text
Space Complexity = O(n)
```

---

## 🛠️ Technologies Used

- **Language:** C
- **Concept:** Fractional Knapsack
- **Algorithm:** Greedy Method
- **Data Structures:** Arrays, Structures
- **Sorting:** Bubble Sort / Selection Sort
- **Compiler:** GCC / Any Standard C Compiler

---

## 📁 Project Structure

```text
Smart-Delivery-Planning/
│
├── smart_delivery_planning.c
└── README.md
```

---

## ▶️ How to Run

### 1. Clone the Repository

```bash
git clone <repository-url>
```

### 2. Open the Project Directory

```bash
cd Smart-Delivery-Planning
```

### 3. Compile the Program

Using GCC:

```bash
gcc smart_delivery_planning.c -o smart_delivery_planning
```

### 4. Run the Program

**Windows:**

```bash
smart_delivery_planning.exe
```

**Linux/macOS:**

```bash
./smart_delivery_planning
```

---

## 🧪 Test Cases

The program handles different situations including:

- Single package
- Multiple packages
- Decimal values and weights
- Vehicle capacity greater than total package weight
- Vehicle capacity equal to total package weight
- Vehicle capacity smaller than a package
- Equal Value/Weight ratios
- Invalid weight
- Invalid capacity
- Invalid number of packages
- Selecting menu options before entering package data
- Re-entering package details after a previous calculation

---

## ⚠️ Input Validation

The program prevents invalid inputs such as:

```text
Number of packages <= 0
Number of packages > MAX_PACKAGES
Weight <= 0
Capacity <= 0
Negative values
```

This also prevents division-by-zero errors during ratio calculation.

---

## 📚 AOA Concepts Covered

This project demonstrates:

- Greedy Algorithms
- Fractional Knapsack
- Optimization
- Value/Weight Ratio
- Sorting
- Arrays
- Structures
- Functions
- Time Complexity
- Space Complexity
- Algorithm Design

---

## 🔍 Fractional Knapsack vs 0/1 Knapsack

| Feature | Fractional Knapsack | 0/1 Knapsack |
|---|---|---|
| Complete package | ✅ | ✅ |
| Fraction of package | ✅ | ❌ |
| Greedy approach | ✅ Optimal | ❌ Not always optimal |
| Dynamic Programming | Not required | Commonly used |
| Sorting by Value/Weight | ✅ | Not sufficient for optimal solution |

This project specifically implements **Fractional Knapsack using the Greedy Method**.

---

## 🎓 Project Type

**Subject:** Analysis and Design of Algorithms (AOA)

**Project Type:** PBLE / Practical-Based Learning Experience

**Topic:** Greedy Method – Fractional Knapsack

**Language:** C

---

## 👨‍💻 Author

**Ayush Ambetkar**

---

## ⭐ Key Takeaway

The project demonstrates how the **Greedy Method** can be used to solve the Fractional Knapsack problem efficiently by always selecting the package with the highest **Value/Weight ratio** first.

```text
Calculate Ratio
       ↓
Sort by Ratio
       ↓
Select Highest Ratio
       ↓
Take Full Package
       ↓
Take Fraction if Required
       ↓
Maximum Value
```

---

## 📜 License

This project is created for **educational and academic purposes**.
