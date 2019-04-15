import java.util.Iterator;

public class Deque<Item> implements Iterable<Item> {
    private class Node<T> {
        private T item;

        private Node<T> prev;
        private Node<T> next;

        public Node(T item, Node<T> prev, Node<T> next) {
            this.item = item;
            this.prev = prev;
            this.next = next;
        }
    }

    private Node<Item> head = null;
    private Node<Item> tail = null;
    private int N = 0;

    public Deque() { // construct an empty deque
    }

    public boolean isEmpty() { // is the deque empty?
        return N == 0;
    }

    public int size() { // return the number of items on the deque
        return N;
    }

    public void addFirst(Item item) { // insert the item at the front
        if (item == null) {
            throw new NullPointerException();
        }

        Node<Item> n = new Node<Item>(item, null, head);
        N++;
        if (head != null) {
            head.prev = n;
        }
        head = n;
        if (N == 1) {
            tail = head;
        }
    }

    public void addLast(Item item) { // insert the item at the end
        if (item == null) {
            throw new NullPointerException();
        }

        Node<Item> n = new Node<Item>(item, tail, null);
        N++;
        if (tail != null) {
            tail.next = n;
        }
        tail = n;
        if (N == 1) {
            head = tail;
        }
    }

    public Item removeFirst() { // delete and return the item at the front
        if (isEmpty()) {
            throw new java.util.NoSuchElementException();
        }

        Item item = head.item;
        head = head.next;
        N--;
        if (head != null) {
            head.prev = null;
        }
        if (N <= 1) {
            tail = head;
        }

        return item;
    }

    public Item removeLast() { // delete and return the item at the end
        if (isEmpty()) {
            throw new java.util.NoSuchElementException();
        }

        Item item = tail.item;
        tail = tail.prev;
        N--;
        if (tail != null) {
            tail.next = null;
        }
        if (N <= 1) {
            head = tail;
        }

        return item;
    }

    private class DequeIterator<T> implements Iterator<T> {
        private Node<T> self;

        public DequeIterator(Node<T> head) {
            self = head;
        }

        @Override
        public boolean hasNext() {
            return self != null;
        }

        @Override
        public T next() {
            if (!hasNext())
                throw new java.util.NoSuchElementException();
            T item = self.item;
            self = self.next;
            return item;
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    public Iterator<Item> iterator() {
        return new DequeIterator<Item>(head);
    }

    public static void main(String[] args) {
        Deque<Integer> deque = new Deque<Integer>();
        for (int i = 0; i < 1024; i++) {
            int c = 4;
            if (deque.isEmpty())
                c = 2;
            int r = StdRandom.uniform(c);
            try {
                switch (r) {
                case 0:
                    deque.addFirst(i);
                    break;
                case 1:
                    deque.addLast(i);
                    break;
                case 2:
                    deque.removeFirst();
                    break;
                case 3:
                    deque.removeLast();
                    break;
                default:
                    break;
                }
            } catch (NullPointerException e) {
                System.out.println("======");
                System.out.println(deque.head);
                System.out.println(deque.tail);
                System.out.println(deque.size());
                System.out.println(deque.isEmpty());
                System.out.println("======");
                throw e;
            } finally {
                System.out.println(r);
            }
        }
    }
}
