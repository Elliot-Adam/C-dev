// Computers1.cpp : Defines the entry point for the console application.
//

#include "FunctionTester.h"
#include "ClassTester.h"
#include "LinkedListTester.h"

#include <stdio.h>
#include <malloc.h>


int GlobalThree = 3;

struct Person
{
    int age;
    char gender;    // M or F
};


int Add(int n1, int* n2)
{
    // n1 and n2 live on the stack of the caller
    printf("%s, n1=%d, %p, n2=%d, %p, GlobalThree=%d, %p\n", __FUNCTION__, n1, &n1, *n2, n2, GlobalThree , &GlobalThree);
    return n1 + *n2;
}

int Increment(int n)
{
    // n lives on the stack of the caller
    int one = 1; // one lives on the stack of Increment()
    printf("%s, n=%d, %p, one=%d, %p, GlobalThree=%d, %p\n", __FUNCTION__, n, &n, one, &one, GlobalThree , &GlobalThree);
    return Add(n, &one);
}


int GoodAdd(int n1, int n2)
{
    int sum = n1 + n2;
    return sum;
}

int* BuggyAdd(int n1, int n2)
{
    int sum = n1 + n2;
    return &sum;
}


int main()
{
    /*int two = 2; 	// two lives on the satck of main()
    int* addressOfThree = (int*)malloc(sizeof(int));	// p_three lives on the stack of main() and points into the heap
    *addressOfThree = GlobalThree;

    Person Persons[10];

    printf("%s, sizeof(char)=%zu, sizeof(short)=%zu, sizeof(int)=%zu, sizeof(long)=%zu, sizeof(long long)=%zu\n", __FUNCTION__, sizeof(char), sizeof(short), sizeof(int), sizeof(long), sizeof(long long));

    printf("%s, sizeof(Person)=%zu, sizeof(Persons)=%zu, countof(Persons)=%zu\n", __FUNCTION__, sizeof(Person), sizeof(Persons), sizeof(Persons)/ sizeof(Persons[0]));

    printf("%s, two=%d, %p, three=%d, %p, GlobalThree=%d, %p\n", __FUNCTION__, two, &two, *addressOfThree, addressOfThree, GlobalThree, &GlobalThree);

    int five = Add(two, addressOfThree);	// five and six live on the stack of main()
    int six = Increment(five);

    int* pEight = BuggyAdd(4, 4);
    int seven = GoodAdd(3, 4);
    printf("%s, *pEight=%d, %p, seven=%d\n", __FUNCTION__, *pEight, pEight, seven);

    free(addressOfThree);	    // clean the heap; this invalidates p_three
    addressOfThree = nullptr;   // clear out the invalid pointer

    FunctionTester functionTester;
    functionTester.Test();

    ClassTester classTester;
    classTester.Test();*/

    LinkedListTester linkedListTester;
    linkedListTester.Test();


}

