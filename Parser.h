/*********************************************************
*	File: 		Parser.h
*	Author: 	Chandler Davidson
*   Date:		11/16/15
*	Purpose:	Define the class that used in Parser.cpp
*********************************************************/
#pragma once
#include <fstream>
#include "Translator.h"
using namespace std;

class Translator;

class Parser
{
private:
	char m_sFileName[64];
	ifstream *inFile;
	Translator *theTranslator;

	void doInsertWord();
	void doChangeWord();
	void doTranslate();
	void doRemoveWord();
	bool getNextLine(char *line, int linelen);

public:
	Parser();
	~Parser();
	void setTranslator(Translator *T);
	void setInFile(char *fileName);
	void ParseCommandFile();
};
