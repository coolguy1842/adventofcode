#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

// unsafe class will not care if you push, pop and insert past its limits
template<class T>
class linkedList {
public:
    struct part {
        struct part* prev = nullptr;
        T data;
        struct part* next = nullptr;

        part(T data) : data(data) {}

        operator=(T data) {
            this->data = data;

            return this;
        }
    };

private:
    size_t __size;
    struct part* __start = nullptr;
    struct part* __end = nullptr;

    struct part* getAt(size_t idx) {
        if(idx >= __size) {
            throw std::range_error("INDEX: INDEX EXCEEDS SIZE\n");
        }

        struct part* part;

        // go from nearest end(either start or end)(NOT TESTED)
        if(idx > (this->__size / 2)) {
            part = this->__end;

            for(size_t i = 0; i < idx; i++) {
                part = part->prev;
            }
        }
        else {
            part = this->__start;

            for(size_t i = 0; i < idx; i++) {
                part = part->next;
            }
        }

        return part;
    }

public:
    linkedList() : __size(0) {}
    ~linkedList() {}

    struct part* begin() const { return this->__start; }
    struct part* end() const { return this->__end; }

    void push_back(T data) {
        struct part* newPart = new part(data);

        switch (__size++) {
        case 0:
            this->__start = newPart;
            break;
        default:
            newPart->prev = this->__end;
            this->__end->next = newPart;
            break;
        }

        this->__end = newPart;
    } 
    
    void push_front(T data) {
        struct part* newPart = new part(data);
            
        switch(__size++) {
        case 0:
            this->__end = newPart;
            break;
        default:
            newPart->next = this->__start;
            this->__start->prev = newPart;
            break;
        }

        this->__start = newPart;
    } 

    // broken function do not use
    void insert(size_t idx, T data) {
        if(idx == 0) {
            push_front(data);
            return;
        }
        else if(idx == __size) {
            push_back(data);

            return;
        }

        struct part* newPart = new part(data);

        struct part* prevPartPtr = this->getAt(idx);
        if(prevPartPtr->next != nullptr) {
            struct part* nextPartPtr = prevPartPtr->next;

            newPart->next = nextPartPtr;
            nextPartPtr->prev = newPart;
        }
        
        newPart->prev = prevPartPtr;
        prevPartPtr->next = newPart;
        
    }

    T pop_back() {
        if(__size == 0) {
            throw std::range_error("POP_BACK: NO VALUE TO POP\n");
        }
        
        struct part* part = this->__end;
        T data = part->data;
        
        if(__size-- != 1) {
            this->__end = part->prev;
            this->__end->next = nullptr;
        } 
        else {
            this->__end = nullptr;
            this->__start = nullptr;
        }

        delete part;
        return data;
    }

    T pop_front() {
        if(__size == 0) {
            throw std::range_error("POP_FRONT: NO VALUE TO POP\n");
        }
        
        struct part* part = this->__start;
        T data = part->data;
        
        if(__size-- != 1) {
            this->__start = part->next;
            this->__start->prev = nullptr;
        } 
        else {
            this->__end = nullptr;
            this->__start = nullptr;
        }

        delete part;
        return data;
    }

    size_t size() { return this->__size; }

    T &operator[](size_t idx) {
        return this->getAt(idx)->data;
    }
};

#endif