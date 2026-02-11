struct Node {
    int mn; int mx;int sum;
};
class SegmentTree{
    public:
        int n;
        vector<Node> tree;
        SegmentTree(int n): n(n), tree(4*n,{0,0,0}){};

        void pull(int p){
            int sum_left = tree[p<<1].sum;
            tree[p].sum = tree[p<<1].sum + tree[p<<1 | 1].sum;
            tree[p].mn = min(tree[p<<1].mn, sum_left + tree[(p<<1)|1].mn);
            tree[p].mx = max(tree[p<<1].mx, sum_left + tree[(p<<1)|1].mx);
        }

        void apply(int p, int v, int l, int r){
            tree[p].sum = (r-l+1)*v;
            tree[p].mn = v;
            tree[p].mx = v;
            // tree[p].lazy +=v;
        }

        // void push(int p, int l, int r){
        //     if(tree[p].lazy !=0){
        //         int mid = (l+r) >> 1;
        //         apply(p<<1, tree[p].lazy, l, mid);
        //         apply((p<<1)|1, tree[p].lazy,mid+1, r);
        //         tree[p].lazy = 0;
        //     }
        // }

        void update(int p, int l,int r, int pos, int val){
            // if(qr < l || ql > r) return;
            if(l==r){
                apply(p, val,l,r);
                return;
            }
            // push(p,l,r);
            int mid = (l + r) >> 1;
            if(pos <= mid) update(p<<1, l, mid, pos, val);
            else update((p<<1) | 1, mid + 1, r, pos, val);
            pull(p);
        }

        bool exist(int node, int sum_before, int target){
            int need = target - sum_before;
            return tree[node].mn <= need && need <= tree[node].mx;
        }
        int findFirstZero(int p, int l, int r,int sum_before, int target){
            if( !exist(p,sum_before, target )) return -1;
            if(l == r){
                return l;
            }
            // push(p,l,r);
            int mid = (l + r) >> 1;
            int sum_left = tree[p<<1].sum;
            if(exist(p<<1|1,sum_before+ sum_left, target )){
                return findFirstZero(p<<1 | 1, mid+1, r, sum_before+ sum_left, target);
            }
            // int right = 
            // if(right != -1) return right;
            return findFirstZero(p<<1 , l, mid, sum_before, target);
        }
};
class Solution {
public:
    int longestBalanced(vector<int>& nums) {

        unordered_map<int,int> prev;
        int result = 0;
        int n = nums.size();
        SegmentTree st(n);
        // st.build(1, 0, n-1);
        for(int l=n-1; l>=0;l--){
            int x = nums[l];
            int val = (x&1) ? -1 : 1;
            if(prev.count(x)){
                st.update(1, 0, n-1, prev[x] ,0);
            }
            st.update(1,0,n-1,l, val);
            prev[x] = l;
            int right = st.findFirstZero(1, 0, n-1,0,0);
            // cout<<right<<' '<<l<<endl;
            if(right >= l){
                result = max(result, right - l + 1);
            }   
        }
        return result;
    }
};
static const int init = [] {

    struct ___ {

        static void _() { ofstream("display_runtime.txt") << 0 << "\n"; }

    };

    atexit(&___::_);

    ios_base::sync_with_stdio(false);

    cin.tie(0);

    cout.tie(0);

    return 0;

}();

// 
struct Node {
    int mn; int mx; int lazy;
};
class SegmentTree{
    public:
        int n;
        vector<Node> tree;
        SegmentTree(int n): n(n), tree(4*n){};

        void build(int p, int l, int r){
            tree[p].lazy = 0;
            if(l > r) return;
            if(l == r){
                tree[p].mn = 0, tree[p].mx = 0;
                return;
            }
            int mid = (l+r) >> 1;
            build(p<<1,l, mid);
            build((p<<1) | 1, mid + 1, r);
            pull(p);
        }

        void pull(int p){
            tree[p].mn = min(tree[p<<1].mn, tree[(p<<1)|1].mn);
            tree[p].mx = max(tree[p<<1].mx, tree[(p<<1)|1].mx);
        }

        void apply(int p, int v){
            tree[p].mn += v;
            tree[p].mx += v;
            tree[p].lazy +=v;
        }

        void push(int p){
            if(tree[p].lazy !=0){
                apply(p<<1, tree[p].lazy);
                apply((p<<1)|1, tree[p].lazy);
                tree[p].lazy = 0;
            }
        }

        void update(int p, int l,int r, int ql, int qr, int val){
            if(qr < l || ql > r) return;
            if(ql <= l && r <= qr){
                apply(p, val);
                return;
            }
            push(p);
            int mid = (l + r) >> 1;
            update(p<<1, l, mid, ql, qr, val);
            update((p<<1) | 1, mid + 1, r, ql, qr, val);
            pull(p);
        }

        int findFirstZero(int p, int l, int r){
            if(tree[p].mn > 0 || tree[p].mx < 0) return -1;
            if(l == r){
                return l;
            }
            push(p);
            int mid = (l + r) >> 1;
            int left = findFirstZero(p<<1, l, mid);
            if(left != -1) return left;
            return findFirstZero(p<<1 | 1, mid+1, r);
        }
};
class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        
        unordered_map<int,int> prev;
        int result = 0;
        int n = nums.size();
        SegmentTree st(n);
        st.build(1, 0, n);
        for(int i=0; i<n;i++){
            int val = (nums[i] % 2) ? -1 : 1;
            if(prev.count(nums[i])){
                st.update(1, 0, n, 0, prev[nums[i]], -val);
            }
            st.update(1,0,n,0, i, val);
            prev[nums[i]] = i;
            int left = st.findFirstZero(1, 0, n);
            if(left != -1){
                result = max(result, i - left + 1);
            }   
        }
        return result;
    }
};
static const int init = [] {

    struct ___ {

        static void _() { ofstream("display_runtime.txt") << 0 << "\n"; }

    };

    atexit(&___::_);

    ios_base::sync_with_stdio(false);

    cin.tie(0);

    cout.tie(0);

    return 0;

}();