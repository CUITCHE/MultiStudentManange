#include "StudentManangeEnginePrivate.h"
#include "MiddleStudent.h"
#include "CollegeStudent.h"

bool StudentManangeEnginePrivate::addStudent(const StudentTypeMapBaseInfo& entity)
{
	if (query(entity.second->getNumber()).first == nil){
		students_list.push_back(entity);
		return true;
	}
	return false;
}

StudentTypeMapBaseInfo StudentManangeEnginePrivate::query(const string &queryString)
{
	StudentTypeMapBaseInfo ret;
	ret.first = nil;
	for each(auto &val in students_list){
		if (queryString == val.second->getName() || queryString == val.second->getNumber()){
			ret = val;
			break;
		}
	}
	return ret;
}

const list<StudentTypeMapBaseInfo>& StudentManangeEnginePrivate::allOfStudent()
{
	return students_list;
}

bool StudentManangeEnginePrivate::removeOneStudent(const string &number)
{
	auto size = students_list.size();
	students_list.remove_if([&](const StudentTypeMapBaseInfo &val){return number==val.second->getNumber();});
	return size != students_list.size();
}

string StudentManangeEnginePrivate::serialize()
{
	string serialize_str;
	for each(auto &val in students_list){
		oss << (int)val.first << " ";
		switch (val.first)
		{
		case Primary:
			serialize_impl(dynamic_pointer_cast<PrimaryStudent>(val.second),serialize_str);
			break;
		case Middle:
			serialize_impl(dynamic_pointer_cast<MiddleStudent>(val.second),serialize_str);
			break;
		case College:
			serialize_impl(dynamic_pointer_cast<CollegeStudent>(val.second),serialize_str);
			break;
		default:
			throw exception("logic error");
			break;
		}
	}
	//移出最后一个空格
	if (serialize_str.size() > 0){
		serialize_str.pop_back();
	}
	return serialize_str;
}

void StudentManangeEnginePrivate::serialize_impl(shared_ptr<PrimaryStudent> info, string &serialize_str)
{
	if (!info){
		return;
	}
	serialize_impl(info.get(),serialize_str);
	oss << info->getEnglish() << " " << info->getMath() << " " << info->getChinese() << "";
	serialize_str.append(oss.str());
	//清空缓冲区
	oss.str("");
}

void StudentManangeEnginePrivate::serialize_impl(shared_ptr<MiddleStudent> info, string &serialize_str)
{
	if (!info){
		return;
	}
	//写入父类——小学生类的成绩
	serialize_impl(dynamic_pointer_cast<PrimaryStudent>(info), serialize_str);
	oss << info->getGeography() << " " << info->getHistory() << " ";
	serialize_str.append(oss.str());
	//清空缓冲区
	oss.str("");
}

void StudentManangeEnginePrivate::serialize_impl(shared_ptr<CollegeStudent> info, string &serialize_str)
{
	if (!info){
		return;
	}
	serialize_impl(info.get(),serialize_str);
	oss << info->getMajor() << " " << info->getEnglish() << " " << info->getProgramDesigned() << " "
		<< info->getAdvancedMath() << " ";
	serialize_str.append(oss.str());
	//清空缓冲区
	oss.str("");
}

void StudentManangeEnginePrivate::serialize_impl(AbstractStudent *info, string& serialize_str)
{
	if (info == nullptr){
		return;
	}
	oss << info->getName() << " " << info->getNumber() <<" " << (int)info->getSex() << " "
		<< info->getAge() << " " << info->getClass() << " ";
	serialize_str.append(oss.str());
	//清空缓冲区
	oss.str("");
}

void StudentManangeEnginePrivate::antiSerialize(const string& serialize_str)
{
	//先读StudentType
	//再读AbstractStudent
	//最后根据StudentType读取相应的AbstractStudent子类的数据
	stringstream ssm(serialize_str);
	int s_type;
	StudentTypeMapBaseInfo infoOne;
	while (ssm.tellp()){
		ssm >> s_type;
		infoOne.first = (StudentType)s_type;
		switch (infoOne.first)
		{
		case Primary:
			infoOne.second.reset(new PrimaryStudent());
			antiSerialize_impl(dynamic_pointer_cast<PrimaryStudent>(infoOne.second), ssm);
			break;
		case Middle:
			infoOne.second.reset(new MiddleStudent());
			antiSerialize_impl(dynamic_pointer_cast<MiddleStudent>(infoOne.second), ssm);
			break;
		case College:
			infoOne.second.reset(new CollegeStudent());
			antiSerialize_impl(dynamic_pointer_cast<CollegeStudent>(infoOne.second), ssm);
			break;
		default:
			students_list.clear();
			throw exception("logic error");
			break;
		}
		students_list.push_back(infoOne);
	}
}

void StudentManangeEnginePrivate::antiSerialize_impl(shared_ptr<PrimaryStudent> info, stringstream &ss)
{
	if (!info){
		return;
	}
	antiSerialize_impl(info.get(),ss);
	float grades = 0.0f;
	ss>>grades;
	info->setEnglish(grades);
	ss>>grades;
	info->setMath(grades);
	ss>>grades;
	info->setChinese(grades);
}

void StudentManangeEnginePrivate::antiSerialize_impl(shared_ptr<MiddleStudent> info, stringstream &ss)
{
	if (!info){
		return;
	}
	antiSerialize_impl(dynamic_pointer_cast<PrimaryStudent>(info),ss);
	float grades;
	ss>>grades;
	info->setGeography(grades);
	ss>>grades;
	info->setHistory(grades);
}

void StudentManangeEnginePrivate::antiSerialize_impl(shared_ptr<CollegeStudent> info, stringstream &ss)
{
	if (!info){
		return;
	}
	antiSerialize_impl(info.get(),ss);
	float grades;
	ss>>grades;
	info->setMajor(grades);
	ss>>grades;
	info->setEnglish(grades);
	ss>>grades;
	info->setProgramDesigned(grades);
	ss>>grades;
	info->setAdvancedMath(grades);
}

void StudentManangeEnginePrivate::antiSerialize_impl(AbstractStudent *info, stringstream &ss)
{
	if (!info){
		return;
	}
	string no, name;
	int sex;
	size_t age;
	size_t Class;
	ss>>name>>no>>sex>>age>>Class;
	info->setName(name);
	info->setNumber(no);
	info->setSex((Stu_Sex)sex);
	info->setAge(age);
	info->setClass(Class);
}
