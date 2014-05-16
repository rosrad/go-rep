// auto generated by go tool dist
// goos=freebsd goarch=386


#include "runtime.h"
#include "arch_GOARCH.h"
#include "malloc.h"
#include "defs_GOOS_GOARCH.h"
#include "type.h"

#line 16 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
static Lock proflock; 
#line 21 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
enum { MProf , BProf } ; 
#line 25 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
struct Bucket 
{ 
Bucket *next; 
Bucket *allnext; 
int32 typ; 
#line 32 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
union 
{ 
struct 
{ 
#line 48 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
uintptr allocs; 
uintptr frees; 
uintptr alloc_bytes; 
uintptr free_bytes; 
#line 53 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
uintptr prev_allocs; 
uintptr prev_frees; 
uintptr prev_alloc_bytes; 
uintptr prev_free_bytes; 
#line 58 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
uintptr recent_allocs; 
uintptr recent_frees; 
uintptr recent_alloc_bytes; 
uintptr recent_free_bytes; 
#line 63 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
} ; 
struct 
{ 
int64 count; 
int64 cycles; 
} ; 
} ; 
uintptr hash; 
uintptr size; 
uintptr nstk; 
uintptr stk[1]; 
} ; 
enum { 
BuckHashSize = 179999 , 
} ; 
static Bucket **buckhash; 
static Bucket *mbuckets; 
static Bucket *bbuckets; 
static uintptr bucketmem; 
#line 84 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
static Bucket* 
stkbucket ( int32 typ , uintptr size , uintptr *stk , int32 nstk , bool alloc ) 
{ 
int32 i; 
uintptr h; 
Bucket *b; 
#line 91 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
if ( buckhash == nil ) { 
buckhash = runtime·SysAlloc ( BuckHashSize*sizeof buckhash[0] , &mstats.buckhash_sys ) ; 
if ( buckhash == nil ) 
runtime·throw ( "runtime: cannot allocate memory" ) ; 
} 
#line 98 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
h = 0; 
for ( i=0; i<nstk; i++ ) { 
h += stk[i]; 
h += h<<10; 
h ^= h>>6; 
} 
#line 105 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
h += size; 
h += h<<10; 
h ^= h>>6; 
#line 109 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
h += h<<3; 
h ^= h>>11; 
#line 112 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
i = h%BuckHashSize; 
for ( b = buckhash[i]; b; b=b->next ) 
if ( b->typ == typ && b->hash == h && b->size == size && b->nstk == nstk && 
runtime·mcmp ( ( byte* ) b->stk , ( byte* ) stk , nstk*sizeof stk[0] ) == 0 ) 
return b; 
#line 118 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
if ( !alloc ) 
return nil; 
#line 121 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
b = runtime·persistentalloc ( sizeof *b + nstk*sizeof stk[0] , 0 , &mstats.buckhash_sys ) ; 
bucketmem += sizeof *b + nstk*sizeof stk[0]; 
runtime·memmove ( b->stk , stk , nstk*sizeof stk[0] ) ; 
b->typ = typ; 
b->hash = h; 
b->size = size; 
b->nstk = nstk; 
b->next = buckhash[i]; 
buckhash[i] = b; 
if ( typ == MProf ) { 
b->allnext = mbuckets; 
mbuckets = b; 
} else { 
b->allnext = bbuckets; 
bbuckets = b; 
} 
return b; 
} 
#line 140 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
static void 
MProf_GC ( void ) 
{ 
Bucket *b; 
#line 145 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
for ( b=mbuckets; b; b=b->allnext ) { 
b->allocs += b->prev_allocs; 
b->frees += b->prev_frees; 
b->alloc_bytes += b->prev_alloc_bytes; 
b->free_bytes += b->prev_free_bytes; 
#line 151 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
b->prev_allocs = b->recent_allocs; 
b->prev_frees = b->recent_frees; 
b->prev_alloc_bytes = b->recent_alloc_bytes; 
b->prev_free_bytes = b->recent_free_bytes; 
#line 156 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
b->recent_allocs = 0; 
b->recent_frees = 0; 
b->recent_alloc_bytes = 0; 
b->recent_free_bytes = 0; 
} 
} 
#line 164 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
void 
runtime·MProf_GC ( void ) 
{ 
runtime·lock ( &proflock ) ; 
MProf_GC ( ) ; 
runtime·unlock ( &proflock ) ; 
} 
#line 173 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
void 
runtime·MProf_Malloc ( void *p , uintptr size ) 
{ 
uintptr stk[32]; 
Bucket *b; 
int32 nstk; 
#line 180 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
nstk = runtime·callers ( 1 , stk , nelem ( stk ) ) ; 
runtime·lock ( &proflock ) ; 
b = stkbucket ( MProf , size , stk , nstk , true ) ; 
b->recent_allocs++; 
b->recent_alloc_bytes += size; 
runtime·unlock ( &proflock ) ; 
#line 191 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
runtime·setprofilebucket ( p , b ) ; 
} 
#line 195 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
void 
runtime·MProf_Free ( Bucket *b , uintptr size , bool freed ) 
{ 
runtime·lock ( &proflock ) ; 
if ( freed ) { 
b->recent_frees++; 
b->recent_free_bytes += size; 
} else { 
b->prev_frees++; 
b->prev_free_bytes += size; 
} 
runtime·unlock ( &proflock ) ; 
} 
#line 209 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
int64 runtime·blockprofilerate; 
#line 211 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
void 
runtime·SetBlockProfileRate ( intgo rate ) 
{ 
int64 r; 
#line 216 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
if ( rate <= 0 ) 
r = 0; 
else { 
#line 220 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
r = ( float64 ) rate*runtime·tickspersecond ( ) / ( 1000*1000*1000 ) ; 
if ( r == 0 ) 
r = 1; 
} 
runtime·atomicstore64 ( ( uint64* ) &runtime·blockprofilerate , r ) ; 
} 
#line 227 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
void 
runtime·blockevent ( int64 cycles , int32 skip ) 
{ 
int32 nstk; 
int64 rate; 
uintptr stk[32]; 
Bucket *b; 
#line 235 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
if ( cycles <= 0 ) 
return; 
rate = runtime·atomicload64 ( ( uint64* ) &runtime·blockprofilerate ) ; 
if ( rate <= 0 || ( rate > cycles && runtime·fastrand1 ( ) %rate > cycles ) ) 
return; 
#line 241 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
nstk = runtime·callers ( skip , stk , nelem ( stk ) ) ; 
runtime·lock ( &proflock ) ; 
b = stkbucket ( BProf , 0 , stk , nstk , true ) ; 
b->count++; 
b->cycles += cycles; 
runtime·unlock ( &proflock ) ; 
} 
#line 252 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
typedef struct Record Record; 
struct Record { 
int64 alloc_bytes , free_bytes; 
int64 alloc_objects , free_objects; 
uintptr stk[32]; 
} ; 
#line 260 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
static void 
record ( Record *r , Bucket *b ) 
{ 
int32 i; 
#line 265 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
r->alloc_bytes = b->alloc_bytes; 
r->free_bytes = b->free_bytes; 
r->alloc_objects = b->allocs; 
r->free_objects = b->frees; 
for ( i=0; i<b->nstk && i<nelem ( r->stk ) ; i++ ) 
r->stk[i] = b->stk[i]; 
for ( ; i<nelem ( r->stk ) ; i++ ) 
r->stk[i] = 0; 
} 
void
runtime·MemProfile(Slice p, bool include_inuse_zero, uint8, uint16, intgo n, bool ok)
{
	n = 0;
	FLUSH(&n);
	ok = 0;
	FLUSH(&ok);
#line 275 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"

	Bucket *b;
	Record *r;
	bool clear;

	runtime·lock(&proflock);
	n = 0;
	clear = true;
	for(b=mbuckets; b; b=b->allnext) {
		if(include_inuse_zero || b->alloc_bytes != b->free_bytes)
			n++;
		if(b->allocs != 0 || b->frees != 0)
			clear = false;
	}
	if(clear) {
		// Absolutely no data, suggesting that a garbage collection
		// has not yet happened. In order to allow profiling when
		// garbage collection is disabled from the beginning of execution,
		// accumulate stats as if a GC just happened, and recount buckets.
		MProf_GC();
		MProf_GC();
		n = 0;
		for(b=mbuckets; b; b=b->allnext)
			if(include_inuse_zero || b->alloc_bytes != b->free_bytes)
				n++;
	}
	ok = false;
	if(n <= p.len) {
		ok = true;
		r = (Record*)p.array;
		for(b=mbuckets; b; b=b->allnext)
			if(include_inuse_zero || b->alloc_bytes != b->free_bytes)
				record(r++, b);
	}
	runtime·unlock(&proflock);
	FLUSH(&n);
	FLUSH(&ok);
}

