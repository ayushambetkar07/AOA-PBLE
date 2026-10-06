#include <stdio.h>
#include <stdlib.h>

#define MAX_PACKAGES 100
#define EPS 0.000001  

struct Package
{
    int id;
    double value;
    double weight;
    double ratio;
    double fraction;
    double selectedWeight;
    double selectedValue;
};

// function declarations
void displayMenu();
void clearBuffer();
int readInt();
double readDouble();
void enterPackageDetails(struct Package p[], int *n, double *capacity, int *entered, int *ratioDone, int *sortDone, int *solved);
void displayPackageDetails(struct Package p[], int n, double capacity, int ratioDone);
void calculateRatios(struct Package p[], int n, int show);
void sortPackages(struct Package p[], int n, int show);
void findMaximumValue(struct Package p[], int n, double capacity, double *totalWeight, double *totalValue);
void displaySelectedPackages(struct Package p[], int n, double totalWeight, double totalValue);

// remove the extra characters left in the input
void clearBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// read an integer, ask again if the input is not a number
int readInt()
{
    int x;
    int result;

    result = scanf("%d", &x);
    while (result != 1)
    {
        if (result == EOF)
        {
            exit(0);   // no more input
        }
        clearBuffer();
        printf("Invalid input! Please enter a number: ");
        result = scanf("%d", &x);
    }
    clearBuffer();
    return x;
}

// read a decimal number, ask again if the input is not a number
double readDouble()
{
    double x;
    int result;

    result = scanf("%lf", &x);
    while (result != 1)
    {
        if (result == EOF)
        {
            exit(0);   // no more input
        }
        clearBuffer();
        printf("Invalid input! Please enter a number: ");
        result = scanf("%lf", &x);
    }
    clearBuffer();
    return x;
}

void displayMenu()
{
    printf("\n==================================================\n");
    printf("        SMART DELIVERY PLANNING\n");
    printf("        FRACTIONAL KNAPSACK\n");
    printf("==================================================\n\n");
    printf("1. Enter Package Details\n");
    printf("2. Display Package Details\n");
    printf("3. Calculate Value/Weight Ratio\n");
    printf("4. Sort Packages by Ratio\n");
    printf("5. Find Maximum Value\n");
    printf("6. Display Selected Packages\n");
    printf("7. Exit\n\n");
    printf("Enter your choice: ");
}

// Option 1 - take the package details from the user
void enterPackageDetails(struct Package p[], int *n, double *capacity, int *entered, int *ratioDone, int *sortDone, int *solved)
{
    int i, count;
    double v, w, cap;

    // reset the old results because new data is going to be entered
    *entered = 0;
    *ratioDone = 0;
    *sortDone = 0;
    *solved = 0;

    // number of packages
    printf("Enter number of packages: ");
    count = readInt();
    while (count <= 0 || count > MAX_PACKAGES)
    {
        if (count <= 0)
            printf("Error: Number of packages must be greater than 0.\n");
        else
            printf("Error: Number of packages cannot be more than %d.\n", MAX_PACKAGES);
        printf("Enter number of packages: ");
        count = readInt();
    }

    // value and weight of every package
    for (i = 0; i < count; i++)
    {
        printf("Enter value of package %d: ", i + 1);
        v = readDouble();
        while (v < 0)
        {
            printf("Error: Value cannot be negative.\n");
            printf("Enter value of package %d: ", i + 1);
            v = readDouble();
        }

        printf("Enter weight of package %d: ", i + 1);
        w = readDouble();
        while (w <= 0)
        {
            printf("Error: Weight must be greater than 0.\n");
            printf("Enter weight of package %d: ", i + 1);
            w = readDouble();
        }

        p[i].id = i + 1;
        p[i].value = v;
        p[i].weight = w;
        p[i].ratio = 0;
        p[i].fraction = 0;
        p[i].selectedWeight = 0;
        p[i].selectedValue = 0;
    }

    // capacity of the vehicle
    printf("Enter maximum carrying capacity of vehicle: ");
    cap = readDouble();
    while (cap <= 0)
    {
        printf("Error: Capacity must be greater than 0.\n");
        printf("Enter maximum carrying capacity of vehicle: ");
        cap = readDouble();
    }

    *n = count;
    *capacity = cap;
    *entered = 1;
    printf("\nPackage details entered successfully.\n");
}

