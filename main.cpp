#include <iostream>
#include <string>
#include <istream>
#include <ostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <memory>
#include <regex>
#include <thread>
#include <mutex>
#include <map>
#include <iterator>
#include <numeric>
#include <cmath>
using namespace std;
class Decryption
{private : 
	string decrypted;
	int rotor1;
	int rotor2;
public: 
	vector <int> index_and;
	vector <int> index_an;
	vector <string> list_and;
	vector <string> list_an;
	Decryption()
	{

	}
	Decryption(string a)
	{
		decrypted = a;
		rotor1 = 1;
		rotor2 = 1;
	}
	char getChar(char cur, int offset)
	{
		offset = offset % 27;
		int distance = (int)cur - 97; // distance of the current character to last character of alphabet or z
		if (offset <= distance)
		{
			int newOffset = (int)cur - offset;
			char newChar = (char)newOffset;
			return newChar;
		}
		else
		{
		    distance = (int)cur - 96;
			int newOffset = offset - distance;
			newOffset = 123 - newOffset;
			char newChar = (char)newOffset;
			return newChar;
		}
	}
	void increment()
	{
		rotor2++;
	}
	void setRotor2(int a)
	{
		rotor2 = a;
	}
	void setAnd()
	{
	
		int length = decrypted.length();
		for (int i = 0; i < length - 2; i++)
		{
		
			int first = abs((int)decrypted[i] - (int)decrypted[i + 1]);
			int second = abs((int)decrypted[i+1] - (int)decrypted[i + 2]);
			//cout << "First : " << first << " Second: " << second << endl;
			if (first == 13 && second == 18)
				index_and.push_back(i);
			if (first == 13 && second == 11)
				index_and.push_back(i);
			if (first == 14 && second == 17)
				index_and.push_back(i);
		}
		//cout << "000000000000000000000000" << endl;
	}
	void setAn()
	{
		int length = decrypted.length();
		for (int i = 0; i < length - 1; i++)
		{
			int first = abs((int)decrypted[i] - (int)decrypted[i + 1]);
			vector<int>::iterator it = find(index_and.begin(), index_and.end(), i);
			if (it == index_and.end())
			{
				if (first == 13)
					index_an.push_back(i);
				if (first == 14)
					index_an.push_back(i);
				
			}
		}
	}
	void printAnd()
	{
		cout << "This is and list" << endl;
		for (int i = 0; i < index_and.size(); i++)
		{
			cout << index_and[i] << decrypted[index_and[i]] << endl;
		}
	}
	void printAn()
	{
		cout << "This is an list" << endl;
		for (int i = 0; i < index_an.size(); i++)
		{
			cout << index_an[i] << endl;
		}
	}
	int chooseOffset(int i)
	{
		int first = abs((int)decrypted[i] - (int)decrypted[i + 1]);
		int second = abs((int)decrypted[i + 1] - (int)decrypted[i + 2]);
		
		int offset;
		char cur = decrypted[i];
		int distance = (int)cur - (int)'a';
		while (distance < i)
		{
			distance += 27;
		}
		offset = distance;
		return offset;
		//if (first == 13 && second == 18) // This 3 if statement is to choose the offset 
		//	offset = 15;
		//if (first == 13 && second == 11)
		//	offset = 23;
		//if (first == 14 && second == 17)
		//	offset = 7;
		//if (offset < i)
		//	offset += 27;
		//return offset;
	}
	int chooseSecond(int i)
	{
		int first = abs((int)decrypted[i] - (int)decrypted[i + 1]);
		int offset;
		char cur = decrypted[i];
		int distance = (int)cur - (int)'a';
		while (distance < i)
		{
			distance += 27;
		}
		offset = distance;
		return offset;
		/*if (first == 13)
			offset = 15;
		if (first == 14)
			offset = 7;
		if (offset < i)
			offset += 27;
		return offset;*/
	}
	void decrypt_and() // decrypt based on n 
	{
		
		for (int i = 0; i < index_and.size(); i++)
		{
			int index = index_and[i];
			int offset = this->chooseOffset(index);
			offset = offset - index;
			string test = decrypted;
			for (int j = 0; j < test.size(); j++)
			{  
				test[j] = this->getChar(test[j], offset);
				if (test[j] == '{')
					test[j] = ' ';
				offset++;
			}
			list_and.push_back(test);
			
		}
	}
	void decrypt()
	{
		for (int i = 0; i < list_and.size(); i++)
		{
			string test = list_and[i];
			string a = "and";
			size_t found = test.find(a);
			int index;
			if (found != std::string::npos)
			{
				index = found;
			}
			if (test[index + 3] == ' ')
				cout << "The decrypted word is: " << test << endl;

		}
	}
	
};
int main ()
{
	Decryption test("tynirtgjdtrnudnrvavnaayshfbvptbggnlbmmobtqwdyjcxkr");
	test.setAnd();
	test.setAn();
	cout << " This decryption scheme work for sentence which have the word and " << endl;
	test.decrypt_and();
	test.decrypt();
	//cout << test.list_and[0] << endl;
	//test.printAnd();
	/*test.printAnd();
	test.printAn();*/

	//char curChar = 'c';
	//cout << test.getChar(curChar, 16);
	system("pause");
	return 0;
}