#define MAXTIMINGS 85

class dht22Spark
{
public:
	dht22Spark(int sigPin);
    void init(void);
	int readValues(void);
	int getCelsius(void);
	int getHumidity(void);

private:
	bool read(void);

    int _sigPin;
	int dht22Temperature, dht22Humidity;
    uint8_t lastState = HIGH;
    uint8_t newState = HIGH;
	uint8_t data[5];
    unsigned long results[85];
    uint8_t state[85];
};
