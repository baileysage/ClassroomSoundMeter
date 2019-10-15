// Controls MAX4466 breakout from Adafruit
#define MIC_PIN   A0  // Microphone is attached to this analog pin
#define DC_OFFSET  0  // DC offset in mic signal - if unusure, leave 0
#define NOISE     10  // Noise/hum/interference in mic signal
#define SAMPLES   60  // Length of buffer for dynamic level adjustment
#define TOP       (N_PIXELS + 2) // Allow dot to go slightly off scale
#define PEAK_FALL 40  // Rate of peak falling dot
#define byte short

class Microphone{
    public:
        byte
        peak,      // Used for falling dot
        dotCount,      // Frame counter for delaying dot-falling speed
        volCount;      // Frame counter for storing past volume data
        int
        vol[SAMPLES],       // Collection of prior volume samples
        lvl,      // Current "dampened" audio level
        minLvlAvg,      // For dynamic adjustment of graph low & high
        maxLvlAvg;

        Microphone();
	    virtual ~Microphone();
    private: 
        float fscale( float originalMin, float originalMax, float newBegin, float
        newEnd, float inputValue, float curve);
};