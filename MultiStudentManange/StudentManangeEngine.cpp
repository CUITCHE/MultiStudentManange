#include "StudentManangeEngine.h"
#include "MiddleStudent.h"
#include "CollegeStudent.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <list>
#include <algorithm>
const char *FileName = "allOfStudentInfomation.i";
const int ascii_digit_begin = 48;
StudentManangeEngine::StudentManangeEngine(void)
	:engine(new StudentManangeEnginePrivate())
{
}

StudentManangeEngine::~StudentManangeEngine(void)
{
	if (engine){
		delete engine;
		engine = nullptr;
	}
}

void StudentManangeEngine::add()
{
	int num = 0;
label_s:
	cout<<"添加学生记录 - 请按序号操作："<<endl;
	cout<<"1:添加小学生信息"<<endl;
	cout<<"2:添加中学生信息"<<endl;
	cout<<"3:添加大学生信息"<<endl;
	
	num = _getch()-ascii_digit_begin;
	if (num > 3 || num < 1){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		Sleep(1000*3);
		system("cls");
		goto label_s;
	}
	AbstractStudent *info = nullptr;
	switch (num)
	{
	case 1:
		info = new PrimaryStudent();
		add_primary((PrimaryStudent*)info);
		break;
	case 2:
		info = new MiddleStudent();
		add_middle((MiddleStudent *)info);
		break;
	case 3:
		info = new CollegeStudent();
		add_college((CollegeStudent *)info);
		break;
	default:
		cout<<"未知错误！程序退出"<<endl;
		_getch();
		exit(-1);
	}
	engine->addStudent(make_pair((StudentType)num,info));
}

void StudentManangeEngine::query()
{
	cout<<"请输入学号或姓名，进行查询:"<<endl;
	string query_str;
	cin>>query_str;
	auto ret = engine->query(query_str);
	if (ret.first == nil){
		cout<<"未找到相关信息，请按任意键继续..."<<endl;
		_getch();
		return;
	}
	//打印学生信息
	switch (ret.first)
	{
	case Primary:
		PrimaryStudent::print_fmt();
		break;
	case Middle:
		MiddleStudent::print_fmt();
		break;
	case College:
		CollegeStudent::print_fmt();
		break;
	default:
		break;
	}
	putchar('\n');
	ret.second->print();
	cout<<"若需要编辑该生信息，请输入0，否则请按任意键返回："<<endl;
	int rcc = _getch()-ascii_digit_begin;
	if (rcc == 0){
		edit(ret);
	}
}


void StudentManangeEngine::edit(StudentTypeMapBaseInfo &info)
{
	switch (info.first)
	{
	case Primary:
		cout<<"小学生信息修改："<<endl;
		{
			edit(info.second.get());
			shared_ptr<PrimaryStudent> vae = std::move(dynamic_pointer_cast<PrimaryStudent>(info.second));
			edit_p(vae);
		}
		break;
	case Middle:
		cout<<"中学生信息修改："<<endl;
		{
			edit(info.second.get());
			shared_ptr<MiddleStudent> vae = std::move(dynamic_pointer_cast<MiddleStudent>(info.second));
			edit_m(vae);
		}
		break;
	case College:
		cout<<"大学生信息修改："<<endl;
		{
			edit(info.second.get());
			shared_ptr<CollegeStudent> vae = std::move(dynamic_pointer_cast<CollegeStudent>(info.second));
			edit_c(vae);
		}
		break;
	default: break;
	}
}

