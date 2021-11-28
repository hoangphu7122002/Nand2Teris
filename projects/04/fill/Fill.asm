// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

	@KBD
	D = A //check pointer index
	@const
	M = D //save value of Keyboard
(MAIN)
	@SCREEN
	D = A
	@R0
	M = D
(CHECK)
	@KBD
	D = M
	@BLACK
	D; JGT // if press then black => jump BLACK
	@WHITE
	0; JMP //else case
(BLACK)
	@R1
	M = -1 // (-1 = 1111 1111 1111 1111)
	@CHANGE
	0; JMP
(WHITE)
	@R1
	M = 0 // (0 = 0000 0000 0000 0000)
	@CHANGE
	0; JMP

(CHANGE)
	@R1
	D = M // set value is 0 or 1 depend on D
	
	@R0
	A = M
	M = D // fill a space with color which is chosen
	
	@R0
	M = M + 1 //next line
	D = M
	@const
	D = D - M
	
	@CHANGE
	D; JLT
	
	@MAIN
	0; JMP

//peseudo code
	