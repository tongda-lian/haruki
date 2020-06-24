Background
	
	This is a simple deep leaning case with 1 input layer (2 does), 1 hidden layer 
	(5 nodes) and 1 output layer (1 node). This case is to train a model to simulate 
	the OR gate, which has 2 input and 1 output.
	Train set and validation set is given and can be edited. 
	Since this is the first demonstration of deep learning by the author, there could
	 be bugs or even something wrong about the derivation of equations. 
	You are welcomed to discuss. 
	
Compile
	$ g++ Train_OR.cpp -o train.out
	$ g++ Validation.cpp -o validate.out 

Usage
	$ ./train.out
	$ ./validate.out

Maintainer
	
	LIAN Tongda (lian@sim.gsic.titech.ac.jp)
	from Tokyo Institute of Technology

Contributing

	Almost everything is in the main function now.
	If the function of multiplication of matrics is realized, 
	at least, it will be easier to read.

Acknowledgement

	I would like to give special thanks to Professor Yokota from Tokyo Tech,
	who gave us the lecture of High Performance Scientific Computing,
	which inspired me to learn about deep learning.
	
