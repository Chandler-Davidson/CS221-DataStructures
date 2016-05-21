/*************************************************************
*	File: 		Translator.cpp
*	Author: 	Chandler Davidson
*   Date:		11/16/15
*	Purpose:	Initialize the functions defined in Translator.h
*************************************************************/
#include "Translator.h"
#include "Parser.h"
#include <iostream>
using namespace std;

// Default Constructor
Translator::Translator()
{
	m_pRoot = NULL;
}

// Default Destructor
Translator::~Translator()
{
	DestroyTree(m_pRoot);
}

// Inserts the alien and English words into the binary tree
void Translator::InsertWord(char *aWord, char *eWord)
{
	TNode *temp;
	TNode *back;
	temp = m_pRoot;
	back = NULL;

	TNode *newNode = new TNode();
	newNode -> left = NULL;
	newNode -> right = NULL;
	strcpy(newNode->key, aWord);
	strcpy(newNode->EngWord, eWord);

	while (temp != NULL)
	{
		back = temp;
		if (strcmp(newNode->key, temp->key) < 0)
		{
			temp = temp->left;
		}

		else
		{
			temp = temp->right;
		}
	}

	if (back == NULL)
	{
		m_pRoot = newNode;
	}

	else
	{
		if (strcmp(newNode->key, back->key) < 0)
		{
			back->left = newNode;
		}

		else
		{
			back->right = newNode;
		}
	}
}

// Translates the given line
void Translator::Translate(char *line)
{
	char ignoreChars[9] = " ,?.!:;";
	char *searchTerm;
	TNode *temp = Search(line);

	searchTerm = strtok(line, ignoreChars);
	temp = Search(searchTerm);

	while (searchTerm != NULL)
	{
		if (temp != NULL)
		{
			cout << temp->EngWord << " ";
		}

		else
		{
			cout << "-unknown- ";
		}

		searchTerm = strtok(NULL, ignoreChars);

		if (searchTerm != NULL)
		{
			temp = Search(searchTerm);
		}
	}
}

// Searches the binary tree for the alien word
TNode *Translator::Search(char *aWord)
{
	TNode *temp = m_pRoot;

	while ((temp != NULL) && (strcmp(temp->key, aWord) != 0))
	{
		if (strcmp(aWord, temp->key) < 0)
		{
			temp = temp->left;
		}

		else
		{
			temp = temp->right;
		}

		if (temp == NULL)
		{
			return NULL;
		}
	}

	return temp;
}

// Prints all of the nodes in the binary tree
void Translator::PrintAll()
{
	PrintAll(m_pRoot);
}

// Prints all of the nodes in the binary tree
void Translator::PrintAll(TNode *rt)
{
	if (rt != NULL)
	{
		PrintAll(rt->left);

		for (int i = 0; rt->key[i] != '\0'; i++)
		{
			cout << rt->key[i];
		}

		cout << " = ";

		for (int i = 0; rt->EngWord[i] != '\0'; i++)
		{
			cout << rt->EngWord[i];
		}
		cout << endl;

		PrintAll(rt->right);
	}
}

// Searches the binary tree for the alien word, then removes it
TNode *Translator::RemoveWord(char *aWord)
{

	TNode *back;
	TNode *temp;
	TNode *delNode;
	TNode *delParent;
	TNode *returnNode;
	returnNode = new TNode();

	temp = m_pRoot;
	back = NULL;

	while ((temp != NULL) && (strcmp(aWord, temp->key) != 0))
	{

		back = temp;
		if (strcmp(aWord, temp->key) < 0)
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}
	}

	if (temp == NULL)
	{
		return NULL;
	}

	else
	{
		if (temp == m_pRoot) //Deleting root;
		{

			delNode = m_pRoot;
			delParent = NULL;
		}
		else
		{

			delNode = temp;
			delParent = back;
		}


		strcpy(returnNode->key, delNode->key);
		strcpy(returnNode->EngWord, delNode->EngWord);
	}

	if (delNode->right == NULL)
	{
		if (delParent == NULL)
		{
			m_pRoot = delNode->left;
			delete delNode;
			return returnNode;
		}
		else
		{
			if (delParent->left == delNode)
			{
				delParent->left = delNode->left;
			}
			else
			{
				delParent->right = delNode->left;
			}

			delete delNode;
			return returnNode;
		}
	}

	else // There is at least one child
	{
		if (delNode->left == NULL)
		{
			if (delParent == NULL) // If deleting the root
			{
				m_pRoot = delNode->right;
				delete delNode;
				return returnNode;
			}
			else
			{
				if (delParent->left == delNode)
				{

					delParent->left = delNode->right;
				}
				else
				{
					delParent->right = delNode->right;
				}

				delete delNode;
				return returnNode;
			}
		}

		else //Case 2, deleting node with two children
		{  
			temp = delNode->left;
			back = delNode;

			while (temp->right != NULL)
			{
				back = temp;
				temp = temp->right;
			}


			strcpy(delNode->key, temp->key);
			strcpy(delNode->EngWord, temp->EngWord);

			//Remove the replacement node from the tree
			if (back == delNode)
			{
				back->left = temp->left;
			}
			else
			{
				back->right = temp->right;
			}


			delete temp;
			return returnNode;
		}
	}
}

// Deletes the entire tree
void Translator::DestroyTree(TNode *rt)
{
	if (rt != NULL)
	{
		DestroyTree(rt->left);
		DestroyTree(rt->right);
		delete rt;
	}
}

bool Translator::ChangeWord(char *aWord, char *eWord)
{
	TNode *temp;
	temp = Search(aWord);

	strcpy(temp->EngWord, eWord);

	temp = m_pRoot;

	return true;
}

