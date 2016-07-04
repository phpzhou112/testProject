// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<algorithm>
#include<iostream>
#include<vector>
#include<deque>
#include<string>
#include<time.h>
#include<random>
using namespace std;

class AAA
{
private:
    int x;
    int y;
public:
    AAA(int a, int b) :x(a), y(b){};

    friend ostream& operator << (ostream &os, AAA &A)
    {
        os << "(" << A.x << ", " << A.y << ")";
        return os;
    }

    bool operator == (const AAA &A) const  //find 没有强制要求const，所以这里const不写也可以
    {
        return (x == A.x && y == A.y);
    }
};

class CEven
{
public:
    bool operator ()(int x)
    {        
        return !(x % 2); //使用位运算判断奇数偶数？ !(x & 1)
    }
};

bool IsEven(int x)
{
    return !(x & 1);
}

void TestVector()
{
    vector<int> iVec{ 1, 4, 6, 2, 8, 3, 9, 7, 5 };
    vector<int>::iterator it;

    //find --> 查找元素 --> 返回迭代器
    it = find(iVec.begin(), iVec.end(), 8);
    cout << "iVec::*it: " << *it << endl;

    //对数组使用 find，返回一个 指向值的指针 (这就相当于迭代器，可以通过 *p 访问元素)
    int arr[] = { 1, 4, 6, 2, 8, 3, 9, 7, 5 };
    int *p = find(arr, arr + sizeof(arr) / sizeof(arr[0]), 9);
    cout << "arr::*p: " << *p << endl;

    //但是 对于关联容器查找元素，不要使用这个find，而应该使用 关联容器的成员函数find
    //因为 使用这个 find 效率很低 O(N); 成员函数的效率 O(logN)

    //error C2678 : 二进制“ == ” : 没有找到接受“AAA”类型的左操作数的运算符(或没有可接受的转换)        
    AAA arrA[] = { AAA(1, 1), AAA(1, 2), AAA(3, 2), AAA(5, 7), AAA(1, 6) };
    AAA *pA = find(arrA, arrA + sizeof(arrA) / sizeof(arrA[0]), AAA(5, 7));
    cout << "arrA::*pA: " << *pA << endl;//找不到则返回 end(),直接输出会崩溃

    //find_if  找第一个满足条件的元素 的迭代器位置
    //已经学了两种方法：仿函数 和  函数指针
    it = find_if(iVec.begin(), iVec.end(), CEven());
    it = find_if(iVec.begin(), iVec.end(), IsEven);
    //第三种方法：拉姆达表达式-->就是一个匿名函数，格式：[](参数列表){函数代码}
    it = find_if(iVec.begin(), iVec.end(), [](int x){return !(x & 1);});
    cout << "iVec 中第一个偶数:" << *it << endl;

    //怎么找出iVec中所有偶数？
    cout << "iVec 中所有偶数: ";
    it = iVec.begin();
    while (1)
    {
        it = find_if(it, iVec.end(), [](int x){ return !(x & 1); });
        if (it == iVec.end())
        {
            break;
        }
        cout << *it << " ";
        it++; //从找到的元素的下一个位置继续往后找
    }
    cout << endl;
}

