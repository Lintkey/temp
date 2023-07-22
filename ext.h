#include "base.h"
#include <bits/extc++.h>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template<class T> using ex_gque = __gnu_pbds::priority_queue<T>;
template<class T> using ex_lque = __gnu_pbds::priority_queue<T, greater<T>>;
template<class T> using RBT = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;