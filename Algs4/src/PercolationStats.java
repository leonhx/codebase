public class PercolationStats {

    private double[] ps;

    public PercolationStats(int N, int T) {
        if (N <= 0 || T <= 0) {
            throw new java.lang.IllegalArgumentException();
        }

        ps = new double[T];
        for (int i = 0; i < T; i++) {
            Percolation per = new Percolation(N);
            while (!per.percolates()) {
                int l = StdRandom.uniform(N * N);
                if (!per.isOpen(l / N + 1, l % N + 1)) {
                    per.open(l / N + 1, l % N + 1);
                }
            }
            int nOpen = 0;
            for (int j = 1; j <= N; j++) {
                for (int k = 1; k <= N; k++) {
                    if (per.isOpen(j, k)) {
                        nOpen++;
                    }
                }
            }
            ps[i] = (double) nOpen / (N * N);
        }
    }

    public double mean() {
        double sum = 0.0;
        for (double p : ps) {
            sum += p;
        }

        return sum / ps.length;
    }

    public double stddev() {
        double avg = mean();
        double sigma = 0.0;
        for (double p : ps) {
            sigma += (avg - p) * (avg - p);
        }
        sigma /= (ps.length - 1);

        return Math.sqrt(sigma);
    }

    public double confidenceLo() {
        double avg = mean();
        double std = stddev();

        return avg - 1.96 * std / Math.sqrt(ps.length);
    }

    public double confidenceHi() {
        double avg = mean();
        double std = stddev();

        return avg + 1.96 * std / Math.sqrt(ps.length);
    }

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        int T = Integer.parseInt(args[1]);

        PercolationStats stats = new PercolationStats(N, T);
        StdOut.printf("mean                    = %s\n", stats.mean());
        StdOut.printf("stddev                  = %s\n", stats.stddev());
        StdOut.printf("95%% confidence interval = %s, %s\n",
                stats.confidenceLo(), stats.confidenceHi() + "\n");
    }

}
