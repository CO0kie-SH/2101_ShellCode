// Console_WriteCode.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

int main()
{
    std::cout << "Hello World!\n";
	char buff[260];
	DWORD tmp;
	do
	{
		printf("请输入试错长度：\n");
		scanf_s("%s", buff, 260);
		if (buff[1] == 'x')
		{
			printf("%s", buff);
			BYTE by[5] = {};
			sscanf_s(buff + 2, "%X", by, 5);
			printf("结果为\n\t%s\n", by);
		}
		else
		{
			sscanf_s(buff, "%lu", &tmp);
			printf("%lu\n\n\t", tmp);
			BYTE* by = new BYTE[tmp], * p = by,
				left = 'A', num = '0';
			for (DWORD i = tmp/2; i >0; i--)
			{
				*p = left;
				p++;
				*p = num;
				p++;
				printf("%c%c", left, num);
				if (num++ == '9')
				{
					left++;
					num = '0';
				}
			}
			printf("\n\n");
			delete[] by;
		}
	} while (true);
}
