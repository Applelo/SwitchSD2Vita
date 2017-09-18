# Switch SD2Vita
### SD2Vita drivers manager and Switch SD memory between ux0: and uma0: memory easily!

This application simplify the setup to install and manage SD2VITA drivers for both ux0:/ and uma0:/ mounting points.

## Changelog

### Version 1.2 - The small Update

- Detect old installation (1.0 version with uma0 config)
- Small change in menu
- Rename ux0:tai folder
- Update PSVita database on switch
- Add an official changelog
- Fix, always fix :)

### Version 1.1 - Yosh Update

- Now using ur0 config exclusively
- Added auto-switch feature
- Fixed some stuff

### Version 1.0 - First Version

- Initial Release

## F.A.Q

### I use the version 1.0, Can I update ?

Yes, you can. Since SwitchSD2Vita 1.2, the homebrew detect if you have an old installation (only for uma0 installation). You just need to use uninstall option.

### Where can I download it?

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

* Developped by *Appelo* and by *yosh778* (who added great features and fix :) )
* *Tuxbot123* for the idea and the bubble customization
* *Team Molecule* for HENkaku and taihen
* [*xyzz* and *The_Flow* for PS Vita gamecard to microSD adapter](https://github.com/xyzz/gamecard-microsd)
* All people contributed to VitaSDK
* *xerpi* for the library vita2D
* *The_FloW* for file function
* *Rinnegatamente* for some part of file function used in lpp-vita
* *KanadeEngel* for database trick
* My master, *MisterAlex*
