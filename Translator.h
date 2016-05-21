/*********************************************************
*	File: 		Translator.h
*	Author: 	Chandler Davidson
*   Date:		11/16/15
*	Purpose:	Define the class that used in Translator.cpp
*********************************************************/
#pragma once
#include "Parser.h"
using namespace std;

struct TNode
{
	char key[33];
	char EngWord[33];
	TNode *left;
	TNode *right;
};

class Translator
{
private:
	TNode *m_pRoot;

	void PrintAll(TNode *rt);
	TNode *Search(char *aWord);
	void DestroyTree(TNode *rt);

public:
	Translator();
	~Translator();
	void InsertWord(char *aWord, char *eWord);
	TNode *RemoveWord(char *aWord);
	bool ChangeWord(char *aWord, char *eWord);
	void Translate(char *line);
	void PrintAll();

};
