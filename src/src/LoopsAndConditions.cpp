#include "LoopsAndConditions.h"

#include <iostream>

#include <string>

// this is the anonymous namespace
// Its types, variables and functions are only visible within this file
// You can use the anonymous namespace in any .cpp-file. The compiler will create a unique one for every file.
namespace
{
}

namespace gris
{
  /** \brief This functions combines the content of sections A1 to A3 of the book "Einstieg in C++" by Arnold Willemer
  */
  void runLoopsAndConditions()
  {
    std::cout << "Please enter up to 10 characters:" << std::endl;
    // read the input
    char input[11]; // one more for the escape character
    std::cin.getline(input, 11);
    // print out input
    for (int i(0); i<10; ++i)
    {
      std::cout << i << ": " << input[i] << std::endl;
    }
    // check how many characters resemble numbers
    int numCharacters = 0;
    int numNumbers    = 0;
    for (int i(0); i<10; ++i)
    {
      if (input[i] >= '0' && input[i] <= '9')
        ++numNumbers;
      else
        ++numCharacters;
    }
    std::cout << "you typed in " << numNumbers << " numbers and " << numCharacters << " other characters" << std::endl;

    using namespace std;
    string antwort;
    bool badInput = true;
    do
    {
      cout << "Hallo, Lust auf ein paar Aufgaben (j/n)?" << endl;
      getline(cin, antwort);
      if (antwort == "j") 
      {
        cout << "Gut, dann viel Spass." << endl; 
        badInput = false;
      }
      else if (antwort == "n") 
      {
        return;
      }
    } while (badInput);
    cout << "Zeit fuer eine kleine Aufgabe.\nWas ist 4(203+66)^2-26?" << endl;
    int loesung1;
    cin >> loesung1; // read in an int
    if (loesung1 == 289418)
    {
      cout << "Super!" << endl;
    }
    else
    {
      cout << "Leider falsch! Jetzt geht's weiter." << endl;
    }
    // if the user typed in something else that an integer, the stream sets an internal error state and future calls won't work.
    // clear() resets the internal error state so it would work again
    cin.clear();
    // now we ignore everything the user might have put in, like the return button or a long list of characters
    cin.ignore(10000,'\n');
    std::cout << "Was ist der fuenfzehnte Buchstabe im Alphabet?" << endl;
    string loesung2;
    getline(cin, loesung2);
    if (loesung2 == "o" || loesung2 == "O")
    {
      cout << "Perfekt! Du hast alle (zwei) Aufgaben erfolgreich geloest!" << endl;
    }
    else
    {
      cout << "Schade schade Schokolade";
    }
    cin.get();
  }
}