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
	cout << path;
	List<grade> tm;
	if (fp.is_open()) {
		cout << "baaaaaa";
		string line;
		while (getline(fp, line)) {
			cout << "hi";
			grade g;
			string sex;
			char k;
			stringstream s(line);
			if(s.tellp()==0)
			getline(s, g.idx, ',');
			getline(s, g.st.id, ',');
			getline(s, g.st.firstName, ',');
			getline(s, g.st.lastName, ',');
			getline(s, g.st.className, ',');
			getline(s, g.st.cccd, ',');
			s >> g.st.age>>k;
			getline(s, g.st.address, ',');
			getline(s, g.st.birth, ',');
			getline(s, sex, ',');
			getline(s, g.st.pass, '\n');
			g.st.sex = (sex == "Nam") ? 0 : 1;
			addToList<grade>(tm, g);
		}
	}
//	cout << tm.head->data.st.firstName;
	fp.close();
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
	ofstream fo(path + "/infoCls.csv");
	while (tm != NULL) {
		fo << tm->data.id << endl;
		gradeToCSV(path + "/" + tm->data.id + ".csv", tm->data.allSt);
		tm = tm->next;
	}
	fo.close();
}

void ghiSem(string path, Semester sem) {
	createFolder(path);
	ofstream fo(path + "/info.csv");
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
	fo.close();
}

void save_data() {
	Node<schoolYear>* tm = hcmus.head;
	string path = "data";
	createFolder(path);
	while (tm!= NULL) {
		//path = path + "/" + tm->data.year;
		//cout << tm->data.year << endl;
		createFolder(path + "/" + tm->data.year);
		ghiClass(path + "/" + tm->data.year, tm->data.cls);
		for (int i = 1; i <= 3; i++) {
			if (tm->data.smt[i].open) {
				ghiSem(path + "/" + tm->data.year +"/sem"+(char)(i+48), tm->data.smt[i]);
			}
		}
		tm = tm->next;
	}
	cout << "daluu";
}



//hello, my name is Nhan6+


Semester load_sem(string path) {
	Semester sem;
	sem.open = false;
	ifstream fi(path + "/info.csv");
	cout << path << endl;
	if (fi.is_open()) {
		cout << "hi";
		sem.open = true;
		string line;
		getline(fi, line);
		stringstream s(line);
		getline(s, sem.begin, ',');
		getline(s, sem.end, '\n');
		while (getline(fi, line)) {
			stringstream s(line);
			Subject sj;
			getline(s, sj.id, ',');
			getline(s, sj.course_name, ',');
			getline(s, sj.class_name, ',');
			getline(s, sj.time, ',');
			getline(s, sj.session, ',');
			getline(s, sj.lecName, ',');
			s >> sj.amount;
			char tm;
			s >> tm;
			s >> sj.credits;
			sj.allSt = gradeStFromFile(path+"/"+sj.id+".csv");
		}
		fi.close();
	}
	return sem;
}

string toS(wchar_t* s) {
	wstring ws(s);
	string tm(ws.begin(), ws.end());
	return tm;
}

void load_cls(string path,List<Class> &l) {
	ifstream fi(path + "/infoCls.csv");
	if (fi.fail()) cout << path;
	while (!fi.eof()) {
		Class cls;
		getline(fi, cls.id);
		cout << cls.id << endl;
		//int h;
		//cin >> h;
		cls.allSt = gradeStFromFile(path + "/" + cls.id + ".csv");
		if(cls.id!="")addToList<Class>(l, cls);
	}
	fi.close();
}

void load_year(string path,string year) {
	schoolYear sc;
	sc.year = year;
	for (char i = '1'; i <= '3'; i++) {
		sc.smt[i - 48] = load_sem(path + "/sem" + i);
		cout << sc.smt[i - 48].open << endl;
	}
	cout << "hi";
	load_cls(path + "/class",sc.cls);
	addToList<schoolYear>(hcmus, sc);
}



void load_data() {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	string path = "data";
	string pa = path + "/*.*";
	wstring ws(pa.begin(), pa.end());
	LPCWSTR k = ws.c_str();	
	hFind = FindFirstFile(k, &FindFileData);
	wstring ws1(FindFileData.cFileName);
	string s(ws1.begin(), ws1.end());
	cout << s << endl;
	while (FindNextFile(hFind, &FindFileData)) {
		string name = toS(FindFileData.cFileName);
		if (name != "..") {
			cout << name << endl;
			load_year(path + "/" + name,name);
		}
	}
}

void getnew(string &year,int &sem) {
	int t = 0;
	sem = 0;
	schoolYear sc;
	Node<schoolYear>* tm = hcmus.head;
	while (tm != NULL) {
		cout << tm->data.year << endl;
		if (t < stoi(tm->data.year)) {
			t = stoi(tm->data.year);
			sc = tm->data;
		}
		tm = tm->next;
	}
	year = to_string(t);
	cout << year;
	system("pause");
	for(int i=3;i>=1;i--)
		if (sc.smt[i].open) {
			sem = i;
			return;
		}
	return;
}