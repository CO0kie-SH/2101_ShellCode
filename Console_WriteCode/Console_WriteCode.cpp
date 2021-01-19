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
			char buf[250], * str = new char[tmp];
			ZeroMemory(str, tmp);
			DWORD i = 1, sLen = 0, len;
			while (true)
			{
				wsprintfA(buf, "A%lu", i++);
				printf("%s", buf);

				len = strlen(buf);
				sLen += len;

				if (sLen >= tmp)
					break;

				strcat_s(str, tmp, buf);
			}
			printf("\n\n");
			delete[] str;
		}
	} while (true);
}
