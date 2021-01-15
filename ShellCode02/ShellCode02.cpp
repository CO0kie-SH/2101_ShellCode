// ShellCode02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

#define defPath "D:\\cacheD\\202101\\2101_ShellCode\\ShellCode01\\shell.txt"


void shell()
{
	_asm
	{
		sub esp, 0x80
		jmp MyShellCode

		// Co0kie
		_asm _emit(0x43) _asm _emit(0x6f) _asm _emit(0x30) _asm _emit(0x6b) _asm _emit(0x69) _asm _emit(0x65) _asm _emit(0x00)
		// CO0kie
		_asm _emit(0x43) _asm _emit(0x4f) _asm _emit(0x30) _asm _emit(0x6b) _asm _emit(0x69) _asm _emit(0x65) _asm _emit(0x00)
		// ExitProcess
		_asm _emit(0x45) _asm _emit(0x78) _asm _emit(0x69) _asm _emit(0x74) _asm _emit(0x50) _asm _emit(0x72) _asm _emit(0x6f) _asm _emit(0x63) _asm _emit(0x65) _asm _emit(0x73) _asm _emit(0x73) _asm _emit(0x00)
		// Kernel32.dll
		_asm _emit(0x4b) _asm _emit(0x65) _asm _emit(0x72) _asm _emit(0x6e) _asm _emit(0x65) _asm _emit(0x6c) _asm _emit(0x33) _asm _emit(0x32) _asm _emit(0x2e) _asm _emit(0x64) _asm _emit(0x6c) _asm _emit(0x6c) _asm _emit(0x00)
		// ExitProcess函数地址
		_asm _emit(0x90) _asm _emit(0x90) _asm _emit(0x90) _asm _emit(0x90)
		// ExitProcess函数返回值
		_asm _emit(0x90) _asm _emit(0x90) _asm _emit(0x90) _asm _emit(0x90)
		// MessageBoxA
		_asm _emit(0x4d) _asm _emit(0x65) _asm _emit(0x73) _asm _emit(0x73) _asm _emit(0x61) _asm _emit(0x67) _asm _emit(0x65) _asm _emit(0x42) _asm _emit(0x6f) _asm _emit(0x78) _asm _emit(0x41) _asm _emit(0x00)
		// User32.dll
		_asm _emit(0x55) _asm _emit(0x73) _asm _emit(0x65) _asm _emit(0x72) _asm _emit(0x33) _asm _emit(0x32) _asm _emit(0x2e) _asm _emit(0x64) _asm _emit(0x6c) _asm _emit(0x6c) _asm _emit(0x00)
		// MessageBoxA函数地址
		_asm _emit(0x90) _asm _emit(0x90) _asm _emit(0x90) _asm _emit(0x90)
		// MessageBoxA函数返回值
		_asm _emit(0x90) _asm _emit(0x90) _asm _emit(0x90) _asm _emit(0x90)
		//LoadLibraryA
		_asm _emit(0x4c) _asm _emit(0x6f) _asm _emit(0x61) _asm _emit(0x64) _asm _emit(0x4c) _asm _emit(0x69) _asm _emit(0x62) _asm _emit(0x72) _asm _emit(0x61) _asm _emit(0x72) _asm _emit(0x79) _asm _emit(0x41) _asm _emit(0x00)
		// LoadLibraryA地址
		_asm _emit(0x90) _asm _emit(0x90) _asm _emit(0x90) _asm _emit(0x90)
		//GetProcAddress
		_asm _emit(0x47) _asm _emit(0x65) _asm _emit(0x74) _asm _emit(0x50) _asm _emit(0x72) _asm _emit(0x6f) _asm _emit(0x63) _asm _emit(0x41) _asm _emit(0x64) _asm _emit(0x64) _asm _emit(0x72) _asm _emit(0x65) _asm _emit(0x73) _asm _emit(0x73) _asm _emit(0x00)
		// GetProcAddress地址
		_asm _emit(0x90) _asm _emit(0x90) _asm _emit(0x90) _asm _emit(0x90)

		MyShellCode:
		call Callme
			Callme :
		pop ebx  // ebx => eip                                                  
			sub ebx, 5

			// 找到Kernel32.dll,并保存其地址                                          
			mov eax, dword ptr fs : [0x30]  // _PEB                                 
			mov eax, [eax + 0xC]  // _PEB_LDR_DATA                                  
			mov eax, [eax + 0x1C]  // InInitalizationOrderLinks                     
			mov eax, [eax]  // Kernel32结构体                                        
			mov edx, [eax + 0x8]  // Kernel32基址  (edx => Kernel32)                 

			// 找到GetProcAddress,并保存其地址										    
			mov eax, [edx + 0x3C]  // 获取PE头偏移									
			add eax, edx  // 获取PE头位置											    
			mov ecx, [eax + 0x78]  // 获取Exprot偏移(64位好像是0x88)  (ecx => Export) 
			add ecx, edx
			mov esi, [ecx + 0x1C]  // 获取EAT										
			add esi, edx
			push esi
			mov esi, [ecx + 0x20]  // 获取ENT										
			add esi, edx
			push esi
			mov esi, [ecx + 0x24]  // 获取EOT										
			add esi, edx
			push esi

			push ebp
			mov ebp, esp
			sub esp, 0xcc
			mov eax, -1
			FindLoop :
		inc eax
			mov ecx, 0xE  // GetProcAddress长度								        
			cld
			mov edi, [ebp + 0x8]  // 获取ENT										    
			mov edi, [edi + eax * 4]  // 获取第n个函数名称地址						    
			add edi, edx
			lea esi, [ebx - 19]  // 获取目标字符串									    
			repe cmpsb
			jne FindLoop
			mov ecx, [ebp + 0x4]  // 获取EOT										    
			mov cx, word ptr[ecx + eax * 2]  // 获取对应的序号(只取两个字节值)		    
			and ecx, 0xffff
			mov eax, [ebp + 0xC]  // 获取EAT										    
			mov eax, [eax + ecx * 4]  // 获取对应的地址(RVA)						    
			add eax, edx  // 获取对应的地址(VA)									    
			mov esp, ebp
			pop ebp
			add esp, 12
			mov[ebx - 4], eax  //保存GetProcAddress函数地址                          

			// 调用GetProcAddress获取LoadLibrary函数地址并保存                         
			lea eax, [ebx - 36]
			push eax
			push edx
			mov eax, dword ptr[ebx - 4]
			call eax
			mov[ebx - 23], eax
			// 调用LoadLibrary函数获取User32.dll基址并保存
			lea eax, [ebx - 0x37]
			push eax
			mov eax, dword ptr[ebx - 23]
			call eax

			// 调用GetProcAddress获取MessageBoxA函数地址并保存
			mov edx, eax
			lea eax, [ebx - 0x43]
			push eax
			push edx
			mov eax, dword ptr[ebx - 4]
			call eax
			mov[ebx - 0x2c], eax

			// 调用LoadLibrary函数获取Kernel32.dll基址并保存
			lea eax, [ebx - 0x58]
			push eax
			mov eax, dword ptr[ebx - 23]
			call eax

			// 调用GetProcAddress获取ExitProcess函数地址并保存
			mov edx, eax
			lea eax, [ebx - 0x64]
			push eax
			push edx
			mov eax, dword ptr[ebx - 4]
			call eax
			mov[ebx - 0x4b], eax
			push 0
			lea eax, dword ptr[ebx - 0x6b]
			push eax
			lea eax, dword ptr[ebx - 0x72]
			push eax
			push 0
			mov eax, [ebx - 0x2c]
			call eax
			mov dword ptr[ebx - 0x28], eax
			push 0
			mov eax, [ebx - 0x4b]
			call eax
			mov dword ptr[ebx - 0x47], eax

	}
	//__asm
	//{
	//	sub esp, 0x66;
	//	__asm _emit(0xE8)__asm _emit(0xFF)__asm _emit(0xFF)__asm _emit(0xFF);
	//	__asm _emit(0xFF)__asm _emit(0xC3)__asm _emit(0x5E);
	//	add esi, 0x7 + 0x8 + 7 + 12 + 11 + 13 + 15;	//指令+地址+文本
	//	call esi;
	//	//Address
	//	__asm _emit(0xA0)__asm _emit(0xEE)__asm _emit(0x87)__asm _emit(0x76);
	//	__asm _emit(0x00)__asm _emit(0x41)__asm _emit(0xC7)__asm _emit(0x76);
	//	//CO0kie 7
	//	__asm _emit(0x43)__asm _emit(0x4F)__asm _emit(0x30)__asm _emit(0x6B)
	//	__asm _emit(0x69)__asm _emit(0x65)__asm _emit(0x00);
	//	//MessageBoxA 12
	//	__asm _emit(0x4D)__asm _emit(0x65)__asm _emit(0x73)__asm _emit(0x73)
	//	__asm _emit(0x61)__asm _emit(0x67)__asm _emit(0x65)__asm _emit(0x42)
	//	__asm _emit(0x6F)__asm _emit(0x78)__asm _emit(0x41)__asm _emit(0x00);
	//	//user32.dll 11
	//	__asm _emit(0x75)__asm _emit(0x73)__asm _emit(0x65)__asm _emit(0x72)
	//	__asm _emit(0x33)__asm _emit(0x32)__asm _emit(0x2E)__asm _emit(0x64)
	//	__asm _emit(0x6C)__asm _emit(0x6C)__asm _emit(0x00);
	//	//LoadLibraryA 13
	//	__asm _emit(0x4C)__asm _emit(0x6F)__asm _emit(0x61)__asm _emit(0x64)
	//	__asm _emit(0x4C)__asm _emit(0x69)__asm _emit(0x62)__asm _emit(0x72)
	//	__asm _emit(0x61)__asm _emit(0x72)__asm _emit(0x79)__asm _emit(0x41)
	//	__asm _emit(0x00);
	//	//GetProcAddress 15
	//	__asm _emit(0x47)__asm _emit(0x65)__asm _emit(0x74)__asm _emit(0x50)
	//	__asm _emit(0x72)__asm _emit(0x6F)__asm _emit(0x63)__asm _emit(0x41)
	//	__asm _emit(0x64)__asm _emit(0x64)__asm _emit(0x72)__asm _emit(0x65)
	//	__asm _emit(0x73)__asm _emit(0x73)__asm _emit(0x00);
	//tag_Load:	//加载API
	//	push esi;
	//	sub esi, 15;
	//	mov ecx, esi;
	//	push esi;
	//	//解析链表
	//	mov esi, fs : [0x30] ;
	//	mov esi, [esi + 0x0C];
	//	mov esi, [esi + 0x1C];
	//	mov esi, [esi];
	//	mov esi, [esi + 0x08];
	//	push esi;
	//	call tag_GetProcAdd;
	//	pop esi;
	//	pop ecx;
	//	sub ecx, 13;		//Load字符串
	//	push eax;			//保存GerProcAddress
	//	mov edi, eax;
	//	push ecx;		//保存字符串
	//	push ecx;
	//	push esi;
	//	call eax;		//CALL GetProc
	//	pop ecx;		//读取字符串
	//	sub ecx, 11;	//得到user32.dll
	//	push eax;		//API Load
	//	push ecx;
	//	push ecx;
	//	call eax;
	//	pop ecx;
	//	sub ecx, 12;
	//	push ecx;
	//	push ecx;
	//	push eax;
	//	call edi;
	//	mov esi, eax;	//user32.dll
	//	call tag_ShellCode;
	//tag_GetProcAdd:
	//	// 找到GetProcAddress,并保存其地址
	//	mov eax, [esi + 0x3C]	// 获取PE头偏移
	//	add eax, esi;			// 获取PE头位置
	//	mov edx, [eax + 0x78];	// 获取Exprot偏移(64位好像是0x88)  (ecx => Export)
	//	add edx, esi;
	//	push edx;
	//	mov ebx, [edx + 0x18];	//获取名字数量
	//	push ebx;
	//	mov edi, [edx + 0x20]; // 获取ENT
	//	add edi, esi;
	//tag_ENT:
	//	mov eax, [edi];
	//	add eax, esi;
	//	push ecx;
	//	push eax;
	//	//push esi;
	//	//call CheckINT;
	//	call strcmp;
	//	add edi, 0x4;
	//	dec ebx;
	//	test eax, eax;
	//	pop edx;
	//	pop ecx;
	//	jnz tag_ENT;
	//	//找到了该函数
	//	pop eax;
	//	sub eax, ebx;
	//	shl eax, 1;
	//	mov edi, [esp];
	//	call tag_GetAdd;	//获取函数地址
	//	pop edi;
	//	ret
	//tag_GetAdd:
	//	mov ecx, [edi + 0x24]; // 获取EOT
	//	add ecx, esi;
	//	add ecx, eax;
	//	mov bx, [ecx];			//得到序号
	//	shl ebx, 2;				//*4

	//	mov ecx, [edi + 0x1C];	//获取EAT
	//	add ecx, esi;
	//	add ecx, ebx;
	//	mov eax, [ecx - 0x4];	//得到地址
	//	add eax, esi;
	//	ret;
	//tag_ShellCode:
	//	xor eax, eax;
	//	sub esi, 0x7;
	//	push eax;
	//	push esi;
	//	push esi;
	//	push eax;
	//	sub esi, 0x8;
	//	call[esi];
	//	add esi, 0x4;
	//	push eax;
	//	call[esi];
	//}
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