#include <iostream>
#include <string>
#include <cstdlib>
#include <exception>
#include "BagInterface.h"
#include "LinkedBag.cpp"
#include "ArrayBag.cpp"



using namespace std;




// Updated this method to take any kind of 'bag'
template<class ItemType>
void displayBag(BagInterface<ItemType>& bag, string name)
{
    cout << name << " contains " << bag.getCurrentSize()
    << " items:" << endl;
    vector<ItemType> bagItems = bag.toVector();

    int numberOfEntries = (int) bagItems.size();
    for (int i = 0; i < numberOfEntries; i++)
    {
        cout << bagItems[i] << " ";
    }  // end for
    cout << endl << endl;
}  // end displayBag

// This method will fill a bag<int> with a specified number of elements.
void intFill(BagInterface<int>& bag, int numItems)
{
    int i;
    for (i = 0; i < numItems; i++)
    {
        bag.add(rand()%6 +1);
    }
}

// This method will fill a bag<string> with a specified number of elements.
void stringFill(BagInterface<string>& bag, int numItems)
{
    string items[] = {"one", "two", "three", "four", "five", "one",
                      "foo", "bar", "baz", "qux", "alpha", "omega"};
    int i;
    for (i = 0; i < numItems; i++)
    {
        bag.add(items[rand()%12]);
    }
}

// This method will remove the first element from a bag
template<class ItemType>
void dropFirst(BagInterface<ItemType>& bag)
{
    vector<ItemType> bagItems = bag.toVector();
    bag.remove(bagItems[0]);
}

void bagTester(BagInterface<string>& bag1, BagInterface<string>& bag2,
               BagInterface<string>& bag3, BagInterface<string>& bag4,
               BagInterface<int>& intBag)
{
    // create test bag pointers to return into
    BagInterface<string>* testBag1;
    BagInterface<string>* testBag2;
    BagInterface<string>* testBag3;
    BagInterface<string>* testBag4;

    // fill them up with some data, and display so we know the initial state
    stringFill(bag1, 3);
    displayBag(bag1 , "bag1");
    stringFill(bag2, 3);
    displayBag(bag2 , "bag2");
    stringFill(bag3, 6);
    displayBag(bag3 , "bag3");
    stringFill(bag4, 6);
    displayBag(bag4 , "bag4");
    intFill(intBag, 6);
    displayBag(intBag, "intBag (just to show ints)");

    bool again;

    // initial simple tests
    cout << "Simple Union test of bag1 and bag2:" << endl;
    testBag1 = bag1.Union(bag2);
    displayBag(*testBag1, "testBag1");

    cout << endl << "Intersection test of bag3 and bag4:" << endl;
    testBag2 = bag3.intersection(bag4);
    displayBag(*testBag2, "testBag2");

    cout << endl << "Difference test of bag3 and bag4:" <<endl;
    testBag3 = bag3.difference(bag4);
    displayBag(*testBag3, "testBag3");

    do
    {
        again = false;
        try
        {
            cout << endl << "Union exception test of bag1 and bag4:" <<endl;
            testBag4 = bag1.Union(bag4);
            displayBag(*testBag4, "testBag4");
        }
        catch (length_error err)
        {
            cout << "Caught error: " << err.what() << " Reducing size of bag4." << endl;
            dropFirst(bag4);
            displayBag(bag4, "Bag4 after drop");
            again = true;
        }
    }
    while (again)
        ;

    // clean up
    delete testBag1;
    delete testBag2;
    delete testBag3;
    delete testBag4;
    testBag1 = NULL;
    testBag2 = NULL;
    testBag3 = NULL;
    testBag4 = NULL;

}  // end bagTester


int main()
{
    BagInterface<string>*  bag1   = NULL;
    BagInterface<string>*  bag2   = NULL;
    BagInterface<string>*  bag3   = NULL;
    BagInterface<string>*  bag4   = NULL;
    BagInterface<int>*     intBag = NULL;

    srand (time(NULL));

    cout << endl << "################# HW Array Bag TESTS ###################"
    << endl << endl;
    bag1 =   new ArrayBag<string>();
    bag2 =   new ArrayBag<string>();
    bag3 =   new ArrayBag<string>();
    bag4 =   new ArrayBag<string>();
    intBag = new ArrayBag<int>();
    bagTester(*bag1, *bag2, *bag3, *bag4, *intBag);

    delete bag1;
    delete bag2;
    delete bag3;
    delete bag4;
    delete intBag;
    bag1   = NULL;
    bag2   = NULL;
    bag3   = NULL;
    bag4   = NULL;
    intBag = NULL;
    cout << endl << "################# END Array Bag TESTS ##################"
    << endl << endl;

    cout << endl << "################# HW Linked Bag TESTS ###################"
    << endl << endl;
    bag1 =   new LinkedBag<string>();
    bag2 =   new LinkedBag<string>();
    bag3 =   new LinkedBag<string>();
    bag4 =   new LinkedBag<string>();
    intBag = new LinkedBag<int>();
    bagTester(*bag1, *bag2, *bag3, *bag4, *intBag);

    delete bag1;
    delete bag2;
    delete bag3;
    delete bag4;
    delete intBag;
    bag1   = NULL;
    bag2   = NULL;
    bag3   = NULL;
    bag4   = NULL;
    intBag = NULL;
    cout << endl << "################# END Linked Bag TESTS ##################"
    << endl << endl;
    return 0;
}  // end main

