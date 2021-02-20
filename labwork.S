  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
  .data
  delayconst: .word 3809
  .text
  .global time2string
  .global delay
hexasc:	
	andi 	$t0,$a0,0xF	# t0 = a0,3:0

	slti 	$t1,$t0,10	# if t0 < 10, t1 = 1 else t1 = 0
	beq 	$t1,$0,else	# if !(t0 < 10) jump to else
	nop
	
	addi 	$t0,$t0,0x30	# t0 += 0x30
	
	j 	done
	nop
else:
	addi 	$t0,$t0,0x37	# t0 += 0x37
done:
	move 	$v0,$t0		# v0 = t0
	jr 	$ra		# return v0
	nop
	###############################################	
delay:	
	lw	$t2,delayconst
delaywhile:
	slt	$t1,$0,$a0		# ms > 0
	beq	$t1,$0,delaywhiledone	#
	nop
	addi	$a0,$a0,-1	# ms = ms - 1
	
	add	$t0,$0,$0	# i = 0
delayfor:
	slt	$t1,$t0,$t2	# i < delayconst
	beq	$t1,$0,delayfordone
	nop
	addi	$t0,$t0,1	# i = i + 1
	
	j	delayfor
	nop
delayfordone:

	j	delaywhile
	nop
delaywhiledone:
 	jr 	$ra
 	nop
 	###############################################	
time2string:
	PUSH	$ra		# saving return address to main since this will be overwritten when calling hexasc
	PUSH	$s0		
	PUSH	$s1		
	move	$s0,$a0		# stores address to write to
	move	$s1,$a1		# stores the NBCD coded argument
	
	# store minute digit 1
	srl	$a0,$s1,12
	andi	$a0,$a0,0xf
	jal	hexasc
	sb	$v0,0($s0)
	
	# store minute digit 2
	srl	$a0,$s1,8
	andi	$a0,$a0,0xf
	jal	hexasc
	sb	$v0,1($s0)
	
	# store ":"
	addi	$t0,$0,0x3a
	sb	$t0,2($s0)
	
	# store second digit 1
	srl	$a0,$s1,4
	andi	$a0,$a0,0xf
	jal	hexasc
	sb	$v0,3($s0)
	
	# store second digit 2
	andi	$a0,$s1,0xf
	jal	hexasc
	sb	$v0,4($s0)
	
	# store null
	sb	$0,5($s0)
	
	POP	$s1
	POP	$s0
	POP	$ra
	jr	$ra		# return to caller
	nop
	###############################################