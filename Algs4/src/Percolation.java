public class Percolation {
    private int N;
    private boolean[][] sites;
    private WeightedQuickUnionUF uf;
    private WeightedQuickUnionUF ufFullness;

    public Percolation(int N) {
        if (N <= 0) {
            throw new java.lang.IllegalArgumentException();
        }
        this.N = N;
        sites = new boolean[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                sites[i][j] = false;
            }
        }
        uf = new WeightedQuickUnionUF(N * N + 2);
        ufFullness = new WeightedQuickUnionUF(N * N + 2);
    }

    public void open(int m, int n) {
        if (m <= 0 || m > N || n <= 0 || n > N) {
            throw new java.lang.IndexOutOfBoundsException();
        }
        int i = m - 1;
        int j = n - 1;

        if (sites[i][j])
            return;

        sites[i][j] = true;
        if (i - 1 >= 0 && sites[i - 1][j]) {
            uf.union(N * (i - 1) + j, N * i + j);
            ufFullness.union(N * (i - 1) + j, N * i + j);
        }
        if (i + 1 < N && sites[i + 1][j]) {
            uf.union(N * (i + 1) + j, N * i + j);
            ufFullness.union(N * (i + 1) + j, N * i + j);
        }
        if (j - 1 >= 0 && sites[i][j - 1]) {
            uf.union(N * i + j - 1, N * i + j);
            ufFullness.union(N * i + j - 1, N * i + j);
        }
        if (j + 1 < N && sites[i][j + 1]) {
            uf.union(N * i + j + 1, N * i + j);
            ufFullness.union(N * i + j + 1, N * i + j);
        }
        if (i == 0) {
            uf.union(N * i + j, N * N);
            ufFullness.union(N * i + j, N * N);
        }
        if (i == N - 1) {
            uf.union(N * i + j, N * N + 1);
        }
    }

    public boolean isOpen(int m, int n) {
        if (m <= 0 || m > N || n <= 0 || n > N) {
            throw new java.lang.IndexOutOfBoundsException();
        }
        int i = m - 1;
        int j = n - 1;

        return sites[i][j];
    }

    public boolean isFull(int m, int n) {
        if (m <= 0 || m > N || n <= 0 || n > N) {
            throw new java.lang.IndexOutOfBoundsException();
        }
        int i = m - 1;
        int j = n - 1;

        return sites[i][j] && ufFullness.connected(N * N, N * i + j);
    }

    public boolean percolates() {
        return uf.connected(N * N, N * N + 1);
    }

    public static void main(String[] args) {
        Percolation per = new Percolation(3);
        per.open(1, 1);
        per.open(3, 1);
        per.open(2, 1);
        per.open(3, 3);
        StdOut.println(per.isFull(3, 3));
    }
}
