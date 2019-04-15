package binarytree

import (
	"testing"
)

func TestPreOrder(t *testing.T) {
	d := New("D", nil, nil)
	g := New("G", nil, nil)
	h := New("H", nil, nil)
	i := New("I", nil, nil)
	e := New("E", nil, g)
	f := New("F", h, i)
	b := New("B", d, nil)
	c := New("C", e, f)
	a := New("A", b, c)
	if a.PreOrder() != "ABDCEGFHI" {
		t.Log(a.PreOrder())
		t.Fail()
	}
}

func TestInOrder(t *testing.T) {
	d := New("D", nil, nil)
	g := New("G", nil, nil)
	h := New("H", nil, nil)
	i := New("I", nil, nil)
	e := New("E", nil, g)
	f := New("F", h, i)
	b := New("B", d, nil)
	c := New("C", e, f)
	a := New("A", b, c)
	if a.InOrder() != "DBAEGCHFI" {
		t.Log(a.InOrder())
		t.Fail()
	}
}

func TestPostOrder(t *testing.T) {
	d := New("D", nil, nil)
	g := New("G", nil, nil)
	h := New("H", nil, nil)
	i := New("I", nil, nil)
	e := New("E", nil, g)
	f := New("F", h, i)
	b := New("B", d, nil)
	c := New("C", e, f)
	a := New("A", b, c)
	if a.PostOrder() != "DBGEHIFCA" {
		t.Log(a.PostOrder())
		t.Fail()
	}
}
