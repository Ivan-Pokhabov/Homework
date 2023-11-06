#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef enum PhonebookErrorCode
{
	ok,
	nullptr,
	memoryError,
	fileOpenningError,
	invalidIndex
} PhonebookErrorCode;

//Struct of phonebook note
typedef struct PhonebookNote PhonebookNote;

//Struct of phonebook list
typedef struct Phonebook Phonebook;

//Creating a phonebook
Phonebook* createPhonebook(void);

//Checking empty list or not
bool isEmpty(const Phonebook* const phonebook, PhonebookErrorCode* errorCode);

//Add new note into phonebook
PhonebookErrorCode add(Phonebook* const phonebook, const char* const name, const char* const number);

//Print all notes from phonebook
PhonebookErrorCode print(const Phonebook* const phonebook);

//Taking data from file to phonebook
PhonebookErrorCode getFileData(const char const fileName[], Phonebook* phonebook, size_t* size);

//Sort notes in phonebook
void mergeSort(Phonebook* phonebook, const size_t leftBorder, const size_t rightBorder, const int parameter, PhonebookErrorCode* errorCode);

//Print instructions of using phonebook
void instructions(void);

//Clear memory of phonebook
void deletePhonebook(Phonebook** phonebook);

//For checking is sorted phonebook or not
bool checkSort(const Phonebook* const phonebook, const int parameter);