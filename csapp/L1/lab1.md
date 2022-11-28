# 求异或
```
根据公式
x^y = ~x&y | ~y&x
int bitXor(int x, int y) {

  return ~x&y | ~y&x;
}
```
# 最小整数
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
# 判断奇数位是不是1
```
先取出奇数位的1,再判断思路同上
int allOddBits(int x) {
  return !(0xAAAAAAAA^(x&0xAAAAAAAA));
}
```
# 取负数
```
取反加一
int negate(int x) {
  return ~x + 0x1;
}
```