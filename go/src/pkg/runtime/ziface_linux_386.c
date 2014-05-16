// auto generated by go tool dist
// goos=linux goarch=386


#include "runtime.h"
#include "arch_GOARCH.h"
#include "type.h"
#include "typekind.h"
#include "malloc.h"
#include "../../cmd/ld/textflag.h"
void
runtime·printiface(Iface i)
{
#line 13 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	runtime·printf("(%p,%p)", i.tab, i.data);
}
void
runtime·printeface(Eface e)
{
#line 17 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	runtime·printf("(%p,%p)", e.type, e.data);
}

#line 21 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
static Itab* hash[1009]; 
static Lock ifacelock; 
#line 24 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
static Itab* 
itab ( InterfaceType *inter , Type *type , int32 canfail ) 
{ 
int32 locked; 
int32 ni; 
Method *t , *et; 
IMethod *i , *ei; 
uint32 h; 
String *iname , *ipkgPath; 
Itab *m; 
UncommonType *x; 
Type *itype; 
Eface err; 
#line 38 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
if ( inter->mhdr.len == 0 ) 
runtime·throw ( "internal error - misuse of itab" ) ; 
#line 41 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
locked = 0; 
#line 44 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
x = type->x; 
if ( x == nil ) { 
if ( canfail ) 
return nil; 
iname = inter->m[0].name; 
goto throw; 
} 
#line 53 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
h = inter->hash; 
h += 17 * type->hash; 
#line 56 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
h %= nelem ( hash ) ; 
#line 60 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
for ( locked=0; locked<2; locked++ ) { 
if ( locked ) 
runtime·lock ( &ifacelock ) ; 
for ( m=runtime·atomicloadp ( &hash[h] ) ; m!=nil; m=m->link ) { 
if ( m->inter == inter && m->type == type ) { 
if ( m->bad ) { 
m = nil; 
if ( !canfail ) { 
#line 75 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
goto search; 
} 
} 
if ( locked ) 
runtime·unlock ( &ifacelock ) ; 
return m; 
} 
} 
} 
#line 85 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
ni = inter->mhdr.len; 
m = runtime·persistentalloc ( sizeof ( *m ) + ni*sizeof m->fun[0] , 0 , &mstats.other_sys ) ; 
m->inter = inter; 
m->type = type; 
#line 90 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
search: 
#line 95 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
i = inter->m; 
ei = i + inter->mhdr.len; 
t = x->m; 
et = t + x->mhdr.len; 
for ( ; i < ei; i++ ) { 
itype = i->type; 
iname = i->name; 
ipkgPath = i->pkgPath; 
for ( ;; t++ ) { 
if ( t >= et ) { 
if ( !canfail ) { 
throw: 
#line 108 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
runtime·newTypeAssertionError ( 
nil , type->string , inter->string , 
iname , &err ) ; 
if ( locked ) 
runtime·unlock ( &ifacelock ) ; 
runtime·panic ( err ) ; 
return nil; 
} 
m->bad = 1; 
goto out; 
} 
if ( t->mtyp == itype && t->name == iname && t->pkgPath == ipkgPath ) 
break; 
} 
if ( m ) 
m->fun[i - inter->m] = t->ifn; 
} 
#line 126 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
out: 
if ( !locked ) 
runtime·panicstring ( "invalid itab locking" ) ; 
m->link = hash[h]; 
runtime·atomicstorep ( &hash[h] , m ) ; 
runtime·unlock ( &ifacelock ) ; 
if ( m->bad ) 
return nil; 
return m; 
} 
#line 138 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
void 
runtime·iterate_itabs ( void ( *callback ) ( Itab* ) ) 
{ 
int32 i; 
Itab *tab; 
#line 144 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
for ( i = 0; i < nelem ( hash ) ; i++ ) { 
for ( tab = hash[i]; tab != nil; tab = tab->link ) { 
callback ( tab ) ; 
} 
} 
} 
#line 151 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
static void 
copyin ( Type *t , void *src , void **dst ) 
{ 
uintptr size; 
void *p; 
Alg *alg; 
#line 158 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
size = t->size; 
alg = t->alg; 
#line 161 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
if ( size <= sizeof ( *dst ) ) 
alg->copy ( size , dst , src ) ; 
else { 
p = runtime·mal ( size ) ; 
alg->copy ( size , p , src ) ; 
*dst = p; 
} 
} 
#line 170 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
static void 
copyout ( Type *t , void **src , void *dst ) 
{ 
uintptr size; 
Alg *alg; 
#line 176 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
size = t->size; 
alg = t->alg; 
#line 179 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
if ( size <= sizeof ( *src ) ) 
alg->copy ( size , dst , src ) ; 
else 
alg->copy ( size , dst , *src ) ; 
} 
#pragma textflag NOSPLIT

