// auto generated by go tool dist
// goos=windows goarch=386


#include "runtime.h"
#include "arch_GOARCH.h"
#ifdef _64BIT
# define PTR_BITS 47
#else
# define PTR_BITS 32
#endif
#define PTR_MASK ((1ull<<PTR_BITS)-1)
#define CNT_MASK (0ull-1)
#ifdef _64BIT
#ifdef GOOS_solaris
#undef PTR_BITS
#undef CNT_MASK
#undef PTR_MASK
#define PTR_BITS 0
#define CNT_MASK 7
#define PTR_MASK ((0ull-1)<<3)
#endif
#endif

#line 35 "/home/14/ren/source/golang/go/src/pkg/runtime/lfstack.goc"
void 
runtime·lfstackpush ( uint64 *head , LFNode *node ) 
{ 
uint64 old , new; 
#line 40 "/home/14/ren/source/golang/go/src/pkg/runtime/lfstack.goc"
if ( ( uintptr ) node != ( ( uintptr ) node&PTR_MASK ) ) { 
runtime·printf ( "p=%p\n" , node ) ; 
runtime·throw ( "runtime·lfstackpush: invalid pointer" ) ; 
} 
#line 45 "/home/14/ren/source/golang/go/src/pkg/runtime/lfstack.goc"
node->pushcnt++; 
new = ( uint64 ) ( uintptr ) node| ( ( ( uint64 ) node->pushcnt&CNT_MASK ) <<PTR_BITS ) ; 
for ( ;; ) { 
old = runtime·atomicload64 ( head ) ; 
node->next = ( LFNode* ) ( uintptr ) ( old&PTR_MASK ) ; 
if ( runtime·cas64 ( head , old , new ) ) 
break; 
} 
} 
#line 55 "/home/14/ren/source/golang/go/src/pkg/runtime/lfstack.goc"
LFNode* 
runtime·lfstackpop ( uint64 *head ) 
{ 
LFNode *node , *node2; 
uint64 old , new; 
#line 61 "/home/14/ren/source/golang/go/src/pkg/runtime/lfstack.goc"
for ( ;; ) { 
old = runtime·atomicload64 ( head ) ; 
if ( old == 0 ) 
return nil; 
node = ( LFNode* ) ( uintptr ) ( old&PTR_MASK ) ; 
node2 = runtime·atomicloadp ( &node->next ) ; 
new = 0; 
if ( node2 != nil ) 
new = ( uint64 ) ( uintptr ) node2| ( ( ( uint64 ) node2->pushcnt&CNT_MASK ) <<PTR_BITS ) ; 
if ( runtime·cas64 ( head , old , new ) ) 
return node; 
} 
} 
void
runtime·lfstackpush_go(uint64* head, LFNode* node)
{
#line 75 "/home/14/ren/source/golang/go/src/pkg/runtime/lfstack.goc"

	runtime·lfstackpush(head, node);
}
void
runtime·lfstackpop_go(uint64* head, LFNode* node)
{
	node = 0;
	FLUSH(&node);
#line 79 "/home/14/ren/source/golang/go/src/pkg/runtime/lfstack.goc"

	node = runtime·lfstackpop(head);
	FLUSH(&node);
}
