// auto generated by go tool dist
// goos=linux goarch=386


#include "runtime.h"
#include "arch_GOARCH.h"
#include "malloc.h"
#include "stack.h"
void
runtime∕debug·setMaxStack(intgo in, intgo out)
{
	out = 0;
	FLUSH(&out);
#line 11 "/home/14/ren/source/golang/go/src/pkg/runtime/rdebug.goc"

	out = runtime·maxstacksize;
	runtime·maxstacksize = in;
	FLUSH(&out);
}
void
runtime∕debug·setGCPercent(intgo in, intgo out)
{
	out = 0;
	FLUSH(&out);
#line 16 "/home/14/ren/source/golang/go/src/pkg/runtime/rdebug.goc"

	out = runtime·setgcpercent(in);
	FLUSH(&out);
}
void
runtime∕debug·setMaxThreads(intgo in, intgo out)
{
	out = 0;
	FLUSH(&out);
#line 20 "/home/14/ren/source/golang/go/src/pkg/runtime/rdebug.goc"

	out = runtime·setmaxthreads(in);
	FLUSH(&out);
}
void
runtime∕debug·SetPanicOnFault(bool enabled, uint8, uint16, bool old)
{
	old = 0;
	FLUSH(&old);
#line 24 "/home/14/ren/source/golang/go/src/pkg/runtime/rdebug.goc"

	old = g->paniconfault;
	g->paniconfault = enabled;
	FLUSH(&old);
}
