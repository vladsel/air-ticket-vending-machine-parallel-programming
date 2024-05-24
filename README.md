# lab2_OS
(23.05.2022)
Develop a program that simulates the operation of a given object, using means for process access to shared resources synchronization. The device being modeled and the means of synchronizing processes are determined by the task variant. 2. Provide visualization of the model's operation with a visual demonstration results. 3. Analyze and explain the obtained results. For results work to provide conclusions about the used synchronization tools.
Modeling object: Air ticket vending machine.
The machine accepts money (there is only one specified denomination - 1 hryvnia) 
and issues change in coins worth up to UAH 1. (1, 2, 5, 10, 25, 50 copies). Surrender amount 
is calculated The initial number of coins of each denomination is given by i is: 
1 cop. – 50 pcs., 2 kop. - 25 pcs., 
5 kopecks – 20 pcs., 10 kopecks. - 15 pcs., 
25 kopecks – 10 pcs., 50 kopecks. - 5 pcs., 
Entering a sales request is carried out by selecting a specific item menu: 
0 - turn on the machine; 1 – buy a ticket to Kyiv worth 28 kopecks;
2 – a ticket to Monte Carlo worth 37 kopecks; 3 – a ticket to London worth 50 kopecks;
4 – a ticket to Berlin worth 77 kopecks; 5 – a ticket to Paris worth 91 kopecks.
If it is possible to issue change, the program forms the required set of coins for 
delivery (also adjusts the bank of coins) and generates a signal for delivery. If needed 
bills for delivery are not available, a corresponding message is generated. Requirements for 
disbursement of money is received after the next session of sale or rejection.

The number of terminals and processes: The model of the automaton should be presented in the form 
of two interacting processes A and B. Process A determines the receipt facts 
requirements for sale and the required surrender amount. Process B is waiting for the moment to appear
of the need to issue change and, if the amount of change is known, determines the amount and 
denominations of the required coins or the impossibility of issuance.

Synchronization tools: To organize access to shared resources, use semaphores.
