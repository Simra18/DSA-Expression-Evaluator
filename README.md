# Expression Evaluator Using Stack in C

This mini-project implements an **Expression Evaluator** in C as part of the **DSA (PBL) internal assessment**.  
It demonstrates infix, postfix, and prefix evaluation using stack data structures with operator precedence and associativity handling.

---

## Overview

An expression evaluator computes the result of arithmetic expressions like:

```
100 + 200 / 2 * 5 + 7
```

Since infix expressions cannot be directly evaluated due to operator precedence, this project converts and evaluates expressions using:

- **Stacks**  
- **Infix → Postfix conversion**
- **Prefix & Postfix evaluation algorithms**

---

## Features

- Infix Expression Evaluation  
- Postfix Expression Evaluation  
- Prefix Expression Evaluation  
- Multi-digit and negative number support  
- Operator precedence and associativity  
- Division, multiplication, subtraction, addition & exponent (`^`)  
- Error handling: invalid tokens, division by zero, stack overflow/underflow  

---

## Data Structures Used

### **1. Integer Stack**
Used to store:
- operands
- intermediate results
- postfix & prefix evaluation values

### **2. Operator Stack**
Used during:
- infix parsing
- precedence comparison
- handling parentheses

---

## Sample Output

<img width="1584" height="298" alt="image" src="https://github.com/user-attachments/assets/1d932efd-6758-4a4f-a188-8f10ced79a8e" />

---

## Conclusion

This project successfully demonstrates the implementation of expression evaluation using stacks in C.  
It highlights key concepts of:

- Parsing  
- Operator precedence  
- Stack-based evaluation  
- Algorithm design  

Future enhancements may include:
- Floating-point number support  
- Unary operators  
- Scientific functions  

---
