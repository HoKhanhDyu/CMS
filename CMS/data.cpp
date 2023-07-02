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

List<Class> clsInYear(string year) {
	schoolYear* sclYear = findYear(year);
	return sclYear->cls;
}

List<Subject> sjInSem(string year, int sem) {
	schoolYear* sclYear = findYear(year);
	return sclYear->smt[sem].sj;
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

List<grade> gradeStFromFile(string path) {
	ifstream fp(path);
	List<grade> tm;
	if (fp.is_open()) {
		string line;
		getline(fp, line);
		while (getline(fp, line)) {
			grade g;
			string sex;
			char k;
			stringstream s(line);
			getline(s, g.st.firstName, ',');
			getline(s, g.st.lastName, ',');
			getline(s, sex, ',');
			getline(s, g.st.birth, ',');
			getline(s, g.st.cccd, ',');
			getline(s, g.st.className, ',');
			getline(s, g.st.pass, ',');
			g.st.sex = (sex == "Nam") ? 0 : 1;
			addToList<grade>(tm, g);
		}
	}
	return tm;
}

void addDsSvToCls(Class& cls, string path) {
	List<grade> g = gradeStFromFile(path);
	Node<grade>* tm = g.head;
	while (tm!=NULL)
	{
		addToList<grade>(cls.allSt, tm->data);
		tm = tm->next;
	}
}

void addDsSvToSJ(Subject& sj, string path) {
	List<grade> g = gradeStFromFile(path);
	Node<grade>* tm = g.head;
	while (tm != NULL)
	{
		addToList<grade>(sj.allSt, tm->data);
		tm = tm->next;
	}
}

void createFolder(string name) {
	_mkdir(name.c_str());
}

void gradeToCSV(string path, List<grade> s) {
	ofstream fo(path);
	Node<grade>* tm = s.head;
	while (tm != NULL) {
		fo << tm->data.idx << ",";
		fo << tm->data.st.id << ",";
		fo << tm->data.st.firstName << ",";
		fo << tm->data.st.lastName << ",";
		fo << tm->data.st.className << ",";
		fo << tm->data.st.cccd << ",";
		fo << tm->data.st.age << ",";
		fo << tm->data.st.address << ",";
		fo << tm->data.st.birth << ",";
		fo << tm->data.st.sex << ",";
		fo << tm->data.st.pass << endl;
		tm = tm->next;
	}
	fo.close();
}

void ghiClass(string path, List<Class> l) {
	Node<Class>* tm = l.head;
	createFolder(path + "/class");
	path = path + "/class";
	while (tm != NULL) {
		gradeToCSV(path + "/" + tm->data.id + ".csv", tm->data.allSt);
		tm = tm->next;
	}
}

void inFolder() {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	LPCWSTR a = L"data/*.*";

	hFind = FindFirstFile(a, &FindFileData);
	while (FindNextFile(hFind, &FindFileData)) {
		wstring ws(FindFileData.cFileName);
		string s(ws.begin(), ws.end());
		cout << s << endl;
	}
}



void ghiSem(string path, Semester sem) {
	createFolder(path);
	ofstream fo(path + "info.csv");
	fo << sem.begin << "," << sem.end << endl;
	Node<Subject>* tm = sem.sj.head;
	while (tm!=NULL)
	{
		fo << tm->data.id << ",";
		fo << tm->data.course_name << ",";
		fo << tm->data.class_name << ",";
		fo << tm->data.time << ",";
		fo << tm->data.session << ",";
		fo << tm->data.lecName << ",";
		fo << tm->data.amount << ",";
		fo << tm->data.credits << endl;
		gradeToCSV(path+"/"+tm->data.id+".csv", tm->data.allSt);
		tm = tm->next;
	}
}

void save_data() {
	Node<schoolYear>* tm = hcmus.head;
	string path = "data";
	createFolder(path);
	while (tm!= NULL) {
		path = path + "/" + tm->data.year;
		createFolder(path + "/" + tm->data.year);
		ghiClass(path + "/" + tm->data.year, tm->data.cls);
		for (int i = 1; i <= 3; i++) {
			if (tm->data.smt[i].open) {
				ghiSem(path,tm->data.smt[i]);
			}
		}
		tm = tm->next;
	}
}



//hello, my name is Nhan6+
LPCWSTR toL(string s) {
	LPCWSTR tm = wstring(s.begin(), s.end()).c_str();
	return tm;
}

string toS(wchar_t* s) {
	wstring ws(s);
	string tm(ws.begin(),ws.end());
	return tm;
}

void load_sem(string path) {

}

void load_year(string path) {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFile(toL(path), &FindFileData);
	while (FindNextFile(hFind, &FindFileData)) {
		string name = toS(FindFileData.cFileName);
		if (name != "..") {
			if (name[0] == 's') load_sem(path + "/" + name);
			else load_cls(path + "/class");
		}
	}
}

void load_data() {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	string path = "data/*.*";

	hFind = FindFirstFile(toL(path), &FindFileData);
	while (FindNextFile(hFind, &FindFileData)) {
		string name = toS(FindFileData.cFileName);
		if (name != "..") {
			load_year(path + "/" + name);
		}
	}
}