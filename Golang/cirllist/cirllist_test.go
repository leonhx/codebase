package cirllist

import (
	"testing"
)

func TestString(t *testing.T) {
	node1 := &node{item: 5}
	node2 := &node{item: 4}
	node3 := &node{item: 3}
	node4 := &node{item: 2}
	node5 := &node{item: 1}
	node1.next = node2
	node2.next = node3
	node3.next = node4
	node4.next = node5
	node5.next = node1
	c := &Cirllist{head: node1, tail: node5, N: 5}
	if c.String() != "[5 4 3 2 1]" {
		t.Log(c.String())
		t.Fail()
	}
}

func initial(n int) *Cirllist {
	c := New(1)
	for i := 2; i <= n; i++ {
		c.Append(i)
	}
	return c
}

func TestRemove(t *testing.T) {
	c := initial(5)
	c.Remove(1)
	if c.String() != "[2 3 4 5]" {
		t.Logf("%v\n", c)
		t.Fail()
	}
	if c.head.item != 2 {
		t.Log("head")
		t.Fail()
	}
	if c.tail.item != 5 {
		t.Log("tail")
		t.Fail()
	}
}
