wd < - OutputPort("watchdog");
stat < - OutputPort("statistics");

class input extends InputPort
{
    name = "Relay control"
           type = "number"

                  function set(value)
    {
        //send the value to the server
        server.show(value);
        if (value == 1) accendi();
        if (value == 0) spegni();
    }
}

function accendi()
{
    server.log("accendo la corrente");
    stat.set(1);
    hardware.pin1.write(0);
}

function spegni()
{
    server.log("spengo la corrente");
    stat.set(0);
    hardware.pin1.write(1);
}

function watchdog()
{
    server.log("watchdog");
    imp.wakeup(5 * 60, watchdog);
    wd.set(0);
}

watchdog();

hardware.pin1.configure(DIGITAL_OUT);
hardware.pin1.write(1);

local input = input();

imp.configure("Relay", [input], [stat, wd]);