# Switch SD2Vita
### SD2Vita drivers manager and Switch SD memory between ux0: and uma0: memory easily!

This application simplify the setup to install and manage SD2VITA drivers for both ux0:/ and uma0:/ mounting points.

## F.A.Q

### Where can I downloaded it?

You can download [here](https://github.com/Applelo/SwitchSD2Vita/releases) and install like an PSVita homebrew.
But the application is also available on [VitaDB](https://vitadb.rinnegatamante.it/#/info/294) and so you can install it thanks to [Vita Homebrew Browser](https://github.com/devnoname120/vhbb).

### The homebrew includes both plugins (gamesd for ux0 and uma0)?
Yes. Just install this homebrew to manage your plugin installation.

### How to disable the SD2Vita plugin
Just use uninstall option to disable the plugin.

### Can I use without SD2Vita card?
No. Why? Because... Ok :)

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
