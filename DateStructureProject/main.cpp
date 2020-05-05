//
//  main.cpp
//  DateStructureProject
//
//  Created by Long Ly on 2020-04-15.
//  Copyright © 2020 Long Ly. All rights reserved.
//

#include <iostream>
#include <vector>
#include "LinkedList.cpp"
using namespace std;

int main(int argc, const char * argv[]) {
    int temp[] = {1, 2, 3, 4};
    MyLinkedList<int> myList(temp);
    MyLinkedListIterator<int> it = myList.iterator();
    
    int value1 = myList.head();
    
    cout << "Head: " << value1 << endl;
    cout << "Origin List: " << endl;
    myList.print(myList);
    value1 = myList.end();
    cout << "Taill: " << value1 << endl;
    
    cout << "Cloned List: " << endl;
    MyLinkedList<int> clone = myList.copy();
    
    clone.print(clone);
    int temp2[] = {5, 6, 7};
    MyLinkedList<int> myList2(temp2);

    cout << "Concat List: " << endl;
    myList.concat(myList2);
    myList.print(myList);
    
    int value = it.next();
    cout << "Next node: " << value << endl;
    value = it.next();
    cout << "Next node: " << value << endl;
    value = it.previous();
    cout << "Previous node: " << value << endl;
    value = it.previous();
    
    try {
        cout << "Previous = " << it.previous() << endl;
        cout << " and I continue here" << endl;
    }
    catch (MyLLInvalidAccessException e) {
        cout << "Exception code = " << e.getCode() << endl;
        cout << e.getMessage() << endl;
    }

    it.add(10);
    cout << "List after added 10: " << endl;
    myList.print(myList);
    value = it.next();
    cout << "Next node: " << value << endl;
    it.remove();
    cout << "List after remove: " << endl;
    myList.print(myList);
    cout << "Go to the begin: " << endl;
    it.goToBegin();
    cout << "Go to the end: " << endl;
    it.goToEnd();
    cout << "Set new value: " << endl;
    it.set(100);
    myList.print(myList);
    return 0;
}
