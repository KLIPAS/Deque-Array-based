#include "Deque.h"
#include <sstream>
#include <algorithm>

namespace DequeN
{

    class Deque::DequeImpl
    {
        int* masyvas;
        int  talpa;
        int  dydis;
        int  priekis;
        int  galas;

    public:
        DequeImpl(int pradineTalpa) : talpa(pradineTalpa), dydis(0), priekis(0), galas(-1)
        {
            if (pradineTalpa <= 0)
                throw std::invalid_argument("Talpa turi buti teigiama");
            masyvas = new int[talpa];
        }

        DequeImpl(const DequeImpl& kitas) : talpa(kitas.talpa), dydis(kitas.dydis),
                                             priekis(kitas.priekis), galas(kitas.galas)
        {
            masyvas = new int[talpa];
            for (int i = 0; i < talpa; i++)
                masyvas[i] = kitas.masyvas[i];
        }

        ~DequeImpl()
        {
            delete[] masyvas;
        }

        int indeksas(int loginis) const
        {
            return (priekis + loginis) % talpa;
        }

        void padidinti()
        {
            int naujaTalpa = talpa * 2;
            int* naujas = new int[naujaTalpa];
            for (int i = 0; i < dydis; i++)
                naujas[i] = masyvas[indeksas(i)];
            delete[] masyvas;
            masyvas = naujas;
            priekis = 0;
            galas   = dydis - 1;
            talpa   = naujaTalpa;
        }

        void idetiGale(int reiksme)
        {
            if (dydis == talpa) padidinti();
            galas = (galas + 1) % talpa;
            masyvas[galas] = reiksme;
            dydis++;
        }

        void idetiPriekyje(int reiksme)
        {
            if (dydis == talpa) padidinti();
            priekis = (priekis - 1 + talpa) % talpa;
            masyvas[priekis] = reiksme;
            dydis++;
        }

        int imtiIsGalo()
        {
            if (dydis == 0) throw DequeError("imtiIsGalo: dekas tuscias");
            int reiksme = masyvas[galas];
            galas = (galas - 1 + talpa) % talpa;
            dydis--;
            return reiksme;
        }

        int imtiIsPriekio()
        {
            if (dydis == 0) throw DequeError("imtiIsPriekio: dekas tuscias");
            int reiksme = masyvas[priekis];
            priekis = (priekis + 1) % talpa;
            dydis--;
            return reiksme;
        }

        int getPriekis() const
        {
            if (dydis == 0) throw DequeError("priekis: dekas tuscias");
            return masyvas[priekis];
        }

        int getGalas() const
        {
            if (dydis == 0) throw DequeError("galas: dekas tuscias");
            return masyvas[galas];
        }

        void nustatyti(int ind, int reiksme)
        {
            if (ind < 0 || ind >= dydis)
                throw std::out_of_range("nustatyti: indeksas uz ribu");
            masyvas[indeksas(ind)] = reiksme;
        }

       void pasalinti(int reiksme)
        {
            for (int i = 0; i < dydis; i++)
            {
                if (masyvas[indeksas(i)] == reiksme)
                {
                    for (int j = i; j < dydis - 1; j++)
                        masyvas[indeksas(j)] = masyvas[indeksas(j + 1)];
            
                    dydis--;
                    galas = indeksas(dydis - 1);
                    return;
            }
        }
    throw std::invalid_argument("operator-=: reiksme nerasta");
}
        int ieskoti(int reiksme) const
        {
            for (int i = 0; i < dydis; i++)
                if (masyvas[indeksas(i)] == reiksme) return i;
            return -1;
        }

        int compare(const DequeImpl& kitas) const
        {
            int min = std::min(dydis, kitas.dydis);
            for (int i = 0; i < min; i++)
            {
                if (masyvas[indeksas(i)] > kitas.masyvas[kitas.indeksas(i)]) return 1;
                if (masyvas[indeksas(i)] < kitas.masyvas[kitas.indeksas(i)]) return -1;
            }
            if (dydis > kitas.dydis) return 1;
            if (dydis < kitas.dydis) return -1;
            return 0;
        }

