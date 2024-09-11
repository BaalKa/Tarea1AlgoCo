import random
import numpy as np

def random_generate(size):
    data = [random.randint(1, 10000) for _ in range(size)]
    
    with open("arreglos/random_generate.txt", "w") as file:
        for num in data:
            file.write(f"{num}\n")

def semiorder(size, percent):
    ordered_size = int(size * percent)
    messy_size = size - ordered_size

    ordered_list = [random.randint(1, 10000) for _ in range(ordered_size)]
    messy_list = [random.randint(1, 10000) for _ in range(messy_size)]
    semiorder_list = ordered_list + messy_list
    random.shuffle(semiorder_list)
    
    with open("arreglos/semiorder.txt", "w") as file:
        for num in semiorder_list:
            file.write(f"{num}\n")

def partially(size, percent):
    partially_list = [random.randint(1, 10000) for _ in range(size)]
    
    ordered_size = int(size * percent)
    partially_list[:ordered_size] = sorted(partially_list[:ordered_size])
    
    with open("arreglos/partially.txt", "w") as file:
        for num in partially_list:
            file.write(f"{num}\n")

def random_matrix(rows, columns):
    matrix = np.random.randint(1, 10000, (rows, columns))
    
    with open("matrices/random_matrix.txt", "w") as file:
        for row in matrix:
            file.write(" ".join(map(str, row)) + "\n")

# random_generate(300000)
# semiorder(300000, 0.65)
# partially(300000, 0.7)
# random_matrix(1000, 1000)           # cuadrada-1 y 2-(cúbica)
random_matrix(1000, 900)       # rectangular-3-(cúbica)
# random_matrix(800, 900)       # rectangular-4-(cúbica)
