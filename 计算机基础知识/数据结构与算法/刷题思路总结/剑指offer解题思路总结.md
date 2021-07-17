# 剑指offer解题思路总结

[toc]

***********************************

## 3、数组中重复数字

*   使用set

>   时间复杂度O(n)  空间复杂度O(n)

*   sort排序

>   时间复杂度O(nlogn)  空间复杂度O(1)

*   原地置换

>   时间复杂度O(n)  空间复杂度O(1)

```c++
int findRepeatNumber(vector<int>& nums) {
    for(int i = 0; i < nums.size(); ++i){
        while(nums[i] != i){
            if(nums[i] == nums[nums[i]])
                return nums[i];
            swap(nums[i], nums[nums[i]]);
        }
    }
    return -1;
}
```



## 4、二维数组中的查找

*   暴力遍历

>   时间复杂度O(MN)

*   标志位法

>   时间复杂度O(M+N)

``` C++
bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
    if(matrix.size() == 0 || matrix[0].size() == 0)
        return false;
    int row = matrix.size();
    int col = matrix[0].size();

    int i = 0, j = col-1;
    while(i < row && j >= 0){
        int n = matrix[i][j];
        if(n == target)
            return true;
        else if(n > target){
            --j;
        } else {
            ++i;
        }
    }

    return false;
}
```



## 5、替换空格

*   双指针

>   时间复杂度O(n)  空间复杂度O(1)

```c++
string replaceSpace(string s) {
    int cnt = 0;
    int len = s.size();
    for(auto c:s){
        if(c == ' ')
            ++cnt;
    }

    s.resize(len + 2*cnt);
    for(int i = len-1, j=s.size()-1; i < j; --i){
        if(s[i] == ' '){
            s[j--] = '0';
            s[j--] = '2';
            s[j--] = '%';
        }else{
            s[j--] = s[i];
        }
    }

    return s;
}
```

**注意：**

**（1）string是不可变的，需要resize** 

**（2）当i==j时，可以提前结束 **



## 6、从尾到头打印链表

*   递归

>   时间复杂度O(n)   空间复杂度O(n)--递归深度

```c++
void recur(ListNode* head, vector<int>& res){
    if(head == NULL)
        return;
    recur(head->next, res);
    res.push_back(head->val);
}

vector<int> reversePrint(ListNode* head) {
    vector<int> res;
    recur(head, res);
    return res;
}
```

*   辅助栈

>   时间复杂度O(n)   空间复杂度O(n)

```c++
vector<int> reversePrint(ListNode* head) {
    vector<int> res;
    stack<int> s;
    while(head != NULL){
        s.push(head->val);
        head = head->next;
    }
    
    while(!s.empty()){
        res.push_back(s.top());
        s.pop();
    }

    return res;
}
```

*   顺序遍历链表+翻转数组(双指针翻转)
*   翻转链表



##  7、重建二叉树

*   递归

>前序遍历性质： 节点按照 [ 根节点 | 左子树 | 右子树 ] 排序
>中序遍历性质： 节点按照 [ 左子树 | 根节点 | 右子树 ] 排序
>后续遍历性质： 节点按照 [ 左子树 | 右子树 | 根节点 ] 排序

实现一：

```c++
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if(preorder.empty())
        return NULL;
    
    TreeNode* root = new TreeNode(preorder[0]);

    //中序遍历中查找根节点   左子树 | 根节点 | 右子树
    int rootIndex = 0;
    for(int i = 0; i < inorder.size(); ++i){
        if(inorder[i] == preorder[0]){
            rootIndex = i;
            break;
        }
    }
    
    vector<int> left_preorder(preorder.begin()+1, preorder.begin()+ rootIndex+1);
    vector<int> right_preorder(preorder.begin()+rootIndex+1, preorder.end());

    vector<int> left_inorder(inorder.begin(), inorder.begin()+rootIndex);
    vector<int> right_inorder(inorder.begin()+rootIndex+1, inorder.end());

    root->left = buildTree(left_preorder, left_inorder);//递归构造左子树
    root->right = buildTree(right_preorder, right_inorder);//递归构造右子树
    return root;
}
```

实现二：

