#include "fileTools.h"
#include "functions.h"
#include "InsertionSort.h"

const char* ERROR_NOT_CORRECT_ARGUMENT = "Provide the number 1 or 2 as a command line argument";

template <typename T, typename TP, typename TS>
int getSolution(T inputFileName, T outputFileName) {
    int personsCount = 0;
    try {
        setPersonsCountFromFile<T>(inputFileName, personsCount);
    } catch (const char* error) {
        std::cerr << error << std::endl;
        return 1;
    }
    TP *persons[personsCount];
    setPersonsFromFile<T, TP, TS>(inputFileName, persons);

    try {
        checkInput<TP, TS>(personsCount, persons);
    } catch (const char* error) {
        std::cerr << error << std::endl;
        return 1;
    }

    sortPersons<TP>(personsCount, persons);

    clearOutputFile<T>(outputFileName);
    try {
        printPersonsInFile<T, TP>(outputFileName, personsCount, persons);
    } catch (const char* error) {
        std::cerr << error << std::endl;
        return 1;
    }


    int endingCardsNumber = getEndingCardsNumber<TP>(personsCount, persons);
    std::cout << "TThe number of cards that expire in the current year: " << endingCardsNumber << std::endl;

    if (isNamesakes<TP>(personsCount, persons)) {
        std::cout << "In the input file there are owners with the same last names, but different names" << std::endl;
    } else {
        std::cout << "In the input file there are no owners with the same last names, but different names" << std::endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    float taskNumber = 0;
    if (argc != 2) {
        std::cerr << ERROR_NOT_CORRECT_ARGUMENT << std::endl;
        return 1;
    } else {
        taskNumber = std::stof(argv[1]);
    }

    if (taskNumber == 2) {
        std::cout << "Using own String class\n" << std::endl;

        String iFileName;
        String oFileName;
        iFileName = getInputFileName<String>();
        oFileName = getOutputFileName<String>();
        const char* inputFileName = iFileName.getStr();
        const char* outputFileName = oFileName.getStr();
        return getSolution<const char*, BankCard<String>, String>(inputFileName, outputFileName);
    } else if (taskNumber == 1) {
        std::cout << "Using the string class from STL\n" << std::endl;

        std::string iFileName;
        std::string oFileName;
        iFileName = getInputFileName<std::string>();
        oFileName = getOutputFileName<std::string>();
        return getSolution<std::string, BankCard<std::string>, std::string>(iFileName, oFileName);
    } else {
        std::cerr << ERROR_NOT_CORRECT_ARGUMENT << std::endl;
        return 1;
    }
}
