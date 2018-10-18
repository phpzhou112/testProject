package main

import (
	_ "fmt"
	_ "reflect"
)

const (
	MAXTABLE = 64
)

//存数据节点
type hashNode struct {
	key   interface{}
	value interface{}
	next  *hashNode
}

//hashtable结构体
type hashTable struct {
	tables [MAXTABLE]hashNode
}

//time33 hash函数
func hashTime33(s interface{}) uint {
	str := s.(string) //类型断言
	length := uint(len(str))
	var hash uint = 0
	var i uint = 0
	for i = 0; i < length; i++ {
		hash = ((hash << 5) + hash) + uint(str[i])
	}
	return hash

}

func (n *hashNode) addHashNode(key interface{}, value interface{}) {
	if n == nil {
		return
	}
	node := new(hashNode)
	node.key = key
	node.value = value
	node.next = n.next
	n.next = node
}

func (n *hashNode) getValue(key interface{}) interface{} {
	p := n.next
	for {
		if p == nil {
			break
		}
		if p.key == key {
			return p.value
		}
		p = p.next
	}
	return nil
}

//返回下标
func (h *hashTable) getIndex(key interface{}) uint {
	switch key.(type) {
	case int:
		keys := key.(int)
		key = string(keys)
		break
	case string:
		break
	default:
		panic("类型不是int和string")
		return 0
		break
	}
	hashNum := hashTime33(key)
	index := hashNum % MAXTABLE
	return index
}

//添加元素
func (h *hashTable) add(key interface{}, value interface{}) {
	index := h.getIndex(key)
	h.tables[index].addHashNode(key, value)
}

//取出元素
func (h *hashTable) get(key interface{}) interface{} {
	index := h.getIndex(key)
	return h.tables[index].getValue(key)
}
