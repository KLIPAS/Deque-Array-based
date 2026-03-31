#include <iostream>
#include "Deque.h"

using namespace DequeN;

int main()
{
    std::cout << "--- Starting Deque Demonstration ---\n";

    Deque d1;
    d1.idetiGale(10);
    d1.idetiGale(20);
    d1.idetiGale(30);
    d1.idetiPriekyje(5);
    std::cout << "d1 after insertions: " << d1.toString() << "\n";

    d1 += 40;
    std::cout << "d1 after += 40: " << d1.toString() << "\n";

    int front = d1.imtiIsPriekio();
    int back  = d1.imtiIsGalo();
    std::cout << "imtiIsPriekio: " << front << "\n";
    std::cout << "imtiIsGalo: " << back << "\n";
    std::cout << "d1 after removal: " << d1.toString() << "\n";

    d1 -= 20;
    std::cout << "d1 after -= 20: " << d1.toString() << "\n";

    d1.nustatyti(0, 99);
    std::cout << "d1 after nustatyti(0, 99): " << d1.toString() << "\n";
    d1 *= 1042;
    std::cout << "d1 after *= 1042: " << d1.toString() << "\n";

    std::cout << "Position of value 99: " << d1[99] << "\n";
    std::cout << "Position of value 0 (not found): " << d1[0] << "\n";

    Deque d2 = d1;
    Deque d3;
    d3 = d1;
    d3 += 100;

    std::cout << "\nd2 (copy of d1): " << d2.toString() << "\n";
    std::cout << "d3 (assigned from d1, added 100): " << d3.toString() << "\n";

    std::cout << "\n--- Comparisons ---\n";
    std::cout << "d1 == d2: " << (d1 == d2 ? "true" : "false") << "\n";
    std::cout << "d1 != d3: " << (d1 != d3 ? "true" : "false") << "\n";
    std::cout << "d1 < d3: "  << (d1 < d3  ? "true" : "false") << "\n";
    std::cout << "d3 > d1: "  << (d3 > d1  ? "true" : "false") << "\n";
    std::cout << "d1 <= d2: " << (d1 <= d2 ? "true" : "false") << "\n";
    std::cout << "d3 >= d1: " << (d3 >= d1 ? "true" : "false") << "\n";

    std::cout << "\n--- Resize ---\n";
    Deque d4(2);
    for (int i = 1; i <= 6; i++) d4.idetiGale(i * 10);
    std::cout << "d4 after 6 insertions (initial capacity 2): " << d4.toString() << "\n";

    std::cout << "\n--- Exceptions ---\n";
    try
    {
        Deque tuscias;
        tuscias.imtiIsPriekio();
    }
    catch (const DequeError& e)
    {
        std::cout << "DequeError: " << e.what() << "\n";
    }

    try
    {
        d1.nustatyti(99, 5);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "out_of_range: " << e.what() << "\n";
    }

    try
    {
        d1 -= 999;
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "invalid_argument: " << e.what() << "\n";
    }

    !d1;
    std::cout << "\nd1 after ! (clear): " << d1.toString() << "\n";
    std::cout << "d1 tuscias(): " << (d1.tuscias() ? "true" : "false") << "\n";

    std::cout << "--- Demonstration Complete ---\n";
    return 0;
}
