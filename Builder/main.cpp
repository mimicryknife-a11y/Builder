#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Burger
{
private:
	string bun;
	string patty;
	string cheese;
	string veggies;
	string sauce;
	string drink;
public:
	void setBun(const string& bun) { this->bun = bun; }
	void setPatty(const string& patty) { this->patty = patty; }
	void setCheese(const string& cheese) { this->cheese = cheese; }
	void setVeggies(const string& veggies) { this->veggies = veggies; }
	void setSauce(const string& sauce) { this->sauce = sauce; }
	void setDrink(const string& drink) { this->drink = drink; }
	
	void showOrder() const {
		cout << "Состав бургера:" << endl
			<< "- Булочка: " << (bun.length() == 0 ? "Отсутствует" : bun) << endl
			<< "- Катлета: " << (patty.length() == 0 ? "Отсутствует" : patty) << endl
			<< "- Сыр: " << (cheese.length() == 0 ? "Отсутствует" : cheese) << endl
			<< "- Овощи: " << (veggies.length() == 0 ? "Отсутствует" : veggies) << endl
			<< "- Соус: " << (sauce.length() == 0 ? "Отсутствует" : sauce) << endl
			<< "- Напиток: " << (drink.length() == 0 ? "Отсутствует" : drink) << endl;
	}
};

class BurgerBuilder
{
protected:
	Burger* burger;
public:
	virtual ~BurgerBuilder() {};
	void createNewBurger() { burger = new Burger(); }

	Burger* getBurger() { return burger; }
	virtual void buildBun() = 0;
	virtual void buildPatty() = 0;
	virtual void buildCheese() = 0;
	virtual void buildVeggies() = 0;
	virtual void buildSauce() = 0;
	virtual void buildDrink() = 0;
};

class ClassicBurgerBuilder : public BurgerBuilder
{
public:
	void buildBun() override { burger->setBun("Классическая булка с кунжутом"); }
	void buildPatty() override { burger->setPatty("Говяжья котлета"); }
	void buildCheese() override { burger->setCheese("Чеддер"); }
	void buildVeggies() override { burger->setVeggies("Салат, помидор, огурцы"); }
	void buildSauce() override { burger->setSauce("Кетчуп и майонез"); }
	void buildDrink() override { burger->setDrink("Кола"); }
};

class VeganBurgerBuilder : public BurgerBuilder
{
public:
	void buildBun() override { burger->setBun("Цельнозерновая булка"); }
	void buildPatty() override { burger->setPatty("Колета из сои"); }
	void buildCheese() override { burger->setCheese("Веганский сыр"); }
	void buildVeggies() override { burger->setVeggies("Авокадо, шпинат, грибы"); }
	void buildSauce() override { burger->setSauce("Веганский майонез и горчица"); }
	void buildDrink() override { burger->setDrink("Зелёный чай"); }
};

class SpicyBurgerBuilder : public BurgerBuilder
{
public:
	void buildBun() override { burger->setBun("Острая булка с перцем"); }
	void buildPatty() override { burger->setPatty("Куриная котлета с чили"); }
	void buildCheese() override { burger->setCheese("Пеппер джек"); }
	void buildVeggies() override { burger->setVeggies("Халапеньо, лук, салат"); }
	void buildSauce() override { burger->setSauce("Острый соус"); }
	void buildDrink() override { burger->setDrink("Острый лимонад"); }
};

class DirectorCashier
{
private:
	BurgerBuilder* builder;
public:
	void setBuilder(BurgerBuilder* builder) { this->builder = builder; }
	Burger* assemble(bool extraVeggies = false)
	{ 
		builder->createNewBurger();
		builder->buildBun();
		builder->buildPatty();
		builder->buildCheese();
		//builder->buildVeggies(); ну это для примера так
		if (extraVeggies)
		{
			builder->buildVeggies();
		}
		builder->buildSauce();
		builder->buildDrink();
		return builder->getBurger();
	}
};

int main() {
	setlocale(0, "ru");

	DirectorCashier cashier;

	ClassicBurgerBuilder classicBurger;
	cashier.setBuilder(&classicBurger);
	Burger* classicBuilder = cashier.assemble();
	classicBuilder->showOrder();

	VeganBurgerBuilder veganBurger;
	cashier.setBuilder(&veganBurger);
	Burger* veganBuilder = cashier.assemble();
	veganBuilder->showOrder();

	delete classicBuilder, veganBuilder;
}