#include <iostream>
#include "driver.h"
#include "dll.h"

auto GetTextHashW(PCWSTR Str) -> UINT {

	UINT32 Hash = NULL;

	while (Str != NULL && *Str) {

		Hash = (UINT32)(65599 * (Hash + (*Str++) + (*Str > 64 && *Str < 91 ? 32 : 0)));
	}

	return Hash;
}


void testSinglePress(driver& d, int count, int flag) {


	for (size_t i = 0; i < 10; i++)// 单按1
	{

		driver::KEYBOARD_INPUT_DATA keyBorad{ 0 };

		keyBorad.Flags = 0; //表示按下
		keyBorad.MakeCode = flag;//按键1

		d.keyboard(&keyBorad);


		driver::KEYBOARD_INPUT_DATA keyBoradDown{ 0 };

		keyBoradDown.Flags = 1; //表示松开
		keyBoradDown.MakeCode = flag;//键盘扫描码

		d.keyboard(&keyBoradDown);

	}
}



void testAllPress(driver& d, int count, int flag) {


	for (size_t i = 0; i < 10; i++)// 连按1
	{

		driver::KEYBOARD_INPUT_DATA keyBorad{ 0 };

		keyBorad.Flags = 0; //表示按下
		keyBorad.MakeCode = flag;//按键1

		d.keyboard(&keyBorad);
	}
	driver::KEYBOARD_INPUT_DATA keyBoradDown{ 0 };

	keyBoradDown.Flags = 1; //表示松开
	keyBoradDown.MakeCode = flag;//键盘扫描码

	d.keyboard(&keyBoradDown);
}

int main()
{
	driver d;
	if (!d.init())
	{
		return 1;
	}
	if (d.verify())
	{
		printf("验证成功\n");
	}
	//if (!d.attach(L"explorer.exe"))
	//{
	//	printf("附加失败");
	//	return 1;
	//}

	//uint64_t base_address = 0;
	//printf("基地址: %llx\n", base_address = d.get_base_address());
	//printf("模块地址: %llx\n", d.get_module_address("explorer.exe"));
	//char x = 'b';
	//d.read(base_address, (uint64_t)&x, 1);
	//printf("%c\n", x);
	//x = 'b';
	//d.write1((uint64_t)&x, d.get_base_address(), 1);
	//d.read(base_address, (uint64_t)&x, 1);
	//printf("%c\n", x);
	//x = 'M';
	//d.write1((uint64_t)&x, d.get_base_address(), 1);
	//auto start = GetTickCount64();
	//for (size_t i = 0; i < 10000; i++)
	//{
	//	d.read<int>(base_address);
	//}
	//printf("cost: %llums\n", GetTickCount64() - start);
	////d.force_delete("C:\\a.txt");
	////d.kill_process("explorer.exe");
	//uint64_t alloc = d.alloc_memory(10, PAGE_READWRITE, FALSE);
	//printf("alloc: %llx\n", alloc);
	//d.free_memory(alloc);
	//driver::MOUSE_INPUT_DATA mid{ 0 };
	//mid.LastX = 100;
	//mid.LastY = 100;
	//mid.ButtonFlags = 0;
	//mid.UnitId = 1;
	//d.mouse(&mid);
	////d.spoof_hwid(0);

	//Sleep(5000);
	//printf("测试单按\n");
	//testSinglePress(d, 10, 0x2);
	//printf("测试一直按\n");

	//testAllPress(d, 10, 0x2);

	//driver::INJECT_DATA data{ 0 };
	//data.InjectHash = GetTextHashW(L"notepad.exe");
	//data.InjectBits = 64;
	//data.InjectData = Dll1;
	//data.InjectSize = sizeof(Dll1);
	//d.inject(&data, sizeof(data));

	//std::cin.get();

	//ZeroMemory(&data, sizeof(data));
	//d.inject(&data, 0);

	HWND hawnd = FindWindow(L"Notepad", NULL);
	if (hawnd == NULL) {

		printf("句柄未发现\n");
		std::cin.get();
		return 0;
	}
	//printf("句柄未发现\n", hawnd);
	d.hide_window(hawnd, WDA_EXCLUDEFROMCAPTURE); //不知道为啥 WDA_MONITOR也显示是全黑 而不是后面的图像

	std::cin.get();
	return 0;
}