        bool isEqual(const DequeImpl& kitas) const
        {
            if (dydis != kitas.dydis) return false;
            for (int i = 0; i < dydis; i++)
                if (masyvas[indeksas(i)] != kitas.masyvas[kitas.indeksas(i)]) return false;
            return true;
        }

        void isvalyti()
        {
            dydis = 0; priekis = 0; galas = -1;
        }

        int getDydis() const { return dydis; }
        int getTalpa() const { return talpa; }
        bool getTuscias() const { return dydis == 0; }

        std::string toString() const
        {
            std::ostringstream oss;
            oss << "Dekas: [";
            for (int i = 0; i < dydis; i++)
            {
                oss << masyvas[indeksas(i)];
                if (i < dydis - 1) oss << ",";
            }
            oss << "] dydis: " << dydis << ", talpa: " << talpa;
            return oss.str();
        }

    DequeError::DequeError(const std::string& message) : std::runtime_error(message) {}

    Deque::Deque() : impl(new DequeImpl(8)) {}

    Deque::Deque(int pradineTalpa) : impl(new DequeImpl(pradineTalpa)) {}

    Deque::Deque(const Deque& kitas) : impl(new DequeImpl(*kitas.impl)) {}

    Deque::~Deque()
    {
        delete impl;
    }

    Deque& Deque::operator=(const Deque& kitas)
    {
        if (this != &kitas)
        {
            DequeImpl* newImpl = new DequeImpl(*kitas.impl);
            delete impl;
            impl = newImpl;
        }
        return *this;
    }

    void Deque::idetiGale(int reiksme) { impl->idetiGale(reiksme); }
    void Deque::idetiPriekyje(int reiksme) { impl->idetiPriekyje(reiksme); }
    int Deque::imtiIsGalo() { return impl->imtiIsGalo(); }
    int Deque::imtiIsPriekio() { return impl->imtiIsPriekio(); }
    int Deque::priekis() const { return impl->getPriekis(); }
    int Deque::galas() const { return impl->getGalas(); }
    void Deque::nustatyti(int indeksas, int reiksme) { impl->nustatyti(indeksas, reiksme); }
    int Deque::dydis() const { return impl->getDydis(); }
    int Deque::talpa() const { return impl->getTalpa(); }
    bool Deque::tuscias() const { return impl->getTuscias(); }
    std::string Deque::toString() const { return impl->toString(); }

    Deque& Deque::operator+=(int reiksme)
    {
        impl->idetiGale(reiksme);
        return *this;
    }

    Deque& Deque::operator-=(int reiksme)
    {
        impl->pasalinti(reiksme);
        return *this;
    }

    Deque& Deque::operator*=(int koduotaPora)
    {
        impl->nustatyti(koduotaPora / 1000, koduotaPora % 1000);
        return *this;
    }

    Deque& Deque::operator!()
    {
        impl->isvalyti();
        return *this;
    }

    int Deque::operator[](int reiksme) const
    {
        if (impl->getTuscias())
            throw std::invalid_argument("operator[]: dekas tuscias");
        return impl->ieskoti(reiksme);
    }

    bool Deque::operator==(const Deque& kitas) const { return impl->isEqual(*kitas.impl); }
    bool Deque::operator!=(const Deque& kitas) const { return !(*this == kitas); }
    bool Deque::operator< (const Deque& kitas) const { return impl->compare(*kitas.impl) == -1; }
    bool Deque::operator> (const Deque& kitas) const { return impl->compare(*kitas.impl) == 1; }
    bool Deque::operator<=(const Deque& kitas) const { return impl->compare(*kitas.impl) <= 0; }
    bool Deque::operator>=(const Deque& kitas) const { return impl->compare(*kitas.impl) >= 0; }

}
