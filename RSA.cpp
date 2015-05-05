#include "RSA.h"


BigInteger::BigInteger()
{
	Sign = true;
}
BigInteger::~BigInteger()
{
	Value.clear();
}
BigInteger::BigInteger(const BigInteger& number){
	Value = number.Value;
	Sign = number.Sign;
}
BigInteger::BigInteger(int number){
	if (number == 0){
		Value.push_back(0);
		Sign = true;
	}
	else
	{
		if (number < 0)
		{
			Sign = false;
			number *= (-1);

		}
		else
		{
			Sign = true;
		}
		while (number != 0)
		{
			Value.push_back(number % 10);
			number /= 10;
		}
	}
}

BigInteger BigInteger::operator=(const BigInteger& number){
	if (this == &number)
		return *this; // разыминовываем указатель
	Value = number.Value;
	Sign = number.Sign;
	return *this;
}



#pragma region D A T A

int cmp(const data_type &a, const data_type &b) {
	if (a.size() != b.size())
		return a.size() - b.size();

	for (int i = a.size()-1, j = b.size()-1; i >= 0; i--, j--)
	{
		if (a[i] != b[j])
			return a[i] - b[j];
	}
	return 0;
}

bool operator < (const data_type &a, const data_type&b) {
	return cmp(a, b) < 0;
}

bool operator > (const data_type &a, const data_type &b) {
	return cmp(a, b) > 0;
}

bool operator == (const data_type &a, const data_type &b) {
	return cmp(a, b) == 0;
}

bool operator != (const data_type &a, const data_type &b) {
	return cmp(a, b) != 0;
}
bool operator <= (const data_type &a, const data_type &b) {
	return cmp(a, b) <= 0;
}

bool operator >= (const data_type &a, const data_type &b) {
	return cmp(a, b) >= 0;
}

data_type operator+(const data_type& left, const  data_type& right){
	data_type result;


	int left_size = left.size(),
		right_size = right.size();

	int i = 0;

	while (i < left_size || i < right_size)
	{
		result.push_back((i < left_size ? left[i] : 0) + (i < right_size ? right[i] : 0));
		i++;
	}


	for (i = 0; i + 1 != result.size(); i++) {
		result[i + 1] += result[i] / 10;
		result[i] %= 10;
	}


	//esli chto i+1

	if (result[i] >= 10) {
		result.push_back(result[i] / 10);
		result[i] %= 10;
	}
	return result;
}
data_type operator-(const data_type& left, const  data_type& right){
	data_type result;

	if (left < right) {
		throw 1;
	}

	if (left == right)
	{
		result.push_back(0);
		return result;
	}
	for (int i = 0;  i< left.size();i++)
	{
		result.push_back(left[i] - (i < right.size() ? right[i] : 0));
	}
	
	for ( int  i = 0;i + 1 < result.size(); i++) {
		result[i] += 10;
		result[i + 1]-=1;
		result[i + 1] += result[i] / 10 ;
		result[i] %= 10;
	}
  /// TODO могут быть ошибки
	data_type::iterator i = result.end() - 1;
	if (result.size() > 1)
		while (result.size() && *i == 0) 
		{
			i = result.erase(i) - 1;
		}

	return result;
}
data_type operator*(const data_type& left, const  data_type& right){
	data_type result;
	result.resize(left.size() + right.size() + 1, 0);
	int j = 0;
	for (int i = 0;	i != left.size(); i++) 
	{
		j = i;
		for ( int g = 0;	g != right.size(); g++, j++) 
		{
			result[j] += left[i] * right[g];
			result[j + 1] += result[j] / 10;
			result[j] %= 10;
		}
	}

	data_type::iterator i = result.end() - 1;
	while (result.size() > 1 && *i == 0) {
		i = result.erase(i) - 1;
	}

	return result;
}
data_type operator/(const data_type& left, const  data_type& right){
	data_type result;
	if (left < right)
	{
		result.push_back(0);
		return result;
	}
	if (!right.size())
		throw 1;

	data_type a = left, b = right;

	int x = 0;
	while (a >=b) 
	{
		b.insert(b.cbegin(), 0);
		x++;
	}

	b.erase(b.cbegin());

	data_type edinica;
	edinica.push_back(1);

	while (x--) {
		while (a >= b) {
			a = a - b;
			result = result + edinica;
		}
		result.insert(result.cbegin(),0);
		b.erase(b.cbegin());
	}

	result.erase(result.cbegin());
	if (result.size() == 0)
		result.push_back(0);
	return result;
}
data_type operator%(const data_type& left, const  data_type& right){

	if (left < right)
		return left;

	int x = 0;
	data_type a = left, b = right;
	while (a >= b) {
		b.insert(b.cbegin(), 0);
		x++;
	}

	b.erase(b.cbegin());

	while (x--) {
		while (a >= b) {
			a = a - b;
		}
		b.erase(b.cbegin());
	}
	return a;
}


