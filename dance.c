#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    SHIFT_SIZE = 3,
    ARRAY_SIZE = 12,
    count = 4,
    G1 = 255
};

unsigned char LED_Data[ARRAY_SIZE] = {};
void shiftArrayRight(uint8_t *array, unsigned int size, unsigned int shift) // 右移数组函数
{
    if (shift >= size)
    {
        shift %= size; // 处理移动位数大于数组大小的情况
    }
    uint8_t temp[shift];
    memcpy(temp, array + size - shift, shift * sizeof(uint8_t));     // 复制末尾的shift个元素到临时数组
    memmove(array + shift, array, (size - shift) * sizeof(uint8_t)); // 将剩余元素向右移动shift位
    memcpy(array, temp, shift * sizeof(uint8_t));                    // 将临时数组中的元素复制回数组开头
}

void shiftArrayLeft(uint8_t *array, unsigned int size, unsigned int shift) // 左移数组函数
{
    if (shift >= size)
    {
        shift %= size; // 处理移动位数大于数组大小的情况
    }
    uint8_t temp[shift];
    memcpy(temp, array, shift * sizeof(uint8_t));                    // sizeof(uint8_t) 1个字的大小// 从array复制shift个元素到临时数组
    memmove(array, array + shift, (size - shift) * sizeof(uint8_t)); // 将剩余元素向左移动shift位，当原地址和目标地址重叠时，使用memmove而不是memcpy
    memcpy(array + size - shift, temp, shift * sizeof(uint8_t));     // 将临时数组中的元素复制回数组末尾，当原地址和目标地址不重叠时，使用memcpy而不是memmove
}

int main()
{

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        LED_Data[i] = i * 40; // 给每个元素赋一个值
    }

    for (int i = 0; i < count; i++)
    {

        // 先右移3位
        shiftArrayRight(LED_Data, ARRAY_SIZE, 3);
        printf("\n");
        for (int i = 0; i < ARRAY_SIZE; ++i)
        {
            printf("%d ", LED_Data[i]);
        }
    }
    for (int i = 0; i < count; i++)
    { // 再左移3位（或任意位数，这里为了展示效果仍使用3位）
        shiftArrayLeft(LED_Data, ARRAY_SIZE, 3);
        printf(":\n");
        for (int i = 0; i < ARRAY_SIZE; ++i)
        {
            printf("%d ", LED_Data[i]);
        }
    }
    return 0;
}
