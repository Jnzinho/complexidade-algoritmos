def max_crossing_sum(arr, left, mid, right):
    # Soma máxima do lado esquerdo
    left_sum = float('-inf')
    total = 0
    for i in range(mid, left - 1, -1):
        total += arr[i]
        left_sum = max(left_sum, total)

    # Soma máxima do lado direito
    right_sum = float('-inf')
    total = 0
    for i in range(mid + 1, right + 1):
        total += arr[i]
        right_sum = max(right_sum, total)

    return left_sum + right_sum


def max_subarray_dc_util(arr, left, right):
    if left == right:
        return arr[left]

    mid = (left + right) // 2

    left_result = max_subarray_dc_util(arr, left, mid)
    right_result = max_subarray_dc_util(arr, mid + 1, right)
    cross_result = max_crossing_sum(arr, left, mid, right)

    return max(left_result, right_result, cross_result)


def max_subarray_dc(arr):
    return max_subarray_dc_util(arr, 0, len(arr) - 1)


arr = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
resultado = max_subarray_dc(arr)
print("Resultado:", resultado)