#pragma endregion


bool operator==(const BigInteger& left, const BigInteger& right)
{
	if (left.Sign != right.Sign)
		return false;
	if (left.Value==right.Value)
	return true;
	else
	{
		return false;
	}

}
bool operator!=(const BigInteger& left, const BigInteger& right)
{
	return !(left == right);
}
bool operator<(const BigInteger& left, const BigInteger& right)
{
	if (left.Sign != right.Sign)
	{
		if (left.Sign == true)
			return false;
		else
			return true;
	}
	if (left.Sign == true) // тогда оба знака равны true
	{
		if (left.Value < right.Value)
			return true;
		else
			return false;
	}
	/// Если не будет работать, смотри сюда
	if (left.Sign == false) // тогда оба знака равны true
	{
		if (left.Value>right.Value)
			return true;
		else
			return false;
	}
}
bool operator>(const BigInteger& left, const BigInteger& right)
{
	return (right < left);
}

ostream& operator<<(ostream& out, const BigInteger& number)
{
	if (!number.Sign)
		out << "-";
	for (int i = number.Value.size() - 1; i >= 0; i--)
		out <<(int) number.Value[i];
	return out;
}


BigInteger operator+(const BigInteger& left, const BigInteger& right){
	BigInteger result;
	if (left.Sign != right.Sign)
	{
		if (left.Sign)
		{
			if (right.Value == left.Value)
			{
				return zero;
			}
			if (right.Value < left.Value)
			{
				result.Sign = true;
				result.Value = left.Value - right.Value;
				return result;
			}
			else
			{
				result.Sign = false;
				result.Value = right.Value - left.Value;
				return result;
			}
		}
		else
		{
			if (right.Value == left.Value)
			{
				return zero;
			}
			if (right.Value > left.Value)
			{
				result.Sign = true;
				result.Value = right.Value - left.Value;
				return result;
			}
			else
			{
				result.Sign = false;
				result.Value = left.Value - right.Value;
				return result;
			}
		}
	}
	else
	{
		if (!left.Sign)
		{
			result.Sign = false;
			result.Value = left.Value + right.Value;
			return result;
		}
		if (left.Sign)
		{
			result.Sign = true;
			result.Value = left.Value + right.Value;
			return result;
		}
	}
	
}
BigInteger operator-(const BigInteger& left, const BigInteger& right){
	BigInteger result;
	if (left.Sign == right.Sign)
	{
		if (left.Value == right.Value)
		{
			return zero;
		}
		if (left.Sign)
		{
			if (left.Value > right.Value)
			{
				result.Sign = true;
				result.Value = left.Value - right.Value;
				return result;
			}
			else
			{
				result.Sign = false;
				result.Value = right.Value - left.Value;
				return result;
			}
		}
		else
		{
			if (left.Value > right.Value)
			{
				result.Sign = false;
				result.Value = left.Value - right.Value;
				return result;
			}
			else
			{
				result.Sign = true;
				result.Value = right.Value - left.Value;
				return result;
			}
		}
	}
	else
	{
		if (left.Sign)
		{
			result.Sign = true;
			result.Value = left.Value + right.Value;
			return result;
		}
		else
		{
			result.Sign = false;
			result.Value = left.Value + right.Value;
			return result;
		}
	}
}
BigInteger operator*(const BigInteger& left, const BigInteger& right)
{
	BigInteger result;

	if (left.Sign != right.Sign)
		result.Sign = false;

	result.Value = left.Value * right.Value;
	return result;
}
BigInteger operator/(const BigInteger& left, const BigInteger& right){
	BigInteger result;

	if (left.Sign != right.Sign)
		result.Sign = false;

	result.Value = left.Value / right.Value;
	return result;
}
BigInteger operator%(const BigInteger& left, const BigInteger& right){
	BigInteger result;
	result.Value = left.Value % right.Value;
	return result;
}

