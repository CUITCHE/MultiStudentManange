#pragma once
//
//��ѧ���࣬�̳���AbstractStudentBaseInfo
//
#include "AbstractStudent.h"
class CollegeStudentInfo: public StudentBaseInfo
{
public:
	virtual float sum(){return major+english+programDesigned+advancedMath;}
	virtual float average(){return sum()/4;}
	float major;			//רҵ�ɼ�
	float english;			//Ӣ��ɼ�
	float programDesigned;	//������Ƴɼ�
	float advancedMath;		//�����ɼ�
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

