/**
class Deque
Array-based double-ended queue (deque) Abstract Data Type.

This class implements a dynamic deque using the Pimpl (Pointer to Implementation) idiom.
Internally uses a circular array that doubles in capacity when full.

Key Features & Operations:
- Memory Management: Implements deep copying and RAII principles.
- Insertion: operator+= adds an element to the back. idetiGale() and idetiPriekyje() insert at either end.
- Deletion: operator-= removes the first element matching the given value. imtiIsGalo() and imtiIsPriekio() remove from either end.
- Editing: operator*= updates an element using encoded format indeksas*1000+reiksme.
- State Management: operator! clears all elements from the deque.
 - Search: operator[] searches for a value and returns its zero-based index, or -1 if not found.
- Comparisons: Fully supports logically aligned relational operators (==, !=, <, >, <=, >=).
- Output: toString() returns a formatted string with the deque's elements, size and capacity.

throws DequeError Custom exception thrown on removal from empty deque.
throws std::out_of_range when accessing an invalid index.
throws std::invalid_argument when searching or removing from an empty deque or value not found.
 */

#ifndef DEQUE_H
#define DEQUE_H

#include <stdexcept>
#include <string>

namespace DequeN{

    class DequeError : public std::runtime_error
    {
    public:
        explicit DequeError(const std::string& message);
    };

    class Deque
    {
    public:
        Deque();
        explicit Deque(int pradineTalpa);
        Deque(const Deque& kitas);
        ~Deque();
        Deque& operator=(const Deque& kitas);

        void idetiGale(int reiksme);
        void idetiPriekyje(int reiksme);
        int imtiIsGalo();
        int imtiIsPriekio();
        int priekis() const;
        int galas() const;
        void nustatyti(int indeksas, int reiksme);
        int dydis() const;
        bool tuscias() const;
        std::string toString() const;

        Deque& operator+=(int reiksme);
        Deque& operator-=(int reiksme);
        Deque& operator*=(int koduotasPoras);
        Deque& operator!();

        int operator[](int reiksme) const;

        bool operator==(const Deque& kitas) const;
        bool operator!=(const Deque& kitas) const;
        bool operator< (const Deque& kitas) const;
        bool operator> (const Deque& kitas) const;
        bool operator<=(const Deque& kitas) const;
        bool operator>=(const Deque& kitas) const;

    private:
        class DequeImpl;
        DequeImpl* impl;
    };

}

#endif