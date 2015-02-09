#pragma once
//
//学生管理引擎
//

#include "StudentManangeEnginePrivate.h"

class StudentManangeEngine
{
public:
	StudentManangeEngine(void);
	~StudentManangeEngine(void);
	//进入循环操作
	int exec();
protected:
	//添加功能：程序能够添加不同学生的记录，
	//提供选择界面供用户选择所要添加的类别，
	//要求学号要唯一，如果添加了重复学号的记录时，
	//则提示数据添加重复并取消添加。
	void add();

	//查询功能：可根据学号、姓名等信息对已添加的学生记录进行查询，
	//如果未找到，给出相应的提示信息，如果找到，则显示相应的记录信息。
	//本函数内部包含以下额外功能
	//编辑功能：可根据查询结果对相应的记录进行修改，修改时注意学号的唯一性。
	void query();

	//对一个学生的信息进行编辑
	void edit(StudentTypeMapBaseInfo &info);

	//显示功能：可显示当前系统中所有学生的记录，每条记录占据一行。
	void showAll();

	//删除功能：主要实现对已添加的学生记录进行删除。
	//如果当前系统中没有相应的记录，则提示“记录为空！”并返回操作。
	void remove();

	//统计功能：能根据多种参数进行统计。能统计学生人数、总分、单科的平均分等。
	void statistics();

	//保存功能：可将当前系统中各类记录存入文件中，存入方式任意。
	void saveToFile();

	//读取功能：可将保存在文件中的信息读入到当前系统中，供用户进行使用。
	void readFromFile();

	//排序功能：可按总分和单科成绩排名次。
	void sort();
private:
	//添加一个学生基本信息
	void add_base(AbstractStudent *info);
	//添加一个小学生
	void add_primary(PrimaryStudent *info);
	//添加一个中学生
	void add_middle(MiddleStudent *info);
	//添加一个大学生
	void add_college(CollegeStudent *info);
	//基本信息修改
	void edit(AbstractStudent *info);
	//小学成绩修改
	void edit_p(shared_ptr<PrimaryStudent> info);
	void edit_m(shared_ptr<MiddleStudent> info);
	void edit_c(shared_ptr<CollegeStudent> info);
private:
	StudentManangeEnginePrivate *engine;
};

