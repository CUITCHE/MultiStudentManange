#pragma once
//
//学生信息虚基类
//子类须实现两个纯虚函数
//
#include <string>
#include <memory>
using std::unique_ptr;
using std::string;
enum Stu_Sex{
	Male,
	Female
};
#define setter(Type,variable, name) void set##name(const Type val){this->variable = val;}
#define getter(Type,variable,name) const Type get##name()const{return variable;}
#define get_setter(Type,variable, name)\
	setter(Type,variable, name)\
	getter(Type,variable,name)

class StudentBaseInfo
{
public:
	virtual float sum(){return 0.0f;}
	virtual float average(){return 0.0f;}
	string stu_no;		//学号
	string stu_name;	//姓名
	Stu_Sex stu_sex;	//性别
	size_t stu_age;		//年龄
	size_t stu_class;	//班级 如：20121，表示2012级1班
};

class AbstractStudent
{
public:
	AbstractStudent(const StudentBaseInfo& info);
	AbstractStudent(void);
	virtual ~AbstractStudent(void){}
	//计算总成绩
	virtual float calc_sum() = 0;
	//计算平均成绩
	virtual float calc_average() = 0;
	//打印输出格式信息
	static void print_fmt();
	virtual void print()const;
	get_setter(string&, _info->stu_no, Number);
	get_setter(string&, _info->stu_name, Name);
	get_setter(Stu_Sex, _info->stu_sex, Sex);
	get_setter(size_t, _info->stu_age, Age);
	get_setter(size_t, _info->stu_class, Class);
protected:
	unique_ptr<StudentBaseInfo> _info;
};

