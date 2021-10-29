//Author:$%U%$
//Date:$%Y%$-$%M%$-$%D%$
#include<cstdio>
#include<cctype>
template <typename tn>void fead(tn &n) {
    tn f = 1, t = 0, r = 1; char ch = getchar();
    while (!isdigit(ch)) {if (ch == '-') f = -1; ch = getchar();}
    while (isdigit(ch)) t = t * 10 + ch - '0', ch = getchar();
    if (ch == '.') {ch = getchar(); while (isdigit(ch)) r *= 10, t += (ch - '0') / r, ch = getchar();}
    n = f * t;
}
int main() {
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    return 0;
}