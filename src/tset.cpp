
// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower=s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower=bf.GetLength();
}

TSet::operator TBitField()
{
	TBitField bf(this->BitField);
  return bf;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField=s.BitField;
	MaxPower=s.GetMaxPower();
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	int res = 1;
	if (MaxPower!=s.MaxPower)
		res=0;
	else 
		res=(BitField==s.BitField);
	return res;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
 	int res=1;
	if (MaxPower!=s.MaxPower)
		return res;
	else 
		res=(BitField!=s.BitField);	
	return res;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet set2(BitField | s.BitField);
  return set2;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TBitField s(MaxPower);
	s.SetBit(Elem);
	TSet set2(BitField | s);
  return set2;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TBitField s(MaxPower);
	s.SetBit(Elem);
	TSet set2(BitField & s);
  return set2;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet set2(BitField & s.BitField);
  return set2;
}

TSet TSet::operator~(void) // дополнение
{
	TSet set2(~BitField);
  return set2;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int t;
	char c;
	do
	{
	 istr>>c;
	}
	while (c!='{');
	do 
	{
		istr>>t;
		s.InsElem(t);
			do
				{
				 istr>>c;
				}
				while ((c!=',')&&(c!='}'));
	}
	while (c!='}');
	
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << '{';
	for (int i = 0; i < s.GetMaxPower(); i++)
	{
		if (s.IsMember(i) == 1)
		{
			ostr << ' ' << i << ',';
		}
	}
	ostr << '}';
	return ostr;
}