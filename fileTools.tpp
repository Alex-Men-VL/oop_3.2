template <typename TS>
TS setFileName(TS &name) {
    TS path("../source/");
    path += name;
    return path;
}

template <typename TS>
TS getInputFileName() {
    char *iFileName = new char[20];
    std::cout << "Enter the name of the input file: ";
    std::cin >> iFileName;
    TS inputFileName(iFileName);
    inputFileName = setFileName(inputFileName);
    return inputFileName;
}

template <typename TS>
TS getOutputFileName(){
    char *oFileName = new char[20];
    std::cout << "Enter the name of the output file: ";
    std::cin >> oFileName;
    TS outputFileName(oFileName);
    outputFileName = setFileName(outputFileName);
    return outputFileName;
}

template <typename TP, typename TS>
void addCardOwner(const char *str, const int len, const int personNumber, TP **persons) {
    int pInfoNumber = 0;
    bool notSpace = true;
    char* info = new char[20];
    int infoLen = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ' && notSpace) {
            info[infoLen] = '\0';
            switch(pInfoNumber) {
                case 0: {
                    persons[personNumber]->setFirstName(info);
                    break;
                }
                case 1: {
                    persons[personNumber]->setLastName(info);
                    break;
                }
                case 2: {
                    persons[personNumber]->setCardNumber(info);
                    break;
                }
            }
            pInfoNumber++;
            info = new char[20];
            infoLen = 0;
            notSpace = false;
            continue;
        } else if (str[i] == ' ') {
            continue;
        } else {
            notSpace = true;
            info[infoLen] = str[i];
            infoLen++;
        }
    info[infoLen] = '\0';
    persons[personNumber]->setCardDate(info);
    }
}

template <typename T, typename TP, typename TS>
void setPersonsFromFile(T inputFileName, TP **persons) {
    std::ifstream inputFile;

    try {
        inputFile.open(inputFileName);
        if (!inputFile) {
            throw ERROR_FILE_NOT_OPEN;
        }

        std::string line;
        getline(inputFile, line);  // skip the first line

        int personNumber = 0;
        while (!inputFile.eof()) {
            persons[personNumber] = new TP();
            getline(inputFile, line);
            int len = line.length();
            const char *cstr = line.c_str();
            addCardOwner<TP, TS>(cstr, len, personNumber, persons);

            personNumber++;
        }
    } catch (const char *error) {
        std::cerr << error << std::endl;
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