```c++
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        this->preorder = preorder;
        this->inorder = inorder;

        return recur(0, 0, inorder.size()-1);
    }
private:
    vector<int> preorder;
    vector<int> inorder;

    TreeNode* recur(int pre_root_idx, int in_left_idx, int in_right_idx){
        if(in_left_idx > in_right_idx)
            return NULL;
        TreeNode* root = new TreeNode(preorder[pre_root_idx]);

        int idx = in_left_idx;
        for(int i = in_left_idx; i <= in_right_idx; ++i){
            if(inorder[i] == preorder[pre_root_idx]){
                idx = i;
                break;
            }
        }

        root->left = recur(pre_root_idx+1, in_left_idx, idx-1);
        root->right = recur(pre_root_idx + (idx-1 - in_left_idx +1) + 1, idx + 1, in_right_idx);

        return root;
    }
};
```

**实现2更节省空间**



## 9、用两个栈实现队列

*   双栈

```c++
class CQueue {
public:
    CQueue() {
        while(!s1.empty()) s1.pop();
        while(!s2.empty()) s2.pop();
    }
    
    void appendTail(int value) {
        s1.push(value);
    }
    
    int deleteHead() {
        if(s2.empty()){
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }

        if(s2.empty()){
            return -1;
        } 
        int res = s2.top();
        s2.pop();

        return res;
    }
private:
    stack<int> s1,s2;
};
```



## 10-1 斐波那契数列

*   递归

```c++
class Solution {
public:
    int fib(int n) {
        if(n < 2) return n;
        return fib(n-1) + fib(n-2);
    }
};
```

**执行超时**

*   动态规划

>   时间复杂度O(n)    空间复杂度O(n)

```c++
class Solution {
public:
    int fib(int n) {
        if(n < 2 | n > 100) return n;
        
        int dp[101] = {0};
        dp[1] = 1;
        for(int i = 2; i <= n; ++i){
            dp[i] = (dp[i-1] + dp[i-2])%1000000007;
        }
        return dp[n];
    }
};
```

*   迭代

>   时间复杂度O(n)  空间复杂度O(1)

```c++
class Solution {
public:
    int fib(int n) {
        if(n < 2 | n > 100) return n;
        
        int pre_pre = 0;
        int pre = 1;
        int cur;
        for(int i = 2; i <= n; ++i){
            cur = (pre + pre_pre)%1000000007;
            pre_pre = pre;
            pre = cur;
        }
        return cur;
    }
};
```



## 10-2 青蛙跳台阶

同10-1 斐波那契数列



## 11、旋转数组的最小数字

*   遍历

>   时间复杂度O(n)

*   二分法

>时间复杂度O(logn)

```c++
class Solution {
public:
    int minArray(vector<int>& numbers) {
        int left = 0, right = numbers.size()-1;
        while(left < right){//注意循环结束条件
            int mid = left + ((right - left) >> 1);

            if(numbers[mid] < numbers[right]){
                right = mid;
            } else if(numbers[mid] > numbers[right]){
                left = mid + 1;
            } else {// numbers[mid] == numbers[right], 无法确定最小值在左边还是右边
                right = right - 1;
            }
        }

        return numbers[left];
    }
};
```

**注：为什么不用numbers[mid]和numbers[left]比较**

**二分法的目的是判断mid在哪个排序数组中，从而缩小区间。**

**当numbers[mid]>numbers[left]时，无法确定mid在哪个排序数组中，而right初始值肯定在右排数组中**

>对于以下两示例，当 i = 0, j = 4, m = 2i=0,j=4,m=2 时，有 nums[m] > nums[i] ，而结果不同。
>[1, 2, 3, 4 ,5][1,2,3,4,5] 旋转点 x = 0x=0 ： mm 在右排序数组（此示例只有右排序数组）；
>[3, 4, 5, 1 ,2][3,4,5,1,2] 旋转点 x = 3x=3 ： mm 在左排序数组。
>
>[旋转数组最小数字题解](https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/solution/mian-shi-ti-11-xuan-zhuan-shu-zu-de-zui-xiao-shu-3/)



## 12、矩阵中的路径

*   DFS+剪枝

>   时间复杂度O(MN*3^k)    空间复杂度O(k)   k为字符串长度 

