//Circular Linked List
package cirllist

import (
	"fmt"
)

type node struct {
	item interface{}
	next *node
}

type Cirllist struct {
	head *node
	tail *node
	N    int
}

func New(item interface{}) *Cirllist {
	t := &node{item: item}
	t.next = t
	return &Cirllist{head: t, tail: t, N: 1}
}

func (c *Cirllist) Append(item interface{}) {
	t := &node{item: item, next: c.head}
	c.tail.next = t
	c.tail = t
	c.N++
}

type OutOfBoundError string

func (err OutOfBoundError) Error() string {
	return string(err)
}

//The index of the last node is 0;
//The index of the first node is 1
func (c *Cirllist) Remove(index int) (err error) {
	if 0 > index || index > c.N {
		return OutOfBoundError("Error: Out Of Bound")
	}
	if c.N == 1 {
		(*c) = Cirllist{}
		c.N = 0
		return
	}
	if index == 0 {
		index = c.N
	}
	n := c.head
	if index == 1 {
		c.head = n.next
		c.tail.next = c.head
		c.N--
		return
	}
	for i := 1; i < index-1; i, n = i+1, n.next {
	}
	n.next = n.next.next
	if index == c.N {
		c.tail = n
	}
	c.N--
	return
}

func (c *Cirllist) IsEmpty() bool {
	return c.N == 0
}

func (c *Cirllist) Size() int {
	return c.N
}

func (c *Cirllist) String() (str string) {
	if c.N == 0 {
		return "[]"
	}
	str += fmt.Sprint("[")
	n := c.head
	for ; n != c.tail; n = n.next {
		str += fmt.Sprintf("%v ", n.item)
	}
	str += fmt.Sprintf("%v]", n.item)
	return
}
