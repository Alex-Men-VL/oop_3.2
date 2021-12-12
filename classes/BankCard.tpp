#include "BankCard.h"

template<class T>
BankCard<T>::BankCard() :
    T(),
    m_firstName(T("")),
    m_lastName(T("")),
    m_cardNumber(T("")),
    m_cardDate(T("")){
}

template<class T>
void *BankCard<T>::operator new(size_t size) {
    void * ptr;
    ptr = malloc(size);  // allocating memory

    if (!ptr) {
        std::bad_alloc ba;  // memory allocation error
        throw ba;
    } else {
        return ptr;
    }
}

template<class T>
void BankCard<T>::operator delete(void *ptr) {
    free(ptr);
}

template<class T>
T BankCard<T>::getFirstName() const {
    return this->m_firstName;
}

template<class T>
T BankCard<T>::getLastName() const {
    return this->m_lastName;
}

template<class T>
T BankCard<T>::getCardNumber() const {
    return this->m_cardNumber;
}

template<class T>
T BankCard<T>::getCardDate() const {
    return this->m_cardDate;
}

template<class T>
int BankCard<T>::getFirstNameLen() const {
    return m_firstName.length();
}

template<class T>
int BankCard<T>::getLastNameLen() const {
    return m_lastName.length();
}

template<class T>
int BankCard<T>::getCardNumberLen() const {
    return m_cardNumber.length();
}

template<class T>
int BankCard<T>::getCardDateLen() const {
    return m_cardDate.length();
}

template<class T>
void BankCard<T>::setFirstName(const char* firstName) {
    T tmp(firstName);
    m_firstName = tmp;
}

template<class T>
void BankCard<T>::setLastName(const char* lastName) {
    T tmp(lastName);
    m_lastName = tmp;
}

template<class T>
void BankCard<T>::setCardNumber(const char* cardNumber) {
    T tmp(cardNumber);
    m_cardNumber = tmp;
}

template<class T>
void BankCard<T>::setCardDate(const char* cardDate) {
    T tmp(cardDate);
    m_cardDate = tmp;
}

template<class T>
bool BankCard<T>::isLess(const BankCard *otherPerson) const {

    if (this->m_lastName < otherPerson->m_lastName) {
        return true;
    } else if (this->m_lastName > otherPerson->m_lastName) {
        return false;
    }

    if (this->m_firstName < otherPerson->m_firstName) {
        return true;
    } else if (this->m_firstName > otherPerson->m_firstName) {
        return false;
    }

    if (this->m_cardNumber < otherPerson->m_cardNumber) {
        return true;
    } else if (this->m_cardNumber > otherPerson->m_cardNumber) {
        return false;
    }

    if (this->m_cardDate < otherPerson->m_cardDate) {
        return true;
    } else if (this->m_cardDate > otherPerson->m_cardDate) {
        return false;
    }
    return false;
}

template<class T>
bool BankCard<T>::isSameLastNames(const BankCard<T> *otherPerson) const {
    return this->m_lastName == otherPerson->m_lastName;
}

template<class T>
bool BankCard<T>::isSameFirstNames(const BankCard<T> *otherPerson) const {
    return this->m_firstName == otherPerson->m_firstName;
}

template<class T>
int BankCard<T>::getCardYear() const {
    T cardDate;
    cardDate = this->m_cardDate;
    int year = 0;
    year += cardDate[3] - '0';
    year *= 10;
    year += cardDate[4] - '0';
    year += 2000;
    return year;
}
