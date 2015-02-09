#pragma once
//
//ѧ����������
//

#include "StudentManangeEnginePrivate.h"

class StudentManangeEngine
{
public:
	StudentManangeEngine(void);
	~StudentManangeEngine(void);
	//����ѭ������
	int exec();
protected:
	//��ӹ��ܣ������ܹ���Ӳ�ͬѧ���ļ�¼��
	//�ṩѡ����湩�û�ѡ����Ҫ��ӵ����
	//Ҫ��ѧ��ҪΨһ�����������ظ�ѧ�ŵļ�¼ʱ��
	//����ʾ��������ظ���ȡ����ӡ�
	void add();

	//��ѯ���ܣ��ɸ���ѧ�š���������Ϣ������ӵ�ѧ����¼���в�ѯ��
	//���δ�ҵ���������Ӧ����ʾ��Ϣ������ҵ�������ʾ��Ӧ�ļ�¼��Ϣ��
	//�������ڲ��������¶��⹦��
	//�༭���ܣ��ɸ��ݲ�ѯ�������Ӧ�ļ�¼�����޸ģ��޸�ʱע��ѧ�ŵ�Ψһ�ԡ�
	void query();

	//��һ��ѧ������Ϣ���б༭
	void edit(StudentTypeMapBaseInfo &info);

	//��ʾ���ܣ�����ʾ��ǰϵͳ������ѧ���ļ�¼��ÿ����¼ռ��һ�С�
	void showAll();

	//ɾ�����ܣ���Ҫʵ�ֶ�����ӵ�ѧ����¼����ɾ����
	//�����ǰϵͳ��û����Ӧ�ļ�¼������ʾ����¼Ϊ�գ��������ز�����
	void remove();

	//ͳ�ƹ��ܣ��ܸ��ݶ��ֲ�������ͳ�ơ���ͳ��ѧ���������ܷ֡����Ƶ�ƽ���ֵȡ�
	void statistics();

	//���湦�ܣ��ɽ���ǰϵͳ�и����¼�����ļ��У����뷽ʽ���⡣
	void saveToFile();

	//��ȡ���ܣ��ɽ��������ļ��е���Ϣ���뵽��ǰϵͳ�У����û�����ʹ�á�
	void readFromFile();

	//�����ܣ��ɰ��ֺܷ͵��Ƴɼ������Ρ�
	void sort();
private:
	//���һ��ѧ��������Ϣ
	void add_base(AbstractStudent *info);
	//���һ��Сѧ��
	void add_primary(PrimaryStudent *info);
	//���һ����ѧ��
	void add_middle(MiddleStudent *info);
	//���һ����ѧ��
	void add_college(CollegeStudent *info);
	//������Ϣ�޸�
	void edit(AbstractStudent *info);
	//Сѧ�ɼ��޸�
	void edit_p(shared_ptr<PrimaryStudent> info);
	void edit_m(shared_ptr<MiddleStudent> info);
	void edit_c(shared_ptr<CollegeStudent> info);
private:
	StudentManangeEnginePrivate *engine;
};

