#include <Arduino.h>
#include <ThreadedGSM.h>

#define SerialDebug Serial
#define SerialModem Serial
#define THREADEDGSM_DEBUG SerialDebug

ThreadedGSM SIM900(SerialModem);

void clock(ThreadedGSM &modem, ThreadedGSM::NetworkTime &Time) {
  SerialDebug.print("Modem Time: ");
  SerialDebug.print(Time.day);
  SerialDebug.print("/");
  SerialDebug.print(Time.month);
  SerialDebug.print("/");
  SerialDebug.print(Time.year);
  SerialDebug.print(" ");
  SerialDebug.print(Time.hour);
  SerialDebug.print(":");
  SerialDebug.print(Time.minute);
  SerialDebug.print(":");
  SerialDebug.println(Time.second);
}

void signal(ThreadedGSM &modem, ThreadedGSM::SignalLevel &Signal) {
  SerialDebug.print("Modem signal: Dbm:");
  SerialDebug.print(Signal.Dbm);
  SerialDebug.print(" value: ");
  SerialDebug.println(Signal.Value);
}

void sms(ThreadedGSM &modem, String &Msg) {
  SerialDebug.print("Received SMS: ");
  SerialDebug.println(Msg);
}

void startup(ThreadedGSM &modem) { SerialDebug.print("Ready"); }

void setup() {
  SerialDebug.begin(115200);
  SerialModem.begin(115200);
  SerialDebug.println("STARTUP\r\n");

  SIM900.begin();
  SIM900.setInterval(ThreadedGSM::INTERVAL_CLOCK, 60000);
  SIM900.setInterval(ThreadedGSM::INTERVAL_SIGNAL, 60000);
  SIM900.setInterval(ThreadedGSM::INTERVAL_INBOX, 30000);
  SIM900.setHandlers({.signal = signal,
                      .clock = clock,
                      .incoming = sms,
                      .ready = startup,
                      .outgoing = NULL,
                      .power = NULL});
}

void loop() { SIM900.loop(); }
