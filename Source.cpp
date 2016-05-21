#include "Parser.h"
#include "Translator.h"
#include <iostream>

int main()
{
	Parser *myParser = new Parser;
	Translator *myTranslator = new Translator;
	char inputfile[50] = "Trans.txt";
	myParser->setTranslator(myTranslator);
	myParser->setInFile(inputfile);
	myParser->ParseCommandFile();

	myTranslator->PrintAll();

	return 0;
}