
// TypedStack.cpp: implementation of the CTypedStack class.
#include "stdafx.h"

#ifndef _CTSTACK_CPP
#define _CTSTACK_CPP
#include "TypedStack.h"
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//���캯��
template <class T>
CTypedStack<T>::CTypedStack(int nCapacity) : m_nTop(-1)
{
	m_nCapacity = nCapacity;
	if(m_nCapacity < 1) m_nCapacity = 1;
	//��ʼ������
	m_ptStack = new T[m_nCapacity];
	if(m_ptStack == NULL)
	{
		AfxMessageBox("�ڴ����ʧ��!");
		exit(1);
	}
}

template <class T>
CTypedStack<T>::~CTypedStack()
{
	if(m_ptStack)
	{
		delete[] m_ptStack;
		m_ptStack = NULL;
	}
}

//Push  (��ջ)
template <class T>
void CTypedStack<T>::Push(const T& item)
{
	if(m_nTop == (m_nCapacity - 1))
	{
		//��Ҫ����
		T* ptNewStack = new T[m_nCapacity + STACK_EXTEND_SIZE];
		if(ptNewStack == NULL)
		{
			AfxMessageBox("�ڴ����ʧ��!");
			exit(1);		
		}
		
		//����Ԫ��
		T* ptSrc = m_ptStack;
		T* ptDst = ptNewStack;
		
		//��ʱ, 
		for(int i = 0; i <= m_nTop; i++)
			*ptDst++ = *ptSrc++;
		
		//ɾ���ɶ�ջ
		delete[] m_ptStack;

		//����ָ���µĵ�ַ
		m_ptStack = ptNewStack;
		
		//������С��¼����Ӧ�ı�
		m_nCapacity += STACK_EXTEND_SIZE;
	}

	//������ѹ���ջ
	m_nTop++;
	m_ptStack[m_nTop] = item;
}

//Push (��ջ)
template <class T>
T CTypedStack<T>::Pop()
{
	if(m_nTop == -1)
	{
		AfxMessageBox("��ջ�ѿ�!");
		exit(1);		
	}

	//���T��һ�������, " = " ���������Ҫ����
	T tTop = m_ptStack[m_nTop];
	m_nTop--;
	return tTop;
}

//Peek  (ʰȡ, ����ջ��Ԫ��)
template <class T>
T CTypedStack<T>::Peek()
{
	if(m_nTop == -1)
	{
		AfxMessageBox("��ջ�ѿ�!");
		exit(1);		
	}

	T tTop = m_ptStack[m_nTop];
	return tTop;
}

//�ڶ�ջ������
//���ر�������Ŀλ�ڶ�ջ�о���ջ��������ƫ����.
//�����Ŀû���ڶ�ջ��, �򷵻� -1 .
template <class T>
int CTypedStack<T>::Search(const T& item)
{
	//�����ջΪ��, ����
	if(m_nTop == -1) return -1;
	
	int i = m_nTop;
	while(i > -1)
	{
		//�Ƚ�λ��ջ�е���Ŀ
			if(m_ptStack[i] == item)
			return (m_nTop - i);
		i--;
	}
	return -1;
}


//����ջ�Ƿ�Ϊ��
template <class T>
BOOL CTypedStack<T>::IsEmpty() const
{
	return (m_nTop == -1);
}

//��ջ�����Ԫ��, �������ͷ��ڴ�
template <class T>
void CTypedStack<T>::ClearItem()
{
	m_nTop = -1;
}

//���ض�ջ�е�Ԫ�صĸ���(ջ���±��1)
template <class T>
int CTypedStack<T>::GetSize()
{
	return (m_nTop + 1);
}

