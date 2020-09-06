 #include <iostream>
#include <sstream>
#include <fstream> 
#include <string>
#include <vector>

using namespace std; 

const int ALPHABET_SIZE = 26; 

// trie node 
struct TrieNode 
{ 
	struct TrieNode *children[ALPHABET_SIZE]; 

	// isEndOfWord is true if the node represents 
	// end of a word 
	bool isEndOfWord;
	string frequency; 
}; 

// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) 
{ 
	struct TrieNode *pNode = new TrieNode; 

	pNode->isEndOfWord = false; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
		pNode->children[i] = NULL; 

	return pNode; 
} 

// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insert(struct TrieNode *root, string key,string frequency) 
{ 
	struct TrieNode *pCrawl = root; 

	for (int i = 0; i < key.length(); i++) 
	{ 
		int index = key[i] - 'a'; 
		if (!pCrawl->children[index]) 
			pCrawl->children[index] = getNode(); 

		pCrawl = pCrawl->children[index]; 
	} 

	// mark last node as leaf 
	pCrawl->isEndOfWord = true;
	pCrawl->frequency=frequency;
} 

// Returns true if key presents in trie, else 
// false 
string search(struct TrieNode *root, string key) 
{ 
	struct TrieNode *pCrawl = root; 

	for (int i = 0; i < key.length(); i++) 
	{ 
		int index = key[i] - 'a'; 
		if (!pCrawl->children[index]) 
			return ""; 

		pCrawl = pCrawl->children[index]; 
	} 

	if (pCrawl != NULL && pCrawl->isEndOfWord)
		return pCrawl->frequency; 
} 

// Driver 
int main() 
{ 
	// Input keys (use only 'a' through 'z' 
	// and lower case) 
	vector<string> row;
	char c=',';
	string wsearch,word,line,res; 
	fstream fin;
	int f=0;
	fin.open("EnglishDictionary.csv",ios::in);
	struct TrieNode *root = getNode(); 
	getline(cin,wsearch);
	// Construct trie
	while(fin.good())
	{
		row.clear(); 
		
		// read an entire row and 
        // store it in a string variable 'line' 
        getline(fin, line);
        
		// used for breaking words 
		stringstream s(line); 

		// read every column data of a row and 
		// store it in a string variable, 'word'
		while (getline(s, word, c)) { 

			// add all the column data 
			// of a row to a vector 
			row.push_back(word); 
		}
		
		insert(root,row[0],row[1]);
		res=search(root,wsearch);
		if(res!="")
		{
			f=1;
			break;
		}
	}
	if(f==1)
		cout<<"Yes,"<<res<<"\n";
	else
		cout<<"No\n";
	return 0; 
} 

