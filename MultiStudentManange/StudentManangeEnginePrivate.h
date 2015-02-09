#pragma once
#include <list>
#include <memory>
#include <sstream>
#include <utility>
#include <exception>
using namespace std;


class AbstractStudent;
class PrimaryStudent;
class MiddleStudent;
class CollegeStudent;

enum StudentType{
	nil,
	Primary,
	Middle,
	College
};
typedef pair<StudentType,shared_ptr<AbstractStudent>> StudentTypeMapBaseInfo;
class StudentManangeEnginePrivate
{
	friend class StudentManangeEngine;
	StudentManangeEnginePrivate(void){}
	~StudentManangeEnginePrivate(void){}

	list<StudentTypeMapBaseInfo> students_list;		//存放所有学生
	ostringstream oss;


	//增加一个学生，小学生，中学生，大学生均可
	//若学号重复，则添加失败，返回false，否则返回true;
	bool addStudent(const StudentTypeMapBaseInfo& entity);

	//查询，传入字符串（学号、姓名均可）
	//如果未找到，StudentType=nil
	StudentTypeMapBaseInfo query(const string &queryString);


	//返回所有学生信息
	const list<StudentTypeMapBaseInfo>& allOfStudent();

	//根据学号删除一个学生
	//ret：false 未找到
	bool removeOneStudent(const string &number);

	//将学生信息序列化，用于文件存取操作
	//可能会抛出异常
	//ret：返回一个string
	string serialize();

	//此方法不能被外界调用
	//序列化一个PrimaryStudent实体
	void serialize_impl(shared_ptr<PrimaryStudent> info, string &serialize_str);

	//此方法不能被外界调用
	//序列化一个MiddleStudent实体
	void serialize_impl(shared_ptr<MiddleStudent> info, string &serialize_str);

	//此方法不能被外界调用
	//序列化一个CollegeStudent实体
	void serialize_impl(shared_ptr<CollegeStudent> info, string &serialize_str);

	//此方法不能被外界调用
	//对基础信息序列化
	void serialize_impl(AbstractStudent *info, string& serialize_str);

	//将序列化string转化为对应的学生实体，
	//与serialize()是相反操作
	void antiSerialize(const string& serialize_str);

	void antiSerialize_impl(shared_ptr<PrimaryStudent> info, stringstream &ss);
	void antiSerialize_impl(shared_ptr<MiddleStudent> info, stringstream &ss);
	void antiSerialize_impl(shared_ptr<CollegeStudent> info, stringstream &ss);
	void antiSerialize_impl(AbstractStudent *info, stringstream &ss);
};