void StudentManangeEngine::edit(AbstractStudent *info)
{
	int isno;
	cout<<"是否修改学号？（Enter键修改，否则请按其它键）:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cout<<"请输入新的学号："<<endl;
		string no;
		cin>>no;
		while(engine->query(no).first != nil){
			cout<<"学号："<<no<<"已存在"<<"请重新输入！"<<endl;
			cout<<"请输入新的学号："<<endl;
			string no;
			cin>>no;
		}
		info->setNumber(no);
	}

	cout<<"是否修改姓名？（Enter键修改，否则请按其它键）:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		string name;
		cout<<"请输入姓名"<<endl;
		cin>>name;
		info->setName(name);
	}

	cout<<"是否修改性别？（Enter键修改，否则请按其它键）:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cout<<"请输入性别代码（0：男 非0：女）："<<endl;
		isno = _getch()-ascii_digit_begin;
		if (isno == 0){
			info->setSex(Male);
		}
		else {
			info->setSex(Female);
		}
	}

	cout<<"是否修改年龄？（Enter键修改，否则请按其它键）:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cout<<"请输入年龄："<<endl;
		cin>>isno;
		info->setAge(isno);
	}

	cout<<"是否修改班级？（Enter键修改，否则请按其它键）:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cout<<"请输入班级（如：201201）："<<endl;
		cin>>isno;
		info->setClass(isno);
		fflush(stdin);
	}
}

void StudentManangeEngine::edit_p(shared_ptr<PrimaryStudent> info)
{
	float grades;
	cout<<"是否修改英语成绩？（Enter键修改，否则请按其它键）:"<<endl;
	int isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cin>>grades;
		info->setEnglish(grades);
	}
	cout<<"是否修改数学成绩？（Enter键修改，否则请按其它键）:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cin>>grades;
		info->setMath(grades);
	}
	cout<<"是否修改语文成绩？（Enter键修改，否则请按其它键）:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cin>>grades;
		info->setChinese(grades);
	}
}

void StudentManangeEngine::edit_m(shared_ptr<MiddleStudent> info)
{
	edit_p(dynamic_pointer_cast<PrimaryStudent>(info));
	cout<<"是否修改地理成绩？（Enter键修改，否则请按其它键）:"<<endl;
	int isno = _getch()-ascii_digit_begin;
	float grades;
	if (isno == 13){
		cin>>grades;
		info->setGeography(grades);
	}
	cout<<"是否修改历史成绩？（Enter键修改，否则请按其它键）:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cin>>grades;
		info->setHistory(grades);
	}
}

void StudentManangeEngine::edit_c(shared_ptr<CollegeStudent> info)
{
	int isno;
	float grades;
	cout<<"是否修改专业成绩？（Enter键修改，否则请按其它键）:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cin>>grades;
		info->setMajor(grades);
	}

	cout<<"是否修改英语成绩？（Enter键修改，否则请按其它键）:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cin>>grades;
		info->setEnglish(grades);
	}

	cout<<"是否修改程序设计成绩？（Enter键修改，否则请按其它键）:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cin>>grades;
		info->setProgramDesigned(grades);
	}

	cout<<"是否修改高等数学成绩？（Enter键修改，否则请按其它键）:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cin>>grades;
		info->setAdvancedMath(grades);
	}
}

void StudentManangeEngine::showAll()
{
	list<shared_ptr<AbstractStudent>> primary, middle,college;
	auto lss = engine->allOfStudent();
	for each (auto &val in lss){
		switch (val.first)
		{
		case Primary:
			primary.push_back(val.second);
			break;
		case Middle:
			middle.push_back(val.second);
			break;
		case College:
			college.push_back(val.second);
			break;
		default:
			break;
		}
	}
	cout<<"小学生信息："<<endl;
	if (primary.size() == 0){
		cout<<"无"<<endl;
	}
	else {
		PrimaryStudent::print_fmt();
		putchar('\n');
		for each (auto &val in primary){
			val->print();
			putchar('\n');
		}
	}
	cout<<"中学生信息："<<endl;
	if (middle.size() == 0){
		cout<<"无"<<endl;
	}
	else {
		MiddleStudent::print_fmt();
		putchar('\n');
		for each (auto &val in middle){
			val->print();
			putchar('\n');
		}
	}
	cout<<"大学生信息："<<endl;
	if (college.size() == 0){
		cout<<"无"<<endl;
	}
	else {
		CollegeStudent::print_fmt();
		putchar('\n');
		for each (auto &val in college){
			val->print();
			putchar('\n');
		}
	}
}

