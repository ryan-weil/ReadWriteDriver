.data

.code
     
FixRegister proc
	mov r12, 0                ; Fixes a register in xxxSetSysColors to prevent it from messing system colors up
    ret
FixRegister endp
     
end