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
	cout<<"���ѧ����¼ - �밴��Ų�����"<<endl;
	cout<<"1:���Сѧ����Ϣ"<<endl;
	cout<<"2:�����ѧ����Ϣ"<<endl;
	cout<<"3:��Ӵ�ѧ����Ϣ"<<endl;
	
	num = _getch()-ascii_digit_begin;
	if (num > 3 || num < 1){
		cout<<"��������ȷ�����֣�"<<endl;
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
		cout<<"δ֪���󣡳����˳�"<<endl;
		_getch();
		exit(-1);
	}
	engine->addStudent(make_pair((StudentType)num,info));
}

void StudentManangeEngine::query()
{
	cout<<"������ѧ�Ż����������в�ѯ:"<<endl;
	string query_str;
	cin>>query_str;
	auto ret = engine->query(query_str);
	if (ret.first == nil){
		cout<<"δ�ҵ������Ϣ���밴���������..."<<endl;
		_getch();
		return;
	}
	//��ӡѧ����Ϣ
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
	cout<<"����Ҫ�༭������Ϣ��������0�������밴��������أ�"<<endl;
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
		cout<<"Сѧ����Ϣ�޸ģ�"<<endl;
		{
			edit(info.second.get());
			shared_ptr<PrimaryStudent> vae = std::move(dynamic_pointer_cast<PrimaryStudent>(info.second));
			edit_p(vae);
		}
		break;
	case Middle:
		cout<<"��ѧ����Ϣ�޸ģ�"<<endl;
		{
			edit(info.second.get());
			shared_ptr<MiddleStudent> vae = std::move(dynamic_pointer_cast<MiddleStudent>(info.second));
			edit_m(vae);
		}
		break;
	case College:
		cout<<"��ѧ����Ϣ�޸ģ�"<<endl;
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
	cout<<"�Ƿ��޸�ѧ�ţ���Enter���޸ģ������밴��������:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cout<<"�������µ�ѧ�ţ�"<<endl;
		string no;
		cin>>no;
		while(engine->query(no).first != nil){
			cout<<"ѧ�ţ�"<<no<<"�Ѵ���"<<"���������룡"<<endl;
			cout<<"�������µ�ѧ�ţ�"<<endl;
			string no;
			cin>>no;
		}
		info->setNumber(no);
	}

	cout<<"�Ƿ��޸���������Enter���޸ģ������밴��������:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		string name;
		cout<<"����������"<<endl;
		cin>>name;
		info->setName(name);
	}

	cout<<"�Ƿ��޸��Ա𣿣�Enter���޸ģ������밴��������:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cout<<"�������Ա���루0���� ��0��Ů����"<<endl;
		isno = _getch()-ascii_digit_begin;
		if (isno == 0){
			info->setSex(Male);
		}
		else {
			info->setSex(Female);
		}
	}

	cout<<"�Ƿ��޸����䣿��Enter���޸ģ������밴��������:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cout<<"���������䣺"<<endl;
		cin>>isno;
		info->setAge(isno);
	}

	cout<<"�Ƿ��޸İ༶����Enter���޸ģ������밴��������:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cout<<"������༶���磺201201����"<<endl;
		cin>>isno;
		info->setClass(isno);
		fflush(stdin);
	}
}

void StudentManangeEngine::edit_p(shared_ptr<PrimaryStudent> info)
{
	float grades;
	cout<<"�Ƿ��޸�Ӣ��ɼ�����Enter���޸ģ������밴��������:"<<endl;
	int isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cin>>grades;
		info->setEnglish(grades);
	}
	cout<<"�Ƿ��޸���ѧ�ɼ�����Enter���޸ģ������밴��������:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cin>>grades;
		info->setMath(grades);
	}
	cout<<"�Ƿ��޸����ĳɼ�����Enter���޸ģ������밴��������:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cin>>grades;
		info->setChinese(grades);
	}
}

