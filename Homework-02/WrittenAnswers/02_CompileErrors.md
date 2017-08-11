## Exercise 01
* **Search Term:**       : 'undefined reference'
* **URL with Solution:** :  http://stackoverflow.com/questions/8709942/meaning-of-undefined-reference-error
* **How to fix:**        : Give 'sayHello()' a function body, which is its definition.

---

## Exercise 02
* **Search Term:**       :  'use of undeclared identifier'
* **URL with Solution:** :  http://stackoverflow.com/questions/22197030/what-is-an-undeclared-identifier-error-and-how-do-i-fix-it
* **How to fix:**        :  Added a declaration for 'sayHello()' before main function.

---

## Exercise 03
* **Search Term:**       :  'uninitialized when used'
* **URL with Solution:** :  http://stackoverflow.com/questions/6813660/warning-uninitialized-variable-but-i-have-initialized-c-compiler-bug
* **How to fix:**        :  We initialized the variable x so that it had a value.

---

## Exercise 04
* **Search Term:**       :  'assignment as a condition'
* **URL with Solution:** :  http://stackoverflow.com/questions/17681535/variable-assignment-in-if-condition
* **How to fix:**        :  We changed the conditional 'if (x=5)' to 'if (x == 5)' so that we're comparing the values x and 5.

---

## Exercise 05
* **Search Term:**       :  'use of undeclared identifier'
* **URL with Solution:** :  http://stackoverflow.com/questions/6813660/warning-uninitialized-variable-but-i-have-initialized-c-compiler-bug
* **How to fix:**        :  Variable was declared and initialized, but the print statement calling for it was outside its scope (the for loop). We put the print line into the for loop.

---

## Exercise 06
* **Search Term:**       :  'comparison of integers of different signs'
* **URL with Solution:** :  http://stackoverflow.com/questions/31709250/error-when-comparing-integers-of-different-signs
* **How to fix:**        :  We shouldn't compare the different types 'int' and 'size_t' in the expression 'index < loopUpperLimit', so we changed the type of loopUpperLimit to 'int'.

---

## Exercise 07
* **Search Term:**       :  'invalid operands to binary expression'
* **URL with Solution:** :  http://stackoverflow.com/questions/20666044/error-invalid-operands-to-binary-expression
* **How to fix:**        :  We realized str (type string) was being compared to a char ('c'), as it had single quotation marks. We change it to double quotation marks.

---

## Exercise 08
* **Search Term:**       :  'unused parameter'
* **URL with Solution:** :  http://www.cplusplus.com/forum/general/43373/
* **How to fix:**        :  We saw input variable y wasn't used in the function body, so we changed the return value to x + y.

---

## Exercise 09
* **Search Term:**       :  'control may reach end of non-void function'
* **URL with Solution:** :  http://stackoverflow.com/questions/19104216/error-control-may-reach-end-of-non-void-function
* **How to fix:**        :  We noticed in the checkrange function you can reach no return value if the if statement in the functions results in being false. We therefore added a 'return false' after the body of the if statement.

---

## Exercise 10
* **Search Term:**       :  'use of undeclared identifier getter'
* **URL with Solution:** :  http://stackoverflow.com/questions/3793716/beginner-c-using-accessors-getters-to-pull-data-from-a-private-member-variab
* **How to fix:**        :  We realized the getter needs to be defined as a member function of a class by using the type and a double colon. We added 'Cow::' to the beginning of the name of 'getNumSpots'.