void
runtime·typ2Itab(Type* t, InterfaceType* inter, Itab** cache, Itab* tab)
{
	tab = 0;
	FLUSH(&tab);
#line 186 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	tab = itab(inter, t, 0);
	runtime·atomicstorep(cache, tab);
	FLUSH(&tab);
}

#pragma textflag NOSPLIT
void
runtime·convT2I(Type* t, InterfaceType* inter, Itab** cache, byte* elem, Iface ret)
{
	ret.tab = 0;
	ret.data = 0;
	FLUSH(&ret);
#line 192 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	Itab *tab;

	tab = runtime·atomicloadp(cache);
	if(!tab) {
		tab = itab(inter, t, 0);
		runtime·atomicstorep(cache, tab);
	}
	ret.tab = tab;
	copyin(t, elem, &ret.data);
	FLUSH(&ret);
}

#pragma textflag NOSPLIT
void
runtime·convT2E(Type* t, byte* elem, Eface ret)
{
	ret.type = 0;
	ret.data = 0;
	FLUSH(&ret);
#line 205 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	ret.type = t;
	copyin(t, elem, &ret.data);
	FLUSH(&ret);
}

#line 210 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
static void assertI2Tret ( Type *t , Iface i , byte *ret ) ; 
#pragma textflag NOSPLIT

void
runtime·assertI2T(Type* t, Iface i, byte ret,  ...)
{
	ret = 0;
	FLUSH(&ret);
#line 213 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	assertI2Tret(t, i, &ret);
	FLUSH(&ret);
}

#line 217 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
static void 
assertI2Tret ( Type *t , Iface i , byte *ret ) 
{ 
Itab *tab; 
Eface err; 
#line 223 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
tab = i.tab; 
if ( tab == nil ) { 
runtime·newTypeAssertionError ( 
nil , nil , t->string , 
nil , &err ) ; 
runtime·panic ( err ) ; 
} 
if ( tab->type != t ) { 
runtime·newTypeAssertionError ( 
tab->inter->string , tab->type->string , t->string , 
nil , &err ) ; 
runtime·panic ( err ) ; 
} 
copyout ( t , &i.data , ret ) ; 
} 
#pragma textflag NOSPLIT

void
runtime·assertI2T2(Type* t, Iface i, byte ret,  ...)
{
	ret = 0;
	FLUSH(&ret);
#line 240 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	bool *ok;
	int32 wid;

	wid = t->size;
	ok = (bool*)(&ret + wid);

	if(i.tab == nil || i.tab->type != t) {
		*ok = false;
		runtime·memclr(&ret, wid);
		return;
	}

	*ok = true;
	copyout(t, &i.data, &ret);
	FLUSH(&ret);
}
void
runtime·assertI2TOK(Type* t, Iface i, bool ok)
{
	ok = 0;
	FLUSH(&ok);
#line 257 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	ok = i.tab!=nil && i.tab->type==t;
	FLUSH(&ok);
}

#line 261 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
static void assertE2Tret ( Type *t , Eface e , byte *ret ) ; 
#pragma textflag NOSPLIT

void
runtime·assertE2T(Type* t, Eface e, byte ret,  ...)
{
	ret = 0;
	FLUSH(&ret);
#line 264 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	assertE2Tret(t, e, &ret);
	FLUSH(&ret);
}

