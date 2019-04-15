
public class PointSET {
    private final SET<Point2D> points;

    public PointSET() {
        points = new SET<Point2D>();
    }

    public boolean isEmpty() {
        return points.isEmpty();
    }

    public int size() {
        return points.size();
    }

    public void insert(Point2D p) {
        points.add(p);
    }

    public boolean contains(Point2D p) {
        return points.contains(p);
    }

    public void draw() {
        for (Point2D p : points) {
            StdDraw.point(p.x(), p.y());
        }
    }

    public Iterable<Point2D> range(RectHV rect) {
        Stack<Point2D> inRangePoints = new Stack<Point2D>();

        for (Point2D p : points) {
            if (rect.contains(p)) {
                inRangePoints.push(p);
            }
        }

        return inRangePoints;
    }

    public Point2D nearest(Point2D point) {
        Point2D nearestPoint = null;
        double minDist = Double.MAX_VALUE;

        for (Point2D p : points) {
            final double dist = point.distanceTo(p);
            if (dist < minDist) {
                nearestPoint = p;
                minDist = dist;
            }
        }

        return nearestPoint;
    }

    public static void main(String[] args) {
    }
}