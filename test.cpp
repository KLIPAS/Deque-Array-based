#include <iostream>
#include <fstream>
#include <string>
#include "Deque.h"

using namespace DequeN;

void runTest(bool condition, const std::string& testName, std::ofstream& log)
{
    std::string result = condition ? "PASSED" : "FAILED";
    std::string output = "Test [" + testName + "]: " + result + "\n";
    std::cout << output;
    log << output;
}

void logMessage(const std::string& msg, std::ofstream& log)
{
    std::cout << msg << "\n";
    log << msg << "\n";
}

int main()
{
    std::ofstream logFile("log.txt");
    if (!logFile)
    {
        std::cerr << "Error: Could not open log.txt\n";
        return 1;
    }

    logMessage("--- Starting Deque Diagnostic Tests ---", logFile);

    Deque d1;

    //Basic State & Insertion
    logMessage("\n[Phase 1: Basic Operations]", logFile);
    runTest(d1.tuscias() == true, "New deque is empty", logFile);
    d1.idetiGale(10);
    d1.idetiGale(20);
    d1.idetiGale(30);
    runTest(d1.tuscias() == false, "Deque not empty after insertions", logFile);
    runTest(d1.dydis() == 3, "Size is 3 after 3 insertions", logFile);
    d1.idetiPriekyje(5);
    runTest(d1.priekis() == 5, "Front is 5 after idetiPriekyje", logFile);
    runTest(d1.galas() == 30, "Back is 30 after idetiGale", logFile);

    //Search & Indexing (operator[])
    logMessage("\n[Phase 2: Search by Value]", logFile);
    runTest(d1[5] == 0, "Find value 5 at index 0", logFile);
    runTest(d1[30] == 3, "Find value 30 at index 3", logFile);
    runTest(d1[99] == -1, "Missing value returns -1", logFile);

    bool caughtNotFound = false;
    try
    {
        Deque tuscias;
        tuscias[5];
    }
    catch (const std::invalid_argument&)
    {
        caughtNotFound = true;
    }
    runTest(caughtNotFound, "Exception thrown for search on empty deque", logFile);

    //Dequeue & Removal
    logMessage("\n[Phase 3: Dequeue and Removal]", logFile);
    runTest(d1.imtiIsPriekio() == 5, "imtiIsPriekio returns front value (5)", logFile);
    runTest(d1.imtiIsGalo() == 30, "imtiIsGalo returns back value (30)", logFile);
    runTest(d1.dydis() == 2, "Size is 2 after two removals", logFile);
    d1 -= 10;
    runTest(d1[10] == -1, "Value 10 removed by operator-=", logFile);

    bool caughtRemove = false;
    try
    {
        d1 -= 999;
    }
    catch (const std::invalid_argument&)
    {
        caughtRemove = true;
    }
    runTest(caughtRemove, "Exception thrown for missing value in operator-=", logFile);

    //Update Operations
    logMessage("\n[Phase 4: Update Operations]", logFile);
    Deque d2;
    d2.idetiGale(10); d2.idetiGale(20); d2.idetiGale(30);
    d2.nustatyti(1, 99);
    runTest(d2[99] == 1, "nustatyti(1, 99) updates element correctly", logFile);
    d2 *= 0 * 1000 + 42;
    runTest(d2.priekis() == 42, "operator*= updates element at index", logFile);

    bool caughtRange = false;
    try
    {
        d2.nustatyti(10, 5);
    }
    catch (const std::out_of_range&)
    {
        caughtRange = true;
    }
    runTest(caughtRange, "nustatyti out of range throws exception", logFile);

    //Deep Copy & Comparisons
    logMessage("\n[Phase 5: Copying and Comparisons]", logFile);
    Deque d3;
    d3 += 1; d3 += 2; d3 += 3;
    Deque d4 = d3;
    runTest(d3 == d4, "Copied deque is equal (operator==)", logFile);
    d4 += 100;
    runTest(d3 != d4, "Modified copy is not equal (operator!=)", logFile);
    runTest(d3 < d4, "Original deque is less than modified copy (operator<)", logFile);
    runTest(d3 <= d4, "operator<= original vs modified", logFile);
    runTest(d4 > d3, "operator> modified vs original", logFile);
    runTest(d4 >= d3, "operator>= modified vs original", logFile);

    Deque d5(d3);
    d5 += 99;
    runTest(d3.dydis() == 3, "Deep copy does not affect original", logFile);
    d3 = d3;
    runTest(d3.dydis() == 3, "Self-assignment is safe", logFile);

    //Automatic Resize
    logMessage("\n[Phase 6: Automatic Resize]", logFile);
    Deque d6(2);
    for (int i = 1; i <= 10; i++) d6.idetiGale(i);
    runTest(d6.dydis() == 10, "Size is 10 after filling past initial capacity", logFile);
    runTest(d6.priekis() == 1, "Front is correct after resize", logFile);
    runTest(d6.galas() == 10, "Back is correct after resize", logFile);

    //Object Cleaning
    logMessage("\n[Phase 7: Object Cleaning]", logFile);
    !d4;
    runTest(d4.tuscias() == true, "Operator! successfully empties the deque", logFile);

    //Underflow Handling
    logMessage("\n[Phase 8: Underflow Handling]", logFile);
    bool caughtUnderflow = false;
    try
    {
        Deque tuscias;
        tuscias.imtiIsPriekio();
    }
    catch (const DequeError&)
    {
        caughtUnderflow = true;
    }
    runTest(caughtUnderflow, "Exception thrown on empty imtiIsPriekio", logFile);

    bool caughtUnderflow2 = false;
    try
    {
        Deque tuscias;
        tuscias.imtiIsGalo();
    }
    catch (const DequeError&)
    {
        caughtUnderflow2 = true;
    }
    runTest(caughtUnderflow2, "Exception thrown on empty imtiIsGalo", logFile);

    logMessage("\n--- Diagnostic Tests Complete ---", logFile);
    logFile.close();
    return 0;
}
