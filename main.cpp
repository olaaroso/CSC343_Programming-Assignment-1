#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <random>

using namespace std;

struct Process {
    int id;
    int startingAddress;
    int sizeMB;
    int unusedMB;
};

void userMemoryAllocation() {
    const int TOTAL_PAGES = 100;
    const int PAGE_SIZE_MB = 160;
    const int UNIT_SIZE_MB = 80;
    int memoryArray[TOTAL_PAGES] = {0}; // Initialize 100 pages to 0 (empty)
    
    vector<Process> report;
    int currentPageIndex = 0;
    int currentAddress = 2000;
    int processId = 1;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 30);

    while (currentPageIndex < TOTAL_PAGES) {
        int numUnits = dis(gen);
        int processSizeMB = numUnits * UNIT_SIZE_MB;
        
        int pagesNeeded = ceil((double)processSizeMB / PAGE_SIZE_MB);

        if (currentPageIndex + pagesNeeded > TOTAL_PAGES) {
            cout << "Memory Full! Cannot fit Process " << processId << endl;
            break;
        }

        for (int i = 0; i < pagesNeeded; i++) {
            memoryArray[currentPageIndex + i] = processId;
        }

        int allocatedSpace = pagesNeeded * PAGE_SIZE_MB;
        int unusedSpace = allocatedSpace - processSizeMB;

        report.push_back({processId, currentAddress, processSizeMB, unusedSpace});

        currentAddress += allocatedSpace;
        currentPageIndex += pagesNeeded;
        processId++;
    }

    cout << "\nSummary Report Format:\n";
    cout << left << setw(12) << "Process Id" 
         << setw(25) << "Starting Memory Address" 
         << setw(25) << "Size of the Process MB" 
         << setw(20) << "Unused Space MB" << endl;
    cout << string(80, '-') << endl;

    for (const auto& p : report) {
        cout << left << setw(12) << p.id 
             << setw(25) << p.address 
             << setw(25) << p.sizeMB 
             << setw(20) << p.unusedMB << endl;
    }
}

int main() {
    userMemoryAllocation();
    return 0;
}
