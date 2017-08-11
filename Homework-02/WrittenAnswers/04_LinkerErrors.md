# Question 1 

**Answer**: We didn't compile lineshuffler and random into .o files before linking with shuffle.cpp.

---

# Question 2

**Answer**: clang++ -std=c++11 -pedantic -Wall -Wextra -c lineshuffler.cpp
            clang++ -std=c++11 -pedantic -Wall -Wextra -c random.cpp  
            clang++ -std=c++11 -pedantic -Wall -Wextra -o program shuffle.cpp random.o lineshuffler.o 
            
---

# Question 3

**Answer**: clang++ -std=c++11 -pedantic -Wall -Wextra -c lineshuffler.cpp
            clang++ -std=c++11 -pedantic -Wall -Wextra -o program shuffle.cpp random.o lineshuffler.o 

---

# Question 4

**Answer**: clang++ -std=c++11 -pedantic -Wall -Wextra -o program shuffle.cpp random.o lineshuffler.o 