void StudentManangeEngine::remove()
{
	cout<<"请输入你要删除学生的学号:"<<endl;
	string number;
	cin>>number;
	auto ret = engine->query(number);
	if (ret.first == nil){
		cout<<"查无此人！"<<endl;
		return;
	}
	cout<<"警告！！此操作不可逆，请Enter键确认。输入其它键，取消此次操作！"<<endl;
	int rcc = _getch()-ascii_digit_begin;
	//13表示回车键
	if (rcc != 13){
		return;
	}
	engine->removeOneStudent(number);
}

void StudentManangeEngine::statistics()
{
	int ret;
label_s:
	cout<<"统计功能："<<endl;
	cout<<"请输入对应数字，进行统计"<<endl;
	cout<<"1:学生人数"<<endl;
	cout<<"2:学生总分"<<endl;
	cout<<"3:单科平均"<<endl;
	
	ret = _getch()-ascii_digit_begin;
	if (ret < 1 || ret > 3){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		goto label_s;
	}
	//统计各类别信息
	list<shared_ptr<AbstractStudent>> primary, middle,college;
	auto lss = engine->allOfStudent();
	for each (auto &val in lss){
		switch (val.first)
		{
		case Primary:
			primary.push_back(val.second);
			break;
		case Middle:
			middle.push_back(val.second);
			break;
		case College:
			college.push_back(val.second);
			break;
		default:
			break;
		}
	}
	switch (ret)
	{
	case 1:
		cout<<"小学总人数："<<primary.size()<<endl;
		cout<<"中学总人数："<<middle.size()<<endl;
		cout<<"大学总人数："<<college.size()<<endl;
		break;
	case 2:
		cout<<"总分："<<endl;
		cout<<"小学--------"<<endl;
		for each(auto &val in primary){
			cout<<val->getName()<<": "<<val->calc_sum();
		}
		cout<<"中学--------"<<endl;
		for each(auto &val in middle){
			cout<<val->getName()<<": "<<val->calc_sum();
		}
		cout<<"大学--------"<<endl;
		for each(auto &val in college){
			cout<<val->getName()<<": "<<val->calc_sum();
		}
		break;
	case 3:
		cout<<"单科平均分："<<endl;
		cout<<"小学--------"<<endl;
		if (primary.size()==0){
			cout<<"无"<<endl;
			break;
		}
		{
			float yinyu=0,shuxue=0,yuwen=0;
			shared_ptr<PrimaryStudent> vae;
			for each (auto &val in primary){
				vae = std::move(dynamic_pointer_cast<PrimaryStudent>(val));
				yinyu+=vae->getEnglish();
				shuxue+=vae->getMath();
				yuwen+=vae->getChinese();
			}
			cout<<"英语："<<yinyu/primary.size()<<endl;
			cout<<"数学："<<shuxue/primary.size()<<endl;
			cout<<"语文："<<yuwen/primary.size()<<endl;
		}
		cout<<"中学--------"<<endl;
		if (middle.size()==0){
			cout<<"无"<<endl;
			break;
		}
		{
			float yinyu=0,shuxue=0,yuwen=0,dili=0,lishi=0;
			shared_ptr<MiddleStudent> vae;
			for each (auto &val in middle){
				vae = std::move(dynamic_pointer_cast<MiddleStudent>(val));
				yinyu+=vae->getEnglish();
				shuxue+=vae->getMath();
				yuwen+=vae->getChinese();
				dili+=vae->getGeography();
				lishi+=vae->getHistory();
			}
			cout<<"英语："<<yinyu/middle.size()<<endl;
			cout<<"数学："<<shuxue/middle.size()<<endl;
			cout<<"语文："<<yuwen/middle.size()<<endl;
			cout<<"地理："<<dili/middle.size()<<endl;
			cout<<"历史："<<lishi/middle.size()<<endl;
		}
		cout<<"大学--------"<<endl;
		if (college.size()==0){
			cout<<"无"<<endl;
			break;
		}
		{
			float zhuanye=0,yinyu=0,sheji=0,shuxue=0;
			shared_ptr<CollegeStudent> vae;
			for each (auto &val in college){
				vae = std::move(dynamic_pointer_cast<CollegeStudent>(val));
				zhuanye+=vae->getMajor();
				yinyu+=vae->getEnglish();
				sheji+=vae->getProgramDesigned();
				shuxue+=vae->getAdvancedMath();
			}
			cout<<"专业："<<zhuanye/college.size()<<endl;
			cout<<"英语："<<yinyu/college.size()<<endl;
			cout<<"程序设计："<<sheji/college.size()<<endl;
			cout<<"高等数学："<<shuxue/college.size()<<endl;
		}
		break;
	default:break;
	}
}

