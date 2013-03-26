//ELECTRIC IMP BUZZER
wd < - OutputPort("watchdog");
stat < - OutputPort("statistics");

class input extends InputPort
{
    name = "Buzzer control"
           type = "number"

                  function set(value)
    {
        //send the value to the server
        server.show(value);
        if (value == 1) accendi();
    }
}

function accendi()
{
    server.log("Suonaaaaa");
    stat.set(1);

    for (local i = 0; i < 80; i++)
    {
        hardware.pin1.write(1);
        imp.sleep(0.001);
        hardware.pin1.write(0);
        imp.sleep(0.002);
    }

    for (local i = 0; i < 100; i++)
    {
        hardware.pin1.write(1);
        imp.sleep(0.001);
        hardware.pin1.write(0);
        imp.sleep(0.001);
    }
}


function watchdog()
{
    server.log("watchdog");
    imp.wakeup(5 * 60, watchdog);
    wd.set(0);
}

watchdog();

hardware.pin1.configure(DIGITAL_OUT);
local input = input();
imp.configure("Buzzer", [input], [stat, wd]);