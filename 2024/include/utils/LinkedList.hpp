#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <cstddef>
#include <spdlog/spdlog.h>
#include <stdexcept>

namespace AOCUtil {

// unsafe class will not care if you push, pop and insert past its limits
template<class T>
struct Node {
    Node* prev = nullptr;
    Node* next = nullptr;

    T data;

    Node(T data) : data(data) {}
    Node operator=(T data) {
        this->data = data;
        return this;
    }
};

template<class T>
class LinkedList {
private:
    size_t _size;
    Node<T>* _start = nullptr;
    Node<T>* _end = nullptr;

    Node<T>* getAt(size_t idx) {
        if(idx >= _size) {
            throw std::range_error("INDEX EXCEEDS SIZE\n");
        }

        Node<T>* node;

        // go from nearest end(either start or end)(NOT TESTED)
        if(idx > (_size / 2)) {
            node = _end;

            for(size_t i = _size - 1; i != idx; i--) {
                node = node->prev;
            }
        }
        else {
            node = _start;

            for(size_t i = 0; i != idx; i++) {
                node = node->next;
            }
        }

        return node;
    }

public:
    LinkedList() : _size(0) {}
    ~LinkedList() {}

    Node<T>* start() const { return _start; }
    Node<T>* back() const { return _end; }

    void push_back(T data) {
        Node<T>* newNode = new Node<T>(data);

        switch(_size++) {
        case 0:
            _start = newNode;
            break;
        default:
            newNode->prev = _end;
            _end->next = newNode;
            break;
        }

        _end = newNode;
    }
    
    void push_front(T data) {
        Node<T>* newNode = new Node<T>(data);
            
        switch(_size++) {
        case 0:
            _end = newNode;
            break;
        default:
            newNode->next = _start;
            _start->prev = newNode;
            break;
        }

        _start = newNode;
    } 

    void insert(size_t idx, T data) {
        if(idx == 0) {
            push_front(data);
            return;
        }
        else if(idx == _size) {
            push_back(data);
            return;
        }
        else if(idx > _size) {
            throw std::range_error("INDEX EXCEEDS SIZE\n");
        }

        Node<T>* newNode = new Node<T>(data);
        Node<T>* prevNode = this->getAt(idx - 1);
        Node<T>* nextNode = prevNode->next;

        if(prevNode->next != nullptr) {
            newNode->next = nextNode;
            nextNode->prev = newNode;
        }
        
        newNode->prev = prevNode;
        prevNode->next = newNode;

        _size++;
    }

    T pop_back() {
        if(_size == 0) {
            throw std::range_error("BACK: NO VALUE TO POP\n");
        }
        
        Node<T>* node = _end;
        T data = node->data;
        
        if(_size-- != 1) {
            _end = node->prev;
            _end->next = nullptr;
        } 
        else {
            _end = nullptr;
            _start = nullptr;
        }

        if(node) {
            delete node;
        }

        return data;
    }

    T pop_front() {
        if(_size == 0) {
            throw std::range_error("FRONT: NO VALUE TO POP\n");
        }
        
        Node<T>* node = _start;
        T data = node->data;
        
        if(_size-- != 1) {
            _start = node->next;
            _start->prev = nullptr;
        } 
        else {
            _end = nullptr;
            _start = nullptr;
        }

        if(node) {
            delete node;
        }

        return data;
    }

    size_t size() { return _size; }
    T& operator[](size_t idx) {
        return this->getAt(idx)->data;
    }
};

};

#endif