// auto generated by go tool dist
// goos=freebsd goarch=arm


#include "runtime.h"
#include "arch_GOARCH.h"
#include "malloc.h"
#include "type.h"
#include "typekind.h"
#include "race.h"
#include "stack.h"
#include "../../cmd/ld/textflag.h"
#pragma dataflag NOPTR

#line 21 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
MHeap runtime·mheap; 
MStats mstats; 
#line 24 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
int32 runtime·checking; 
#line 26 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
extern MStats mstats; 
#line 28 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
extern volatile intgo runtime·MemProfileRate; 
#line 30 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
static MSpan* largealloc ( uint32 , uintptr* ) ; 
static void profilealloc ( void *v , uintptr size ) ; 
static void settype ( MSpan *s , void *v , uintptr typ ) ; 
#line 38 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
void* 
runtime·mallocgc ( uintptr size , uintptr typ , uint32 flag ) 
{ 
int32 sizeclass; 
uintptr tinysize , size1; 
intgo rate; 
MCache *c; 
MSpan *s; 
MLink *v , *next; 
byte *tiny; 
#line 49 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( size == 0 ) { 
#line 53 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
return &runtime·zerobase; 
} 
if ( m->mallocing ) 
runtime·throw ( "malloc/free - deadlock" ) ; 
#line 59 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
m->locks++; 
m->mallocing = 1; 
#line 62 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( DebugTypeAtBlockEnd ) 
size += sizeof ( uintptr ) ; 
#line 65 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
c = m->mcache; 
if ( !runtime·debug.efence && size <= MaxSmallSize ) { 
if ( ( flag& ( FlagNoScan|FlagNoGC ) ) == FlagNoScan && size < TinySize ) { 
#line 98 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
tinysize = c->tinysize; 
if ( size <= tinysize ) { 
tiny = c->tiny; 
#line 102 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( ( size&7 ) == 0 ) 
tiny = ( byte* ) ROUND ( ( uintptr ) tiny , 8 ) ; 
else if ( ( size&3 ) == 0 ) 
tiny = ( byte* ) ROUND ( ( uintptr ) tiny , 4 ) ; 
else if ( ( size&1 ) == 0 ) 
tiny = ( byte* ) ROUND ( ( uintptr ) tiny , 2 ) ; 
size1 = size + ( tiny - c->tiny ) ; 
if ( size1 <= tinysize ) { 
#line 111 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
v = ( MLink* ) tiny; 
c->tiny += size1; 
c->tinysize -= size1; 
m->mallocing = 0; 
m->locks--; 
if ( m->locks == 0 && g->preempt ) 
g->stackguard0 = StackPreempt; 
return v; 
} 
} 
#line 122 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
s = c->alloc[TinySizeClass]; 
if ( s->freelist == nil ) 
s = runtime·MCache_Refill ( c , TinySizeClass ) ; 
v = s->freelist; 
next = v->next; 
s->freelist = next; 
s->ref++; 
if ( next != nil ) 
PREFETCH ( next ) ; 
( ( uint64* ) v ) [0] = 0; 
( ( uint64* ) v ) [1] = 0; 
#line 135 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( TinySize-size > tinysize ) { 
c->tiny = ( byte* ) v + size; 
c->tinysize = TinySize - size; 
} 
size = TinySize; 
goto done; 
} 
#line 144 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( size <= 1024-8 ) 
sizeclass = runtime·size_to_class8[ ( size+7 ) >>3]; 
else 
sizeclass = runtime·size_to_class128[ ( size-1024+127 ) >> 7]; 
size = runtime·class_to_size[sizeclass]; 
s = c->alloc[sizeclass]; 
if ( s->freelist == nil ) 
s = runtime·MCache_Refill ( c , sizeclass ) ; 
v = s->freelist; 
next = v->next; 
s->freelist = next; 
s->ref++; 
if ( next != nil ) 
PREFETCH ( next ) ; 
if ( ! ( flag & FlagNoZero ) ) { 
v->next = nil; 
#line 161 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( size > 2*sizeof ( uintptr ) && ( ( uintptr* ) v ) [1] != 0 ) 
runtime·memclr ( ( byte* ) v , size ) ; 
} 
done: 
c->local_cachealloc += size; 
} else { 
#line 168 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
s = largealloc ( flag , &size ) ; 
v = ( void* ) ( s->start << PageShift ) ; 
} 
#line 172 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( flag & FlagNoGC ) 
runtime·marknogc ( v ) ; 
else if ( ! ( flag & FlagNoScan ) ) 
runtime·markscan ( v ) ; 
#line 177 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( DebugTypeAtBlockEnd ) 
* ( uintptr* ) ( ( uintptr ) v+size-sizeof ( uintptr ) ) = typ; 
#line 180 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
m->mallocing = 0; 
#line 183 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( UseSpanType && ! ( flag & FlagNoScan ) && typ != 0 ) 
settype ( s , v , typ ) ; 
#line 186 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( raceenabled ) 
runtime·racemalloc ( v , size ) ; 
#line 189 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( runtime·debug.allocfreetrace ) 
runtime·tracealloc ( v , size , typ ) ; 
#line 192 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( ! ( flag & FlagNoProfiling ) && ( rate = runtime·MemProfileRate ) > 0 ) { 
if ( size < rate && size < c->next_sample ) 
c->next_sample -= size; 
else 
profilealloc ( v , size ) ; 
} 
#line 199 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
m->locks--; 
if ( m->locks == 0 && g->preempt ) 
g->stackguard0 = StackPreempt; 
#line 203 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( ! ( flag & FlagNoInvokeGC ) && mstats.heap_alloc >= mstats.next_gc ) 
runtime·gc ( 0 ) ; 
#line 206 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
return v; 
} 
#line 209 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
static MSpan* 
largealloc ( uint32 flag , uintptr *sizep ) 
{ 
uintptr npages , size; 
MSpan *s; 
void *v; 
#line 217 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
size = *sizep; 
if ( size + PageSize < size ) 
runtime·throw ( "out of memory" ) ; 
npages = size >> PageShift; 
if ( ( size & PageMask ) != 0 ) 
npages++; 
s = runtime·MHeap_Alloc ( &runtime·mheap , npages , 0 , 1 , ! ( flag & FlagNoZero ) ) ; 
if ( s == nil ) 
runtime·throw ( "out of memory" ) ; 
s->limit = ( byte* ) ( s->start<<PageShift ) + size; 
*sizep = npages<<PageShift; 
v = ( void* ) ( s->start << PageShift ) ; 
#line 230 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
runtime·markspan ( v , 0 , 0 , true ) ; 
return s; 
} 
#line 234 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
static void 
profilealloc ( void *v , uintptr size ) 
{ 
uintptr rate; 
int32 next; 
MCache *c; 
#line 241 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
c = m->mcache; 
rate = runtime·MemProfileRate; 
if ( size < rate ) { 
#line 246 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( rate > 0x3fffffff ) 
rate = 0x3fffffff; 
next = runtime·fastrand1 ( ) % ( 2*rate ) ; 
#line 252 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
next -= ( size - c->next_sample ) ; 
if ( next < 0 ) 
next = 0; 
c->next_sample = next; 
} 
runtime·MProf_Malloc ( v , size ) ; 
} 
#line 260 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
void* 
runtime·malloc ( uintptr size ) 
{ 
return runtime·mallocgc ( size , 0 , FlagNoInvokeGC ) ; 
} 
#line 267 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
void 
runtime·free ( void *v ) 
{ 
int32 sizeclass; 
MSpan *s; 
MCache *c; 
uintptr size; 
#line 275 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( v == nil ) 
return; 
#line 281 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( m->mallocing ) 
runtime·throw ( "malloc/free - deadlock" ) ; 
m->mallocing = 1; 
#line 285 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( !runtime·mlookup ( v , nil , nil , &s ) ) { 
runtime·printf ( "free %p: not an allocated block\n" , v ) ; 
runtime·throw ( "free runtime·mlookup" ) ; 
} 
size = s->elemsize; 
sizeclass = s->sizeclass; 
#line 293 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( size < TinySize ) 
runtime·throw ( "freeing too small block" ) ; 
#line 296 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( runtime·debug.allocfreetrace ) 
runtime·tracefree ( v , size ) ; 
#line 301 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
runtime·MSpan_EnsureSwept ( s ) ; 
#line 303 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( s->specials != nil ) 
runtime·freeallspecials ( s , v , size ) ; 
#line 306 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
c = m->mcache; 
if ( sizeclass == 0 ) { 
#line 309 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
s->needzero = 1; 
#line 312 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
runtime·markfreed ( v ) ; 
runtime·unmarkspan ( v , 1<<PageShift ) ; 
#line 328 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( runtime·debug.efence ) 
runtime·SysFault ( ( void* ) ( s->start<<PageShift ) , size ) ; 
else 
runtime·MHeap_Free ( &runtime·mheap , s , 1 ) ; 
c->local_nlargefree++; 
c->local_largefree += size; 
} else { 
#line 336 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( size > 2*sizeof ( uintptr ) ) 
( ( uintptr* ) v ) [1] = ( uintptr ) 0xfeedfeedfeedfeedll; 
else if ( size > sizeof ( uintptr ) ) 
( ( uintptr* ) v ) [1] = 0; 
#line 343 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
c->local_nsmallfree[sizeclass]++; 
c->local_cachealloc -= size; 
if ( c->alloc[sizeclass] == s ) { 
#line 347 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
runtime·markfreed ( v ) ; 
( ( MLink* ) v ) ->next = s->freelist; 
s->freelist = v; 
s->ref--; 
} else { 
#line 353 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
runtime·MCache_Free ( c , v , sizeclass , size ) ; 
} 
} 
m->mallocing = 0; 
} 
#line 359 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
int32 
runtime·mlookup ( void *v , byte **base , uintptr *size , MSpan **sp ) 
{ 
uintptr n , i; 
byte *p; 
MSpan *s; 
#line 366 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
m->mcache->local_nlookup++; 
if ( sizeof ( void* ) == 4 && m->mcache->local_nlookup >= ( 1<<30 ) ) { 
#line 369 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
runtime·lock ( &runtime·mheap ) ; 
runtime·purgecachedstats ( m->mcache ) ; 
runtime·unlock ( &runtime·mheap ) ; 
} 
#line 374 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
s = runtime·MHeap_LookupMaybe ( &runtime·mheap , v ) ; 
if ( sp ) 
*sp = s; 
if ( s == nil ) { 
runtime·checkfreed ( v , 1 ) ; 
if ( base ) 
*base = nil; 
if ( size ) 
*size = 0; 
return 0; 
} 
#line 386 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
p = ( byte* ) ( ( uintptr ) s->start<<PageShift ) ; 
if ( s->sizeclass == 0 ) { 
#line 389 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( base ) 
*base = p; 
if ( size ) 
*size = s->npages<<PageShift; 
return 1; 
} 
#line 396 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
n = s->elemsize; 
if ( base ) { 
i = ( ( byte* ) v - p ) /n; 
*base = p + i*n; 
} 
if ( size ) 
*size = n; 
#line 404 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
return 1; 
} 
#line 407 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
void 
runtime·purgecachedstats ( MCache *c ) 
{ 
MHeap *h; 
int32 i; 
#line 414 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
h = &runtime·mheap; 
mstats.heap_alloc += c->local_cachealloc; 
c->local_cachealloc = 0; 
mstats.nlookup += c->local_nlookup; 
c->local_nlookup = 0; 
h->largefree += c->local_largefree; 
c->local_largefree = 0; 
h->nlargefree += c->local_nlargefree; 
c->local_nlargefree = 0; 
for ( i=0; i<nelem ( c->local_nsmallfree ) ; i++ ) { 
h->nsmallfree[i] += c->local_nsmallfree[i]; 
c->local_nsmallfree[i] = 0; 
} 
} 
#line 432 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
uintptr runtime·sizeof_C_MStats = sizeof ( MStats ) - ( NumSizeClasses - 61 ) * sizeof ( mstats.by_size[0] ) ; 
#define MaxArena32 (2U<<30)