#line 268 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
static void 
assertE2Tret ( Type *t , Eface e , byte *ret ) 
{ 
Eface err; 
#line 273 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
if ( e.type == nil ) { 
runtime·newTypeAssertionError ( 
nil , nil , t->string , 
nil , &err ) ; 
runtime·panic ( err ) ; 
} 
if ( e.type != t ) { 
runtime·newTypeAssertionError ( 
nil , e.type->string , t->string , 
nil , &err ) ; 
runtime·panic ( err ) ; 
} 
copyout ( t , &e.data , ret ) ; 
} 
#pragma textflag NOSPLIT

void
runtime·assertE2T2(Type* t, Eface e, byte ret,  ...)
{
	ret = 0;
	FLUSH(&ret);
#line 289 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	bool *ok;
	int32 wid;

	wid = t->size;
	ok = (bool*)(&ret + wid);

	if(t != e.type) {
		*ok = false;
		runtime·memclr(&ret, wid);
		return;
	}

	*ok = true;
	copyout(t, &e.data, &ret);
	FLUSH(&ret);
}
void
runtime·assertE2TOK(Type* t, Eface e, bool ok)
{
	ok = 0;
	FLUSH(&ok);
#line 306 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	ok = t==e.type;
	FLUSH(&ok);
}
void
runtime·convI2E(Iface i, Eface ret)
{
	ret.type = 0;
	ret.data = 0;
	FLUSH(&ret);
#line 310 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	Itab *tab;

	ret.data = i.data;
	if((tab = i.tab) == nil)
		ret.type = nil;
	else
		ret.type = tab->type;
	FLUSH(&ret);
}
void
runtime·assertI2E(InterfaceType* inter, Iface i, Eface ret)
{
	ret.type = 0;
	ret.data = 0;
	FLUSH(&ret);
#line 320 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	Itab *tab;
	Eface err;

	tab = i.tab;
	if(tab == nil) {
		// explicit conversions require non-nil interface value.
		runtime·newTypeAssertionError(
			nil, nil, inter->string,
			nil, &err);
		runtime·panic(err);
	}
	ret.data = i.data;
	ret.type = tab->type;
	FLUSH(&ret);
}
void
runtime·assertI2E2(InterfaceType* inter, Iface i, Eface ret, bool ok)
{
	ret.type = 0;
	ret.data = 0;
	FLUSH(&ret);
	ok = 0;
	FLUSH(&ok);
#line 336 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	Itab *tab;

	USED(inter);
	tab = i.tab;
	if(tab == nil) {
		ret.type = nil;
		ok = 0;
	} else {
		ret.type = tab->type;
		ok = 1;
	}
	ret.data = i.data;
	FLUSH(&ret);
	FLUSH(&ok);
}
void
runtime·convI2I(InterfaceType* inter, Iface i, Iface ret)
{
	ret.tab = 0;
	ret.data = 0;
	FLUSH(&ret);
#line 351 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	Itab *tab;

	ret.data = i.data;
	if((tab = i.tab) == nil)
		ret.tab = nil;
	else if(tab->inter == inter)
		ret.tab = tab;
	else
		ret.tab = itab(inter, tab->type, 0);
	FLUSH(&ret);
}

#line 363 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
void 
runtime·ifaceI2I ( InterfaceType *inter , Iface i , Iface *ret ) 
{ 
Itab *tab; 
Eface err; 
#line 369 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
tab = i.tab; 
if ( tab == nil ) { 
#line 372 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
runtime·newTypeAssertionError ( 
nil , nil , inter->string , 
nil , &err ) ; 
runtime·panic ( err ) ; 
} 
ret->data = i.data; 
ret->tab = itab ( inter , tab->type , 0 ) ; 
} 
void
runtime·assertI2I(InterfaceType* inter, Iface i, Iface ret)
{
	ret.tab = 0;
	ret.data = 0;
	FLUSH(&ret);
#line 381 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	runtime·ifaceI2I(inter, i, &ret);
	FLUSH(&ret);
}
void
runtime·assertI2I2(InterfaceType* inter, Iface i, Iface ret, bool ok)
{
	ret.tab = 0;
	ret.data = 0;
	FLUSH(&ret);
	ok = 0;
	FLUSH(&ok);
#line 385 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	Itab *tab;

	tab = i.tab;
	if(tab != nil && (tab->inter == inter || (tab = itab(inter, tab->type, 1)) != nil)) {
		ret.data = i.data;
		ret.tab = tab;
		ok = 1;
	} else {
		ret.data = 0;
		ret.tab = 0;
		ok = 0;
	}
	FLUSH(&ret);
	FLUSH(&ok);
}

