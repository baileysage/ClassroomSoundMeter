// Controls MAX4466 breakout from Adafruit
#define MIC_PIN        A0  // SoundIO is attached to this analog pin
#define WARN_OUT_PIN   10  
#define ALARM_OUT_PIN  11
#define SOUND_ACTIVE_PIN 12
#define SAMPLE_WINDOW   10  // Sample window for average level
#define PEAK_HANG 24 //Time of pause before peak dot falls
#define PEAK_FALL 4 //Rate of falling peak dot
#define INPUT_FLOOR 10 //Lower range of analogRead input
#define INPUT_CEILING 300 //Max range of analogRead input, the lower the value the more sensitive (1023 = max)
#define METER_CEILING 3

class SoundIO{
    public:
        SoundIO();
	    virtual ~SoundIO();
        int checkMic();
        void playWarning();
        void playAlarm();
    private: 
        float fscale( float originalMin, float originalMax, float newBegin, float
        newEnd, float inputValue, float curve);

        short peak;      // Peak level of column; used for falling dots
        unsigned int sample;

        short dotCount;  //Frame counter for peak dot
        short dotHangCount; //Frame counter for holding peak dot
};