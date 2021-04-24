#define PRG_BANK_LEVEL_DEFS 4

const extern unsigned char levelFirstScreens[];
const extern unsigned char levelFirstDimensions[];
const extern unsigned char levelStartXPos[];
const extern unsigned char levelStartYPos[];

void load_level(void);
void draw_level_intro(void);