#line 313 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
typedef struct BRecord BRecord; 
struct BRecord { 
int64 count; 
int64 cycles; 
uintptr stk[32]; 
} ; 
void
runtime·BlockProfile(Slice p, intgo n, bool ok)
{
	n = 0;
	FLUSH(&n);
	ok = 0;
	FLUSH(&ok);
#line 320 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"

	Bucket *b;
	BRecord *r;
	int32 i;

	runtime·lock(&proflock);
	n = 0;
	for(b=bbuckets; b; b=b->allnext)
		n++;
	ok = false;
	if(n <= p.len) {
		ok = true;
		r = (BRecord*)p.array;
		for(b=bbuckets; b; b=b->allnext, r++) {
			r->count = b->count;
			r->cycles = b->cycles;
			for(i=0; i<b->nstk && i<nelem(r->stk); i++)
				r->stk[i] = b->stk[i];
			for(; i<nelem(r->stk); i++)
				r->stk[i] = 0;			
		}
	}
	runtime·unlock(&proflock);
	FLUSH(&n);
	FLUSH(&ok);
}

#line 346 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
typedef struct TRecord TRecord; 
struct TRecord { 
uintptr stk[32]; 
} ; 
void
runtime·ThreadCreateProfile(Slice p, intgo n, bool ok)
{
	n = 0;
	FLUSH(&n);
	ok = 0;
	FLUSH(&ok);
#line 351 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"

	TRecord *r;
	M *first, *mp;
	
	first = runtime·atomicloadp(&runtime·allm);
	n = 0;
	for(mp=first; mp; mp=mp->alllink)
		n++;
	ok = false;
	if(n <= p.len) {
		ok = true;
		r = (TRecord*)p.array;
		for(mp=first; mp; mp=mp->alllink) {
			runtime·memmove(r->stk, mp->createstack, sizeof r->stk);
			r++;
		}
	}
	FLUSH(&n);
	FLUSH(&ok);
}
void
runtime·Stack(Slice b, bool all, uint8, uint16, intgo n)
{
	n = 0;
	FLUSH(&n);
#line 370 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"

	uintptr pc, sp;
	
	sp = runtime·getcallersp(&b);
	pc = (uintptr)runtime·getcallerpc(&b);

	if(all) {
		runtime·semacquire(&runtime·worldsema, false);
		m->gcing = 1;
		runtime·stoptheworld();
	}

	if(b.len == 0)
		n = 0;
	else{
		g->writebuf = (byte*)b.array;
		g->writenbuf = b.len;
		runtime·goroutineheader(g);
		runtime·traceback(pc, sp, 0, g);
		if(all)
			runtime·tracebackothers(g);
		n = b.len - g->writenbuf;
		g->writebuf = nil;
		g->writenbuf = 0;
	}
	
	if(all) {
		m->gcing = 0;
		runtime·semrelease(&runtime·worldsema);
		runtime·starttheworld();
	}
	FLUSH(&n);
}

