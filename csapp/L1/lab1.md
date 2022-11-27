# 第一题求异或
```
根据公式
x^y = ~x&y | ~y&x
int bitXor(int x, int y) {

  return ~x&y | ~y&x;
}
```
# 第二题最小整数
```
0x10000...
int tmin(void) {
  return 0x1 << 31;
}
```
# 判断一个数是不是最大
```
int isTmax(int x) {
  return !(~(0x1 << 31) ^ x);
}
```