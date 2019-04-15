package stack

import (
	"fmt"
)

type node struct {
	item string
	next *node
}

type Stack struct {
	first *node
	N     int
}

func New() *Stack {
	return &Stack{}
}

func (s *Stack) Push(i string) {
	t := &node{item: i, next: s.first}
	*s = Stack{first: t, N: s.N + 1}
}

func (s *Stack) Pop() string {
	i := s.first.item
	s.first = s.first.next
	s.N--
	return i
}

func (s *Stack) Peek() string {
	return s.first.item
}

func (s *Stack) IsEmpty() bool {
	return s.first == nil
}

func (s *Stack) Size() int {
	return s.N
}

func (s *Stack) String() (str string) {
	if s.N == 0 {
		return "[]"
	}
	str += fmt.Sprint("[")
	c := s.first
	for ; c.next != nil; c = c.next {
		str += fmt.Sprintf("%v ", c.item)
	}
	str += fmt.Sprintf("%v]", c.item)
	return
}
