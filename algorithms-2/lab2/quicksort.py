import time
import tracemalloc
from random import uniform

recursion_calls = 0
max_recursion_depth = 0
merge_operations = 0

def merge_sort(nums, depth=0):
    global recursion_calls, max_recursion_depth, merge_operations
    
    recursion_calls += 1
    max_recursion_depth = max(max_recursion_depth, depth)
    
    if len(nums) <= 1:
        return nums
    
    mid = len(nums) // 2
    left = merge_sort(nums[:mid], depth + 1)
    right = merge_sort(nums[mid:], depth + 1)
    
    return merge(left, right)

def merge(left, right):
    global merge_operations
    
    sorted_list = []
    i = j = 0
    
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            sorted_list.append(left[i])
            i += 1
        else:
            sorted_list.append(right[j])
            j += 1
        merge_operations += 1
    
    sorted_list.extend(left[i:])
    sorted_list.extend(right[j:])
    merge_operations += len(left) - i + len(right) - j
    
    return sorted_list

if __name__ == "__main__":
    dimensions = [1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000]

    for dimension in dimensions:
        for approach in range(20):
            nums = [uniform(-1, 1) for _ in range(dimension)]

            # Сброс счетчиков
            recursion_calls = 0
            max_recursion_depth = 0
            merge_operations = 0

            # Замер памяти до сортировки
            tracemalloc.start()
            before_memory = tracemalloc.get_traced_memory()[1]  # Пик до начала

            # Замер времени
            start_time = time.time()
            sorted_nums = merge_sort(nums)
            end_time = time.time()
            execution_time = end_time - start_time

            # Замер памяти после сортировки
            after_memory = tracemalloc.get_traced_memory()[1]  # Пик после завершения
            tracemalloc.stop()

            additional_memory = after_memory - before_memory

            # Запись результатов в файл
            with open("results.txt", "a", encoding='UTF-8') as file:
                file.write(
                    f"Размерность: {dimension} "
                    f"Время: {execution_time:.6f} "
                    f"Количество вызовов рекурсии: {recursion_calls} "
                    f"Глубина рекурсии: {max_recursion_depth} "
                    f"Количество операций слияния: {merge_operations} "
                    f"Доп. память: {additional_memory} байт\n"
                )
