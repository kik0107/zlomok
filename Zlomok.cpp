#include <iostream>
#include <random>
#include "Zlomok.h"

int Zlomok::getCit() const
{
    return cit;
}

void Zlomok::setCit(int other)
{
    //cit=other;
    this->cit=other;
}

int Zlomok::getMen() const
{
    return men;
}

void Zlomok::setMen(int other)
{
    men = other;
}

/*void Zlomok::nacitajZlomok()
{
    using std::cout;
    cout<<"Zadaj citatel:";
    std::cin>>cit;
    cout<<"Zadaj menovatel:";
    std::cin>>men;
}*/

Zlomok::Zlomok()
{
    std::cin>>*this;
    naZakladnyTvar();
}

Zlomok::Zlomok(int otherCit):cit(otherCit),men(1)
{
    //cit=otherCit;
    //men =1;
}

Zlomok::Zlomok(int otherCit, int otherMen):cit(otherCit),men(otherMen)
{
    naZakladnyTvar();
    //cit=otherCit;
    //men=otherMen;
}

/*void Zlomok::vytlacZlomok() const
{
    std::cout<<cit<<"/"<<men<<std::endl;
}

Zlomok Zlomok::plus(Zlomok other) const
{
    //return Zlomok(cit*other.men+other.cit*men,men*other.men);
    return {cit*other.men+other.cit*men,men*other.men};
}

Zlomok Zlomok::plus(const Zlomok &other) const
{
    return {cit*other.men+other.cit*men,men*other.men};
}

Zlomok Zlomok::minus(const Zlomok &other) const
{
    return {cit*other.men-other.cit*men,men*other.men};
}*/

Zlomok Zlomok::operator+(const Zlomok &other) const
{
    return {cit*other.men+other.cit*men,men*other.men};
}

Zlomok Zlomok::operator+(int other) const
{
    return (*this)+Zlomok(other);
}

Zlomok operator+(int cislo, const Zlomok &other)
{
    return other+cislo;
}

Zlomok Zlomok::operator-(const Zlomok &other) const
{
    return {cit*other.men-other.cit*men,men*other.men};
}

Zlomok operator-(int cislo, const Zlomok &other)
{
    return other-cislo;
}

Zlomok Zlomok::operator-(int other) const
{
    return Zlomok(other)-(*this);
}


Zlomok Zlomok::operator*(const Zlomok &other) const
{
    return {cit*other.cit,men*other.men};
}

Zlomok Zlomok::operator/(const Zlomok &other) const
{
    return {cit*other.men,men*other.cit};
}

bool Zlomok::operator<(const Zlomok &other) const
{
    return cit*other.men<other.cit*men;
}

bool Zlomok::operator==(const Zlomok &other) const
{
    return cit*other.men==other.cit*men;;
}

std::ostream &operator<<(std::ostream &os, const Zlomok &other)
{
    if(other.men==1)
    {
        os<<other.cit;
    }
    else
    {
        os<<other.cit<<"/"<<other.men;
    }
    return os;
}



const Zlomok &Zlomok::operator++()
{
    cit+=men;
    return (*this);
}

Zlomok Zlomok::operator++(int nevyuzity)
{
    auto tmp = (*this);
    cit+=men;
    return tmp;
}

std::istream &operator>>(std::istream &is, Zlomok &other)
{
//    std::cout<<"Zadaj citatel:";
//    is>>other.cit;
//    std::cout<<"Zadaj menovatel:";
//    is>>other.men;
    other.cit = Zlomok::getInt("Zadaj citatel:");
    other.men = Zlomok::getInt("Zadaj menovatel:", false);
    other.naZakladnyTvar();
    return is;
}

void Zlomok::naZakladnyTvar()
{
    int najmensi = Zlomok::NSD(abs(cit), abs(men));
    if (men < 0)
    {
        cit *= -1;
        men *= -1;
    }
    cit /= najmensi;
    men /= najmensi;
}

int Zlomok::NSD(int a, int b)
{
    int c;
    while (b != 0)
    {
        c = b;
        b = a % b;
        a = c;
    }
    return a;
}


int Zlomok::generujInt(int min, int max, bool nulaPovolena)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<int> distr(min, max); // define the range
    if(nulaPovolena)
    {
        return distr(eng); //generate number
    }
    int c;
    while((c=(distr(eng)==0)));
    return c;
}

Zlomok Zlomok::generujZlomok()
{
        return {generujInt(), generujInt( false)};
}

int Zlomok::getInt(const char * text,bool nulaPovolena, int min, int max)
{
    int cislo; //premenna do ktorej budeme nacitavat cislo a ktoru budeme vracat
    while(true)  //nekonecny cyklus
    {
        std::cout<<text;
        try   //blok kde budeme zachytavat vynimky
        {
            if(!(std::cin>>cislo))  //ak nastala chyba pri citani do premennej cislo typu int
            {
                throw Zlomok::ExNiejeCislo("Zadany vstup nie je platnym celym cislom!");  //vyhodim vynimku t.j. vytvorim objekt typu vynimky a poslem mu texttovu spravu
            }
            if(cislo< min || cislo>max) //ak cislo nepatri do urceneho intervalu
            {
                throw Zlomok::ExMimoInterval();  //vyhodim vynimku ExMimoInterval
            }
            if(cislo==0 && !nulaPovolena) //ak nebola povolena nula ale bola zadana
            {
                throw 0; //vyhodim vynimku ktorou je cele cislo, mohol by to byt aj retazec, float....
            }
        }
        catch(Zlomok::ExNiejeCislo &ex)
        {
            std::cin.clear(); //vymaze chybovy bit, ktory sa nasytavil pri citani s chybou
            std::cin.ignore(1000,'\n'); //vymaze buffer klavesnice
            std::cout<<ex.dajSpravu(); //vytlacime chybovu spravu pomocou objektu vynimky
            continue; //vratime sa na zaciatok while
        }
        catch(Zlomok::ExMimoInterval &ex)
        {
            std::cout<<ex.what(); //vypiseme chybovu spravu pomocou prepisanej metody what()
            continue;   //vratime sa na zaciatok while
        }
        catch(int cislo)
        {
            std::cout<<"Nula nie je povolena!";  //vypiseme priamo chybovu spravu
            continue;  //vratime sa na zaciatok while
        }
    return cislo;  //sem sa dostaneme len vtedy, ked ziadna vynimka nevznikne, hodnota je spravna a mozeme ju vratit
    }               //return prerusi nekonecny cyklus a sposobi navrat z funkcie
}

Zlomok *Zlomok::generujPoleZlomkov(int pocet)
{
    auto * pole = new Zlomok[pocet]; //alokuje na hromade pamat pre pocet objektov typu zlomok
    //Zlomok *pole= (Zlomok *)malloc(pocet*sizeof(Zlomok)) //toto je zapis v C
    return nullptr;
}




