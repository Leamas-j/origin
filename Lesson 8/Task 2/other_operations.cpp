#include "iostream"
#include <string>

class Fraction {
private:
	int numerator_;
	int denominator_;
public:
	Fraction(int numerator, int denomenator) {
		numerator_ = numerator;
		denominator_ = denomenator;
	}	
	Fraction operator +(Fraction f) {
		Fraction fr((numerator_ * f.denominator_) + (f.numerator_ * denominator_), denominator_ * f.denominator_);
		return fr.reduce();
	}
	Fraction operator -(Fraction f) {
		Fraction fr((numerator_ * f.denominator_) - (f.numerator_ * denominator_), denominator_ * f.denominator_);
		return fr.reduce();
	}
	Fraction operator *(Fraction f) {
		Fraction fr(numerator_ * f.numerator_, denominator_ * f.denominator_);
		return fr.reduce();
	}
	Fraction operator /(Fraction f) {
		Fraction fr(numerator_ * f.denominator_, denominator_ * f.numerator_);
		return fr.reduce();
	}
	Fraction operator -() {
		return Fraction(-numerator_, denominator_);
	}
	Fraction& operator ++() {
		*this = *this + Fraction(1,1);
		reduce();
		return *this;
	}
	Fraction operator ++(int) {
		Fraction tmp = *this;
		*this = *this + Fraction(1, 1);
		return tmp.reduce();
	}
	Fraction& operator --() {
		*this = *this - Fraction(1, 1);
		reduce();
		return *this;
	}
	Fraction operator --(int) {
		Fraction tmp = *this;
		*this = *this - Fraction(1, 1);
		return tmp.reduce();
	}
	Fraction reduce() {
		int a{ abs(numerator_) };
		int b{ abs(denominator_) };
		int c{};
		while (b) {
			c = a % b;
			a = b;
			b = c;
		}
		numerator_ /= a;
		denominator_ /= a;
		return *this;
	}
	friend std::ostream& operator <<(std::ostream& cout, Fraction fr);
};

std::ostream& operator <<(std::ostream& cout, Fraction fr) {
	return std::cout << fr.numerator_ << "/" << fr.denominator_;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RU");

	int num{}, den{};

	std::cout << "Введите числитель дроби 1: ";	
	std::cin >> num;
	do {
		std::cout << "Введите знаменатель дроби 1: ";		
		std::cin >> den;
		if(!den) std::cout << "Знаменатель не может быть 0!\n";		
	} while (!den);
	Fraction fr1(num, den);

	std::cout << "Введите числитель дроби 2: ";
	std::cin >> num;
	do {
		std::cout << "Введите знаменатель дроби 2: ";
		std::cin >> den;
		if (!den) std::cout << "Знаменатель не может быть 0!\n";
	} while (!den);	
	Fraction fr2(num, den);

	std::cout << fr1 << " + " << fr2 << " = " << (fr1 + fr2) << std::endl;
	std::cout << fr1 << " - " << fr2 << " = " << (fr1 - fr2) << std::endl;
	std::cout << fr1 << " * " << fr2 << " = " << (fr1 * fr2) << std::endl;
	std::cout << fr1 << " / " << fr2 << " = " << (fr1 / fr2) << std::endl;
	
	std::cout << "++" << fr1 << " * " << fr2;
	std::cout << " = " << (++fr1 * fr2) << std::endl;
	std::cout << "Значение дроби 1 = " << fr1 << std::endl;

	std::cout << fr1 << "--" << " * " << fr2;
	std::cout << " = " << (fr1-- * fr2) << std::endl;
	std::cout << "Значение дроби 1 = " << fr1 << std::endl;
	return 0;
}

