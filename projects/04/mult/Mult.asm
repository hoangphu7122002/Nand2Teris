// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

//---------------Peseudo Code-------------

// int i = 1;
// int mul = 0;
// while (i <= b){
//   mul = mul + a;
//   i++;
// }

//----------------------------------------

//-----------------CODE-------------------

	//Initialize
	@i
	M = 1
	@mul
	M = 0
	
(while)
	//while (i <= b)
	@R1
	D = M
	@i
	D = M - D
	@exit
	D; JGT //i > b => out loop

	//looping
	@R0
	D = M
	@mul
	M = D + M
	@i
	M = M + 1
	
	@while //return loop
	0; JMP

(exit)
	@mul
	D = M
	@2
	M = D
//end
	@22
	0; JMP
//----------------------------------------

