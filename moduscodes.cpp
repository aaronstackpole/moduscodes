#include <iostream>
#include <string>

using namespace std;

struct CypherMap
{
	string Alphabet;
	string Cypherbet;
	string CodewordEncrypted;
	string CodewordDecrypted;
};
struct CodewordMap
{
	string Letters;
	string Numbers;
	string Codeword;
	string LaunchCode;
};

string g_inputBuffer;

namespace MODUS
{
	class LaunchEngine
	{
		CypherMap*				m_cypherMap;
		CodewordMap*			m_codewordMap;

	public:
		LaunchEngine()
			: m_cypherMap{ new CypherMap() }
			, m_codewordMap{ new CodewordMap() }
		{}
		~LaunchEngine()
		{
			delete m_codewordMap;
			delete m_cypherMap;
		}

		CypherMap* GetCypherMapPtr() { return m_cypherMap; }
		CodewordMap* GetCodeWordMapPtr() { return m_codewordMap; }

		void FindCypherbet(string codeword)
		{
			string cypher;
			for (auto & i : codeword)
			{
				i = toupper(i);
			}
			cypher = codeword;

			for (auto i : m_cypherMap->Alphabet)
			{
				bool found = false;
				for (auto j : codeword)
				{
					if (i == j) found = true;
				}
				if (!found) cypher += i;
			}

			m_cypherMap->Cypherbet = cypher;
		}
		void DecryptLetters(string codeword)
		{
			string decrypted;
			for (auto & i : codeword)
			{
				i = toupper(i);
			}

			for (auto i : codeword)
			{
				int j = 0;
				for (auto jj : m_cypherMap->Cypherbet)
				{
					if (i == jj)
					{
						decrypted += m_cypherMap->Alphabet[j];
						break;
					}
					j++;
				}
			}

			m_cypherMap->CodewordDecrypted = decrypted;
		}
		void FindLaunchCode(string codeword)
		{
			string code;
			for (auto & i : codeword)
			{
				i = toupper(i);
			}

			for (auto i : codeword)
			{
				int j = 0;
				for (auto jj : m_cypherMap->CodewordDecrypted)
				{
					if (i == jj)
					{
						code += m_codewordMap->Numbers[j];
						break;
					}
					j++;
				}
			}

			m_codewordMap->LaunchCode = code;
		}
	};
}

int main()
{
	auto pEngine = new MODUS::LaunchEngine();


	auto pCypherMap = pEngine->GetCypherMapPtr();
	auto pCodewordMap = pEngine->GetCodeWordMapPtr();

	pCypherMap->Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	cout << "Welcome to MODUS!" << endl;
	cout << "Please input encryption key word: ";
	getline(cin, g_inputBuffer);
	pCypherMap->CodewordEncrypted = g_inputBuffer;

	pEngine->FindCypherbet(pCypherMap->CodewordEncrypted);
	cout << endl;

	cout << "We have determined your cypherbet to be: " << pCypherMap->Cypherbet << endl;
	cout << "Input your code letters (8): ";
	getline(cin, g_inputBuffer);
	pCodewordMap->Letters = g_inputBuffer;
	cout << "Input your code numbers (8): ";
	getline(cin, g_inputBuffer);
	pCodewordMap->Numbers = g_inputBuffer;

	pEngine->DecryptLetters(pCodewordMap->Letters);	
	cout << endl;

	cout << "Your decrypted letters are: " << pCypherMap->CodewordDecrypted << endl;
	cout << "Input your unscrambled word: ";
	getline(cin, g_inputBuffer);
	pCodewordMap->Codeword = g_inputBuffer;

	pEngine->FindLaunchCode(pCodewordMap->Codeword);
	cout << endl;

	cout << "Your launch code is: " << pCodewordMap->LaunchCode << endl;
	cout << "Happy nuking!" << endl << endl;

	delete pEngine;

	return 0;
}
