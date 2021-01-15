// Console_Encode.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>


BOOL v_decode(char* Path)
{
	//读取文件信息
	HANDLE handle = CreateFileA(Path, GENERIC_READ,		//打开文件句柄
		0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (handle == INVALID_HANDLE_VALUE)
		return 0;
	DWORD dwLen = GetFileSize(handle, 0), dwRead;
	if (dwLen < 1)	return 0;

	BOOL bRet = 0;
	BYTE* p1 = new BYTE[dwLen];

	if (!ReadFile(handle, p1, dwLen, &dwRead, NULL)
		|| dwRead != dwLen)
	{
		CloseHandle(handle);
		printf("读取文件失败。");
	}
	else
	{
		CloseHandle(handle);

		WORD* start = (WORD*)(p1 + 0x26);
		if (*start != 0xe6FF)
		{
			printf("请使用jmp esi定位！");
			delete[] p1;
			return 0;
		}
		BYTE* p2 = new BYTE[dwLen];
		for (int key = 0; key < 0xFF; key++)
		{
			bRet = 1;
			for (DWORD i = 0; i < dwRead; i++)
			{
				p2[i] = i > 0x20 ? (p1[i] ^ key) : p1[i];
				if (0x00 == p2[i] || 0x0A == p2[i] || 0x0D == p2[i] || 0x20 == p2[i])
				{
					// 如果加密后的字节为0x00直接跳出循环，用下一个KEY进行加密
					bRet = 0;
					break;
				}
			}
			if (bRet)	//成功
			{
				printf("加密成功，[%02X]，加密后：\n\nchar cShellCode[] = \\\n\"", key);
				for (DWORD i = 0; i < dwRead; i++)
				{
					printf("\\x%02X", p2[i]);
					if ((i + 1) % 16 == 0)
					{
						printf("\"\\\n\"");
					}
				}
				printf("\";\n\n解密：\n\n\"");
				for (DWORD i = 0; i < dwRead; i++)
				{
					BYTE by = i > 0x20 ? (p1[i] ^ key) : p1[i];
					printf("\\x%02X", by);
					if ((i + 1) % 16 == 0)
					{
						printf("\"\\\n\"");
					}
				}
				printf("\";\n\n");
				break;
			}
		}
		delete[] p2;
	}
	delete[] p1;
	return bRet;
}


int main()
{
	char buff[255] = {};
	do
	{
		std::cout << "请输入功能：\nA1:加密shellcode\n";
		scanf_s("%s", buff, 255);
		if (strcmp(buff, "exit") == 0)
		{
			break;
		}
		else if (strcmp(buff, "A1") == 0)
		{
			std::cout << "请输入拖入文件：";
			scanf_s("%s", buff, 255);
			if (INVALID_FILE_ATTRIBUTES != GetFileAttributesA(buff))
				v_decode(buff);
		}
	} while (true);
}