// (a*b) % mod
BigInteger modul_mult(BigInteger &a, BigInteger &b, BigInteger &modul){
	if (b == zero)
		return one;
	if (b == one)
		return a;
	BigInteger trans, supp;
	trans = b % two;
	if (trans == zero)
	{
		supp = b / two;
		trans = modul_mult(a, supp, modul);
		supp = trans*two;
		supp = supp%modul;
		return supp;
	}
	supp = b - one;
	trans = modul_mult(a, supp, modul);
	supp = trans + a;
	supp = supp%modul;
	return supp;
}
//(a^b) % mod
BigInteger fast_power(BigInteger &num, BigInteger &power, BigInteger &modulus){
	if (power == zero)
		return one;
	if (power == one)
		return num;


	BigInteger trans, supp;
	trans = power % two;
	if (trans == zero)
	{
		supp = power / two;
		trans = fast_power(num, supp, modulus);
		supp = modul_mult(trans, trans, modulus);
		supp = supp%modulus;
		return supp;
	}
	supp = power - one;
	trans = fast_power(num, supp, modulus);
	supp = modul_mult(trans, num, modulus);
	supp = supp%modulus;
	return supp;
}
RSA::RSA()
{

	BigInteger p, q, fi;
	PrimeGenerator(p);
	PrimeGenerator(q);
	n = p*q;
	fi = (p - one)*(q - one); // Функция Эйлера
	e = (BigInteger)65537; 
	d = euclid(e, fi);

}
RSA::~RSA()
{

}
BigInteger RSA::euclid(const BigInteger& exp, const BigInteger& mod)
{
	BigInteger a(exp), b(mod);
	BigInteger x1(zero), x2(one), y1(one), y2(zero);
	BigInteger q, r, x, y;

	while (b != zero){

		q = a / b;
		r = a - q*b;
		x = x2 - q*x1;
		y = y2 - q*y1;
		a = b;
		b = r;
		x2 = x1;
		x1 = x;
		y2 = y1;
		y1 = y;

	}
	
	if (x2 < zero)
		x2 = x2 + mod;
	return x2;

}
// Рандомит любые числа
void RSA::Randomiser(BigInteger &num, int Digits){ // Digits - разряды
	num = one;
	int new_rand;
	for (int i = 0; i < Digits; i++){
		new_rand = rand() % 9 + 1;
		num = num + num + num*new_rand;
	}

	num = num + num;
	num = num + one;
}
// Рандомит число меньшее срандомленных ранее для текста рабина-миллера
void RSA::RangeRandomiser(BigInteger &num, const BigInteger &top){

	int Digit = (rand() % (LENGTH-1)) + 1;
	Randomiser(num, Digit);
}
// Тест Рабина-Миллера
bool RSA::IsPrime(BigInteger &num){

	BigInteger num_minus_one; // Она нужна, хранит именно num - one
	num_minus_one = num - one;

	BigInteger temp, trans, random, mod, supp;
	trans = num_minus_one;
	temp = num_minus_one%two;

	while (temp == zero)
	{
		trans = trans / two;
		temp = trans%two;
	}

	for (int i = 0; i < PROBABILITY; i++)
	{
		temp = trans;
		RangeRandomiser(random, num_minus_one);

		mod = fast_power(random, temp, num);

		while (temp != num_minus_one && mod != one && mod != num_minus_one)
		{
			mod = modul_mult(mod, mod, num);
			temp = temp*two;
		}
		supp = temp%two;
		if (mod != num_minus_one && supp == zero)
		{
			return false;
		}

	}
	return true;
}

// Рандомит числа нужно длинны, потом проверяет, является ли число простым
void RSA::PrimeGenerator(BigInteger &num){
	bool supp = false;
	while (!supp){
		Randomiser(num, LENGTH); // length - константа (размер p и q) у нас будет 155 (пока что 16)
		supp = IsPrime(num);
	}
}

void RSA::encryption(BigInteger & incoming_message, BigInteger& encrypted_messgae){
	encrypted_messgae = fast_power(incoming_message, e, n);
}

void RSA::decryption(BigInteger& out_message, BigInteger& encrypted_message){
	out_message = fast_power(encrypted_message, d, n);
}

void RSA::publish_keys(BigInteger& a, BigInteger& b){
	a = e;
	b = n;
}


