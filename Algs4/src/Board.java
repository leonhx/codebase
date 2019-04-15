import java.util.Iterator;

public class Board {
    private int[][] board;

    public Board(int[][] blocks) {
        final int N = blocks.length;
        board = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                board[i][j] = blocks[i][j];
            }
        }
    }

    public int dimension() {
        return board.length;
    }

    public int hamming() {
        int dist = 0;
        final int N = dimension();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                final int block = board[i][j];
                if (block != 0 && block != i * N + j + 1)
                    dist++;
            }
        }
        return dist;
    }

    public int manhattan() {
        int dist = 0;
        final int N = dimension();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                final int block = board[i][j];
                if (block == 0)
                    continue;
                final int I = (block - 1) / N;
                final int J = (block - 1) % N;
                dist += Math.abs(I - i) + Math.abs(J - j);
            }
        }
        return dist;
    }

    public boolean isGoal() {
        return hamming() == 0;
    }

    public Board twin() {
        final int N = dimension();
        final Board that = copy();

        int I = 0;
        for (int j = 0; j < N; j++) {
            if (that.board[I][j] == 0) {
                I++;
                break;
            }
        }
        final int J = 0;
        that.board[I][J] = this.board[I][J + 1];
        that.board[I][J + 1] = this.board[I][J];

        return that;
    }

    public boolean equals(Object y) {
        if (y == this)
            return true;

        if (y == null)
            return false;

        if (y.getClass() != this.getClass())
            return false;

        Board that = (Board) y;
        final int N = this.dimension();

        if (N != that.dimension())
            return false;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (this.board[i][j] != that.board[i][j])
                    return false;
            }
        }

        return true;
    }

    private Board copy() {
        final int N = dimension();
        int[][] anotherBoard = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                anotherBoard[i][j] = this.board[i][j];
            }
        }
        return new Board(anotherBoard);
    }

    public Iterable<Board> neighbors() {
        final Stack<Board> boards = new Stack<Board>();
        final int N = dimension();
        boolean foundWhite = false;
        int i = 0, j = 0;
        while (!foundWhite && i < N) {
            if (this.board[i][j] == 0) {
                foundWhite = true;
            }
            if (foundWhite)
                break;
            else {
                i += (j + 1) / N;
                j = (j + 1) % N;
            }
        }

        if (i > 0) {
            final Board that = copy();
            that.board[i][j] = that.board[i - 1][j];
            that.board[i - 1][j] = 0;
            boards.push(that);
        }

        if (i != N - 1) {
            final Board that = copy();
            that.board[i][j] = that.board[i + 1][j];
            that.board[i + 1][j] = 0;
            boards.push(that);
        }

        if (j != 0) {
            final Board that = copy();
            that.board[i][j] = that.board[i][j - 1];
            that.board[i][j - 1] = 0;
            boards.push(that);
        }

        if (j != N - 1) {
            final Board that = copy();
            that.board[i][j] = that.board[i][j + 1];
            that.board[i][j + 1] = 0;
            boards.push(that);
        }

        return new Iterable<Board>() {
            @Override
            public Iterator<Board> iterator() {
                return boards.iterator();
            }
        };
    }

    public String toString() {
        final int N = dimension();
        final int max = N * N - 1;
        final String formatter;
        if (max < 10) {
            formatter = "%3d";
        } else if (max < 100) {
            formatter = "%4d";
        } else if (max < 1000) {
            formatter = "%5d";
        } else if (max < 10000) {
            formatter = "%6d";
        } else if (max < 100000) {
            formatter = "%7d";
        } else {
            formatter = " %d ";
        }

        final StringBuilder sb = new StringBuilder();
        sb.append(N);
        sb.append('\n');

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                sb.append(String.format(formatter, board[i][j]));
            }
            sb.append('\n');
        }

        return sb.toString();
    }

    public static void main(String[] args) {
        In in = new In(args[0]);
        int N = in.readInt();
        int[][] blocks = new int[N][N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                blocks[i][j] = in.readInt();
        Board initial = new Board(blocks);

        for (Board neighbor : initial.neighbors()) {
            System.out.println(neighbor);
        }
    }
}