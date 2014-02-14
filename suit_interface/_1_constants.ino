
short rotaryDebounce = 100;     // debounce time
short buttonDebounce = 400;     // debounce time

short displaySpeed = 100;
long nextDisplayTime = 0;


// INTERFACE interfaceStates
#define INTERFACE_LIST_PROGRAMS 0
#define INTERFACE_CUSTOMIZE_PROGRAM 1
#define INTERFACE_CUSTOMIZE_PROGRAM_EDIT 2


#define ROWS_OF_TEXT 8



char* propertyNames[] = {"Save",
                         "Brightness",
                         "Tempo",
                         "Eq Band"};//{"Save","Mode","Speed","Duty","Thickness","Fade","Brightness","Input"};

short number_of_programs = programs.numberOfPrograms();
short number_of_properties = sizeof(propertyNames)/2;





//#define PROPERTY_MODE 1
//#define PROPERTY_DUTY 3
//#define PROPERTY_THICKNESS 4
//#define PROPERTY_FADE 5
//#define PROPERTY_INPUT 7

//PROGRAM OPTION DATA
#define PROPERTY_BRIGHTNESS 1
#define PROPERTY_TEMPO 2
#define PROPERTY_EQ_BAND 3

unsigned char propertyValues[] = {0,10,135,0};