```c++
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        rows = board.size();
        cols = board[0].size();

        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < cols; ++j){
                 if(dfs(board, word, 0, i, j)){
                         return true;
                }
            }
        }
        return false;
    }

    bool dfs(vector<vector<char>>& board, string word, int index, int i, int j){        
        if(i < 0 || i >= rows || j < 0 || j >= cols || board[i][j] != word[index]) return false;
        if(index == word.size()-1) return true;

        board[i][j] = '/0';
        bool res = dfs(board, word, index+1, i-1, j) || dfs(board, word, index+1, i+1, j) || dfs(board, word, index+1, i, j-1) || dfs(board, word, index+1, i, j+1);
        board[i][j] = word[index];
        return res;
    }

    int rows,cols;
};
```



## 13、机器人的运动范围

*   DFS

>时间复杂度O(MN)    空间复杂度O(MN)

```c++
class Solution {
public:
    int movingCount(int m, int n, int k) {
        vector<vector<bool>> visited(m, vector<bool>(n));
        return dfs(visited, m, n, k, 0, 0);
    }

    int dfs(vector<vector<bool>>& visited, int m, int n, int k, int i, int j){
        if(i >= m || j >= n || vistied[i][j] || bitSum(i)+ bitSum(j) > k) return 0;
        visited[i][j] = true;
        return 1+ dfs(visted, m, n, k, i+1, j) + dfs(visted, m, n, k, i, j+1);
    }

    int bitSum(int n){
        int sum = 0;
        while(n > 0){
            sum += n%10;
            n = n/10;
        }
        return sum;
    }
};
```

*   BFS

>   时间复杂度O(MN)   空间复杂度O(MN)

```c++
待完善
```



## 14-1 剪绳子

*   动态规划

>   时间复杂度O(N^2)   空间复杂度O(N)

```c++
class Solution {
public:
    int cuttingRope(int n) {
        int dp[60] = {0};
        dp[0] = 0;
        dp[1] = 1;

        for(int i = 2; i <= n; ++i){
            for(int j = 1; j < i; ++j){
                dp[i] = max(dp[i], max(j*(i-j), j*dp[i-j]));
            }
        }

        return dp[n];
    }
};
```

*   贪心算法

>   时间复杂度O(1)    空间复杂度O(1)

```c++
class Solution {
public:
    int cuttingRope(int n) {
        if(n < 2)
            return 0;
        if(n < 4)
            return n-1;

        int countOf3 = n/3;
        if(n%3 == 1) --countOf3;
        int countOf2 = (n - countOf3*3) >> 1;

        return pow(3, countOf3) * pow(2, countOf2); 
    }
};
```





## 14-II 剪绳子

*   贪心算法

>   时间复杂度O(1)   空间复杂度O(1)

```c++
class Solution {
public:
    int cuttingRope(int n) {
        if(n < 2)
            return 0;
        if(n < 4)
            return n-1;

        long res = 1;
        while(n > 4){
            res *= 3;
            res %= 1000000007;
            n -= 3;
        }

        return res*n %1000000007;
    }
};
```

**注意res类型为long**



## 15、二进制中1的个数

*   利用1，每次左移一次1，然后与n位与，需要左移32次

```c++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        int cnt = 0;
        while(cnt < 32){
            if(n&(1<<cnt))
                ++res;
            ++cnt;
        }
        return res;
    }
};
```



*   利用n&(n-1)，直至n减为0     计算的次数为数据中1的个数

```c++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        while(n > 0){
            res +=1;
            n = n&(n-1);
        }
        return res;
    }
};
```



## 16、数值的整数次方

*   暴力

>   时间超时   时间复杂度O(n)   

```c++
class Solution {
public:
    double myPow(double x, int n) {
        if(x == 0) return 0;

        long exponent = n;
        if(exponent < 0){
            x = 1/x;
            exponent = abs(exponent);
        }

        double res = 1.0;
        while(exponent > 0){
            res *= x;
            --exponent;
        }

        return res;
    }
};
```

*   指数二分法

>   时间复杂度O(logn) 

```c++
class Solution {
public:
    double myPow(double x, int n) {
        if(x == 0) return 0;

        long exponent = n;
        if(exponent < 0){
            x = 1/x;
            exponent = abs(exponent);
        }

        double res = 1.0;
        while(exponent > 0){
            if((exponent&1) == 1)
                res *= x;
            x = x*x;
            exponent = exponent >> 1;
        }

        return res;
    }
};
```

