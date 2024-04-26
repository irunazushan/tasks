#include <iostream>
#include <map>
#include <memory>
#include <string>

class StudentDB {
 private:
  struct Student;

 public:
  void addStudent(unsigned int id, const std::string& name, unsigned int age) {
    students[id] = std::make_shared<Student>(Student{id, name, age});
  }

  bool deleteStudentById(unsigned int id) { return students.erase(id) > 0; }

  std::shared_ptr<Student> findStudent(unsigned int id) {
    auto it = students.find(id);
    if (it != students.end()) {
      return it->second;
    }
    return nullptr;
  }

  void printStudentsInfo(unsigned int id) {
    auto student = findStudent(id);
    if (student) {
      std::cout << "Student ID: " << student->id << ", Name: " << student->name
                << ", Age: " << student->age << std::endl;
    } else {
      std::cout << "Student with ID " << id << " not found." << std::endl;
    }
  }

 private:
  struct Student {
    unsigned int id;
    std::string name;
    unsigned int age;
  };

  std::map<int, std::shared_ptr<Student>> students;
};

int main() {
  StudentDB database;

  database.addStudent(1, "Anya", 20);
  database.addStudent(2, "Danya", 19);
  database.addStudent(3, "Boris", 46);
  database.addStudent(4, "Peter", 20);
  database.addStudent(4, "Alex", 20);

  database.findStudent(2);
  database.findStudent(3);
  database.findStudent(1);
  database.deleteStudentById(3);
  database.printStudentsInfo(1);
  database.printStudentsInfo(2);
  database.printStudentsInfo(3);

  return 0;
}
