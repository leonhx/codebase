package stack

import (
	"testing"
)

func TestNew(t *testing.T) {
	s := New()
	if s.String() != "[]" {
		t.Logf("1: %v\n", s)
		t.Fail()
	}
}

func TestPush(t *testing.T) {
	s := New()
	s.Push(2)
	if s.String() != "[2]" || s.first.item != 2 {
		t.Logf("%v %v\n", s, s.first.item)
		t.Fail()
	}
	s.Push(3)
	if s.String() != "[3 2]" || s.first.item != 3 {
		t.Logf("%v %v\n", s, s.first.item)
		t.Fail()
	}
	s.Push(5)
	if s.String() != "[5 3 2]" || s.first.item != 5 {
		t.Logf("%v %v\n", s, s.first.item)
		t.Fail()
	}
	s.Push(7)
	if s.String() != "[7 5 3 2]" || s.first.item != 7 {
		t.Logf("%v %v\n", s, s.first.item)
		t.Fail()
	}
	s.Push(11)
	if s.String() != "[11 7 5 3 2]" || s.first.item != 11 {
		t.Logf("%v %v\n", s, s.first.item)
		t.Fail()
	}
}

func TestPop(t *testing.T) {
	s := New()
	s.Push(2)
	tmp := s.Pop()
	if s.String() != "[]" || tmp != 2 {
		t.Logf("%v %v %v\n", s, tmp, s.N)
		t.Fail()
	}
	s.Push(3)
	if s.String() != "[3]" {
		t.Logf("%v\n", s)
		t.Fail()
	}
	s.Push(5)
	tmp = s.Pop()
	if s.String() != "[3]" || tmp != 5 {
		t.Logf("%v %v %v\n", s, tmp, s.N)
		t.Fail()
	}
	s.Push(7)
	s.Push(11)
	if s.String() != "[11 7 3]" {
		t.Logf("%v\n", s)
		t.Fail()
	}
	tmp = s.Pop()
	if s.String() != "[7 3]" || tmp != 11 {
		t.Logf("%v %v %v\n", s, tmp, s.N)
		t.Fail()
	}
}
