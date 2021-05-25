#include "Registration.h"

//format the code, VS should have something, google it

//UniversityMember based class ==================================
//Constructor
UniversityMember::UniversityMember() :name(), surname(), id() {}

//output of personal information. it is used in every member registration, since they all need personal info
void UniversityMember::personalDetailsRegistration(std::ostream& os)const
{
  os << "Name: " << getName() << '\n';
  os << "Surname: " << getSurname() << '\n';
  os << "ID: " << getID() << '\n';
}

//ostream overloading
std::ostream& operator<<(std::ostream& out, const UniversityMember& uniMember)
{
  uniMember.print(out);
  return out;
}
//istream overloading
std::istream& operator>>(std::istream& input, UniversityMember& uniMember)
{
  std::cout << "Enter name: ";
  std::getline(input, uniMember.name);
  std::cout << "Enter surname: ";
  std::getline(input, uniMember.surname);
  std::cout << "Enter id: ";
  std::getline(input, uniMember.id);
  std::cout << "\n";

  return input;
}

//register a university member. we enter the personal info that is needed for every type of member
//using the overloaded operator above, and then use it for the registration used in every class
const UniversityMember& UniversityMember::memberRegistration()
{
  std::cout << "\nPlease enter the data for the university member.\n";
  std::cin >> *this;
  return *this;
}

//this function prints the output.
void UniversityMember::print(std::ostream& out) const
{
  personalDetailsRegistration(out);
}

//prints in the text file the university member (of every type)
void UniversityMember::serializeMember(std::ostream& os) const
{
  os << "-----" << getClassName() << "-----\n";
  os << *this;
}
//=== CLASS END ==================================================


// Student derived class =========================================
Student::Student() : UniversityMember(), grades(0, 0), gradesAverage(0) {}

float const Student::calculateGradesAverage() const
{
  float average;
  size_t sum = 0;
  for (size_t g : grades)
    sum += g;
  average = (float)sum / grades.size();
  return average;
}


const UniversityMember& Student::memberRegistration()
{
  UniversityMember::memberRegistration();

  //this do-while asks the user to enter the number of courses the student has completed
  size_t input;
  std::string str;
  std::cout << "Enter number of courses the student has completed (1-5): ";
  do
  {
    std::getline(std::cin, str);
    try
    {
      input = std::stoi(str);
      if (input < 1 || input>5)
      {
        std::cout << "VALUE OUT OF BOUNDS.\nPlease enter an acceptable value between 1 and 5.\n";
        continue;
      }
      else
      {
        grades.resize(input);
        break;
      }
    }
    catch (const std::invalid_argument&) {
      std::cout << "Wrong input. Please try again\n";
      continue;
    }
  } while (true);

  //this do-while asks the user to enter the the grades of the courses the student has completed
  std::string s;
  size_t i = 0;
  do
  {
    std::cout << "Enter course grade for course no" << i + 1 << ": ";
    std::cin.clear();

    std::getline(std::cin, s);
    try
    {
      grades[i] = std::stoi(s);
      if (this->grades[i] < 0 || this->grades[i]>100)
      {
        std::cout << "VALUE OUT OF BOUNDS.\nPlease enter an acceptable value between 0 and 100.\n";
        continue;
      }
      else
      {
        ++i;
        continue;
      }
    }
    catch (const std::invalid_argument&) {
      std::cout << "Wrong input. Please try again\n";
      continue;
    }
  } while (i < grades.size());

  //calculate the average of the grades
  gradesAverage = this->calculateGradesAverage();
  return *this;
}

void Student::print(std::ostream& os) const
{
  personalDetailsRegistration(os);
  size_t g = 1;
  for (int i : grades)
    os << "Course " << g++ << " grade: " << i << '\n';
  os << "Grades Average: " << std::fixed << std::setprecision(2) << gradesAverage << '\n';
}
//=== CLASS END ==================================================


// Faculty derived class =========================================
Faculty::Faculty() : UniversityMember(), canTeach(false) {}

const UniversityMember& Faculty::memberRegistration()
{
  UniversityMember::memberRegistration();

  //check if the faculty member can teach. it is a do-while because
  //unless we add an acceptable input it repeats
  std::string s;
  size_t input;
  do
  {
    std::cout << "Please input 1 if faculty member is active and can teach or 0 if temporarily inactive:\n";

    std::cin.clear();
    std::getline(std::cin, s);
    //can do without try-catch. it can be applied though
    try
    {
      input = std::stoi(s);
      if (input == 1)
      {
        canTeach = true;
        return *this;
      }
      else if (input == 0)
      {
        canTeach = false;
        return *this;
      }
      else
      {
        std::cout << "Wrong number. Please try again\n";
        continue;
      }
    }
    catch (const std::invalid_argument&) {
      std::cout << "Wrong input. Please try again\n";
      continue;
    }
  } while (true);
}

void Faculty::print(std::ostream& os) const
{
  personalDetailsRegistration(os);
  //use boolalpha to change the int to a string for the boolean  
  os << "Can Teach: " << std::boolalpha << getCanTeach() << '\n';
}
//=== CLASS END ==================================================


//=== TA derived class ===========================================
TA::TA() : Student(), Faculty() {}

const UniversityMember& TA::memberRegistration()
{
  Student::memberRegistration();
  setCanTeach(this->getGradesAverage() > 80);
  return *this;
}

void TA::print(std::ostream& os) const
{
  Student::print(os);

  //use boolalpha to change the int to a string for the boolean  
  os << "Can Teach: " << std::boolalpha << getCanTeach() << '\n';
}
//=== CLASS END ==================================================


//=== Professor derived class ====================================
Professor::Professor() :Faculty(), officeNumber(0) {}

const UniversityMember& Professor::memberRegistration()
{
  Faculty::memberRegistration();

  if (this->getCanTeach())
  {
    std::string s;
    do
    {
      std::cout << "Please enter the office number (Between 100-499): ";
      std::cin.clear();

      std::getline(std::cin, s);
      try
      {
        this->officeNumber = std::stoi(s);
        if (this->officeNumber >= 100 && this->officeNumber < 500)
          return *this;
        std::cout << "Error input, please enter an acceptable value.\n";
      }
      catch (const std::invalid_argument&) {
        std::cout << "Wrong input. Please try again\n";
        continue;
      }
    } while (true);
  }
  else
    std::cout << "ATTENTION! PROFESSOR ACCOUNT INACTIVE\n";
  return *this;
}

void Professor::print(std::ostream& out) const
{
  personalDetailsRegistration(out);
  //use boolalpha to change the int to a string for the boolean  
  out << "Active Teaching Personnel: " << std::boolalpha << getCanTeach() << '\n';
  out << "Office: " << officeNumber << '\n';
}
//=== CLASS END ==================================================