// Option 2 - show all packages in a table
void displayPackageDetails(struct Package p[], int n, double capacity, int ratioDone)
{
    int i;

    printf("\n------------------------------------------------------------\n");
    printf("%-10s%-13s%-14s%s\n", "ID", "Value", "Weight", "Ratio");
    printf("------------------------------------------------------------\n");
    for (i = 0; i < n; i++)
    {
        printf("%-10d%-13.2f%-14.2f", p[i].id, p[i].value, p[i].weight);
        if (ratioDone == 1)
            printf("%.2f\n", p[i].ratio);
        else
            printf("Not Calculated\n");
    }
    printf("------------------------------------------------------------\n");
    printf("\nVehicle Capacity: %.2f\n", capacity);
}

// Option 3 - ratio = value / weight
void calculateRatios(struct Package p[], int n, int show)
{
    int i;

    for (i = 0; i < n; i++)
    {
        p[i].ratio = p[i].value / p[i].weight;   // weight is never 0 (checked while input)

        if (show == 1)
        {
            printf("\nPackage %d\n", p[i].id);
            printf("Value  : %.2f\n", p[i].value);
            printf("Weight : %.2f\n", p[i].weight);
            printf("Ratio  : %.2f\n", p[i].ratio);
        }
    }
}

// Option 4 - selection sort (highest ratio first)
void sortPackages(struct Package p[], int n, int show)
{
    int i, j;
    struct Package temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            // if the next package has a bigger ratio, swap them
            if (p[i].ratio < p[j].ratio)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    if (show == 1)
    {
        printf("\nPackages sorted by Value/Weight Ratio:\n\n");
        printf("------------------------------------------------------------\n");
        printf("%-10s%-13s%-14s%s\n", "ID", "Value", "Weight", "Ratio");
        printf("------------------------------------------------------------\n");
        for (i = 0; i < n; i++)
        {
            printf("%-10d%-13.2f%-14.2f%.2f\n", p[i].id, p[i].value, p[i].weight, p[i].ratio);
        }
        printf("------------------------------------------------------------\n");
    }
}

// Option 5 - greedy fractional knapsack
// (packages must already be sorted by ratio)
void findMaximumValue(struct Package p[], int n, double capacity, double *totalWeight, double *totalValue)
{
    int i;
    double remaining;

    remaining = capacity;
    *totalWeight = 0;
    *totalValue = 0;

    // clear old selection
    for (i = 0; i < n; i++)
    {
        p[i].fraction = 0;
        p[i].selectedWeight = 0;
        p[i].selectedValue = 0;
    }

    printf("\n==================================================\n");
    printf("           GREEDY SELECTION PROCESS\n");
    printf("==================================================\n\n");
    printf("Initial Vehicle Capacity: %.2f\n", capacity);

    for (i = 0; i < n; i++)
    {
        // stop when the vehicle is full
        if (remaining <= EPS)
            break;

        printf("\nPackage %d\n", p[i].id);
        printf("Value  : %.2f\n", p[i].value);
        printf("Weight : %.2f\n", p[i].weight);
        printf("Ratio  : %.2f\n", p[i].ratio);

        if (p[i].weight <= remaining + EPS)
        {
            // full package fits
            p[i].fraction = 1.0;
            p[i].selectedWeight = p[i].weight;
            p[i].selectedValue = p[i].value;

            remaining = remaining - p[i].selectedWeight;
            if (remaining < 0)
                remaining = 0;

            printf("Selection : FULL\n");
        }
        else
        {
            // full package does not fit, so take only a fraction
            p[i].fraction = remaining / p[i].weight;
            p[i].selectedWeight = p[i].weight * p[i].fraction;
            p[i].selectedValue = p[i].value * p[i].fraction;

            remaining = 0;

            printf("Selection : %.2f%%\n", p[i].fraction * 100);
        }

        *totalWeight = *totalWeight + p[i].selectedWeight;
        *totalValue = *totalValue + p[i].selectedValue;

        printf("Selected Weight : %.2f\n", p[i].selectedWeight);
        printf("Selected Value  : %.2f\n", p[i].selectedValue);
        printf("Remaining Capacity : %.2f\n", remaining);
    }

    printf("\n==================================================\n");
    printf("                 FINAL RESULT\n");
    printf("==================================================\n\n");
    printf("Total Weight Used : %.2f\n", *totalWeight);
    printf("Maximum Value     : %.2f\n", *totalValue);
    printf("\n==================================================\n");
}

