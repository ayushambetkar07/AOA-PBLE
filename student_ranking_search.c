
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STUDENTS 100
#define NUM_SUBJECTS 5
#define NAME_LEN 50

typedef struct {
    int roll;
    char name[NAME_LEN];
    int marks[NUM_SUBJECTS];
    int total;
} Student;

const char *subjectNames[NUM_SUBJECTS] = {
    "Mathematics", "Physics", "Chemistry", "Data Structures", "C Programming"
};

Student students[MAX_STUDENTS];
int studentCount = 0;

void addStudent();
void editStudent();
void displayAll();
void displayList(Student arr[], int n);
void selectionSort(Student arr[], int n, int ascending, long *comparisons, long *swaps);
void insertionSort(Student arr[], int n, int ascending, long *comparisons, long *shifts);
void sortByRoll(Student arr[], int n);
int  binarySearch(Student arr[], int n, int targetRoll, long *comparisons);
void sortAndRank();
void searchStudent();
void generateTestData(Student arr[], int n, int mode);
void analyzePerformance();

void addStudent() {
    Student s;
    int i;

    if (studentCount >= MAX_STUDENTS) {
        printf("\nStudent list is full!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Full Name: ");
    scanf(" %[^\n]", s.name);

    s.total = 0;
    for (i = 0; i < NUM_SUBJECTS; i++) {
        printf("Enter marks for %s: ", subjectNames[i]);
        scanf("%d", &s.marks[i]);
        s.total += s.marks[i];
    }

    students[studentCount] = s;
    studentCount++;
    printf("\nStudent added successfully!\n");
}

void editStudent() {
    int roll, found = -1;
    int i;

    if (studentCount == 0) {
        printf("\nNo records available to edit.\n");
        return;
    }

    printf("\nEnter Roll Number of student to edit: ");
    scanf("%d", &roll);

    /* linear search since data is not sorted here */
    for (i = 0; i < studentCount; i++) {
        if (students[i].roll == roll) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nStudent with Roll Number %d not found.\n", roll);
        return;
    }

    printf("\nEditing record for: %s\n", students[found].name);
    printf("Enter new Full Name: ");
    scanf(" %[^\n]", students[found].name);

    students[found].total = 0;
    for (i = 0; i < NUM_SUBJECTS; i++) {
        printf("Enter new marks for %s: ", subjectNames[i]);
        scanf("%d", &students[found].marks[i]);
        students[found].total += students[found].marks[i];
    }
    printf("\nRecord updated successfully!\n");
}

void displayList(Student arr[], int n) {
    int i, j;

    if (n == 0) {
        printf("\nNo records to display.\n");
        return;
    }

    printf("\n%-6s %-20s %-6s %-6s %-6s %-6s %-8s %-6s\n",
           "Roll", "Name", "Maths", "Phy", "Chem", "DS", "C-Prog", "Total");

    for (i = 0; i < n; i++) {
        printf("%-6d %-20s", arr[i].roll, arr[i].name);
        for (j = 0; j < NUM_SUBJECTS; j++)
            printf(" %-6d", arr[i].marks[j]);
        printf(" %-6d\n", arr[i].total);
    }
}

void displayAll() {
    displayList(students, studentCount);
}

/* sorts by total marks, counts comparisons and swaps */
void selectionSort(Student arr[], int n, int ascending, long *comparisons, long *swaps) {
    int i, j, targetIndex;
    Student temp;

    *comparisons = 0;
    *swaps = 0;

    for (i = 0; i < n - 1; i++) {
        targetIndex = i;

        for (j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (ascending) {
                if (arr[j].total < arr[targetIndex].total)
                    targetIndex = j;
            } else {
                if (arr[j].total > arr[targetIndex].total)
                    targetIndex = j;
            }
        }

        /* swap only if position actually changes */
        if (targetIndex != i) {
            temp = arr[i];
            arr[i] = arr[targetIndex];
            arr[targetIndex] = temp;
            (*swaps)++;
        }
    }
}

/* sorts by total marks, counts comparisons and shifts */
void insertionSort(Student arr[], int n, int ascending, long *comparisons, long *shifts) {
    int i, j;
    Student key;
    int shouldShift;

    *comparisons = 0;
    *shifts = 0;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0) {
            (*comparisons)++;
            shouldShift = ascending ? (arr[j].total > key.total)
                                    : (arr[j].total < key.total);
            if (!shouldShift) break;

            arr[j + 1] = arr[j];
            (*shifts)++;
            j--;
        }
        arr[j + 1] = key;
    }
}

/* simple sort by roll number, needed before binary search */
void sortByRoll(Student arr[], int n) {
    int i, j;
    Student key;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j].roll > key.roll) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/* array must be sorted by roll number before calling this */
