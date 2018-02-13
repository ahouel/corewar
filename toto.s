.name "toto"
.comment "le seul et unique"

start:	sti r1, %:live, %1
		sti r1, %:affi, %1
		sti r1, %:affi2, %1
		sti r1, %:affi3, %1
		and r1, %0, r1
		fork %:affi
		zjmp %:live

live:	live %1
		zjmp %:live

affi:	live %1
		ld %78, r2
		aff r2
		ld %111, r2
		aff r2
		ld %117, r2
		aff r2
		ld %115, r2
		aff r2
		ld %32, r2
		aff r2

affi2:	live %1
		ld %115, r2
		aff r2
		ld %111, r2
		aff r2
		ld %109, r2
		aff r2
		aff r2
		ld %101, r2
		aff r2
		ld %115, r2
		aff r2
		ld %32, r2
		aff r2

affi3:	live %1
		ld %98, r2
		aff r2
		ld %101, r2
		aff r2
		ld %97, r2
		aff r2
		ld %117, r2
		aff r2
		ld %120, r2
		aff r2
		ld %46, r2
		aff r2

