#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Person {
public:
    Person(const string& name, const string& type_) : Name(name), type(type_) {}
    virtual void Walk(const string& destination) const = 0;
    const string Name;
    const string type;
};

class Student : public Person {
public:
    Student(const string& name, const string& favouriteSong) : Person(name, "Student"), FavouriteSong(favouriteSong) {}
    void Learn() const {
        cout << type << ": " << Name << " learns" << endl;
    }
    void Walk(const string& destination) const override {
        cout << type << ": " << Name << " walks to: " << destination << endl;
        cout << type << ": " << Name << " sings a song: " << FavouriteSong << endl;
    }
    void SingSong() const {
        cout << type << ": " << Name << " sings a song: " << FavouriteSong << endl;
    }
private:
    const string FavouriteSong;
};

class Teacher : public Person {
public:
    Teacher(const string& name, const string& subject) : Person(name, "Teacher"), Subject(subject) {}
    void Teach() const {
        cout << type << ": " << Name << " teaches: " << Subject << endl;
    }
    void Walk(const string& destination) const override {
        cout << type << ": " << Name << " walks to: " << destination << endl;
    }
private:
    const string Subject;
};

class Policeman : public Person {
public:
    Policeman(const string& name) : Person(name, "Policeman") {}
    void Check(const Person& p) const {
        cout << "Policeman: " << Name << " checks " << p.type << ". " << p.type << "'s name is: " << p.Name << endl;
    }
    void Walk(const string& destination) const override {
        cout << type << ": " << Name << " walks to: " << destination << endl;
    }
};

void VisitPlaces(const Person& p, const vector<string>& places) {
    for (const auto& place : places) {
        p.Walk(place);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, { "Moscow", "London" });
    p.Check(s);
    VisitPlaces(s, { "Moscow", "London" });
    return 0;
}




//#include <iostream>
//#include <string>
//#include <vector>
//
//using namespace std;
///***********************_Human_class_declaration_***********************/
//class Human {
//public:
//	Human(const string& type, const string& name);
//	virtual void Walk(const string& destination) const;
//
//	const string type_, name_;
//};
//
///***********************_Student_class_declaration_********************/
//class Student : public Human {
//public:
//	Student(const string& name, const string& favouriteSong);
//	void Learn() const;
//	void Walk(const string& destination) const override;
//	void SingSong() const;
//
//private:
//	const string favourite_song_;
//};
//
///***********************_Teacher_class_declaration_*********************/
//class Teacher : public Human {
//public:
//	Teacher(const string& name, const string& subject);
//	void Teach();
//
//private:
//	const string subject_;
//};
//
///***********************_Policeman_class_declaration_******************/
//class Policeman : public Human {
//public:
//	Policeman(string name);
//	void Check(const Human& h) const;
//};
//
///***********************_Additional_functions_declarations_************/
//void VisitPlaces(const Human& h, const vector<string>& places);
//
///***********************_Main_function_*********************************/
//int main() {
//	Teacher t("Jim", "Math");
//	Student s("Ann", "We will rock you");
//	Policeman p("Bob");
//
//	VisitPlaces(t, { "Moscow", "London" });
//	p.Check(s);
//	VisitPlaces(s, { "Moscow", "London" });
//	return 0;
//}
//
///***********************_Human_class_methods_definitions_***************/
//Human::Human(const string& type, const string& name) :
//	type_(type), name_(name)
//{}
//
//void Human::Walk(const string& destination) const {
//	cout << type_ << ": " << name_ << " walks to: " << destination << endl;
//}
//
///***********************_Student_class_methods_definitions_*************/
//Student::Student(const string& name, const string& favouriteSong) :
//	Human("Student", name),
//	favourite_song_(favouriteSong)
//{}
//
//void Student::Learn() const {
//	cout << "Student: " << name_ << " learns" << endl;
//}
//
//void Student::Walk(const string& destination) const {
//	Human::Walk(destination);
//	SingSong();
//}
//
//void Student::SingSong() const {
//	cout << "Student: " << name_ << " sings a song: " << favourite_song_ << endl;
//}
//
///***********************_Teacher_class_methods_definitions_*************/
//Teacher::Teacher(const string& name, const string& subject) :
//	Human("Teacher", name), subject_(subject)
//{}
//
//void Teacher::Teach() {
//	cout << "Teacher: " << name_ << " teaches: " << subject_ << endl;
//}
//
///***********************_Policeman_class_methods_definition_************/
//Policeman::Policeman(string name) :
//	Human("Policeman", name)
//{}
//
//void Policeman::Check(const Human& h) const {
//	cout << "Policeman: " << name_ << " checks " << h.type_ << ". " << h.type_ << "'s name is: " << h.name_ << endl;
//}
//
///***********************_Additional_functions_definitions_**************/
//void VisitPlaces(const Human& h, const vector<string>& places) {
//	for (auto p : places) {
//		h.Walk(p);
//	}
//}