void StudentManangeEngine::saveToFile()
{
	ofstream os;
	os.open(FileName,ios::out|ios::trunc);
	if (os.is_open() == false){
		cout<<"文件打开失败！"<<endl;
		return;
	}
	string str = engine->serialize();
	os << str;
	os.close();
	cout<<"操作成功！"<<endl;
}

void StudentManangeEngine::readFromFile()
{
	ifstream is;
	is.open(FileName, ios::in);
	if (is.is_open() == false){
		cout<<"文件打开失败！"<<endl;
		return;
	}
	string str;
	//求文件长度
	is.seekg(0,ios::end);
	int pos = (int)is.tellg().seekpos();
	//将文件指针至开始处
	is.seekg(ios::beg);
	str.resize(pos);
	//一次性读完
	is.read((char *)str.c_str(),pos);
	is.close();
	engine->antiSerialize(str);
	cout<<"操作成功！"<<endl;
}

void StudentManangeEngine::sort()
{
	int ret;
label_s:
	cout<<"排序功能："<<endl;
	cout<<"请输入对应数字，进行类别排序"<<endl;
	cout<<"1:总分"<<endl;
	cout<<"2:单科成绩"<<endl;

	ret = _getch()-ascii_digit_begin;
	if (ret < 1 || ret > 2){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		goto label_s;
	}
	//统计各类别信息
	list<shared_ptr<AbstractStudent>> primary, middle,college;
	auto lss = engine->allOfStudent();
	for each (auto &val in lss){
		switch (val.first)
		{
		case Primary:
			primary.push_back(val.second);
			break;
		case Middle:
			middle.push_back(val.second);
			break;
		case College:
			college.push_back(val.second);
			break;
		default:
			break;
		}
	}
	switch (ret)
	{
	case 1:
		cout<<"总分排序----"<<endl;
		cout<<"小学--------"<<endl;
		if (primary.size()==0){
			cout<<"无"<<endl;
		}
		else{
			primary.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<PrimaryStudent>(lhs)->calc_sum() > dynamic_pointer_cast<PrimaryStudent>(rhs)->calc_sum();
			});
			printf_s("%8s","总分");
			PrimaryStudent::print_fmt();
			putchar('\n');
			shared_ptr<PrimaryStudent> vae;
			for each (auto &val in primary){
				vae = std::move(dynamic_pointer_cast<PrimaryStudent>(val));
				printf_s("%8f",vae->calc_sum());
				vae->print();
				putchar('\n');
			}
		}

		cout<<"中学--------"<<endl;
		if (middle.size()==0){
			cout<<"无"<<endl;
		}
		else{
			middle.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<MiddleStudent>(lhs)->calc_sum() > dynamic_pointer_cast<MiddleStudent>(rhs)->calc_sum();
			});
			printf_s("%8s","总分");
			MiddleStudent::print_fmt();
			putchar('\n');
			shared_ptr<MiddleStudent> vae;
			for each (auto &val in middle){
				vae = std::move(dynamic_pointer_cast<MiddleStudent>(val));
				printf_s("%8f",vae->calc_sum());
				vae->print();
				putchar('\n');
			}
		}

		cout<<"大学--------"<<endl;
		if (college.size()==0){
			cout<<"无"<<endl;
		}
		else{
			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<CollegeStudent>(lhs)->calc_sum() > dynamic_pointer_cast<CollegeStudent>(rhs)->calc_sum();
			});
			printf_s("%8s","总分");
			CollegeStudent::print_fmt();
			putchar('\n');
			shared_ptr<CollegeStudent> vae;
			for each (auto &val in college){
				vae = std::move(dynamic_pointer_cast<CollegeStudent>(val));
				printf_s("%8f",vae->calc_sum());
				vae->print();
				putchar('\n');
			}
		}
		break;
	case 2:
		cout<<"单科成绩排序----"<<endl;
		cout<<"小学--------"<<endl;
		if (primary.size()==0){
			cout<<"无"<<endl;
		}
		else{
			shared_ptr<PrimaryStudent> vae;
			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<PrimaryStudent>(lhs)->getEnglish() > dynamic_pointer_cast<PrimaryStudent>(rhs)->getEnglish();
			});
			cout<<"英语单科："<<endl;
			PrimaryStudent::print_fmt();
			putchar('\n');
			for each (auto &val in primary){
				vae = std::move(dynamic_pointer_cast<PrimaryStudent>(val));
				vae->print();
				putchar('\n');
			}

			cout<<"数学单科："<<endl;
			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<PrimaryStudent>(lhs)->getMath() > dynamic_pointer_cast<PrimaryStudent>(rhs)->getMath();
			});
			PrimaryStudent::print_fmt();
			putchar('\n');
			for each (auto &val in primary){
				vae = std::move(dynamic_pointer_cast<PrimaryStudent>(val));
				vae->print();
				putchar('\n');
			}

			cout<<"语文单科："<<endl;
			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<PrimaryStudent>(lhs)->getChinese() > dynamic_pointer_cast<PrimaryStudent>(rhs)->getChinese();
			});
			PrimaryStudent::print_fmt();
			putchar('\n');
			for each (auto &val in primary){
				vae = std::move(dynamic_pointer_cast<PrimaryStudent>(val));
				vae->print();
				putchar('\n');
			}
		}

		cout<<"中学--------"<<endl;
		if (middle.size()==0){
			cout<<"无"<<endl;
		}
		else{
			shared_ptr<MiddleStudent> vae;
			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<MiddleStudent>(lhs)->getEnglish() > dynamic_pointer_cast<MiddleStudent>(rhs)->getEnglish();
			});
			cout<<"英语单科："<<endl;
			MiddleStudent::print_fmt();
			putchar('\n');
			for each (auto &val in middle){
				vae = std::move(dynamic_pointer_cast<MiddleStudent>(val));
				vae->print();
				putchar('\n');
			}

			cout<<"数学单科："<<endl;
			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<MiddleStudent>(lhs)->getMath() > dynamic_pointer_cast<MiddleStudent>(rhs)->getMath();
			});
			MiddleStudent::print_fmt();
			putchar('\n');
			for each (auto &val in middle){
				vae = std::move(dynamic_pointer_cast<MiddleStudent>(val));
				vae->print();
				putchar('\n');
			}

			cout<<"语文单科："<<endl;
			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<MiddleStudent>(lhs)->getChinese() > dynamic_pointer_cast<MiddleStudent>(rhs)->getChinese();
			});
			MiddleStudent::print_fmt();
			putchar('\n');
			for each (auto &val in middle){
				vae = std::move(dynamic_pointer_cast<MiddleStudent>(val));
				vae->print();
				putchar('\n');
			}
			cout<<"地理单科："<<endl;
			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<MiddleStudent>(lhs)->getGeography() > dynamic_pointer_cast<MiddleStudent>(rhs)->getGeography();
			});
			MiddleStudent::print_fmt();
			putchar('\n');
			for each (auto &val in middle){
				vae = std::move(dynamic_pointer_cast<MiddleStudent>(val));
				vae->print();
				putchar('\n');
			}

			cout<<"历史单科："<<endl;
			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<MiddleStudent>(lhs)->getHistory() > dynamic_pointer_cast<MiddleStudent>(rhs)->getHistory();
			});
			MiddleStudent::print_fmt();
			putchar('\n');
			for each (auto &val in middle){
				vae = std::move(dynamic_pointer_cast<MiddleStudent>(val));
				vae->print();
				putchar('\n');
			}
		}

		cout<<"大学--------"<<endl;
		if (college.size()==0){
			cout<<"无"<<endl;
		}
		else{
			shared_ptr<CollegeStudent> vae;
			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<CollegeStudent>(lhs)->getMajor() > dynamic_pointer_cast<CollegeStudent>(rhs)->getMajor();
			});
			cout<<"专业单科："<<endl;
			CollegeStudent::print_fmt();
			putchar('\n');
			for each (auto &val in college){
				vae = std::move(dynamic_pointer_cast<CollegeStudent>(val));
				vae->print();
				putchar('\n');
			}

			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<CollegeStudent>(lhs)->getEnglish() > dynamic_pointer_cast<CollegeStudent>(rhs)->getEnglish();
			});
			cout<<"英语单科："<<endl;
			CollegeStudent::print_fmt();
			putchar('\n');
			for each (auto &val in college){
				vae = std::move(dynamic_pointer_cast<CollegeStudent>(val));
				vae->print();
				putchar('\n');
			}

			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<CollegeStudent>(lhs)->getProgramDesigned() > dynamic_pointer_cast<CollegeStudent>(rhs)->getProgramDesigned();
			});
			cout<<"程序设计单科："<<endl;
			CollegeStudent::print_fmt();
			putchar('\n');
			for each (auto &val in college){
				vae = std::move(dynamic_pointer_cast<CollegeStudent>(val));
				vae->print();
				putchar('\n');
			}

			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<CollegeStudent>(lhs)->getAdvancedMath() > dynamic_pointer_cast<CollegeStudent>(rhs)->getAdvancedMath();
			});
			cout<<"高等数学单科："<<endl;
			CollegeStudent::print_fmt();
			putchar('\n');
			for each (auto &val in college){
				vae = std::move(dynamic_pointer_cast<CollegeStudent>(val));
				vae->print();
				putchar('\n');
			}
		}
		break;
	default: break;
	}
}

