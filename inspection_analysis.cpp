/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: [Jazer E. Ramos Muniz]
 * Lab: 12 - Search, Sorting and Statistics
 * Description: [inspection_analysis.cpp]
 * Due Date: [Nov 4, 2026]
 */

#include <iostream> // Provides console input and output
#include <iomanip> // Provides table and decimal formatting
#include <string> // Provides string and getline
using namespace std;

struct Inspection {
    int id = 0;
    string area;
    double vibration = 0.0;
    bool isEmpty = true;
};

int findInspectionById(const Inspection inspections[], int capacity, int targetId);
int displayInspectionsByArea(const Inspection inspections[], int capacity, string targetArea);
int copyVibrations(const Inspection inspections[], int capacity, double values[]);
void selectionSort(double values[], int count);
double calculateMean(const double values[], int count);
double calculateMedian(const double sortedValues[], int count);
void displayModes(const double sortedValues[], int count);
void displayInspection(Inspection inspection);

int main() {
    const int CAPACITY = 6;
    Inspection inspections[CAPACITY] = {
        {101, "Assembly", 0.30, false},
        {104, "Power", 0.15, false},
        {109, "Assembly", 0.30, false},
        {115, "Thermal", 0.45, false},
        {118, "Power", 0.10, false},
        {123, "Assembly", 0.15, false}
    };
    double sortedVibrations[CAPACITY] = {};
    int menuChoice = 0;

    cout << fixed << setprecision(2);
    do {
        cout << "\nInspection Analysis\n";
        cout << "1. Find inspection by ID\n";
        cout << "2. List inspections by area\n";
        cout << "3. Analyze vibration readings\n";
        cout << "4. Exit\n";
        cout << "Enter option number: ";
        if (!(cin >> menuChoice)) {
            return 0;
        }

        if (menuChoice == 1) {
            int targetId = 0;
            cout << "Enter inspection ID: ";
            if (!(cin >> targetId)) {
                return 0;
            }
            int foundIndex = findInspectionById(inspections, CAPACITY, targetId);
            if (foundIndex == -1) {
                cout << "Inspection not found." << endl;
            } else {
                displayInspection(inspections[foundIndex]);
            }
        } else if (menuChoice == 2) {
            string targetArea;
            cout << "Enter area: ";
            if (!getline(cin >> ws, targetArea)) {
                return 0;
            }
            int matchCount = displayInspectionsByArea(inspections, CAPACITY, targetArea);
            cout << "Matches: " << matchCount << endl;
        } else if (menuChoice == 3) {
            int valueCount = copyVibrations(inspections, CAPACITY, sortedVibrations);
            if (valueCount == 0) {
                cout << "No readings available for statistics." << endl;
            } else {
                selectionSort(sortedVibrations, valueCount);
                cout << "Values used: " << valueCount << endl;
                cout << "Mean: " << calculateMean(sortedVibrations, valueCount) << endl;
                cout << "Median: " << calculateMedian(sortedVibrations, valueCount) << endl;
                cout << "Mode: ";
                displayModes(sortedVibrations, valueCount);
            }
        } else if (menuChoice != 4) {
            cout << "Invalid option." << endl;
        }
    } while (menuChoice != 4);

    return 0;
}

void displayInspection(Inspection inspection) {
    cout << "ID: " << inspection.id
         << " | Area: " << inspection.area
         << " | Vibration: " << inspection.vibration << endl;
}

int findInspectionById(const Inspection inspections[], int capacity, int targetId) {
    for (int i = 0; i < capacity; i++) {
        if (!inspections[i].isEmpty && inspections[i].id == targetId) {
            return i;
        }
    }
    return -1;
}

int displayInspectionsByArea(const Inspection inspections[], int capacity, string targetArea) {
    int matchCount = 0;
    for (int i = 0; i < capacity; i++) {
        if (!inspections[i].isEmpty && inspections[i].area == targetArea) {
            displayInspection(inspections[i]);
            matchCount++;
        }
    }
    return matchCount;
}

int copyVibrations(const Inspection inspections[], int capacity, double values[]) {
    int valueCount = 0;
    for (int i = 0; i < capacity; i++) {
        if (!inspections[i].isEmpty) {
            values[valueCount] = inspections[i].vibration;
            valueCount++;
        }
    }
    return valueCount;
}

void selectionSort(double values[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (values[j] < values[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            double temp = values[i];
            values[i] = values[minIndex];
            values[minIndex] = temp;
        }
    }
}

double calculateMean(const double values[], int count) {
    double total = 0.0;
    for (int i = 0; i < count; i++) {
        total += values[i];
    }
    return count > 0 ? total / count : 0.0;
}

double calculateMedian(const double sortedValues[], int count) {
    if (count <= 0) {
        return 0.0;
    }
    if (count % 2 == 1) {
        return sortedValues[count / 2];
    }
    return (sortedValues[count / 2 - 1] * 100.0
        + sortedValues[count / 2] * 100.0) / 200.0;
}

void displayModes(const double sortedValues[], int count) {
    int maxFrequency = 0;
    for (int i = 0; i < count;) {
        int frequency = 1;
        while (i + frequency < count && sortedValues[i + frequency] == sortedValues[i]) {
            frequency++;
        }
        if (frequency > maxFrequency) {
            maxFrequency = frequency;
        }
        i += frequency;
    }

    if (maxFrequency < 2) {
        cout << "N/A" << endl;
        return;
    }

    bool firstMode = true;
    for (int i = 0; i < count;) {
        int frequency = 1;
        while (i + frequency < count && sortedValues[i + frequency] == sortedValues[i]) {
            frequency++;
        }
        if (frequency == maxFrequency) {
            if (!firstMode) {
                cout << ", ";
            }
            cout << sortedValues[i];
            firstMode = false;
        }
        i += frequency;
    }
    cout << endl;
}

/*
 * Test Cases:
 * 1. Inputs: 1, 109, 4
 *    Expected: ID: 109 | Area: Assembly | Vibration: 0.30
 *    Observed: ID: 109 | Area: Assembly | Vibration: 0.30
 *
 * 2. Inputs: 1, 999, 4
 *    Expected: Inspection not found.
 *    Observed: Inspection not found.
 *
 * 3. Inputs: 2, Assembly, 2, Optics, 4
 *    Expected: Assembly displays inspections 101, 109, and 123 (3 matches);
 *              Optics displays no inspections (0 matches).
 *    Observed: Assembly displayed inspections 101, 109, and 123 (3 matches);
 *              Optics displayed no inspections (0 matches).
 *
 * 4. Inputs: 3, 4
 *    Expected: 6 readings; mean 0.24; median 0.23; modes 0.15 and 0.30.
 *              Sorted copy: 0.10, 0.15, 0.15, 0.30, 0.30, 0.45.
 *    Observed: Values used: 6; mean 0.24; median 0.23; modes 0.15 and 0.30.
 *              The sorted copy is not printed by the program.
 */

 /*
 * Analysis:
 * 1. So the program can access the matching inspection.
 * 2. To find and display every match.
 * 3. Because empty inspections are skipped.
 * 4. To keep the original inspections unchanged.
 * 5. The third and fourth values: 0.15 and 0.30.
 */