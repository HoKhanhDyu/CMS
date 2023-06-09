#pragma once
#include<iostream>

using namespace std;

template <typename T>
struct Node
{
	T data;
	Node<T>* next;
};

template <typename T>
struct List
{
	Node<T>* head = NULL;
	Node<T>* tail = NULL;
};

struct Student
{
	int idx;
	string firstName, lastName, id, address, className, pass, cccd;
	int age, sex;
	string birth;
};

struct Lecturer
{
	int idx;
	string firstName, lastName, degree, id, cccd, field, pass;
	int sex;
};

struct grade {
	int idx;
	Student st;
	double GPA, MP, FP, OP;
};

struct Class {
	string id;
	List<grade>allSt;
};

struct Subject {
	string id;//ma khoa hoc
	string course_name, class_name, time, session;
	string lecName;//Ten giang vien
	int amount, credits;
	List<grade> allSt;
};

struct Semester {
	bool open = false;
	string begin, end;
	List<Subject> sj;//Danh sach mon hoc
};

struct schoolYear {
	string year;
	Semester smt[4];
	List<Class> cls;
};

void addYear(string year);
void addSem(string year, int sem, Semester s);
void addClass(string year, Class cls);



void check();