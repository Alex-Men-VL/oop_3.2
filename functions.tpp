template<typename TP>
int getEndingCardsNumber(const int pCount, TP **persons) {
    time_t seconds = time(NULL);
    tm* time = localtime(&seconds);
    int totalYear = time->tm_year + 1900;
    int count = 0;

    for (int i = 0; i < pCount; i++) {
        if (persons[i]->getCardYear() == totalYear) {
            count++;
        }
    }
    return count;
}

template<typename TP>
bool isNamesakes(const int pCount, TP **persons) {
    for (int i= 0; i< pCount; i++) {
        for (int j = i + 1; j < pCount; j++) {
            bool isSameLastNames = persons[i]->isSameLastNames(persons[j]);
            bool isSameFirstNames = persons[i]->isSameFirstNames(persons[j]);
            if (isSameLastNames && !isSameFirstNames) {
                return true;
            }
        }
    }
    return false;
}
