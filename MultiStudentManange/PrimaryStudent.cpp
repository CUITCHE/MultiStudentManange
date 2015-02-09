#include "PrimaryStudent.h"


PrimaryStudent::PrimaryStudent(const PrimaryStudentInfo& info)
	:_info(new PrimaryStudentInfo(info))
	,AbstractStudent(info)
{
}

PrimaryStudent::PrimaryStudent(void)
	:_info(new PrimaryStudentInfo())
{
}

void PrimaryStudent::print_fmt()
{
	AbstractStudent::print_fmt();
	printf_s("%8s%8s%8s","Ó¢Óï","ÊıÑ§","ÓïÎÄ");
}

void PrimaryStudent::print() const
{
	AbstractStudent::print();
	printf_s("%8f%8f%8f",getEnglish(),getMath(),getChinese());
}
