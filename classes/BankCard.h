#ifndef OOP2_PERSON_H
#define OOP2_PERSON_H

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

    void setFirstName(const char*);
    void setLastName(const char*);
    void setCardNumber(const char*);
    void setCardDate(const char*);

    bool isLess(const BankCard<T>*) const;
    bool isSameLastNames(const BankCard<T>*) const;
    bool isSameFirstNames(const BankCard<T>*) const;
    int getCardYear() const;
};

#include "BankCard.tpp"

#endif //OOP2_PERSON_H
