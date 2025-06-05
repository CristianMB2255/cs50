from cs50 import get_float

# Get input
change = 0
while change <= 0:
    change = get_float("Change: ")

# Loop until change becomes 0
coins = 0
while change > 0:
    
    # Round to avoid floating point imprecision
    change = round(change, 2)

    # Calculate the quarters
    if (change >= 0.25):
        change -= 0.25
        coins += 1
        continue

    # Calculate the dimes
    if (change >= 0.1):
        change -= 0.1
        coins += 1
        continue

    # Calculate the nickels
    if (change >= 0.05):
        change -= 0.05
        coins += 1
        continue

    # Calculate the penies
    if (change >= 0.01):
        change -= 0.01
        coins += 1
        continue

# Print result
print(coins)
