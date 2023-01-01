//
//  main.c
//  practice
//
//  Created by weilin on 2019/4/1.
//  Copyright © 2019 weilin. All rights reserved.
//  Edited by Austin on 2022/02/18
//


#include <stdio.h>
#include <stdlib.h>

// 易錯題目: Q53, Q54-3

int main(int argc, const char * argv[]) {
    // insert code here...

	// 基本觀念
	// ------------------------------------------------------------------------------------------------------//
	// #include <stdio.h>
	const int global_x = 1;  // 儲存於 data 區段（唯讀區域）
	int global_y = 1;        // 儲存於 data 區段（可讀寫區域）
	int global_z;            // 儲存於 bss 區段
	int main() {
		const static int x = 1; // 儲存於 data 區段（唯讀區域）
		static int y = 1;       // 儲存於 data 區段（可讀寫區域）
		static int z;           // 儲存於 bss 區段
		int w = 1;              // 儲存於 stack 區段

		// 儲存於 heap 區段
		char *buf = (char*)malloc(sizeof(char) * 100);
		// ...
		free(buf);

		return 0;
	}
	// -----------------------------------------------------------------------------------------------------//
	// Static
	//Static variables have a property of preserving their value even after they are out of their scope! Hence, 
	// static variables preserve their previous value in their previous scope and are not initialized again in the new scope. 
	int fun()
	{
		static int count = 0;
		count++;
		return count;
	}

	int main()
	{
		printf("%d ", fun()); //=> print 1
		printf("%d ", fun()); // => print 2
		return 0;
	}
    
	// -----------------------------------------------------------------------------------------------------//
	// C 的 extern 用法
	// 變數使用前要先宣告(declaration)，C 的 extern 關鍵字，用來表示此變數已經在別處定義(definition)，]
	// 告知程式到別的地方找尋此變數的定義(可能在同一個檔案或其他檔案)。
	// [範例1] 變數定義在同一個檔案
	// 以下程式若無「extern int x; 」，會編譯錯誤。
	// 若僅無「extern」，雖然可以編譯成功，但效果是main()裡面宣告了一個沒有初始值的 x，印出的 x 將是不可預期的，而不是x = 10。
	int main(int argc, char** argv) {
		extern int x;
		printf("%d\n", x);
		return (EXIT_SUCCESS);
	}
	int x = 10;

	// [範例2] 變數定義在其他檔案
	// 以下程式若無「extern」，我測試依然可以編譯成功，查了一些資料，似乎都我沒要的答案，後來翻到我手邊有一本書寫保險一點還是要寫extern。
	// 但是「extern」關鍵字，如果用在檔案內的全域變數似乎可有可無，這我還是不太懂。但我還是會加上「extern」，畢竟看到「extern」，至少會讓「人」知道這個變數已經在別處定義了。
	// [aa0.c]
	extern int x;
	void test1() {
		int x = 11;
		printf("test1():%d\n", x); 
	}

	void test2() {
		x = 12;
		printf("test2():%d\n", x); 
	}

	int main(int argc, char** argv) {
		printf("main():%d\n", x); //全域x=1 
		aa_test(); //全域x=1
		test1(); //test1()區域x=11
		aa_test(); //全域x=1
		test2(); //全域x=12
		aa_test(); //全域x=12
		printf("main():%d\n", x); //全域x=12
		return (EXIT_SUCCESS);
	}

	// [aa1.c]
	int x = 1;

	void aa_test() {
		printf("aa_test():%d\n", x);
	}

	// -------------------------------------------------------------------------------------------------------//

	// char a[] = "test"; ==> a[] = {'t', 'e', 's', 't', '\0'}
	// char strA[] = "test";
	// char *strB = "test";
	// const char *strC = "test";
	// strA[0] = 'T';  <= O 編譯可過
	// strB[0] = 'T';  <= X 編譯可過但 是未定義行為, 由char *strB = "test" 這種方式宣告，記憶體位置是唯獨的，此方法不安全因此應加const
	// strC[0] = 'T';  <= X 編譯不可過, 較安全的方式
	// strA = strB; <= X, (char [] = char*) (x) strA為陣列，不可直接給值，陣列無法放在等是左邊
	// strA = strC; same as above.
	// strB = strA; <= O, (char * = char []) (O), 將strB指標指向 &strA[0]的意思
	// strB = strC; <= X, (char * = const char *) (x), const衝突, strC為const, 若strB = strC, 修改strB及修改到strC, 衝突!
	// strC = strA; <= O, (const char * = char[]), (O), 可以的, 可讀可寫變成唯讀, 無衝突
	// strC = strB; <= O, (const char * = char *), (O), 可以的, 可讀可寫變成唯讀, 無衝突
	// 總結 const *Type = *Type; *Type 可以轉成 const *Type

	//union跟struct一樣，都是產生一種新的資料型態，只是不同的是，struct是每個成員變數都配置一段空間，union則是共用一段記憶體空間。
	union StateMachine {
		char character;
		int number;
		char *str;
		double exp;
	};
	// 一個union只配置一個足夠大的空間以來容納最大長度的資料成員，以上例而言，最大長度是double型態，所以StateMachine的記憶體空間 就是double型態的長度。
	// char 1 byte
	// short 2 byte
	// int 4 
	// long x86 : 4, x64 : 8 byte ?
	// long long  x86 : 8 byte
	// float 4 byte
	// pointer 4 byte
	// double 8 byte
	// long double 16 byte
	union MyUnion
	{
		int i;
		long l;
		unsigned char c[4];
	};
	void myUnionTest()
	{
		union MyUnion myUnion;
		myUnion.i = 3;
		if (myUnion.i == 3)
		{
			printf("i is 3 \n");
			for (int i = 0; i < 4; i++)
			{
				printf("c[%d]: %x \n", i, myUnion.c[i]); //因為intel is little endian, 輸出應該是 3 0 0 0
			}
		}
		myUnion.l = 5;
		if (myUnion.l == 5)
		{
			printf("l is 5 \n");
			for (int i = 0; i < 4; i++)
			{
				printf("c[%d]: %x \n", i, myUnion.c[i]); //因為intel is little endian, 輸出應該是 5 0 0 0 
			}
		}
		if (myUnion.i == 3)
		{
			printf("i is still 3"); // X => i and f 共用記憶體空間, i 不再是3
		}
		else if (myUnion.i == 5)
		{
			printf("i is no longer 3, is 5 \n");
			for (int i = 0; i < 4; i++)
			{
				printf("c[%d]: %x \n", i, myUnion.c[i]);
			}
		}

	}
    //Question 1
    // a[5] = {1,2,3,4,5}
    // int *p = a;
    // *(p++)+=100;
    // *(++p)+= 97;
    //values in a[5] are?
    // a[5] = {101,2,100,4,5}

    //Question 2
    // please write a strcmp funtion with char *sl, char *s2, with the same string return 0, else return -1
	int strcmp(char *s1, char *s2)
	{
		while (*s1 != '\0' && *s2 != '\0')
		{
			if (*s1 == *s2)
			{
				s1++;
				s2++;
			}
			else
			{
				return -1;
			}
		}

		if (*s1 == '\0' && *s2 != '\0')
		{
			return -1;
		}
		if (*s1 != '\0' && *s2 == '\0')
		{
			return -1;
		}
		return 0;
	}
	int main()
	{
		const char *s1 = "abdwweqweqwec";  // 用char *來儲存字串常數是read only, 加上const比較好  "" == const char *
		const char *s2 = "abdwweqweqwec";
		int result = stringCompare(s1, s2);
		printf("%d", result);
		return 0;
	}

    //Question 3
    // int a[5]
    // please write a sort funtion to sort array a

	//Insertion sort
	int swap(int* a, int* b)
	{
		int temp = *a;
		*a = *b;
		*b = temp;
	}

	int main()
	{
		//printf("Hello World");
		int a[5] = { 21,34,1,2,56 };
		int min;
		for (int i = 0; i < 5; i++)
		{
			min = i;
			for (int j = i + 1; j < 5; j++)
			{
				if (a[j] < a[min])
				{
					min = j;
				}
			}
			if (a[min] < a[i])
			{
				swap(&a[min], &a[i]);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			printf("%d ,", a[i]);
		}

		return 0;
	}
    //Question 4
    // explain valotile
	// 加上關鍵字volatile, 告知編譯器在編譯此變數時，位置分配在記憶體中，因為此變數隨時可能改變，不要使用暫存器中的值
	// 避免取值時出現錯誤
	static int foo;
	void bar(void) {
		foo = 0;

		while (foo != 255)
			;
	}
	// ex. 一個執行最佳化的編譯器會提示沒有代碼能修改foo的值，並假設它永遠都只會是0.因此編譯器將用類似下列的無限迴圈替換函式體：
	void bar_optimized(void) {
		foo = 0;

		while (true)
			;
	}
	// 使用volatile則不會
	static volatile int foo;

	void bar(void) {
		foo = 0;

		while (foo != 255)
			;
	}
    
    //Question 5
    //#define ADD_TWO(x,y) x+=2;y+=2
    //int FLAG = 0;
    //if(FLAG) ADD_TWO(j,k); 
    // int j = 5;
    // int k = 7;
    // what is the value of j,k
    
	//Ans: 5,9
    
    //Question 6
    //with unsigned int a[20]={1,5,9,11,18,21,23,53,200,230,330,331,332,333,400,401,405,430,450,480};
    //please write a function to print 0~500 but not include values in a array
	void func(int *a, int size)
	{
		int i, indexA;
		i = 0; indexA = 0;
		for (i = 0; i <= 500; i++)
		{
			if (i >= a[indexA])
			{
				indexA++;
			}
			else
			{
				printf("%d", i);
			}
		}
	}
    
    
    //Question 7
    //write a function with a given value b and range is in 0~4,
    //if 0 means printf 0~99 but not include value in a array;1 mean 100~199 and so on
	int testFunction(int b, int *a, int size)
	{
		int start = b * 100;
		int end = start + 100;
		int i = 0;
		while (a[i] < start && i < size)
		{
			i++;
		}

		for (; start <end; start++)
		{
			if (start >= a[i] )
			{
				i++;
			}
			else
			{
				printf("%d ", start);
			}
		}
	}
    
    //Question 8
	struct ListStruct {
		unsigned int DataH;
		unsigned int DataL;
		unsigned int NextPtr;
	};
	struct ListStruct ListArray[1000];
	unsigned int ListHead = 0;
	// 條件1 ListArray[Entry1].NextPtr = ListArray[Entry2]
	// 條件2 ListArray[Entry2].DataH << 16 + ListArray[Entry2].DataL > ListArray[Entry1].DataH << 16 + ListArray[Entry1].DataL
	// 條件2 說明資料是遞增，找到後就不用再找
    //give two data DATA_A, DATA_B, please find the entry with Data_H == DATA_A and Data_L == DATA_B
    //and report PreEntry and FindEntry with ListNode[PreEntry].next == ListNode[FindEntry]
    //if not found report NotFound
	void founEntry(int DATA_A, int DATA_B)
	{
		int preEntry = NULL;
		int findEntry = ListHead;
		while (ListArray[findEntry] != NULL)
		{
			if (ListArray[findEntry].DataH == DATA_A && ListArray[findEntry].DataL == DATA_B)
			{
				printf("PreEntry is %d, FindEntry is %d", preEntry, findEntry);
				return;
			}
			preEntry = findEntry;
			findEntry = ListArray[findEntry].NextPtr;
		}

		printf("NotFound");
	}
	

	////Question 9
	//// printf ?
	//int B = 2;
	//void func(int** p)
	//{
	//	*p = &B;
	//}

	//int main()
	//{
	//	int A = 1, C = 3;
	//	int* ptrA = &A;
	//	func(&ptrA);
	//	printf("%d", *ptrA);
	//	return 0;
	//}
	//Ans: 2

	//Question 10
	// printf ?
	// int B = 2;
	//void func(int* p)
	//{
	//	p = &B;
	//}

	//int main()
	//{
	//	int A = 1, C = 3;
	//	int* ptrA = &A;
	//	func(ptrA);
	//	printf("%d", *ptrA);
	//	return 0;
	//}*/
	//Ans: 1


	//Question11
	//ask: the value of v ?
	//	unsigned long  v1 = 0x 00001111;
	//	 unsigned long v2 = 0x 00001202;
	//	 unsigned long v;
	//	 v = v1 & (~v2);
	//	 v = v | v2;
	//   v = (v1 & (~v2)) | v2 = (v1 | v2) & (~v2 | v2) = v1|v2 & 1 = v1|v2 = 0x 00001313


	//Question12 
	// 給一個 8-bit size的值求最高位元是在第幾個bit 
	int get_highest_bit(unsigned int n)
	{
		n |= (n >> 1);
		n |= (n >> 2);
		n |= (n >> 4);
		n |= (n >> 8);
		n |= (n >> 16);
		return n - (n >> 1);
	}
	// or 另一種解法  //1~8
	int get_highest_bit(unsigned int n)
	{
		// 2分法
		if (n == 0)
		{
			return -1;
		}
		int highest = 8;
		int shift = 0;
		if (n >> 4 == 0)
		{
			//highest = 3;
			n = n << 4;
			shift = 4;
		}

		highest = highest - shift; // actually highest is not necessary;

		if (n >> 6 == 0)
		{
			shift = shift + 2;
			n = n << 2;
		}


		if (n >> 7 == 0)
		{
			shift = shift + 1;
		}

		return 8 - shift;
	}
	// 二分法簡化
	int get_highest_bit(unsigned int n)
	{
		int k = 0;
		int highestBit = 8 - k;
		int bitCount = 4;

		int count = 1;
		while (bitCount >= 1)
		{
			if (n >> (8 - bitCount) == 0)
			{
				n = n << bitCount;
				k += bitCount;
			}
			bitCount /= 2;
		}
		return 8 - k;
	}
	//Question13
	//SET BIT(n) = 1, CLEAR BIT(n) = 0 ; n start from 0
	//寫function 把某個數的第x個bit改成1或0(改成1直接用or、改成0用mask 之後and)
	int set_bit(int x, int n)
	{
		x = x | (1 << n);
		return x;
	}

	int clear_bit(int x, int n)
	{
		x = x & ~(1 << n);
		return x;
	}


	//Question14
	// 判斷是否是2的次方 
	bool isSquare(int n)
	{
		int bitNum = get_bit_1_count(n);
		if (bitNum == 1)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	int get_bit_1_count(int n)
	{
		int count = 0;
		while (n != 0)
		{
			n = n & (n - 1);
			count++;
		}
		return count;
	}


	//Question15
	//判斷一整數是偶數還是奇數
	int main()
	{
		int x = 123;
		bool isOdd = false;
		if (x & 1 == 1) isOdd = true; // 奇數 
		else isOdd = false;	 // 偶數

		return 0;
	}

	//Question16
	//請擷取出Input中的第七個bit值 as Question17
	// (n>>6) & 1 bit count from 1 ~8;


	//Question17
	//請擷取出Input中的第N個bit值?
	int main()
	{
		int input = 12;
		int N = 6;

		int n = input >> N; // N start from 0
		int ans = n & 1;
		return 0;
	}

	//Question18
	//計算有幾個位元是 1?
	//  Ans:
	//    0x5a5a
	//    0101 1010 0101 1010
    //	-                   1
	//	------------------------------
	//	  0101 1010 0101 1001
	//	& 0101 1010 0101 1010
	//	------------------------------
	//	  0101 1010 0101 1000
	// 這樣就會消除最低 bit
    // 之後我們繼續做，就可以消除倒數第二的 bit，以此類推
	int get_bit_1_count(unsigned int n)
	{
		int count = 0;
		while (n != 0)
		{
			n = n & (n - 1);
			count++;
		}
		return count;
	}

	// 找最低位的1
	int least_significant_1_bit(int x)
	{
		return x & -x;  // x & (~x+1)
	}

	// 顛倒位元
	unsigned int reverseBit(unsigned int n)
	{
		// abcd efgh ijkl mnop qrst uvwx yzAB CDEF
		// qrst uvwx yzAB CDEF abcd efgh ijkl mnop   <= n<<16 | n>>16
		// yzAB CDEF qrst uvwx ijkl mnop abcd efgh   <= ((a & 0xFF00FF00) >> 8) | ((a & 0x00FF00FF) << 8)  1111111100000000/0000000011111111 (FF00FF00/00FF00FF)
		// CDEF yzAB uvwx qrst mnop ijkl efgh abcd   <= ((a & 0xF0F0F0F0) >> 4) | ((a & 0x0F0F0F0F) << 4)  1111000011110000/0000111100001111 (F0F0F0F0/0F0F0F0F) 
		// EFCD AByz wxuv stqr opmn klij ghef cdab   <= ((a & 0xCCCCCCCC) >> 2) | ((a & 0x33333333) << 2)  1100110011001100/0011001100110011 (CCCCCCCC/33333333)
		// FEDC BAzy xwvu tsrq ponm lkji hgfe dcba   <= ((a & 0xAAAAAAAA) >> 2) | ((a & 0x55555555) << 2)  1010101010101010/0101010101010101 (AAAAAAAA/55555555)
		unsigned int a;
		a = (n >> 16) | (n << 16);
		a = ((a & 0xFF00FF00) >> 8) | ((a & 0x00FF00FF) << 8);
		a = ((a & 0xF0F0F0F0) >> 4) | ((a & 0x0F0F0F0F) << 4);
		a = ((a & 0xCCCCCCCC) >> 2) | ((a & 0x33333333) << 2);
		a = ((a & 0xAAAAAAAA) >> 2) | ((a & 0x55555555) << 2)
		return a;
	}
	
	void printBits(size_t const size, void const * const ptr)
	{
		unsigned char *b = (unsigned char*)ptr;
		unsigned char byte;
		int i, j;

		for (i = size - 1; i >= 0; i--) {
			for (j = 7; j >= 0; j--) {
				byte = (b[i] >> j) & 1;
				printf("%u", byte);
			}
		}
		puts("");
	}

	int main()
	{
		int n = 12;
		printBits(sizeof(int), &n);
		int count = 0;
		while (n != 0)
		{
			n = n & n - 1; //消除最後的bit, 看消了幾次才得到0, 就知道總共有幾個bit is 1
			count++;
		}

		printf("1 count is : %d", count);
		return count;
	}


	void revsign(int x)
	{
		return ~x + 1;    //-x = ~x+1 <= 可記住這個
	}

	int plus1(int x)
	{
		return -~x;    //x+1 = ~(~x)+1 = -(~x)
	}

	int minus1(int x)
	{
		return ~- x;    //x = -(-x) = ~(-x)+1
	}

	// 計算32位整數的絕對值 ??? 怪
	// 負數 ~X+1;
	// 以 short x = 1為例
	// x = 00000000 00000001 =>-x = ~x + 1
	// ~x= 11111111 11111110
	// +                   1
	//--------------------------
	// -x= 11111111 11111111   <= -1的二進位

	int abs(int x)
	{
		return (x^(x >> 31)) - (x >> 31);
	}
	// 首先需要注意的是右移時會擴充套件符號位。如果x是正數，那麼x>>31=0，毫無疑問，return語句中的表示式結果就是x；如果x是負數，那麼x>>31的結果就是全1，也就是我們必須牢記的-1，於是


	// Question19 循環偵測 HappyNum
	// 19 => 1*1+9*9 = 82
	// 82 => 8*8+2*2 = 68..... if end to 1 => it is HappyNum
	// 68 => 6*6 + 8*8= 100
	// 110 => 1*1 =>1    ... end to 1
	int next_n(int n)
	{
		int sum = 0;
		while (n != 0)
		{
			int d = n % 10;
			sum += d * d;
			n /= 10;
		}
		return sum;
	}

	bool isHappyNum(int n)
	{
		int fast = n;
		int slow = n;		
		do
		{
			fast = next_n(next_n(fast));
			slow = next_n(slow);
		} while (fast != slow);

		if (fast == 1)
		{
			return true;
		}
		else return false;
	}

	// Question20 Single Number
	// Given a non - empty array of integers nums, every element appears twice except for one.Find that single one.
    // You must implement a solution with a linear runtime complexity and use only constant extra space.
	// A^B^A^C^B = A^A^B^B^C = C
	int singleNumber(int* nums, int numsSize)
	{
		int ans = nums[0];
		for (int i = 1; i < numsSize; i++)
		{
			ans = ans ^ nums[i];
		}
		return ans;

	}


	// Question21 get date after n days.
	// 
	//ans:
	struct Date
	{
		int year;
		int month;
		int day;
	};

	struct Date get_date(struct Date currentDate, int nDaysAfter)
	{
		struct Date ansDate;
		ansDate = currentDate;
		int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		//int daysInMonth_2[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		for (int i = 1; i <= nDaysAfter; i++)
		{
			ansDate.day++;
			if ((ansDate.year % 4 == 0 && ansDate.year % 100 != 0) || ansDate.year % 400 == 0)
			{
				daysInMonth[1] = 29;
			}
			else
			{
				daysInMonth[1] = 28;
			}

			if (ansDate.day > daysInMonth[ansDate.month - 1])
			{
				ansDate.month++;
				ansDate.day = 1;
				if (ansDate.month > 12)
				{
					ansDate.month = 1;
					ansDate.year++;
				}
			}
		}

		return ansDate;
	}

	int main()
	{
		struct Date currentDate;
		struct Date ansDate;
		currentDate.year = 2022;
		currentDate.month = 2;
		currentDate.day = 18;
		printf("%d-%d-%d \n", currentDate.year, currentDate.month, currentDate.day);
		struct Date newDate = get_date(currentDate, 1500);
		printf("%d-%d-%d \n", newDate.year, newDate.month, newDate.day);

		return 0;
	}


	// Question22 實作binary search
	// code : 以下做法有問題，如果要找的值有重複，答案會不一定
	int binary_search(int a[], int target, int size)
	{
		ttQuicksort(a, size);

		int index = binary_search_recur(a, 0, size - 1, target);]
		printf("%d", index);
	}

	int  binary_search_recur(int *a, int left, int right, int target)
	{
		if (right <= left)
		{
			if (left >=0 && a[left] == target)
			{
				return left;
			}
			if (right >=0 && a[right] == target)
			{
				return right;
			}
			return -1;
		}
		int mid = (left + right) / 2;
		if (a[mid] >= target)
		{
			return binary_search_recur(a, left, mid - 1, target);
		}
		else
		{
			return binary_search_recur(a, mid+1, right, target);
		}


	}

	// 以下此方法，可以調整當target重複時，要最小的index or 最大的index
	int ttBinary_search(int *a, int start, int end, int target)
	{
		int left = start;
		int right = end;
		int result = -1;

		while (right >= left)
		{
			int mid = (left + right) / 2;
			if (target < a[mid])  //回傳最大的 若target <=a[mid] 則回傳最小的index
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}

		}
		if (a[left] == target && left >=0)
		{
			result = left;
		}
		if (a[right] == target && right >=0)
		{
			result = right;
		}

		return result;
	}
	
	// quick sort
	void ttQuickSort(int *a, int start, int end)
	{
		if (start >= end)
		{
			return;
		}

		int left = start;
		int right = end;
		int pivot = start;

		while (right > left)
		{
			if (a[right] >= a[pivot])
			{
				right--;
			}
			else if (a[left] <= a[pivot])
			{
				left++
			}
			else
			{
				swpa(&a[left], &a[right]);
			}
		}
		if (left == right)
		{
			swap(&a[pivot], &a[left]);
		}

		ttQuickSort(a, start, left);
		ttQuicksort(a, left + 1, end);
	}


	// bubble sort
	void swap(int *a, int *b)
	{
		int temp = *a;
		*a = *b;
		*b = temp;
	}

	void bubble_sort(int a[], int size)
	{
		int i, j;
		for (j = 1; j < size - 1; j++)
		{
			for (i = 0; i < size - j; i++)
			{
				if (a[i] > a[i + 1])
				{
					swap(&a[i], &a[i + 1]);
				}
			}
		}
	}

	void insertion_sort(int a[], int size)
	{
		for (int i = 1; i < size; i++)
		{
			int j = i - 1;
			int key = a[i]; //key = 2, 
			while (j >= 0 && key < a[j])
			{
				a[j + 1] = a[j];
				j--;
			}
			a[j + 1] = key;
		}
	}

	void quick_sort_recursion(int a[], int start, int end)
	{
		if (end <= start)
		{
			return;
		}
		int left = start;
		int right = end;
		int key = a[start];
		while (left != right)
		{
			if (a[right] >= key && right > left)
			{
				right--;
			}
			else if (a[left] <= key && right > left)
			{
				left++;
			}
			else
			{
				if (left != right)
				{
					swap(&a[left], &a[right]);
				}
			}
		}
		swap(&a[start], &a[right]);
		quick_sort_recursion(a, start, left - 1);
		quick_sort_recursion(a, right + 1, end);
	}

	void quick_sort(int a[], int size)
	{
		quick_sort_recursion(a, 0, size - 1);
	}

	// 遞迴寫法
	int binary_search(int a[], int target, int size, int start, int end)
	{
		if (start > end)
		{
			if (a[start] == target) return start;
			if (a[end] == target) return end;
			return -1;
		}
		int mid = (start + end) / 2;
		if (target >= a[mid])
		{
			return ttBinary_search(a, mid + 1, end, target);
		}
		else
		{
			return ttBinary_search(a, start, mid - 1, target);
		}
	}

	// Question23
	// Re-write void(*(*papf)[3])(char *); 
	// typedef__________;
	// pf(*papf)[3];

    // Ans:
	// typedef void(*pf)(char*)  papf是一個指標，指向一個大小為3的陣列，陣列內放function, 此function傳入 指向char的指標, 此function不回傳


	// Question24 
	// Difference between processs and thread.

	// Ans: Process can have multi threads.
	// Process 是電腦中已執行 Program 的實體。
	// 每一個 Process 是互相獨立的。
	//	Process 本身不是基本執行單位，而是 Thread(執行緒)的容器。
	//	Process 需要一些資源才能完成工作，如 CPU、記憶體、檔案以及I / O裝置。

	// 同一個 Process 會同時存在多個 Thread。
	// 	同一個 Process 底下的 Thread 共享資源，如 記憶體、變數等，不同的Process 則否。
	//	在多執行緒中(Multithreading)，兩個執行緒若同時存取或改變全域變數(Global Variable)，則可能發生同步(Synchronization，恐龍本第六章)問題。若執行緒之間互搶資源，則可能產生死結(Deadlock，恐龍本第七章)，同樣的，如何避免或預防上述兩種情況的發生，依然是 OS 所關注並改善的。


	// Question25
	// What is "volatile"
	// Explain “volatile”.Can we use “const” and “volatile” in the same variable ? Can we use “volatile” in a pointer ?
	//一個定義為 volatile 的變量是說這變量可能會被意想不到地改變（尤其在嵌入式系統），因此編譯器不會去假設這個變量的值了。精確地說就是，優化器不會將其優化，而是在用到這個變量時必須每次都重新讀取這個變量的值，不是使用保存在暫存器裡的備份。
	//下面是 volatile 變量的幾個例子︰
	//	1. 並行設備的硬體暫存器(如︰狀態暫存器)
	//	2. 一個中斷服務子程序中會訪問到的非自動變數(Non - automatic variables)
	//	3. 多執行緒中共享的變數
	//	是的。一個例子是只讀的狀態寄存器（不應該被程式修改，但有可能被硬體修改，比如interrupt routine）。它是 volatile 因為它可能被意想不到地改變。它是 const 因為程序不應該試圖去修改它。
	//	是的。比如當一個中斷服務的子程序修改一個指向buffer的pointer時。

	// Question26
	// Explain lvalue and rvalue

	// Ans:
	// 左值 (lvalue) : 一個佔據某個特定記憶體的值。
	// 右值(rvalue) : 一個 expression 結束後就消失的值。
	//基本上這兩個定義包含了全部的值，非左即右，非右即左。
	int a = 1;
	int b = a + 1;  // 這裡的 a 被直接視為右值
	int arr[] = { a, b };
	int *p = arr;
	*(p + 1) = 10;  // 利用 * 將右值 (p + 1) 傳換成左值
    return 0;

	// Question27
	// Stack and Heap?

	// Ans:
    // Stack: 存放函數的參數、區域變數等，由空間配置系統自行產生與回收。(會稱作 stack 是由於其配置遵守 LIFO)
    // Heap : 一般由程式設計師分配釋放，執行時才會知道配置大小，如 malloc / new 和 free / delete。(注意其資料結構不是 DS 中的 heap 而是 link - list)


	// Question28
	// Print?
	int main()
	{
		int arri[] = { 1, 2 ,3 };
		int *ptri = arri;

		char arrc[] = { 1, 2 ,3 };
		char *ptrc = arrc;

		printf("sizeof arri[] = %d ", sizeof(arri));
		printf("sizeof ptri = %d ", sizeof(ptri));

		printf("sizeof arrc[] = %d ", sizeof(arrc));
		printf("sizeof ptrc = %d ", sizeof(ptrc));

		return 0;
	}

    // Ans:
	// sizeof arri[] = 12 sizeof ptri = 4 sizeof arrc[] = 3 sizeof ptrc = 4
    // Size of an array is number of elements multiplied by the type of element, 
	// that is why we get sizeof arri as 12 and sizeof arrc as 3. 
	// Size of a pointer is fixed for a compiler.All pointer types take same number of bytes for a compiler.
	// That is why we get 4 for both ptri and ptrc.


	// Question29
	// Print?
	int main()
	{
		int a;
		char *x;
		x = (char *)&a;
		a = 512;
		x[0] = 1;
		x[1] = 2;
		printf("%dn", a);
		return 0;
	}

    // Ans:
	// Machine dependent
	// Explanation : Output is 513 in a little endian machine.To understand this output, let integers be stored using 16 bits.
	// In a little endian machine, when we do x[0] = 1 and x[1] = 2, 
	// the number a is changed to 00000001 00000010 which is representation of 513 in a little endian machine.


	// Question30
	// int (*p)[3] ???
	// int *p[3] ???  array with 3 integer pointer  p[0], p[1], p[2] each of them is a pointer to integer
	// For int (*p)[3]: Here “p” is the variable name of the pointer which can point to an array of three integers.
	// p -> a[3] p指向有三個int的陣列
	int main()
	{
		// Declaring a pointer to store address
		// pointing to an array of size 3
		int(*p)[3];

		// Define an array of size 3
		int a[3] = { 1, 2, 3 };

		// Store the base address of the
		// array in the pointer variable
		p = &a;   // p => ([1,2,3])

		// Print the results
		for (int i = 0; i < 3; i++) {
			cout << *(*(p)+i) << " ";   // 
		}

		//ans: 1,2,3  *p = a, *p+1 = a+1, *(*p+1) = *(a+1)=a[1] = 2;

		return 0;
	}

	// For int *p[3]: Here “p” is an array of the size 3 which can store integer pointers.
	// p[0], p[1], p[2] p為三個pointer的陣列
	int main()
	{
		// Declare an array of size 3 which
		// will store integer pointers
		int* p[3];

		// Integer variables
		int a = 1, b = 2, c = 3;

		// Store the address of integer
		// variable at each index
		p[0] = &a;
		p[1] = &b;
		p[2] = &c;

		// Print the result
		for (int i = 0; i < 3; i++) {
			cout << *p[i] << " ";
		}
		//ans: 1,2,3
		return 0;
	}


	// Question31
	// What does the following C - statement declare ? int(*f) (int*);

	// Ans:
	// int* f(int *)---- f is a function which takes integer pointer as an argument and returns address of an integer.
	// int(*f)(int *)-- - f is a pointer to a function which takes integer pointer as argument and returns intger.
	//  int *f()表示這個函式的功能是返回一個地址。
	//	int(*f)()表示這是一個函式的指標。它要指向一個函式才能有用，指向一個函式之後可以用它來代替該函式。之後使用這個指標相當於使用該函式。
	//	int *a[]是一個指標陣列，表示陣列中的每一個元素都是一個指標, 可以指向一個int型別的數值。
	//	int(*a)[]這是一個指向多維陣列的指標變數。

	// Question32
	// 給一個int a[20]已排序的陣列，請寫一個function(a, size)能印出0~500的數字，且不包含a陣列內的元素，請用最少的時間和空間複雜度完成。
	void function(int a[], int size)
	{
		int index = 0;

		while (a[index] < 0)
		{
			index++;
		}

		for (int i = 0; i <= 500; i++)
		{
			if (i >= a[index] && index <size)
			{
				index++;
			}
			else
			{
				printf("%d,", i);
			}
		}
	}

	// Question33
	// Q2: 給一個int a[20]已排序的陣列，請寫一個function(a, size, b)能依照參數b(b = 0~4)別印出該區間的數字，且不包含a陣列內的元素，例如：
	// b = 0: 0~99
	// b = 1: 100~199

	void function(int a[], int size, int b)
	{
		int start = b * 100;
		int *ptr = a;
		for (start = b * 100; start < start + 100; start++)
		{
			if (start >= *ptr)
			{
				ptr++;
			}
			else 
			{
				printf("%d,", start);
			}
		}
	}

	// Question 34
	// 給一個unsigned short，問換算成16進制後四個值是不是一樣，是回傳1，否則0
	// 例如：0xFFFF return 1, 0xAAAB return 0
	int getsame(unsigned short n)
	{
		unsigned int a[4];
		for (int i = 0; i < 4; i++)
		{
			a[i] = n << (i * 4);
			a[i] = n >> 12;
		}
		if (a[0] == a[1] == a[2] == a[3])
		{
			return 1;
		}
		return 0;
	}

	// Question  35
	// 一個non empty linked list 找middle noe的值，如果有兩個Middle node, return second middle node
	struct Node {
		int data;
		Node * next;
	};
	typedef struct Node Node;

	void addNode_front(Node **head, int data)
	{
		if (*head != NULL)
		{
			Node *newNode = (Node *)malloc(sizeof(Node));
			newNode->data = data;
			newNode->next = *head;
			*head = newNode;
		}
	}

	void addNode_back(Node **head, int data)
	{
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->data = data;
		newNode->next = NULL;

		Node *current = *head;
		if (*head == NULL)
		{
			*head = newNode;
			return;
		}
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = newNode;

	}

	void insertNode(Node **previousNode, int data)
	{
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->data = data;
		newNode->next = (*previousNode)->next;

		(*previousNode)->next = newNode;
	}

	void print_node_list(Node *head)
	{
		while (head != NULL)
		{
			printf("%d->", head->data);
			head = head->next;
		}
		printf("\n");

	}

	Node* getMiddleNode_better(Node *head)
	{
		Node *fast = head;
		Node *slow = head;

		while (fast != NULL && fast->next != NULL) {
			fast = fast->next;
			/*if (fast == NULL)
			{
				break;
			}*/
			fast = fast->next;
			slow = slow->next;
		}
		return slow;
	}

	void delete_node(Node **head, int dataToDelete)
	{
		//Node *curNode = (Node *)malo(sizeof(Node));
		Node *curNode = *head;
		Node *preNode = NULL;

		if (curNode->data == dataToDelete)
		{
			*head = curNode->next;
			free(curNode);
			return;
		}

		for (; curNode != NULL; curNode = curNode->next)
		{
			if (curNode->data == dataToDelete)
			{
				preNode->next = curNode->next;
				curNode->next = NULL;
				free(curNode);
				break;
			}
			else
			{
				preNode = curNode;
			}
		}

	}

	void delete_node_by_position(Node **head, int position)
	{
		int index = 0;
		Node *curNode = *head;
		Node *preNode = NULL;
		if (position == 0)
		{
			*head = (*head)->next;
			free(curNode);
			free(preNode);
			return;
		}

		for (; curNode != NULL; curNode = curNode->next)
		{
			if (index == position)
			{
				preNode->next = curNode->next;
				free(curNode);
				break;
			}
			preNode = curNode;
			index++;
		}

		// 另一種做法, 停在要刪除的前一個
		/*for (int i = 0; i < position-1; i++)
		{
			curNode = curNode->next;
		}
		curNode->next = curNode->next->next;
		Node *del = curNode->next;
		del->next = NULL;
		free(del);*/
		return;
	}

	int main(void)
	{
		Node *head = NULL;
		for (int i = 0; i <= 10; i++)
		{
			addNode_back(&head, i);
		}

		print_node_list(head);
		return 0;
	}


	// Question36
	// 印出 N層
	//   *    N= 1
	//  ***   N=2
	// *****  N=3

	void print_triangle(int n)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < (2 * n + 1); j++)
			{
				int layercount = 2 * n - 1;
				int startCount = 2 * i + 1;
				int preSpace = (layercount - startCount) / 2;
				if (j < preSpace)
				{
					printf(" ");
				}
				else if (j >= preSpace && j < startCount + preSpace)
				{
					printf("*");
				}
				else
				{
					printf(" ");
				}
			}
			printf("\n");
		}
	}

	// Question37 費式數列
	// 11,12,23,35,58,....N 用一個函數 輸入值是位置的值n, 要找出相對應的值'

	int function_fig2(int n)
	{
		int i = 11;
		int j = 12;
		if (n == 0)
		{
			return 0;
		}
		if (n == 1)
		{
			return i;
		}
		if (n == 2)
		{
			return j;
		}
		
		return function_fig2(n - 1) + function_fig2(n - 2);
	}


	int function_fib(int n)
	{
		int i = 11;
		int j = 12;
		if (n == 0)
		{
			return i;
		}
		else if (n == 1)
		{
			return j;
		}
		else
		{
			return function(n - 1) + function(n - 2);

			// or 以下方法
			int pre = j;
			int prepre = i;
			int sum = i + j;
			for (int k = 2; k < n; k++) //n= 3
			{
				prepre = pre;
				pre = sum;
				sum = pre + prepre;

			}
			return sum;
		}
	}
	
	// n = 4
	// function(3)+function(2)
	// = function(2) + function(1) + function(1) + function(0)


	// Qustion38
	// Not sorted array search, use binary-tree?????



	// Question39
	// What is hash function
	// ans:
	// hash function 將 輸入值經由function計算返回一儲存陣列or table大小內的index, 
	// hash function 將一個輸入值mapping到一個範圍內的值
	// index可能會重複，因此需處理衝突狀況
	// ex. arr[100];  現在有一個要儲存的值為1005, 
	// int index = hashfunc(1005);  arr[index] => add node of 1005


	// Question40
	// Global 直接宣告參數不給值跟function 裡面宣告參數不給值, 直接印會印出什麼
	// Global變數宣告不初始化，存在bss, 預設為0
	// 區域變數宣告不初始化，存在stack，直接印 編譯不會過。

	// Question41
	//兩個 String還是Char陣列 分別丟同樣的字串,問如果直接 == 會有什麼樣的結果, true, false或不能編譯
	// strA[] = {'A','B','C'};
	// strB[] = {'A','B','C'};   strA == strB return false;  *strA == *strB return true;  
	// const char *strA = "ABC";
	// const char *strB = "ABC"; strA == strB return true;  *strA == *strB => 'A' = 'A' return true
	//  const char *strA = "ABCd";
	// const char *strB = "ABCD"; strA == strB return false; *strA == *strB => 'A' = 'A' return true

	// Question42
	//a) int a; // An integer
	//b) int *a; // A pointer to an integer
	//c) int **a; // A pointer to a pointer to an integer
	//d) int a[10]; // An array of 10 integers
	//e) int *a[10]; // An array of 10 pointers to integers
	//f) int(*a)[10]; // A pointer to an array of 10 integers
	//g) int(*a)(int); // A pointer to a function a that takes an integer argument and returns an integer
	//h) int(*a[10])(int); // An array of 10 pointers to functions that take an integer argument and return an integer
	//這題型感覺算重要，有舉出一個考

	// Question42
	// Swap using bitwise

	// Ans:
	void swap_bitwise(int *a, int *b)
	{
		int x = *a ^ *b;
		*b = x ^ *b;
		*a = x ^ *a;

		// or 

		*a = *a ^ *b;
		*b = *a ^ *b;
		*a = *a ^ *b;
	}

	// Question43 
	// Missing Number Problem （檢查缺少的正整數）
	// 陣列放入 1 到 10 的正整數，但是少了一個。找出少了哪一個。, 
	// int array[9] = {2, 3, 5, 9, 4, 6, 10, 8, 1}
	//Ans:

	int find_missingNum(int *a, int size, int totalNums)
	{
		
		int total[totalNums];
		for (int i = 0; i < totalNums; i++)
		{
			total[i] = i + 1;  // 放入1~totalNum
		}

		int n = 0;
		for (int i = 0; i < totalNums; i++)
		{
			n = n ^ total[i];
		}
		for (int i = 0; i < size; i++)
		{
			n = n ^ a[i];
		}
		return n;
	}

	//Question 44
	extern void func1(void);
	extern void func2(void);
	extern void func3(void);
	extern void func4(void);
	extern void func5(void);

	void main(int n)
	{
		void (*fpt[5])(void):
		if n == 1 execute func1;
		if n == 2 execute func2;
		if n == 3 execute func3;
		if n == 4 execute func4;
		if n == 5 execute func5;
	}

	//保證 n 一定是上面五個數字之一
    //不能用if 和 switch case, 請用你認為最快的方法實作main

    //Ans :
	void main(int n)
	{
		void (*fp[5])();
		fp[0] = func1;
		fp[1] = func2;
		fp[2] = func3;
		fp[3] = func4;
		fp[4] = func5;

		fp[n - 1]();
	}


	// Question45
	extern void func1(void);
	extern void func2(void);
	extern void func3(void);
	extern void func4(void);
	extern void func5(void);

	void main(int n)
	{
		if n == 33 execute func1;
		if n == 67 execute func2;
		if n == 324 execute func3;
		if n == 231 execute func4;
		if n == 687 execute func5;
	}
	// 保證 n 一定是上面五個數字之一`,使用if, 請用你認為最快的方法實作main
	void main(int n)
	{
		if (n < 231)
			if (n != 67)
				func1();
			else
				func2();
		else if (n > 231)
			if (n != 324)
				func3();
			else
				func5();
		else
			func4();
	}

	// Question46
	// Reverse a string
	// Ans:  直接反轉原字串，尚位找到解法，網路上的無法執行。
	char *ReverseString(char *str)
	{
		
		int count = 0;
		while (*str != '\0')
		{
			str++;
			count++;
		}
		char *reverString[count+1];
		str--;
		for (int i = 0; i < count; i++)
		{
			*reverString = *str;
			str--;
			reverString++;
		}
		reverString++;
		*reverString = '\0';

		return reverString;
	}
	

	// Question47
	//寫一個“標準”巨集MIN ，這個巨集輸入兩個參數並返回較小的一個。  
	// Ans:  加上括號最安全
    // #define MIN(a,b) ((a) < (b) ? (a) : (b))

	//寫一個 聚集MALLOC，取得一個空間 (type, siez)
	// #define MALLOC ((type) *)malloc((size) * sizeof(type))
	// #define MyDefine(x,y) do{  \
			printf("%c \n", x);   \
			printf("%c \n", y);   \
	// }while(0)


	// Question48
	// Write a MARCO to calculate the square of integer a   
	// Ans:
	// #define SQUARE(a) ((a)*(a))

	// Question49
	//Write a code to reverse the linked list. For example: [0] -> [n], [1]->[n-1],…[n]->[0].
	void tttReverseLinkedList(Node **head)
	{
		Node *ptr = *head;
		Node *pre = NULL;
		Node *nextNode = NULL;
		if (ptr == NULL)
		{
			return;
		}
		if (ptr->next == NULL)
		{
			return;
		}

		while (ptr != NULL && ptr->next != NULL)
		{
			nextNode = ptr->next;
			ptr->next = pre;
			pre = ptr;
			ptr = nextNode;
		}

		ptr->next = pre;
		*head = ptr;
	}


	// Question50
	// Find the possible error
	// Int ival;
	// Int **p;
	// Ival = *p;
	// Ans:
	// reference a pointer to a int

	// Question51
	//What is the possible error of below SQR function
	int SQR(volatile int *a) {
		return (*a)*(*a);
	}
	// Ans: 其他地方有可能改變*a的值，因為她是volatile, 
	// 以下寫法較佳
	long square(volatile int *ptr)
	{
		int a;
		a = *ptr;
		return a * a;
	}

	// Question52 
	// 用預處理指令#define 聲明一個常數，用以表明1年中有多少秒（忽略閏年問題）
	// #define secInYear (365)*(24)*(3600)UL //可能溢位 加上UL

	// Question53
	//一個整型數（An integer） => int a;
	//一個指向整型數的指標（A pointer to an integer）=> int *a
	//一個指向指標的的指標，它指向的指標是指向一個整型數（A pointer to a pointer to an integer） => int **a
	//一個有10個整型數的陣列（An array of 10 integers） => int a[10]
	//一個有10個指標的陣列，該指標是指向一個整型數的（An array of 10 pointers to integers） int *a[10]
	//一個指向有10個整型數陣列的指標（A pointer to an array of 10 integers） int (*a)[10]
	//一個指向函數的指標，該函數有一個整型參數並返回一個整型數（A pointer to a function that takes an integer as an argument and returns an integer） int (*fptr)(int) // int *fptr(int) => 則是一個function 傳入int 回傳 int pointer
	//一個有10個指標的陣列，該指標指向一個函數，該函數有一個整型參數並返回一個整型數（ An array of ten pointers to functions that take an integer argument and return an integer ） int (*ptr[10])(int)

	// Question54
	// What does the following C-statement declare? int (*f) (int*);
	//Ans:
	//A pointer to a function that takes an integer pointer as argument and returns an

	//The following ‘C’ statement : int *f[](); declares:
	//Ans:
	//Array of functions returning pointers to integers

	//The following statement in ‘C’ int (*f())[ ]; declares
	//Ans:
	//a function returning a pointer to an array of integers.



	// Question55
	// LeetCode CountingElement

	// Question56
	// write a code that check the input is a multiple of 3 or not without using division or mod
	int check3multiple(int n)
	{
		if (n < 3 && n > 0)
		{
			return 0;
		}
		if (n == 0 || n == 3) retrun 1;
		while (n - 3 > 0)
		{
			n -= 3;
		}

		return check3multiple(n);
	}
	//這個是剛好用 3 的特性來解
	int divide3(int a) {
		int ans = 0;
		while (a) {
			ans += a & 1;
			a >>= 1;
			ans -= a & 1;
			a >>= 1;
		}
		return !(ans);
	}

	//通用算法(This can use for any number)
	/*
	set Number = abcde(2進位)
	abcde = abc<<2 + de
		  = abc*(4) + ed
		  = abc(*3) + (abc + de)
	任何數字都可以用類似的方式拆出用 &跟<<完成的判斷
	*/

	int isMult3(unsigned int n)
	{
		if (n == 0)
			return 1;
		if (n < 3)
			return 0;

		//   (除4的商數 + 除4的餘數) 為3的倍數 
		//   假設 N = 4a+b (a為除4的商, b為除4的餘數) N = 4a + b = 3a + (a+b), 若a+b 為3的倍數則N為3的倍數
		//   所以 => (除4的商數 + 除4的餘數) 為3的倍數 
		//   求除4的餘數 n & (4-1)
		n = (n >> 2) + (n & 3);

		/* Recursive call till you get n
			or a special terminate condition */
		return(isMultN(n));
	}

	// Question57
	// 求最大公因數

	//Ans:
	int getMaxCommonFactor(int a, int b)
	{
		int max = (a > b) ? a : b;
		int min = (a > b) ? b : a;
		int mod = max % min;	
		if (mod == 0)
		{
			return min;
		}
		return getMaxCommonFactor(min, mod);
	}

	// Question58
	//給你一個unsigned short，問換算成16進制後四個值是不是一樣，是回傳1，否則0
	//Ans:
	int is2byteHaveSameHex(unsigned short n)
	{
		unsigned short a[4];
		for (int i = 0; i < 4; i++)
		{
			a[i] = n << (i * 4);
			a[i] = a[i] >> 12;
		}

		if (a[0] == a[1] && a[1] == a[2] && a[2] == a[3])
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	// Question59
	//What is “const” ? and what is the meaning of :
	const int a;				//    a為常量
	int const a;				//    a為常量
	const int *a;				// *ptr為常量
	int const *a				// *ptr為常量
	int * const a;				//  ptr為常量；
	int const * a const;		//*ptr、ptr均為常量；
	const int * const ptr;		//*ptr、ptr均為常量；
	//const 代表只可讀不可改。
	//1. 一個常數型整數
	//2. 同 1，一個常數型整數
	//3. 一個指向常數型整數的指標(整型數不可修改，但指標可以)
	//4. 同3
	//5. 一個指向整數的常數型指標(指標指向的整數可以修改，但指標不可修改)
	//6. 一個指向常數型整數的常數型指標(指標指向的整數不可修改，同時指標也不可修改)
	//7. 同6

	// Question60
	//What is the difference between “Inline Function” and “Macro” ?
	//Macro是在預處理時直接單純的文字替換，inline function是在compile階段時，直接取代function。比較下面兩個例子：
	//	inline寫法：
	//	inline int square(int x) {
	//	return x * x;
	//}
	//output: SQUARE(3 + 2) →(3 + 2) * (3 + 2) = 25
	//Macro寫法：
	//#define SQUARE(x) (x * x)
	//output : SQUARE(3 + 2) → 3 + 2 * 3 + 2 = 11

	// Question61
	// Explain “static” ?
	//	1. static 出現在變數前，且該變數宣告於函式中(C / C++)：
	//	局部變數加上 static 修飾後便不會因為離開可視範圍而消失。
	//	2. static 出現在變數前，且該變數不是宣告於函式中(C / C++)：
	//	讓變數只限定在該檔案內，而不是整個程式中（解決編譯時連結多個檔案造成相同變數名衝突）。
	//	3. static 出現在類別的成員變數前(C++ only)：
	//	表示該變數不屬於某個類別實例，他屬於這個類別，所有以此類別生成出來的實例都共用這個變數。
	//	4. static 出現在類別的成員函式之前(C++ only)：
	//	表示該函式不屬於某個類別實例，他屬於這個類別，所有以此類別生成出來的實例都共用這個函式（即便我們沒有產生實例出來，我們也隨時可以取用這個函式）（同 python 的 @static method）。


	// Question62
	// 計算m和n中不同的位的個數
	// Ans;
	int getDifferentBitCount(int m, int n)
	{
		int n = m ^ n;  //xor 不同為1, 相同為0
		int count = 0;
		while (n != 0)
		{
			n = n & (n - 1);
			count++;
		}

		return count;
	}
}


