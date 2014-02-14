#define PROGRAM_OFF_ID                0
#define PROGRAM_VU_METER_ID           1
#define PROGRAM_ACCEL_BOUNCE_ID       2
#define PROGRAM_SCATTER_DOWN_ID       3
#define PROGRAM_DOUBLE_BOUNCE_ID      4
#define PROGRAM_SPARKLE_ID            5
#define PROGRAM_WARP_ID               6
#define PROGRAM_PULSE_ID              7
#define PROGRAM_WHITENOISE_ID         8
#define PROGRAM_GRAVITY_DOWN_ID       9

#define PROGRAM_GRAVITY_BOUNCE_ID    10
#define PROGRAM_GRAVITY_UP_ID        11
#define PROGRAM_SWEEP_DOWN_ID        12
#define PROGRAM_SWEEP_UP_ID          13
#define PROGRAM_BOUNCE_ID            14
#define  PROGRAM_EMPTY_1             15
#define  PROGRAM_EMPTY_2             16
#define PROGRAM_DOUBLE_UP_ID         17
#define PROGRAM_DOUBLE_DOWN_ID       18
#define PROGRAM_BOOT_ID              19

#define PROGRAM_GRADIENT_BOUNCE_ID   20
#define PROGRAM_FLICKER_ID           21


typedef struct {
  int id;
  String name;
} ProgramSetting;

const ProgramSetting EMPTY_PROGRAM = {-1,"empty"};


void printStruct(ProgramSetting *in);
void printStruct(ProgramSetting *in)
{
    Serial.print(in->id);
    Serial.print('-');
    Serial.print(in->name);
};

class Programs
{
    public:
        Programs();
        void addProgram(ProgramSetting *in);
        void printPrograms();
        int numberOfPrograms();
        String getProgramName(int idx);

    private:
        int count;
        ProgramSetting programs[22];
};

Programs programs;

Programs::Programs()
{
    count = 0;
}

void Programs::addProgram(ProgramSetting *in)
{
    programs[count] = *in;
    count++;
}

int Programs::numberOfPrograms()
{
    return count;
}

String Programs::getProgramName(int idx)
{
    return programs[idx].name;
}


void setupPrograms()
{
    ProgramSetting a;
    a = EMPTY_PROGRAM;
    a.id = PROGRAM_OFF_ID;
    a.name = "Off";
    programs.addProgram(&a);
    
    ProgramSetting vueter = EMPTY_PROGRAM;
    a.id = PROGRAM_VU_METER_ID;
    a.name = "VU Meter";
    programs.addProgram(&a);
}



char* PROGRAM_00_NAME = "Off";
char* PROGRAM_01_NAME = "VU Meter";
char* PROGRAM_02_NAME = "Accel Bnc";
char* PROGRAM_03_NAME = "SactterDwn";
char* PROGRAM_04_NAME = "DoubleBnc";
char* PROGRAM_05_NAME = "Sparkle";
char* PROGRAM_06_NAME = "Warp";
char* PROGRAM_07_NAME = "Pulse";
char* PROGRAM_08_NAME = "White Noise";
char* PROGRAM_09_NAME = "GravityDown";

char* PROGRAM_10_NAME = "GravityBou";
char* PROGRAM_11_NAME = "GravityUp";
char* PROGRAM_12_NAME = "SweepDown";
char* PROGRAM_13_NAME = "SweepUp";
char* PROGRAM_14_NAME = "Bounce";
char* PROGRAM_15_NAME = "";
char* PROGRAM_16_NAME = "";
char* PROGRAM_17_NAME = "DoubleUp";
char* PROGRAM_18_NAME = "DoubleDown";
char* PROGRAM_19_NAME = "Boot";

char* PROGRAM_20_NAME = "Gradient Bnc";
char* PROGRAM_21_NAME = "Flicker";

//STORED PROGRAM DATA
//char* programNames[] = {
//  PROGRAM_00_NAME, PROGRAM_01_NAME, PROGRAM_02_NAME, PROGRAM_03_NAME, PROGRAM_04_NAME, PROGRAM_05_NAME, PROGRAM_06_NAME, PROGRAM_07_NAME, PROGRAM_08_NAME, PROGRAM_09_NAME,
//  PROGRAM_10_NAME, PROGRAM_11_NAME, PROGRAM_12_NAME, PROGRAM_13_NAME, PROGRAM_14_NAME, PROGRAM_15_NAME, PROGRAM_16_NAME, PROGRAM_17_NAME, PROGRAM_18_NAME, PROGRAM_19_NAME,
//  PROGRAM_20_NAME, PROGRAM_21_NAME
//};


#define SINGLE_BOUNCE false
#define DOUBLE_BOUNCE true

//PROGRAM DECLARATIONS
enum BounceType{NORMAL,SWEEPUP,SWEEPDOWN,GRADIENT,GRAVITY,GRAVITYUP,GRAVITYDOWN,SCATTERDOWN,WARP};
