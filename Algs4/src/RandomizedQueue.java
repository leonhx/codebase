import java.util.Iterator;

public class RandomizedQueue<Item> implements Iterable<Item> {
    private Item[] items;
    private int N = 0;

    public RandomizedQueue() { // construct an empty randomized queues
        items = (Item[]) new Object[1];
    }

    private void resize(int size) {
        Item[] newItems = (Item[]) new Object[size];
        for (int i = 0; i < N; i++) {
            newItems[i] = items[i];
        }
        items = newItems;
    }

    public boolean isEmpty() { // is the queue empty?
        return N == 0;
    }

    public int size() { // return the number of items on the queue
        return N;
    }

    public void enqueue(Item item) { // add the item
        if (item == null) {
            throw new NullPointerException();
        }

        if (N == items.length) {
            resize(2 * items.length);
        }

        items[N++] = item;
    }

    private int randomIndex() {
        if (N > 0 && N == items.length / 4) {
            resize(items.length / 2);
        }

        return StdRandom.uniform(N);
    }

    public Item dequeue() { // delete and return a random item
        if (isEmpty()) {
            throw new java.util.NoSuchElementException();
        }

        int i = randomIndex();
        Item item = items[i];
        items[i] = items[--N];
        items[N] = null;

        return item;
    }

    public Item sample() { // return (but do not delete) a random item
        if (isEmpty()) {
            throw new java.util.NoSuchElementException();
        }

        int i = randomIndex();
        return items[i];
    }

    private class RandomIterator<T> implements Iterator<T> {
        private T[] items;
        private int index = 0;

        public RandomIterator(T[] items, int N) {
            this.items = (T[]) new Object[N];
            for (int i = 0; i < N; i++) {
                this.items[i] = items[i];
                int j = StdRandom.uniform(i + 1);
                if (j == i)
                    continue;
                T tmp = this.items[j];
                this.items[j] = this.items[i];
                this.items[i] = tmp;
            }
        }

        @Override
        public boolean hasNext() {
            return index != items.length;
        }

        @Override
        public T next() {
            if (!hasNext()) {
                throw new java.util.NoSuchElementException();
            }

            return this.items[index++];
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }

    }

    public Iterator<Item> iterator() {
        return new RandomIterator<Item>(items, N);
    }

    public static void main(String[] args) {
        RandomizedQueue<Integer> rq = new RandomizedQueue<Integer>();
        for (int i = 0; i < 128000; i++) {
            int c = 4;
            if (rq.isEmpty())
                c = 2;
            int r = StdRandom.uniform(c);
            try {
                switch (r) {
                case 0:
                    rq.enqueue(i);
                    break;
                case 1:
                    rq.size();
                    break;
                case 2:
                    rq.sample();
                    break;
                case 3:
                    rq.dequeue();
                    break;
                default:
                    break;
                }
            } catch (NullPointerException e) {
                System.out.println("======");
                System.out.println("======");
                throw e;
            } finally {
                System.out.println(r);
            }
        }
    }
}