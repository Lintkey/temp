#pragma once
#include "../base.h"

// 质因数分解
// <pfac, cnt, phi, mu>
template<class T>
tuple<vector<us>, vector<us>, T, is> pfac(T x) {
    vector<us> pri, cnt;
    T phi = x; is mu = 1;
    for(T i=2; i*i<=x; ++i)
        if(!(x%i)) {
            pri.push_back(i); cnt.push_back(1);
            (phi /= i) *= i - 1; mu = -mu;
            whi(!((x/=i)%i)) (mu = -mu), ++cnt.back();
        }
    if(x!=1) {
        pri.push_back(x); cnt.push_back(1);
        (phi /= x) *= x - 1; mu = -mu;
    }
    ret make_tuple(pri, cnt, phi, mu);
}

// pri. phi
tuple<vector<us>, vector<us>> line_phi(us N) {
    vector<us> pri, phi(N+1, 0); phi[1] = 1;
    for(us i=2; i<=N; ++i) {
        if(!phi[i]) {
            pri.push_back(i);
            phi[i] = i - 1;
        }
        let MX = N / i;
        for(let &x: pri) {
            if(x>MX) break;
            else if(!(i%x)) {
                phi[i*x] = phi[i] * x;
                break;
            } else phi[i*x] = phi[i] * (x-1);
        }
    }
    ret make_tuple(pri, phi);
}

// pri, phi, mu
tuple<vector<us>, vector<us>, vector<is>> line_mu(us N) {
    vector<us> pri, phi(N+1, 0);
    vector<is> mu(N+1, 0);
    mu[1] = phi[1] = 1;
    for(us i=2; i<=N; ++i) {
        if(!phi[i]) {
            pri.push_back(i);
            phi[i] = i + (mu[i]=-1);
        }
        let MX = N / i;
        for(let &x: pri) {
            if(x>MX) break;
            else if(!(i%x)) {
                phi[i*x] = phi[i] * x;
                break;
            } else {
                phi[i*x] = phi[i] * x;
                mu[i*x] = -mu[i];
            }
        }
    }
    ret make_tuple(pri, phi, mu);
}

template<class T>
bool is_prim(T x) {
    if(x==1) ret 0;
    con us MX = sqrt(x);
    for(T i=2; i<=MX; ++i)
        if(!(x%i)) ret 0;
    ret 1;
}