void StudentManangeEngine::add_base(AbstractStudent *info)
{
	string number, name;
	int sex;
	int age,Class;
	cout<<"请输入学号：";
label_number:
	cin>>number;
	if (engine->query(number).first != nil){
		cout<<"学号已存在，请重新输入学号"<<endl;
		goto label_number;
	}
	cout<<"请输入姓名：";
	cin>>name;

label_sex:
	cout<<"请输入"<<name<<"的性别（0：男 1：女）:";
	cin>>sex;
	if (sex < 0 || sex > 1){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		goto label_sex;
	}
label_age:
	cout<<"请输入"<<name<<"的年龄（>0）："<<endl;
	cin>>age;
	if (age <= 0){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		goto label_age;
	}

label_class:
	cout<<"请输入"<<name<<"的班级（>0）:"<<endl;
	cin>>Class;
	if (Class <= 0){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		goto label_class;
	}
	info->setName(number);
	info->setName(name);
	info->setSex((Stu_Sex)sex);
	info->setAge(age);
	info->setClass(Class);
}

void StudentManangeEngine::add_primary(PrimaryStudent *info)
{
	//添加基础信息
	add_base(info);
	float english,math,chinese;
label_english:
	cout<<"请输入"<<info->getName()<<"的英语成绩（0-100）:"<<endl;
	cin>>english;
	if (english < 0 || english > 100){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		goto label_english;
	}
label_math:
	cout<<"请输入"<<info->getName()<<"的数学成绩（0-100）:"<<endl;
	cin>>math;
	if (math < 0 || math > 100){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		goto label_math;
	}
label_chinese:
	cout<<"请输入"<<info->getName()<<"的语文成绩（0-100）:"<<endl;
	cin>>chinese;
	if (chinese < 0 || chinese > 100){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		goto label_chinese;
	}
	info->setEnglish(english);
	info->setMath(math);
	info->setChinese(chinese);
}

