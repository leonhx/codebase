public class KdTree {
    private Node root;
    private boolean contains;

    public static void main(String[] args) {
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public int size() {
        return size(root);
    }

    private int size(Node x) {
        if (x == null) return 0;
        else return x.N;
    }

    public void insert(Point2D p) {
        // TODO
    }

    public boolean contains(Point2D p) {
        return contains(root, p);
    }

    private boolean contains(Node x, Point2D p) {
        if (x == null) return false;
        if (x.point.equals(p)) return true;

        double cmp = 0.0;
        if (x.isVertical) {
            cmp = x.point.x() - p.x();
        } else {
            cmp = x.point.y() - p.y();
        }

        if (cmp < 0.0) return contains(x.left, p);
        else return contains(x.right, p);
    }

    public void draw() {
        Stack<LineSegment> lines = new Stack<LineSegment>();
        Queue<Node> nodes = new Queue<Node>();
        if (root != null)
            nodes.enqueue(root);

        while (!nodes.isEmpty()) {
            Node n = nodes.dequeue();
            if (n.left != null)
                nodes.enqueue(n.left);
            if (n.right != null)
                nodes.enqueue(n.right);
            double xMin = 0.0, xMax = 1.0, yMin = 0.0, yMax = 1.0;
            for (LineSegment line : lines) {
                if (!n.isVertical && line.isVertical) {
                    if (n.point.y() < line.start.y() || n.point.y() > line.end.y())
                        continue;
                    double xLine = line.start.x();
                    if (n.point.x() < xLine && xMax > xLine) {
                        xMax = xLine;
                    } else if (n.point.x() > xLine && xMin < xLine) {
                        xMin = xLine;
                    }
                } else if (n.isVertical && !line.isVertical) {
                    if (n.point.x() < line.start.x() || n.point.x() > line.end.x())
                        continue;
                    double yLine = line.start.y();
                    if (n.point.y() < yLine && yMax > yLine) {
                        yMax = yLine;
                    } else if (n.point.y() > yLine && yMin < yLine) {
                        yMin = yLine;
                    }
                }
            }
            if (n.isVertical) {
                StdDraw.line(n.point.x(), yMin, n.point.x(), yMax);
            } else {
                StdDraw.line(xMin, n.point.y(), xMax, n.point.y());
            }
        }
    }

    public Iterable<Point2D> range(RectHV rect) {
        return null; // TODO
    }

    public Point2D nearest(Point2D point) {
        return null; // TODO
    }

    private class Node {
        private Point2D point;
        private boolean isVertical;
        private Node left, right;
        private int N;

        public Node(Point2D point, boolean isVertical, int N) {
            this.point = point;
            this.isVertical = isVertical;
            this.N = N;
        }
    }

    private class LineSegment {
        private Point2D start, end;
        private boolean isVertical;

        public LineSegment(Point2D start, Point2D end) {
            assert start.y() <= end.y();
            assert start.x() <= end.x();
            this.start = start;
            this.end = end;
            this.isVertical = start.x() == end.x();
        }
    }
}
