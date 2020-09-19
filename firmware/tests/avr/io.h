// Stubs to allow tests to execute AVR code paths

static int TCCR2A;
static int TCCR2B;
static int OCR2A;
static int TIMSK2;

static int WGM21 = 1;
static int CS22 = 2;
static int OCIE2A = 4;

#define ISR(X) void X ()