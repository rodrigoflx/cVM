# cVM
A simple C Bytecode Interpreter/Virtual Machine, based on the one made by Felix Angell

> Instruction Set
> 0. HALT
> 1. JUMP
> 2. FJUMP
> 3. CALL
> 4. RET
> 5. PUSH
> 6. POP
> 7. LOAD
> 8. STORE
> 9. MOV
> 10. SET
> 11. ADD
> 12. SUB
> 13. MUL
> 14. DIV
> 15. AND
> 16. OR
> 17. NOT
> 18. PRINT

## Example Program
`	PUSH 6
	PUSH 7
	ADD
	PRINT`
### Translation
	5 6
	5 7
	11
	18
	