void StudentManangeEngine::add_middle(MiddleStudent *info)
{
	add_primary(info);
	float geography,history;
label_georaphy:
	cout<<"请输入"<<info->getName()<<"的地理成绩（0-100）:"<<endl;
	cin>>geography;
	if (geography < 0 || geography > 100){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		goto label_georaphy;
	}
label_history:
	cout<<"请输入"<<info->getName()<<"的历史成绩（0-100）:"<<endl;
	cin>>history;
	if (history < 0 || history > 100){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		goto label_history;
	}
}

void StudentManangeEngine::add_college(CollegeStudent *info)
{
	//添加基础信息
	add_base(info);
	float major;			//专业成绩
	float english;			//英语成绩
	float programDesigned;	//程序设计成绩
	float advancedMath;		//高数成绩
label_major:
	cout<<"请输入"<<info->getName()<<"的专业成绩（0-100）:"<<endl;
	cin>>major;
	if (major < 0 || major > 100){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		goto label_major;
	}
label_english:
	cout<<"请输入"<<info->getName()<<"的英语成绩（0-100）:"<<endl;
	cin>>english;
	if (english < 0 || english > 100){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		goto label_english;
	}
label_programDesigned:
	cout<<"请输入"<<info->getName()<<"的程序设计成绩（0-100）:"<<endl;
	cin>>programDesigned;
	if (programDesigned < 0 || programDesigned > 100){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		goto label_programDesigned;
	}
label_advancedMath:
	cout<<"请输入"<<info->getName()<<"的高数成绩（0-100）:"<<endl;
	cin>>advancedMath;
	if (advancedMath < 0 || advancedMath > 100){
		cout<<"请输入正确的数字！"<<endl;
		fflush(stdin);
		goto label_advancedMath;
	}
	info->setMajor(major);
	info->setEnglish(english);
	info->setProgramDesigned(programDesigned);
	info->setAdvancedMath(advancedMath);
}

