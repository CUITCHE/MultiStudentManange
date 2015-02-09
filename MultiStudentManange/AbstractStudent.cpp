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
	printf_s("%8s%8s%8s%8s%8s","ѧ��","����","�Ա�","����","�༶");
}

void AbstractStudent::print() const
{
	printf_s("%8s%8s%8s%8ud%8ud",getNumber(),getName(),getSex()==Male ? "��":"Ů",getAge(),getClass());
}
