#ifndef OOP_3_2_BANKCARD_H
#define OOP_3_2_BANKCARD_H

#include "String.h"

template <class T>
class BankCard : public T {
    T m_firstName;
    T m_lastName;
    T m_cardNumber;
    T m_cardDate;
public:
    BankCard();

    void operator delete(void *);
    void* operator new(size_t size);

    T getFirstName() const;
    T getLastName() const;
    T getCardNumber() const;
    T getCardDate() const;

    int getFirstNameLen() const;
    int getLastNameLen() const;
    int getCardNumberLen() const;
    int getCardDateLen() const;

    void setCardOwner(T&, T&, T&, T&);

    bool isLess(const BankCard<T>*) const;
    bool isSameLastNames(const BankCard<T>*) const;
    bool isSameFirstNames(const BankCard<T>*) const;
    int getCardYear() const;
};

#include "BankCard.tpp"

#endif //OOP_3_2_BANKCARD_H
