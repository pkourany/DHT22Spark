#include "dht22Spark.h"

dht22Spark::dht22Spark(int sigPin) {
	_sigPin = sigPin;
}

void dht22Spark::init() {
    pinMode(_sigPin, INPUT);
}

int dht22Spark::readValues(void) {
    int _h, _t, _tAndH;
    if (read()) {
        _h = data[0];
        _h *= 256;
        _h += data[1];
        dht22Humidity = _h;

        _t = data[2] & 0x7F;
        _t *= 256;
        _t += data[3];

        if (data[2] & 0x80)
         _t *= -1;
         dht22Temperature = _t;
         _t <<= 16;    
         _tAndH = _t + _h; // combine values to get both with one GET
        return _tAndH;
    }
    return -1; // return -1 if the read fails
}


bool dht22Spark::read(void) {
    uint8_t i, j=0;
    unsigned long t0 = 0;
    unsigned long t1 = 0;
	
    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

    // send start sequence to the DHT22
    pinMode(_sigPin, OUTPUT);
    digitalWrite(_sigPin, LOW);
    delay(20);
    digitalWrite(_sigPin, HIGH);
    delayMicroseconds(40);
    pinMode(_sigPin, INPUT); // switch to input to read from the DHT22

    for (i=0; i< MAXTIMINGS; i++) {

        t0 = micros();
        while (newState == lastState) {
            t1 = micros();
            newState = digitalRead(_sigPin);
            if (t1 - t0 >= 500) break;
        }

        lastState = newState;
        if ((t1 - t0) > 500) break;

        // ignore first 4 transitions
        if (i >= 4  &&  lastState == 0) {
            // shove each bit into the storage bytes
            data[j/8] <<= 1;

            if ((t1 - t0) > 40) // in tests, low values were 22 to 26, and high values were 67 to 73
                data[j/8] |= 1;

            j++;
        }
    }
    // check we read 40 bits and that the checksum matches
    if ((j >= 40) &&  (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)))
        return true;

    return false;
}

int dht22Spark::getCelsius(void) {
	return dht22Temperature;
}

int dht22Spark::getHumidity(void) {
	return dht22Humidity;
}