int StudentManangeEngine::exec()
{
	int ret = 0;
	while (true){
		cout<<"学生成绩管理系统，输入对应数字进行操作"<<endl;
		cout<<"1:添加一个学生"<<endl;
		cout<<"2:查询一个学生"<<endl;
		cout<<"3:显示所有学生"<<endl;
		cout<<"4:删除一个学生"<<endl;
		cout<<"5:多功能统计"<<endl;
		cout<<"6:将学生信息保存到文件"<<endl;
		cout<<"7:从磁盘文件上读取学生信息到内存"<<endl;
		cout<<"8:排序"<<endl;
		cout<<"9:退出"<<endl;
		ret = _getch()-ascii_digit_begin;
		if (ret < 1 || ret > 9){
			cout<<"输入错误，请输入正确的数字"<<endl;
			fflush(stdin);
			Sleep(2000);
			system("cls");
			continue;
		}
		switch (ret)
		{
		case 1: this->add();		break;
		case 2: this->query();		break;
		case 3: this->showAll();	break;
		case 4: this->remove();		break;
		case 5: this->statistics();	break;
		case 6: this->saveToFile();	break;
		case 7: this->readFromFile();break;
		case 8: this->sort();		break;
		case 9: goto label_exit;	break;
		}
	}
label_exit:
	this->saveToFile();
	return ret;
}
