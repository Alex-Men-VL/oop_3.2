#ifndef IND_7_STRING_H
#define IND_7_STRING_H

#include <iostream>

class String {
public:
    String();
    explicit String(char);
    explicit String(const char*);

    String(const String&);
    String(String &&) noexcept;

    ~String();

    String& operator=(const String&);
    String& operator=(String&&) noexcept ;

    String operator+(const String&);
    void operator+=(const String&);

    friend bool operator==(const String&, const String&);
    friend bool operator!=(const String&, const String&);
    friend bool operator>(const String&, const String&);
    friend bool operator>=(const String&, const String&);
    friend bool operator<(const String&, const String&);
    friend bool operator<=(const String&, const String&);

    char& operator[](int);

    friend std::ostream& operator<<(std::ostream&, const String&);

    char* getStr() const;
    size_t length() const;
private:
    char *m_str;
};

#endif //IND_7_STRING_H
