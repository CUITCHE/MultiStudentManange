#include "MiddleStudent.h"


MiddleStudent::MiddleStudent(const MiddleStudentInfo& info)
	:_info(new MiddleStudentInfo(info))
	,PrimaryStudent(info)
{
}

MiddleStudent::MiddleStudent(void)
	:_info(new MiddleStudentInfo())
{
}

void MiddleStudent::print_fmt()
{
	PrimaryStudent::print_fmt();
	printf_s("%8s%8s","����","��ʷ");
}

void MiddleStudent::print() const
{
	AbstractStudent::print();
//	printf_s("%s�ĳɼ���Ϣ��\n",this->getName());
	
	printf_s("%8f%8f",getGeography(),getHistory());
}
