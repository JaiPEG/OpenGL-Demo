#ifndef BITS_H221
#define BITS_H221

typedef int BOOL;

#ifndef TRUE
#define TRUE 1
#endif // TRUE

#ifndef FALSE
#define FALSE 0
#endif // FALSE

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

BOOL isNeg(int i);
BOOL isPos(int i);
BOOL isOppSigns(int a, int b);
//int abs(int i);
//int min(int a, int b);
//int max(int a, int b);
BOOL isPow2(unsigned int i);
unsigned int log2(unsigned int i);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BITS_H221