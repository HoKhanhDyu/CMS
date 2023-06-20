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
			s >> g.st.idx;
			getline(s, g.st.id, ',');
			getline(s, g.st.id, ',');
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

void load_data() {

}

void createFolder(string name) {
	_mkdir(("hihi/"+name).c_str());
}

void save_data() {
	Node<schoolYear>* tm = hcmus.head;
	while (tm != NULL) {
		path pathObj(folderPath);
	}
}