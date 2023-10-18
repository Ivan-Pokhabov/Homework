#pragma once

//��������� �����, ��������� �������.
typedef struct CharStack CharStack;

//��������� �������� � ������ ����� ��������. ���������� -1, ���� �� ������� �������� ������ ��� ����� ������� �����. ����� 0.
int pushChar(CharStack** head, char value);

//�������� ��������� �� ������ ����� ��������. ���������� -1, ��� �������� ������� �����.
int popChar(CharStack** head);

//������ ������� �������� ����� ��������
char topChar(CharStack** head);

//������� ����� ��������
void clearChar(CharStack** head);
