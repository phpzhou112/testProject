package main

import (
	"fmt"
)

type Node struct {
	data int
	next *Node
}

func (n *Node) addData(data int) {
	if n == nil {
		return
	}
	node := new(Node)
	node.data = data
	node.next = n.next
	n.next = node
}
func (n *Node) traverse() {
	p := n.next
	for {
		if p == nil {
			break
		}
		fmt.Println(p.data)
		p = p.next
	}
}

type Stack struct {
	key  interface{}
	next *Stack
	tail *Stack
}

func (s *Stack) push(key interface{}) {
	node := new(Stack)
	node.next = s.next
	node.key = key
	s.next = node
	s.tail = s.next
}
func (s *Stack) pop() interface{} {
	key := s.tail.key
	s.next = s.tail.next
	s.tail = s.next
	return key
}

func testList() {
	var n Node
	n.addData(100)
	n.addData(200)
	n.addData(300)
	n.traverse()
}

func testStack() {
	var s Stack
	s.push(100)
	s.push(200)
	fmt.Println(s.pop())
	s.push(700)
	fmt.Println(s.pop())
	fmt.Println(s.pop())
}