**注意事项**

**指数n为负值时，取绝对值要使用abs而不能使用负号(会溢出)**

**x==0，要提前返回，避免n为0，以及1/x出现除0操作**



## 17、打印从1到最大的n位数

*   不考虑大数情况

```c++
class Solution {
public:
    vector<int> printNumbers(int n) {
        vector<int> res;
        int cnt = pow(10,n);

        for(int i = 1; i < cnt; ++i){
            res.push_back(i);
        }

        return res;
    }
};
```

*   考虑大数情况

```c++
#include <String>
#include <iostream>

using namespace std;

bool increaseNums(char* nums, int n){
    bool flag = true;
    int income = 1;

    for(int i = n-1; i >= 0; --i){
        int num = nums[i]-'0'+income;
        if(num > 9){
            if(i == 0){
                flag = false;
                break;
            }
            nums[i] = '0';
        } else{
            nums[i]+=1;
            break;
        }
    }

    return flag;
}

void printNums(char* nums, int n){
    int i;
    for(i = 0; i < n; ++i){
        if(nums[i] != '0')
            break;
    }
    for(int k = i; k < n; ++k)
        cout << nums[k];
    cout << endl;
}

int main(){
    int n = 2;
     char* nums = new char[n+1];
     for(int i = 0; i < n; ++i)
        nums[i] = '0';

    while(increaseNums(nums, n)){
        printNums(nums, n);
    }

    delete[] nums;
    return 0;
}
```



## 18、删除链表节点

*   双指针+哨兵

```C++
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode* dummy = new ListNode(0);//哨兵，便于处理
        dummy->next = head;
        
        ListNode* pre = dummy;
        ListNode* cur = pre->next;

        while(cur != NULL){
            if(cur->val == val){
                pre->next = cur->next;
                break;
            }
            pre = cur;
            cur = cur->next;
        }

        return dummy->next;
    }
};
```



*   递归

```c++
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if(head == NULL)    return head;

        if(head->val == val)
            return head->next;

        head->next = deleteNode(head->next, val);
        return head;
    }
};
```



## 19、正则表达式匹配

*   待完善



## 20、表示数值的字符串

*   待完善



## 21、调整数组顺序使奇数位于偶数前面

*   首先扫描一遍，统计奇数个数，就可以确定偶数数据的起始下标（需要用另外的一个数组备份数据）

>   时间复杂度O(n)  空间复杂度O(n)

*   双指针

>   时间复杂度O(n)  空间复杂度O(1)

```c++
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int len = nums.size();
        int p = 0,q = 0;//
        while(q < len){
            if(nums[q]%2 == 1){
                swap(nums[p], nums[q]);
                ++p;
            }
            ++q;
        }

        return nums;
    }
};
```



## 22、链表中倒数第K个节点

*   先扫描一遍链表，计算链表长度，然后计算出倒数第K个链表位于正数第几个，再遍历链表

>   时间复杂度O(n)

```c++
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        int len = 0;
        ListNode* p = head;
        while(p != NULL){
            ++len;
            p = p->next;
        }

        int cnt = len-k;
        p = head;
        while(cnt > 0){
            p = p->next;
            --cnt;
        }

        return p;
    }
};
```

*   双指针，前一个指针先走K-1步，然后两指针再同步走，前指针到达链表尾，后指针即为倒数第K个节点

```c++
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* former = head;
        ListNode* latter = head;

        while(k > 0 && former != NULL){
            former = former->next;
            --k;
        }

        while(former != NULL){
            former = former->next;
            latter = latter->next;
        }

        return latter;
    }
};
```



## 24、反转链表

*   头插法 + 哨兵简化操作

>时间复杂度O(n)

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* dummy = new ListNode(0);
        
        ListNode* p = head;
        while(p != NULL){
            ListNode* cur = p;
            p = p->next;
            cur->next = dummy->next;
            dummy->next = cur;
        }

        return dummy->next;;
    }
};
```

*   双指针法

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* p1 = NULL;
        ListNode* p2 = head;

        while(p2 != NULL){
            ListNode* t = p2->next;
            p2->next = p1;
            p1 = p2;
            p2 = t;
        }

        return p1;
    }
};
```

