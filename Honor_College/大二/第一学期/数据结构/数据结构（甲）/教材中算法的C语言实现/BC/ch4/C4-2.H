 // c4-2.h 串的堆分配存储
 struct HString
 {
   char *ch; // 若是非空串,则按串长分配存储区,否则ch为NULL
   int length; // 串长度
 };