#line 403 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
static void 
saveg ( uintptr pc , uintptr sp , G *gp , TRecord *r ) 
{ 
int32 n; 
#line 408 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
n = runtime·gentraceback ( pc , sp , 0 , gp , 0 , r->stk , nelem ( r->stk ) , nil , nil , false ) ; 
if ( n < nelem ( r->stk ) ) 
r->stk[n] = 0; 
} 
void
runtime·GoroutineProfile(Slice b, intgo n, bool ok)
{
	n = 0;
	FLUSH(&n);
	ok = 0;
	FLUSH(&ok);
#line 413 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"

	uintptr pc, sp, i;
	TRecord *r;
	G *gp;
	
	sp = runtime·getcallersp(&b);
	pc = (uintptr)runtime·getcallerpc(&b);
	
	ok = false;
	n = runtime·gcount();
	if(n <= b.len) {
		runtime·semacquire(&runtime·worldsema, false);
		m->gcing = 1;
		runtime·stoptheworld();

		n = runtime·gcount();
		if(n <= b.len) {
			ok = true;
			r = (TRecord*)b.array;
			saveg(pc, sp, g, r++);
			for(i = 0; i < runtime·allglen; i++) {
				gp = runtime·allg[i];
				if(gp == g || gp->status == Gdead)
					continue;
				saveg(~(uintptr)0, ~(uintptr)0, gp, r++);
			}
		}
	
		m->gcing = 0;
		runtime·semrelease(&runtime·worldsema);
		runtime·starttheworld();
	}
	FLUSH(&n);
	FLUSH(&ok);
}

