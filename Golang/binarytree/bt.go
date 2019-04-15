package binarytree

import (
	"fmt"
)

type node struct {
	element interface{}
}

type BinaryTree struct {
	root  *node
	left  *BinaryTree
	right *BinaryTree
}

/*
 * `root`: root element. NOT A NODE OR A TREE!
 * `left`: the left subtree of this binary tree
 * `right`: the right subtree of this binary tree
 */
func New(root interface{}, left, right *BinaryTree) *BinaryTree {
	return &BinaryTree{
		root:  &node{element: root},
		left:  left,
		right: right,
	}
}

//Get the preorder string of the nodes in the binary tree.
//Note: No whitespace between elements
func (b *BinaryTree) PreOrder() (preorder string) {
	if b != nil {
		preorder += fmt.Sprintf("%v", b.root.element)
		preorder += b.left.PreOrder()
		preorder += b.right.PreOrder()
	}
	return
}

//Get the inorder string of the nodes in the binary tree.
//Note: No whitespace between elements
func (b *BinaryTree) InOrder() (inorder string) {
	if b != nil {
		inorder += b.left.InOrder()
		inorder += fmt.Sprintf("%v", b.root.element)
		inorder += b.right.InOrder()
	}
	return
}

//Get the postorder string of the nodes in the binary tree.
//Note: No whitespace between elements
func (b *BinaryTree) PostOrder() (postorder string) {
	if b != nil {
		postorder += b.left.PostOrder()
		postorder += b.right.PostOrder()
		postorder += fmt.Sprintf("%v", b.root.element)
	}
	return
}
