//
//  MyLinkedList.cpp
//  DateStructureProject
//
//  Created by Long Ly on 2020-04-15.
//  Copyright © 2020 Long Ly. All rights reserved.
//
#include<exception>
#include <iostream>
#include <string>
#include<vector>
#include "LinkedList.hpp"
#include <map>
#include <iterator>
using namespace std;

#pragma MyLLInvalidAccessException
class MyLLInvalidAccessException : public exception {
private:
    int code;
    string msg;
public:
    MyLLInvalidAccessException(int code){
        this->code = code;
        
        switch(code) {
            case 1:
                this->msg = "Invalid head() call: empty list";
                break;
            case 2:
                this->msg = "Invalid end() call: empty list";
                break;
            case 11:
                this->msg = "Invalid next() call: hasNext() false";
                break;
            case 12:
                this->msg = "Invalid previous() call: hasPrevious() false";
                break;
            case 13:
                this->msg = "Invalid set(T v) call: undefined current position";
                break;
            case 14:
                this->msg = "Invalid remove() call: undefined current position";
                break;
        }
    }
    
    int getCode() {
        return this->code;
    }
    
    string getMessage() {
        return this->msg;
    }
};

template <class T> class MyLinkedList;
template <class T> class MyLinkedListIterator;
template <class T> class Node;

template <class T> class Node {
private:
    T data;
    Node<T>* next;
    Node<T>* prev;
    
    Node(T v)
    {
        this->data = v;
        this->next = nullptr;
        this->prev = nullptr;
    }
    friend class MyLinkedList<T>;
    friend class MyLinkedListIterator<T>;
};

#pragma MyLinkedList
template <class T> class MyLinkedList {
    friend class MyLinkedListIterator<T>;
private:
    Node<T>* first;
    Node<T>* last;
public:
    MyLinkedList() {}
    
    MyLinkedList(T v) {
        Node<T>* node = new Node<T>(v);
        this->first = node;
        this->last = node;
    }
    
    MyLinkedList(T v[]) {
        this->first = nullptr;
        this->last = nullptr;
        
        for(int i = 0; i < sizeof(*v); i++) {
            if(sizeof(*v) == 1) {
                Node<T>* new_node = new Node<T>(v[i]);
                first = new_node;
                last = new_node;
                return;
            }
            
            if(first == nullptr) {
                Node<T>* new_node = new Node<T>(v[i]); // [first|new_node|last]
                
                Node<T>* next_new_node = new Node<T>(v[i+1]); // [first|next_new_node|last]
                
                first = new_node;
                first->next = next_new_node; // ->
                
                next_new_node->prev = first; // <-
                
                last = next_new_node; //
                
                i = 1;
            }
            else append(v[i]);
        }
    }
    
    vector<T> toVector() {
        vector<T> w;
        Node<T>* current = this->first;
        
        while(current != nullptr) {
            w.push_back(current->data);
            current = current->next;
        }
        return w;
    }
    
    void print(MyLinkedList<T> list) {
        Node<T>* first_node = list.first;
        while(first_node != nullptr) {
            cout << first_node->data << endl;
            first_node = first_node->next;
        }
    }
    
    MyLinkedList<T> copy()
    {
        MyLinkedList<T> result = *this;
        return result;
    }
    
    T head() {
        if(first == nullptr) {
            MyLLInvalidAccessException e(1);
            throw e;
        }
        return first->data;
    }
    
    MyLinkedList<T>* tail() {
        MyLinkedList<T>* result = new MyLinkedList<T>();
        
        if(last != nullptr) {
            Node<T> last_node = new Node<T>(last->data);
            
            result->first = last_node;
            result->last = last_node;
            //result->append(last->data);
        }
        return result;
    }
    
    T end() {
        if(first == nullptr && last == nullptr) {
            MyLLInvalidAccessException e(2);
            throw e;
        }
        
        while(last != nullptr && last->next != nullptr) {
            last = last->next;
        }
        return last->data;
    }
    
    void append(T e) {
        Node<T>* new_node = new Node<T>(e);
        if(last->next == nullptr) {
            Node<T>* second_last =  last;
            second_last->next = new_node;
            last = new_node;
            last->prev = second_last;
        }
    }
    
    void concat(MyLinkedList<T> lc) {
        Node<T>* head = lc.first;
        while(head != nullptr && head->next != nullptr)  {
            append(head->data);
            head = head->next;
        }
    }
    
    MyLinkedListIterator<T> iterator() {
        MyLinkedListIterator<T> it(*this);
        it.current = nullptr;
        it.itnext= first;
        return it;
    }
    
//    MyLinkedListIterator<T> iterator() {
//        return *new MyLinkedListIterator<T>(*this);
//    }
};
#pragma MyLinkedListIterator
template <class T> class MyLinkedListIterator {
    friend class MyLinkedList<T>;
private:
    Node<T>* itnext;
    Node<T>* current = nullptr;
    MyLinkedList<T>* ch;
public:
    MyLinkedListIterator<T>(MyLinkedList<T> &a) : ch(&a){};
//    MyLinkedListIterator<T>(MyLinkedList<T> &a) {
//        current = nullptr;
//        itnext = a.first;
//        ch = &a;
//    }
    void goToBegin() {
        while(current != nullptr && current->prev != nullptr) {
            cout << current->data << endl;
            current = current->prev;
        }
        //TO test it
        cout << current->data << endl;
    }
    
    void goToEnd() {
        while(current != nullptr && current->next != nullptr) {
            cout << current->data << endl;
            current = current->next;
        }
        //TO test it
        cout << current->data << endl;
    }
    
    
    bool hasNext() {
        if(itnext == nullptr) {
            MyLLInvalidAccessException e(11);
            throw e;
            return false;
        }
        return true;
    }

    T next() {
        if(hasNext())
        {
            current = itnext;
            itnext = itnext->next;
        }
            return current->data;
    }
    
    bool hasPrev() {
        if(current->prev == nullptr) {
            MyLLInvalidAccessException e(12);
            throw e;
            return false;
        }
        return true;
    }

    T previous() {
         if(hasPrev())
            current = current->prev;
        return current->data;
    }
    
    void set(T v) {
        Node<T>* node_data = new Node<T>(v);
        current->data = node_data->data;
    }
    
    void add(T v) {
        Node<T>* new_node = new Node<T>(v);
        
        if(current->prev != nullptr && current->next != nullptr) { // in the middle of the list
            Node<T>* prev_node = current->prev;
            new_node->next = prev_node->next;
            prev_node->next = new_node;
        }
        
        if(current->prev == nullptr) { // if first element
            Node<T>* second_node = current->next;
            current->next = new_node;
            new_node->next = second_node;
            new_node->prev = current;
        }
        
        if(current->next == nullptr)
            ch->append(v);
    }
    
    void remove() {
        if(current != nullptr) { //
            Node<T>* temp;
            if(current->prev != nullptr && current->next != nullptr) { // in the middle of the list
                temp = current->prev;
                temp->next = itnext;
                itnext->prev = temp;
                delete current;
            }
            
            if(current->prev == nullptr) { //if head
                ch->first = current->next;
                if(ch->first != nullptr)
                    ch->first->prev = nullptr;
                delete current;
                current = nullptr;
            }
            
            if(current->next == nullptr) { // if last element
                ch->last = current->prev;
                if(ch->last != nullptr)
                    ch->last->next = nullptr;
                delete current;
                current = nullptr;
            }
        }
        else {
            MyLLInvalidAccessException e(14);
            throw e;
        }
    }
};
