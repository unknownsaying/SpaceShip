#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// 简化的 RAM 结构
typedef struct {
    uint8_t* data;           // 内存数据数组
    uint32_t size;           // 内存大小（字节）
    uint32_t capacity;       // 总容量
    uint32_t read_count;     // 读取计数
    uint32_t write_count;    // 写入计数
    uint8_t memory_type;     // 内存类型
} RAM;

// 内存类型常量
#define RAM_TYPE_DRAM   0
#define RAM_TYPE_SRAM   1
#define RAM_TYPE_DDR3
#define RAM_TYPE_DDR4   2
#define RAM_TYPE_DDR5   3

// 创建 RAM
RAM* ram_create(uint32_t size_kb, uint8_t type) {
    RAM* ram = malloc(sizeof(RAM));
    ram->capacity = size_kb * 1024;
    ram->size = 0;
    ram->data = calloc(ram->capacity, sizeof(uint8_t));
    ram->read_count = 0;
    ram->write_count = 0;
    ram->memory_type = type;
    return ram;
}

// 销毁 RAM
void ram_destroy(RAM* ram) {
    if (ram) {
        free(ram->data);
        free(ram);
    }
}

// 读取内存
uint8_t ram_read(RAM* ram, uint32_t address) {
    if (address >= ram->capacity) {
        printf("内存读取错误: 地址越界\n");
        return 0;
    }
    ram->read_count++;
    return ram->data[address];
}

// 写入内存
void ram_write(RAM* ram, uint32_t address, uint8_t value) {
    if (address >= ram->capacity) {
        printf("内存写入错误: 地址越界\n");
        return;
    }
    ram->data[address] = value;
    ram->write_count++;
    ram->size = (address + 1 > ram->size) ? address + 1 : ram->size;
}

// 打印 RAM 状态
void ram_print_status(RAM* ram) {
    const char* type_str[] = {"DRAM", "SRAM", "DDR4", "DDR5"};
    printf("RAM 状态: %u KB %s | 读取: %u | 写入: %u | 使用率: %.1f%%\n",
           ram->capacity / 1024, type_str[ram->memory_type],
           ram->read_count, ram->write_count,
           (float)ram->size / ram->capacity * 100);
}

// 使用示例
int main() {
    // 创建 8KB DRAM
    RAM* my_ram = ram_create(8, RAM_TYPE_DRAM);
    
    // 写入测试数据
    ram_write(my_ram, 0x100, 0xAB);
    ram_write(my_ram, 0x101, 0xCD);
    
    // 读取数据
    uint8_t val1 = ram_read(my_ram, 0x100);
    uint8_t val2 = ram_read(my_ram, 0x101);
    
    printf("读取数据: 0x%02X 0x%02X\n", val1, val2);
    
    // 显示状态
    ram_print_status(my_ram);
    
    // 清理
    ram_destroy(my_ram);
    return 0;
}