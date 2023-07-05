#include"menu.h"
#include"data.h"

string nowYear = "2023";
int nowSem = 2;

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
	system("cls");
	cout << "Nam hoc hien tai la " << nowYear << " hoc ki " << nowSem << endl;
	printf("1.Them 1 sinh vien vao lop\n");
	printf("2.Them 1 sinh vien vao mon hoc\n");
	printf("3.Nhap danh sach sinh vien cho lop\n");
	printf("4.Nhap danh sach sinh vien cho mon hoc\n");
	printf("0.Thoat\n");
	printf("Nhap lua chon: ");
	cin >> k;
	switch (k) {
	case 1:
		svToCls();
		break;
	case 2:
		svToSj();
		break;
	case 3:
		fileToCls();
		break;
	case 4:
		fileToSJ();
		break;
	case 0:
		return;
	}
	menu_themSinhVien();
}

void menu_new() {
	int k;
	system("cls");
	cout << "Nam hoc hien tai la " << nowYear << " hoc ki " << nowSem << endl;
	printf("1.Nam hoc\n");
	printf("2.Hoc ki\n");
	printf("3.Lop\n");
	printf("4.Mon hoc\n");
	printf("5.Sinh vien\n");
	printf("0.Thoat\n");
	printf("Nhap lua chon: ");
	cin >> k;
	cin.ignore();
	switch (k) {
	case 1:
		themNamHoc();
		break;
	case 2:
		themHocKi();
		break;
	case 3:
		themLop();
		check();
		break;
	case 4:
		themMonHoc();
		break;
	case 5:
		menu_themSinhVien();
		break;
	case 0:
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
	system("cls");
	cout << "Nam hoc hien tai la " << nowYear << " hoc ki " << nowSem << endl;
	printf("1.Lop hoc\n");
	printf("2.Mon hoc\n");
	printf("0.Thoat\n");
	printf("Nhap lua chon: ");
	cin >> k;
	switch (k) {
	case 1:
		xem_lop();
		break;
	case 2:
		xem_mon();
		break;
	case 0:
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

void menu() {
	getnew(nowYear, nowSem);
	int k;
	system("cls");
	cout << "Nam hoc hien tai la " << nowYear << " hoc ki " << nowSem << endl;
	printf("1.New\n");
	printf("2.Xem\n");
	printf("3.Xuat csv\n");
	printf("4.Cap nhat diem\n");
	printf("0.Thoat\n");
	printf("Nhap lua chon: ");
	cin >> k;
	switch (k) {
	case 1:
		menu_new();
		break;
	case 2:
		menu_view();
		break;
	case 3:
		xuatCSV();
		break;
	case 4:
		capnhatdiem();
		break;
	case 0:
		return;
	}
	menu();
}