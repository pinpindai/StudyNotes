# TopK问题

[toc]

## 问题描述

从arr[1:n]中，找出最大的K个数

## 解决方法

### 排序--全排序

算法思路：使用快排，从大到小进行排序，然后取最大的K个数

时间复杂度：O(nlogn)

空间复杂度：O(logn)



### 排序--部分排序

算法思路：使用冒泡排序或者选择排序，只排前K大的数

时间复杂度：O(kn)

空间复杂度：O(1)



### 堆

算法思路：维护一个包含K个元素的小顶堆，保存前K大的元素

```C++
class myCompare{
    public:
    bool operator()(const pair<int, int>& lh, const pair<int, int>& rh) {
        return lh.second > rh.second;
    }
};

vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> record;
    for(int num: nums) {
        record[num]++;
    }
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, myCompare> pri_que;
    
    for(auto iter = record.begin(); iter != record.end(); ++iter) {
        pri_que.push(*iter);
        if(pri_que.size() > k) {
            pri_que.pop();
        }
    }
    
    vector<int> res(k);
    for(int i = k-1; i >= 0; --i) {
        res[i] = pri_que.top().first;
        pri_que.pop();
    }
    
    return res;
}
```

时间复杂度：O(n)

空间复杂度：O(k)



### 随机选择法--partition

算法思想：借助快排中的partition，利用减治法，找到第K大元素，然后执行一次partition

时间复杂度：O(n)

空间复杂度：O(1)