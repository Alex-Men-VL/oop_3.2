template <class TP>
void sortPersons(const int pCount, TP** persons) {
    TP* tmp;
    for (int i = 1; i < pCount; i++) {
        for (int j = i; j > 0 && persons[j]->isLess(persons[j-1]); j--) {
            tmp = persons[j-1];
            persons[j-1] = persons[j];
            persons[j] = tmp;
        }
    }
}
