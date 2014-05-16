// auto generated by go tool dist
// goos=linux goarch=amd64


#include "runtime.h"
void
runtime·complex128div(Complex128 n, Complex128 d, Complex128 q)
{
	q.real = 0;
	q.imag = 0;
	FLUSH(&q);
#line 8 "/home/14/ren/source/golang/go/src/pkg/runtime/complex.goc"

	int32 ninf, dinf, nnan, dnan;
	float64 a, b, ratio, denom;

	// Special cases as in C99.
	ninf = n.real == runtime·posinf || n.real == runtime·neginf ||
	       n.imag == runtime·posinf || n.imag == runtime·neginf;
	dinf = d.real == runtime·posinf || d.real == runtime·neginf ||
	       d.imag == runtime·posinf || d.imag == runtime·neginf;

	nnan = !ninf && (ISNAN(n.real) || ISNAN(n.imag));
	dnan = !dinf && (ISNAN(d.real) || ISNAN(d.imag));

	if(nnan || dnan) {
		q.real = runtime·nan;
		q.imag = runtime·nan;
	} else if(ninf && !dinf) {
		q.real = runtime·posinf;
		q.imag = runtime·posinf;
	} else if(!ninf && dinf) {
		q.real = 0;
		q.imag = 0;
	} else if(d.real == 0 && d.imag == 0) {
		if(n.real == 0 && n.imag == 0) {
			q.real = runtime·nan;
			q.imag = runtime·nan;
		} else {
			q.real = runtime·posinf;
			q.imag = runtime·posinf;
		}
	} else {
		// Standard complex arithmetic, factored to avoid unnecessary overflow.
		a = d.real;
		if(a < 0)
			a = -a;
		b = d.imag;
		if(b < 0)
			b = -b;
		if(a <= b) {
			ratio = d.real/d.imag;
			denom = d.real*ratio + d.imag;
			q.real = (n.real*ratio + n.imag) / denom;
			q.imag = (n.imag*ratio - n.real) / denom;
		} else {
			ratio = d.imag/d.real;
			denom = d.imag*ratio + d.real;
			q.real = (n.imag*ratio + n.real) / denom;
			q.imag = (n.imag - n.real*ratio) / denom;
		}
	}
	FLUSH(&q);
}
