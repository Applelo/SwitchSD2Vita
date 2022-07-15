# Switch SD2Vita

### Switch your mount point between ux0 and uma0 easily for your SD2Vita!

This application simplify the setup to install and manage SD2VITA drivers for both ux0:/ and uma0:/ mounting points.
You can also switch to another mount point if you want (xmc0, imc0, grw0) :)

![alt text](https://pbs.twimg.com/media/DoRtr6UXgAEY8S8.jpg "Screenshot")

SwitchSD2Vita saves a config file in `ux0:data/SwitchSD2Vita` directory. For more informations, see the [F.A.Q section](#faq).

This homebrew uses [StorageMgr](https://github.com/CelesteBlue-dev/PSVita-StorageMgr) by _Celestblue-dev_.

## Changelog

See [changelog file](https://github.com/Applelo/SwitchSD2Vita/blob/master/CHANGELOG.md)

## F.A.Q

### I use an older version of the homebrew, can I update safely ?

Yes, you can. SwitchSD2Vita detect if you have an older installation. You just need to use the uninstall option.

### Where can I download it?

You can download this homebrew [here](https://github.com/Applelo/SwitchSD2Vita/releases) and install like any like Vita homebrew.
But the application is also available on [VitaDB](https://vitadb.rinnegatamante.it/#/info/294) and so, you can install it thanks to the [Vita Homebrew Browser](https://github.com/devnoname120/vhbb).

### The homebrew includes StorageMgr plugin?

Yes. Just install this homebrew to manage your plugin installation.

### How to disable the plugin?

Just use uninstall option and reboot your vita to disable the plugin.

### What is the MCD option added in 2.1 version?

The MCD option was added to answer to the issue [#14](https://github.com/Applelo/SwitchSD2Vita/issues/14).

The official vita memory is not applied as uma0 if you choose the ux0 by default. This option correct this problem with a MCD option which is added in StorageMgr config file (uma0 for ux0 installation or else ux0).

By default, the option is activated but you can easily deactivated this one in the main menu if you want to continue to use it like before the 2.1 update.

### What data are stored by SwitchSD2Vita on my device?

The application store some data :

- the MCD option
- the current version of SwitchSD2Vita you use (to prevent problem with future migrations).

You can find the file _config.json_ in `ux0:data/SwitchSD2Vita` directory.

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

## Creditss

- Developed & maintained by _Applelo_
- _RealYoti_ for StorageMgr 3.74 update
- _theheroGAC_ for updating SwitchSD2Vita
- _yosh_ for the pull request [#5](https://github.com/Applelo/SwitchSD2Vita/pull/5) with fixes
- _Tuxbot123_ for the idea and the bubble customization
- _wababc_ for test and suggestion
- _Celestblue-dev_ for [StorageMgr plugin](https://github.com/CelesteBlue-dev/PSVita-StorageMgr)
- All people bringing pull requests to this project
- _Team Molecule_ for HENkaku and taihen
- All people contributed to VitaSDK
- _xerpi_ for the library vita2D
- _The_FloW_ for file functions and HENkaku 3.65/3.68
- _KanadeEngel_ for database trick
- My master, _MisterAlex_
