// TypedStack.h: interface for the CTypedStack class.

//ģ���ջ

#ifndef _CTSTACK_H
#define _CTSTACK_H

//������
#define STACK_EXTEND_SIZE			10 

template <class T> 
class CTypedStack  
{
public:
	CTypedStack(int nCapacity = 10);
	virtual ~CTypedStack();

public:

	//��ջ
	void Push(const T& item);

	//��ջ
	T Pop();

	//����ջ��Ԫ��
	T Peek();

	//����ջ�Ƿ�Ϊ��
	BOOL IsEmpty() const;

	//���ջ�е�Ԫ��,�������ͷ��ڴ�
	void ClearItem();

	//���ض�ջ�е�Ԫ�صĸ���
	int GetSize();

	//�ڶ�ջ������
	int Search(const T& item);


private:

	//��ջջ����λ��
	int m_nTop;

	//��ʵ��,�����ַ���:
	//��һ,ͨ������,��ָ�����鳤��
	//�ڶ�,��̬����,�ڹ��캯���з���
	//����,��̬�ռ�����,���ַ���ʱ�俪����һ��,������,
	
	//�洢Ԫ�صĶ�̬����
	T* m_ptStack;

	//��ջ����(��̬��ȫ����)
	int m_nCapacity;


};


#ifndef _CTSTACK_CPP
#define _CTSTACK_CPP
#include "TypedStack.cpp"
#endif

#endif 

