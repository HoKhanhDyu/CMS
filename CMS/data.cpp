#include"data.h"
#include"menu.h"

List<schoolYear> hcmus;

template <typename T>
void addToList(List<T>& l, T data) { //them 1 phan tu vao List co kieu T
	Node<T>* tm = new Node<T>;
	tm->data = data;
	tm->next = NULL;
	if (l.head == NULL) {
		l.head = tm;
		l.tail = tm;
		return;
	}
	l.tail->next = tm;
	l.tail = tm;
}

void addYear(string year) {
	schoolYear tm;
	tm.year = year;
	addToList<schoolYear>(hcmus, tm);
}

schoolYear* findYear(string year) {
	Node<schoolYear>* tm = hcmus.head;
	while (tm != NULL) {
		if (tm->data.year == year) return &tm->data;
		tm = tm->next;
	}
	schoolYear s;
	s.year = "0";
	return &s;
}

void addSem(string year, int sem, Semester s) {
	schoolYear* tm = findYear(year);
	s.open = true;
	tm->smt[sem] = s;
}



void addClass(string year, Class cls) {
	schoolYear* sclYear = findYear(year);
	addToList<Class>(sclYear->cls, cls);
}

void addSubject(string year, int sem, Subject sj) {
	schoolYear* sclYear = findYear(year);
	addToList<Subject>(sclYear->smt[sem].sj, sj);
}



void check() {
	cout << hcmus.head->data.year << endl;
	cout << hcmus.head->data.cls.head->data.id;
	system("pause");
}

List<Class> slsInYear(string year) {
	schoolYear* sclYear = findYear(year);
	return sclYear->cls;
}

void add1StToCls(Class& cls, Student st) {
	grade tm;
	tm.st = st;
	addToList<grade>(cls.allSt, tm);
}

void add1StToSj(Subject &sj, Student st) {
	grade tm;
	tm.st = st;
	addToList<grade>(sj.allSt, tm);
}