void recursion(int leval) {
    //1、判断递归是否结束
    if (leval > MAX_LEVEL) {
        std::cout << result << std::endl;
        return;
    }

    //2、处理本层逻辑
    process();

    //3、递归
    recursion(level+1);

    //4、重置状态(如果需要的话)
    reverse_state(level);
}