# Code Snippet 1

**Code**:`Cow& mabel = bessie;`

**Translation**: Mabel is a reference to a Cow that refers to bessie.

**Type**: We know that `bessie` must... be a Cow.

---

# Code Snippet 2

**Code**: `bessie* findFriend(const Monkey& george)`

**Translation**: findFriend is a function that takes a const reference to a Monkey, george, that returns a pointer to an object or class type named bessie.

**Type**: We know that `bessie` must... be a custom type like a structure or a class and not a variable.

---

# Code Snippet 3

**Code**: `Cow** mabel = bessie;`

**Translation**: Mabel is a pointer to a pointer to a Cow that points to bessie.

**Type**: We know that `bessie` must... be a pointer to a Cow.

---

# Code Snippet 4

**Code**: `Cow*** mabel = *bessie`

**Translation**: Mabel is a pointer to a pointer to a pointer to a Cow that points to the value bessie points to.

**Type**: We know that `bessie` must... be a pointer to a pointer to a pointer to a Cow.

---

# Code Snippet 5

**Code**: ` Cow& mabel = *bessie;`

**Translation**: Mabel is a reference to a cow that refers to the value bessie points to.

**Type**: We know that `bessie` must... be a pointer to a Cow.

---

# Code Snippet 6

**Code**: `Cow* & mabel = *bessie;`

**Translation**: Mabel is a reference to a pointer to a Cow that points to the value bessie points to.

**Type**: We know that `bessie` must... be a pointer to a pointer to a Cow.

---

# Code Snippet 7

**Code**: `delete bessie;`

**Translation**: Destroy and deallocate the object pointed to by bessie.

**Type**: We know that `bessie` must... be a pointer. (probably to a cow)

---

# Code Snippet 8

**Code**: `delete[] bessie;`

**Translation**: Destroy and deallocate the array of object pointed to by bessie.

**Type**: We know that `bessie` must... be a pointer to an array. (probably of Cows)

---

# Code Snippet 9

**Code**: `delete[] *bessie;`

**Translation**: Destroy and deallocate the array of object pointed to by the value of the pointer that bessie points to.

**Type**: We know that `bessie` must... be a pointer to a pointer to an array.

---

# Code Snippet 10

**Code**: `delete bessie[3];`

**Translation**: Destroy and deallocate the object pointed to by the value of the object 3 to the right of where bessie points.

**Type**: We know that `bessie` must... be an array of pointers

