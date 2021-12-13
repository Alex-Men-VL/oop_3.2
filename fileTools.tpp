template <typename TS>
TS setFileName(TS &name) {
    TS path("../source/");
    path += name;
    return path;
}

template <typename TS>
TS getInputFileName() {
    TS inputFileName;
    std::cout << "Enter the name of the input file: ";
    std::cin >> inputFileName;
    inputFileName = setFileName(inputFileName);
    return inputFileName;
}

template <typename TS>
TS getOutputFileName(){
    TS outputFileName;
    std::cout << "Enter the name of the output file: ";
    std::cin >> outputFileName;
    outputFileName = setFileName(outputFileName);
    return outputFileName;
}

template <typename T, typename TP, typename TS>
void setPersonsFromFile(T inputFileName, TP **persons) {
    std::ifstream inputFile;
    TS firstName;
    TS lastName;
    TS cardNumber;
    TS cardDate;
    inputFile.open(inputFileName);
    if (!inputFile) {
        throw ERROR_FILE_NOT_OPEN;
    }

    int count;
    inputFile >> count;

    int personNumber = 0;
    while (personNumber != count) {
        persons[personNumber] = new TP();
        inputFile >> lastName >> firstName >> cardNumber >> cardDate;
        persons[personNumber]->setCardOwner(lastName, firstName, cardNumber, cardDate);
        personNumber++;
    }
}

template <typename TS>
void setPersonsCountFromFile(TS inputFileName, int &count) {
    std::ifstream inputFile;

    inputFile.open(inputFileName);
    if (!inputFile) {
        throw ERROR_FILE_NOT_OPEN;
    }
    inputFile >> count;
    if (count < 1) {
        throw ERROR_NOT_CORRECT_PERSON_COUNT;
    }
}

template <typename TP, typename TS>
void checkInput(const int pCount, TP **persons) {
    for (int pNumber = 0; pNumber < pCount; pNumber++) {
        char lastNameFirstLetter = persons[pNumber]->getLastName()[0];
        if (!isupper(lastNameFirstLetter)) {
            throw ERROR_FL_LN_NOT_CAPITAL;
        }
        char firstNameFirstLetter = persons[pNumber]->getFirstName()[0];
        if (!isupper(firstNameFirstLetter)) {
            throw ERROR_FL_FN_NOT_CAPITAL;
        }
        int lastNameLen = persons[pNumber]->getLastNameLen();
        if (lastNameLen < 3 || lastNameLen > 15) {
            throw ERROR_NOT_CORRECT_LN;
        }

        int firstNameLen = persons[pNumber]->getFirstNameLen();
        if (firstNameLen < 2 || firstNameLen > 10) {
            throw ERROR_NOT_CORRECT_FN;
        }

        int cardNumberLen = persons[pNumber]->getCardNumberLen();
        if (cardNumberLen != 16) {
            throw ERROR_NOT_CORRECT_CN;
        }

        for (int digitNumber = 0; digitNumber < cardNumberLen; digitNumber++) {
            char digit = persons[pNumber]->getCardNumber()[digitNumber];
            if (!(digit >= '0' && digit <= '9')) {
                throw ERROR_NOT_CORRECT_CN;
            }
        }

        TS cardDate{};
        cardDate = persons[pNumber]->getCardDate();
        int cardDateLen =  persons[pNumber]->getCardDateLen();
        if (cardDateLen != 5) {
            throw ERROR_NOT_CORRECT_DATE;
        }
        for (int digitNumber = 0; digitNumber < cardDateLen; digitNumber++) {
            if (digitNumber != 2) {
                char digit = cardDate[digitNumber];
                if (!(digit >= '0' && digit <= '9')) {
                    throw ERROR_NOT_CORRECT_DATE;
                }
            } else {
                char sign = cardDate[digitNumber];
                if (sign != '/') {
                    throw ERROR_NOT_CORRECT_DATE;
                }
            }

            if ((cardDate[0] == '0' && cardDate[1] == '0') || (cardDate[3] == '0' && cardDate[4] == '0')) {
                throw ERROR_NOT_CORRECT_DATE;
            }
        }
    }
}

template <typename TS>
void clearOutputFile(TS outputFileName) {
    std::ofstream outputFile;
    outputFile.open(outputFileName, std::ofstream::out | std::ofstream::trunc);
    outputFile.close();
}

template <typename TS, typename TP>
void printPersonsInFile(TS outputFileName, const int pCount, TP **persons) {
    std::ofstream outputFile;

    outputFile.open(outputFileName, std::ios::app);
    if (!outputFile) {
        throw ERROR_FILE_NOT_OPEN;
    }
    outputFile << pCount << "\n";
    for (int i = 0; i < pCount; i++) {
        outputFile << persons[i]->getLastName() << " ";
        outputFile << persons[i]->getFirstName() << " ";
        outputFile << persons[i]->getCardNumber() << " ";
        outputFile << persons[i]->getCardDate() << "\n";
    }
}
