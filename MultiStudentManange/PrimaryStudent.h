#pragma once
//
//Сѧ����
//�̳���AbstractStudentBaseInfo��������ѧ����̳�
//
#include "AbstractStudent.h"
class PrimaryStudentInfo:public StudentBaseInfo
{
public:
	float sum(){return english+math+chinese;}
	float average(){return sum()/3;}
	float english;		//Ӣ��ɼ�
	float math;			//��ѧ�ɼ�
	float chinese;		//���ĳɼ�
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

