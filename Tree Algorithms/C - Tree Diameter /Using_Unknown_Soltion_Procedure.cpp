#include <stdio.h>

#define N 200000

#define MAX(a, b) ((a) > (b)) ? (a) : (b);

static inline int getint() {
    int x, y;
    while((x = getchar_unlocked()) < '0') {}
    x -= '0';
    while((y = getchar_unlocked()) >= '0') { x = x * 10 + y - '0'; }
    return x;
}

int main() {
	static int p[N], d[N], h[N];
	int n;
	scanf("%d", &n);

	for(int i = 1; i < n ; i++) {
		int a = getint();
		int b = getint();

		if(!p[a]) {
			p[a] = b;
			d[b]++;
		} else {
			int op = p[b];
			p[b] = a;
			d[a]++;
			while(op) {
				int gp = p[op];
				d[op]--;
				d[b]++;
				p[op] = b;
				b = op;
				op = gp;
			}
		}
	}

	int diam = 0;
	for(int i = 1; i <= n; i++) {
		int e = i;
		while(p[e] && d[e] == 0) {
			d[e]--;
			int pe = p[e];
			diam = MAX(diam, h[e] + h[pe] + 1);
			h[pe] = MAX(h[pe], h[e] + 1);
			e = pe;
			d[e]--;
		}
	}

	printf("%d\n", diam);
}
