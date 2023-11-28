def prime_factors(n):
    i = 2
    factors = []
    while i * i <= n:
        if n % i:
            i += 1
        else:
            n //= i
            factors.append(i)
    if n > 1:
        factors.append(n)
    return factors


# print(prime_factors(5562737))
# print(prime_factors(8782)) 

print(prime_factors(28380))
print(prime_factors(9451520)) 