void StudentManangeEngine::edit_m(shared_ptr<MiddleStudent> info)
{
	edit_p(dynamic_pointer_cast<PrimaryStudent>(info));
	cout<<"�Ƿ��޸ĵ���ɼ�����Enter���޸ģ������밴��������:"<<endl;
	int isno = _getch()-ascii_digit_begin;
	float grades;
	if (isno == 13){
		cin>>grades;
		info->setGeography(grades);
	}
	cout<<"�Ƿ��޸���ʷ�ɼ�����Enter���޸ģ������밴��������:"<<endl;
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
	cout<<"�Ƿ��޸�רҵ�ɼ�����Enter���޸ģ������밴��������:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cin>>grades;
		info->setMajor(grades);
	}

	cout<<"�Ƿ��޸�Ӣ��ɼ�����Enter���޸ģ������밴��������:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cin>>grades;
		info->setEnglish(grades);
	}

	cout<<"�Ƿ��޸ĳ�����Ƴɼ�����Enter���޸ģ������밴��������:"<<endl;
	isno = _getch()-ascii_digit_begin;
	if (isno == 13){
		cin>>grades;
		info->setProgramDesigned(grades);
	}

	cout<<"�Ƿ��޸ĸߵ���ѧ�ɼ�����Enter���޸ģ������밴��������:"<<endl;
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
	cout<<"Сѧ����Ϣ��"<<endl;
	if (primary.size() == 0){
		cout<<"��"<<endl;
	}
	else {
		PrimaryStudent::print_fmt();
		putchar('\n');
		for each (auto &val in primary){
			val->print();
			putchar('\n');
		}
	}
	cout<<"��ѧ����Ϣ��"<<endl;
	if (middle.size() == 0){
		cout<<"��"<<endl;
	}
	else {
		MiddleStudent::print_fmt();
		putchar('\n');
		for each (auto &val in middle){
			val->print();
			putchar('\n');
		}
	}
	cout<<"��ѧ����Ϣ��"<<endl;
	if (college.size() == 0){
		cout<<"��"<<endl;
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
	cout<<"��������Ҫɾ��ѧ����ѧ��:"<<endl;
	string number;
	cin>>number;
	auto ret = engine->query(number);
	if (ret.first == nil){
		cout<<"���޴��ˣ�"<<endl;
		return;
	}
	cout<<"���棡���˲��������棬��Enter��ȷ�ϡ�������������ȡ���˴β�����"<<endl;
	int rcc = _getch()-ascii_digit_begin;
	//13��ʾ�س���
	if (rcc != 13){
		return;
	}
	engine->removeOneStudent(number);
}

void StudentManangeEngine::statistics()
{
	int ret;
label_s:
	cout<<"ͳ�ƹ��ܣ�"<<endl;
	cout<<"�������Ӧ���֣�����ͳ��"<<endl;
	cout<<"1:ѧ������"<<endl;
	cout<<"2:ѧ���ܷ�"<<endl;
	cout<<"3:����ƽ��"<<endl;
	
	ret = _getch()-ascii_digit_begin;
	if (ret < 1 || ret > 3){
		cout<<"��������ȷ�����֣�"<<endl;
		fflush(stdin);
		goto label_s;
	}
	//ͳ�Ƹ������Ϣ
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
		cout<<"Сѧ��������"<<primary.size()<<endl;
		cout<<"��ѧ��������"<<middle.size()<<endl;
		cout<<"��ѧ��������"<<college.size()<<endl;
		break;
	case 2:
		cout<<"�ܷ֣�"<<endl;
		cout<<"Сѧ--------"<<endl;
		for each(auto &val in primary){
			cout<<val->getName()<<": "<<val->calc_sum();
		}
		cout<<"��ѧ--------"<<endl;
		for each(auto &val in middle){
			cout<<val->getName()<<": "<<val->calc_sum();
		}
		cout<<"��ѧ--------"<<endl;
		for each(auto &val in college){
			cout<<val->getName()<<": "<<val->calc_sum();
		}
		break;
	case 3:
		cout<<"����ƽ���֣�"<<endl;
		cout<<"Сѧ--------"<<endl;
		if (primary.size()==0){
			cout<<"��"<<endl;
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
			cout<<"Ӣ�"<<yinyu/primary.size()<<endl;
			cout<<"��ѧ��"<<shuxue/primary.size()<<endl;
			cout<<"���ģ�"<<yuwen/primary.size()<<endl;
		}
		cout<<"��ѧ--------"<<endl;
		if (middle.size()==0){
			cout<<"��"<<endl;
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
			cout<<"Ӣ�"<<yinyu/middle.size()<<endl;
			cout<<"��ѧ��"<<shuxue/middle.size()<<endl;
			cout<<"���ģ�"<<yuwen/middle.size()<<endl;
			cout<<"����"<<dili/middle.size()<<endl;
			cout<<"��ʷ��"<<lishi/middle.size()<<endl;
		}
		cout<<"��ѧ--------"<<endl;
		if (college.size()==0){
			cout<<"��"<<endl;
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
			cout<<"רҵ��"<<zhuanye/college.size()<<endl;
			cout<<"Ӣ�"<<yinyu/college.size()<<endl;
			cout<<"������ƣ�"<<sheji/college.size()<<endl;
			cout<<"�ߵ���ѧ��"<<shuxue/college.size()<<endl;
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
		cout<<"�ļ���ʧ�ܣ�"<<endl;
		return;
	}
	string str = engine->serialize();
	os << str;
	os.close();
	cout<<"�����ɹ���"<<endl;
}

