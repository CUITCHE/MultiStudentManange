#include "CollegeStudent.h"

CollegeStudent::CollegeStudent(const CollegeStudentInfo& info)
	:_info(new CollegeStudentInfo(info))
	,AbstractStudent(info)
{
}

CollegeStudent::CollegeStudent(void)
	:_info(new CollegeStudentInfo())
{
}

void CollegeStudent::print_fmt()
{
	AbstractStudent::print_fmt();
	printf_s("%8s%8s%8s%8s","专业","英语","程序设计","高等数学");
}

void CollegeStudent::print() const
{
	AbstractStudent::print();
	printf_s("%8f%8f%8f%8f",getMajor(),getEnglish(),getProgramDesigned(),getAdvancedMath());
}
