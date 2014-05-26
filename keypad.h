#ifndef keypad_h
#define keypad_h

#ifdef KEYPAD_PUB
#define KEYPADPUB
#else
#define KEYPADPUB extern
#endif

 
/* Keys commands*/
#define RELEASEKEY      0x00
#define STOP_CMD				0x01
#define ONOFF_CMD       0x02
#define DOOR_CMD				0x40

#ifndef DOOR_DIS
#define GetDoorState() (door_old == 0x40 ? 0/*Door closed*/:1/*Door opened*/)
#else
#define GetDoorState()	0
#endif
/* globals */
KEYPADPUB unsigned char door_old; /* holds a keystroke */
KEYPADPUB unsigned char keypad_stat;
KEYPADPUB unsigned int key_time;
KEYPADPUB unsigned char key_repeat_flg;
KEYPADPUB unsigned char  ChkKeyPad(void);
KEYPADPUB void UpdateDisTimers(void);
KEYPADPUB void event_man(void);
KEYPADPUB void init_keypad(void);

#endif /* keypad_h */