void TestAlg1()
{
    vector<int> iVec{ 1, 3, 5, 7, 9 };
    vector<int> iVec1;
    vector<int> iVec2;
    vector<int>::iterator it;
    int iRet;

    //all_of  判断某个区间的元素是否所有元素满足某个条件
    //any_of  判断..............是否存在元素............
    //none_of 判断..............所有元素都不满足某个条件
    iRet = all_of(iVec.begin(), iVec.end(), [](int x){return x & 1; });
    cout << "所有元素都是奇数?:" << (iRet?"Yes":"No") << endl;
    iRet = any_of(iVec.begin(), iVec.end(), [](int x){return x > 5; });
    cout << "存在大于5的元素 ?:" << (iRet ? "Yes" : "No") << endl;
    iRet = none_of(iVec.begin(), iVec.end(), [](int x){return x > 10; });
    cout << "没有大于10的元素 ?:" << (iRet ? "Yes" : "No") << endl;

    //for_each 对区间内所有元素执行某个操作
    cout << "iVec中所有元素:";
    for_each(iVec.begin(), iVec.end(), [](int x){ cout << x << " "; });
    cout << endl;
    //-->for_each 遍历区间迭代器，依次对拉姆达表达式传入 *it
    //我们想把 iVec中所有元素 加上 1 ? 注意：使用引用传递入参 (函数调用时传入 *it 的引用)
    for_each(iVec.begin(), iVec.end(), [](int &x){ ++x; });
    cout << "iVec中所有元素:";
    for_each(iVec.begin(), iVec.end(), [](int x){ cout << x << " "; });
    cout << endl;

    //find, find_if 查找第一个元素，第一个满足条件的元素(举例见 TestVector())
    //find_if_not   查找第一个不满足条件的元素，事实上，使用 find_if 就可以达到这个函数的目的
    //find_end      查找最后一个子序列的位置, 返回迭代器，指向子序列的开始位置
    //find_first_of ！！！不是找第一个子序列，而是找 第一个存在于子序列中的元素位置
    //adjacent_find  找连续两个元素相等的元素位置 (第一个，相邻且相等)
    iVec.assign({ 1, 2, 3, 7, 8, 9, 1, 2, 3, 7, 5, 3, 1, 2, 3, 4 });
    iVec1.assign({ 1, 2, 3, /*7*/});
    it = find_end(iVec.begin(), iVec.end(), iVec1.begin(), iVec1.end());
    cout << "最后一个子序列的位置: ";
    for_each(it, iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    iVec1.assign({ 7, 5, 3, 99});
    //从 iVec.begin() 开始，到 end(), 如果 元素存在于 iVec1 中，则返回这个迭代器
    //这里找到的是第一个 3 
    //跟 find 类似，只是说 find 只能查某个元素，这个能查 多个元素
    it = find_first_of(iVec.begin(), iVec.end(), iVec1.begin(), iVec1.end());
    cout << "第一个存在于子序列的元素位置: ";
    for_each(it, iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    iVec.assign({1,2,3,3,4,5,5,6,7,7,9});
    it = adjacent_find(iVec.begin(), iVec.end());
    cout << "第一对相邻相等的元素:" << *it << ", " << *(it+1) << endl;

    vector<string> sVec{ "aaa", "BB", "cccc", "DDDD", "ee", "ff" };
    vector<string>::iterator sIt;
    //找第一对长度相等的字符串位置
    sIt = adjacent_find(sVec.begin(), sVec.end(),
        [](string s1, string s2){ return s1.length() == s2.length(); });
    cout << "第一对长度相等的字符串:" << *sIt << ", " << *(sIt+1) << endl;

    //count, count_if 统计元素个数，统计满足条件的元素个数 (已讲)
    //mismatch 找两个序列中，第一对不相等的元素位置, 返回一个pair<it,it> 分别指向两个容器的不等元素位置
    //1：第二个区间，只需要提供 开始位置，mismatch 函数内部会从这个位置不停往后找
    //            和 第一个区间内元素比较，假如第二个区间比较短，可能出现 第二个区间越界崩溃(取*end()的值)
    //            所以，第二个区间，我们一般填写 长度比较长的 那个区间
    //2：不限于比较两个相同类型容器
    //3：可以增加比较函数
    iVec1.assign({ 1, 3, 5, 7, 8, 4, 6, });
    iVec2.assign({ 1, 3, 5, 7, 9, 2, 4, 6 });
    typedef vector<int>::iterator  VITER;
    pair<VITER, VITER> pairVec = 
        mismatch(iVec1.begin(), iVec1.end(), iVec2.begin());
    cout << "第一对不相等元素:" << *(pairVec.first) << ", " 
        << *(pairVec.second) << endl;

    iVec1.assign({ 1, 3, 5, 7, 9 });
    iVec2.assign({ 1, 3, 5, 7 });
    //mismatch(iVec1.begin(), iVec1.end(), iVec2.begin()); 这样会导致崩溃

    //不限于相同容器
    int iArr[] = { 1, 3, 5, 7, 8, 10 };
    mismatch(iVec1.begin(), iVec1.end(), iArr);

    vector<string>  sVec1{ "aa", "bb", "ccc", "dddd" };
    vector<string>  sVec2{ "ab", "cd", "efg", "hij" };
    //找第一对长度相等的字符串位置
    mismatch(sVec1.begin(), sVec1.end(), sVec2.begin(),
        [](string s1, string s2){ return s1.length() == s2.length(); });
}

void TestAlg2()
{
	vector<int> iVec;
	vector<int> iVec1;
	vector<int> iVec2;
	vector<string> sVec;
	vector<int>::iterator it;
	vector<int>::iterator it1;
	vector<int>::iterator it2;
	vector<string>::iterator sIt;
	int iRet;

	//equal 判定两个容器，在某段区间内是否相等
	//对于第三个参数，没有区间的上限，所以，和mismatch一样，如果长度不够，会出异常
	//所以把长的区间方后面
	iVec1.assign({ 1, 5, 7, 4, 8 });
	iVec2.assign({ 0, 5, 7, 4, 9, 1 });
	iRet = equal(iVec1.begin() + 1, iVec1.end() - 1, iVec2.begin() + 1);
	cout << "iVec1 equal iVec2? : " << (iRet ? "YES" : "NO") << endl;
	//vs2015 支持 第四个参数指定区间边界
	//iRet = equal(iVec1.begin() + 1, iVec1.end() - 1, 
	//						iVec2.begin() + 1, iVec2.begin()+2);
	//和mismatch一样， equal 还支持比较函数作为第四个参数(相等运算符)

	//is_permutation 判断两个区间内元素是不是一样的(顺序可以不一样)
	//第二个区间，只需要传入起始位置，如果长度不够，也会出问题
	//同样的，也支持传入比较函数作为 第四个参数(相等运算符)
	iVec1.assign({ 1, 5, 7, 4, 8 });
	iVec2.assign({ 4, 8, 1, 7, 5, 1 });
	iRet = is_permutation(iVec1.begin(), iVec1.end(), iVec2.begin());
	cout << "permutation? : " << (iRet ? "YES" : "NO") << endl;

	vector<string>  sVec1{ "aa", "bb", "ccc", "dddd" };
	vector<string>  sVec2{ "abbc", "cd", "ab", "hij" };
	//判定字符串是否一样
	iRet = is_permutation(sVec1.begin(), sVec1.end(), sVec2.begin());
	cout << "[1]string permutation?: " << (iRet ? "YES" : "NO") << endl;
	//使用自定义比较方式(判定长度)
	iRet = is_permutation(sVec1.begin(), sVec1.end(), sVec2.begin(),
		[](string s1, string s2){ return s1.length() == s2.length(); });
	cout << "[2]string permutation?: " << (iRet ? "YES" : "NO") << endl;

	//search 查找第一个子序列 （和 find_end 想对应）
	//返回 前面那个区间的 迭代器
	//可以增加相等的判定条件，作为第 5 个参数，使用方法 同 mismatch
	iVec1.assign({ 1, 3, 4, 5, 7, 4, 5, 8, 7, 4, 5 });
	deque<int> iDeq1{ 4, 5 };
	it = search(iVec1.begin(), iVec1.end(), iDeq1.begin(), iDeq1.end());
	cout << "第一个子序列开始位置: ";
	for_each(it, iVec1.end(), [](int x){cout << x << " "; });
	cout << endl;

	//search_n 查找连续 N 个 等于 M 的元素的位置
	iVec.assign({ 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 4, 4, 7, 8 });
	it = search_n(iVec.begin(), iVec.end(), 2, 4); //查找连续两个等于4的元素位置
	cout << "连续2个等于 4 的位置:";
	for_each(it, iVec.end(), [](int x){cout << x << " "; });
	cout << endl;

	//search_n 可以增加条件
	//1: 可以增加判断相等的条件
	//2: 可以增加其他判断条件	
	sVec.assign({ "abbc", "cd", "ab", "hiaj", "Bbac", "AAAA", "D" });
	//查找连续 3 个长度为 4 的字符串位置
	//这里 拉姆达表达式 中的 b 参数，就是 4 (search_n 的第4个参数)
	sIt = search_n(sVec.begin(), sVec.end(), 3, 4,
		[](string a, int b){ return a.length() == b; });
	cout << "连续 3个长度为 4 的字符串位置:";
	for_each(sIt, sVec.end(), [](string s){cout << s << " "; });
	cout << endl;
	//查找连续 3 个 小于于 "Z" 的字符串位置 （这里的小于，就是默认比较ASCII）
	//拉姆达表达式第一个入参必须是 容器内元素的类型
	//拉姆达表达式第二个入参必须是 search_n 第 4 个参数的类型
	sIt = search_n(sVec.begin(), sVec.end(), 3, "Z",
		[](string s1, string s2){ return s1 < s2; });
	cout << "连续 3 个小于 \"Z\" 的字符串位置:";
	for_each(sIt, sVec.end(), [](string s){cout << s << " "; });
	cout << endl;

	//copy    把一段区间的元素值，赋值给另一段区间 
	//				(第二段区间长度必须足够，否则越界异常)
	//copy_n  拷贝 n 个长度的内容，这里就只需要指定两个 区间的起始位置，和拷贝长度
	//copy_if 对区间内满足某个条件的函数执行拷贝操作
	//copy_backward  第二个区间指定结束位置，两个区间从结束位置开始往前拷贝
	iVec1.assign({ 1, 4, 7, 8, 9, 5 });
	iVec2.assign({ 2, 2, 2, 2, 2, 2, 2, 2, 2 });
	copy(iVec1.begin(), iVec1.end(), iVec2.begin());
	cout << "copy to iVec2:";
	for_each(iVec2.begin(), iVec2.end(), [](int x){cout << x << " "; });
	cout << endl;

	copy_n(iVec1.begin(), 3, iVec2.begin() + iVec1.size());
	cout << "copy_n to iVec2:";
	for_each(iVec2.begin(), iVec2.end(), [](int x){cout << x << " "; });
	cout << endl;

	iVec1.assign({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }); 
	iVec2.clear();
	iVec2.resize(10);
	//复制所有奇数到 iVec2
	copy_if(iVec1.begin(), iVec1.end(), iVec2.begin(), [](int x){return x & 1; });
	cout << "复制所有奇数到iVec2:";
	for_each(iVec2.begin(), iVec2.end(), [](int x){cout << x << " "; });
	cout << endl;

	iVec1.assign({ 1, 2, 3, 4, 5 });
	iVec2.clear();
	iVec2.resize(10);
	copy_backward(iVec1.begin(), iVec1.end(), iVec2.end());
	cout << "拷贝元素到iVec2末尾：";
	for_each(iVec2.begin(), iVec2.end(), [](int x){cout << x << " "; });
	cout << endl;

	//move  move_backward 功能 和 copy, copy_backward 一样 ！！！！！
	//区别:  类似于 memmove（块拷贝） 和memcpy（顺序拷贝） 的区别
	//	实测：现在 memmove 和 memcpy 功能是一样的

	//swap       交换两个迭代器的值(迭代器变了)
	//iter_swap  交换迭代器指向的值，(值变了)
	//swap_ranges  交换容器内一段区间的值 （相当于在区间内依次调用 iter_swap）
	iVec1.assign({ 1, 2, 3, 4 });
	iVec2.assign({ 5, 6, 7, 8 });
	it1 = iVec1.begin();
	it2 = iVec2.begin();
	swap(it1, it2); //这里不会改变 iVec1 和 iVec2中的元素，只是交换了 it1 和it2的值
	swap(*(it1+1), *(it2+1));     //这里会改变 iVec1 和 iVec2 中的元素值
	iter_swap(it1 + 2, it2 + 2);  //这里会改变 iVec1 和 iVec2 中的元素值
	
	cout << "iVec1:";
	for_each(iVec1.begin(), iVec1.end(), [](int x){cout << x << " "; });
	cout << endl;
	cout << "iVec2:";
	for_each(iVec2.begin(), iVec2.end(), [](int x){cout << x << " "; });
	cout << endl;

	swap_ranges(iVec1.begin(), iVec1.end(), iVec2.begin());

	// transform  把某段区间元素，执行某个操作后，存入另一个容器区间
	sVec.assign({ "A", "ABC", "bc", "eeee" });
	iVec.resize(4);
	//取 sVec 各个元素长度，存入 iVec
	transform(sVec.begin(), sVec.end(), iVec.begin(), 
				[](string s){ return s.length(); });

	//replace:   查找元素并替换(替换所有)
	//replace_if 替换满足某个条件的元素(替换所有)
	//replace_copy     把 replace 的替换结果输出到另一个容器，本容器元素不变
	//replace_copy_if  把 replace_if 的替换结果输出到另一个容器，本容器元素不变
	iVec.assign({ 1, 2, 3, 4, 5, 6, 3 });
	//把 iVec 中的3 替换位 9
	replace(iVec.begin(), iVec.end(), 3, 9);
	//把 iVec中所有奇数替换为 0 
	replace_if(iVec.begin(), iVec.end(), [](int x){return x & 1; }, 0);

	iVec1.resize(iVec.size());
	replace_copy(iVec.begin(), iVec.end(), iVec1.begin(), 3, 9);

	replace_copy_if(iVec.begin(), iVec.end(), iVec1.begin(),
				[](int x){return x & 1; }, 0);

    //fill    填充某个区间内的值
    //fill_n  从某个位置开始，填充 N  个值
    iVec.assign({ 1, 2, 3, 4, 5, 6, 3 });
    fill(iVec.begin(), iVec.begin() + 5, 10);
    cout << "fill iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;
    fill_n(iVec.begin(), 5, 9); //效果同fill(iVec.begin(), iVec.begin() + 5, 9);

    //generate   按照某种规则，设置区间内的元素值
    iVec.resize(5);
    generate(iVec.begin(), iVec.end(), [](){static int x = 1; return x++;});
    cout << "generate iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;
    //填充斐波那契数列： 1 1 2 3 5 8  每个接下来的数，是前面两数的和
    iVec.resize(10);
    {
        generate_n(iVec.begin(), 10, []()  {
            static int i = 0, j = 1, k = 0;
            if (k == 0)
            {
                k = 1; //刚开始只是作为一个标志
                return 1;
            }
            else
            {
                k = i + j;
                i = j;
                j = k;
                return k;
            }
        }
        );
    }
    cout << "generate_n iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    //remove   删除所有等于某个值的元素
    //         删除机制：把待删除元素后面的元素前移，替换这个元素
    //         remove 是外部函数，无法改变原容器的元素个数
    //         遍历到区间末尾后，把所有元素前移后，返回处理好的最后一个元素位置
    //remove_if      按条件删除
    //remove_copy    把remove 的结果 copy到另外一段区间，源区间元素不变
    //remove_copy_if 把remove_if 的结果 copy到另外一段区间，源区间元素不变
    //对于 list 容器，内部实现了 remove 就不要调用这个进行删除元素
    iVec.assign({ 1, 3, 2, 3, 4, 3 });
    it = remove(iVec.begin(), iVec.end(), 3);//删除等于3的元素
            //返回迭代器, 从区间开始到这个迭代器位置，是处理好的结果，这个迭代器之后的继续保持原值
    cout << "remove iVec:";
    for_each(iVec.begin(), it, [](int x){cout << x << " "; }); 
    cout << "Release iVec:";
    for_each(it, iVec.end(), [](int x){cout << x << " "; });//it 开始到 end 是‘废弃’位置
    cout << endl;

    iVec.assign({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    //删除所有奇数
    it = remove_if(iVec.begin(), iVec.end(), [](int x){return x & 1; });
    cout << "remove_if odd iVec:";
    for_each(iVec.begin(), it, [](int x){cout << x << " "; });
    cout << endl;

    //把iVec中 除了 3 之外所有元素 copy 到 iVec1, iVec1中 copy结束位置是 it
    iVec1.resize(10);
    it = remove_copy(iVec.begin(), iVec.end(), iVec1.begin(), 3);

    iVec.assign({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    iVec1.resize(10);
    it = remove_copy_if(iVec.begin(), iVec.end(), iVec1.begin(), [](int x){return x & 1; });
    cout << "remove_copy even->iVec1:";
    for_each(iVec1.begin(), it, [](int x){cout << x << " "; });
    cout << endl;

    //unique 把相邻的相等元素删掉(只保留 1 个)
    //       它的删除机制和 remove 一样，不改变 容器长度，
    //       只是指明 操作完成后 的结束位置
    //       可以增加比较函数，用户定义相等运算符
    //unique_copy 和 remove_copy 一样，操作结果保存到另一个容器，源区间元素不变
    iVec.assign({ 1, 2, 2, 3, 3, 3, 5, 4, 5, 4 });
    it = unique(iVec.begin(), iVec.end());
    cout << "unique->iVec:";
    for_each(iVec.begin(), it, [](int x){cout << x << " "; });
    cout << endl;

    sVec.assign({ "AA", "BB", "CDE", "FFF", "GK" });
    sIt = unique(sVec.begin(), sVec.end(), 
             [](string A, string B){ return A.length() == B.length(); });
    cout << "unique-->sVec:";
    for_each(sVec.begin(), sIt, [](string s){cout << s << " "; });
    cout << endl;

    //reverse       把区间内元素逆序
    //reverse_copy  把逆序结果存入另一个容器，源区间元素不变
    iVec.assign({ 1, 2, 3, 4, 5 });
    iVec1.resize(iVec.size());
    reverse(iVec.begin(), iVec.end()); //区间内元素逆序
    reverse_copy(iVec.begin(), iVec.end(), iVec1.begin());//逆序结果存入 iVec1

    //rotate   旋转容器内的元素， 第二个参数作为新的开头元素
    //         把 第一个参数到第二个参数区间的元素，移动到末尾
    //rotate_copy  和前面一样，旋转结果存入另一个容器
    iVec.assign({ 1, 2, 3, 4, 5, 6, 7 });
    rotate(iVec.begin(), iVec.begin() + 2, iVec.end());
    cout << "rotate->iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    //random_shuffle  把容器内数据随机重排, 第三个可选参数为 随机数种子、
    //shuffle         把容器内数据随机重排
    //list 不能使用这两个函数 (因为入参是随机访问迭代器，函数内部会做迭代器加减运算)
    iVec.assign({ 1, 2, 3, 4, 5, 6, 7 });
    //还可以使用  GetTickCount(); //计算机启动到现在经历的微秒数
    random_shuffle(iVec.begin(), iVec.end(), [](int x){ return time(NULL) % x; });
    cout << "random_shuffle->iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    iVec.assign({ 1, 2, 3, 4, 5, 6, 7 });
    shuffle(iVec.begin(), iVec.end(), default_random_engine());
    cout << "shuffle->iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    //partition 把容器内数据 按照某个分类方法，分成两类，
    //          分别放在容器的前后两个部分，前部分是满足条件的元素
    //                                      后部分是不满足条件的元素
    //                                      返回分界点迭代器(后部分的起始位置)
    //                                      为什么不是返回 前部分的结束位置？-->左闭右开区间
    //          不能保证排序，不稳定的分类方法
    //stable_partition  稳定的分类方法，保证有序性(同一个分类里面，原来在前面的，分类后仍然在前面)
    //                  保证稳定性，必然牺牲效率
    //is_partitioned    判断容器内部是否按照某个规则分类了
    //partition_copy    分类结果保存到另一个容器
    //partition_point   获取分类的分界点
    //                  先 使用 is_partitioned 进行判断后再调用
    //                  (如果对没有分类的区间调用，会出异常)

    iVec.assign({ 1, 2, 3, 4, 5, 6, 7 });
    //按照奇偶分类，奇数放前面
    it = partition(iVec.begin(), iVec.end(), [](int x){ return x & 1; });
    cout << "partition->iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;
    cout << "分界点：" << *it << endl;

    iVec.assign({ 1, 2, 3, 4, 5, 6, 7 });
    //按照奇偶分类，奇数放前面
    it = stable_partition(iVec.begin(), iVec.end(), [](int x){ return x & 1; });
    cout << "stable_partition->iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;
    cout << "分界点：" << *it << endl;

    iVec.assign({ 1, 5, 6, 4, 3, 8, 9, 7 });
    //判断 iVec 是否按照 < 7 分类
    iRet = is_partitioned(iVec.begin(), iVec.end(), [](int x){return x < 7; });
    cout << "按照小于7分类？：" << (iRet ? "YES" : "NO") << endl;

    //sort   对区间内数据排序， 默认升序排列，或者通过拉姆达函数来定义排序规则
    //       快速排序算法，不稳定排序
    //stable_sort  稳定排序， 用法 同 sort
    //partial_sort  部分排序：只找出序列里面前面 N 个元素放到前面，后面的不管是否有序
    //              相当于 sort 只处理了一部分，就退出排序了
    //partial_sort_copy  排序结果到另一个容器
    //is_sorted     判断容器区间内元素是否有序(默认判断升序，降序的话穿函数)
    //is_sorted_until  针对 partial_sort 的有序性判断

    //nth_element      对区间内元素排序， 某一个元素位置找好了则退出排序
    iVec.assign({ 1, 5, 6, 4, 3, 8, 9, 7 });
    sort(iVec.begin(), iVec.end()); //升序排列
    sort(iVec.begin(), iVec.end(), [](int a, int b){return b < a; }); //降序排列

    iVec.assign({ 1, 3, 5, 2, 8, 6, 4 });
    //在 iVec.begin() 到 iVec.end() 区间内，排好前面 3 个元素
    partial_sort(iVec.begin(), iVec.begin()+3,  iVec.end());
    cout << "partial_sort->iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    iVec.assign({ 1, 3, 5, 2, 8, 6, 4 });    
    //对 iVec.begin() 到 iVec.end()区间元素排序 ，第三个元素排好序了就退出排序
    //!!!! 事实上，第二个参数完全不起作用，它的操作结果是整个区间排序
    // 同学们可以回去尝试一下， 第二个参数传入另一个容器的迭代器
    nth_element(iVec.begin(), iVec.begin() + 3, iVec.end());

    //lower_bound   找第一个大于等于某个元素的位置 (排序时插入的下界 --左边开始位置)
    //upper_bound   找第一个大于某个元素的位置 (排序时插入的上界     --右边结束位置)
    //equal_range   返回 pair 两个值分别是 lower_bound 和 upper_bound
    //需要 容器内元素已经排好序了 （默认升序）
    //如果 容器内元素非升序排列，需要使用 拉姆达函数(仿函数，函数指针都行)指定排序规则
    //二分法查找
    iVec.assign({ 1, 3, 5, 6, 6, 6, 7, 8, 8 });
    it = lower_bound(iVec.begin(), iVec.end(), 6);
    cout << "lower_bound:";
    for_each(it, iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    sort(iVec.begin(), iVec.end(), [](int a, int b){return a > b; });
    cout << "iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    it = upper_bound(iVec.begin(), iVec.end(), 6, [](int a, int b){return a > b; });
    cout << "upper_bound:";
    for_each(it, iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    //binary_search  二分法查找元素，找到则返回 true，否则 false， 入参同 上
    //               默认查找升序排列序列，如果非升序排列，需要指定排序规则
    //               对于非排序的容器，查找结果不准确

    //merge 归并两个排好序的区间内元素，到另一个容器中
    iVec1.assign({ 1, 4, 7, 9 });
    iVec2.assign({ 0, 5, 6, 8, 10 });
    iVec.resize(10);
    //把iVec1 和 iVec2 归并排序到 iVec
    //归并前需要保证 iVec1 和 iVec2 都是升序排列
    //返回 归并后 在 iVec 中的结束位置
    //需要保证 iVec 足够长，否则出错
    it = merge(iVec1.begin(), iVec1.end(), iVec2.begin(), iVec2.end(), iVec.begin());
    cout << "merge iVec:";
    for_each(iVec.begin(), it, [](int x){cout << x << " "; });
    cout << endl;
    //如果 iVec1 和 iVec2 都是降序排列？--- 同 upper_bound 一样，增加排序规则

    //inplace_merge  把一个容器中的两部分元素进行归并，
    //                      这两部分元素都需要是有序的，而且排序方式一样
    //               默认是 升序排列
    // 这里举一个降序排列的例子，升序排列的话，不要拉姆达表达式
    iVec.assign({ 9, 6, 5, 10, 8, 3, 1 });
    it = find(iVec.begin(), iVec.end(), 10); //两部分的分界点 (两部分都是降序排列)
    inplace_merge(iVec.begin(), it, iVec.end(), [](int a, int b){return a > b; });
    cout << "inplace_merge iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    //includes  判断一个容器中数据是否包含另一个容器中所有数据
    //          需要容器中数据都有序 （两个容器排序方式一样）
    //          默认升序，如果其他排序，需要使用 拉姆达表达式指明排序规则
    iVec.assign({ 1, 2, 3, 4, 5, 6, 7 });
    iVec1.assign({ 1, 3, 7 });
    iRet = includes(iVec.begin(), iVec.end(), iVec1.begin(), iVec1.end());
    cout << "iVec includes iVec1?:" << (iRet ? "YES" : "NO") << endl;

    //set_union         取两个区间的并集，存入另一个容器
    //set_intersection  取两个区间的交集，存入另一个容器
    //set_difference    取两个区间的差集，存入另一个容器
    //set_symmetric_difference 取两个区间的对称差集，存入另一个容器
    //              返回 存入的结束位置
    iVec1.assign({ 1, 2, 3, 3, 5 });
    iVec2.assign({ 3, 4, 5, 6, 7 });
    iVec.resize(10);
    it = set_union(iVec1.begin(), iVec1.end(), iVec2.begin(), iVec2.end(), iVec.begin());
    cout << "union iVec1&iVec2:";
    for_each(iVec.begin(), it, [](int x){cout << x << " "; });
    cout << endl;

    //make_heap   把容器构造成堆结构 (大堆)
    //            如果要构造小堆，需要添加 拉姆达函数
    //push_heap   往堆中插入数据，保持堆仍然是大堆(小堆)
    //pop_heap    从堆中删除元素，保持堆仍然是大堆(小堆)
    //is_heap       判断是否满足堆结构
    //is_heap_until 判断某个区间前面多少个元素满足堆结构，返回第一个不满足堆结构的位置
    //sort_heap   堆排序--对一个堆结构的数据进行排序(需要先把序列堆化)
    //      其他排序规则，需要对所有函数都加上比较规则
    iVec.assign({ 1, 3, 5, 7, 2, 4, 6, 8 });
    make_heap(iVec.begin(), iVec.end());//构造大堆，构造小堆，则第三个参数增加比较规则
    cout << "make_heap:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    iVec.push_back(10);
    push_heap(iVec.begin(), iVec.end());//作用只是调整最后一个元素，需要手动插入元素到末尾

    pop_heap(iVec.begin(), iVec.end()); //作用只是把堆顶元素交换到末尾，并调整堆
    iVec.pop_back();//手动去除最后元素并删除，删除最大的元素


    sort_heap(iVec.begin(), iVec.end());//排序前提: is_heap(iVec.begin(), iVec.end())
    cout << "sort_heap:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    //min  找最小值
    //max  找最大值
    //minmax 找最小值和最大值， 返回一个  pair 类型变量
    //min_element  最小值位置（迭代器）
    //max_element  最大值位置
    //minmax_element 最小值和最大值位置，  返回一个  pair 类型变量
    //举例略

    //lexicographical_compare   字典比较两个容器内元素大小
    //                          先比较第一个元素，相等则比较下一个，不相等的返回结果
    //                          元素的比较方式 可以 自定义(默认，int 直接比较，字符串，比较 ascII, ....)
    //  返回 > 0,  = 0, <0   分别表示 两个容器  iVec1 > iVec2. iVec1==iVec2, iVec1 < iVec2
    sVec1.assign({ "aaa", "bbb", "ABC", "DDD" });
    sVec2.assign({ "aaa", "bbb", "ABCD", "DDD" });
    lexicographical_compare(sVec1.begin(), sVec1.end(), sVec2.begin(), sVec2.end());

    //next_permutation
    //prev_permutation    
    //把元素来一个全排列， next_permutation 和 prev_permutation 分别返回 下一个/上一个 排列方式
    //全排列：排出一个序列的所有排序方式
    //N 个元素的排序方式，有 N 的阶乘种 (N! = N*(N-1)*(N-2)*...*1)
    iVec.assign({ 1, 2, 3, 4 });
    for (int i = 0; i < 10; i++)
    {
        cout << "第 " << i + 1 << " 种排列:";
        for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
        cout << endl;
        next_permutation(iVec.begin(), iVec.end());
    }


}


int _tmain(int argc, _TCHAR* argv[])
{
    //TestVector();
    //TestAlg1();
	TestAlg2();	

    system("pause");
	return 0;
}

