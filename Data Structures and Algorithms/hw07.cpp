/*
Kenneth Huynh
Data Structures and Algorithms
Homework 7
*/

#include <iostream>
#include <stack>
using namespace std;

// This is code from Weiss
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>
using namespace std;

class Tokenizer
{
public:
	Tokenizer(istream & input)
		: currentLine(1), errors(0), inputStream(input) { }

	// The public routines
	char getNextOpenClose();
	string getNextID();
	int getLineNumber() const;
	int getErrorCount() const;

private:
	enum CommentType { SLASH_SLASH, SLASH_STAR };

	istream & inputStream;     // Reference to the input stream
	char ch;                   // Current character
	int currentLine;           // Current line
	int errors;                // Number of errors detected

	// A host of internal routines
	bool nextChar();
	void putBackChar();
	void skipComment(CommentType start);
	void skipQuote(char quoteType);
	string getRemainingString();
};


// nextChar sets ch based on the next character in
// inputStream and adjusts currentLine if necessary.
// It returns the result of get.
// putBackChar puts the character back onto inputStream.
// Both routines adjust currentLine if necessary.
bool Tokenizer::nextChar()
{
	if (!inputStream.get(ch))
		return false;
	if (ch == '\n')
		currentLine++;
	return true;
}

void Tokenizer::putBackChar()
{
	inputStream.putback(ch);
	if (ch == '\n')
		currentLine--;
}

// Precondition: We are about to process a comment;
//                 have already seen comment start token.
// Postcondition: Stream will be set immediately after
//                 comment ending token.
void Tokenizer::skipComment(CommentType start)
{
	if (start == SLASH_SLASH)
	{
		while (nextChar() && (ch != '\n'))
			;
		return;
	}

	// Look for */
	bool state = false;    // Seen first char in comment ender.

	while (nextChar())
	{
		if (state && ch == '/')
			return;
		state = (ch == '*');
	}
	cout << "Unterminated comment at line " << getLineNumber() << endl;
	errors++;
}

// Precondition: We are about to process a quote;
//                   have already seen beginning quote.
// Postcondition: Stream will be set immediately after
//                   matching quote.
void Tokenizer::skipQuote(char quoteType)
{
	while (nextChar())
	{
		if (ch == quoteType)
			return;
		if (ch == '\n')
		{
			cout << "Missing closed quote at line " << (getLineNumber() - 1) << endl;
			errors++;
			return;
		}
		// If a backslash, skip next character.
		else if (ch == '\\')
			nextChar();
	}
}

// Return the next opening or closing symbol or '\0' (if EOF).
// Skip past comments and character and string constants.
char Tokenizer::getNextOpenClose()
{
	while (nextChar())
	{
		if (ch == '/')
		{
			if (nextChar())
			{
				if (ch == '*')
					skipComment(SLASH_STAR);
				else if (ch == '/')
					skipComment(SLASH_SLASH);
				else if (ch != '\n')
					putBackChar();
			}
		}
		else if (ch == '\'' || ch == '"')
			skipQuote(ch);
		else if (ch == '\\')  // Extra case, not in text
			nextChar();
		else if (ch == '(' || ch == '[' || ch == '{' ||
			ch == ')' || ch == ']' || ch == '}')
			return ch;
	}
	return '\0';       // End of file
}

// Return current line number.
int Tokenizer::getLineNumber() const
{
	return currentLine;
}

// Return current line number.
int Tokenizer::getErrorCount() const
{
	return errors;
}

// Return indicates if ch can be part of a C++ identifier.
bool isIdChar(char ch)
{
	return ch == '_' || isalnum(ch);
}

// Return an identifier read from input stream.
// First character is already read into ch.
string Tokenizer::getRemainingString()
{
	string result;

	for (result = ch; nextChar(); result += ch)
		if (!isIdChar(ch))
		{
			putBackChar();
			break;
		}

	return result;
}

// Return next identifier, skipping comments
// string constants, and character constants.
// Return "" if end of stream is reached.
string Tokenizer::getNextID()
{
	while (nextChar())
	{
		if (ch == '/')
		{
			if (nextChar())
			{
				if (ch == '*')
					skipComment(SLASH_STAR);
				else if (ch == '/')
					skipComment(SLASH_SLASH);
				else
					putBackChar();
			}
		}
		else if (ch == '\\')
			nextChar();
		else if (ch == '\'' || ch == '"')
			skipQuote(ch);
		else if (!isdigit(ch) && isIdChar(ch))
			return getRemainingString();
	}
	return "";       // End of file
}


// Code from Weiss
// Symbol is the class that will be placed on the Stack.
struct Symbol
{
	char token;
	int  theLine;
};

class Balance
{
public:
	Balance(istream & is) :tok(is), errors(0){}
	int checkBalance() { // returns the number of mismatched parenthesis
		stack<Symbol> stax;
		Symbol x;
		x.token = tok.getNextOpenClose();
		x.theLine = tok.getLineNumber();
		while (x.token != '\0') {
			if (stax.empty() && x.token == ')' || x.token == ']' || x.token == '}') { // cParen when stack empty
				cout << "Excessive closing parenthesis on line " << x.theLine << endl;
				errors++;
			}
			else if (x.token == '(' || x.token == '[' || x.token == '{'){ // oParen
				stax.push(x);
			}
			else { // cParen and stack not empty
				checkMatch(stax.top(), x);
				stax.pop();
			}
			x.token = tok.getNextOpenClose();
			x.theLine = tok.getLineNumber();
		}
		while (!stax.empty()) { // stack not empty even after going through the whole file
			cout << "Excessive opening parenthesis on line " << stax.top().theLine << endl;
			stax.pop();
			errors++;
		}
		return errors;
	}
private:
	Tokenizer tok;
	int errors;
	void checkMatch(const Symbol & oParen, const Symbol & cParen) {
		if (oParen.token == '(') {
			if (cParen.token != ')') {
				errors++;
				cout << "Parenthesis mismatch." << oParen.token << " does not match with " << cParen.token << endl;
			}
		}
		else if (oParen.token == '[') {
			if (cParen.token != ']') {
				errors++;
				cout << "Parenthesis mismatch." << oParen.token << " does not match with " << cParen.token << endl;
			}
		}
		else if (oParen.token == '{') {
			if (cParen.token != '}') {
				errors++;
				cout << "Parenthesis mismatch." << oParen.token << " does not match with " << cParen.token << endl;
			}
		}
	}
};


int main() {
	ifstream ifs;
	ifs.open("Text.txt");

	Balance bal(ifs);
	int errors = bal.checkBalance();
	cout << "Number of errors: " << errors << endl;
	return 0;
}