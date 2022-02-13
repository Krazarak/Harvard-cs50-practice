from cs50 import get_int

# Get height from user
while True:
    height = get_int("Height(between 1 and 8):")
    if height > 0 and height < 9:
        break
# Print pyramid per users number
for row in range(height):
    for space in range(height - row - 1, 0, -1):
        print(" ", end="")
    for hash in range(row + 1):
        print("#", end="")
    print("  ", end="")
    for right_hash in range(row+1):
        print("#", end="")
    # New line
    print("\n", end="")