/**
class Deque
Masyvo pagrįsta dvigubai sulankyti eiga (deque) Abstrakti Duomenų Struktūra.
Ši klasė realizuoja dinaminę deque naudodama Pimpl (Rodiklį į Realizaciją) idiomą.
Viduje naudoja žiedinį masyvą, kuris dvigubina talpą, kai pasipildo.
Pagrindinės Savybės & Operacijos:
- Atminties Valdymas: Realizuoja gilų kopijimą ir RAII principus.
- Įdėjimas: operator+= prideda elementą į pabaigą. idetiGale() ir idetiPriekyje() įdeda į bet kurą galą.
- Šalinimas: operator-= šalina pirmąjį elementą, kurio reikšmė sutampa. imtiIsGalo() ir imtiIsPriekio() šalina iš abiejų galų.
- Redagavimas: operator*= atnaujina elementą naudodama koduotą formatą indeksas*1000+reiksme.
- Būsenos Valdymas: operator! išvalo visus elementus iš deque.
- Paieška: operator[] ieško reikšmės ir grąžina jos nulinės pakopos indeksą arba -1, jei nerasta.
- Palyginimas: Pilnai palaiko logiškai suderintuosius reliacinius operatorius (==, !=, <, >, <=, >=).
- Išvestis: toString() grąžina suformatavę eilutę su deque elementais, dydžiu ir talpa.

throws DequeError Pasirinktinė išimtis, iškelta šalinant iš tuščios deque.

throws std::out_of_range pasiekus negaliojantį indeksą.

throws std::invalid_argument ieškant ar šalinant iš tuščios deque arba jei reikšmė nerasta.
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
        int talpa() const;
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
