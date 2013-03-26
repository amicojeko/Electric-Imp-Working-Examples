// Electric Imp
// Interruttore a mercurio

hardware.pin2.configure(DIGITAL_OUT);

// you can read the imp's input voltage at any time with:
local voltage = hardware.voltage();
server.log(format("Running at %.2f V", voltage));

// We use this variable to create a "dead band" around the current value on the potentiometer
// this can be used to decrease the rate at which we push data to planner by discarding values that
// are the same as the last one
local lastRawValue = 0;

// creo la porta di output
local my_output = OutputPort("infrared");

server.log("Hardware Configured");

function changed()
{
    // Handle change of pin state
    server.show(hardware.pin1.read());
    server.log(hardware.pin1.read());
    my_output.set(hardware.pin1.read());
    hardware.pin2.write(hardware.pin1.read());
}

hardware.pin1.configure(DIGITAL_IN_PULLUP, changed);


server.log("Interruttore a Mercurio pronto");
imp.configure("Interruttore a mercurio", [], [my_output]);
//EOF