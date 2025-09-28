// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp)
{
    if (mp <= 0)
        throw "error";
    MaxPower = mp;
    BitField = TBitField(mp);
}

TSet::TSet(const TSet &s)
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}

TSet::TSet(const TBitField &bf)
{
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "error";
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem)
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "error";
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem)
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "error";
    BitField.ClrBit(Elem);
}

TSet& TSet::operator=(const TSet &s)
{
    if (this == &s)
        return *this;
    
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    
    return *this;
}

int TSet::operator==(const TSet &s) const
{
    if (MaxPower != s.MaxPower)
        return 0;
    
    for (int i = 0; i < MaxPower; i++)
    {
        if (IsMember(i) != s.IsMember(i))
            return 0;
    }
    
    return 1;
}

int TSet::operator!=(const TSet &s) const
{
    if (*this == s)
        return 0;
    else
        return 1;
}

TSet TSet::operator+(const TSet &s)
{
    int newSize;
    if (MaxPower > s.MaxPower)
        newSize = MaxPower;
    else
        newSize = s.MaxPower;
    
    TSet result(newSize);
    
    for (int i = 0; i < MaxPower; i++)
    {
        if (IsMember(i))
            result.InsElem(i);
    }
    
    for (int i = 0; i < s.MaxPower; i++)
    {
        if (s.IsMember(i))
            result.InsElem(i);
    }
    
    return result;
}

TSet TSet::operator+(const int Elem)
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "error";
    
    TSet result(*this);
    result.InsElem(Elem);
    return result;
}

TSet TSet::operator-(const int Elem)
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "error";
    
    TSet result(*this);
    result.DelElem(Elem);
    return result;
}

TSet TSet::operator*(const TSet &s)
{
    int newSize;
    if (MaxPower > s.MaxPower)
        newSize = MaxPower;
    else
        newSize = s.MaxPower;
    
    TSet result(newSize);
    
    int minSize;
    if (MaxPower < s.MaxPower)
        minSize = MaxPower;
    else
        minSize = s.MaxPower;
    
    for (int i = 0; i < minSize; i++)
    {
        if (IsMember(i) && s.IsMember(i))
            result.InsElem(i);
    }
    
    return result;
}

TSet TSet::operator~(void)
{
    TSet result(MaxPower);
    
    for (int i = 0; i < MaxPower; i++)
    {
        if (!IsMember(i))
            result.InsElem(i);
    }
    
    return result;
}

istream &operator>>(istream &istr, TSet &s)
{
    int num;
    for (int i = 0; i < s.GetMaxPower(); i++)
    {
        istr >> num;
        if (num == 1)
            s.InsElem(i);
        else
            s.DelElem(i);
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s)
{
    ostr << "{";
    int count = 0;
    
    for (int i = 0; i < s.GetMaxPower(); i++)
    {
        if (s.IsMember(i))
        {
            if (count > 0)
                ostr << ", ";
            ostr << i;
            count++;
        }
    }
    
    ostr << "}";
    return ostr;
}
