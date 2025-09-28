// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len <= 0)
        throw "error";
    
    BitLen = len;
    MemLen = (len + 31) / 32;
    pMem = new TELEM[MemLen];
    
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf)
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const
{
    if (n < 0 || n >= BitLen)
        throw "error";
    
    return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const
{
    if (n < 0 || n >= BitLen)
        throw "error";
    
    return 1 << (n % 32);
}

int TBitField::GetLength(void) const
{
    return BitLen;
}

void TBitField::SetBit(const int n)
{
    int i = GetMemIndex(n);
    TELEM m = GetMemMask(n);
    pMem[i] = pMem[i] | m;
}

void TBitField::ClrBit(const int n)
{
    int i = GetMemIndex(n);
    TELEM m = GetMemMask(n);
    pMem[i] = pMem[i] & ~m;
}

int TBitField::GetBit(const int n) const
{
    int i = GetMemIndex(n);
    TELEM m = GetMemMask(n);
    if ((pMem[i] & m) != 0)
        return 1;
    else
        return 0;
}

TBitField& TBitField::operator=(const TBitField &bf)
{
    if (this == &bf)
        return *this;
    
    delete[] pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    
    return *this;
}

int TBitField::operator==(const TBitField &bf) const
{
    if (BitLen != bf.BitLen)
        return 0;
    
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 0;
    
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf)
{
    int newLen;
    if (BitLen > bf.BitLen)
        newLen = BitLen;
    else
        newLen = bf.BitLen;
    
    TBitField result(newLen);
    
    for (int i = 0; i < MemLen; i++)
        result.pMem[i] = pMem[i];
    
    for (int i = 0; i < bf.MemLen; i++)
        result.pMem[i] = result.pMem[i] | bf.pMem[i];
    
    return result;
}

TBitField TBitField::operator&(const TBitField &bf)
{
    int newLen;
    if (BitLen > bf.BitLen)
        newLen = BitLen;
    else
        newLen = bf.BitLen;
    
    TBitField result(newLen);
    
    int smaller;
    if (MemLen < bf.MemLen)
        smaller = MemLen;
    else
        smaller = bf.MemLen;
    
    for (int i = 0; i < smaller; i++)
        result.pMem[i] = pMem[i] & bf.pMem[i];
    
    return result;
}

TBitField TBitField::operator~(void)
{
    TBitField result(BitLen);
    
    for (int i = 0; i < MemLen; i++)
        result.pMem[i] = ~pMem[i];
    
   
    int bitsLeft = BitLen % 32;
    if (bitsLeft != 0)
    {
        TELEM mask = (1 << bitsLeft) - 1;
        result.pMem[MemLen - 1] &= mask;
    }
    
    return result;
}

istream &operator>>(istream &istr, TBitField &bf)
{
    int x;
    for (int i = 0; i < bf.BitLen; i++)
    {
        istr >> x;
        if (x == 1)
            bf.SetBit(i);
        else if (x == 0)
            bf.ClrBit(i);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf)
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i);
    return ostr;
}