// Option 6 - show only the packages which were selected
void displaySelectedPackages(struct Package p[], int n, double totalWeight, double totalValue)
{
    int i;
    char percent[20];

    printf("\n===============================================================\n");
    printf("                  SELECTED PACKAGES\n");
    printf("===============================================================\n\n");
    printf("%-6s%-20s%-15s%s\n", "ID", "Original Weight", "Fraction", "Selected Weight");
    printf("%-6s%-20s%-15s%s\n", "", "Original Value", "", "Selected Value");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        if (p[i].fraction > 0)
        {
            sprintf(percent, "%.2f%%", p[i].fraction * 100);
            printf("%-6d%-20.2f%-15s%.2f\n", p[i].id, p[i].weight, percent, p[i].selectedWeight);
            printf("%-6s%-35.2f%.2f\n\n", "", p[i].value, p[i].selectedValue);
        }
    }

    printf("---------------------------------------------------------------\n");
    printf("\nTotal Weight Used : %.2f\n", totalWeight);
    printf("Maximum Value     : %.2f\n", totalValue);
    printf("\n===============================================================\n");
}

int main()
{
    struct Package packages[MAX_PACKAGES];
    int n = 0;
    double capacity = 0;
    double totalWeight = 0, totalValue = 0;
    int choice;

    // these flags tell us which steps are already done
    int entered = 0, ratioDone = 0, sortDone = 0, solved = 0;

    while (1)
    {
        displayMenu();
        choice = readInt();

        if (choice == 1)
        {
            enterPackageDetails(packages, &n, &capacity, &entered, &ratioDone, &sortDone, &solved);
        }
        else if (choice == 2)
        {
            if (entered == 0)
                printf("Please enter package details first.\n");
            else
                displayPackageDetails(packages, n, capacity, ratioDone);
        }
        else if (choice == 3)
        {
            if (entered == 0)
                printf("Please enter package details first.\n");
            else
            {
                calculateRatios(packages, n, 1);
                ratioDone = 1;
            }
        }
        else if (choice == 4)
        {
            if (entered == 0)
                printf("Please enter package details first.\n");
            else
            {
                // ratios are needed before sorting
                if (ratioDone == 0)
                {
                    calculateRatios(packages, n, 0);
                    ratioDone = 1;
                }
                sortPackages(packages, n, 1);
                sortDone = 1;
            }
        }
        else if (choice == 5)
        {
            if (entered == 0)
                printf("Please enter package details first.\n");
            else
            {
                // do the ratio and sorting steps automatically if the user skipped them
                if (ratioDone == 0)
                {
                    calculateRatios(packages, n, 0);
                    ratioDone = 1;
                }
                if (sortDone == 0)
                {
                    sortPackages(packages, n, 0);
                    sortDone = 1;
                }
                findMaximumValue(packages, n, capacity, &totalWeight, &totalValue);
                solved = 1;
            }
        }
        else if (choice == 6)
        {
            if (entered == 0)
                printf("Please enter package details first.\n");
            else if (solved == 0)
                printf("Please run \"Find Maximum Value\" first.\n");
            else
                displaySelectedPackages(packages, n, totalWeight, totalValue);
        }
        else if (choice == 7)
        {
            printf("Thank you for using Smart Delivery Planning!\n");
            break;
        }
        else
        {
            printf("Invalid choice! Please enter a number from 1 to 7.\n");
        }
    }

    return 0;
}
