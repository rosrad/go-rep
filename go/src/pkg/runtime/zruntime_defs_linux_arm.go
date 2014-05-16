// auto generated by go tool dist

package runtime
import "unsafe"
var _ unsafe.Pointer

type lock struct {
	key	uint32
}

type note struct {
	key	uint32
}

type _string struct {
	str	*uint8
	len	int32
}

type funcval struct {
	fn	func()
}

type iface struct {
	tab	*itab
	data	unsafe.Pointer
}

type eface struct {
	_type	*_type
	data	unsafe.Pointer
}

type _complex64 struct {
	real	float32
	imag	float32
}

type _complex128 struct {
	real	float64
	imag	float64
}

type slice struct {
	array	*uint8
	len	uint32
	cap	uint32
}

type gobuf struct {
	sp	uint32
	pc	uint32
	g	*g
	ctxt	unsafe.Pointer
	ret	uint32
	lr	uint32
}

type gcstats struct {
	nhandoff	uint64
	nhandoffcnt	uint64
	nprocyield	uint64
	nosyield	uint64
	nsleep	uint64
}

type libcall struct {
	fn	func(unsafe.Pointer)
	n	uint32
	args	unsafe.Pointer
	r1	uint32
	r2	uint32
	err	uint32
}

type wincallbackcontext struct {
	gobody	unsafe.Pointer
	argsize	uint32
	restorestack	uint32
	cleanstack	uint8
}

type g struct {
	stackguard0	uint32
	stackbase	uint32
	panicwrap	uint32
	_defer	*_defer
	_panic	*_panic
	sched	gobuf
	syscallstack	uint32
	syscallsp	uint32
	syscallpc	uint32
	syscallguard	uint32
	stackguard	uint32
	stack0	uint32
	stacksize	uint32
	param	unsafe.Pointer
	status	int16
	goid	int64
	waitsince	int64
	waitreason	*int8
	schedlink	*g
	ispanic	uint8
	issystem	uint8
	isbackground	uint8
	preempt	uint8
	paniconfault	uint8
	raceignore	int8
	m	*m
	lockedm	*m
	sig	int32
	writenbuf	int32
	writebuf	*uint8
	sigcode0	uint32
	sigcode1	uint32
	sigpc	uint32
	gopc	uint32
	racectx	uint32
	end	[0]uint32
}

type m struct {
	g0	*g
	moreargp	unsafe.Pointer
	morebuf	gobuf
	moreframesize	uint32
	moreargsize	uint32
	cret	uint32
	procid	uint64
	gsignal	*g
	tls	[4]uint32
	mstartfn	func()
	curg	*g
	caughtsig	*g
	p	*p
	nextp	*p
	id	int32
	mallocing	int32
	throwing	int32
	gcing	int32
	locks	int32
	dying	int32
	profilehz	int32
	helpgc	int32
	spinning	uint8
	blocked	uint8
	fastrand	uint32
	ncgocall	uint64
	ncgo	int32
	cgomal	*cgomal
	park	note
	alllink	*m
	schedlink	*m
	machport	uint32
	mcache	*mcache
	stackinuse	int32
	stackcachepos	uint32
	stackcachecnt	uint32
	stackcache	[32]unsafe.Pointer
	lockedg	*g
	createstack	[32]uint32
	freglo	[16]uint32
	freghi	[16]uint32
	fflag	uint32
	locked	uint32
	nextwaitm	*m
	waitsema	uint32
	waitsemacount	uint32
	waitsemalock	uint32
	gcstats	gcstats
	needextram	uint8
	traceback	uint8
	waitunlockf	func(*g, unsafe.Pointer) uint8
	waitlock	unsafe.Pointer
	forkstackguard	uint32
	end	[0]uint32
}

type p struct {
	lock
	id	int32
	status	uint32
	link	*p
	schedtick	uint32
	syscalltick	uint32
	m	*m
	mcache	*mcache
	deferpool	[5]*_defer
	goidcache	uint64
	goidcacheend	uint64
	runqhead	uint32
	runqtail	uint32
	runq	[256]*g
	gfree	*g
	gfreecnt	int32
	pad	[64]uint8
}

type stktop struct {
	stackguard	uint32
	stackbase	uint32
	gobuf	gobuf
	argsize	uint32
	panicwrap	uint32
	argp	*uint8
	_panic	uint8
	malloced	uint8
}

type sigtab struct {
	flags	int32
	name	*int8
}

type _func struct {
	entry	uint32
	nameoff	int32
	args	int32
	frame	int32
	pcsp	int32
	pcfile	int32
	pcln	int32
	npcdata	int32
	nfuncdata	int32
}

type itab struct {
	inter	*interfacetype
	_type	*_type
	link	*itab
	bad	int32
	unused	int32
	fun	[0]func()
}

type timers struct {
	lock
	timerproc	*g
	sleeping	uint8
	rescheduling	uint8
	waitnote	note
	t	**timer
	len	int32
	cap	int32
}

type timer struct {
	i	int32
	when	int64
	period	int64
	fv	*funcval
	arg	eface
}

