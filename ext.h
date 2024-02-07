#pragma once
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
template<class T> using gque = __gnu_pbds::priority_queue<T>;
template<class T> using lque = __gnu_pbds::priority_queue<T, std::greater<T>>;
template<class T> using RBT = __gnu_pbds::tree<T, __gnu_pbds::null_type,
    std::less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
#define EXT