#line 400 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
void 
runtime·ifaceE2I ( InterfaceType *inter , Eface e , Iface *ret ) 
{ 
Type *t; 
Eface err; 
#line 406 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
t = e.type; 
if ( t == nil ) { 
#line 409 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
runtime·newTypeAssertionError ( 
nil , nil , inter->string , 
nil , &err ) ; 
runtime·panic ( err ) ; 
} 
ret->data = e.data; 
ret->tab = itab ( inter , t , 0 ) ; 
} 
#line 418 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
bool 
runtime·ifaceE2I2 ( InterfaceType *inter , Eface e , Iface *ret ) 
{ 
ret->tab = itab ( inter , e.type , 1 ) ; 
if ( ret->tab == nil ) 
return false; 
ret->data = e.data; 
return true; 
} 
void
reflect·ifaceE2I(InterfaceType* inter, Eface e, Iface* dst)
{
#line 428 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	runtime·ifaceE2I(inter, e, dst);
}
void
runtime·assertE2I(InterfaceType* inter, Eface e, Iface ret)
{
	ret.tab = 0;
	ret.data = 0;
	FLUSH(&ret);
#line 432 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	runtime·ifaceE2I(inter, e, &ret);
	FLUSH(&ret);
}
void
runtime·assertE2I2(InterfaceType* inter, Eface e, Iface ret, bool ok)
{
	ret.tab = 0;
	ret.data = 0;
	FLUSH(&ret);
	ok = 0;
	FLUSH(&ok);
#line 436 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	if(e.type == nil) {
		ok = 0;
		ret.data = nil;
		ret.tab = nil;
	} else if((ret.tab = itab(inter, e.type, 1)) == nil) {
		ok = 0;
		ret.data = nil;
	} else {
		ok = 1;
		ret.data = e.data;
	}
	FLUSH(&ret);
	FLUSH(&ok);
}
void
runtime·assertE2E(InterfaceType* inter, Eface e, Eface ret)
{
	ret.type = 0;
	ret.data = 0;
	FLUSH(&ret);
#line 450 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	Type *t;
	Eface err;

	t = e.type;
	if(t == nil) {
		// explicit conversions require non-nil interface value.
		runtime·newTypeAssertionError(
			nil, nil, inter->string,
			nil, &err);
		runtime·panic(err);
	}
	ret = e;
	FLUSH(&ret);
}
void
runtime·assertE2E2(InterfaceType* inter, Eface e, Eface ret, bool ok)
{
	ret.type = 0;
	ret.data = 0;
	FLUSH(&ret);
	ok = 0;
	FLUSH(&ok);
#line 465 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	USED(inter);
	ret = e;
	ok = e.type != nil;
	FLUSH(&ret);
	FLUSH(&ok);
}

