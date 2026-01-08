"""
File: compare_js.py
Author: Simon Lartey
Date: 10/19/2025

Description:
Python version of code demonstrating syntax, scoping, and function behavior.
This script mirrors the JavaScript examples to explicitly compare the two languages.
"""

# ---------------------------
# 1️⃣ Variable Declaration
# ---------------------------
x = 42          # Python infers type dynamically
y = "hello"
z = [1, 2, 3]

print("Python Variable Types:")
print("x =", x, "type:", type(x))
print("y =", y, "type:", type(y))
print("z =", z, "type:", type(z))
print()


# ---------------------------
# 2️⃣ Scoping Rules (LEGB)
# ---------------------------
global_var = "global"

def outer_function():
    outer_var = "outer"

    def inner_function():
        inner_var = "inner"
        print(f"Accessing {global_var} from global scope")
        print(f"Accessing {outer_var} from enclosing scope")
        print(f"Accessing {inner_var} from local scope")
    
    inner_function()

outer_function()
print()


# ---------------------------
# 3️⃣ Control Flow
# ---------------------------
n = 5
if n > 10:
    print("n is greater than 10")
elif n == 5:
    print("n is exactly 5")
else:
    print("n is less than 10")
print()

for i in range(3):
    print(f"for loop count: {i}")
print()

while n > 0:
    print(f"while loop count: {n}")
    n -= 1
print()


# ---------------------------
# 4️⃣ Function as First-Class Object
# ---------------------------
def greet(name):
    return f"Hello, {name}!"

# Assign function to variable
welcome = greet
print(welcome("Simon"))

# Pass function as argument
def execute(func, arg):
    print("Executing passed function...")
    print(func(arg))

execute(greet, "Joyce")

# Return function from function
def multiplier(factor):
    def multiply(n):
        return n * factor
    return multiply

double = multiplier(2)
print("Double of 10 is:", double(10))
print()


# ---------------------------
# 5️⃣ Built-in Types and Operators
# ---------------------------
a, b = 10, 3
print(f"Addition: {a + b}")
print(f"Subtraction: {a - b}")
print(f"Multiplication: {a * b}")
print(f"Division: {a / b}")
print(f"Modulus: {a % b}")
print(f"Exponentiation: {a ** b}")
print()
