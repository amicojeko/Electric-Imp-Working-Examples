// Electric Imp
// Sensore di distanza ad infrarossi
 
// pin 8 is an analog input (we read the voltage on the pin with an ADC)
// analog inputs read a value between 0 (for 0 V) and 65,535 (16-bit ADC) for the imp's supply voltage, which should be 3.3V
hardware.pin1.configure(ANALOG_IN);
 
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
 
function checkSensor() {
    // leggo il valore del pin1
    local rawValue = hardware.pin1.read();
    // calcolo la differenza tra il valore letto e l'ultima lettura
    local delta = math.abs(rawValue - lastRawValue);
    // in questo modo filtro tutte le microvariazioni dovute all'imprecisioni della lettua
    if (delta > 150) {
        local potValue = rawValue / 65535.0;

        if (potValue == 1) {
        	server.log("Distante");
        	// Tutto quello che avviene qui, avviene se non ci sono ostacoli rilevati
        	server.show(0);
        	my_output.set(0);
        }else{
        	server.log("Vicino");
        	// Tutto quello che avviene qui, avviene se c'è qualcosa davanti al sensore
        	server.show(1);
        	my_output.set(1);
        }

        lastRawValue = rawValue;
    }
    imp.wakeup(0.01, checkSensor);
}


server.log("Distance Sensor Started");
imp.configure("Infrared distance sensor", [], [my_output]);
checkSensor();
 
//EOF