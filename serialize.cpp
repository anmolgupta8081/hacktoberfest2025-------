/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // Encodes a tree to a single string (Serialization)
    string serialize(TreeNode* root) {
        // Step 1: Handle empty tree
        if (!root) return "";
        
        string s = "";
        queue<TreeNode*> q;
        q.push(root);
        
        // Step 2: Level-order traversal (BFS)
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();

            // Step 3: Build string with values and null markers
            if (curr == NULL) {
                s.append("#,");
            } else {
                s.append(to_string(curr->val) + ",");
                // Add children to queue (even if NULL)
                q.push(curr->left);
                q.push(curr->right);
            }
        }
        return s;
    }

    // Decodes your encoded data to tree (Deserialization)
    TreeNode* deserialize(string data) {
        // Step 1: Handle empty string
        if (data.size() == 0) return NULL;
        
        stringstream s(data);
        string str;
        
        // Step 2: Parse root node
        getline(s, str, ',');
        TreeNode* root = new TreeNode(stoi(str));
        queue<TreeNode*> q;
        q.push(root);
        
        // Step 3: Level-order reconstruction
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            // Step 4: Process left child
            getline(s, str, ',');
            if (str == "#") {
                node->left = NULL;
            } else {
                TreeNode* leftNode = new TreeNode(stoi(str));
                node->left = leftNode;
                q.push(leftNode);
            }

            // Step 4: Process right child
            getline(s, str, ',');
            if (str == "#") {
                node->right = NULL;
            } else {
                TreeNode* rightNode = new TreeNode(stoi(str));
                node->right = rightNode;
                q.push(rightNode);
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
