We have an LED marquee (LED-Laufschrift) that we are trying to reverse engineer and to do fun stuff with it.

* Chip: TMP68HC11A0T
* EPROM: M27C64A-15F
* Dimensions: 7 rows, 60 columns

## EPROM

We extracted the EPROM using a programmer that is compatible with [minipro](https://gitlab.com/DavidGriffith/minipro).

```
minipro -p "M27C64A@DIP28" -r eprom.bin
```

The `eprom.s19` and `eprom.intel` files were produced with the help of [SRecord](http://srecord.sourceforge.net/):

```
srec_cat eeprom.bin -binary -o eprom.s19
srec_cat eeprom.bin -binary -o eprom.intel -intel
```

`eprom.dis` was obtained using the [DHC11 disassembler](https://www.techedge.com.au/utils/dhc11.htm).
As of now, this is the very first attempt, so the disassembly might contain errors - 
e.g. not yet taking vectors into account
(see the [DHC11 tutorial](http://www.techedge.com.au/utils/dhc11tut.htm) for details on how to do that).
The DHC11 output was the following:
![DHC11 output](https://raw.githubusercontent.com/Chaostreff-Potsdam/led_laufschrift/main/dhc11_output.png)
