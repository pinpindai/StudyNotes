//注意使用二分查找的前提条件是数组a[n]有序
//其他二分查找的变种也是在此模板上进行修改
bool BinarySearch(int a[], int n, int target){
    int left = 0;
    int right = n-1;
    int middle;
    
    //1、注意循环的判断条件 left <= right
    while(left <= right) {
        //2、注意middle=(left+right)/2可能会发生溢出
        middle = left + ((right - left) >> 1);
        
        if(a[middle] == target) {
            //找到了目标值
            return true;
        } else if(a[middle] > target) {
            right = middle - 1;
        } else { // a[middle] < target
            left = middle + 1;
        }
    }
    
    //没找到返回false
    return false;
}