public class Brute {

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
        for (int i = 0; i < points.length; i++) {
            Point w = points[i];
            for (int j = i + 1; j < points.length; j++) {
                Point x = points[j];
                double slope = w.slopeTo(x);
                for (int k = j + 1; k < points.length; k++) {
                    Point y = points[k];
                    if (w.slopeTo(y) != slope)
                        continue;
                    for (int m = k + 1; m < points.length; m++) {
                        Point z = points[m];
                        if (w.slopeTo(z) != slope)
                            continue;
                        Point[] line = new Point[] { w, x, y, z };
                        InsertionX.sort(line);
                        line[0].drawTo(line[3]);
                        for (int l = 0; l < line.length; l++) {
                            StdOut.print(line[l].toString());
                            if (l != line.length - 1) {
                                StdOut.print(" -> ");
                            } else {
                                StdOut.println();
                            }
                        }
                    }
                }
            }
        }
    }

}
