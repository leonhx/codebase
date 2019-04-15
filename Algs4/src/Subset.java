public class Subset {

    public static void main(String[] args) {
        int k = Integer.parseInt(args[0]);

        RandomizedQueue<String> rq = new RandomizedQueue<String>();
        int m = 0;
        while (!StdIn.isEmpty()) {
            String str = StdIn.readString();
            m++;
            if (m > k) {
                if (StdRandom.uniform(m) < k) {
                    rq.dequeue();
                } else {
                    continue;
                }
            }
            rq.enqueue(str);
        }

        for (int i = 0; i < k; i++) {
            StdOut.println(rq.dequeue());
        }
    }

}
