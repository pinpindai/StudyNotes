//动态规划的核心点在于状态的定义
//状态定义的好，就会很容易推出状态转移方程
void DynamicPrograming(int a[], int n) {
    //1、定义状态含义 明确dp[i]的含义
    int dp[n+1] = {0};
    
    //2、确定初始状态
    dp[0] = 0;
    dp[1] = 1;
    
    //3、根据状态转移方程推导计算
    for(int i = 2; i <= n; ++i){
        //状态转移方程 
        dp[i] = min(...);
    }
    
    //4、返回最优解
    return dp[n];
}