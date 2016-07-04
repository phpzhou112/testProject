// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
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

    bool operator == (const AAA &A) const  //find û��ǿ��Ҫ��const����������const��дҲ����
    {
        return (x == A.x && y == A.y);
    }
};

class CEven
{
public:
    bool operator ()(int x)
    {        
        return !(x % 2); //ʹ��λ�����ж�����ż���� !(x & 1)
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

    //find --> ����Ԫ�� --> ���ص�����
    it = find(iVec.begin(), iVec.end(), 8);
    cout << "iVec::*it: " << *it << endl;

    //������ʹ�� find������һ�� ָ��ֵ��ָ�� (����൱�ڵ�����������ͨ�� *p ����Ԫ��)
    int arr[] = { 1, 4, 6, 2, 8, 3, 9, 7, 5 };
    int *p = find(arr, arr + sizeof(arr) / sizeof(arr[0]), 9);
    cout << "arr::*p: " << *p << endl;

    //���� ���ڹ�����������Ԫ�أ���Ҫʹ�����find����Ӧ��ʹ�� ���������ĳ�Ա����find
    //��Ϊ ʹ����� find Ч�ʺܵ� O(N); ��Ա������Ч�� O(logN)

    //error C2678 : �����ơ� == �� : û���ҵ����ܡ�AAA�����͵���������������(��û�пɽ��ܵ�ת��)        
    AAA arrA[] = { AAA(1, 1), AAA(1, 2), AAA(3, 2), AAA(5, 7), AAA(1, 6) };
    AAA *pA = find(arrA, arrA + sizeof(arrA) / sizeof(arrA[0]), AAA(5, 7));
    cout << "arrA::*pA: " << *pA << endl;//�Ҳ����򷵻� end(),ֱ����������

    //find_if  �ҵ�һ������������Ԫ�� �ĵ�����λ��
    //�Ѿ�ѧ�����ַ������º��� ��  ����ָ��
    it = find_if(iVec.begin(), iVec.end(), CEven());
    it = find_if(iVec.begin(), iVec.end(), IsEven);
    //�����ַ�������ķ����ʽ-->����һ��������������ʽ��[](�����б�){��������}
    it = find_if(iVec.begin(), iVec.end(), [](int x){return !(x & 1);});
    cout << "iVec �е�һ��ż��:" << *it << endl;

    //��ô�ҳ�iVec������ż����
    cout << "iVec ������ż��: ";
    it = iVec.begin();
    while (1)
    {
        it = find_if(it, iVec.end(), [](int x){ return !(x & 1); });
        if (it == iVec.end())
        {
            break;
        }
        cout << *it << " ";
        it++; //���ҵ���Ԫ�ص���һ��λ�ü���������
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

    //all_of  �ж�ĳ�������Ԫ���Ƿ�����Ԫ������ĳ������
    //any_of  �ж�..............�Ƿ����Ԫ��............
    //none_of �ж�..............����Ԫ�ض�������ĳ������
    iRet = all_of(iVec.begin(), iVec.end(), [](int x){return x & 1; });
    cout << "����Ԫ�ض�������?:" << (iRet?"Yes":"No") << endl;
    iRet = any_of(iVec.begin(), iVec.end(), [](int x){return x > 5; });
    cout << "���ڴ���5��Ԫ�� ?:" << (iRet ? "Yes" : "No") << endl;
    iRet = none_of(iVec.begin(), iVec.end(), [](int x){return x > 10; });
    cout << "û�д���10��Ԫ�� ?:" << (iRet ? "Yes" : "No") << endl;

    //for_each ������������Ԫ��ִ��ĳ������
    cout << "iVec������Ԫ��:";
    for_each(iVec.begin(), iVec.end(), [](int x){ cout << x << " "; });
    cout << endl;
    //-->for_each ������������������ζ���ķ����ʽ���� *it
    //������� iVec������Ԫ�� ���� 1 ? ע�⣺ʹ�����ô������ (��������ʱ���� *it ������)
    for_each(iVec.begin(), iVec.end(), [](int &x){ ++x; });
    cout << "iVec������Ԫ��:";
    for_each(iVec.begin(), iVec.end(), [](int x){ cout << x << " "; });
    cout << endl;

    //find, find_if ���ҵ�һ��Ԫ�أ���һ������������Ԫ��(������ TestVector())
    //find_if_not   ���ҵ�һ��������������Ԫ�أ���ʵ�ϣ�ʹ�� find_if �Ϳ��Դﵽ���������Ŀ��
    //find_end      �������һ�������е�λ��, ���ص�������ָ�������еĿ�ʼλ��
    //find_first_of �����������ҵ�һ�������У������� ��һ���������������е�Ԫ��λ��
    //adjacent_find  ����������Ԫ����ȵ�Ԫ��λ�� (��һ�������������)
    iVec.assign({ 1, 2, 3, 7, 8, 9, 1, 2, 3, 7, 5, 3, 1, 2, 3, 4 });
    iVec1.assign({ 1, 2, 3, /*7*/});
    it = find_end(iVec.begin(), iVec.end(), iVec1.begin(), iVec1.end());
    cout << "���һ�������е�λ��: ";
    for_each(it, iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    iVec1.assign({ 7, 5, 3, 99});
    //�� iVec.begin() ��ʼ���� end(), ��� Ԫ�ش����� iVec1 �У��򷵻����������
    //�����ҵ����ǵ�һ�� 3 
    //�� find ���ƣ�ֻ��˵ find ֻ�ܲ�ĳ��Ԫ�أ�����ܲ� ���Ԫ��
    it = find_first_of(iVec.begin(), iVec.end(), iVec1.begin(), iVec1.end());
    cout << "��һ�������������е�Ԫ��λ��: ";
    for_each(it, iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    iVec.assign({1,2,3,3,4,5,5,6,7,7,9});
    it = adjacent_find(iVec.begin(), iVec.end());
    cout << "��һ��������ȵ�Ԫ��:" << *it << ", " << *(it+1) << endl;

    vector<string> sVec{ "aaa", "BB", "cccc", "DDDD", "ee", "ff" };
    vector<string>::iterator sIt;
    //�ҵ�һ�Գ�����ȵ��ַ���λ��
    sIt = adjacent_find(sVec.begin(), sVec.end(),
        [](string s1, string s2){ return s1.length() == s2.length(); });
    cout << "��һ�Գ�����ȵ��ַ���:" << *sIt << ", " << *(sIt+1) << endl;

    //count, count_if ͳ��Ԫ�ظ�����ͳ������������Ԫ�ظ��� (�ѽ�)
    //mismatch �����������У���һ�Բ���ȵ�Ԫ��λ��, ����һ��pair<it,it> �ֱ�ָ�����������Ĳ���Ԫ��λ��
    //1���ڶ������䣬ֻ��Ҫ�ṩ ��ʼλ�ã�mismatch �����ڲ�������λ�ò�ͣ������
    //            �� ��һ��������Ԫ�رȽϣ�����ڶ�������Ƚ϶̣����ܳ��� �ڶ�������Խ�����(ȡ*end()��ֵ)
    //            ���ԣ��ڶ������䣬����һ����д ���ȱȽϳ��� �Ǹ�����
    //2�������ڱȽ�������ͬ��������
    //3���������ӱȽϺ���
    iVec1.assign({ 1, 3, 5, 7, 8, 4, 6, });
    iVec2.assign({ 1, 3, 5, 7, 9, 2, 4, 6 });
    typedef vector<int>::iterator  VITER;
    pair<VITER, VITER> pairVec = 
        mismatch(iVec1.begin(), iVec1.end(), iVec2.begin());
    cout << "��һ�Բ����Ԫ��:" << *(pairVec.first) << ", " 
        << *(pairVec.second) << endl;

    iVec1.assign({ 1, 3, 5, 7, 9 });
    iVec2.assign({ 1, 3, 5, 7 });
    //mismatch(iVec1.begin(), iVec1.end(), iVec2.begin()); �����ᵼ�±���

    //��������ͬ����
    int iArr[] = { 1, 3, 5, 7, 8, 10 };
    mismatch(iVec1.begin(), iVec1.end(), iArr);

    vector<string>  sVec1{ "aa", "bb", "ccc", "dddd" };
    vector<string>  sVec2{ "ab", "cd", "efg", "hij" };
    //�ҵ�һ�Գ�����ȵ��ַ���λ��
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

	//equal �ж�������������ĳ���������Ƿ����
	//���ڵ�����������û����������ޣ����ԣ���mismatchһ����������Ȳ���������쳣
	//���԰ѳ������䷽����
	iVec1.assign({ 1, 5, 7, 4, 8 });
	iVec2.assign({ 0, 5, 7, 4, 9, 1 });
	iRet = equal(iVec1.begin() + 1, iVec1.end() - 1, iVec2.begin() + 1);
	cout << "iVec1 equal iVec2? : " << (iRet ? "YES" : "NO") << endl;
	//vs2015 ֧�� ���ĸ�����ָ������߽�
	//iRet = equal(iVec1.begin() + 1, iVec1.end() - 1, 
	//						iVec2.begin() + 1, iVec2.begin()+2);
	//��mismatchһ���� equal ��֧�ֱȽϺ�����Ϊ���ĸ�����(��������)

	//is_permutation �ж�����������Ԫ���ǲ���һ����(˳����Բ�һ��)
	//�ڶ������䣬ֻ��Ҫ������ʼλ�ã�������Ȳ�����Ҳ�������
	//ͬ���ģ�Ҳ֧�ִ���ȽϺ�����Ϊ ���ĸ�����(��������)
	iVec1.assign({ 1, 5, 7, 4, 8 });
	iVec2.assign({ 4, 8, 1, 7, 5, 1 });
	iRet = is_permutation(iVec1.begin(), iVec1.end(), iVec2.begin());
	cout << "permutation? : " << (iRet ? "YES" : "NO") << endl;

	vector<string>  sVec1{ "aa", "bb", "ccc", "dddd" };
	vector<string>  sVec2{ "abbc", "cd", "ab", "hij" };
	//�ж��ַ����Ƿ�һ��
	iRet = is_permutation(sVec1.begin(), sVec1.end(), sVec2.begin());
	cout << "[1]string permutation?: " << (iRet ? "YES" : "NO") << endl;
	//ʹ���Զ���ȽϷ�ʽ(�ж�����)
	iRet = is_permutation(sVec1.begin(), sVec1.end(), sVec2.begin(),
		[](string s1, string s2){ return s1.length() == s2.length(); });
	cout << "[2]string permutation?: " << (iRet ? "YES" : "NO") << endl;

	//search ���ҵ�һ�������� ���� find_end ���Ӧ��
	//���� ǰ���Ǹ������ ������
	//����������ȵ��ж���������Ϊ�� 5 ��������ʹ�÷��� ͬ mismatch
	iVec1.assign({ 1, 3, 4, 5, 7, 4, 5, 8, 7, 4, 5 });
	deque<int> iDeq1{ 4, 5 };
	it = search(iVec1.begin(), iVec1.end(), iDeq1.begin(), iDeq1.end());
	cout << "��һ�������п�ʼλ��: ";
	for_each(it, iVec1.end(), [](int x){cout << x << " "; });
	cout << endl;

	//search_n �������� N �� ���� M ��Ԫ�ص�λ��
	iVec.assign({ 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 4, 4, 7, 8 });
	it = search_n(iVec.begin(), iVec.end(), 2, 4); //����������������4��Ԫ��λ��
	cout << "����2������ 4 ��λ��:";
	for_each(it, iVec.end(), [](int x){cout << x << " "; });
	cout << endl;

	//search_n ������������
	//1: ���������ж���ȵ�����
	//2: �������������ж�����	
	sVec.assign({ "abbc", "cd", "ab", "hiaj", "Bbac", "AAAA", "D" });
	//�������� 3 ������Ϊ 4 ���ַ���λ��
	//���� ��ķ����ʽ �е� b ���������� 4 (search_n �ĵ�4������)
	sIt = search_n(sVec.begin(), sVec.end(), 3, 4,
		[](string a, int b){ return a.length() == b; });
	cout << "���� 3������Ϊ 4 ���ַ���λ��:";
	for_each(sIt, sVec.end(), [](string s){cout << s << " "; });
	cout << endl;
	//�������� 3 �� С���� "Z" ���ַ���λ�� �������С�ڣ�����Ĭ�ϱȽ�ASCII��
	//��ķ����ʽ��һ����α����� ������Ԫ�ص�����
	//��ķ����ʽ�ڶ�����α����� search_n �� 4 ������������
	sIt = search_n(sVec.begin(), sVec.end(), 3, "Z",
		[](string s1, string s2){ return s1 < s2; });
	cout << "���� 3 ��С�� \"Z\" ���ַ���λ��:";
	for_each(sIt, sVec.end(), [](string s){cout << s << " "; });
	cout << endl;

	//copy    ��һ�������Ԫ��ֵ����ֵ����һ������ 
	//				(�ڶ������䳤�ȱ����㹻������Խ���쳣)
	//copy_n  ���� n �����ȵ����ݣ������ֻ��Ҫָ������ �������ʼλ�ã��Ϳ�������
	//copy_if ������������ĳ�������ĺ���ִ�п�������
	//copy_backward  �ڶ�������ָ������λ�ã���������ӽ���λ�ÿ�ʼ��ǰ����
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
	//�������������� iVec2
	copy_if(iVec1.begin(), iVec1.end(), iVec2.begin(), [](int x){return x & 1; });
	cout << "��������������iVec2:";
	for_each(iVec2.begin(), iVec2.end(), [](int x){cout << x << " "; });
	cout << endl;

	iVec1.assign({ 1, 2, 3, 4, 5 });
	iVec2.clear();
	iVec2.resize(10);
	copy_backward(iVec1.begin(), iVec1.end(), iVec2.end());
	cout << "����Ԫ�ص�iVec2ĩβ��";
	for_each(iVec2.begin(), iVec2.end(), [](int x){cout << x << " "; });
	cout << endl;

	//move  move_backward ���� �� copy, copy_backward һ�� ����������
	//����:  ������ memmove���鿽���� ��memcpy��˳�򿽱��� ������
	//	ʵ�⣺���� memmove �� memcpy ������һ����

	//swap       ����������������ֵ(����������)
	//iter_swap  ����������ָ���ֵ��(ֵ����)
	//swap_ranges  ����������һ�������ֵ ���൱�������������ε��� iter_swap��
	iVec1.assign({ 1, 2, 3, 4 });
	iVec2.assign({ 5, 6, 7, 8 });
	it1 = iVec1.begin();
	it2 = iVec2.begin();
	swap(it1, it2); //���ﲻ��ı� iVec1 �� iVec2�е�Ԫ�أ�ֻ�ǽ����� it1 ��it2��ֵ
	swap(*(it1+1), *(it2+1));     //�����ı� iVec1 �� iVec2 �е�Ԫ��ֵ
	iter_swap(it1 + 2, it2 + 2);  //�����ı� iVec1 �� iVec2 �е�Ԫ��ֵ
	
	cout << "iVec1:";
	for_each(iVec1.begin(), iVec1.end(), [](int x){cout << x << " "; });
	cout << endl;
	cout << "iVec2:";
	for_each(iVec2.begin(), iVec2.end(), [](int x){cout << x << " "; });
	cout << endl;

	swap_ranges(iVec1.begin(), iVec1.end(), iVec2.begin());

	// transform  ��ĳ������Ԫ�أ�ִ��ĳ�������󣬴�����һ����������
	sVec.assign({ "A", "ABC", "bc", "eeee" });
	iVec.resize(4);
	//ȡ sVec ����Ԫ�س��ȣ����� iVec
	transform(sVec.begin(), sVec.end(), iVec.begin(), 
				[](string s){ return s.length(); });

	//replace:   ����Ԫ�ز��滻(�滻����)
	//replace_if �滻����ĳ��������Ԫ��(�滻����)
	//replace_copy     �� replace ���滻����������һ��������������Ԫ�ز���
	//replace_copy_if  �� replace_if ���滻����������һ��������������Ԫ�ز���
	iVec.assign({ 1, 2, 3, 4, 5, 6, 3 });
	//�� iVec �е�3 �滻λ 9
	replace(iVec.begin(), iVec.end(), 3, 9);
	//�� iVec�����������滻Ϊ 0 
	replace_if(iVec.begin(), iVec.end(), [](int x){return x & 1; }, 0);

	iVec1.resize(iVec.size());
	replace_copy(iVec.begin(), iVec.end(), iVec1.begin(), 3, 9);

	replace_copy_if(iVec.begin(), iVec.end(), iVec1.begin(),
				[](int x){return x & 1; }, 0);

    //fill    ���ĳ�������ڵ�ֵ
    //fill_n  ��ĳ��λ�ÿ�ʼ����� N  ��ֵ
    iVec.assign({ 1, 2, 3, 4, 5, 6, 3 });
    fill(iVec.begin(), iVec.begin() + 5, 10);
    cout << "fill iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;
    fill_n(iVec.begin(), 5, 9); //Ч��ͬfill(iVec.begin(), iVec.begin() + 5, 9);

    //generate   ����ĳ�ֹ������������ڵ�Ԫ��ֵ
    iVec.resize(5);
    generate(iVec.begin(), iVec.end(), [](){static int x = 1; return x++;});
    cout << "generate iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;
    //���쳲��������У� 1 1 2 3 5 8  ÿ����������������ǰ�������ĺ�
    iVec.resize(10);
    {
        generate_n(iVec.begin(), 10, []()  {
            static int i = 0, j = 1, k = 0;
            if (k == 0)
            {
                k = 1; //�տ�ʼֻ����Ϊһ����־
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

    //remove   ɾ�����е���ĳ��ֵ��Ԫ��
    //         ɾ�����ƣ��Ѵ�ɾ��Ԫ�غ����Ԫ��ǰ�ƣ��滻���Ԫ��
    //         remove ���ⲿ�������޷��ı�ԭ������Ԫ�ظ���
    //         ����������ĩβ�󣬰�����Ԫ��ǰ�ƺ󣬷��ش���õ����һ��Ԫ��λ��
    //remove_if      ������ɾ��
    //remove_copy    ��remove �Ľ�� copy������һ�����䣬Դ����Ԫ�ز���
    //remove_copy_if ��remove_if �Ľ�� copy������һ�����䣬Դ����Ԫ�ز���
    //���� list �������ڲ�ʵ���� remove �Ͳ�Ҫ�����������ɾ��Ԫ��
    iVec.assign({ 1, 3, 2, 3, 4, 3 });
    it = remove(iVec.begin(), iVec.end(), 3);//ɾ������3��Ԫ��
            //���ص�����, �����俪ʼ�����������λ�ã��Ǵ���õĽ�������������֮��ļ�������ԭֵ
    cout << "remove iVec:";
    for_each(iVec.begin(), it, [](int x){cout << x << " "; }); 
    cout << "Release iVec:";
    for_each(it, iVec.end(), [](int x){cout << x << " "; });//it ��ʼ�� end �ǡ�������λ��
    cout << endl;

    iVec.assign({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    //ɾ����������
    it = remove_if(iVec.begin(), iVec.end(), [](int x){return x & 1; });
    cout << "remove_if odd iVec:";
    for_each(iVec.begin(), it, [](int x){cout << x << " "; });
    cout << endl;

    //��iVec�� ���� 3 ֮������Ԫ�� copy �� iVec1, iVec1�� copy����λ���� it
    iVec1.resize(10);
    it = remove_copy(iVec.begin(), iVec.end(), iVec1.begin(), 3);

    iVec.assign({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    iVec1.resize(10);
    it = remove_copy_if(iVec.begin(), iVec.end(), iVec1.begin(), [](int x){return x & 1; });
    cout << "remove_copy even->iVec1:";
    for_each(iVec1.begin(), it, [](int x){cout << x << " "; });
    cout << endl;

    //unique �����ڵ����Ԫ��ɾ��(ֻ���� 1 ��)
    //       ����ɾ�����ƺ� remove һ�������ı� �������ȣ�
    //       ֻ��ָ�� ������ɺ� �Ľ���λ��
    //       �������ӱȽϺ������û�������������
    //unique_copy �� remove_copy һ��������������浽��һ��������Դ����Ԫ�ز���
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

    //reverse       ��������Ԫ������
    //reverse_copy  ��������������һ��������Դ����Ԫ�ز���
    iVec.assign({ 1, 2, 3, 4, 5 });
    iVec1.resize(iVec.size());
    reverse(iVec.begin(), iVec.end()); //������Ԫ������
    reverse_copy(iVec.begin(), iVec.end(), iVec1.begin());//���������� iVec1

    //rotate   ��ת�����ڵ�Ԫ�أ� �ڶ���������Ϊ�µĿ�ͷԪ��
    //         �� ��һ���������ڶ������������Ԫ�أ��ƶ���ĩβ
    //rotate_copy  ��ǰ��һ������ת���������һ������
    iVec.assign({ 1, 2, 3, 4, 5, 6, 7 });
    rotate(iVec.begin(), iVec.begin() + 2, iVec.end());
    cout << "rotate->iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    //random_shuffle  �������������������, ��������ѡ����Ϊ ��������ӡ�
    //shuffle         �������������������
    //list ����ʹ������������ (��Ϊ�����������ʵ������������ڲ������������Ӽ�����)
    iVec.assign({ 1, 2, 3, 4, 5, 6, 7 });
    //������ʹ��  GetTickCount(); //��������������ھ�����΢����
    random_shuffle(iVec.begin(), iVec.end(), [](int x){ return time(NULL) % x; });
    cout << "random_shuffle->iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    iVec.assign({ 1, 2, 3, 4, 5, 6, 7 });
    shuffle(iVec.begin(), iVec.end(), default_random_engine());
    cout << "shuffle->iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    //partition ������������ ����ĳ�����෽�����ֳ����࣬
    //          �ֱ����������ǰ���������֣�ǰ����������������Ԫ��
    //                                      �󲿷��ǲ�����������Ԫ��
    //                                      ���طֽ�������(�󲿷ֵ���ʼλ��)
    //                                      Ϊʲô���Ƿ��� ǰ���ֵĽ���λ�ã�-->����ҿ�����
    //          ���ܱ�֤���򣬲��ȶ��ķ��෽��
    //stable_partition  �ȶ��ķ��෽������֤������(ͬһ���������棬ԭ����ǰ��ģ��������Ȼ��ǰ��)
    //                  ��֤�ȶ��ԣ���Ȼ����Ч��
    //is_partitioned    �ж������ڲ��Ƿ���ĳ�����������
    //partition_copy    ���������浽��һ������
    //partition_point   ��ȡ����ķֽ��
    //                  �� ʹ�� is_partitioned �����жϺ��ٵ���
    //                  (�����û�з����������ã�����쳣)

    iVec.assign({ 1, 2, 3, 4, 5, 6, 7 });
    //������ż���࣬������ǰ��
    it = partition(iVec.begin(), iVec.end(), [](int x){ return x & 1; });
    cout << "partition->iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;
    cout << "�ֽ�㣺" << *it << endl;

    iVec.assign({ 1, 2, 3, 4, 5, 6, 7 });
    //������ż���࣬������ǰ��
    it = stable_partition(iVec.begin(), iVec.end(), [](int x){ return x & 1; });
    cout << "stable_partition->iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;
    cout << "�ֽ�㣺" << *it << endl;

    iVec.assign({ 1, 5, 6, 4, 3, 8, 9, 7 });
    //�ж� iVec �Ƿ��� < 7 ����
    iRet = is_partitioned(iVec.begin(), iVec.end(), [](int x){return x < 7; });
    cout << "����С��7���ࣿ��" << (iRet ? "YES" : "NO") << endl;

    //sort   ���������������� Ĭ���������У�����ͨ����ķ�ﺯ���������������
    //       ���������㷨�����ȶ�����
    //stable_sort  �ȶ����� �÷� ͬ sort
    //partial_sort  ��������ֻ�ҳ���������ǰ�� N ��Ԫ�طŵ�ǰ�棬����Ĳ����Ƿ�����
    //              �൱�� sort ֻ������һ���֣����˳�������
    //partial_sort_copy  ����������һ������
    //is_sorted     �ж�����������Ԫ���Ƿ�����(Ĭ���ж����򣬽���Ļ�������)
    //is_sorted_until  ��� partial_sort ���������ж�

    //nth_element      ��������Ԫ������ ĳһ��Ԫ��λ���Һ������˳�����
    iVec.assign({ 1, 5, 6, 4, 3, 8, 9, 7 });
    sort(iVec.begin(), iVec.end()); //��������
    sort(iVec.begin(), iVec.end(), [](int a, int b){return b < a; }); //��������

    iVec.assign({ 1, 3, 5, 2, 8, 6, 4 });
    //�� iVec.begin() �� iVec.end() �����ڣ��ź�ǰ�� 3 ��Ԫ��
    partial_sort(iVec.begin(), iVec.begin()+3,  iVec.end());
    cout << "partial_sort->iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    iVec.assign({ 1, 3, 5, 2, 8, 6, 4 });    
    //�� iVec.begin() �� iVec.end()����Ԫ������ ��������Ԫ���ź����˾��˳�����
    //!!!! ��ʵ�ϣ��ڶ���������ȫ�������ã����Ĳ��������������������
    // ͬѧ�ǿ��Ի�ȥ����һ�£� �ڶ�������������һ�������ĵ�����
    nth_element(iVec.begin(), iVec.begin() + 3, iVec.end());

    //lower_bound   �ҵ�һ�����ڵ���ĳ��Ԫ�ص�λ�� (����ʱ������½� --��߿�ʼλ��)
    //upper_bound   �ҵ�һ������ĳ��Ԫ�ص�λ�� (����ʱ������Ͻ�     --�ұ߽���λ��)
    //equal_range   ���� pair ����ֵ�ֱ��� lower_bound �� upper_bound
    //��Ҫ ������Ԫ���Ѿ��ź����� ��Ĭ������
    //��� ������Ԫ�ط��������У���Ҫʹ�� ��ķ�ﺯ��(�º���������ָ�붼��)ָ���������
    //���ַ�����
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

    //binary_search  ���ַ�����Ԫ�أ��ҵ��򷵻� true������ false�� ���ͬ ��
    //               Ĭ�ϲ��������������У�������������У���Ҫָ���������
    //               ���ڷ���������������ҽ����׼ȷ

    //merge �鲢�����ź����������Ԫ�أ�����һ��������
    iVec1.assign({ 1, 4, 7, 9 });
    iVec2.assign({ 0, 5, 6, 8, 10 });
    iVec.resize(10);
    //��iVec1 �� iVec2 �鲢���� iVec
    //�鲢ǰ��Ҫ��֤ iVec1 �� iVec2 ������������
    //���� �鲢�� �� iVec �еĽ���λ��
    //��Ҫ��֤ iVec �㹻�����������
    it = merge(iVec1.begin(), iVec1.end(), iVec2.begin(), iVec2.end(), iVec.begin());
    cout << "merge iVec:";
    for_each(iVec.begin(), it, [](int x){cout << x << " "; });
    cout << endl;
    //��� iVec1 �� iVec2 ���ǽ������У�--- ͬ upper_bound һ���������������

    //inplace_merge  ��һ�������е�������Ԫ�ؽ��й鲢��
    //                      ��������Ԫ�ض���Ҫ������ģ���������ʽһ��
    //               Ĭ���� ��������
    // �����һ���������е����ӣ��������еĻ�����Ҫ��ķ����ʽ
    iVec.assign({ 9, 6, 5, 10, 8, 3, 1 });
    it = find(iVec.begin(), iVec.end(), 10); //�����ֵķֽ�� (�����ֶ��ǽ�������)
    inplace_merge(iVec.begin(), it, iVec.end(), [](int a, int b){return a > b; });
    cout << "inplace_merge iVec:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    //includes  �ж�һ�������������Ƿ������һ����������������
    //          ��Ҫ���������ݶ����� ��������������ʽһ����
    //          Ĭ�������������������Ҫʹ�� ��ķ����ʽָ���������
    iVec.assign({ 1, 2, 3, 4, 5, 6, 7 });
    iVec1.assign({ 1, 3, 7 });
    iRet = includes(iVec.begin(), iVec.end(), iVec1.begin(), iVec1.end());
    cout << "iVec includes iVec1?:" << (iRet ? "YES" : "NO") << endl;

    //set_union         ȡ��������Ĳ�����������һ������
    //set_intersection  ȡ��������Ľ�����������һ������
    //set_difference    ȡ��������Ĳ��������һ������
    //set_symmetric_difference ȡ��������ĶԳƲ��������һ������
    //              ���� ����Ľ���λ��
    iVec1.assign({ 1, 2, 3, 3, 5 });
    iVec2.assign({ 3, 4, 5, 6, 7 });
    iVec.resize(10);
    it = set_union(iVec1.begin(), iVec1.end(), iVec2.begin(), iVec2.end(), iVec.begin());
    cout << "union iVec1&iVec2:";
    for_each(iVec.begin(), it, [](int x){cout << x << " "; });
    cout << endl;

    //make_heap   ����������ɶѽṹ (���)
    //            ���Ҫ����С�ѣ���Ҫ��� ��ķ�ﺯ��
    //push_heap   �����в������ݣ����ֶ���Ȼ�Ǵ��(С��)
    //pop_heap    �Ӷ���ɾ��Ԫ�أ����ֶ���Ȼ�Ǵ��(С��)
    //is_heap       �ж��Ƿ�����ѽṹ
    //is_heap_until �ж�ĳ������ǰ����ٸ�Ԫ������ѽṹ�����ص�һ��������ѽṹ��λ��
    //sort_heap   ������--��һ���ѽṹ�����ݽ�������(��Ҫ�Ȱ����жѻ�)
    //      �������������Ҫ�����к��������ϱȽϹ���
    iVec.assign({ 1, 3, 5, 7, 2, 4, 6, 8 });
    make_heap(iVec.begin(), iVec.end());//�����ѣ�����С�ѣ���������������ӱȽϹ���
    cout << "make_heap:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    iVec.push_back(10);
    push_heap(iVec.begin(), iVec.end());//����ֻ�ǵ������һ��Ԫ�أ���Ҫ�ֶ�����Ԫ�ص�ĩβ

    pop_heap(iVec.begin(), iVec.end()); //����ֻ�ǰѶѶ�Ԫ�ؽ�����ĩβ����������
    iVec.pop_back();//�ֶ�ȥ�����Ԫ�ز�ɾ����ɾ������Ԫ��


    sort_heap(iVec.begin(), iVec.end());//����ǰ��: is_heap(iVec.begin(), iVec.end())
    cout << "sort_heap:";
    for_each(iVec.begin(), iVec.end(), [](int x){cout << x << " "; });
    cout << endl;

    //min  ����Сֵ
    //max  �����ֵ
    //minmax ����Сֵ�����ֵ�� ����һ��  pair ���ͱ���
    //min_element  ��Сֵλ�ã���������
    //max_element  ���ֵλ��
    //minmax_element ��Сֵ�����ֵλ�ã�  ����һ��  pair ���ͱ���
    //������

    //lexicographical_compare   �ֵ�Ƚ�����������Ԫ�ش�С
    //                          �ȱȽϵ�һ��Ԫ�أ������Ƚ���һ��������ȵķ��ؽ��
    //                          Ԫ�صıȽϷ�ʽ ���� �Զ���(Ĭ�ϣ�int ֱ�ӱȽϣ��ַ������Ƚ� ascII, ....)
    //  ���� > 0,  = 0, <0   �ֱ��ʾ ��������  iVec1 > iVec2. iVec1==iVec2, iVec1 < iVec2
    sVec1.assign({ "aaa", "bbb", "ABC", "DDD" });
    sVec2.assign({ "aaa", "bbb", "ABCD", "DDD" });
    lexicographical_compare(sVec1.begin(), sVec1.end(), sVec2.begin(), sVec2.end());

    //next_permutation
    //prev_permutation    
    //��Ԫ����һ��ȫ���У� next_permutation �� prev_permutation �ֱ𷵻� ��һ��/��һ�� ���з�ʽ
    //ȫ���У��ų�һ�����е���������ʽ
    //N ��Ԫ�ص�����ʽ���� N �Ľ׳��� (N! = N*(N-1)*(N-2)*...*1)
    iVec.assign({ 1, 2, 3, 4 });
    for (int i = 0; i < 10; i++)
    {
        cout << "�� " << i + 1 << " ������:";
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

