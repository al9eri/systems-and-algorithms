# RADIX SORT IMPLEMENTATION (HW Q2)
# Sorts numbers digit by digit using Least Significant Digit (LSD) approach

def count_sort_digit(num_list, exp_val, base_val):
    # num_list: list of integers to sort
    # exp_val: current digit's place (1 for units, 10 for tens, etc.)
    # base_val: the base (e.g., 10 for decimal)

    size = len(num_list)
    sorted_list = [0] * size  # Output list to store sorted values
    freq = [0] * base_val     # Frequency count of digits (0 to base-1)

    # Step 1: Count occurrences of each digit at current position
    for idx in range(size):
        dig = (num_list[idx] // exp_val) % base_val
        freq[dig] += 1

    # Step 2: Turn count array into cumulative count (positions)
    for j in range(1, base_val):
        freq[j] += freq[j - 1]

    # Step 3: Build sorted list from the back to maintain stability
    for idx in range(size - 1, -1, -1):
        dig = (num_list[idx] // exp_val) % base_val
        freq[dig] -= 1
        sorted_list[freq[dig]] = num_list[idx]

    return sorted_list

def radix_sort_main(num_list, base_val):
    # Main Radix Sort loop: process digits from LSD to MSD

    if not num_list:
        return num_list

    max_val = max(num_list)  # Used to determine number of digits
    exp_val = 1
    passes = []  # Store each pass result for demonstration

    # While there are still digits to process
    while max_val // exp_val > 0:
        num_list = count_sort_digit(num_list, exp_val, base_val)
        passes.append(num_list.copy())
        exp_val *= base_val  # Move to next digit position

    return passes

if __name__ == '__main__':
    # Sample input for demo purposes
    base_val = 10
    nums = [170, 45, 75, 90, 802, 24, 2, 66]

    print("Input:", nums)
    sorted_passes = radix_sort_main(nums, base_val)

    print("\n--- Passes ---")
    for i, arr in enumerate(sorted_passes):
        print(f"Pass {i+1}:", arr)

    # Save passes to output.txt for submission format
    with open('output.txt', 'w') as out_file:
        for arr in sorted_passes:
            out_file.write(" ".join(str(x) for x in arr) + "\n")
    print("\nSorted passes saved to output.txt")