*   递归

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == NULL || head->next == NULL)
            return head;
        
        ListNode* p = reverseList(head->next);

        head->next->next = head;
        head->next = NULL;
        return p;
    }
};
```



## 25、合并两个排序的链表

*   遍历两个排序的链表

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* p = dummy;

        while(l1 != NULL && l2 != NULL){
            if(l1->val > l2->val){
                p->next = l2;
                l2 = l2->next;
            } else {
                p->next = l1;
                l1 = l1->next;
            }
            p = p->next;
        }
        p->next = l1 == NULL? l2:l1;
        return dummy->next;
    }
};
```

*   递归

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == NULL) return l2;
        if(l2 == NULL) return l1;

        if(l1->val <= l2->val){
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }else{
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};
```



## 26、树的子结构

*   递归

>   时间复杂度O(mn)    m为树A节点个数，n为树B节点个数

```c++
class Solution {
public:
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if(A == NULL || B == NULL) return false;
        
        return isSame(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }

    bool isSame(TreeNode* root1, TreeNode* root2){
        if(root2 == NULL) return true;
        if(root1 == NULL) return false;

        return root1->val == root2->val && isSame(root1->left, root2->left) && isSame(root1->right, root2->right);
    }
};
```



## 27、二叉树的镜像

*   前序或者后续遍历

```c++
class Solution {
public:
    TreeNode* mirrorTree(TreeNode* root) {
        if(root == NULL) return root;
        swap(root->left, root->right);

        mirrorTree(root->left);
        mirrorTree(root->right);
        return root;
    }
};
```

**注：中序遍历不行**



## 28、对称的二叉树



*   递归

```c++
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root == NULL) return true;

        return recur(root->left, root->right);
    }

    bool recur(TreeNode* root1, TreeNode* root2){
        if(root1 == NULL && root2 == NULL) return true;
        if(root1 == NULL || root2 == NULL) return false;

        return (root1->val == root2->val) && recur(root1->left, root2->right) && recur(root1->right, root2->left);
    }
};
```



## 29、顺时针打印矩阵

*   画示意图，辅助思考确定边界

```c++
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if(matrix.empty()) return res;
        int t = 0;              //上边界
        int b = matrix.size()-1;//下边界
        int l = 0;              //左边界
        int r = matrix[0].size()-1;//右边界

        while(true){
            //left->right
            for(int i = l; i <= r; ++i)  res.push_back(matrix[t][i]);
            if(++t > b) break;
            //top->bottom
            for(int i = t; i <= b; ++i) res.push_back(matrix[i][r]);
            if(--r < l) break;
            //left->right
            for(int i = r; i >= l; --i) res.push_back(matrix[b][i]);
            if(--b < t) break;
            //bottom->top
            for(int i = b; i >= t; --i) res.push_back(matrix[i][l]);
            if(++l > r) break;
        }

        return res;
    }
};
```



## 30、包含min函数的栈

```c++
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }
    
    void push(int x) {
        s.push(x);
        if(min_stack.empty() || min_stack.top() > x)
            min_stack.push(x);
        else{
            int min_num = min_stack.top();
            min_stack.push(min_num);
        }
    }
    
    void pop() {
        s.pop();
        min_stack.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int min() {
        return min_stack.top();
    }

    stack<int> s;
    stack<int> min_stack;
};
```



## 31、栈的压入弹出序列

```c++
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> s;
        int i = 0;

        for(auto num: pushed){
            s.push(num);
            while(!s.empty() && s.top() == popped[i]){
                s.pop();
                ++i;
            }
        }

        return s.empty();
    }
};
```



## 32-1、从上到下打印二叉树

*   层序遍历

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> levelOrder(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            TreeNode* node = q.front();
            q.pop();
            if(node != NULL){
                res.push_back(node->val);
                q.push(node->left);
                q.push(node->right);
            }
        }

        return res;
    }
};
```



## 32-2、从上到下打印二叉树

*   层序遍历+辅助队列