type lfnode struct {
	next	*lfnode
	pushcnt	uint32
}

type parfor struct {
	body	func(*parfor, uint32)
	done	uint32
	nthr	uint32
	nthrmax	uint32
	thrseq	uint32
	cnt	uint32
	ctx	unsafe.Pointer
	wait	uint8
	thr	*parforthread
	pad	uint32
	nsteal	uint64
	nstealcnt	uint64
	nprocyield	uint64
	nosyield	uint64
	nsleep	uint64
}

type cgomal struct {
	next	*cgomal
	alloc	unsafe.Pointer
}

type debugvars struct {
	allocfreetrace	int32
	efence	int32
	gctrace	int32
	gcdead	int32
	scheddetail	int32
	schedtrace	int32
}

var precisestack	uint8
var copystack	uint8
type alg struct {
	hash	func(*uint32, uint32, unsafe.Pointer)
	equal	func(*uint8, uint32, unsafe.Pointer, unsafe.Pointer)
	print	func(uint32, unsafe.Pointer)
	copy	func(uint32, unsafe.Pointer, unsafe.Pointer)
}

var algarray	[22]alg
var startup_random_data	*uint8
var startup_random_data_len	uint32
type _defer struct {
	siz	int32
	special	uint8
	argp	*uint8
	pc	*uint8
	fn	*funcval
	link	*_defer
	args	[1]unsafe.Pointer
}

type _panic struct {
	arg	eface
	stackbase	uint32
	link	*_panic
	_defer	*_defer
	recovered	uint8
	aborted	uint8
}

type stkframe struct {
	fn	*_func
	pc	uint32
	lr	uint32
	sp	uint32
	fp	uint32
	varp	*uint8
	argp	*uint8
	arglen	uint32
}

var emptystring	string
var zerobase	uint32
var allg	**g
var allglen	uint32
var lastg	*g
var allm	*m
var allp	**p
var gomaxprocs	int32
var needextram	uint32
var panicking	uint32
var goos	*int8
var ncpu	int32
var iscgo	uint8
var sysargs	func(int32, **uint8)
var maxstring	uint32
var hchansize	uint32
var cpuid_ecx	uint32
var cpuid_edx	uint32
var debug	debugvars
var maxstacksize	uint32
var blockprofilerate	int64
var worldsema	uint32
var nan	float64
var posinf	float64
var neginf	float64
type mlink struct {
	next	*mlink
}

type fixalloc struct {
	size	uint32
	first	func(unsafe.Pointer, *uint8)
	arg	unsafe.Pointer
	list	*mlink
	chunk	*uint8
	nchunk	uint32
	inuse	uint32
	stat	*uint64
}

type _1_ struct {
	size	uint32
	nmalloc	uint64
	nfree	uint64
}

type mstats struct {
	alloc	uint64
	total_alloc	uint64
	sys	uint64
	nlookup	uint64
	nmalloc	uint64
	nfree	uint64
	heap_alloc	uint64
	heap_sys	uint64
	heap_idle	uint64
	heap_inuse	uint64
	heap_released	uint64
	heap_objects	uint64
	stacks_inuse	uint64
	stacks_sys	uint64
	mspan_inuse	uint64
	mspan_sys	uint64
	mcache_inuse	uint64
	mcache_sys	uint64
	buckhash_sys	uint64
	gc_sys	uint64
	other_sys	uint64
	next_gc	uint64
	last_gc	uint64
	pause_total_ns	uint64
	pause_ns	[256]uint64
	numgc	uint32
	enablegc	uint8
	debuggc	uint8
	by_size	[67]_1_
}

var memstats	mstats
var class_to_size	[67]int32
var class_to_allocnpages	[67]int32
var size_to_class8	[129]int8
var size_to_class128	[249]int8
type mcachelist struct {
	list	*mlink
	nlist	uint32
}

type mcache struct {
	next_sample	int32
	local_cachealloc	int32
	tiny	*uint8
	tinysize	uint32
	alloc	[67]*mspan
	free	[67]mcachelist
	local_nlookup	uint32
	local_largefree	uint32
	local_nlargefree	uint32
	local_nsmallfree	[67]uint32
}

type mtypes struct {
	compression	uint8
	data	uint32
}

type special struct {
	next	*special
	offset	uint16
	kind	uint8
}

type specialfinalizer struct {
	special
	fn	*funcval
	nret	uint32
	fint	*_type
	ot	*ptrtype
}

type specialprofile struct {
	special
	b	*bucket
}

type mspan struct {
	next	*mspan
	prev	*mspan
	start	uint32
	npages	uint32
	freelist	*mlink
	sweepgen	uint32
	ref	uint16
	sizeclass	uint8
	incache	uint8
	state	uint8
	needzero	uint8
	elemsize	uint32
	unusedsince	int64
	npreleased	uint32
	limit	*uint8
	types	mtypes
	speciallock	lock
	specials	*special
	freebuf	*mlink
}

type mcentral struct {
	lock
	sizeclass	int32
	nonempty	mspan
	empty	mspan
	nfree	int32
}

type _2_ struct {
	mcentral
	pad	[32]uint8
}

