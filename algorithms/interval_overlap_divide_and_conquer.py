# OVERLAP ANALYSIS BETWEEN INTERVALS (Project Q3)
# Includes Brute Force and Divide & Conquer approaches

def digit_sort_intervals(intervals, pos, radix):
    # Sort intervals by the 'start' value using radix digit sort
    size = len(intervals)
    sorted_intervals = [0] * size
    freq = [0] * radix

    # Count digits at current digit position
    for i in range(size):
        start_val = intervals[i][0]
        digit_val = (start_val // pos) % radix
        freq[digit_val] += 1

    # Convert to cumulative count
    for i in range(1, radix):
        freq[i] += freq[i - 1]

    # Place elements in sorted order (stable sort)
    for i in range(size - 1, -1, -1):
        start_val = intervals[i][0]
        digit_val = (start_val // pos) % radix
        sorted_intervals[freq[digit_val] - 1] = intervals[i]
        freq[digit_val] -= 1

    return sorted_intervals

def radix_sort_intervals(intervals, radix):
    # Full LSD Radix Sort on intervals by start year
    if not intervals:
        return intervals

    max_start = max(item[0] for item in intervals)  # Find largest start year
    pos = 1

    # Keep sorting for each digit place
    while max_start // pos > 0:
        intervals = digit_sort_intervals(intervals, pos, radix)
        pos *= radix

    return intervals

def bf_overlap(intervals):
    # Brute force check all pairs of intervals
    best_overlap = 0
    best_pair = ()
    total = len(intervals)

    for i in range(total):
        for j in range(i + 1, total):
            s1, e1 = intervals[i]
            s2, e2 = intervals[j]

            # Calculate overlap
            current = max(0, min(e1, e2) - max(s1, s2))

            # Update best if current is larger
            if current > best_overlap:
                best_overlap = current
                best_pair = (i, j)

    return best_pair, best_overlap

def dc_overlap(intervals):
    # Divide and conquer to find max overlap more efficiently
    count = len(intervals)

    if count <= 1:
        return 0, ()

    if count == 2:
        s1, e1 = intervals[0]
        s2, e2 = intervals[1]
        curr = max(0, min(e1, e2) - max(s1, s2))
        return curr, (0, 1)

    mid = count // 2
    left_side = intervals[:mid]
    right_side = intervals[mid:]

    # Recursively get best from left and right halves
    left_val, left_pair = dc_overlap(left_side)
    right_val, right_pair = dc_overlap(right_side)

    # Find max 'end' in left to check crossing overlaps
    left_max_end = max(pair[1] for pair in left_side)

    cross_val = 0
    cross_pair = ()

    # Sort right side by start year to find overlap with left
    right_sorted = sorted(right_side, key=lambda x: x[0])
    for idx in range(len(right_sorted)):
        sR, eR = right_sorted[idx]

        if sR > left_max_end:
            break  # No more possible overlaps

        current = min(left_max_end, eR) - sR
        if current > cross_val:
            cross_val = current
            cross_pair = (mid - 1, mid + idx)

    # Return the best overlap
    overall = max(left_val, right_val, cross_val)
    if overall == left_val:
        return left_val, left_pair
    elif overall == right_val:
        return right_val, right_pair
    else:
        return cross_val, cross_pair

# ====== TEST BLOCK FOR DEMO PURPOSES =======
if __name__ == '__main__':
    # Sample intervals: (birth, death)
    intervals = [(1850, 1900), (1880, 1930), (1910, 1960)]
    base = 10

    print("Original Intervals:", intervals)

    # Brute Force Method
    print("\n--- Brute Force ---")
    bf = bf_overlap(intervals)
    print("Best Pair:", bf[0], "Overlap:", bf[1])

    # Divide & Conquer Method (with radix sort)
    print("\n--- Divide & Conquer ---")
    sorted_intervals = radix_sort_intervals(intervals, base)
    dc = dc_overlap(sorted_intervals)
    print("Sorted by Birth Year:", sorted_intervals)
    print("Best Pair:", dc[1], "Overlap:", dc[0])