int binarySearch(Student arr[], int n, int targetRoll, long *comparisons) {
    int low = 0, high = n - 1;
    int mid;
    *comparisons = 0;

    while (low <= high) {
        mid = (low + high) / 2;
        (*comparisons)++;

        if (arr[mid].roll == targetRoll)
            return mid;
        else if (arr[mid].roll < targetRoll)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void sortAndRank() {
    int order, ascending, i, topperIndex;
    Student copyForSelection[MAX_STUDENTS];
    Student copyForInsertion[MAX_STUDENTS];
    long selComparisons, selSwaps, insComparisons, insShifts;

    if (studentCount == 0) {
        printf("\nNo records available. Please add students first.\n");
        return;
    }

    printf("\nChoose Rank Order - 1: Ascending  2: Descending: ");
    scanf("%d", &order);
    ascending = (order == 1) ? 1 : 0;

    for (i = 0; i < studentCount; i++) {
        copyForSelection[i] = students[i];
        copyForInsertion[i] = students[i];
    }

    selectionSort(copyForSelection, studentCount, ascending, &selComparisons, &selSwaps);
    insertionSort(copyForInsertion, studentCount, ascending, &insComparisons, &insShifts);

    printf("\n--- Rank List (Selection Sort) ---\n");
    displayList(copyForSelection, studentCount);
    printf("Comparisons: %ld | Swaps: %ld\n", selComparisons, selSwaps);

    printf("\n--- Rank List (Insertion Sort) ---\n");
    displayList(copyForInsertion, studentCount);
    printf("Comparisons: %ld | Shifts: %ld\n", insComparisons, insShifts);

    printf("\n--- Topper Details ---\n");
    topperIndex = ascending ? (studentCount - 1) : 0;
    printf("Roll No: %d | Name: %s | Total Marks: %d\n",
           copyForSelection[topperIndex].roll,
           copyForSelection[topperIndex].name,
           copyForSelection[topperIndex].total);
}

void searchStudent() {
    Student sortedCopy[MAX_STUDENTS];
    int i, targetRoll, index;
    long comparisons;

    if (studentCount == 0) {
        printf("\nNo records available. Please add students first.\n");
        return;
    }

    for (i = 0; i < studentCount; i++)
        sortedCopy[i] = students[i];

    sortByRoll(sortedCopy, studentCount);

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &targetRoll);

    index = binarySearch(sortedCopy, studentCount, targetRoll, &comparisons);

    if (index != -1) {
        printf("\nRecord Found!\n");
        printf("Roll No: %d | Name: %s | Total Marks: %d\n",
               sortedCopy[index].roll, sortedCopy[index].name, sortedCopy[index].total);
    } else {
        printf("\nRecord not found for Roll Number %d.\n", targetRoll);
    }
    printf("Comparisons made (Binary Search): %ld\n", comparisons);
}

/* mode: 1 = sorted, 2 = reverse sorted, 3 = random */
void generateTestData(Student arr[], int n, int mode) {
    int i, j, baseValue;

    for (i = 0; i < n; i++) {
        arr[i].roll = i + 1;
        sprintf(arr[i].name, "Test%d", i + 1);

        if (mode == 1) baseValue = i * 2;
        else if (mode == 2) baseValue = (n - i) * 2;
        else baseValue = rand() % 100;

        arr[i].total = 0;
        for (j = 0; j < NUM_SUBJECTS; j++) {
            arr[i].marks[j] = baseValue / NUM_SUBJECTS;
            arr[i].total += arr[i].marks[j];
        }
    }
}

/* tests different data sizes and arrangements to show how work
   done by each algorithm changes */
void analyzePerformance() {
    int testSizes[4] = {5, 10, 20, 50};
    int numSizes = 4;
    const char *arrangementNames[3] = {"Already Sorted", "Reverse Sorted", "Random Order"};
    int s, mode, n, i;
    Student baseData[MAX_STUDENTS];
    Student copyForSelection[MAX_STUDENTS];
    Student copyForInsertion[MAX_STUDENTS];
    long selComparisons, selSwaps, insComparisons, insShifts;

    printf("\n===================================================================\n");
    printf(" SORTING PERFORMANCE ANALYSIS\n");
    printf("===================================================================\n");
    printf("%-6s %-16s %16s %10s %16s %10s\n",
           "n", "Arrangement", "Sel-Comparisons", "Sel-Swaps",
           "Ins-Comparisons", "Ins-Shifts");
    printf("-------------------------------------------------------------------\n");

    for (s = 0; s < numSizes; s++) {
        n = testSizes[s];

        for (mode = 1; mode <= 3; mode++) {
            generateTestData(baseData, n, mode);

            for (i = 0; i < n; i++) {
                copyForSelection[i] = baseData[i];
                copyForInsertion[i] = baseData[i];
            }

            selectionSort(copyForSelection, n, 1, &selComparisons, &selSwaps);
            insertionSort(copyForInsertion, n, 1, &insComparisons, &insShifts);

            printf("%-6d %-16s %16ld %10ld %16ld %10ld\n",
                   n, arrangementNames[mode - 1],
                   selComparisons, selSwaps, insComparisons, insShifts);
        }
        printf("-------------------------------------------------------------------\n");
    }

    printf("\nObservation:\n");
    printf("- Selection Sort comparisons stay almost same regardless of arrangement.\n");
    printf("- Insertion Sort shifts are lowest on sorted data, highest on reverse.\n");
    printf("- As n increases, work increases for both algorithms.\n");
}

int main() {
    int choice;

    srand((unsigned int) time(NULL));

    printf("=====================================================\n");
    printf(" SMART STUDENT RANKING AND SEARCH SYSTEM\n");
    printf("=====================================================\n");

    do {
        printf("\n----------------- MENU -----------------\n");
        printf("1. Add Student\n");
        printf("2. Edit Student\n");
        printf("3. Display All Students\n");
        printf("4. Sort & Rank (Selection vs Insertion)\n");
        printf("5. Search Student (Binary Search)\n");
        printf("6. Analyze Sorting Performance\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: editStudent(); break;
            case 3: displayAll(); break;
            case 4: sortAndRank(); break;
            case 5: searchStudent(); break;
            case 6: analyzePerformance(); break;
            case 7: printf("\nExiting program. Goodbye!\n"); break;
            default: printf("\nInvalid choice, try again.\n");
        }
    } while (choice != 7);

    return 0;
}