#line 436 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
void 
runtime·mallocinit ( void ) 
{ 
byte *p , *p1; 
uintptr arena_size , bitmap_size , spans_size , p_size; 
extern byte end[]; 
uintptr limit; 
uint64 i; 
bool reserved; 
#line 446 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
p = nil; 
p_size = 0; 
arena_size = 0; 
bitmap_size = 0; 
spans_size = 0; 
reserved = false; 
#line 454 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
USED ( p ) ; 
USED ( p_size ) ; 
USED ( arena_size ) ; 
USED ( bitmap_size ) ; 
USED ( spans_size ) ; 
#line 460 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
runtime·InitSizes ( ) ; 
#line 462 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( runtime·class_to_size[TinySizeClass] != TinySize ) 
runtime·throw ( "bad TinySizeClass" ) ; 
#line 468 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
limit = 0; 
#line 473 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( sizeof ( void* ) == 8 && ( limit == 0 || limit > ( 1<<30 ) ) ) { 
#line 498 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
arena_size = MaxMem; 
bitmap_size = arena_size / ( sizeof ( void* ) *8/4 ) ; 
spans_size = arena_size / PageSize * sizeof ( runtime·mheap.spans[0] ) ; 
spans_size = ROUND ( spans_size , PageSize ) ; 
for ( i = 0; i <= 0x7f; i++ ) { 
p = ( void* ) ( i<<40 | 0x00c0ULL<<32 ) ; 
p_size = bitmap_size + spans_size + arena_size + PageSize; 
p = runtime·SysReserve ( p , p_size , &reserved ) ; 
if ( p != nil ) 
break; 
} 
} 
if ( p == nil ) { 
#line 528 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
bitmap_size = MaxArena32 / ( sizeof ( void* ) *8/4 ) ; 
arena_size = 512<<20; 
spans_size = MaxArena32 / PageSize * sizeof ( runtime·mheap.spans[0] ) ; 
if ( limit > 0 && arena_size+bitmap_size+spans_size > limit ) { 
bitmap_size = ( limit / 9 ) & ~ ( ( 1<<PageShift ) - 1 ) ; 
arena_size = bitmap_size * 8; 
spans_size = arena_size / PageSize * sizeof ( runtime·mheap.spans[0] ) ; 
} 
spans_size = ROUND ( spans_size , PageSize ) ; 
#line 547 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
p = ( byte* ) ROUND ( ( uintptr ) end + ( 1<<18 ) , 1<<20 ) ; 
p_size = bitmap_size + spans_size + arena_size + PageSize; 
p = runtime·SysReserve ( p , p_size , &reserved ) ; 
if ( p == nil ) 
runtime·throw ( "runtime: cannot reserve arena virtual address space" ) ; 
} 
#line 557 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
p1 = ( byte* ) ROUND ( ( uintptr ) p , PageSize ) ; 
#line 559 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
runtime·mheap.spans = ( MSpan** ) p1; 
runtime·mheap.bitmap = p1 + spans_size; 
runtime·mheap.arena_start = p1 + spans_size + bitmap_size; 
runtime·mheap.arena_used = runtime·mheap.arena_start; 
runtime·mheap.arena_end = p + p_size; 
runtime·mheap.arena_reserved = reserved; 
#line 566 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( ( ( uintptr ) runtime·mheap.arena_start & ( PageSize-1 ) ) != 0 ) 
runtime·throw ( "misrounded allocation in mallocinit" ) ; 
#line 570 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
runtime·MHeap_Init ( &runtime·mheap ) ; 
m->mcache = runtime·allocmcache ( ) ; 
#line 574 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
runtime·free ( runtime·malloc ( TinySize ) ) ; 
} 
#line 577 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
void* 
runtime·MHeap_SysAlloc ( MHeap *h , uintptr n ) 
{ 
byte *p , *p_end; 
uintptr p_size; 
bool reserved; 
#line 584 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( n > h->arena_end - h->arena_used ) { 
#line 587 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
byte *new_end; 
#line 589 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
p_size = ROUND ( n + PageSize , 256<<20 ) ; 
new_end = h->arena_end + p_size; 
if ( new_end <= h->arena_start + MaxArena32 ) { 
#line 594 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
p = runtime·SysReserve ( h->arena_end , p_size , &reserved ) ; 
if ( p == h->arena_end ) { 
h->arena_end = new_end; 
h->arena_reserved = reserved; 
} 
else if ( p+p_size <= h->arena_start + MaxArena32 ) { 
#line 602 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
h->arena_end = p+p_size; 
h->arena_used = p + ( - ( uintptr ) p& ( PageSize-1 ) ) ; 
h->arena_reserved = reserved; 
} else { 
uint64 stat; 
stat = 0; 
runtime·SysFree ( p , p_size , &stat ) ; 
} 
} 
} 
if ( n <= h->arena_end - h->arena_used ) { 
#line 614 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
p = h->arena_used; 
runtime·SysMap ( p , n , h->arena_reserved , &mstats.heap_sys ) ; 
h->arena_used += n; 
runtime·MHeap_MapBits ( h ) ; 
runtime·MHeap_MapSpans ( h ) ; 
if ( raceenabled ) 
runtime·racemapshadow ( p , n ) ; 
#line 622 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( ( ( uintptr ) p & ( PageSize-1 ) ) != 0 ) 
runtime·throw ( "misrounded allocation in MHeap_SysAlloc" ) ; 
return p; 
} 
#line 628 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( h->arena_end - h->arena_start >= MaxArena32 ) 
return nil; 
#line 634 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
p_size = ROUND ( n , PageSize ) + PageSize; 
p = runtime·SysAlloc ( p_size , &mstats.heap_sys ) ; 
if ( p == nil ) 
return nil; 
#line 639 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( p < h->arena_start || p+p_size - h->arena_start >= MaxArena32 ) { 
runtime·printf ( "runtime: memory allocated by OS (%p) not in usable range [%p,%p)\n" , 
p , h->arena_start , h->arena_start+MaxArena32 ) ; 
runtime·SysFree ( p , p_size , &mstats.heap_sys ) ; 
return nil; 
} 
#line 646 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
p_end = p + p_size; 
p += - ( uintptr ) p & ( PageSize-1 ) ; 
if ( p+n > h->arena_used ) { 
h->arena_used = p+n; 
if ( p_end > h->arena_end ) 
h->arena_end = p_end; 
runtime·MHeap_MapBits ( h ) ; 
runtime·MHeap_MapSpans ( h ) ; 
if ( raceenabled ) 
runtime·racemapshadow ( p , n ) ; 
} 
#line 658 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( ( ( uintptr ) p & ( PageSize-1 ) ) != 0 ) 
runtime·throw ( "misrounded allocation in MHeap_SysAlloc" ) ; 
return p; 
} 
#line 663 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
static struct 
{ 
Lock; 
byte* pos; 
byte* end; 
} persistent; 
#line 670 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
enum 
{ 
PersistentAllocChunk = 256<<10 , 
PersistentAllocMaxBlock = 64<<10 , 
} ; 
#line 680 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
void* 
runtime·persistentalloc ( uintptr size , uintptr align , uint64 *stat ) 
{ 
byte *p; 
#line 685 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( align != 0 ) { 
if ( align& ( align-1 ) ) 
runtime·throw ( "persistentalloc: align is now a power of 2" ) ; 
if ( align > PageSize ) 
runtime·throw ( "persistentalloc: align is too large" ) ; 
} else 
align = 8; 
if ( size >= PersistentAllocMaxBlock ) 
return runtime·SysAlloc ( size , stat ) ; 
runtime·lock ( &persistent ) ; 
persistent.pos = ( byte* ) ROUND ( ( uintptr ) persistent.pos , align ) ; 
if ( persistent.pos + size > persistent.end ) { 
persistent.pos = runtime·SysAlloc ( PersistentAllocChunk , &mstats.other_sys ) ; 
if ( persistent.pos == nil ) { 
runtime·unlock ( &persistent ) ; 
runtime·throw ( "runtime: cannot allocate memory" ) ; 
} 
persistent.end = persistent.pos + PersistentAllocChunk; 
} 
p = persistent.pos; 
persistent.pos += size; 
runtime·unlock ( &persistent ) ; 
if ( stat != &mstats.other_sys ) { 
#line 709 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
runtime·xadd64 ( stat , size ) ; 
runtime·xadd64 ( &mstats.other_sys , - ( uint64 ) size ) ; 
} 
return p; 
} 
#line 715 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
static void 
settype ( MSpan *s , void *v , uintptr typ ) 
{ 
uintptr size , ofs , j , t; 
uintptr ntypes , nbytes2 , nbytes3; 
uintptr *data2; 
byte *data3; 
#line 723 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
if ( s->sizeclass == 0 ) { 
s->types.compression = MTypes_Single; 
s->types.data = typ; 
return; 
} 
size = s->elemsize; 
ofs = ( ( uintptr ) v - ( s->start<<PageShift ) ) / size; 
#line 731 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
switch ( s->types.compression ) { 
case MTypes_Empty: 
ntypes = ( s->npages << PageShift ) / size; 
nbytes3 = 8*sizeof ( uintptr ) + 1*ntypes; 
data3 = runtime·mallocgc ( nbytes3 , 0 , FlagNoProfiling|FlagNoScan|FlagNoInvokeGC ) ; 
s->types.compression = MTypes_Bytes; 
s->types.data = ( uintptr ) data3; 
( ( uintptr* ) data3 ) [1] = typ; 
data3[8*sizeof ( uintptr ) + ofs] = 1; 
break; 
#line 742 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
case MTypes_Words: 
( ( uintptr* ) s->types.data ) [ofs] = typ; 
break; 
#line 746 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
case MTypes_Bytes: 
data3 = ( byte* ) s->types.data; 
for ( j=1; j<8; j++ ) { 
if ( ( ( uintptr* ) data3 ) [j] == typ ) { 
break; 
} 
if ( ( ( uintptr* ) data3 ) [j] == 0 ) { 
( ( uintptr* ) data3 ) [j] = typ; 
break; 
} 
} 
if ( j < 8 ) { 
data3[8*sizeof ( uintptr ) + ofs] = j; 
} else { 
ntypes = ( s->npages << PageShift ) / size; 
nbytes2 = ntypes * sizeof ( uintptr ) ; 
data2 = runtime·mallocgc ( nbytes2 , 0 , FlagNoProfiling|FlagNoScan|FlagNoInvokeGC ) ; 
s->types.compression = MTypes_Words; 
s->types.data = ( uintptr ) data2; 
#line 767 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
for ( j=0; j<ntypes; j++ ) { 
t = data3[8*sizeof ( uintptr ) + j]; 
t = ( ( uintptr* ) data3 ) [t]; 
data2[j] = t; 
} 
data2[ofs] = typ; 
} 
break; 
} 
} 
#line 778 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
uintptr 
runtime·gettype ( void *v ) 
{ 
MSpan *s; 
uintptr t , ofs; 
byte *data; 
#line 785 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
s = runtime·MHeap_LookupMaybe ( &runtime·mheap , v ) ; 
if ( s != nil ) { 
t = 0; 
switch ( s->types.compression ) { 
case MTypes_Empty: 
break; 
case MTypes_Single: 
t = s->types.data; 
break; 
case MTypes_Words: 
ofs = ( uintptr ) v - ( s->start<<PageShift ) ; 
t = ( ( uintptr* ) s->types.data ) [ofs/s->elemsize]; 
break; 
case MTypes_Bytes: 
ofs = ( uintptr ) v - ( s->start<<PageShift ) ; 
data = ( byte* ) s->types.data; 
t = data[8*sizeof ( uintptr ) + ofs/s->elemsize]; 
t = ( ( uintptr* ) data ) [t]; 
break; 
default: 
runtime·throw ( "runtime·gettype: invalid compression kind" ) ; 
} 
if ( 0 ) { 
runtime·printf ( "%p -> %d,%X\n" , v , ( int32 ) s->types.compression , ( int64 ) t ) ; 
} 
return t; 
} 
return 0; 
} 
#line 817 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
void* 
runtime·mal ( uintptr n ) 
{ 
return runtime·mallocgc ( n , 0 , 0 ) ; 
} 
#pragma textflag NOSPLIT

