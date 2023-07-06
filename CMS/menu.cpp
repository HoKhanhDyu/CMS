#include"menu.h"
#include"data.h"
#include <conio.h>

string nowYear = "2023";
int nowSem = 2;

void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

int choose(const char* ten, const char* a[], int n) {
	int ch = 0;
	while (true) {
		system("cls");
		cout << "Nam " << nowYear << " hoc ki " << nowSem << endl<<endl;
		cout << ten << endl << endl;
		for (int i = 0; i < n; i++) {
			if (i == ch) cout << ">>" << a[i] << endl;
			else cout << "  " << a[i] << endl;
		}
		char k = _getch();
		if (k == 80) {
			ch = (ch + 1) % n;
		}
		if (k == 72) {
			ch = (ch + n - 1) % n;
		}
		if (k == 13) return ch;
	}
}

Class* chonLop() {
	List<Class> l = clsInYear(nowYear);
	int t = 0;
	Node<Class>* tm = l.head;
	while (tm != NULL) {
		cout << ++t << ". " << tm->data.id<<endl;
		tm = tm->next;
	}
	cout << "Nhap chi so cua lop can chon: ";
	int k;
	cin >> k;
	cin.ignore();
	tm = l.head;
	k--;
	while (k--) tm = tm->next;
	return &(tm->data);
}

Subject* chonMon() {
	List<Subject> l = sjInSem(nowYear,nowSem);
	int t = 0;
	Node<Subject>* tm = l.head;
	while (tm != NULL) {
		cout << ++t << ". " << tm->data.id<<endl;
		tm = tm->next;
	}
	cout << "Nhap chi so cua mon can chon: ";
	int k;
	cin >> k;
	cin.ignore();
	tm = l.head;
	k--;
	while (k--) tm = tm->next;
	return &(tm->data);
}

void themNamHoc() {
	string year;
	cout << "Nhap nam can tao: ";
	cin >> year;
	addYear(year);
	nowYear = year;
	nowSem = 0;
}

void themHocKi() {
	cout << "Hien la nam " << nowYear << " hoc ki " << nowSem << endl;
	cout << "Nhap hoc ki can them: ";
	int sem;
	cin >> sem;
	Semester s;
	cout << "Nhap ngay bat dau: ";
	cin >> s.begin;
	cout << "Nhap ngay ket thuc: ";
	cin >> s.end;
	addSem(nowYear, sem, s);
	nowSem = sem;
}

void themLop() {
	Class cls;
	cout << "Nhap ten lop: ";
	cin >> cls.id;
	addClass(nowYear, cls);
}

void themMonHoc() {
	Subject tm;
	cout << "Nhap ma khoa hoc: ";
	getline(cin, tm.id);
	cout << "Nhap ten khoa hoc: ";
	getline(cin, tm.course_name);
	cout << "Nhap ten lop hoc: ";
	getline(cin, tm.class_name);
	cout << "Nhap ten giao vien: ";
	getline(cin, tm.lecName);
	cout << "Nhap so tin chi: ";
	cin >> tm.credits;
	cout << "Nhap so luong sinh vien toi da: ";
	cin >> tm.amount;
	cin.ignore();
	cout << "Nhap ngay hoc trong tuan: ";
	getline(cin, tm.time);
	cout << "Nhap buoi hoc: ";
	getline(cin, tm.session);
	addSubject(nowYear, nowSem, tm);
}

Student getAStudent() {
	Student tm;
	string sex;
	cout << "Nhap ho sinh vien: ";
	getline(cin, tm.firstName);
	cout << "Nhap ten sinh vien: ";
	getline(cin, tm.lastName);
	cout << "Nhap id sinh vien: ";
	getline(cin, tm.id);
	cout << "Nhap gioi tinh sinh vien (Nam/Nu): ";
	getline(cin, sex);
	tm.sex = (sex == "Nam") ? 0 : 1;
	cout << "Nhap ngay sinh sinh vien (dd/mm/yyyy): ";
	getline(cin, tm.birth);
	return tm;
}

