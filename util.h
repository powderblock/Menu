#ifndef	TGJ_UTIL_INC
#define	TGJ_UTIL_INC

extern float worldsize;
extern int width, height;
extern float aspect;

void quit(int);
void mouse(float*, float*);

//Clamp a value to a range
//Inside the header because inline functions need to be
inline int clamp(int x, int a, int b) {
    if (x > b) return b;
    else if (x < a) return a;
    else return x;
}
inline float clamp(float x, float a, float b) {
	if (x > b) return b;
	else if (x < a) return a;
	return x;
}

#endif
