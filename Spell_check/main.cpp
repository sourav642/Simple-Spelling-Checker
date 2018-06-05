//Simple code for a spell checker
//@author-Sourav
#include<bits/stdc++.h>
#include "Dictionary.h"
using namespace std;
typedef Dictionary<string>::Iterator iterDec;
#define TABLE_SIZE 19000
const char* DELIMITER=" ";//Only space is considered a a delimeter
int SpellCheck(Dictionary<string>& Dictionary, string word);
int main()
{
	// declare variables
	int result=0,ch=0,k=0;
	string userin;
	string currWord;
	ifstream infile;
	Dictionary<string> Dictionary(TABLE_SIZE);

	// open the dictionary file
	infile.open("Dictionary.txt");

	// check if the file exists
	if(infile.fail())
	{
		cout<<"\nERROR:file could not be found\n";
		exit(1);
	}

	while(infile >> currWord)
	{
		// makes sure duplicate words are not inserted into table
		if(!Dictionary.search_table(currWord))
		{
			Dictionary.insert(currWord);
		}
	}
	infile.close();
	cout <<"----------------------SPELLING CHECKER---------------------\n\n" << "Total no. of words in the dictionary:"<<Dictionary.total_elements() <<"\n";

	do{
		cout<<"\nEnter a sentence: ";
		getline(cin,userin);
		cout<<"\n";
		result=0;
		/*split each word from the string into individual words to check if
		they are spelled correctly*/
		char* splitInput = strtok(const_cast<char*>(userin.c_str()),DELIMITER);
		while(splitInput!=NULL)
		{
			currWord=splitInput;
			transform(currWord.begin(), currWord.end(), currWord.begin(), ::tolower);
			result+=SpellCheck(Dictionary,currWord);
			splitInput=strtok(NULL,DELIMITER);
		}
        if(result==0)
            cout <<"No word(s) are mispelled!!\n";
		cout<<"\nDo you want to enter another sentence? (yes=1 OR no=0): ";
		cin >> ch;
		cin.ignore(numeric_limits<streamsize>::max(),'\n'); // clear the buffer
	}while(ch==1);
	return 0;
}// end of main
int SpellCheck(Dictionary<string>& Dictionary, string word)
{
	int suggest = 0;
	string remove1[100];
	int numRemove=0;

	if(!Dictionary.search_table(word))
	{

		cout<<"*"<<word<<"*\n"<<"Suggestions:";

		for(int i=0;i<word.length();i++)
		{
			string alt = word;
			for(int j = 97; j <= 122; j++)
			{
				//trial and error replacing one character at a time
				alt[i] = (char)j;
				if(Dictionary.search_table(alt))
				{
					cout<<alt<<", ";
					remove1[numRemove++] = alt;
					++suggest;

					Dictionary.remove(alt);
				}
				//inserting new character and checking
				string ins = word.substr(0, i) + (char)j + word.substr(i);
				if(Dictionary.search_table(ins))
				{
					cout<<ins<<", ";
					remove1[numRemove++] = ins;
					++suggest;

					Dictionary.remove(ins);
				}
			}
		}

		for(int i=0; i<word.length()-1;i++)
		{
			// checking for pair of characters
			string t_pos = word.substr(0,i) + word[i+1] + word[i] + word.substr(i+2);
			if(Dictionary.search_table(t_pos))
			{
				cout<<t_pos<<", ";
				remove1[numRemove++] = t_pos;
				++suggest;

				Dictionary.remove(t_pos);

			}
			string del = word.substr(0, i)+ word.substr(i + 1);
			if(Dictionary.search_table(del))
			{
				cout<<del<<", ";
				remove1[numRemove++]=del;
				++suggest;

				Dictionary.remove(del);
			}
		}
		while(numRemove>=0)
		{
			Dictionary.insert(remove1[numRemove--]);
		}
		if(suggest < 1)
		{
			cout<<"\nNo suggestions found!!!";
		}
		cout<<"\n\n";
		return 1;
	}
	return 0;
}
