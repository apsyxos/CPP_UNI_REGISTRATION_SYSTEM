#include <iostream>
#include <vector>
#include <iomanip>
#include <memory>
#include <string>

class UniversityMember
{
private:
  std::string name, surname, id;
  //this value is used when we want to output the member in the txt file. there is one in every class
  std::string className = "University Member";
protected:
  //getters
  std::string const& getName()const { return name; }
  std::string const& getSurname()const { return surname; }
  std::string const& getID()const { return id; }

  //ostream overloading
  friend std::ostream& operator <<(std::ostream& out, const UniversityMember& uniMember);
  //istream overloading
  friend std::istream& operator>>(std::istream& input, UniversityMember&);

  //printing the personal info of every member. it is applied in every class
  //it is added in the print method that is overriden and used in every class as needed
  void personalDetailsRegistration(std::ostream& os)const;

public:
  //Constructor
  UniversityMember();

  virtual std::string const& getClassName()const { return className; }

  //registering a university member
  virtual const UniversityMember& memberRegistration();
  //output of the member that we register
  virtual void print(std::ostream&)const;
  //output the member to the text file
  void serializeMember(std::ostream& os)const;

  //rule of 5(copy constructor,move constructor,move assignment, assignment operator, destructor)
  UniversityMember(const UniversityMember& uniMember) = delete;
  UniversityMember(UniversityMember&& uniMember) = delete;
  UniversityMember& operator=(UniversityMember&& uniMember) = delete;
  UniversityMember& operator= (const UniversityMember& uniMember) = delete;
  virtual ~UniversityMember() = default;
};

//virtual to solve the diamond inheritance problem
class Student : public virtual UniversityMember
{
private:
  std::vector<size_t> grades;
  float gradesAverage;
  std::string className = "Student";

protected:
  const std::vector<size_t>& getGrades()const { return grades; }
  float getGradesAverage() const { return gradesAverage; }
  //this function calculates the average of the courses of the student
  float const calculateGradesAverage() const;

public:
  Student();

  std::string const& getClassName()const override { return className; }

  //registering a student. we are overriding the memberRegistration in the Person class
  const UniversityMember& memberRegistration() override;
  void print(std::ostream&) const override;

  Student(const Student& stu) = delete;
  Student(Student&& stu) = delete;
  Student& operator=(Student&& stu) = delete;
  Student& operator =(const Student& stu) = delete;
  ~Student() = default;
};

//virtual to solve the diamond inheritance problem
class Faculty : public virtual UniversityMember
{
private:
  bool canTeach;
  std::string className = "Faculty";

protected:
  //const can either be on the left or right of the return type
  bool const getCanTeach() const { return canTeach; }
  const void setCanTeach(const bool& teachable) { canTeach = teachable; }

public:
  Faculty();

  std::string const& getClassName()const override { return className; }

  const UniversityMember& memberRegistration() override;
  void print(std::ostream&) const override;

  Faculty(const Faculty& faculty) = delete;
  Faculty(Faculty&& faculty) = delete;
  Faculty& operator=(Faculty&& faculty) = delete;
  Faculty& operator =(const Faculty& faculty) = delete;
  ~Faculty() = default;
};

class TA : public virtual Student, public virtual Faculty
{
private:
  std::string className = "TA";

public:
  TA();

  std::string const& getClassName()const final { return className; }

  const UniversityMember& memberRegistration() final;
  void print(std::ostream&) const final;

  TA(const TA& ta) = delete;
  TA(TA&& ta) = delete;
  TA& operator=(TA&& ta) = delete;
  TA& operator =(const TA& ta) = delete;
  ~TA() = default;
};


class Professor : public virtual Faculty
{
private:
  int officeNumber;
  std::string className = "Professor";

public:
  Professor();

  std::string const& getClassName()const final { return className; }

  const UniversityMember& memberRegistration() final;
  void print(std::ostream&) const final;

  Professor(const Professor& professor) = delete;
  Professor(Professor&& professor) = delete;
  Professor& operator=(Professor&& professor) = delete;
  Professor& operator =(const Professor& professor) = delete;
  ~Professor() = default;
};