void svToCls() {
	cout << "Chon lop can them" << endl;
	Class* cls = chonLop();
	cout << "Nhap thong tin tin vien can them: " << endl;
	Student st = getAStudent();
	add1StToCls(*cls, st);
}

void svToSj() {
	cout << "Chon mon can them" << endl;
	Subject* sj = chonMon();
	cout << "Nhap thong tin tin vien can them: " << endl;
	Student st = getAStudent();
	add1StToSj(*sj, st);
}

void fileToCls() {
	cout << "Chon lop can them" << endl;
	Class* cls = chonLop();
	string path;
	cout << "Nhap dia chi file data: ";
	getline(cin, path);
	addDsSvToCls(*cls, path);
}

void fileToSJ() {
	cout << "Chon mon can them" << endl;
	Subject* sj = chonMon();
	string path;
	cout << "Nhap dia chi file data: ";
	getline(cin, path);
	addDsSvToSJ(*sj, path);
}

void menu_themSinhVien() {
	int k;
	const char* a[] = {
	"Them 1 sinh vien vao lop",
	"Them 1 sinh vien vao mon hoc",
	"Nhap danh sach sinh vien cho lop",
	"Nhap danh sach sinh vien cho mon hoc",
	"Thoat"
	};
	k=choose("Them sinh vien:", a, 5);
	switch (k) {
	case 0:
		svToCls();
		break;
	case 1:
		svToSj();
		break;
	case 2:
		fileToCls();
		break;
	case 3:
		fileToSJ();
		break;
	case 4:
		return;
	}
	menu_themSinhVien();
}

void menu_new() {
	int k;
	const char* a[] = {
	"Nam hoc",
	"Hoc ki",
	"Lop",
	"Mon hoc",
	"Sinh vien",
	"Thoat"
	};
	k = choose("Menu them:", a, 6);
	switch (k) {
	case 0:
		themNamHoc();
		break;
	case 1:
		themHocKi();
		break;
	case 2:
		themLop();
		check();
		break;
	case 3:
		themMonHoc();
		break;
	case 4:
		menu_themSinhVien();
		break;
	case 5:
		return;
	}
	menu_new();
}

void xem_lop() {
	cout << "Chon lop can xem" << endl;
	Class* cls = chonLop();
	system("cls");
	cout << "Danh sach lop " << cls->id << endl;
	Node<grade>* tm = cls->allSt.head;
	int k = 0;
	while (tm != NULL) {
		cout << ++k << ". " << tm->data.st.lastName<<endl;
		tm = tm->next;
	}
	system("pause");
}

void xoaMonHoc() {
	List<Subject> l = sjInSem(nowYear, nowSem);
	int t = 0;
	Node<Subject>* tm = l.head;
	while (tm != NULL) {
		cout << ++t << ". " << tm->data.id << endl;
		tm = tm->next;
	}
	cout << "Nhap chi so cua mon can chon: ";
	int k;
	cin >> k;
	cin.ignore();
	tm = l.head;
	if (k == 1) {
		l.head = l.head->next;
		delete tm;
		return;
	}
	k=k-2;
	while (k--) tm = tm->next;
	Node<Subject>* tm2 = tm->next;
	tm = tm2->next;
	delete tm2;
}

void xem_mon() {
	cout << "Chon mon can xem" << endl;
	Subject* sj = chonMon();
	system("cls");
	cout << "Danh sach lop " << sj->course_name << endl;
	Node<grade>* tm = sj->allSt.head;
	int k = 0;
	while (tm != NULL) {
		cout << ++k << ". " << tm->data.st.lastName << endl;
		tm = tm->next;
	}
	system("pause");
}


