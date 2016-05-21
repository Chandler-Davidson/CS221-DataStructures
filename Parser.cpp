/*************************************************************
*	File: 		Parser.cpp
*	Author: 	Chandler Davidson
*   Date:		11/16/15
*	Purpose:	Initialize the functions defined in Parser.h
*************************************************************/
#include "Parser.h"
#include "Translator.h" 
#include <iostream>
#include <fstream>
using namespace std;

// Default Constructor
Parser::Parser()
{
	inFile = NULL;
	theTranslator = NULL;
}

// Default Destructor
Parser::~Parser()
{
	delete inFile;
	delete theTranslator;
}

// Sets the translator to be used in this class
void Parser::setTranslator(Translator *T)
{
	theTranslator = T;
}

// Sets the private member variable for the text file name
void Parser::setInFile(char *fileName)
{
	strcpy(m_sFileName, fileName);
	inFile = new ifstream();

	inFile -> open(m_sFileName);

	if (!inFile -> is_open())
	{
		cout << "File was unable to open." << endl;
		exit(0);
	}

	return;
}

// Function sets the line char array to the next line the file
// Function provided by Coleman
bool Parser::getNextLine(char *line, int linelen)
{
	bool done = false;

	while (!done)
	{
		inFile -> getline(line, linelen);

		if (inFile -> good())				// If a line was successfully read
		{
			if (strlen(line) = =  0)		// Skip any blank lines
			{
				continue;
			}
			else if (line[0] = =  '#')	// Skip any comment lines
			{
				continue;
			}

			else						// Got a valid data line so return with this line
			{
				done = true;
			}
		}
		else
		{
			strcpy(line, "");
			return false;
		}
	}
	return true;
}

// Takes the next line and calls the appropriate function
void Parser::ParseCommandFile()
{
	char line[200] = {};
	inFile = new ifstream;
	inFile -> open(m_sFileName);

	while (inFile -> good())	// The whole file
	{
		getNextLine(line, 199);
		if (strcmp(line, "INSERT") = =  0)
		{
			doInsertWord();
		}

		else if (strcmp(line, "REMOVE") = =  0)
		{
			doRemoveWord();
		}

		else if (strcmp(line, "TRANSLATE") = =  0)
		{
			doTranslate();
		}

		else if (strcmp(line, "CHANGE") = =  0)
		{
			doChangeWord();
		}
	}

	inFile -> close();
}

// Parses text file for the alien and english words
// Then calls the appropriate function
void Parser::doInsertWord()
{
	char	line[200] = "";
	char	alienWord[33] = "";
	char	englishWord[33] = "";
	char	*temp = NULL;
	int		numberOfTimes;

	cout << "\n = = =  = INSERTING = = =  = \n" << endl;

	getNextLine(line, 199);
	numberOfTimes = atoi(line);

	for (int i = 0; i < numberOfTimes; i++)
	{
		getNextLine(line, 199);

		temp = strtok(line, " ");
		strcpy(alienWord, temp);

		temp = strtok(NULL, "\n");
		strcpy(englishWord, temp);

		theTranslator -> InsertWord(alienWord, englishWord);

		cout << "Inserting " << alienWord << " = " << englishWord << endl;
	}
}

// Parses text file for the alien and english words
// Then calls the appropriate function
void Parser::doChangeWord()
{
	char	line[200] = "";
	char	alienWord[33] = "";
	char	englishWord[33] = "";
	char	*temp = NULL;
	int		numberOfTimes;

	cout << "\n = = =  = CHANGING = = =  = \n" << endl;

	getNextLine(line, 199);
	numberOfTimes = atoi(line);

	for (int i = 0; i < numberOfTimes; i++)
	{
		getNextLine(line, 199);

		temp = strtok(line, " ");
		strcpy(alienWord, temp);

		temp = strtok(NULL, "\n");
		strcpy(englishWord, temp);

		if (theTranslator -> ChangeWord(alienWord, englishWord))
		{
			cout << alienWord << " is changed to " << englishWord << endl;
		}

		else
		{
			cout << "Word not found." << endl;
			exit(0);
		}
	}
}

// Parses text file for the alien word
// Then calls the appropriate function
void Parser::doTranslate()
{
	char	line[200] = "";
	int		numberOfTimes;
	int		back = 0;

	getNextLine(line, 199);
	numberOfTimes = atoi(line);

	cout << "\n = = =  = TRANSLATING = = =  = \n" << endl;

	for (int i = 0; i < numberOfTimes; i++)
	{
		getNextLine(line, 199);

		cout << "Translating: " << line << "\n\t";

		theTranslator -> Translate(line);

		cout << "\n";
	}
}

// Parses text file for the alien word
// Then calls the appropriate function
void Parser::doRemoveWord()
{
	TNode	*returnNode;
	char	line[200] = "";
	int		numberOfTimes;

	cout << "\n = = =  = REMOVING = = =  = \n" << endl;

	getNextLine(line, 199);
	numberOfTimes = atoi(line);

	for (int i = 0; i < numberOfTimes; i++)
	{
		getNextLine(line, 199);

		returnNode = theTranslator -> RemoveWord(line);
		
		if (strcmp(returnNode -> key, line) = =  0)
		{
			cout << "Successfully removed " << line << "." << endl;
			delete returnNode;
		}

		else
		{
			cout << "The word was not removed." << endl;
			delete returnNode;
			return;
		}
	}

}