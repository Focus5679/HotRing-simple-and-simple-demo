
#pragma once
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class htEntry {
public:
	htEntry(const string &k, const string &v, htEntry *n, unsigned int t, unsigned char o, unsigned char r):
		key(k), val(v), next(n), tag(t), occupied(o), rehash(r) {}

	htEntry() : htEntry("", "", nullptr, 0, 0, 0) {}
	htEntry(const string &k, const string &v, htEntry *n, unsigned int t) : htEntry(k, v, n, t, 0, 0) {}
    htEntry(const string &k, unsigned t) : htEntry(k, "", nullptr, t, 0, 0){}

    string getKey()const;
    void setKey(const string &s);

    string getVal()const;
    void setVal(const string &s);

    htEntry *getNext()const;
    void setNext(htEntry *n);
    
    unsigned int getTag()const;
    void setTag(const unsigned int t);
    
    unsigned char getOccupied()const;
    void setOccupied(const unsigned char o);

    unsigned char getRehash()const;
    void setRehash(const unsigned char r);

    bool operator < (const htEntry &other);
	

private:
	
	string key;                 // 键
	string val;                 // 值

    unsigned int tag;           // tag值
    unsigned char occupied;     // 占用标识，多线程实现时启用
    unsigned char rehash;       // rehash标识

    htEntry *next;            // 指向下个哈希表节点，形成链表
};

class hotring {
public:
    //构造函数
    hotring(unsigned int sz);
    ~hotring();

    //插入
    bool insert(const string &key, const string &val);
    //删除
    bool remove(const string &key);
    //更新
    bool update(const string &key, const string &val);
    //查找
    htEntry *search(const string &key);

    unsigned int getfindcnt();
    unsigned int getmaxFindcnt();
    unsigned int getminFindcnt();
private:
    // 计算哈希值的函数
    unsigned int hashFunction(const string &key);

    // 测试所用函数
    void setMinMax(const unsigned int onecnt);

private:
	vector<htEntry*> table;     // 哈希表数组
	unsigned int size;          // 哈希表大小
	unsigned int sizemask;      // 哈希表大小掩码，用于计算索引值 总是等于size-1
    unsigned int r;             // 记录访问次数当r==R时,开始热点转移
    htEntry *compareItem;       // 用于查询时比较

    // 测试所用变量
    const unsigned int R = 5;   // 控制多少次访问后进行热点转移
	unsigned int findcnt;       // 统计总的查找次数
    unsigned int maxFindcnt;    // 统计最大查找次数,一定程度上反应尾延迟
    unsigned int minFindcnt;    // 统计最小查找次数
};


class ht {
public:
    //构造函数
    ht(unsigned int sz);


    //插入
    bool insert(const string &key, const string &val);
    //删除
    bool remove(const string &key);
    //更新
    bool update(const string &key, const string &val);
    //查找
    htEntry *search(const string &key);

    unsigned int getfindcnt();
    unsigned int getmaxFindcnt();
    unsigned int getminFindcnt();
private:
    // 计算哈希值的函数
    unsigned int hashFunction(const string &key);

    // 测试所用函数
    void setMinMax(const unsigned int onecnt);

private:
    vector<htEntry*> table;   // 哈希表数组
    unsigned int size;          // 哈希表大小
    unsigned int sizemask;      // 哈希表大小掩码，用于计算索引值 总是等于size-1
    unsigned int r;             // 记录访问次数当r==R时,开始热点转移

    // 测试所用变量
    const unsigned int R = 5;   // 控制多少次访问后进行热点转移
    unsigned int findcnt;       // 统计总的查找次数
    unsigned int maxFindcnt;    // 统计最大查找次数,一定程度上反应尾延迟
    unsigned int minFindcnt;    // 统计最小查找次数
};