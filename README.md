# Karatsuba-Algorithm
 The Karatsuba algorithm is a fast multiplication algorithm that uses a divide and conquer approach to multiply two numbers. The naive algorithm for multiplying two numbers has a running time of O(n^^2) while this algorithm has a running time of O(n^^(1.585) Being able to multiply numbers quickly is very important. Computer scientists often consider multiplication to be a constant time O(1) operation, and this is a reasonable simplification for smaller numbers; but for larger numbers, the actual running times need to be factored in, which is O(n^^2). The point of the Karatsuba algorithm is to break large numbers down into smaller numbers so that any multiplications that occur happen on smaller numbers.
 
 If T(n) denotes the total number of elementary operations that the algorithm performs when multiplying two n-digit numbers, thenime Complexity of  Karatsuba-Algorithm is : 
 
 **T(n) = 3T(n/2) + c1n + c2**
 
 
 
 
