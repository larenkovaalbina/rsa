#pragma once
#include<vector>
#include<iostream>

using namespace std;

typedef vector<unsigned char>  data_type;

class BigInteger
{
public:
	BigInteger();
	~BigInteger();
	BigInteger(const BigInteger&);
	BigInteger(int);
	BigInteger operator=(const BigInteger&);


	friend ostream& operator<<(ostream&, const BigInteger&);

	friend bool operator==(const BigInteger&, const BigInteger&);
	friend bool operator!=(const BigInteger&, const BigInteger&);
	friend bool operator>(const BigInteger&, const BigInteger&);
	friend bool operator<(const BigInteger&, const BigInteger&);

	friend BigInteger operator+(const BigInteger&, const BigInteger&);
	friend BigInteger operator-(const BigInteger&, const BigInteger&);
	friend BigInteger operator*(const BigInteger&, const BigInteger&);
	friend BigInteger operator/(const BigInteger&, const BigInteger&);
	friend BigInteger operator%(const BigInteger&, const BigInteger&);
	friend BigInteger modul_mult(BigInteger&, BigInteger&, BigInteger&);
	friend BigInteger fast_power(BigInteger&, BigInteger&, BigInteger&);
private:

	data_type Value;
	bool Sign;
};

const BigInteger zero(0);
const BigInteger one(1);
const BigInteger two(2);
const int LENGTH(6);
const int PROBABILITY(5); // ������������

class RSA : public BigInteger
{
public:
	RSA();
	~RSA();
	void encryption(BigInteger&, BigInteger&);
	void decryption(BigInteger&, BigInteger&);
	void publish_keys(BigInteger&, BigInteger&);
private:

	BigInteger euclid(const BigInteger&, const BigInteger&);
	void Randomiser(BigInteger &, int);
	void RangeRandomiser(BigInteger &, const BigInteger &);
	bool IsPrime(BigInteger &);
	void PrimeGenerator(BigInteger &);
	BigInteger e; // �������� ����������
	BigInteger d; // ��������� ����������
	BigInteger n; // p*q, ��� p � q ������� ����� (BigInteger)

};

