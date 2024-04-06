#!/usr/bin/python3
import sys


def factorial(number):
    result = 0
    for i in range(1, int(number ** 0.5) + 1):
        if number % i == 0:
            result = i
            break
    return result

if __name__ == "__main__":
    numbers = sys.stdin.readlines()
    for number in numbers:
        res = factorial(number)
        print("{} = {} * {}".format(number ,res, number / res))