void StudentManangeEngine::readFromFile()
{
	ifstream is;
	is.open(FileName, ios::in);
	if (is.is_open() == false){
		cout<<"�ļ���ʧ�ܣ�"<<endl;
		return;
	}
	string str;
	//���ļ�����
	is.seekg(0,ios::end);
	int pos = (int)is.tellg().seekpos();
	//���ļ�ָ������ʼ��
	is.seekg(ios::beg);
	str.resize(pos);
	//һ���Զ���
	is.read((char *)str.c_str(),pos);
	is.close();
	engine->antiSerialize(str);
	cout<<"�����ɹ���"<<endl;
}

void StudentManangeEngine::sort()
{
	int ret;
label_s:
	cout<<"�����ܣ�"<<endl;
	cout<<"�������Ӧ���֣������������"<<endl;
	cout<<"1:�ܷ�"<<endl;
	cout<<"2:���Ƴɼ�"<<endl;

	ret = _getch()-ascii_digit_begin;
	if (ret < 1 || ret > 2){
		cout<<"��������ȷ�����֣�"<<endl;
		fflush(stdin);
		goto label_s;
	}
	//ͳ�Ƹ������Ϣ
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
		cout<<"�ܷ�����----"<<endl;
		cout<<"Сѧ--------"<<endl;
		if (primary.size()==0){
			cout<<"��"<<endl;
		}
		else{
			primary.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<PrimaryStudent>(lhs)->calc_sum() > dynamic_pointer_cast<PrimaryStudent>(rhs)->calc_sum();
			});
			printf_s("%8s","�ܷ�");
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

		cout<<"��ѧ--------"<<endl;
		if (middle.size()==0){
			cout<<"��"<<endl;
		}
		else{
			middle.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<MiddleStudent>(lhs)->calc_sum() > dynamic_pointer_cast<MiddleStudent>(rhs)->calc_sum();
			});
			printf_s("%8s","�ܷ�");
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

		cout<<"��ѧ--------"<<endl;
		if (college.size()==0){
			cout<<"��"<<endl;
		}
		else{
			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<CollegeStudent>(lhs)->calc_sum() > dynamic_pointer_cast<CollegeStudent>(rhs)->calc_sum();
			});
			printf_s("%8s","�ܷ�");
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
		cout<<"���Ƴɼ�����----"<<endl;
		cout<<"Сѧ--------"<<endl;
		if (primary.size()==0){
			cout<<"��"<<endl;
		}
		else{
			shared_ptr<PrimaryStudent> vae;
			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<PrimaryStudent>(lhs)->getEnglish() > dynamic_pointer_cast<PrimaryStudent>(rhs)->getEnglish();
			});
			cout<<"Ӣ�ﵥ�ƣ�"<<endl;
			PrimaryStudent::print_fmt();
			putchar('\n');
			for each (auto &val in primary){
				vae = std::move(dynamic_pointer_cast<PrimaryStudent>(val));
				vae->print();
				putchar('\n');
			}

			cout<<"��ѧ���ƣ�"<<endl;
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

			cout<<"���ĵ��ƣ�"<<endl;
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

		cout<<"��ѧ--------"<<endl;
		if (middle.size()==0){
			cout<<"��"<<endl;
		}
		else{
			shared_ptr<MiddleStudent> vae;
			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<MiddleStudent>(lhs)->getEnglish() > dynamic_pointer_cast<MiddleStudent>(rhs)->getEnglish();
			});
			cout<<"Ӣ�ﵥ�ƣ�"<<endl;
			MiddleStudent::print_fmt();
			putchar('\n');
			for each (auto &val in middle){
				vae = std::move(dynamic_pointer_cast<MiddleStudent>(val));
				vae->print();
				putchar('\n');
			}

			cout<<"��ѧ���ƣ�"<<endl;
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

			cout<<"���ĵ��ƣ�"<<endl;
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
			cout<<"�����ƣ�"<<endl;
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

			cout<<"��ʷ���ƣ�"<<endl;
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

		cout<<"��ѧ--------"<<endl;
		if (college.size()==0){
			cout<<"��"<<endl;
		}
		else{
			shared_ptr<CollegeStudent> vae;
			college.sort([](const shared_ptr<AbstractStudent> &lhs,const shared_ptr<AbstractStudent> &rhs){
				return dynamic_pointer_cast<CollegeStudent>(lhs)->getMajor() > dynamic_pointer_cast<CollegeStudent>(rhs)->getMajor();
			});
			cout<<"רҵ���ƣ�"<<endl;
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
			cout<<"Ӣ�ﵥ�ƣ�"<<endl;
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
			cout<<"������Ƶ��ƣ�"<<endl;
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
			cout<<"�ߵ���ѧ���ƣ�"<<endl;
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
	cout<<"������ѧ�ţ�";
label_number:
	cin>>number;
	if (engine->query(number).first != nil){
		cout<<"ѧ���Ѵ��ڣ�����������ѧ��"<<endl;
		goto label_number;
	}
	cout<<"������������";
	cin>>name;

label_sex:
	cout<<"������"<<name<<"���Ա�0���� 1��Ů��:";
	cin>>sex;
	if (sex < 0 || sex > 1){
		cout<<"��������ȷ�����֣�"<<endl;
		fflush(stdin);
		goto label_sex;
	}
label_age:
	cout<<"������"<<name<<"�����䣨>0����"<<endl;
	cin>>age;
	if (age <= 0){
		cout<<"��������ȷ�����֣�"<<endl;
		fflush(stdin);
		goto label_age;
	}

label_class:
	cout<<"������"<<name<<"�İ༶��>0��:"<<endl;
	cin>>Class;
	if (Class <= 0){
		cout<<"��������ȷ�����֣�"<<endl;
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
	//��ӻ�����Ϣ
	add_base(info);
	float english,math,chinese;
label_english:
	cout<<"������"<<info->getName()<<"��Ӣ��ɼ���0-100��:"<<endl;
	cin>>english;
	if (english < 0 || english > 100){
		cout<<"��������ȷ�����֣�"<<endl;
		fflush(stdin);
		goto label_english;
	}
label_math:
	cout<<"������"<<info->getName()<<"����ѧ�ɼ���0-100��:"<<endl;
	cin>>math;
	if (math < 0 || math > 100){
		cout<<"��������ȷ�����֣�"<<endl;
		fflush(stdin);
		goto label_math;
	}
label_chinese:
	cout<<"������"<<info->getName()<<"�����ĳɼ���0-100��:"<<endl;
	cin>>chinese;
	if (chinese < 0 || chinese > 100){
		cout<<"��������ȷ�����֣�"<<endl;
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
	cout<<"������"<<info->getName()<<"�ĵ���ɼ���0-100��:"<<endl;
	cin>>geography;
	if (geography < 0 || geography > 100){
		cout<<"��������ȷ�����֣�"<<endl;
		fflush(stdin);
		goto label_georaphy;
	}
label_history:
	cout<<"������"<<info->getName()<<"����ʷ�ɼ���0-100��:"<<endl;
	cin>>history;
	if (history < 0 || history > 100){
		cout<<"��������ȷ�����֣�"<<endl;
		fflush(stdin);
		goto label_history;
	}
}

void StudentManangeEngine::add_college(CollegeStudent *info)
{
	//��ӻ�����Ϣ
	add_base(info);
	float major;			//רҵ�ɼ�
	float english;			//Ӣ��ɼ�
	float programDesigned;	//������Ƴɼ�
	float advancedMath;		//�����ɼ�
label_major:
	cout<<"������"<<info->getName()<<"��רҵ�ɼ���0-100��:"<<endl;
	cin>>major;
	if (major < 0 || major > 100){
		cout<<"��������ȷ�����֣�"<<endl;
		fflush(stdin);
		goto label_major;
	}
label_english:
	cout<<"������"<<info->getName()<<"��Ӣ��ɼ���0-100��:"<<endl;
	cin>>english;
	if (english < 0 || english > 100){
		cout<<"��������ȷ�����֣�"<<endl;
		fflush(stdin);
		goto label_english;
	}
label_programDesigned:
	cout<<"������"<<info->getName()<<"�ĳ�����Ƴɼ���0-100��:"<<endl;
	cin>>programDesigned;
	if (programDesigned < 0 || programDesigned > 100){
		cout<<"��������ȷ�����֣�"<<endl;
		fflush(stdin);
		goto label_programDesigned;
	}
label_advancedMath:
	cout<<"������"<<info->getName()<<"�ĸ����ɼ���0-100��:"<<endl;
	cin>>advancedMath;
	if (advancedMath < 0 || advancedMath > 100){
		cout<<"��������ȷ�����֣�"<<endl;
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
		cout<<"ѧ���ɼ�����ϵͳ�������Ӧ���ֽ��в���"<<endl;
		cout<<"1:���һ��ѧ��"<<endl;
		cout<<"2:��ѯһ��ѧ��"<<endl;
		cout<<"3:��ʾ����ѧ��"<<endl;
		cout<<"4:ɾ��һ��ѧ��"<<endl;
		cout<<"5:�๦��ͳ��"<<endl;
		cout<<"6:��ѧ����Ϣ���浽�ļ�"<<endl;
		cout<<"7:�Ӵ����ļ��϶�ȡѧ����Ϣ���ڴ�"<<endl;
		cout<<"8:����"<<endl;
		cout<<"9:�˳�"<<endl;
		ret = _getch()-ascii_digit_begin;
		if (ret < 1 || ret > 9){
			cout<<"���������������ȷ������"<<endl;
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
