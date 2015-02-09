#pragma once
//
//大学生类，继承自AbstractStudentBaseInfo
//
#include "AbstractStudent.h"
class CollegeStudentInfo: public StudentBaseInfo
{
public:
	virtual float sum(){return major+english+programDesigned+advancedMath;}
	virtual float average(){return sum()/4;}
	float major;			//专业成绩
	float english;			//英语成绩
	float programDesigned;	//程序设计成绩
	float advancedMath;		//高数成绩
};
class CollegeStudent :public AbstractStudent
{
public:
	CollegeStudent(const CollegeStudentInfo& info);
	CollegeStudent(void);
	virtual ~CollegeStudent(void){}
	static void print_fmt();
	virtual void print()const;
	virtual float calc_sum(){return _info->sum();}
	virtual float calc_average(){return _info->average();}

	get_setter(float, _info->major, Major);
	get_setter(float, _info->english, English);
	get_setter(float, _info->programDesigned, ProgramDesigned);
	get_setter(float, _info->advancedMath, AdvancedMath);
private:
	unique_ptr<CollegeStudentInfo> _info;
};