#line 471 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
static uintptr 
ifacehash1 ( void *data , Type *t , uintptr h ) 
{ 
Alg *alg; 
uintptr size; 
Eface err; 
#line 478 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
if ( t == nil ) 
return 0; 
#line 481 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
alg = t->alg; 
size = t->size; 
if ( alg->hash == runtime·nohash ) { 
#line 486 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
runtime·newErrorString ( runtime·catstring ( runtime·gostringnocopy ( ( byte* ) "hash of unhashable type " ) , *t->string ) , &err ) ; 
runtime·panic ( err ) ; 
} 
if ( size <= sizeof ( data ) ) 
alg->hash ( &h , size , &data ) ; 
else 
alg->hash ( &h , size , data ) ; 
return h; 
} 
#line 496 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
uintptr 
runtime·ifacehash ( Iface a , uintptr h ) 
{ 
if ( a.tab == nil ) 
return h; 
return ifacehash1 ( a.data , a.tab->type , h ) ; 
} 
#line 504 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
uintptr 
runtime·efacehash ( Eface a , uintptr h ) 
{ 
return ifacehash1 ( a.data , a.type , h ) ; 
} 
#line 510 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
static bool 
ifaceeq1 ( void *data1 , void *data2 , Type *t ) 
{ 
uintptr size; 
Alg *alg; 
Eface err; 
bool eq; 
#line 518 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
alg = t->alg; 
size = t->size; 
#line 521 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
if ( alg->equal == runtime·noequal ) { 
#line 524 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
runtime·newErrorString ( runtime·catstring ( runtime·gostringnocopy ( ( byte* ) "comparing uncomparable type " ) , *t->string ) , &err ) ; 
runtime·panic ( err ) ; 
} 
#line 528 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
eq = 0; 
if ( size <= sizeof ( data1 ) ) 
alg->equal ( &eq , size , &data1 , &data2 ) ; 
else 
alg->equal ( &eq , size , data1 , data2 ) ; 
return eq; 
} 
#line 536 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
bool 
runtime·ifaceeq_c ( Iface i1 , Iface i2 ) 
{ 
if ( i1.tab != i2.tab ) 
return false; 
if ( i1.tab == nil ) 
return true; 
return ifaceeq1 ( i1.data , i2.data , i1.tab->type ) ; 
} 
#line 546 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"
bool 
runtime·efaceeq_c ( Eface e1 , Eface e2 ) 
{ 
if ( e1.type != e2.type ) 
return false; 
if ( e1.type == nil ) 
return true; 
return ifaceeq1 ( e1.data , e2.data , e1.type ) ; 
} 
void
runtime·ifaceeq(Iface i1, Iface i2, bool ret)
{
	ret = 0;
	FLUSH(&ret);
#line 556 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	ret = runtime·ifaceeq_c(i1, i2);
	FLUSH(&ret);
}
void
runtime·efaceeq(Eface e1, Eface e2, bool ret)
{
	ret = 0;
	FLUSH(&ret);
#line 560 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	ret = runtime·efaceeq_c(e1, e2);
	FLUSH(&ret);
}
void
runtime·ifacethash(Iface i1, uint32 ret)
{
	ret = 0;
	FLUSH(&ret);
#line 564 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	Itab *tab;

	ret = 0;
	tab = i1.tab;
	if(tab != nil)
		ret = tab->type->hash;
	FLUSH(&ret);
}
void
runtime·efacethash(Eface e1, uint32 ret)
{
	ret = 0;
	FLUSH(&ret);
#line 573 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	Type *t;

	ret = 0;
	t = e1.type;
	if(t != nil)
		ret = t->hash;
	FLUSH(&ret);
}
void
reflect·unsafe_Typeof(Eface e, Eface ret)
{
	ret.type = 0;
	ret.data = 0;
	FLUSH(&ret);
#line 582 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	if(e.type == nil) {
		ret.type = nil;
		ret.data = nil;
	} else {
		ret = *(Eface*)(e.type);
	}
	FLUSH(&ret);
}
void
reflect·unsafe_New(Type* t, byte* ret)
{
	ret = 0;
	FLUSH(&ret);
#line 591 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	ret = runtime·cnew(t);
	FLUSH(&ret);
}
void
reflect·unsafe_NewArray(Type* t, intgo n, byte* ret)
{
	ret = 0;
	FLUSH(&ret);
#line 595 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	ret = runtime·cnewarray(t, n);
	FLUSH(&ret);
}
void
reflect·typelinks(Slice ret)
{
	ret.array = 0;
	ret.len = 0;
	ret.cap = 0;
	FLUSH(&ret);
#line 599 "/home/14/ren/source/golang/go/src/pkg/runtime/iface.goc"

	extern Type *typelink[], *etypelink[];
	static int32 first = 1;
	ret.array = (byte*)typelink;
	ret.len = etypelink - typelink;
	ret.cap = ret.len;
	FLUSH(&ret);
}
