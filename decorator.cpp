#include <iostream>
#include <string>
using namespace std;

// размеры чашек
enum class Size { S = 80, M = 180, L = 280, XXL = 500 };

class Drink abstract // базовый абстрактный напиток
{
protected:
    Size size;
    double price;
    string description;

public:
    Size getSize() const
    {
        return size;
    }

    double getPrice() const
    {
        return price;
    }

    string getDescription() const
    {
        return description;
    }

    void print() const
    {
        cout << description << " = " << price << " UAH\n";
    }
};

// чёрный чай - конкретный базовый напиток без добавок
class BlackTea : public Drink
{
public:
    BlackTea(Size size)
    {
        this->size = size;
        description = "black tea from teabag";

        if (size == Size::M) price = 27; // 180г
        else if (size == Size::L) price = 32; // 280г
        else throw "invalid cup size";
    }
};

// зелёный чай - конкретный базовый напиток без добавок
class GreenTea : public Drink
{
public:
    GreenTea()
    {
        // size = ...
        description = "green leaf tea";
        price = 45;
    }
};

// эспрессо - конкретный базовый напиток без добавок
class Espresso : public Drink
{
public:
    Espresso()
    {
        // size = ...
        description = "small portion of strong coffee";
        price = 29;
    }
};

////////////////////////////////////////////////////////////////

// базовая абстрактная добавка (надо было назвать Additive?)
class Condiment abstract : public Drink // добавка помечена как наследник напитка - это важно для реализации паттерна!
{
protected:
    Drink* drink; // указатель на оригинальный напиток
};

// молоко
class MilkCondiment : public Condiment
{
public:
    MilkCondiment(Drink* drink)
    {
        this->drink = drink; // базовый напиток, в который пойдёт добавка
        description = this->drink->getDescription() + " + Milk (3 UAH)";
        price = this->drink->getPrice() + 3;
    }

    MilkCondiment() // молоко может быть основой напитка
    {
        this->drink = this; // базовый напиток, в который пойдёт добавка
        description = "glass of milk";
        price = 10;
    }
};

class ChocolateCondiment : public Condiment
{
public:
    ChocolateCondiment(Drink* drink)
    {
        this->drink = drink;
        description = this->drink->getDescription() + " + Chocolate (5 UAH)";
        price = this->drink->getPrice() + 5;
    }
};

class SugarCondiment : public Condiment
{
public:
    SugarCondiment(Drink* drink)
    {
        this->drink = drink;
        description = this->drink->getDescription() + " + Sugar (1 UAH)";
        price = this->drink->getPrice() + 1;
    }
};

int main()
{
    Drink* espresso = new Espresso;
    Drink* blackTea = new BlackTea(Size::L);
    Drink* greenTea = new GreenTea;

    espresso->print();
    blackTea->print();
    greenTea->print();

    cout << "================================================\n";

    Drink* capuccino = new SugarCondiment(new MilkCondiment(new Espresso));
    capuccino->print();

    Drink* chocolateCapuccino = new ChocolateCondiment(capuccino);
    chocolateCapuccino->print();

    Drink* extraSweetBlackTea = new SugarCondiment(new SugarCondiment(new SugarCondiment(new BlackTea(Size::L))));
    extraSweetBlackTea->print();

    Drink* glassOfMilk = new MilkCondiment(new MilkCondiment(new MilkCondiment));
    glassOfMilk->print();
}