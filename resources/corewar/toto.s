.name "aure"
.comment "salut"

live %-1
ld 10, r9
st r2, r3
add r1, r2, r3
sub r3, r2, r4
and r1, r4, r2
or r3, r4, r7
xor r1, r8, r7
zjmp %42
ldi r2, %42, r4
sti r3, r4, %45
live %-1
fork %42
lld %50, r2
live %-1
lldi r1, %60, r8
lfork %800
aff r2
