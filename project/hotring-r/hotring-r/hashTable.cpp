#include "hotring-r.h"

ht::ht(unsigned int sz) :table(0), findcnt(0), minFindcnt(0x7fffffff), maxFindcnt(0)
{
    unsigned int htsz = 1;
    while (htsz < sz) htsz <<= 1;
    this->table.resize(htsz, nullptr);
    size = htsz;
    sizemask = htsz - 1;
}

unsigned int ht::hashFunction(const string & key)
{
    unsigned int hash = 5381;

    for (char c : key)
    {
        hash += (hash << 5) + c;
    }
    //return key[0] << 7;
    return (hash & 0x7FFFFFFF);
}

void ht::setMinMax(const unsigned int onecnt)
{
    this->maxFindcnt = max(this->maxFindcnt, onecnt);
    this->minFindcnt = min(this->minFindcnt, onecnt);
}

bool ht::insert(const string & key, const string & val)
{
    // 去重
    if (search(key) != nullptr) return false;

    unsigned int hashValue = hashFunction(key);
    unsigned int index = hashValue & this->sizemask;
    unsigned int tag = hashValue & (~this->sizemask);
    htEntry *newItem = new htEntry(key, val, nullptr, tag);
    htEntry *pre = nullptr;
    htEntry *nxt = nullptr;

    //头插法插入
    newItem->setNext(table[index]);
    table[index] = newItem;
    
    return true;
}

bool ht::remove(const string & key)
{
    htEntry *p = search(key);
    unsigned int hashValue = hashFunction(key);
    unsigned int index = hashValue & this->sizemask;

    if (p == nullptr) return false;

    if (table[index] == p)
    {
        table[index] = p->getNext();
    }
    else 
    {
        htEntry *pre = table[index];
        while (pre && pre->getNext() != p)
        {
            pre = pre->getNext();
        }
        pre->setNext(p->getNext());
    }
    delete p;
    return true;
}

bool ht::update(const string & key, const string & val)
{
    htEntry *p = search(key);
    if (p == nullptr) return false;
    p->setVal(val);
    return true;
}

htEntry *ht::search(const string & key)
{
    unsigned int hashValue = hashFunction(key);
    unsigned int index = hashValue & this->sizemask;
    htEntry *p = table[index];
    unsigned int precnt = findcnt;
    bool hotspotAware = false;

    ++this->findcnt;
    while (p && p->getKey() != key) {
        ++this->findcnt;
        p = p->getNext();
    }
    setMinMax(this->findcnt - precnt);
    return p;
}

unsigned int ht::getfindcnt()
{
    return this->findcnt;
}

unsigned int ht::getmaxFindcnt()
{
    return this->maxFindcnt;
}

unsigned int ht::getminFindcnt()
{
    return this->minFindcnt;
}

