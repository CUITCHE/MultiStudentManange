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

	list<StudentTypeMapBaseInfo> students_list;		//�������ѧ��
	ostringstream oss;


	//����һ��ѧ����Сѧ������ѧ������ѧ������
	//��ѧ���ظ��������ʧ�ܣ�����false�����򷵻�true;
	bool addStudent(const StudentTypeMapBaseInfo& entity);

	//��ѯ�������ַ�����ѧ�š��������ɣ�
	//���δ�ҵ���StudentType=nil
	StudentTypeMapBaseInfo query(const string &queryString);


	//��������ѧ����Ϣ
	const list<StudentTypeMapBaseInfo>& allOfStudent();

	//����ѧ��ɾ��һ��ѧ��
	//ret��false δ�ҵ�
	bool removeOneStudent(const string &number);

	//��ѧ����Ϣ���л��������ļ���ȡ����
	//���ܻ��׳��쳣
	//ret������һ��string
	string serialize();

	//�˷������ܱ�������
	//���л�һ��PrimaryStudentʵ��
	void serialize_impl(shared_ptr<PrimaryStudent> info, string &serialize_str);

	//�˷������ܱ�������
	//���л�һ��MiddleStudentʵ��
	void serialize_impl(shared_ptr<MiddleStudent> info, string &serialize_str);

	//�˷������ܱ�������
	//���л�һ��CollegeStudentʵ��
	void serialize_impl(shared_ptr<CollegeStudent> info, string &serialize_str);

	//�˷������ܱ�������
	//�Ի�����Ϣ���л�
	void serialize_impl(AbstractStudent *info, string& serialize_str);

	//�����л�stringת��Ϊ��Ӧ��ѧ��ʵ�壬
	//��serialize()���෴����
	void antiSerialize(const string& serialize_str);

	void antiSerialize_impl(shared_ptr<PrimaryStudent> info, stringstream &ss);
	void antiSerialize_impl(shared_ptr<MiddleStudent> info, stringstream &ss);
	void antiSerialize_impl(shared_ptr<CollegeStudent> info, stringstream &ss);
	void antiSerialize_impl(AbstractStudent *info, stringstream &ss);
};