void menu_view() {
	int k;
	const char* a[]{
	"Lop hoc",
	"Mon hoc",
	"Thoat"
	};
	k=choose("Xem mon va lop:", a, 3);
	switch (k) {
	case 0:
		xem_lop();
		break;
	case 1:
		xem_mon();
		break;
	case 2:
		return;
	}
	menu_view();
}

void xuatCSV() {
	cout << "Chon mon can xuat:" << endl;
	Subject* sj = chonMon();
	system("cls");
	cout << "Chon vi tri luu:";
	string path;
	getline(cin, path);
	gradeToCSV(path + "/" + sj->id+".csv", sj->allSt);
}

void capnhatdiem() {
	cout << "Chon mon can nhap" << endl;
	Subject* sj = chonMon();
	cout << "Nhap dia chi cua file";
	string path;
	getline(cin, path);
	sj->allSt = gradeStFromFile(path);
}



void menuGV() {
	const char* name = "Menu giao vien";
	const char* a[6] = {
		"New",
		"Xem",
		"Xoa",
		"Xuat csv",
		"Cap nhat diem",
		"Thoat"
	};
	int k=choose(name,a, 6);
	switch (k) {
	case 0:
		menu_new();
		break;
	case 1:
		menu_view();
		break;
	case 2:
		xoaMonHoc();
		break;
	case 3:
		xuatCSV();
		break;
	case 4:
		capnhatdiem();
		break;
	case 5:
		return;
	}
	menuGV();
}

void changepass(string id) {
	string pass, pass1, pass2;
	do {
		system("cls");
		cout << "Nhap mat khau cu:";
		getline(cin, pass);
		cout << "Nhap mat khau moi:";
		getline(cin, pass1);
		cout << "Xac nhan mat khau:";
		getline(cin, pass2);
		if (pass1 != pass2) {
			cout << "Mat khau khong khop!!!" << endl;
			system("pause");
			continue;
		}
		else if (changepass(id, pass, pass1)) {
			cout << "Doi mat khau thanh cong!";
			system("pause");
			break;
		}
		else cout << "Sai mat khau!";
		system("pause");
	} while (true);
}

void xemSJ(string id) {
	system("cls");
	cout << "Danh sach mon hoc:" << endl;
	List<SVSJ> k = getSJ(id, nowYear, nowSem);
	Node<SVSJ>* tm = k.head;
	int t = 0;
	while (tm != NULL) {
		cout << ++t << ". " << tm->data.name;
		tm = tm->next;
	}
	system("pause");
}

void xemDiem(string id) {
	system("cls");
	cout << "Diem mon hoc:" << endl;
	List<SVSJ> k = getSJ(id, nowYear, nowSem);
	Node<SVSJ>* tm = k.head;
	int t = 0;
	while (tm != NULL) {
		t++;
		scanf("%4d. %s|%f|%f|%f|%f",t,tm->data.name.c_str(),tm->data.OP,tm->data.MP,tm->data.FP,tm->data.MP*0.25+tm->data.FP*0.5+tm->data.OP*0.25);
		tm = tm->next;
	}
	system("pause");
}

void menuSV(string id) {
	const char* a[] = {
		"Doi mat khau",
		"Xem khoa hoc",
		"Xem diem",
		"Thoat"
	};
	int k = choose("Menu sinh vien:", a, 4);
	switch (k)
	{
	case 0:
		changepass(id);
		break;
	case 1:
		xemSJ(id);
		break;
	case 2:
		xemDiem(id);
		break;
	case 3:
		return;
		break;
	}
	menuSV(id);
}

void login() {
	int k = -1;
	string id, pass;
	do {
		system("cls");
		cout << "Nhap id: ";
		getline(cin, id);
		cout << "Nhap mat khau: ";
		getline(cin, pass);
		k = checkpass(id, pass);
		if (k == 0) {
			cout << "Sai mat khau vui long nhap lai!!!!" << endl;
			system("pause");
		}
	} while (k == 0);
	Nocursortype();
	if (k == 2) menuGV();
	else menuSV(id);
}