#line 449 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
static Lock tracelock; 
#line 451 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
static int8* 
typeinfoname ( int32 typeinfo ) 
{ 
if ( typeinfo == TypeInfo_SingleObject ) 
return "single object" ; 
else if ( typeinfo == TypeInfo_Array ) 
return "array" ; 
else if ( typeinfo == TypeInfo_Chan ) 
return "channel" ; 
runtime·throw ( "typinfoname: unknown type info" ) ; 
return nil; 
} 
#line 464 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
void 
runtime·tracealloc ( void *p , uintptr size , uintptr typ ) 
{ 
int8 *name; 
Type *type; 
#line 470 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
runtime·lock ( &tracelock ) ; 
m->traceback = 2; 
type = ( Type* ) ( typ & ~3 ) ; 
name = typeinfoname ( typ & 3 ) ; 
if ( type == nil ) 
runtime·printf ( "tracealloc(%p, %p, %s)\n" , p , size , name ) ; 
else 
runtime·printf ( "tracealloc(%p, %p, %s of %S)\n" , p , size , name , *type->string ) ; 
if ( m->curg == nil || g == m->curg ) { 
runtime·goroutineheader ( g ) ; 
runtime·traceback ( ( uintptr ) runtime·getcallerpc ( &p ) , ( uintptr ) runtime·getcallersp ( &p ) , 0 , g ) ; 
} else { 
runtime·goroutineheader ( m->curg ) ; 
runtime·traceback ( ~ ( uintptr ) 0 , ~ ( uintptr ) 0 , 0 , m->curg ) ; 
} 
runtime·printf ( "\n" ) ; 
m->traceback = 0; 
runtime·unlock ( &tracelock ) ; 
} 
#line 490 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
void 
runtime·tracefree ( void *p , uintptr size ) 
{ 
runtime·lock ( &tracelock ) ; 
m->traceback = 2; 
runtime·printf ( "tracefree(%p, %p)\n" , p , size ) ; 
runtime·goroutineheader ( g ) ; 
runtime·traceback ( ( uintptr ) runtime·getcallerpc ( &p ) , ( uintptr ) runtime·getcallersp ( &p ) , 0 , g ) ; 
runtime·printf ( "\n" ) ; 
m->traceback = 0; 
runtime·unlock ( &tracelock ) ; 
} 
#line 503 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
void 
runtime·tracegc ( void ) 
{ 
runtime·lock ( &tracelock ) ; 
m->traceback = 2; 
runtime·printf ( "tracegc()\n" ) ; 
#line 510 "/home/14/ren/source/golang/go/src/pkg/runtime/mprof.goc"
runtime·tracebackothers ( g ) ; 
runtime·printf ( "end tracegc\n" ) ; 
runtime·printf ( "\n" ) ; 
m->traceback = 0; 
runtime·unlock ( &tracelock ) ; 
} 