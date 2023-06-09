#include"menu.h"
#include"data.h"

string nowYear = "2023";
int nowSem = 2;

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
	cout << "Nhap ngay hoc trong tuan: ";
	getline(cin, tm.time);
	cout << "Nhap buoi hoc: ";
	getline(cin, tm.session);

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
		//menu_themSinhVien();
		break;
	case 0:
		return;
	}
	menu_new();
}

void menu() {
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
	case 0:
		return;
	}
	menu();
}