```c++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(root == NULL) return res;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            int size = q.size();
            vector<int> vec;
            for(int i = 0; i < size; ++i){
                TreeNode* node = q.front();
                q.pop();
                vec.push_back(node->val);
                if(node->left != NULL)
                    q.push(node->left);
                if(node->right != NULL)
                    q.push(node->right);
            }
            res.push_back(vec);
        }

        return res;
    }
};
```



## 32-3、从上到下打印二叉树

*   层序遍历+数组根据奇偶层改变插入顺序（或者数组翻转）

```c++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(root == NULL) return res;
        queue<TreeNode*> q;
        q.push(root);
        bool odd = true;

        while(!q.empty()){
            int size = q.size();
            vector<int> vec(size);
            for(int i = 0; i < size; ++i){
                TreeNode* node = q.front();
                q.pop();
                int index = odd? i: size-1-i;
                vec[index] = node->val;
                if(node->left != NULL)
                    q.push(node->left);
                if(node->right != NULL)
                    q.push(node->right);
            }
            odd = !odd;
            res.push_back(vec);
        }

        return res;
    }
};
```

*   层序遍历+双端队列

```c++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(root == NULL) return res;
        deque<TreeNode*> q;
        q.push_back(root);
        bool odd = false;

        while(!q.empty()){
            int size = q.size();
            vector<int> vec;
            for(int i = 0; i < size; ++i){
                if(odd){
                    TreeNode* node = q.back();
                    q.pop_back();
                    vec.push_back(node->val);
                    if(node->right != NULL)
                        q.push_front(node->right);
                    if(node->left != NULL)
                        q.push_front(node->left);

                } else{
                    TreeNode* node = q.front();
                    q.pop_front();
                    vec.push_back(node->val);
                    if(node->left != NULL)
                        q.push_back(node->left);
                    if(node->right != NULL)
                        q.push_back(node->right);
                }
                
            }
            odd = !odd;
            res.push_back(vec);
        }

        return res;
    }
};
```

*   层序遍历+双栈

>   待完善



## 33、二叉搜索树的后续遍历

*   分治+递归

>   后续遍历： 左子树 | 右子树 | 根节点
>
>   二叉搜索树特点：左子树节点都小于根节点，右子树节点都大于根节点

```c++
class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        return verify(postorder, 0, postorder.size()-1); 
    }

    bool verify(vector<int>& postorder, int start, int end){
        if(start >= end) return true;

        int root_val = postorder[end];
        int index = start;
        while(index <= end && postorder[index] < root_val)
            ++index;
        for(int i = index; i < end; ++i){
            if(postorder[i] < root_val)
                return false;
        }

        return verify(postorder, start, index-1) && verify(postorder, index, end-1);
    }
};
```



## 34、二叉树中和为某一值的路径

*   前序遍历+中间过程值记录

```c++
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        searchPathSum(root, sum, vec);
        return res;
    }

    void searchPathSum(TreeNode* root, int sum, vector<int> vec){
        if(root == NULL) return;

        sum -= root->val;
        vec.push_back(root->val);
        if(sum == 0 && root->left == NULL && root->right == NULL){
            res.push_back(vec);
        }
        
        searchPathSum(root->left, sum, vec);
        searchPathSum(root->right, sum, vec);
        vec.pop_back();
        
        return;
    }

    vector<vector<int>> res;
    vector<int> vec;
};
```



## 35、复杂链表的复制

>步骤：
>
>1、在原链表上复制每个节点
>
>2、调整复制节点的random指针
>
>3、将原链表和复制链表分离

```c++
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == NULL) return NULL;
        Node* copy_head;

        Node* node = head;
        //在每个节点后面插入复制的节点  如原来1->2->3 变为1->1->2->2->3->3
        while(node != NULL){
            Node* copy_node = new Node(node->val);
            copy_node->next = node->next;
            copy_node->random = node->random;
            node->next = copy_node;
            node = node->next->next;
        }

        //调整复制节点的random指向
        node = head;
        while(node != NULL){
            Node* copy_node = node->next;
            if(node->random != NULL)
                copy_node->random = node->random->next;
            node = node->next->next;
        }

        //将原链表和复制的链表分离
        node = head;
        copy_head = head->next;
        while(node != NULL){
            Node* copy_node = node->next;
            node->next = copy_node->next;
            node = node->next;
            if(node != NULL)
                copy_node->next = node->next;
        }

        return copy_head;
    }
};
```

