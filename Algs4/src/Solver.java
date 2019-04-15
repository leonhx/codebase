import java.util.Iterator;

public class Solver {
    private class Node implements Comparable<Node> {
        private Board board;
        private Node prev;
        private int moves;
        private int dist;

        public Node(Board board, Node prev) {
            this.board = board;
            this.prev = prev;
            if (prev == null) {
                this.moves = 0;
            } else {
                this.moves = prev.getMoves() + 1;
            }
            this.dist = board.manhattan();
        }

        public Board getBoard() {
            return board;
        }

        public Node getPrev() {
            return prev;
        }

        public int getMoves() {
            return moves;
        }

        public int getPriority() {
            return moves + dist;
        }

        public boolean hasSearchedBefore() {
            Node node = getPrev();
            while (node != null) {
                if (node.getBoard().equals(this.board)) {
                    return true;
                }
                node = node.getPrev();
            }
            return false;
        }

        @Override
        public int compareTo(Node that) {
            return this.getPriority() - that.getPriority();
        }
    }

    private final MinPQ<Node> initQueue = new MinPQ<Node>();
    private final MinPQ<Node> twinQueue = new MinPQ<Node>();
    private Node goal = null;
    private boolean solvable = false;

    public Solver(Board initial) {
        initQueue.insert(new Node(initial, null));
        twinQueue.insert(new Node(initial.twin(), null));

        while (!initQueue.isEmpty() && !twinQueue.isEmpty()) {
            final Node init = initQueue.delMin();
            if (init.getBoard().isGoal()) {
                goal = init;
                solvable = true;
                break;
            }

            final Node twin = twinQueue.delMin();
            if (twin.getBoard().isGoal()) {
                goal = twin;
                solvable = false;
                break;
            }

            for (Board board : init.getBoard().neighbors()) {
                Node node = new Node(board, init);
                if (!node.hasSearchedBefore()) {
                    initQueue.insert(node);
                }
            }

            for (Board board : twin.getBoard().neighbors()) {
                Node node = new Node(board, twin);
                if (!node.hasSearchedBefore()) {
                    twinQueue.insert(node);
                }
            }
        }
    }

    public boolean isSolvable() { // is the initial board solvable?
        return solvable;
    }

    public int moves() { // min number of moves to solve initial board; -1 if
                         // unsolvable
        if (!solvable) {
            return -1;
        } else {
            return goal.getMoves();
        }
    }

    private class ArrayIterator implements Iterator<Board> {
        private Board[] arr;
        private int i;

        public ArrayIterator(Board[] arr) {
            this.arr = arr;
            this.i = 0;
        }

        @Override
        public boolean hasNext() {
            return i < arr.length;
        }

        @Override
        public Board next() {
            return arr[i++];
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    public Iterable<Board> solution() { // sequence of boards in a shortest
                                        // solution; null if unsolvable
        if (!solvable) {
            return null;
        } else {
            Node node = goal;
            final Board[] sol = new Board[moves() + 1];
            for (int i = sol.length - 1; i >= 0; i--) {
                sol[i] = node.getBoard();
                node = node.getPrev();
            }

            return new Iterable<Board>() {
                @Override
                public Iterator<Board> iterator() {
                    return new ArrayIterator(sol);
                }
            };
        }
    }

    public static void main(String[] args) {

        // create initial board from file
        In in = new In(args[0]);
        int N = in.readInt();
        int[][] blocks = new int[N][N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                blocks[i][j] = in.readInt();
        Board initial = new Board(blocks);

        // solve the puzzle
        Solver solver = new Solver(initial);

        // print solution to standard output
        if (!solver.isSolvable())
            StdOut.println("No solution possible");
        else {
            StdOut.println("Minimum number of moves = " + solver.moves());
            for (Board board : solver.solution())
                StdOut.println(board);
        }
    }
}