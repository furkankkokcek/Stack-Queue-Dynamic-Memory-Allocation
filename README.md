# Stack, Queue and Dynamic Memory Allocation
This stack and queue structures are used on basic client-server
simulation.The simulation has at least client and only one server.Clients have
stack and queue for process or interrupt.Server also has two structures and
execute the process or interrupt for it's current situation.At this
simulation,stack structure is more priority than queue structure.For
example,when we used send command or execute command,algorithm firstly
checks the stack structure if it is not available than uses queue structure.If
there are some errors in the executing or sending part, algorithm will save the
type of the error to log file of each client and server.
