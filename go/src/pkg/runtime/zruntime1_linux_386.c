// auto generated by go tool dist
// goos=linux goarch=386


#include "runtime.h"
#include "arch_GOARCH.h"
#include "type.h"
void
runtime·GOMAXPROCS(intgo n, intgo ret)
{
	ret = 0;
	FLUSH(&ret);
#line 10 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	ret = runtime·gomaxprocsfunc(n);
	FLUSH(&ret);
}
void
runtime·NumCPU(intgo ret)
{
	ret = 0;
	FLUSH(&ret);
#line 14 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	ret = runtime·ncpu;
	FLUSH(&ret);
}
void
runtime·NumCgoCall(int64 ret)
{
	ret = 0;
	FLUSH(&ret);
#line 18 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	M *mp;

	ret = 0;
	for(mp=runtime·atomicloadp(&runtime·allm); mp; mp=mp->alllink)
		ret += mp->ncgocall;
	FLUSH(&ret);
}
void
runtime·newParFor(uint32 nthrmax, ParFor* desc)
{
	desc = 0;
	FLUSH(&desc);
#line 26 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	desc = runtime·parforalloc(nthrmax);
	FLUSH(&desc);
}
void
runtime·parForSetup(ParFor* desc, uint32 nthr, uint32 n, byte* ctx, bool wait, byte* body)
{
#line 30 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	runtime·parforsetup(desc, nthr, n, ctx, wait, *(void(**)(ParFor*, uint32))body);
}
void
runtime·parForDo(ParFor* desc)
{
#line 34 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	runtime·parfordo(desc);
}
void
runtime·parForIters(ParFor* desc, uintptr tid, uintptr start, uintptr end)
{
	start = 0;
	FLUSH(&start);
	end = 0;
	FLUSH(&end);
#line 38 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	runtime·parforiters(desc, tid, &start, &end);
	FLUSH(&start);
	FLUSH(&end);
}
void
runtime·gogoBytes(int32 x)
{
	x = 0;
	FLUSH(&x);
#line 42 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	x = RuntimeGogoBytes;
	FLUSH(&x);
}
void
runtime·typestring(Eface e, String s)
{
	s.str = 0;
	s.len = 0;
	FLUSH(&s);
#line 46 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	s = *e.type->string;
	FLUSH(&s);
}
void
runtime·golockedOSThread(bool ret)
{
	ret = 0;
	FLUSH(&ret);
#line 50 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	ret = runtime·lockedOSThread();
	FLUSH(&ret);
}
void
runtime·NumGoroutine(intgo ret)
{
	ret = 0;
	FLUSH(&ret);
#line 54 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	ret = runtime·gcount();
	FLUSH(&ret);
}
void
runtime·getgoroot(String out)
{
	out.str = 0;
	out.len = 0;
	FLUSH(&out);
#line 58 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	byte *p;

	p = runtime·getenv("GOROOT");
	out = runtime·gostringnocopy(p);
	FLUSH(&out);
}

#line 71 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"
void runtime·sigpanic ( void ) ; 
void
runtime·Caller(intgo skip, uintptr retpc, String retfile, intgo retline, bool retbool)
{
	retpc = 0;
	FLUSH(&retpc);
	retfile.str = 0;
	retfile.len = 0;
	FLUSH(&retfile);
	retline = 0;
	FLUSH(&retline);
	retbool = 0;
	FLUSH(&retbool);
#line 73 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	Func *f, *g;
	uintptr pc;
	uintptr rpc[2];

	/*
	 * Ask for two PCs: the one we were asked for
	 * and what it called, so that we can see if it
	 * "called" sigpanic.
	 */
	retpc = 0;
	if(runtime·callers(1+skip-1, rpc, 2) < 2) {
		retfile = runtime·emptystring;
		retline = 0;
		retbool = false;
	} else if((f = runtime·findfunc(rpc[1])) == nil) {
		retfile = runtime·emptystring;
		retline = 0;
		retbool = true;  // have retpc at least
	} else {
		retpc = rpc[1];
		pc = retpc;
		g = runtime·findfunc(rpc[0]);
		if(pc > f->entry && (g == nil || g->entry != (uintptr)runtime·sigpanic))
			pc--;
		retline = runtime·funcline(f, pc, &retfile);
		retbool = true;
	}
	FLUSH(&retpc);
	FLUSH(&retfile);
	FLUSH(&retline);
	FLUSH(&retbool);
}
void
runtime·Callers(intgo skip, Slice pc, intgo retn)
{
	retn = 0;
	FLUSH(&retn);
#line 103 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	// runtime.callers uses pc.array==nil as a signal
	// to print a stack trace.  Pick off 0-length pc here
	// so that we don't let a nil pc slice get to it.
	if(pc.len == 0)
		retn = 0;
	else
		retn = runtime·callers(skip, (uintptr*)pc.array, pc.len);
	FLUSH(&retn);
}
void
runtime∕pprof·runtime_cyclesPerSecond(int64 res)
{
	res = 0;
	FLUSH(&res);
#line 113 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	res = runtime·tickspersecond();
	FLUSH(&res);
}
void
sync·runtime_procPin(intgo p)
{
	p = 0;
	FLUSH(&p);
#line 117 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	M *mp;

	mp = m;
	// Disable preemption.
	mp->locks++;
	p = mp->p->id;
	FLUSH(&p);
}
void
sync·runtime_procUnpin()
{
#line 126 "/home/14/ren/source/golang/go/src/pkg/runtime/runtime1.goc"

	m->locks--;
}
