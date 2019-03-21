#include <iostream>
#include "Node.cpp"
#include "LinkedList.cpp"
using namespace std;

int main()
{
    int i;
    LinkedList<int> test;

    for(i = 0; i < 10; i++){
        test.insert(i + 1,  i + 1);
    }

    for(i = 0; i < test.getLength(); i++){
        cout << test.getEntry(i + 1) << " ";
    }
    cout << endl;
    
    if(test.isEmpty()){
        cout << "List is empty" << endl;
    }
    else{
        cout << "List is not empty" << endl;
    }

    cout << "List length is " << test.getLength() << endl;

    test.remove(5);

    for(i = 0; i < test.getLength(); i++){
        cout << test.getEntry(i + 1) << " ";
    }
    cout << endl;

    test.remove(5);

    for(i = 0; i < test.getLength(); i++){
        cout << test.getEntry(i + 1) << " ";
    }
    cout << endl;

    if(test.isEmpty()){
        cout << "List is empty" << endl;
    }
    else{
        cout << "List is not empty" << endl;
    }

    cout << "List length is " << test.getLength() << endl;

    test.replace(1, 9);

    for(i = 0; i < test.getLength(); i++){
        cout << test.getEntry(i + 1) << " ";
    }
    cout << endl;

    test.clear();

    cout << "List length is " << test.getLength() << endl;

    if(test.isEmpty()){
        cout << "List is empty" << endl;
    }
    else{
        cout << "List is not empty" << endl;
    }

    return 0; 
}
