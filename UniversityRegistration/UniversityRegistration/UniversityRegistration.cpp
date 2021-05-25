#include <iostream>
#include <memory>
#include <fstream>
#include "Registration.h"

/*
This is a program that creates and updates a list of university members, of different types
and adding them to a txt file to be stored. Each member will have at least a name, surname, and id,
and afterward, extra information, depending on the category they belong to.

The categorization of the types of members was done with the help of classes and took advantage of all
the OOP concepts that C++ includes, like inheritance, abstraction, and encapsulation. Specifically,
the diamond inheritance problem was used in this example, since it is a nice way to demonstrate
possible issues that are seen in C++, like early binding.

For the program, the user follows the console commands, and uses the numerical values given to input
the necessary info. Then, the user is asked to confirm the input and when that happens,
the university member created is added to the text file, as well as added in a vector, 
that can be accessed and show in the console all the members that were added while the program is active. 
*/


namespace records
{
  std::vector<std::unique_ptr<UniversityMember>> members;
  std::ofstream uniMemberFile;
}

/*
* This function creates a new member, confirms the input, 
and then adds it in the text file and the vector of members.
This is the most important function that is used when we choose the type of member we want to create.
*/
template<class T, typename = typename std::enable_if<std::is_base_of<UniversityMember, T>::value>::type>
void registeringMember()
{
  std::unique_ptr<T> t;
  std::string s;
  do
  {
    t = std::make_unique<T>();
    t->memberRegistration();
    std::cout << "----- Input Results -----\n";
    t->print(std::cout);
    std::cout << "-------------------------\n\n";
    std::cout << "Confirm if the member information is correct.\nPress 'Y' if it is, or 'N' if it is not and you want to input the information again.\n";
    std::cin.clear();
    std::getline(std::cin, s);
    if (s == "Y" || s == "y")
      break;
    else if (s == "N" || s == "n")
    {
      std::cout << "Wrong information were added, please repeat the process\n";
      continue;
    }
    else
    {
      std::cout << "ATTENTION! No confirmation was given. Input of current member information will repeat\n";
      continue;
    }
  } while (true);
  t->serializeMember(records::uniMemberFile);
  records::members.push_back(std::move(t));
  records::uniMemberFile.flush();
}

//This function includes a “for” loop that prints on the console every member that has been added while the program is used.
//It is one of the numerical options in the main list. 
void registrationListAdditions()
{
  std::cout << "----- REGISTRATION LIST ADDITIONS -----\n";
  for (size_t i = 0; i < records::members.size(); ++i)
  {
    std::cout << "----- Entry no: " << i + 1 << " -----\n";
    records::members[i]->print(std::cout);
    std::cout << "-----------------------\n";
  }
  std::cout << "---------------------------------------\n";
}

/*
This function asks the user to choose what they want to do. 
It uses a “do-while” loop and runs continuously until the user explicitly chooses to exit the program 
through one of the commands. The input that is asked is a number, however, it is registered as a string,
since that way it is easier to manage input that is not asked from the user and was inputted by mistake,
like a wrong number or a word.
*/
void createMember()
{
  std::cout << "University Registration System\n";
  std::string s;
  do
  {
    std::cout << "\nPress 1 to add a new university member,\n2 to add a student,\n3 to add a faculty member,"
      "\n4 to add a TA,\n5 to add a professor account,\n9 to show current member additions,\nor 0 to exit the program.\n";

    std::cin.clear();

    std::getline(std::cin, s);
    if (s == "1")
      registeringMember<UniversityMember>();
    else if (s == "2")
      registeringMember<Student>();
    else if (s == "3")
      registeringMember<Faculty>();
    else if (s == "4")
      registeringMember<TA>();
    else if (s == "5")
      registeringMember<Professor>();
    else if (s == "9")
      registrationListAdditions();
    else if (s == "0")
    {
      std::cout << '\n';
      return;
    }
    else
      std::cout << "Wrong input. Please try again\n";
  } while (true);
}


auto main()->int
{
  //opening txt file
  records::uniMemberFile.open("Members.txt", std::fstream::app);
  //if we cant open the file, terminate
  if (!records::uniMemberFile.is_open())
  {
    std::cerr << "ERROR! FILE 'Member.txt' NOT OPEN!\n";
    return 0;
  }

  //run registration "manager"
  createMember();

  //closing txt file
  records::uniMemberFile.close();
  return 0;
}

