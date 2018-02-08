.name "gomme"
.comment "on efface tout !"

start:	sti r1, %:live, %1
		sti r1, %:restevivant, %1
		sti r2, %:id, %0
		sti r1, %:loadattack, %1
		sti r1, %:attack, %1
		and r1, %0, r1
		fork %:live
		ld %200, r5
		ld %4, r6
		add r8, r9, r10
		zjmp %:restevivant

restevivant: 	live %1
				fork %:attack
				add r8, r9, r10
				zjmp %:loadattack

loadattack:	live %1
			fork %:prepatt
			add r8, r9, r10
			zjmp %:loadattack

live:	live %1
		zjmp %:live

id: live %0

prepatt:	ld %:id, r5
			ld %4, r6
			add r8, r9, r10
			zjmp %:attack

attack:	live %1
		sti r2, r5, %10
		add r5, r6, r5
		sti r5, r2, %:id
		add r8, r9, r10
		zjmp %:attack
		
