# Switch SD2Vita
### Switch SD memory between ux0: and uma0: memory easily!


The homebrew simplify the SD2Vita setup. You can install your SD like ux0: memory or uma0:. You must reboot your console after.



## Build
Install **VitaSDK** with [**VDPM**](https://github.com/vitasdk/vdpm) and run the followed commands :

```shell
cmake .
make
```

You can also use this followed commands to send directly built files :

```shell
#send eboot.bin file with FTP
make send
#send vpk with FTP
make send_vpk
#copy eboot.bin file with USB
make copy
#send vpk with USB
make copy_vpk
```

## Credits

* *Tuxbot123* for the idea and the bubble customization
* *Team Molecule* for HENkaku and taihen
* [*xyzz* for PS Vita gamecard to microSD adapter](https://github.com/xyzz/gamecard-microsd)
* All people contributed to VitaSDK
* *xerpi* for the library vita2D
* *The_FloW* for file function
* *Rinnegatamente* because I steal a part of your work :p
* My master, *MisterAlex*
