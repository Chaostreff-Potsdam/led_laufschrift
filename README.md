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