type mheap struct {
	lock
	free	[128]mspan
	freelarge	mspan
	busy	[128]mspan
	busylarge	mspan
	allspans	**mspan
	sweepspans	**mspan
	nspan	uint32
	nspancap	uint32
	sweepgen	uint32
	sweepdone	uint32
	spans	**mspan
	spans_mapped	uint32
	bitmap	*uint8
	bitmap_mapped	uint32
	arena_start	*uint8
	arena_used	*uint8
	arena_end	*uint8
	arena_reserved	uint8
	central	[67]_2_
	spanalloc	fixalloc
	cachealloc	fixalloc
	specialfinalizeralloc	fixalloc
	specialprofilealloc	fixalloc
	speciallock	lock
	largefree	uint64
	nlargefree	uint64
	nsmallfree	[67]uint64
}

var checking	int32
var fingwait	uint8
var fingwake	uint8
type bitvector struct {
	n	int32
	data	*uint32
}

type stackmap struct {
	n	int32
	nbit	int32
	data	[0]uint32
}

type _type struct {
	size	uint32
	hash	uint32
	_unused	uint8
	align	uint8
	fieldalign	uint8
	kind	uint8
	alg	*alg
	gc	unsafe.Pointer
	_string	*string
	x	*uncommontype
	ptrto	*_type
	zero	*uint8
}

type method struct {
	name	*string
	pkgpath	*string
	mtyp	*_type
	typ	*_type
	ifn	func()
	tfn	func()
}

type uncommontype struct {
	name	*string
	pkgpath	*string
	mhdr	[]byte
	m	[0]method
}

type imethod struct {
	name	*string
	pkgpath	*string
	_type	*_type
}

type interfacetype struct {
	_type
	mhdr	[]byte
	m	[0]imethod
}

type maptype struct {
	_type
	key	*_type
	elem	*_type
	bucket	*_type
	hmap	*_type
}

type chantype struct {
	_type
	elem	*_type
	dir	uint32
}

type slicetype struct {
	_type
	elem	*_type
}

type functype struct {
	_type
	dotdotdot	uint8
	in	[]byte
	out	[]byte
}

type ptrtype struct {
	_type
	elem	*_type
}

type bucket struct {
	tophash	[8]uint8
	overflow	*bucket
	data	[1]uint64
}

type hmap struct {
	count	uint32
	flags	uint32
	hash0	uint32
	b	uint8
	keysize	uint8
	valuesize	uint8
	bucketsize	uint16
	buckets	*uint8
	oldbuckets	*uint8
	nevacuate	uint32
}

type hiter struct {
	key	*uint8
	value	*uint8
	t	*maptype
	h	*hmap
	buckets	*uint8
	bptr	*bucket
	offset	uint8
	done	uint8
	b	uint8
	bucket	uint32
	i	uint32
	check_bucket	int32
}

type sudog struct {
	g	*g
	selectdone	*uint32
	link	*sudog
	releasetime	int64
	elem	*uint8
}

type waitq struct {
	first	*sudog
	last	*sudog
}

type hchan struct {
	qcount	uint32
	dataqsiz	uint32
	elemsize	uint16
	pad	uint16
	closed	uint8
	elemtype	*_type
	sendx	uint32
	recvx	uint32
	recvq	waitq
	sendq	waitq
	lock
}

type scase struct {
	sg	sudog
	_chan	*hchan
	pc	*uint8
	kind	uint16
	so	uint16
	receivedp	*uint8
}

type _select struct {
	tcase	uint16
	ncase	uint16
	pollorder	*uint16
	lockorder	**hchan
	scase	[1]scase
}

























































type sched struct {
	lock
	goidgen	uint64
	midle	*m
	nmidle	int32
	nmidlelocked	int32
	mcount	int32
	maxmcount	int32
	pidle	*p
	npidle	uint32
	nmspinning	uint32
	runqhead	*g
	runqtail	*g
	runqsize	int32
	gflock	lock
	gfree	*g
	gcwaiting	uint32
	stopwait	int32
	stopnote	note
	sysmonwait	uint32
	sysmonnote	note
	lastpoll	uint64
	profilehz	int32
}

var m0	m
var g0	g
var extram	*m
var newprocs	int32
var allglock	lock
var allgcap	uint32
var scavenger	funcval
var initdone	funcval
var _cgo_thread_start	func(unsafe.Pointer)
type cgothreadstart struct {
	m	*m
	g	*g
	tls	*uint32
	fn	func()
}

type _3_ struct {
	lock
	fn	func(*uint32, int32)
	hz	int32
	pcbuf	[100]uint32
}

var prof	_3_
var etext	[0]uint8
type pdesc struct {
	schedtick	uint32
	schedwhen	int64
	syscalltick	uint32
	syscallwhen	int64
}

var externalthreadhandlerp	uint32
var experiment	[0]int8






























type parforthread struct {
	pos	uint64
	nsteal	uint64
	nstealcnt	uint64
	nprocyield	uint64
	nosyield	uint64
	nsleep	uint64
	pad	[32]uint8
}

