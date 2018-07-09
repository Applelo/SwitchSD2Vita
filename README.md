# Switch SD2Vita

### Switch your mount point between ux0 and uma0 easily for your SD2Vita!

This application simplify the setup to install and manage SD2VITA drivers for both ux0:/ and uma0:/ mounting points.
You can also switch to another mount point if you want (xmc0, imc0, grw0) :)

This homebrew uses [StorageMgr](https://github.com/CelesteBlue-dev/PSVita-StorageMgr) by *Celestblue-dev*.

## Changelog

### Version 2.0 - StorageMgr is better, faster, stronger

- Use PSVita-StorageMgr instead of gamesdcard-microsd (thanks to @CelesteBlue-dev)
- You can choose what mount point you want for your gamesdcard
- Support the 3.68 PSVita Version
- A lot of improvements inside :)

### Version 1.3 - The very small Update

- Support the 3.65/3.67 PSVita Version (thanks to @TheOfficialFloW & @ArkSource)


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

### I use an older version of the homebrew (lower than 2.0), Can I update safely ?

Yes, you can. SwitchSD2Vita 2.0 version detect if you have an old installation. You just need to use the uninstall option.

### Where can I download it?

You can download [here](https://github.com/Applelo/SwitchSD2Vita/releases) and install like any like Vita homebrew.
But the application is also available on [VitaDB](https://vitadb.rinnegatamante.it/#/info/294) and so you can install it thanks to [Vita Homebrew Browser](https://github.com/devnoname120/vhbb).

### The homebrew includes StorageMgr plugin?
Yes. Just install this homebrew to manage your plugin installation.

### How to disable the SD2Vita?
Just use uninstall option and reboot your vita to disable the plugin.

### Can I use without SD2Vita?
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
#emulate in Vita3K but doesn't work :p
make emulate
```

## Credits

* Developped & maintened by *Applelo*
* *Tuxbot123* for the idea and the bubble customization
* *wababc* for test and suggestion
* *Celestblue-dev* for [StorageMgr plugin](https://github.com/CelesteBlue-dev/PSVita-StorageMgr)
* All people bringing pull requests to this project
* *Team Molecule* for HENkaku and taihen
* All people contributed to VitaSDK
* *xerpi* for the library vita2D
* *The_FloW* for file functions and HENkaku 3.65/3.68
* *KanadeEngel* for database trick
* My master, *MisterAlex*
