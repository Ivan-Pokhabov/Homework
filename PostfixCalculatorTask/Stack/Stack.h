#pragma once


//��������� �����, ��������� ����� �����.
typedef struct
{
	int value;
	struct IntStack* previous;
} IntStack;

//��������� �����, ��������� �������
typedef struct
{
	char value;
	struct CharStack* previous;
} CharStack;

//��������� �������� � ������ ����� ��������. ���������� -1, ���� �� ������� �������� ������ ��� ����� ������� �����. ����� 0.
int pushChar(CharStack** head, char value);

//��������� �������� � ������ ����� ����� �����. ���������� -1, ���� �� ������� �������� ������ ��� ����� ������� �����. ����� 0.
int pushInt(IntStack** head, int value);

//�������� ��������� �� ������ ����� ��������. ���������� -1, ��� �������� ������� �����.
int popChar(CharStack** head);

//�������� ��������� �� ������ ����� ����� �����. ���������� -1, ��� �������� ������� �����.
int popInt(IntStack** head);

//������ ������� �������� ����� ��������
char topChar(CharStack** head);

//������ ������� �������� ����� ����� �����
int topInt(IntStack** head);

//������� ����� ��������
void clearChar(CharStack** head);

//������� ����� ����� �����
void clearInt(IntStack** head);