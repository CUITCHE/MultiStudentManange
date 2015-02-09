#include "AbstractStudent.h"

AbstractStudent::AbstractStudent(const StudentBaseInfo& info)
	:_info(new StudentBaseInfo(info))
{
}

AbstractStudent::AbstractStudent(void)
	:_info(new StudentBaseInfo())
{
}

void AbstractStudent::print_fmt()
{
	printf_s("%8s%8s%8s%8s%8s","学号","姓名","性别","年龄","班级");
}

void AbstractStudent::print() const
{
	printf_s("%8s%8s%8s%8ud%8ud",getNumber(),getName(),getSex()==Male ? "男":"女",getAge(),getClass());
}
