#pragma once
//
//小学生类
//继承自AbstractStudentBaseInfo，将被中学生类继承
//
#include "AbstractStudent.h"
class PrimaryStudentInfo:public StudentBaseInfo
{
public:
	float sum(){return english+math+chinese;}
	float average(){return sum()/3;}
	float english;		//英语成绩
	float math;			//数学成绩
	float chinese;		//语文成绩
};

class PrimaryStudent :public AbstractStudent
{
public:
	PrimaryStudent(const PrimaryStudentInfo& info);
	PrimaryStudent(void);
	virtual ~PrimaryStudent(void){}
	virtual float calc_sum(){return _info->sum();}
	virtual float calc_average(){return _info->average();}
	static void print_fmt();
	virtual void print()const;
	get_setter(float,_info->english,English);
	get_setter(float,_info->math,Math);
	get_setter(float,_info->chinese,Chinese);
protected:
	unique_ptr<PrimaryStudentInfo> _info;
};

