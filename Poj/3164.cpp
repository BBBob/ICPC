#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
#define LL long long


const int Maxn = 1000;
const double MOD = 1e9;
struct obj
{
    int u, v;
    double w;
}e[Maxn * Maxn];
int n, m;

/*
 * ��С����ͼ�����̶���     O(VE)
 * ����ͼ��С������
 * �����̶������һ�����ڵ������е��������ıߣ�
 * ��������2*MOD����߷���ֵΪ-1, ����ͨ; ���, ���������������Ľ��
 * ����pre����Ϣ�ܹ�����������
 * ע��������0~n-1, ��ΪҪ�������±�Ž�ͼ��ͳһ
 * mytype ����ʵ�����ȷ��
 */
typedef double mytype;
int visit[Maxn], pre[Maxn], belong[Maxn], ROOT;
mytype inv[Maxn];
mytype dirtree(int n, int m, int root) {
    mytype sum = 0;
    int i, j, k, u, v;
    while (true) {
        for (i = 0; i < n; i++) {
            inv[i] = MOD;
            pre[i] = -1;
            belong[i] = -1;
            visit[i] = -1;
        }
        inv[root] = 0;
        for (i = 0; i < m; i++) {//��ԭ���⣬��ÿ�������С���
            u = e[i].u; v = e[i].v;
            if (u != v) {
                if (e[i].w < inv[v]) {
                    inv[v] = e[i].w;
                    pre[v] = u;
                    if(u == root) ROOT = i; //��¼�����ڵı�
                                            //�����ʱ����ROOT-m������ԭͼ�ĸ����
                }
            }
        }
        for (i = 0; i < n; i++) {

            if (inv[i] == MOD) return -1;
        }
        int num = 0;
        for (i = 0; i < n; i++) { //��Ȧ������Ȧ
            if (visit[i] == -1) {
                j = i;
                for(j = i; j != -1 && visit[j] == -1 && j != root; j = pre[j]) {
                    visit[j] = i;
                }
                if (j != -1 && visit[j] == i) {
                    for (k = pre[j]; k != j; k = pre[k]) {
                        belong[k] = num;
                    }
                    belong[j] = num ++ ;
                }
            }
            sum += inv[i];
        }
        if (num == 0) return sum;
        for (i = 0; i < n; i++){
            if (belong[i] == -1) {
                belong[i] = num ++ ;
            }
        }
        for (i = 0; i < m; i++) { //���¹�ͼ
            e[i].w = e[i].w - inv[e[i].v];
            e[i].v = belong[e[i].v];
            e[i].u = belong[e[i].u];
        }
        n = num;
        root = belong[root];
    }
}

int x[Maxn], y[Maxn];

double SQR(LL x) { return x * x; }

int main()
{
    while(~scanf("%d%d", &n, &m)) {
        for(int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);
        for(int i = 0; i < m; i++) scanf("%d%d", &e[i].u, &e[i].v);
        for(int i = 0; i < m; i++) { e[i].u--; e[i].v--; }
        for(int i = 0; i < m; i++) e[i].w = sqrt(SQR(x[e[i].u] - x[e[i].v]) + SQR(y[e[i].u] - y[e[i].v]));
        double ans = dirtree(n, m, 0);
        if(ans > 2 * MOD || ans < 0) puts("poor snoopy");
        else printf("%.2f\n", ans);
    }
    return 0;
}
