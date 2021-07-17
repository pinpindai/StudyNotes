struct TreeNode{
    int val;
    TreeNode* left, right;
    TreeNode(int val) { this.val = val;}
}

//广度优先搜索
void BFS(TreeNode* root) {
    queue<TreeNode*> q;
    if(root != null) 
        q.push(root);
    
    int size;
    TreeNode* node;
    while(!q.empty()) {
        size = q.size();
        for(int i = 0; i < size; ++i){
            node = q.front(); q.pop(); //取出队列最前面的节点
            
            //处理当前的节点
            process(node);
            
            //将当前节点的左孩子、右孩子节点插入队列末尾
            if(node->left != null) {
                q.push(node->left);
            }
            if(node->right != null) {
                q.push(node->right);
            }
        }
    }
}