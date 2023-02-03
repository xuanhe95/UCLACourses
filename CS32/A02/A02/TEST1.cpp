#include "Set.h"
#include <type_traits>

#define CHECKTYPE(c, f, r, a)  \
        {  \
         static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
             "You did not declare " #c "::" #f " as the Project 2 spec does");  \
         auto p = static_cast<r (c::*)a>(&c::f);  \
         (void) p;  \
        }
#define CHECKTYPENONMEMBER(f, r, a)  \
        {  \
         static_assert(std::is_same<decltype(&f), r (*)a>::value, \
             "You did not declare " #f " as the Project 2 spec does");  \
         auto p = static_cast<r (*)a>(f);  \
         (void) p;  \
        }

static_assert(std::is_default_constructible<Set>::value,
	"Set must be default-constructible.");
static_assert(std::is_copy_constructible<Set>::value,
	"Set must be copy-constructible.");
static_assert(std::is_copy_assignable<Set>::value,
	"Set must be assignable.");

void thisFunctionWillNeverBeCalled()
{
	CHECKTYPE(Set, empty, bool, () const);
	CHECKTYPE(Set, size, int, () const);
	CHECKTYPE(Set, insert, bool, (const ItemType&));
	CHECKTYPE(Set, erase, bool, (const ItemType&));
	CHECKTYPE(Set, contains, bool, (const ItemType&) const);
	CHECKTYPE(Set, get, bool, (int, ItemType&) const);
	CHECKTYPE(Set, swap, void, (Set&));
	CHECKTYPENONMEMBER(unite, void, (const Set&, const Set&, Set&));
	CHECKTYPENONMEMBER(butNot, void, (const Set&, const Set&, Set&));
}

int main()
{}