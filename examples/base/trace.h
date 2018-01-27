int magic_trace(char *filename, char *file, char *function, int line, char *format, ...);
int stack_trace(char *filename);
int force_trace(char *filename, const char *p, int n);
#define MT(...) magic_trace( "magic.trace", __FILE__, (char*)__FUNCTION__, __LINE__, __VA_ARGS__ )
#define ST() stack_trace("stack.trace")
#define FT(p,n) force_trace("force.trace",(p),(n))