void
runtime·new(Type* typ, uint8* ret)
{
	ret = 0;
	FLUSH(&ret);
#line 824 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"

	ret = runtime·mallocgc(typ->size, (uintptr)typ | TypeInfo_SingleObject, typ->kind&KindNoPointers ? FlagNoScan : 0);
	FLUSH(&ret);
}

#line 828 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
static void* 
cnew ( Type *typ , intgo n , int32 objtyp ) 
{ 
if ( ( objtyp& ( PtrSize-1 ) ) != objtyp ) 
runtime·throw ( "runtime: invalid objtyp" ) ; 
if ( n < 0 || ( typ->size > 0 && n > MaxMem/typ->size ) ) 
runtime·panicstring ( "runtime: allocation size out of range" ) ; 
return runtime·mallocgc ( typ->size*n , ( uintptr ) typ | objtyp , typ->kind&KindNoPointers ? FlagNoScan : 0 ) ; 
} 
#line 839 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
void* 
runtime·cnew ( Type *typ ) 
{ 
return cnew ( typ , 1 , TypeInfo_SingleObject ) ; 
} 
#line 845 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"
void* 
runtime·cnewarray ( Type *typ , intgo n ) 
{ 
return cnew ( typ , n , TypeInfo_Array ) ; 
} 
void
runtime·GC()
{
#line 851 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"

	// We assume that the user expects unused memory to have
	// been freed when GC returns. To ensure this, run gc(1) twice.
	// The first will do a collection, and the second will force the
	// first's sweeping to finish before doing a second collection.
	// The second collection is overkill, but we assume the user
	// has a good reason for calling runtime.GC and can stand the
	// expense. At the least, this fixes all the calls to runtime.GC in
	// tests that expect finalizers to start running when GC returns.
	runtime·gc(1);
	runtime·gc(1);
}
void
runtime·SetFinalizer(Eface obj, Eface finalizer)
{
#line 864 "/home/14/ren/source/golang/go/src/pkg/runtime/malloc.goc"

	byte *base;
	uintptr size;
	FuncType *ft;
	int32 i;
	uintptr nret;
	Type *t;
	Type *fint;
	PtrType *ot;
	Iface iface;

	if(obj.type == nil) {
		runtime·printf("runtime.SetFinalizer: first argument is nil interface\n");
		goto throw;
	}
	if(obj.type->kind != KindPtr) {
		runtime·printf("runtime.SetFinalizer: first argument is %S, not pointer\n", *obj.type->string);
		goto throw;
	}
	ot = (PtrType*)obj.type;
	// As an implementation detail we do not run finalizers for zero-sized objects,
	// because we use &runtime·zerobase for all such allocations.
	if(ot->elem != nil && ot->elem->size == 0)
		return;
	// The following check is required for cases when a user passes a pointer to composite literal,
	// but compiler makes it a pointer to global. For example:
	//	var Foo = &Object{}
	//	func main() {
	//		runtime.SetFinalizer(Foo, nil)
	//	}
	// See issue 7656.
	if((byte*)obj.data < runtime·mheap.arena_start || runtime·mheap.arena_used <= (byte*)obj.data)
		return;
	if(!runtime·mlookup(obj.data, &base, &size, nil) || obj.data != base) {
		// As an implementation detail we allow to set finalizers for an inner byte
		// of an object if it could come from tiny alloc (see mallocgc for details).
		if(ot->elem == nil || (ot->elem->kind&KindNoPointers) == 0 || ot->elem->size >= TinySize) {
			runtime·printf("runtime.SetFinalizer: pointer not at beginning of allocated block (%p)\n", obj.data);
			goto throw;
		}
	}
	if(finalizer.type != nil) {
		runtime·createfing();
		if(finalizer.type->kind != KindFunc)
			goto badfunc;
		ft = (FuncType*)finalizer.type;
		if(ft->dotdotdot || ft->in.len != 1)
			goto badfunc;
		fint = *(Type**)ft->in.array;
		if(fint == obj.type) {
			// ok - same type
		} else if(fint->kind == KindPtr && (fint->x == nil || fint->x->name == nil || obj.type->x == nil || obj.type->x->name == nil) && ((PtrType*)fint)->elem == ((PtrType*)obj.type)->elem) {
			// ok - not same type, but both pointers,
			// one or the other is unnamed, and same element type, so assignable.
		} else if(fint->kind == KindInterface && ((InterfaceType*)fint)->mhdr.len == 0) {
			// ok - satisfies empty interface
		} else if(fint->kind == KindInterface && runtime·ifaceE2I2((InterfaceType*)fint, obj, &iface)) {
			// ok - satisfies non-empty interface
		} else
			goto badfunc;

		// compute size needed for return parameters
		nret = 0;
		for(i=0; i<ft->out.len; i++) {
			t = ((Type**)ft->out.array)[i];
			nret = ROUND(nret, t->align) + t->size;
		}
		nret = ROUND(nret, sizeof(void*));
		ot = (PtrType*)obj.type;
		if(!runtime·addfinalizer(obj.data, finalizer.data, nret, fint, ot)) {
			runtime·printf("runtime.SetFinalizer: finalizer already set\n");
			goto throw;
		}
	} else {
		// NOTE: asking to remove a finalizer when there currently isn't one set is OK.
		runtime·removefinalizer(obj.data);
	}
	return;

badfunc:
	runtime·printf("runtime.SetFinalizer: cannot pass %S to finalizer %S\n", *obj.type->string, *finalizer.type->string);
throw:
	runtime·throw("runtime.SetFinalizer");
}
