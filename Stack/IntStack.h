#pragma once

//��������� �����, ��������� ����� �����.
typedef struct IntStack IntStack;

//��������� �������� � ������ ����� ����� �����. ���������� -1, ���� �� ������� �������� ������ ��� ����� ������� �����. ����� 0.
int pushInt(IntStack** head, int value);

//�������� ��������� �� ������ ����� ����� �����. ���������� -1, ��� �������� ������� �����.
int popInt(IntStack** head);

//������ ������� �������� ����� ����� �����
int topInt(IntStack** head);

//������� ����� ����� �����
void clearInt(IntStack** head);