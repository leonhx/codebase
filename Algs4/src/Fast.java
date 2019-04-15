import java.util.Arrays;

public class Fast {

    private static void printAndDraw(Point w, Point[] points, int lo, int hi) {
        Point[] tmp = new Point[hi - lo + 1];
        tmp[0] = w;
        for (int i = 1; i < tmp.length; i++) {
            tmp[i] = points[lo + i - 1];
        }
        MergeX.sort(tmp);
        if (tmp[0].compareTo(w) != 0)
            return;
        tmp[0].drawTo(tmp[tmp.length - 1]);
        for (int i = 0; i < tmp.length; i++) {
            StdOut.print(tmp[i]);
            if (i == tmp.length - 1)
                StdOut.println();
            else
                StdOut.print(" -> ");
        }
    }

    public static void main(String[] args) {
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        String filename = args[0];
        final In in = new In(filename);
        final int N = in.readInt();
        Point[] points = new Point[N];
        for (int i = 0; i < points.length; i++) {
            points[i] = new Point(in.readInt(), in.readInt());
            points[i].draw();
        }
        MergeX.sort(points);
        for (int i = 0; i < points.length - 3; i++) {
            Point w = points[i];
            Point[] tmp = new Point[N - 1];
            for (int j = 0; j < tmp.length; j++) {
                if (j < i)
                    tmp[j] = points[j];
                else
                    tmp[j] = points[j + 1];
            }
            Arrays.sort(tmp, w.SLOPE_ORDER);
            double[] slopes = new double[N - 1];
            for (int j = 0; j < tmp.length; j++) {
                slopes[j] = w.slopeTo(tmp[j]);
            }
            int j = 0;
            while (j < slopes.length) {
                double k = slopes[j];
                int m = j + 1;
                while (m < slopes.length && slopes[m] == k)
                    m++;
                if (m - j >= 3) {
                    printAndDraw(w, tmp, j, m);
                }
                j = m;
            }
        }
    }
}
