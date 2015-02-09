#pragma once
//
//中学生类，继承自PrimaryStudent
//
#include "PrimaryStudent.h"
class MiddleStudentInfo: public PrimaryStudentInfo
{
public:
	virtual float sum(){return PrimaryStudentInfo::sum()+history+geography;}
	virtual float average(){return (PrimaryStudentInfo::average()+sum()/2)/2;}
	float history;		//历史成绩
	float geography;
};
class MiddleStudent :public PrimaryStudent
{
public:
	MiddleStudent(const MiddleStudentInfo& info);
	MiddleStudent(void);
	virtual ~MiddleStudent(void){}
	virtual float calc_sum(){return _info->sum();}
	virtual float calc_average(){return _info->average();}
	static void print_fmt();
	virtual void print()const;
	get_setter(float,_info->history,History);
	get_setter(float,_info->geography,Geography);
private:
	unique_ptr<MiddleStudentInfo> _info;
};

