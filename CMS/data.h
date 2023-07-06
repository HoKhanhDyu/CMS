#pragma once
//#include<bits/stdc++.h>

#include<direct.h>
#include<iostream>
#include<fstream>
#include <windows.h>
#include <sstream>
#include <stdio.h>
#include <tchar.h>

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
	string firstName, lastName, id, address, className, pass, cccd;
	int age, sex;
	string birth;
};

struct Lecturer
{
	string firstName, lastName, degree, id, cccd, field, pass;
	int sex;
};

struct grade {
	string idx;
	Student st;
	double MP, FP, OP;
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

struct tk {
	string id, pass="abc", cv;
};

struct SVSJ {
	string name;
	double MP, FP, OP;
};

void addYear(string year);
void addSem(string year, int sem, Semester s);
void addClass(string year, Class cls);
void addSubject(string year, int sem, Subject sj);
List<Class> clsInYear(string year);
void add1StToCls(Class& cls, Student st);
void add1StToSj(Subject& sj, Student st);
List<Subject> sjInSem(string year, int sem);
void addDsSvToCls(Class& cls, string path);
void addDsSvToSJ(Subject& sj, string path);
void load_data();
void save_data();
void getnew(string& year, int& sem);
void gradeToCSV(string path, List<grade> s);
List<grade> gradeStFromFile(string path);
int checkpass(string id, string pass);
bool changepass(string id, string pass, string newpass);
List<SVSJ> getSJ(string id, string year, int sem);

void check();