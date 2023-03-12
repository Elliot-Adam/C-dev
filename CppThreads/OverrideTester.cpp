#include <stdio.h>	// printf
#include <memory>	// shared_ptr

#include "OverrideTester.h"

class Base
{
	int data = 10;

public:
	int Execute()
	{
		return data + 1;
	}
};

class Derived : public Base
{
	int data = 20;

public:
	int Execute()
	{
		return data + 1;
	}
};

class VirtualBase
{
	int data = 50;

public:
	virtual int Execute()
	{
		return data + 1;
	}
};

class VirtualDerived : public VirtualBase
{
	int data = 60;

public:
	virtual int Execute()	// Overrides VirtualBase::Execute()
	{
		return data + 1;
	}
};


#pragma region ThreadsTester
void OverrideTester::Test()
{
	Base b;
	Derived d;			// Derived also includes Base

	VirtualBase vb;
	VirtualDerived vd;	// VirtualDerived also includes VirtualBase

	printf("%s, sizeof(Base)=%zu, sizeof(Derived)=%zu, sizeof(VirtualBase)=%zu, sizeof(VirtualDerived)=%zu\n", 
		__FUNCTION__, sizeof(Base), sizeof(Derived), sizeof(VirtualBase), sizeof(VirtualDerived));

	printf("%s, b.Execute()=%d, d.Execute()=%d, vb.Execute()=%d, vd.Execute()=%d\n",
		__FUNCTION__, b.Execute(), d.Execute(), vb.Execute(), vd.Execute());

	Base*			pb = &b;		// pointer to Base
	Derived*		pd = &d;		// pointer to Derived
	Base*			pbd = &d;		// pointer to the base of the Derived

	printf("%s, pb->Execute()=%d, pd->Execute()=%d, pbd->Execute()=%d\n",
		__FUNCTION__, pb->Execute(), pd->Execute(), pbd->Execute());


	VirtualBase*	pvb = &vb;		// pointer to Base		
	VirtualDerived* pvd = &vd;		// pointer to Derived
	VirtualBase*	pbvd = &vd;		// pointer to the base of the VirtualDerived


	printf("%s, pvb->Execute()=%d, pvd->Execute()=%d, pbvd->Execute()=%d\n",
		__FUNCTION__, pvb->Execute(), pvd->Execute(), pbvd->Execute());

	printf("%s, pb=%p, pd=%p, pbd=%p\n", __FUNCTION__, pb, pd, pbd);
	printf("%s, pvb=%p, pvd=%p, pbvd=%p\n", __FUNCTION__, pvb, pvd, pbvd);

}
#pragma endregion ThreadsTester

